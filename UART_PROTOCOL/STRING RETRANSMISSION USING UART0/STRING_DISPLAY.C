#include<LPC21XX.H>
#include"LCD_DISPLAY.H"

void UART0_CONFIG(void);
unsigned char UART0_RX(void);
void UART0_TX(unsigned char TxByte);

void UART0_STRING(unsigned char*s);


int main(){
	unsigned char RxByte, string[100];
	unsigned int i=0;
	PINSEL0 = 0X5;																								    	PINSEL0 |= 0X5;
	UART0_CONFIG();
	LCD_INIT();
	while(1){
		RxByte = UART0_RX();
		if(RxByte != '\r' && RxByte != '\n'){
			string[i++] = RxByte; 
		}
		else{
			UART0_STRING(string);
			LCD_CMD(0X80);
			LCD_STRING(string);
		}
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


void UART0_STRING(unsigned char*s){
	while(*s){
		UART0_TX (*s++);
	}
}

