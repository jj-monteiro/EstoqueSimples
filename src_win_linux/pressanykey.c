#include "pressanykey.h"

void myPause(FILE *in){
	int ch;
	do
		ch = fgetc(in); 
	while (ch != EOF && ch != '\n'); 
	clearerr(in);
    //desliga o cursor do terminal
	system("setterm -cursor off");
	printf("Pressione [ENTER] para continuar...");
	getchar();
    //liga o cursor do terminal
	system("setterm -cursor on");
}