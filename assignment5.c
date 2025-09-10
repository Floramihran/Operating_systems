#include <stdio.h>
    	int main(){
    char str[] = "Hello";
    char *s = str;
    
    while(*s !='\0'){
        printf("%c", *s);
        s++;
    }
    
    printf("\n");
    
    int count = 0;
    for(char *p = str ; *p !='\0' ; p++)
    count++;
    printf("Number of characters in the String: %d\n", count);
    
    return 0;
         }

