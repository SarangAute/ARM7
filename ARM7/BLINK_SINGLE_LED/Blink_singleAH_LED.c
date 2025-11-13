#include<lpc21xx.h>
#define led 1<<17
void delay(int ms){
	int i;
	for( ;ms>0; ms--)
		for(i=12000; i>0; i--);
}
int main(){
	IODIR0 = led;
	while(1){
		IOSET0 = led;
		delay(500);
		IOCLR0 = led;
		delay(500);
	}
}