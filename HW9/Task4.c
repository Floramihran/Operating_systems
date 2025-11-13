#include <stdio.h>
#include <pthread.h>

void* calculate_square(void* arg){
	int number = *(int*)arg;
	int square = number * number;
	printf("Square of %d is %d\n", number, square);
	return NULL;

}


int main(){
	int numbers[] = {1, 2, 3, 4,5};
	int num_count = sizeof(numbers) / sizeof(numbers[0]);
	pthread_t threads[num_count];

	for (int i = 0; i < num_count; i++){
		if (pthread_create(&threads[i], NULL, calculate_square, &numbers[i]) != 0){
			perror("Failed  to create thread");
			return 1;
		}
	}

	for (int i = 0;  i < num_count; i++){
		pthread_join(threads[i], NULL);
	}

	printf("All square calculations completed!\n");
	return 0;

}

