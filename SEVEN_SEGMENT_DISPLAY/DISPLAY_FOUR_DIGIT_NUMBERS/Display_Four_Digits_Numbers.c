#include<LPC21XX.H>
#include"delay.h"
#define SEG_D 0XFF
#define SEG_1 1<<8
#define SEG_2 1<<9
#define SEG_3 1<<10
#define SEG_4 1<<11
typedef unsigned char U8;
U8 SEG_LUT[] = {0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF9,0X80,0X98};
void DisplayDigits(int);

int main(){
	IODIR0 = SEG_D|SEG_1|SEG_2|SEG_3|SEG_4;
	while(1){
		DisplayDigits(1234);
	}
}

void DisplayDigits(int n){
	unsigned char k;
	for(k=0;k<100;k++){
		IOCLR0 = SEG_D;
		IOSET0 = SEG_LUT[n%10];
		IOSET0 = SEG_4;
		delaymilisec(5);
		IOCLR0 = SEG_4;
		n /= 10;
		
		IOCLR0 = SEG_D;
		IOSET0 = SEG_LUT[n%10];
		IOSET0 = SEG_3;
		delaymilisec(5);
		IOCLR0 = SEG_3;
		n /= 10;

		IOCLR0 = SEG_D;
		IOSET0 = SEG_LUT[n%10];
		IOSET0 = SEG_2;
		delaymilisec(5);
		IOCLR0 = SEG_2;
		n /= 10;

		IOCLR0 = SEG_D;
		IOSET0 = SEG_LUT[n%10];
		IOSET0 = SEG_1;
		delaymilisec(5);
		IOCLR0 = SEG_1;
		n /= 10;
	}
}					  