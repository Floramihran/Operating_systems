#include <stdio.h>
#include <stdlib.h>

int main(){
	int *grades;
	int n;
	int highest, lowest;

	printf("Enter the number of students: ");
	scanf("%d", &n);

	grades = (int *)malloc(n * sizeof(int));

	if (grades == NULL){
		printf("memory allocation failed!\n");
		return 1;
	}

	printf("Eneter the grades: ");
	for (int i = 0; i < n; i++){
		scanf("%d", &grades[i]);
	}

	highest = grades[0];
	lowest = grades[0];

	for (int i = 1; i < n; i++){
		if (grades[i] > highest){
			highest = grades[i];
		}
		if (grades[i] < lowest){
			lowest = grades[i];
		}
	}

	printf("Highest grade: %d\n", highest);
	printf("Lowest grade: %d\n", lowest);

	free(grades);

	return 1;
}
