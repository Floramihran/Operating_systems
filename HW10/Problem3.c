#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 8


int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;


int P, C, K;
int total_produced = 0;
int total_consumed = 0;

void* producer(void *arg){
	int id = *(int*)arg;


	for(int i = 0; i < K; i++){

		int item = id * 1000 + i;

		sem_wait(&empty_slots);
		pthread_mutex_lock(&buffer_mutex);

		buffer[in_pos] = item;
		in_pos = (in_pos + 1) % BUFFER_SIZE;
		total_produced++;

		printf("Producer %d produced item: %d\n", id, item);

		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&full_slots);
	
		usleep(1000);
	
	}

	printf("Producer %d finished\n", id);
	return NULL;
}

void* consumer(void *arg){
        int id = *(int*)arg;


	while(1){
        pthread_mutex_lock (&buffer_mutex);

		if (total_consumed >= P * K && total_produced >= P * K){
			
			pthread_mutex_unlock(&buffer_mutex);
			break;
		
		}

		pthread_mutex_unlock(&buffer_mutex);

        sem_wait(&full_slots);
        pthread_mutex_lock(&buffer_mutex);

        int item = buffer[out_pos];
        out_pos = (out_pos + 1) % BUFFER_SIZE;
        total_consumed++;

        printf("Consumer %d consumed item: %d\n", id, item);

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_slots);

        usleep(1800);

        }

        printf("Consumer %d finished\n", id);
        return NULL;
}


int main(int argc, char* argv[]){


	if (argc != 4){
		printf("Usage: %s producers consumers items_per_producer \n", argv[0]);
		return 1;
	}

	P = atoi(argv[1]);
	C = atoi(argv[2]);
	K = atoi(argv[3]);

	if (P <= 0 || C <= 0 || K <= 0){
		printf("All arguments mut be positive integers\n");
		return 1;
	}

	printf("Buffer size: %d, ", BUFFER_SIZE);
	printf("Producer: %d, Consumers: %d, Items per producer: %d\n", P, C, K);
	printf("Total items to produce: %d\n", P * K );

	sem_init(&empty_slots, 0, BUFFER_SIZE);
	sem_init(&full_slots, 0, 0);
	pthread_mutex_init(&buffer_mutex, NULL);

	for (int i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = 1;

	pthread_t producers[P];
	pthread_t consumers[C];
	int producer_id [P];
	int consumer_id [C];

	for (int i = 0; i < P; i++){
		producer_id[i] = i;
		pthread_create(&producers[i], NULL, producer, &producer_id[i]);
	
	}

	 for (int i = 0; i < C; i++){
                consumer_id[i] = i;
                pthread_create(&consumers[i], NULL, consumer, &consumer_id[i]);
    }

	 for (int i = 0; i < P; i++){ 
	 	pthread_join(producers[i], NULL);
	 }
	 
	 sleep(2);

	 for (int i = 0; i < C; i++)
		 sem_post(&full_slots);

	 for (int i = 0; i < C; i++)
		 pthread_join(consumers[i], NULL);

	 printf("\n");
	 printf("Total consumed: %d\n", total_consumed);
	 printf("Remaining buffer items: %d\n", (in_pos >= out_pos) ? (in_pos - out_pos) : (BUFFER_SIZE - out_pos + in_pos) );

	 sem_destroy(&empty_slots);
	 sem_destroy(&full_slots);
	 pthread_mutex_destroy(&buffer_mutex);

	 return 0;
}
