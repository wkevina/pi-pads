/****************************
* input_device.c
* 
* 
*
****************************/
	
#include <signal.h>
	
int main() {
	
	while(sigwait(&signals, &signum) != -1)
        if(signum == SIGTERM)
            break;
    
    return EX_OK;
	
}