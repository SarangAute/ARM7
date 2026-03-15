#include<LPC21XX.H>
#include<stdio.h>

void UART0_INIT(unsigned int Baud){
	PINSEL0 |= 0X5;
	U0LCR = 0X83;
	switch(Baud){
		case 115200: U0DLL = 32;	break;	//PCLK = 60MHz
		case 921600: U0DLL = 4;	break;
		default: U0DLL = 32;
	}
	U0LCR = 0X03;
}

void UART0_TX(unsigned char TxBit){
	U0THR = TxBit;
	while((U0LSR&(1<<5))==0);
}

unsigned char UART0_RX(void){
	while((U0LSR & 0X1)==0);
	return U0RBR;
}

void UART0_STRING(char *s){
	while(*s)
		UART0_TX(*s++);
}

void UART0_INTEGER(int num){
	char buff[15];
	sprintf(buff,"%d",num);
	UART0_STRING(buff);
}

void UART0_HEX(int num){
	char buff[15];
	sprintf(buff,"%x",num);
	UART0_STRING(buff);
}
