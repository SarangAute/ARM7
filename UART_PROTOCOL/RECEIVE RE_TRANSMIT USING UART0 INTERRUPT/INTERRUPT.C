#include<lpc21xx.h>
#define LED 1<<17
#define SW 14

void UART0_CONFIG(void){
	PINSEL0 |= 0X5;
	U0LCR= 0X83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0X03;
}

void uart0_isr(void)__irq{
	int temp;
	temp = U0IIR;
	if(temp == 0x04)
		U0THR = U0RBR;
	VICVectAddr =0 ;	
}

int main(){
	IODIR0 = LED;
	UART0_CONFIG();
	VICIntSelect = 0;
	VICVectCntl0 = (0X20)|6;
	VICVectAddr0 = (unsigned long)uart0_isr;
	U0IER = (1<<1)|(1<<0);
	VICIntEnable = 1<<6;

	while(1){
		if (((IOPIN0>>SW)&1)==0)
			IOCLR0 = LED;
		else
			IOSET0 = LED;
	}
}
