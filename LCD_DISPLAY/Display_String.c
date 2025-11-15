#include<LPC21XX.H>
#include "delay.h"
#define LCD_D 0XFF
#define RS 1<<8
#define E 1<<9

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STRING(unsigned char*);

int main(){
	LCD_INIT();
	LCD_CMD(0X80);
	LCD_STRING("EMBEDDED");
}

void LCD_INIT(void){
	IODIR0 = LCD_D|RS|E;
	LCD_CMD(0X01);
	LCD_CMD(0X02);
	LCD_CMD(0X0C);
	LCD_CMD(0X38);
}
void LCD_CMD(unsigned char cmd){
	//IOPIN0 = cmd;
	IOCLR0=LCD_D;
	IOSET0=cmd;
	IOCLR0 = RS;
	IOSET0=E;
	delaymilisec(2);
	IOCLR0=E;
}
void LCD_DATA(unsigned char d){
	IOCLR0=LCD_D;
	IOSET0=RS;
	IOSET0=E;
	delaymilisec(2);
	IOCLR0=E;
}
void LCD_STRING(unsigned char* s){
	while(*s)
	LCD_DATA(*s++);
}