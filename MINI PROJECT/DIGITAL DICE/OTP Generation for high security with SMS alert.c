#include<LPC21XX.H>
#include<stdio.h>
#include"LCD_DISPLAY.H"
#include"UART0.H"
#include"functions.h"

/******GLOBAL DECLARATIONS*******/
unsigned char name[] = "OTP Generation for high security with SMS alert ";
unsigned char S1[] = "ENTER THE PASS";
unsigned int cn, cnt=0;

void isr0(void) __irq
{
	while(((IOPIN0>>16)&1)==0);
	EXTINT = 0X01;
	IOSET0 = 1<<14;
	IOCLR0 = 1<<14;
	
	delaymilisec(300);
	cn++;
	cnt=cn/2;
	VICVectAddr = 0;
	while(((IOPIN0>>16)&1)==0);
}


int pass, OTP, OTPpin;


int main(){
	int const password = 1111;
	char otpstr[10], cntstr[10];
//		unsigned int count = 0;
	
	/*TIMER 0 FOR OTP GENRATION*/
	T0PR = 9999;
	T0TCR =0X01;
	
	/***LCD_DISPLAY***/
	LCD_INIT();
	LCD_CMD(0X80);
	LCD_ROLLING_STRING(name);
	delaymilisec(1000);
	
	/***UART0***/
	PINSEL0 |= 0X5;			//INITIALIZING PIN P0.0 &P0.1 FOR UART0 (POLING METHOD)
	UART0_CONFIG();

	/***EXTINT0***/

	IODIR0|=1<<14;
	//IOSET0|=1<<16;
	PINSEL1|=0x01;
	VICIntSelect = 0<<14;
	
	VICVectCntl0 = 0x20|14;
	VICVectAddr0 = (unsigned long)isr0;

	EXTMODE = 0X01;
	EXTPOLAR = 0X01;

	VICIntEnable = 1<<14;


	
	while(1){
		LCD_CMD(0X01);
		LCD_CMD(0X80);
		LCD_STRING(S1);				//S1[] = "ENTER THE PASS ";
		
		pass = keypadDigits();
		
		if(password == pass){
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			LCD_STRING("ACCESS GRANTED");	//FOR LCD DISPLAY
			delaysec(1);
			
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			LCD_STRING("OTP GENRATING...");
			delaymilisec(500);
			
			/**OTP GENRATOIN**/
			OTP=OTP_Genration();
			OTP = fourdigit(OTP);
			sprintf(otpstr, "%d", OTP);		//CONVERTING INT TO STRING
			
			GSMstatements();
			Send2Gsm("ACCESS GRANTED ");
			Send2Gsm("OTP: ");
			Send2Gsm(otpstr);
			UART0_TX(0X1A);		  //CTRL+Z
			delaymilisec(500);
			
			
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			LCD_STRING("ENTER OTP:") ;	//FOR LCD DISPLAY
			
// 			LCD_CMD(0XC0);
// 			LCD_STRING(otpstr);
			
			OTPpin = keypadDigits();   //ENTERED 4 DIGITS THROUGH KEYPAD

			if(OTP == OTPpin){
//			if(1111 == OTPpin){
				LCD_CMD(0X01);
				LCD_CMD(0X80);
				LCD_STRING("OTP CORRECT");
				delaysec(1);

				LCD_INIT();
				LCD_CMD(0X01);
				LCD_CMD(0X80);
				LCD_STRING("IR VALUE:");
				LCD_CMD(0X89);
				LCD_INTEGER(cnt);

				sprintf(cntstr, "%d", cnt);		//CONVERTING INT TO STRING
			
				GSMstatements();
				Send2Gsm("ACCESS GRANTED ");
				Send2Gsm("OTP CORRECT ");
				Send2Gsm("IR VALUE: ");
				Send2Gsm(cntstr);
				UART0_TX(0X1A);		  //CTRL+Z
				delaymilisec(500);
			}
			else{
				denied();
				if(chance >= 3){
					ChanceEnd();
					return 0;					//EXIT FROM PROGRAM
				}
			}
		}							
		else{
				denied();
				if(chance >= 3){
					ChanceEnd();
					return 0;					//EXIT FROM PROGRAM
				}
		}
	}
}

