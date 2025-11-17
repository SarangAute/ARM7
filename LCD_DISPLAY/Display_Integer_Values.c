#include<LPC21XX.H>
#include "delay.H"
#define LCD_D 0xff
#define RS 1<<8
#define E 1<<9

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INTEGER(int);

int main(){
	LCD_INIT();
	LCD_CMD(0x80);
	LCD_INTEGER(-1234);
}
void LCD_INIT(void){
	IODIR0 = LCD_D|RS|E;
	LCD_CMD(0X01);
	LCD_CMD(0X02);
	LCD_CMD(0X0C);
	LCD_CMD(0X38);
}

void LCD_CMD(unsigned char cmd){
	IOCLR0 = LCD_D;
	IOSET0 = cmd;
	IOCLR0 = RS;
	IOSET0 = E;
	delaymilisec(2);
	IOCLR0 = E;
}			    

void LCD_DATA(unsigned char d){
	IOCLR0=LCD_D;
	IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delaymilisec(2);
	IOCLR0=E;
}

void LCD_INTEGER(int n){
	unsigned char a[5];
	signed char i =0;
	if(n==0){
		LCD_DATA ('0');
	}
	else if(n<0){
		LCD_DATA('-');
		n=-n;
	}
	while(n>0){
		a[i++] = n%10;
		n=n/10;
	}
	for(--i;i>=0;i--)
		LCD_DATA(a[i]+48);
}