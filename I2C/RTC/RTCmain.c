#include<lpc21xx.h>
#include"LCD_DISPLAY.H"

void I2C_INIT(void);
void START(void);
void WRITE(char);
void STOP(void);
void READ (char addr, char pos);
char ACK(void);
void NACK(void);
char DECtoBIN(char);

/* 	  7		6	  5	   4     3	 2	  1	  0
	| - | IEN | STA | STO | SI | AA | - | - |  		*/

int i;
unsigned char ReadB[20];

int main(){
	I2C_INIT();
	LCD_INIT();
	LCD_CMD(0X80);
	START();
	WRITE(0X68<<1);	//slave address
	WRITE(0X00);	//data address
	WRITE(0X10);	//second
	WRITE(0X15);	//min
	WRITE(0X63);	//hour
	WRITE(0X06);	//day
	WRITE(0X30);	//date
	WRITE(0X01);	//month
	WRITE(0X26);	//year
	STOP();
	delaymilisec(10);
	LCD_STRING("I2C RTC ");

	while(1){
		READ(0X68<<1,0x00);	
		for(i=0;i<7;i++){
			if(i==2)
				ReadB[i] = (ReadB[i]&0x1f);
			else
				ReadB[i] = DECtoBIN(ReadB[i]);
		}
		LCD_STRING("D:");	
		LCD_INTEGER(ReadB[4] );	 //DD
		LCD_INTEGER(ReadB[5] );	//MM	
		LCD_INTEGER(ReadB[6] );	//YY

		LCD_CMD(0XC0);
		LCD_STRING("T: ");		//time
		LCD_INTEGER(ReadB[2]);	//HOUR
		LCD_INTEGER(ReadB[1]);	//MIN
		LCD_INTEGER(ReadB[0]);	//SEC		
	
		LCD_STRING("DY: ");		//week-day
		LCD_INTEGER(ReadB[3]);	
	}			   	
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

void READ(char addr, char pos){
	char ch;
	START();
	WRITE(addr);
	WRITE(pos);
	START();
	WRITE(addr|1);
	for(i=0;i<7;i++){
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

char DECtoBIN(char x){
	return(((x>>4)*10)+(x&0xf));	
}
