#include <stdio.h>
#include <stdlib.h>

struct WithoutPack {
	char a;
	int b;
	double c;
};

#pragma pack(1)
struct PackedStruct1 {
	char a;
	int b;
	double c;
};

#pragma pack(2)
struct PackedStruct2 {
        char a;
        int b;
        double c;
};

#pragma pack(4)
struct PackedStruct4 {
        char a;
        int b;
        double c;
};

int main(){

	struct WithoutPack p;

		printf("Size of struct WithoutPack: %lu bytes.\n", sizeof(struct WithoutPack));
		printf("Address of a: %p\n", (void*)&p.a);
		printf("Address of b: %p\n", (void*)&p.b);
		printf("Address of c: %p\n", (void*)&p.c);

		printf("\n");


	struct PackedStruct1 p1;

        printf("Size of struct PackedStruct1: %lu bytes.\n", sizeof(struct PackedStruct1));
        printf("Address of a: %p\n", (void*)&p1.a);
        printf("Address of b: %p\n", (void*)&p1.b);
        printf("Address of c: %p\n", (void*)&p1.c);

        printf("\n");

	struct PackedStruct2 p2;

        printf("Size of struct PackedStruct2: %lu bytes.\n", sizeof(struct PackedStruct2));
        printf("Address of a: %p\n", (void*)&p2.a);
        printf("Address of b: %p\n", (void*)&p2.b);
        printf("Address of c: %p\n", (void*)&p2.c);

        printf("\n");

	struct PackedStruct4 p4;

        printf("Size of struct PackedStruct4: %lu bytes.\n", sizeof(struct PackedStruct4));
        printf("Address of a: %p\n", (void*)&p4.a);
        printf("Address of b: %p\n", (void*)&p4.b);
        printf("Address of c: %p\n", (void*)&p4.c);

        printf("\n");


	return 0;
}
