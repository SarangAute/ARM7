#include<LPC21XX.H>
#define LCD_D 0xff
#define RS 1<<8
#define E 1<<9


unsigned char CGRAM_LUT[]={
	0x0E,0x11,0x11,0x1F,0x1F,0x1F,0x1F,0x00,
	0x04,0x0E,0x0E,0x0E,0x04,0x00,0x04,0x00,
	0x0E,0x11,0x01,0x1F,0x1F,0x1F,0x1F,0x00,
	0x0A,0x1F,0x1F,0x0E,0x04,0x00,0x00,0x00
};


void delaymilisec(int n){
	int i;
	for(;n>0;n--)
		for(i=12000;i>0;i--);
}


void LCD_CMD(unsigned char cmd){
	IOPIN0 = (IOPIN0&0XFFFFFF00)|cmd;
	//IOCLR0=LCD_D;
	//IOSET0=cmd;
	IOCLR0 = RS;
	IOSET0=E;
	delaymilisec(2);
	IOCLR0=E;
}


void LCD_INIT(void){
	IODIR0 = LCD_D|RS|E;
	LCD_CMD(0X01);
	LCD_CMD(0X02);
	LCD_CMD(0X0C);
	LCD_CMD(0X38);
}



void LCD_DATA(unsigned char d){
	IOPIN0 = (IOPIN0&0XFFFFFF00)|d;
	//IOCLR0=LCD_D;
	//IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delaymilisec(2);
	IOCLR0=E;
}

void LCD_STRING(unsigned char* s){
	int count=0;
	while(*s){
		LCD_DATA(*s++);
		count++;
		if(count == 16)
			LCD_CMD(0xc0);
	}
}

void CGRAM_WRITE(unsigned char n){
	unsigned char i;
	LCD_CMD(0X40);
	for(i=0;i<n;i++)
		LCD_DATA(CGRAM_LUT[i]);
}


int main(){
	char s[] = "BE HAPPY & HAVE GREAT FUTURE.. ";
	int i,n,j;
	LCD_INIT();
	CGRAM_WRITE(32);
	LCD_CMD(0X80);
	LCD_DATA(0);
	LCD_CMD(0X81);
	LCD_DATA(1);
	LCD_CMD(0XC0);
	LCD_DATA(2);
	LCD_CMD(0XC1);
	LCD_DATA(3);
	
	LCD_CMD(0X83);
	LCD_STRING("HELLO GUYS");
	
	while(1){
		for(i=0;s[i];i++);
		n=i;
		
		for(i=0;i<n;i++){
			LCD_CMD(0XC2);
			for(j=0;j<16;j++){
				LCD_DATA(s[(i+j)%n]);
			}
		delaymilisec(100);
		}
	}
}

