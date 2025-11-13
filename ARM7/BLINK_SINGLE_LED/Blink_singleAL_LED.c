#include<lpc21xx.h>
#define AL_LED 1<<0
void delay(int ms){
	int i;
	for( ;ms>0;ms--)
		for(i=12000;i>0;i--);
}
int main(){
	IODIR0 = AL_LED;	//p0.0 is select as output
	IOSET0 = AL_LED;	//power off p0.0(1st LED)
	while(1){
		IOCLR0 = AL_LED; // Power on p0.0 LED pin
		delay(1000);	 // delay of 1-second
		IOSET0 = AL_LED; //power off p0.0 LED pin
		delay(1000);     //delay of 2-second
	}
}