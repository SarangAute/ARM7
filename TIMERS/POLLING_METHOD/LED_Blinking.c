#include<LPC21XX.H>
#define LED_1 1<<0
#define LED_2 1<<1
#define LED_3 1<<2
#define LED_4 1<<3

void DelaySec(int n){
T0PR = 15000000-1;			//VALUE/SETING TIMER FOR 1 SEC
	T0TCR = 0X01;			//START/ENABLE COUNTER
	while(T0TC<n);			//WAITING FOR n SEC
	T0TCR = 0X02;		   	//RESET TIMER CONTROL REGISTER
	T0TCR = 0X00;		   	//DISABLE COUNTER REGISTER}
}
int main(){
	IODIR0 = LED_1|LED_2|LED_3|LED_4;
	IOSET0 = LED_1|LED_2|LED_3|LED_4;
	while(1){
		IOCLR0 = LED_1;
		DelaySec(1);	
		IOSET0 = LED_1;
		IOCLR0 = LED_2;
		DelaySec(1);	
		IOSET0 = LED_2;
		IOCLR0 = LED_3;
		DelaySec(1);	
		IOSET0 = LED_3;
		IOCLR0 = LED_4;
		DelaySec(1);	
		IOSET0 = LED_4;
	}
}
