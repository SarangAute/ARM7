#include<lpc21xx.h>
#include"lcd_display.h"

void i2c_init(void);
void start(void);
void write(char);
void stop(void);
char read(void);
char ack(void);


int main(){
	char ch;
	i2c_init();
	LCD_INIT();
	LCD_CMD(0X80);
	write(0xa0);
	write(0x00);
	write('S');
	stop();
	delaymilisec(1000);
	ch=read();
	LCD_STRING("I2C");
	LCD_CMD(0XC0);
	LCD_STRING("READ BYTE: ");
	LCD_DATA(ch);
}

void i2c_init(){
	PINSEL0 |= 0X50;	//P0.2,P0.3
	I2SCLL=75;
	I2SCLH=75;		    
	I2CONSET=1<<6;		//I2EN
	start();
}

void start(){
	I2CONSET=1<<5;		//STA BIT
	I2CONCLR=1<<3;		//SI FLAG
	while(((I2CONSET>>3)&1)==0);
	I2CONCLR=1<<5;
}

void write(char x){
	I2DAT=x;
	I2CONCLR=1<<3;
	while(((I2CONSET>>3)&1)==0);
}

void stop(void){
	I2CONSET=1<<4;		//STO BIT
	I2CONCLR=1<<3;
}

char read(void){
	char ch;
	start();
	write(0xa0);
	write(0x00);
	start();
	write(0xa1);  //SLAVE ADD WITH READ BIT
	ch=ack();
	stop();
	return ch;
}  

char ack(void){
	char ch;
	I2CONSET = 1<<2;  //AA BIT
	I2CONCLR=1<<3;
	while(((I2CONSET>>3)&1)==0);
	ch = I2DAT;
	return ch;
}

