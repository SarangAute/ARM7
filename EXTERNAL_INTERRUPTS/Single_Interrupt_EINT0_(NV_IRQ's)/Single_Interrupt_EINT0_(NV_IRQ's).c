#include<LPC21XX.H>
#define LED1 1<<0

void non_vect_isr(void)__irq{
	EXTINT = 0X01;
	IOSET0 = LED1;
	IOCLR0 = LED1;
	VICVectAddr = 0;
}

int main(){
	unsigned int count=0;
	PINSEL1=0X01;
	IODIR0 = LED1;
	VICIntSelect = 0;
	VICDefVectAddr = (unsigned long)non_vect_isr;
	
	EXTMODE = 0X01;
	EXTPOLAR = 0X00;
	
	VICIntEnable = 1<<14;
	
	while(1){
		count++;
	}
}
