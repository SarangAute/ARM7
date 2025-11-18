#include<LPC21XX.H>
#include "delay.h"
#define LCD_D 0xff
#define RS 1<<8
#define E 1<<9

void CGRAM_WRITE(unsigned char);
void LCD_INIT ();
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);

unsigned char cgram_lut[] ={0x0E,0X1B,0X11,0X11,0X11,0X11,0X1F,0X00,
			0x0E,0X1B,0X11,0X11,0X11,0X1F,0X1F,0X00,
			0x0E,0X1B,0X11,0X11,0X1F,0X1F,0X1F,0X00,
			0x0E,0X1B,0X11,0X1F,0X1F,0X1F,0X1F,0X00,
			0x0E,0X1B,0X1F,0X1F,0X1F,0X1F,0X1F,0X00,
			0x0E,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X00};

int main(){
	char symbol=0;
	LCD_INIT();
	CGRAM_WRITE(48);
	while(1){
		LCD_CMD(0X80);
		LCD_DATA(symbol++);
		delaymilisec(500);
		if(symbol == 6)
			symbol=0;
	}
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
                                        