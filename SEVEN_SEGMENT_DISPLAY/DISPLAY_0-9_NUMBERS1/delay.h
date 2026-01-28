void delaysec(int n){
	T0PR = 15000000-1;
	T0TCR = 0X01;
	while(T0TC < n){
		T0TCR = 0X00;
	}
}
void delaymilisec(int n){
	//T0PR = 15000-1;
	//T0TCR = 0X01;
	//while(T0TC < n){
		//T0TCR = 0X00;
	//}
	int i;
	for(;n>0;n--)
		for(i=12000;i>0;i--);
}	 