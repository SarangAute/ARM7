#include<lpc21xx.h>
#define LED 1<<17
#define SW 14
int main(){
	IODIR0 = LED;
	while(1){
		if(((IOPIN0>>SW)&1)==0)
			IOCLR0=LED;
		else
			IOSET0 = LED;
	}
}