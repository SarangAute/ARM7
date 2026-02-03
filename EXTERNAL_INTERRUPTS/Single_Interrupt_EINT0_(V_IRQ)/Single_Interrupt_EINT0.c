/*ECP FOR EINT0 INTERRUPT USING LPC2129
1) SELECT VECTORED IRQ
2) ALLOCATE SLOT 0
3) SELECT LOW LEVEL SENSITIVITY         */

#include<LPC21XX.H>
#define  LED1 1<<17

/********EINT0 ISR********/
void ext_int0_isr(void)__irq{
	EXTINT = 0X01; //TO CLEAR EINT0 FLAG

	IOSET0 = LED1;
	IOCLR0 = LED1;
	VICVectAddr = 0; //INDICATE END OF ISR
}
/*******END OF EINT0 ISR*******/

int main (){
	unsigned int count =0;
	/**** CONFIGUR THE PINS****/
	PINSEL1 = 0X01; //P0.16 IS CONFIGURED AS EINT0 PIN
	IODIR0 = LED1;	//P0.17 AS OUTPUT PIN
	/**************************/

	/****CONFIGUR THE INTERRUPTS****/
	VICIntSelect =0;  //ALL ARE IRQ's
	VICVectCntl0 = (0X20)|14; //14=EINT0
	VICVectAddr0 = (unsigned long)ext_int0_isr;
	/*******************************/

	/**SELECT TRIGERRING MODE FOR EINT0**/
	EXTMODE = 0X00;
	EXTPOLAR = 0X00;
	/************************************/

	VICIntEnable = 1<<14; //TO ENABLE EINT0 INTERRUPT

	/***MAIN LINE CODE***/
	while(1){
		count++;
	}
	/********************/
}
