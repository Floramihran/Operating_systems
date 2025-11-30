#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define K 2
#define N 8

sem_t printers;
pthread_mutex_t counter_mutex;

int working_printers = 0;
int max_working_printers = 0;

void* print_job(void* arg){

	int job_id = *(int*)arg;

	printf("Job %d: waiting for printer \n", job_id);

	sem_wait(&printers);

	pthread_mutex_lock(&counter_mutex);


	if (++working_printers > max_working_printers)
		max_working_printers = working_printers;

	printf("Job %d: Started printing, working printers: %d\n", job_id, working_printers);
	pthread_mutex_unlock(&counter_mutex);

	int print_time = 1 + (rand() % 3);
	sleep(print_time);

	pthread_mutex_lock(&counter_mutex);
	working_printers--;
	printf("Job %d: Finished printing after %d seconds (working printers: %d)\n", job_id, print_time, working_printers);

	pthread_mutex_unlock(&counter_mutex);

	sem_post(&printers);

	return NULL;
	
}

int main(int argc, char* argv[]){

	int num_printers = K;
	int num_jobs = N;

	if (argc == 3){
		
		num_printers = atoi(argv[1]);
		num_jobs = atoi(argv[2]);
	}

	printf("Printers available: %d\n", num_printers);
	printf("Print jobs: %d\n", num_jobs);

	sem_init(&printers, 0, num_printers);
	pthread_mutex_init(&counter_mutex, NULL);

	srand(time(NULL));

	pthread_t jobs[num_jobs];
	int job_ids[num_jobs];


	for (int i = 0; i < num_jobs; i++){
		job_ids[i] = i + 1;
		pthread_create(&jobs[i], NULL, print_job, &job_ids[i]);

		usleep(100000);

	}

	for (int i = 0; i < num_jobs; i++)
		pthread_join(jobs[i], NULL);

	printf("\n");
	printf("Maximum concurrently used printers: %d\n ", max_working_printers);
	sem_destroy(&printers);
	pthread_mutex_destroy(&counter_mutex);

	return 0;
}


