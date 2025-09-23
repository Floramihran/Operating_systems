#include <stdio.h>
#include <stdlib.h>

void out1(){
	printf("First atexit() succeeded.\n");
}

void out2(){                                                                                                                    printf("Second atexit() succeeded.\n");
}


int main(){
	int x;
	float f;

	f = (float)x;

	//atexit(out1);
	//atexit(out2);
	
	// I have to change the order so it prints in right order
	atexit(out2);
        atexit(out1);

	printf("Hello!\n");

	return 0;

} 
