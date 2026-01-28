#include "delay.h"
#define	seg_d 0xff
#define seg_4 1<<8
#define seg_3 1<<9
#define seg_2 1<<10
#define seg_1 1<<11
typedef unsigned char U8;
U8 seg_lut[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
void DisplayDigits(int n);
static unsigned int segcase_(int pos);
static unsigned int segcase_(int pos)
{
    switch(pos)
    {
        case 1: return seg_1; 
        case 2: return seg_2;
        case 3: return seg_3;
        case 4: return seg_4;
    }
    return 0;
}
void DisplayDigits(int n){
	int i;
	unsigned char k;
	for(k=0;k<10;k++){
		for(i=4;i>0;i--){
			IOCLR0 = seg_d;
			IOSET0 = seg_lut[n%10];
			IOCLR0 = segcase_(i);
			delaymilisec(5);
			IOSET0 = segcase_(i);
			n /= 10;
		}
		delaysec(1);
	  }
}
