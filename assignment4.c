#include <stdio.h>
    	int main(){
    int a = 3;
    int *ptr = &a;
    int **dptr = &ptr;
    
    printf("Value of a using pointer: %d\n", *ptr); 
    printf("Value of a using double pointer: %d\n", **dptr);
    
    return 0;
    }

