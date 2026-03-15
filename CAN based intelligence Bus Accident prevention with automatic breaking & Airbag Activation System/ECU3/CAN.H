#include<LPC21XX.H>

typedef struct CAN2{
	unsigned int id;
	unsigned int rtr;
	unsigned int dlc;
	unsigned int byteA;
	unsigned int byteB;
}CAN2_MSG;


void CAN2_INIT(void){
	PINSEL1 |= 0X14000;	//P0.23: TD2, P0.24: RD2
	VPBDIV = 1;	//PCLK: 60MHz
	C2MOD = 0X1;	//RESET MODE
	AFMR = 0X2;	//ALL RECEIVE MSG ARE ACCEPTED
	C2BTR = 0X1C001D;	//B125Kbps
	C2MOD = 0X00;
}

void CAN2_TX (CAN2_MSG m1){
	C2TID1 = m1.id;
	C2TFI1 = ((m1.dlc)<<16);
	if(m1.rtr == 0){
		C2TFI1 &= ~(1<<30);	//RTR = 0
		C2TDA1 = m1.byteA;	//LOWER 4 BYTES OF DATA
		C2TDB1 = m1.byteB;	//UPPER 4 BYTES OF DATA
	}
	else{
		C2TFI1 |= (1<<30);	//RTR = 1
	}
	C2CMR = (1<<0)|(1<<5);	//START TX AND SELECT TX BUFFER 1
	while((C2GSR & (1<<3))==0);	//WAITING FOR DATA TX
}

void CAN2_RX(CAN2_MSG* m1){
//	while((C2GSR & (1<<3))==0);
	while((C2GSR&0x1)==0);
	m1->id = C2RID;
	m1->dlc = (C2RFS>>16) & 0XF;
	m1->rtr = (C2RFS>>30) & 0X1;
	if(m1->rtr == 0){
		m1->byteA = C2RDA;
		m1->byteB = C2RDB;
	}
	C2CMR = (1<<2);	//FREE RECEIVE BUFFER
}




