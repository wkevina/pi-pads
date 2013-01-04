/****************************
* input_device.c
*
*
*
****************************/
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sysexits.h>
	
#include <string.h>

#include <sys/ioctl.h>
	
#include <linux/input.h>
#include <linux/uinput.h>

/*

uinput IOCTL codes

#define UINPUT_IOCTL_BASE      
#define UI_DEV_CREATE           
#define UI_DEV_DESTROY          
 
#define UI_SET_EVBIT            
#define UI_SET_KEYBIT           
#define UI_SET_RELBIT           
#define UI_SET_ABSBIT           
#define UI_SET_MSCBIT           
#define UI_SET_LEDBIT           
#define UI_SET_SNDBIT           
#define UI_SET_FFBIT            
#define UI_SET_PHYS             
#define UI_SET_SWBIT

input event struct

struct input_event {
	struct timeval time;
	__u16 type;
	__u16 code;
	__s32 value;
};


uinput device struct

struct uinput_user_dev {
	char name[80];
	struct input_id id;
	int ff_effects_max;
	int absmax[ABS_MAX + 1];
	int absmin[ABS_MAX + 1];
	int absfuzz[ABS_MAX + 1];
	int absflat[ABS_MAX + 1];
};

*/

void wait_for_term(){
	sigset_t signals;

	sigfillset(&signals);

	int signum;

	while(sigwait(&signals, &signum) != -1)
	    if(signum == SIGINT)
	        break;
}

int send_button_event(int input_fd, unsigned short code){
	
	struct input_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.type = EV_KEY;
	ev.code = code;
	ev.value = 0x0001;
	
	int ret = write(input_fd, &ev, sizeof(ev));	
	ev.value = 0x0000;	
	ret = write(input_fd, &ev, sizeof(ev));
	
	return ret;
}

void poll_user(int input_fd){
	
	printf("Press the keys 0-9 to generate button events.");
	
	char key;
	
	while(1){
		key = getchar();
		if (key == 'q' || key == 'Q')
			break;
		
		if (key >= '0' && key <= '9') {
			if( send_button_event(input_fd, BTN_GAMEPAD + key - 48) < 0 )
				break;
		}
	}	
}

int main() {
	int uinput_fd;
	
	// Open the uinput device file, which is our way to talk to the uinput system
	uinput_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	// Quit if the file couldn't be opened
	if (uinput_fd < 0) {
		printf("Can't open uinput\n");
		exit(EXIT_FAILURE);
	}
	
	// Tell uinput what event types we'll be sending
	
	int ret;
	
	ret = ioctl(uinput_fd, UI_SET_EVBIT, EV_KEY);
	if (ret < 0) {
		printf("Can't set key bit\n");
		exit(EXIT_FAILURE);
	}
	ret = ioctl(uinput_fd, UI_SET_EVBIT, EV_SYN);
	if (ret < 0) {
		printf("Can't set syn bit\n");
		exit(EXIT_FAILURE);
	}
	
	int key;
	for (key = BTN_GAMEPAD; key <= BTN_THUMBR; ++key) {
		ret = ioctl(uinput_fd, UI_SET_KEYBIT, key);	
		if (ret < 0) {
			printf("Can't set all buttons\n");
			exit(EXIT_FAILURE);
		}	
	}
	
	struct uinput_user_dev user_device; // Describes the input device for uinput
	memset(&user_device, 0, sizeof(user_device)); // Initialize everything to nil
	
	// Fill in the uinput_user_dev struct
	snprintf(user_device.name, UINPUT_MAX_NAME_SIZE, "pipad-input");
	user_device.id.bustype = BUS_USB;
	user_device.id.vendor  = 0xF0F0;
	user_device.id.product = 0xBABA;
	user_device.id.version = 1;

	ret = write(uinput_fd, &user_device, sizeof(user_device));
	if (ret < 0) {
		printf("Can't create device\n");
		exit(EXIT_FAILURE);
	}
	
	ret = ioctl(uinput_fd, UI_DEV_CREATE);	
	if (ret < 0) {		
		printf("Can't create device\n");		
		exit(EXIT_FAILURE);	
	}
		
	//wait_for_term();
	
	poll_user(uinput_fd);
	
	ret = ioctl(uinput_fd, UI_DEV_DESTROY);
	close(uinput_fd);
	
    return EX_OK;
}
