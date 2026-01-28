void DisplayDigit(int n){
	int i;
	unsigned char k;
	for(i=4;i>0;i--){
		for(k=0;k<100;k++){
			IOCLR0 = seg_d;
			IOSET0 = seg_lut[n%10];
			IOSET0 = SEG_i;
			delaysec(1);
			IOCLR0 = seg_i;
			n /= 10;
		}
	}
}