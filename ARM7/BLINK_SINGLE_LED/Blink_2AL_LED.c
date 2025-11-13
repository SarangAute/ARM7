#include<lpc21xx.h>
#define LED0 1<<0
#define LED1 1<<1

void delay(int ms){
	int i;
	for( ;ms>0;ms--)
		for(i=12000;i>0;i--);
}
int main(){
	IODIR0 = LED0|LED1;
	IOSET0 = LED0|LED1;

	while(1){
		IOCLR0 = LED0|LED1;
		delay(1000);
		IOSET0 = LED0|LED1;
		delay(1000);
	}
}