#include<LPC21XX.H>
#define LED 1<<17
#define SW 14

char str[] = "Sarang";
volatile int i = 0;

void UART0_CONFIG(void){
	PINSEL0 = 0X5;
	U0LCR = 0X83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0X03;
}

void UART0_ISR(void)__irq{
	int temp;
	
	if(str[i]!='\0'){
		U0THR = str[i++];
	}
	else{
		 temp = U0IIR;  //reading this register to clear interrupt
	}
	VICVectAddr =0;
}

int main(){
	IODIR0 = LED;		    
	UART0_CONFIG();
	VICIntSelect = 0;
	VICVectCntl0 = (0x20)|6;
	VICVectAddr0 = (unsigned long)UART0_ISR;
	U0IER = 1<<1; //ENABLE THRE INTERRUPT
	VICIntEnable = 1<<6;
	U0THR = str[i++];
	while(1){
		if(((IOPIN0>>SW)&1)==0)
			IOCLR0 = LED;
		else
			IOSET0 = LED;
	}
}
