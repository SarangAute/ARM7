#include<LPC21XX.H>
#include"CAN.H"
#include"ULTRASONIC.H"
#include"lcd_display.h"

int main(){
	CAN2_MSG m1;
	unsigned int TIME, DISTANCE;
	ULTRASONIC_INIT();
	CAN2_INIT();
	LCD_INIT();
	
	m1.id = 0x100;		//256
	m1.rtr = 0;	//data frame
	m1.dlc = 4;
	
	LCD_CMD(0X80);
	
	while(1){
		TRIG_MODE();
		ECHO_MODE();
		TIME = T1TC;
		DISTANCE = (TIME/58);
		m1.byteA = DISTANCE;
		m1.byteB = 0;
		CAN2_TX(m1);
		LCD_INTEGER(DISTANCE);
		delaymilisec(750);
	}
}
