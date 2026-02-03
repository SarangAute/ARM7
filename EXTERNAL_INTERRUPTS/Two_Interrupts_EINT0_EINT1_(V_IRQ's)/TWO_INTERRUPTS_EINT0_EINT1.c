#include<LPC21XX.H>
#define LED1 1<<0
#define LED2 1<<1


void EXT_INT0_ISR(void) __irq{
	EXTINT = 0X01;
	IOSET0 = LED1;
	IOCLR0 = LED1;
	VICVectAddr = 0;
}

void EXT_INT1_ISR(void) __irq{
	EXTINT = 0X02;
	IOSET0 = LED2;
	IOCLR0 = LED2;
	VICVectAddr = 0;
}

int main(){
	unsigned int COUNT = 0;
	PINSEL1 = 0X01;
	PINSEL0=0X20000000;

	IODIR0 = LED1|LED2;
	VICIntSelect = 0;

	/* SLOT 0 */
	VICVectCntl0 = (0X20)|14;
	VICVectAddr0 = (unsigned long)EXT_INT0_ISR;

	/* SLOT 1 */
	VICVectCntl1 = (0X20)|15;
	VICVectAddr1= (unsigned long)EXT_INT1_ISR;

	/* TRIGGERING MODE */
	EXTMODE = 0x03;	//EDGE SENSITIVE
	EXTPOLAR = 0x00; // FALLING EDGE
	
	VICIntEnable=(1<<14)|(1<<15);

	while(1){
		COUNT++;
	}
}
