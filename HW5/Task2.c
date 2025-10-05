#include <stdio.h>
#include <stdlib.h>


int main(){
	int *arr;
	int n;
	float sum = 0, average;

	printf("Enter the number of elements: ");
	scanf("%d", &n);

	arr = (int *)calloc(n, sizeof(int));

	if (arr == NULL){
		printf("Memory allocation failed!\n");
		return 1;
	}

	printf("Array after calloc: ");
	for(int i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}

	printf("\n");

	printf("Enter %d integers: ", n);
	for (int i = 0; i < n; i++ ){
		scanf("%d", &arr[i]);
	}

	printf("Updated array: ");
	for (int i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}

	printf("\n");

	for (int i = 0; i < n; i++){
		sum +=arr[i];
	}

	average = sum / n;

	printf("Average of the array: %.1f\n", average);

	free(arr);

	return 0;
}
