#include<LPC21XX.H>
#include<stdlib.h>
#include"UART0.H"
#include"CAN.H"
#include"DELAY.H"
#define AIRBAG 1<<5

int main(){
	unsigned int speed;
	CAN2_MSG m1;
	CAN2_INIT();
	PINSEL0|=0X4000;
	IODIR0|=AIRBAG;
	PINSEL1|=0X400;
	UART0_INIT(115200);
	IOSET0|=AIRBAG;
	UART0_STRING("4th NODE \r\n");

	PWMMR0=60000000-1;		//TOTAL PWM
	PWMMCR=0X03;		//FOR RESET AFTER MAX SPEED
	PWMPCR=0X2000|0x200;		//ENABLE 5TH & 2nd PWM
	PWMTCR=0X09;		//ENABLE PWM AND COUNTER
	PWMLER=0X24;		//LATCH ENABLE REGISTER(used while change in PWM)
	while(1){
		delaymilisec(500);
		CAN2_RX(&m1);
		if(m1.id==0x300){			
			if(m1.rtr == 0){
				if(m1.byteA!=55){
					
					UART0_INTEGER(m1.byteA);
					UART0_STRING("\r\n");
					switch(m1.byteA){
						case 11: PWMMR5=0;
								UART0_STRING("DIST_CONDITION: "); 
								 UART0_STRING("<10CM");
								UART0_STRING("\r\n");
								IOCLR0|=AIRBAG;
								exit(0);
							 		break;			//0% duty cycle
						case 22: PWMMR5=15000000; 
								UART0_STRING("DIST_CONDITION: "); 
								UART0_STRING("<30 CM");
								UART0_STRING("\r\n");
								break;		//25% duty cycle
						case 33: PWMMR5=30000000;
								UART0_STRING("DIST_CONDITION: ");  
								 UART0_STRING("<50 CM");
								UART0_STRING("\r\n");
								break;   		//50% duty cycle
						case 44: PWMMR5=45000000;
								UART0_STRING("DIST_CONDITION: "); 
								 UART0_STRING("70CM");
								UART0_STRING("\r\n");
						 break;		//75% duty cycle 
						  
					}
				}
				else{	UART0_STRING("speed p: ");
						UART0_INTEGER(m1.byteB);
						UART0_STRING("\r\n");
						while(PWMIR!=0X01);	//waiting for interrupt
						PWMIR = 0X01;		//clearing interrupt
						speed = m1.byteB;
						speed*=600000;			//total PWM 60000000-1
						PWMMR5=speed;
				}
				PWMLER=0X024;
			}
		}
		 
	}
}

