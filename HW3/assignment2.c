#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t child1, child2;
	int status;

	child1 = fork();

	if (child1 < 0){
		perror("fork failed");
		exit(1);
	}
	else if (child1 == 0){
		printf("Child 1 PID = %d\n", getpid());
		sleep(2);
		exit(3);
	}
	else{
	
	child2 = fork();
	if (child2 < 0){
                perror("fork failed");
      		exit(1);
      	}
        else if (child2 == 0){
                printf("Child 2 PID = %d\n", getpid());
		sleep(4);
		exit(5);
	}
	else{
		waitpid(child2, &status, 0);
		printf("Child 2 exited with %d\n" , WEXITSTATUS(status));
	
	 	wait(&status);
                printf("Child 1 exited with %d\n" , WEXITSTATUS(status));
	}
	}
	return 0;

}
