#include<LPC21XX.H>
#include"CAN.H"
#include"UART0.H"
#include"DELAY.H"

int main(){
	CAN2_MSG m1,m2;	//m1=rx , m2=tx
	CAN2_INIT();
	UART0_INIT(115200);

	m2.id = 0x00000300;
	m2.rtr = 0;	//data frame
	m2.dlc = 8;

	while(1){
		delaymilisec(500);
		CAN2_RX(&m1);

		if(m1.rtr == 0){
			if(m1.id==0x100){
				if((m1.byteA>0)&&(m1.byteA<=10)){		//byteA=Distance
					m2.byteA=11;		//duty_cycle=0
				}
				else if((m1.byteA>10)&&(m1.byteA<=30)){
					m2.byteA=22;		//duty_cycle=25
				}
				else if((m1.byteA>30)&&(m1.byteA<=50)){
					m2.byteA=33;		//duty_cycle=50
				}
				else if((m1.byteA>50)&&(m1.byteA<=70)){
					m2.byteA=44;		//duty_cycle=75
				}
				else
				{
					 	m2.byteA=55;		//dummy
				}
			}
			
			if(m1.id==0x200){
				m2.byteB = m1.byteB;	//byteB=speed;
			}

			CAN2_TX(m2);

			UART0_STRING("DIST: ");
			if(m1.id==0X100)
				UART0_INTEGER(m1.byteA);

			UART0_STRING(" ");
			UART0_STRING("SPEED: ");
			if(m1.id==0X200)
				UART0_INTEGER(m1.byteB);
			delaymilisec(350);
			UART0_STRING("\r\n");
		}
	}
}

