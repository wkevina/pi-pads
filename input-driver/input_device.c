/****************************
* input_device.c
* 
* 
*
****************************/
	
#include <signal.h>
#include <sysexits.h>
	
int main() {
	
	sigset_t signals;
	
	sigfillset(&signals);
	
	int signum;
	
	while(sigwait(&signals, &signum) != -1)
        if(signum == SIGINT)
            break;
    
    return EX_OK;
	
}