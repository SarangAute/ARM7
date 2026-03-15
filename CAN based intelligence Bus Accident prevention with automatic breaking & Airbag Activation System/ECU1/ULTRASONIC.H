#include"delay.h"
#define TRIG 1<<2
#define ECHO (IOPIN0&(1<<3))

void ULTRASONIC_INIT (void){
	IODIR0|=TRIG;
	T1TCR=0X00;
	T1PR=59;	//ASSUMING AS 60MHz
}

void TRIG_MODE (void){
	T1TC=T1PC=0;	//INITIAL CONDITION STARTING FROM 0
	IOSET0 = TRIG;
	delaymicrosec(10);
	IOCLR0 = TRIG;
}

void ECHO_MODE(void){
	while(!ECHO);
	T1TCR=0X01;
	while(ECHO);
	T1TCR=0X00;
}



