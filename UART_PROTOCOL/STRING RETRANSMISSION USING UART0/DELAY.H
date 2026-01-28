#include<LPC21XX.H>

void DelayMiliSec(int n){
	T0PR = 15000-1;
	T0TCR=0X01;
	while(T0TC<n);
	T0TCR=0X03;
	T0TCR=0X00;
}

void DelaySec(int n){
	T0PR = 15000000-1;
	T0TCR=0X01;
	while(T0TC<n);
	T0TCR=0X03;
	T0TCR=0X00;
}
