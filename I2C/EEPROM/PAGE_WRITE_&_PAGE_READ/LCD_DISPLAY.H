#include<LPC21XX.H>
#include"DELAY.H"
#define LCD_D 0XF<<8 // USING 4 LINE INSTEAD 8
#define RS 1<<12
#define E 1<<13


void LCD_CMD(unsigned char cmd){
	IOCLR0 = LCD_D;
	IOSET0 = (cmd>>4 & 0x0F)<<8;
	IOCLR0 = RS;
	IOSET0 = E;
	delaymilisec(2);
	IOCLR0 = E;

	IOCLR0 = LCD_D;
	IOSET0 = (cmd & 0x0F)<<8;
	IOCLR0 = RS;
	IOSET0 = E;
	delaymilisec(2);
	IOCLR0 = E;
}


void LCD_INIT(){
	IODIR0 |= LCD_D|RS|E;
	LCD_CMD(0x03); 
  	LCD_CMD(0x02); 
  	LCD_CMD(0x28); 
  	LCD_CMD(0x0C); 
 	LCD_CMD(0x01); 
  	LCD_CMD(0x06); 
}


void LCD_DATA(unsigned char d){
	IOCLR0 = LCD_D;
	IOSET0 = (d>>4 & 0x0F)<<8;
	IOSET0 = RS;
	IOSET0 = E;
	delaymilisec(2);
	IOCLR0 = E;
	
	IOCLR0 = LCD_D;
	IOSET0 = (d & 0X0F)<<8;
	IOSET0 = RS;
	IOSET0 = E;
	delaymilisec(2);
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
	   
