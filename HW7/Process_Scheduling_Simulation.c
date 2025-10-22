#include <stdio.h>
#include <stdlib.h>

struct Process{
	int pid;
	int arrival_time;
	int burst_time;
	int turnaround_time;
	int waiting_time;
	int response_time;
	int completion_time;

};

void swap(struct Process *a, struct Process *b){
	struct Process temp = *a;
	*a = *b;
	*b = temp;
}

void sortByArrival(struct Process processes[], int n){
	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - i - 1; j++){
			if(processes[j].arrival_time > processes[j + 1].arrival_time){
				swap(&processes[j], &processes[j + 1]);
			}
		}
	
	}
}

void sortByBurst(struct Process processes[], int n){
	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - i - 1; j++){
			if(processes[j].burst_time > processes[j + 1].burst_time){
				swap(&processes[j], &processes[j + 1]);
			}
		
		}
	
	}

}

void fcfs(struct Process processes[], int n){
	printf("\n=== First Come First Served (FCFS) ===\n");

	sortByArrival(processes, n);

	int current_time = 0;

	printf("Grantt chart: |");

	for (int i = 0; i < n; i++){
		if (processes[i].arrival_time > current_time)
			current_time = processes[i].arrival_time;

		printf("  P%d  ", processes[i].pid);
		if (i < n - 1)
			printf("|");
		
		processes[i].completion_time = current_time + processes[i].burst_time;
		processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
		processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
		processes[i].response_time = processes[i].waiting_time;

		current_time = processes[i].completion_time;
	}
	printf("|\n");

	printf("PID\tAT\tBT\tWT\tTAT\tRT\n");

	float avg_wt = 0, avg_tat = 0, avg_rt = 0;

	for (int i = 0; i < n; i++){
		printf("%d \t %d \t %d \t %d \t %d \t %d \n",
			processes[i].pid,
			processes[i].arrival_time,
			processes[i].burst_time,
			processes[i].waiting_time,
			processes[i].turnaround_time,
			processes[i].response_time
		      );

		avg_wt += processes[i].waiting_time;
		avg_tat += processes[i].turnaround_time;
		avg_rt += processes[i].response_time;
	
	}

	avg_wt /= n;
	avg_tat /= n;
	avg_rt /= n;

	printf("\nAverage Waiting Time: %.2f\n", avg_wt);
	printf("Average Turnaround Time: %.2f\n", avg_tat);
	printf("Average Response Time: %.2f\n ", avg_rt);

}

void sjf(struct Process processes[], int n){
	printf("\n=== Shortest Job First (SJF) ===\n");

	struct Process *sjf_processes = malloc(n * sizeof(struct Process));
	for (int i = 0; i < n; i++){
		sjf_processes[i] = processes[i];
	
	}
	
	int completed = 0;
	int current_time = 0;
	int *executed = calloc(n, sizeof(int));

	printf("Gantt Chart: |");

	while (completed < n){
		int shortest = -1;
		int min_burst = 9999;

		for (int i = 0; i < n; i++){
			if (!executed[i] && sjf_processes[i].arrival_time <= current_time){
				if(sjf_processes[i].burst_time< min_burst){	
				min_burst = sjf_processes[i].burst_time;
				shortest = i;
			}

			else if (sjf_processes[i].burst_time == min_burst && shortest != -1){
				if (sjf_processes[i].arrival_time < sjf_processes[shortest].arrival_time){
				shortest = i;
				}
			}
		}
	
		}

		if (shortest == -1){
			current_time++;
			continue;
		}
		
		printf("  P%d   ", sjf_processes[shortest].pid);
		if(completed < n - 1)
			printf("|");
	


		sjf_processes[shortest].completion_time = current_time + sjf_processes[shortest].burst_time;
		sjf_processes[shortest].turnaround_time = sjf_processes[shortest].completion_time - sjf_processes[shortest].arrival_time;
		sjf_processes[shortest].waiting_time = sjf_processes[shortest].turnaround_time - sjf_processes[shortest].burst_time;
		sjf_processes[shortest].response_time = sjf_processes[shortest].waiting_time;

		current_time = sjf_processes[shortest].completion_time;
		executed[shortest] = 1;
		completed++;
}
	printf("|\n");

	printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
	float avg_wt = 0, avg_tat = 0, avg_rt = 0;

	for (int i = 0; i < n; i++){
		printf("%d \t %d \t %d \t %d \t %d \t %d \n", 
				sjf_processes[i].pid,
				sjf_processes[i].arrival_time,
				sjf_processes[i].burst_time,
				sjf_processes[i].waiting_time,
				sjf_processes[i].turnaround_time,
				sjf_processes[i].response_time
			);

			avg_wt += sjf_processes[i].waiting_time;
			avg_tat += sjf_processes[i].turnaround_time;
			avg_rt += sjf_processes[i].response_time;
	}

	avg_wt /= n;
	avg_tat /= n;
	avg_rt /= n;

	printf("\nAverage Waiting Time: %.2f\n",  avg_wt);
	printf("Average Turnaround Time: %.2f\n", avg_tat);
	printf("Average response Time: %.2f\n", avg_rt);

	free(sjf_processes);
	free(executed);
	
}


int main(){
	int n;

	printf("Enter the number of processes: ");
	scanf("%d", &n);

	if(n < 0){
		printf("Invalid  number of processes!\n");
		return 1;
	}
	else if (n == 0){
		printf("Nothing to do!\n");
		return 0;
	}

	struct Process *processes = malloc(n * sizeof(struct Process));

	for (int i = 0;  i < n; i++){
		printf("Enter the arrival time and burst time for process %d: ", i + 1);
		scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
		processes[i].pid = i + 1;
		processes[i].turnaround_time = 0;
		processes[i].waiting_time = 0;
		processes[i].response_time = 0;
		processes[i].completion_time = 0;
	}

	printf("\n\n");

	fcfs(processes, n);

	printf("\n\n");

	sjf(processes, n);

	free(processes);
	return 0;
		
}	





