/*TASK 1 - CONTROL LED1 USING PUSH BUTTON SWITCH 
  TASK 2 - TOGGLE LED2 INFINITELY @500ms   */

#include<lpc21xx.h>
#define LED1 1<<17
#define LED2 1<<16
#define SW 14

int FLAG = 0;

void TIMER0_ISR(void) __irq{
	T0IR = 0X01;	 
	if(FLAG == 0){
		IOSET0 = LED2;
		FLAG =1;
	}
	else{
		 IOCLR0 = LED2;
		 FLAG = 0;
	}
}
int main(){
	IODIR0 = LED1|LED2;
	T0MR0 = 7500000-1;
	T0MCR = 0X03;
	VICIntSelect = 0;
	VICVectCntl0 = (0X20)|4;
	VICVectAddr0 = (unsigned long)TIMER0_ISR;
	VICIntEnable = 1<<4;
	T0TCR = 0X01;

	while(1){
		if(((IOPIN0>>SW)&1)==0){
			IOCLR0 = LED1;
		}
		else
			IOSET0 = LED1;
	}
}