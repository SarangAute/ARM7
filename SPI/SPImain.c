#include<lpc21xx.h>
#include"lcd_display.h"

void SPI_INIT(char mode);
float READ(char ch_no);
unsigned char SPI_DAT(char DATA);

int main(){
	float Fval;
	LCD_INIT();
	LCD_CMD(0X86);
	LCD_STRING("SPI");
	SPI_INIT(3);
	while(1){
		Fval=READ(0);
		LCD_CMD(0XC0);
		LCD_STRING("VOLTAGE: ");
		LCD_FLOAT(Fval);
		//LCD_CMD(0X01);
	}

}

void SPI_INIT(char mode){
	PINSEL0 |= 0X1500;
	S0SPCCR = 150;
	IODIR0 |=1<<7;
	S0SPCR=(1<<5|mode<<3);
}
float READ(char ch_no){
	char Hbit,Lbit;
	int value;
	IOCLR0=1<<7;	//selecting slave for start tx and rx
	SPI_DAT(0X06);
	Hbit=SPI_DAT(ch_no<<6);
	Lbit=SPI_DAT(0x00);
	IOSET0=1<<7;	//stop slave tx and rx 
	value = (((Hbit & (0x0f))<<8)| Lbit);
	return ((value * 3.3)/4096);
}

unsigned char SPI_DAT(char DATA){
	S0SPDR=DATA;
	while(((S0SPSR>>7)&1)==0);
	return S0SPDR;
}
