#include<LPC21XX.H>

void UART0_CONFIG(void){
	U0LCR = 0X83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0X03;
}

void UART0_Tx(unsigned char TxBytes){
	U0THR = TxBytes;
	while(((U0LSR>>5)&1)==0);
}

int main(){
	unsigned char ALP='A';
	PINSEL0 |= 0X5;
	UART0_CONFIG();
	while(1){
		UART0_Tx(ALP++);
		if(ALP > 'Z'){
			ALP = 'A';
			UART0_Tx('\r');
			UART0_Tx('\n');
		}
	} 
}
