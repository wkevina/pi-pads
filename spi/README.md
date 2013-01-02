## Raspberry Pi SPI Example program

This is a simple C program that demonstrates the basic method of accessing the SPI port on the Raspberry Pi, as well as a simple test of the hardware.

## Instructions

To build the program, simply type `make` while in the directory that contains this file you are reading.

To run the program, type:

	sudo build/spi-test /dev/spidev0.0

Note: The program must be run with sudo, as only the root user is allowed to access the SPI device.  Future developments may involve making a symlink to this device that is allowed to be read by a group that we create.  That will simplify deployment for the user.

You should see some output in the console, the final line being the value read from the SPI interface.  It should be zero unless you connect a loopback jumper to the MOSI and MISO pins.

