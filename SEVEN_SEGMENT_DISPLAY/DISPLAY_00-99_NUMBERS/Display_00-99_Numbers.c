#include<LPC21XX.H>
#include"sevensegmentdisplay.h"
#define	seg_d 0xff
//#define seg_1 1<<8
//#define seg_2 1<<9
typedef unsigned char U8;
//U8 seg_lut[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};

int main(){
 	int digit = 0;
 	IODIR0 = seg_d|seg_1|seg_2|seg_3|seg_4;
 	while(digit < 1000)
	{
 		DisplayDigits(digit++);
		if(digit == 10000)
			digit=0;
	//	delaymilisec(100);		
	}	 
}
