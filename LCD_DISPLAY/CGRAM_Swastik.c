#include<LPC21XX.H>
#include "delay.h"
#define LCD_D 0xff
#define RS 1<<8
#define E 1<<9

void CGRAM_WRITE(unsigned char);
void LCD_INIT ();
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);

unsigned char cgram_lut[] ={0x17,0x14,0x14,0x1F,0x05,0x05,0x1D,0x00};

int main(){
	LCD_INIT();
	CGRAM_WRITE(8);
	LCD_CMD(0X80);
	LCD_DATA(0);
}

void CGRAM_WRITE(unsigned char n){
	unsigned char i;
	LCD_CMD(0X40);
	for(i=0;i<n;i++)
		LCD_DATA(cgram_lut[i]);
}

void LCD_INIT(){
	IODIR0=LCD_D|RS|E;
	LCD_CMD(0X01);
	LCD_CMD(0X02);
	LCD_CMD(0X0C);
	LCD_CMD(0X38);
}

void LCD_CMD(unsigned char cmd){
	IOCLR0=LCD_D;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delaymilisec(2);
	IOCLR0=E;
}
void LCD_DATA(unsigned char d){
	IOCLR0=LCD_D;
	IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delaymilisec(2);
	IOCLR0=E;
}
                                        