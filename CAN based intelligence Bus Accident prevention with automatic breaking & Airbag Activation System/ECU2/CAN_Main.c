#include<LPC21XX.H>
#include"CAN.H"
#include"SPEED.H"
#include"LCD_DISPLAY.H"

int main(){
	CAN2_MSG m1;
	int Speed;
	SPI_INIT(3);		//3 IS MODE '11'
	CAN2_INIT();
	LCD_INIT();
	
	m1.id = 0x00000200;
	m1.rtr = 0;	//data frame
	m1.dlc = 6;

	while(1){
		Speed=SPEED(READ(0));
		
		m1.byteA = 0;
		m1.byteB = Speed;

		CAN2_TX(m1);


		LCD_CMD(0X80);
		LCD_STRING("SPEED: ");
		LCD_INTEGER(Speed);
			
		delaymilisec(750);

		LCD_CMD(0X01);
	}
}
