#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

	pid_t pid = fork();

	if (pid < 0){
		perror("fork failed");
		exit(1);
	}
	if (pid == 0){
		printf("Child PID = %d\n", getpid());
		printf("Child process exiting.\n");
		exit(0);
	}
	else{
		printf("Parent sleeping for 20 seconds.");
		sleep(20);
		printf("Parent exiting.\n");
	}

	return 0;

}
