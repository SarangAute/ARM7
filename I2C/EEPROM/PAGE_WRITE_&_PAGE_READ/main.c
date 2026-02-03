#include<lpc21xx.h>
#include"lcd_display.h"

void I2C_INIT(void);
void START(void);
void WRITE(char);
void STOP(void);
void READ(void);
char ACK(void);
void NACK(void);

int i;
unsigned char ReadB[20];

int main(){
	char data[]="AUTE";
	I2C_INIT();
	LCD_INIT();
	LCD_CMD(0X80);
	LCD_STRING("I2C PAGE W & R");
	START();
	WRITE(0XA0);
	WRITE(0X00);
	for(i=0;i<4;i++)
		WRITE(data[i]);	
	
	STOP();	
	delaymilisec(1000);
	READ();
	LCD_CMD(0XC0);
	LCD_STRING(ReadB);
}

void I2C_INIT(void){
	PINSEL0 |= 0X50;
	I2SCLL = 75;
	I2SCLH = 75;
	I2CONSET = 1<<6;
}

void START(void){
	I2CONSET = 1<<5;
	I2CONCLR = 1<<3;
	while(((I2CONSET>>3)&1)==0);
	I2CONCLR = 1<<5;
}

void WRITE(char x){
	I2DAT = x;
	I2CONCLR = 1<<3;
	while(((I2CONSET>>3)&1)==0);
}

void STOP(void){
	I2CONSET = 1<<4;
	I2CONCLR = 1<<3;
}

void READ(void){
	char ch;
	START();
	WRITE(0XA0);
	WRITE(0X00);
	START();
	WRITE(0XA1);
	for(i=0;i<4;i++){
		ch=ACK();
		ReadB[i]=ch;
	}
	NACK();
	STOP();
}

char ACK(void){
	char ch;
	I2CONSET = 1<<2;
	I2CONCLR = 1<<3;
	while(((I2CONSET>>3)&1)==0);
	ch=I2DAT;
	return ch;
}

void NACK(void){
	I2CONCLR = 1<<2;
	I2CONCLR = 1<<3;
	while(((I2CONSET>>3)&1)==0);
}
