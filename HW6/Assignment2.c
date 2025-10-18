#include <stdio.h>
#include <stdlib.h>


struct Point1{
	char a;
	int b;
	double c;
};

struct Point2{
        double c;
        int b;
        char a;
};

struct Point3{
	int b;
	char a;
	double c;
};



int main(){
	
	struct Point1 p1;
	
	printf("Size of struct Point1: %lu bytes.\n", sizeof(struct Point1));
	printf("Address of a: %p\n", (void*)&p1.a);
	printf("Address of b: %p\n", (void*)&p1.b);
	printf("Address of c: %p\n", (void*)&p1.c);

	printf("\n");

	struct Point2 p2;

	printf("Size of struct Point2: %lu bytes.\n", sizeof(struct Point2));
    printf("Address of c: %p\n", (void*)&p2.c);
    printf("Address of b: %p\n", (void*)&p2.b);
    printf("Address of a: %p\n", (void*)&p2.a);

    printf("\n");


	struct Point3 p3;

	printf("Size of struct Point3: %lu bytes.\n", sizeof(struct Point3));
    printf("Address of b: %p\n", (void*)&p3.b);
    printf("Address of a: %p\n", (void*)&p3.a);
    printf("Address of c: %p\n", (void*)&p3.c);

    printf("\n");


	return 0;

}
