void delaymilisec(int ms){
	int i;
	for(;ms>0;ms--)
		for(i=0;i<12000;i++);
}
