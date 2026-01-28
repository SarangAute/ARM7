#include<LPC21XX.H>
#include"DELAY.H"
#define LCD_D 0XF<<4  // USING 4 LINE INSTEAD 8
#define RS 1<<8
#define E 1<<9


void LCD_CMD(unsigned char cmd){
	IOCLR0 = LCD_D;
	IOSET0 = (((cmd>>4)&0x0F)<<4);
	IOCLR0 = RS;
	IOSET0 = E;
	DelayMiliSec(2);
	IOCLR0 = E;

	IOCLR0 = LCD_D;
	IOSET0 = ((cmd&0x0F)<<4);
	IOCLR0 = RS;
	IOSET0 = E;
	DelayMiliSec(2);
	IOCLR0 = E;
}


void LCD_INIT(){
	IODIR0 = LCD_D|RS|E;
	LCD_CMD(0X01);
	LCD_CMD(0X02);
	LCD_CMD(0X0C);
	LCD_CMD(0X28); 		// FOR 4 LINE Tx
}


void LCD_DATA(unsigned char d){
	IOCLR0 = LCD_D;
	IOSET0 = (((d>>4)&0x0F)<<4);
	IOSET0 = RS;
	IOSET0 = E;
	DelayMiliSec(2);
	IOCLR0 = E;
	
	IOCLR0 = LCD_D;
	IOSET0 = (d&0X0F)<<4;
	IOSET0 = RS;
	IOSET0 = E;
	DelayMiliSec(2);
	IOCLR0 = E;
}

void LCD_STRING(unsigned char* S){
	int count = 0;
	while(*S){
		LCD_DATA(*S++);
		count++;
		if(count == 16)
			LCD_CMD(0XC0);
	}
}

void LCD_INTEGER(int n)
{
	unsigned char a[5];
	signed int i=0;
	if(n==0)
		LCD_DATA('0');
	else if (n<0){
		LCD_DATA('-');
		n=-n;
		}
	
	while(n>0){
		a[i++]=(n%10);
		n=n/10;
	}
	for(--i;i>=0;i--)
		LCD_DATA(a[i]+48);	
}

