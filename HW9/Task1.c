#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct {
	int thread_id;
	char* message;

}thread_data_t;

void* print_thread_info(void* arg){
	thread_data_t* data = (thread_data_t*)arg;
	printf("Thread ID: %d, %s\n",data->thread_id, data->message);
	return NULL;

}

int main(){
	pthread_t threads[3];
	thread_data_t thread_data[3];



	thread_data[0].thread_id = 1;
	thread_data[0].message = "Hello from thread 1!";

	thread_data[1].thread_id = 2;
        thread_data[1].message = "Hello from thread 2!";

	thread_data[2].thread_id = 3;
        thread_data[2].message = "Hello from thread 3!";

	for (int i = 0; i < 3; i++){
		if (pthread_create(&threads[i], NULL, print_thread_info, (void*)&thread_data[i]) != 0){
			perror("Failed to create thread");
			return 1;
		}
}
	for (int i = 0; i < 3; i++){
		if(pthread_join(threads[i], NULL) !=0){
			perror("Failed to join thread");
			return 1;
		}
	}

	printf("All threads completed successfully!\n");
	return 0;

}
