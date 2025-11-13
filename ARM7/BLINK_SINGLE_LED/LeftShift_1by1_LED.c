#include<lpc21xx.h>
#define LEDs 0XFF	//00.....11111111 = 0xff

void delay(int ms){
	int i;
	for( ;ms>0;ms--)
		for(i=12000;i>0;i--);
}

int main(){
	IODIR0 = LEDs;
	IOSET0 = LEDs;

	while(1){
	int j;
		for(j=0;j<8;j++){
			IOCLR0 = 1<<j;	  //leds will on 1 by 1 with dealy of 1 sec..
			delay(1000);
		}
		IOSET0 = LEDs;	  // all leds will get off in single instruction
		delay(500);
	}
}