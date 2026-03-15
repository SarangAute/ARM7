#define MSTR 1<<5	//1=MASTER & 0=SLAVE MODE

void SPI_INIT(char mode);
float READ(char ch_no);
unsigned char SPI_DAT(char DATA);
int SPEED (float);

void SPI_INIT(char mode){
	PINSEL0 |= 0X1500;				//P0.4 P0.5 P0.6 P0.7
	S0SPCCR = 150;					//CLK 
	IODIR0 |=1<<7;
	S0SPCR=(MSTR|mode<<3);
}
float READ(char ch_no){
	char Hbit,Lbit;
	int value;
	IOCLR0=1<<7;					//selecting slave for start tx and rx
	SPI_DAT(0X06);
	Hbit=SPI_DAT(ch_no<<6);
	Lbit=SPI_DAT(0x00);
	IOSET0=1<<7;					//stop slave tx and rx 
	value = (((Hbit & (0x0f))<<8)| Lbit);
	return ((value * 3.3)/4096);
}

unsigned char SPI_DAT(char DATA){
	S0SPDR=DATA;					//SOSPDR -DATA REGISTER
	while(((S0SPSR>>7)&1)==0);		//SOSPSR -STATUS REGISTER
	return S0SPDR;
}

int SPEED (float Vtg){
	return ((Vtg*100)/3.2);
}
