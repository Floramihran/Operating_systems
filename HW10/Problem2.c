#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


long long balance = 0;
pthread_mutex_t account_mutex;
pthread_spinlock_t account_spinlock;


int use_mutex = 1;
int use_long_cs = 0;
int num_threads = 4;
int operations_per_thread = 100000;

void* deposit_thread(void* arg){

	for (int i = 0; i < operations_per_thread; i ++){
	
		if(use_mutex)
			pthread_mutex_lock(&account_mutex);
		else 
			pthread_spin_lock(&account_spinlock);

		balance++;

		if(use_long_cs)
			usleep(100);

		if(use_mutex)
			pthread_mutex_unlock(&account_mutex);
		else
			pthread_spin_unlock(&account_spinlock);
	
	}

	return NULL;
}

void* withdraw_thread(void* arg){

        for (int i = 0; i < operations_per_thread; i ++){

                if(use_mutex)
                        pthread_mutex_lock(&account_mutex);
                else
                        pthread_spin_lock(&account_spinlock);

                balance--;

                if(use_long_cs)
                        usleep(100);

                if(use_mutex)
                        pthread_mutex_unlock(&account_mutex);
                else
                        pthread_spin_unlock(&account_spinlock);

        }

        return NULL;
}

int main(int argc, char* argv[]){

	if(argc != 3){
	
		printf("Usage: %s sync_type cs_length \n", argv[0]);
		printf(" snc_type: mutex | spin\n");
		printf(" cs_length: short | long\n");
		return 1;
	
	}

	use_mutex = (strcmp(argv[1], "mutex") == 0);
	use_long_cs = (strcmp(argv[2], "long") == 0);

	if (!use_mutex && strcmp(argv[1], "spin") != 0){
		printf("sync_type must be 'mutex' or 'spin'\n");
		return 1;
	}

	if (!use_long_cs && strcmp(argv[2], "short") != 0){
                printf("cs_length must be 'short' or 'long'\n");
                return 1;
        }


	printf("Syncronization: %s\n", use_mutex ? "Mutex" : "Spinlock");
	printf("Critical Section: %s\n", use_long_cs ? "Long" : "Short");
	printf("Threads: %d (2 deposit, 2 withdraw)\n", num_threads);
	printf("Operation per thread: %d\n", operations_per_thread);
	printf("Expected balance: 0\n");

	if (use_mutex)
		pthread_mutex_init(&account_mutex, NULL);
	else 
		pthread_spin_init(&account_spinlock, 0);

	balance = 0;

	pthread_t threads[num_threads];
	int deposit_threads = num_threads / 2;
	int withdraw_threads = num_threads - deposit_threads;

	for (int i = 0; i < deposit_threads; i++)
		pthread_create(&threads[i], NULL, deposit_thread, NULL);
	for (int i = deposit_threads; i < num_threads; i++)
		pthread_create(&threads[i], NULL, withdraw_thread, NULL);

	for (int i = 0; i < num_threads; i++)
		pthread_join(threads[i], NULL);

	if (use_mutex)
		pthread_mutex_destroy(&account_mutex);
	else
		pthread_spin_destroy(&account_spinlock);

	if (balance != 0)
		printf("INCORRECT\n");

	return 0;

}



