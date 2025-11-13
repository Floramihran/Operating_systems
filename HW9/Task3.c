#include <stdio.h>
#include <pthread.h>

void* print_numbers(void* arg){
	int thread_id = *(int*)arg;

	for (int i = 1; i <= 5; i++){
		printf("Thread %d: Number %d\n", thread_id, i);
	}
	return NULL;
}



int main(){

	pthread_t threads[3];
	int thread_id[3] ={1, 2, 3};


	for (int i = 0; i < 3; i++){
		if (pthread_create(&threads[i], NULL, print_numbers, &thread_id[i]) != 0){
			perror("Failed to create thread");
			return 1;
		}
	}

	for(int i = 0; i < 3; i++){
		pthread_join(threads[i], NULL);
	}

	printf("All threads completed!\n");
	return 0;



}
