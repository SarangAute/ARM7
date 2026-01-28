#include<LPC21XX.H>
#include "delay.h"
#define SSD 0xff
typedef unsigned char U8;   // macro used for data type
U8 SSD_LUT[] = {0X0C, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X98};

int main(){
	U8 digit = 0;
	IODIR0 = SSD;
	while(1){
		IOCLR0 = SSD;
		IOSET0 = SSD_LUT[digit++];
		delaymilisec(1000);
	}
}