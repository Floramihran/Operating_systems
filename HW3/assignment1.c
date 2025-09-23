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
	}
	if (pid > 0){
                printf("Parent PID = %d\n", getpid());
        }	
	
	return 0;
}
