#include<LPC21XX.H>
void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);

int main(){
	unsigned char RxByte;
	PINSEL0 |= 0X5;

	UART0_CONFIG();
	while(1){
		RxByte = UART0_RX();
		RxByte ^= 32;
		UART0_TX(RxByte);
	}
}

void UART0_CONFIG(void){
	U0LCR = 0X83;
	U0DLL = 97; 
	U0DLM = 0;
	U0LCR = 0X03;
}

void UART0_TX(unsigned char TxByte){
	U0THR = TxByte;
	while(((U0LSR>>5)&1)==0);
}

unsigned char UART0_RX(void){
	while((U0LSR & 1)==0);
	return U0RBR;
}
