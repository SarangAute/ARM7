#include<LPC21XX.H>
#include"LCD_DISPLAY.H"
#define SW1 16
#define SW2 17
unsigned char cgram_lut[]={
  		0X00,0X00,0X00,0X06,0X06,0X00,0X00,0X00,	//1
		0X00,0X03,0X03,0X00,0X00,0X18,0X18,0X00,  	//2
		0X00,0X1B,0X1B,0X00,0X04,0X04,0X00,0X00,	//3
		0X00,0X1B,0X1B,0X00,0X00,0X1B,0X1B,0X00,
		0X00,0X1B,0X1B,0X04,0X04,0X1B,0X1B,0X00,
		0X1B,0X1B,0X00,0X1B,0X1B,0X00,0X1B,0X1B
};

void CGRAM_WRITE(unsigned char n){
	unsigned char i;
	LCD_CMD(0X40);
	for(i=0;i<n;i++)
		LCD_DATA(cgram_lut[i]);
}

int random(void){
	return T1PC;
}
int main(){
	int var, hist[10], i=0;
	T1PR = 5;
	T1TCR =0X01;
	LCD_INIT();
	LCD_CMD(0X80);
	LCD_STRING("DIGITAL DICE:");
	
	while(1){
		if(((IOPIN0>>SW1)&1)==0)
		{
			var = random()+1;
			for(i=0;i<10-1;i++)
				hist[10-1-i] = hist[10-2-i];
			hist[0] = var-1;
			LCD_CMD(0XC0);
			LCD_INTEGER(var);
			CGRAM_WRITE(48);
			LCD_CMD(0XC1);
			LCD_DATA(var-1);
  			while(((IOPIN0>>SW1)&1)==0);
	 	}
		if(((IOPIN0>>SW2)&1)==0){
			LCD_CMD(0XC5);
			for(i=0;i<10;i++){
				LCD_DATA(hist[i]);
			}
			while(((IOPIN0>>SW2)&1)==0);
		}
		else{
			random();
		}
	}
}



