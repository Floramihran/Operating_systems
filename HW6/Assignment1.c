#include <stdio.h>

int main(){
	
	int a;
	char b;
	double c;
	short d;

	printf("Size of int: %lu bytes. \n", sizeof(int));
	printf("Size of char: %lu bytes. \n", sizeof(char));
	printf("Size of double: %lu bytes. \n", sizeof(double));
	printf("Size of short: %lu bytes. \n", sizeof(short));

	printf("\n");

	printf("Address of a: %p\n", (void*)&a);
	printf("Address of b: %p\n", (void*)&b);
	printf("Address of c: %p\n", (void*)&c);
	printf("Address of d: %p\n", (void*)&d);


	return 0;

}
