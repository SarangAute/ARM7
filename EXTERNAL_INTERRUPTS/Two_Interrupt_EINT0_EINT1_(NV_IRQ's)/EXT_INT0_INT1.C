#include<LPC21XX.H>
#define LED1 1<<0
#define LED2 1<<1

void ext_int_isr(void)__irq{
	if((VICIRQStatus>>14)&1){
		EXTINT = 0X01;
		IOSET0 = LED1;
		IOCLR0 = LED1;
	}
	if((VICIRQStatus>>15)&1){
		EXTINT = 0X02;
		IOSET0 = LED1;
		IOCLR0 = LED1;
	}
	VICVectAddr =0;
}

int main(){
	unsigned int count = 0;
	PINSEL1 = 0X01;
	PINSEL0 = 0X20000000;
	IODIR0 = LED1|LED2;
	VICIntSelect = 0;
	
	VICDefVectAddr = (unsigned long)ext_int_isr;
	
	EXTMODE = 0X03;
	EXTPOLAR = 0X00;
	
	VICIntEnable = (1<<14)|(1<<15);
	
	while(1){
		count++;
	} 
}
