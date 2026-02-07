#include<lpc21xx.h>
void FIQ_Sarang(void)__irq{
	EXTINT = 0X01;
	IOSET0 = 1<<0;
	IOCLR0 = 1<<0;
	VICVectAddr=0;
}

int main(){
	unsigned int count =0;
	PINSEL1 |= 0X1;
	IODIR0 = 1<<0;
	VICIntSelect = (1<<14);
	

	
	EXTMODE = 0X00;
	EXTPOLAR = 0X00;
	

	
	VICIntEnable = (1<<14);
	
	while(1){
		count++;
	}
}

/*in startup file on line number 256 248 change name of FIQ function
*/