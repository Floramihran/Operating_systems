#include <stdio.h>
int main(){
	int var = 5;
	int *ip = &var;

	printf("Address of var variable: %p\n", &var);
	printf("Address stored in ip variable: %p\n", ip);

	*ip = 10;
	printf("New value of variable: %d\n", var);

	return 0;
}
