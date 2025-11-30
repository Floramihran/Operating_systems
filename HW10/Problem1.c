#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


long long counter = 0;
pthread_mutex_t mutex;
pthread_spinlock_t spinlock;


int N, M;

void* increment_unsync(void* arg){

	for (int i = 0; i < M; i++)
		counter++;
	return NULL;

}

void* increment_mutex(void* arg){

	for (int i = 0; i < M; i++){
		pthread_mutex_lock(&mutex);
		counter++;
		pthread_mutex_unlock(&mutex);
	  }
                
        return NULL;

}

void* increment_spinlock(void* arg){

		 for (int i = 0; i < M; i++){
           pthread_spin_lock(&spinlock);
           counter++;
           pthread_spin_unlock(&spinlock);
        }

        return NULL;

}



int main(int argc, char* argv[]){

	if (argc != 4){
		printf("Usage: %s mode num_threads increment_per_thread \n", argv[0]);
		printf("Modes are 0 = unsync, 1=mutex, 2=spinlock\n");
		return 1;
	}

	int mode = atoi(argv[1]);
	N = atoi(argv[2]);
	M = atoi(argv[3]);

	if (N <= 0 || M <= 0){
	
		printf("N and M must be positive integers \n");
		return 1;
	
	}

	pthread_t threads[N];
	long long expected = (long long)N * M;

	if (mode == 1)
		pthread_mutex_init(&mutex, NULL);
	else if (mode == 2)
		pthread_spin_init(&spinlock, 0);

	printf("Mode: ");
	if (mode == 0)
		printf ("No synchronization\n");	
	else if (mode == 1)
        printf ("mutex lock\n");
	else if (mode == 2)
		printf ("spinlock\n");

	printf("Threads: %d, Increments per thread: %d\n", N, M);
	printf("Expected value: %lld\n", expected);

	counter = 0;

	for (int i = 0; i < N; i++){
	
		switch(mode){
		
			case 0:
				pthread_create(&threads[i], NULL, increment_unsync, NULL);
				break;
			case 1:
				pthread_create(&threads[i], NULL, increment_mutex, NULL);
                                break;	
			case 2:
				pthread_create(&threads[i], NULL, increment_spinlock, NULL);
                                break;
			default:
				perror("thread creation failed");
				exit(1);
				break;	
		}
	}

	for (int i = 0; i < N; i++)
		pthread_join(threads[i], NULL);

	printf("Actual value: %lld\n", counter);
	printf("Difference: %lld\n", expected - counter);
	printf("Result: %s\n", counter ==  expected ? "CORRECT" : "INCORRECT");

	if (mode ==  1)
		pthread_mutex_destroy(&mutex);
	else if (mode == 2)
		pthread_spin_destroy(&spinlock);

	return 0;

}
