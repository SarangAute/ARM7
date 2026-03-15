#include<lpc21xx.h>
void delaymilisec(int n);
void delaysec(int n);
void delaymicrosec(int n);
void can_delaysec(int n);

void delaymilisec(int n){
	T0PR = 60000-1;
	T0TCR = 0X01;
	while(T0TC < n);
	T0TCR = 0X03;
		T0TCR = 0X00;
	
}

void delaymicrosec(int n){
	T1PR = 60-1;
	T1TCR = 0X01;
	while(T1TC < n);
	T1TCR = 0X03;
		T1TCR = 0X00;
	
}

void can_delaysec(int n){
	T1PR = 60000000-1;
	T1TCR = 0X01;
	while(T1TC < n);
	T1TCR = 0X03;
		T1TCR = 0X00;
	
}


void delaysec(int n){
	T1PR = 60000000-1;
	T1TCR = 0X01;
	while(T1TC < n);
	T1TCR = 0X03;
		T1TCR = 0X00;
	
}

