#include <stdio.h>
#include <pthread.h>

#define ARRAY_SIZE 8

typedef struct{
	int* array;
	int start;
	int end;
	int thread_id;
}thread_data_t;


void* partial_sum(void* arg){
	thread_data_t* data = (thread_data_t*)arg;
	int sum = 0;

	for (int i = data->start; i < data->end; i++){
		sum += data->array[i];
	}

	printf("Thread %d: Partial sum from index %d to %d is %d\n", data->thread_id, data->start, data->end - 1, sum);

	return NULL;

}

int main(){

	int array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};
	pthread_t thread[2];
	thread_data_t thread_data[2];

	int half = ARRAY_SIZE /2;

	thread_data[0].array = array;
	thread_data[0].start = 0;
	thread_data[0].end = half;
	thread_data[0].thread_id = 1;

	thread_data[1].array = array;
        thread_data[1].start = half;
        thread_data[1].end = ARRAY_SIZE;
        thread_data[1].thread_id = 2;	

	for (int i = 0; i < 2; i++){
		if (pthread_create(&thread[i], NULL, partial_sum, &thread_data[i]) != 0){
			perror("Failed to create thread");
			return 1;
		}
	}


	for(int i = 0; i < 2; i++){
		pthread_join(thread[i], NULL);
	}

	int total_sum = 0;
	for(int i = 0; i < ARRAY_SIZE; i++){
		total_sum += array[i];
	}

	printf("Total sum is %d\n", total_sum);

	return 0;


}
