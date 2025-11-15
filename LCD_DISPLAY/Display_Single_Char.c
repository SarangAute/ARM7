#include<lpc21xx.h>
#include"delay.h"
#define LCD_D 0xff
#define RS 1<<8
#define E 1<<9

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);

int main(){
	char i;
	LCD_INIT();
	
	while(1){
		for(i='A';i<='Z';i++){
			LCD_CMD(0x80);
			LCD_DATA(i);
			delaymilisec(500);
		}
	}
}
void LCD_INIT(){
	IODIR0 = LCD_D|RS|E;
	LCD_CMD(0X01);
	LCD_CMD(0X02);
	LCD_CMD(0X0C);
	LCD_CMD(0X38);
}
void LCD_CMD(unsigned char cmd){
	IOPIN0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delaymilisec(2);
	IOCLR0=E;
}
void LCD_DATA(unsigned char d){
	IOPIN0=d;
	IOSET0=RS;
	IOSET0=E;
	delaymilisec(2);
	IOCLR0=E;
}