/******************************************************************************
*
* spi_test.c
* author: Kevin Ward
* ----------------------------------------------------------
* Simple program to test SPI transfers.	 Based on an example 
* from Tino Goehlert <http://www.cmdrkeen.net/> 
*
*
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

// some defines for our SPI config
#define SPI_MODE 0 /// SPI Mode
#define SPI_BITS_PER_WORD 8 ///
// we're sending bytewise
#define SPI_MAX_SPEED 1000000 /// maximum speed is 1Mhz

//global spi file descriptor
int spi_fd;

/* spi_wr_1b: * - sending one byte and write the received byte into the send
buffer. */
char spi_wr_1b(unsigned char data, int delay) {
	
	int ret = 0;
	struct spi_ioc_transfer spi;

	spi.tx_buf = (unsigned long) &data;
	spi.rx_buf = (unsigned long) &data;
	spi.len = 1;
	spi.delay_usecs = delay;
	spi.speed_hz = 0;
	spi.bits_per_word = 0;

	if(ret = ioctl (spi_fd, SPI_IOC_MESSAGE(1), &spi) < 0){
		printf("ERROR while sending: %s\n", strerror(errno));
	}
	return data;
}

/*spi_open * - Open the given SPI channel and configures it. * - there are 
normally two SPI devices on your PI: * /dev/spidev0.0: activates the CS0 pin 
during transfer * /dev/spidev0.1: activates the CS1 pin during transfer */ 
int spi_open(char* dev) {
	
	int _mode = SPI_MODE;
	int _bpw = SPI_BITS_PER_WORD;
	int _speed = SPI_MAX_SPEED;

	if((spi_fd = open(dev, O_RDWR)) < 0){
		printf("error opening %s\n",dev);
		return -1;
	} else {
		printf("%s opened successfully ;-)\n",dev);
	}

	if (ioctl (spi_fd, SPI_IOC_WR_MODE, &_mode) < 0)
		return -1 ;
	if (ioctl (spi_fd, SPI_IOC_RD_MODE, &_mode) < 0)
		return -1 ;

	if (ioctl (spi_fd, SPI_IOC_WR_BITS_PER_WORD, &_bpw) < 0)
		return -1 ;
	if (ioctl (spi_fd, SPI_IOC_RD_BITS_PER_WORD, &_bpw) < 0)
		return -1 ;

	if (ioctl (spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &_speed) < 0)
		return -1 ;
	if (ioctl (spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &_speed) < 0)
		return -1 ;
	
	printf("Mode: %i\nBPW: %i\nSpeed: %i\n", _mode, _bpw, _speed);
	
	return 0;
}

int main(int argc, char* argv[]) {
	
	unsigned char data = 0xA2;

	if(argc <= 1){
		printf("too few args, try %s /dev/spidev0.0\n",argv[0]);
		return -1;
	}

	// open and configure SPI channel. (/dev/spidev0.0 for example)
	if(spi_open(argv[1]) < 0){
		printf("spi_open failed\n");
		return -1;
	}

	// send one byte - receive one byte.
	spi_wr_1b(data,0);
	printf("RECEIVED: %.2X\n",data);

	// close SPI channel
	close(spi_fd);

	return 0; 
}
