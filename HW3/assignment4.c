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
		exit(1);
	}

	                                                                            child2 = fork();                                                            if (child2 < 0){                                                                   perror("fork failed");                                                      exit(1);                                                            }                                                                            else if (child2 == 0){                                                              exit(2);                                                           }

	waitpid(child1, &status, 0);
	if (WIFEXITED(status)){
		printf("Child 1 exited normally with status = %d\n", WEXITSTATUS(status));
	}else{
		printf("Child 1 did not exit normally.");
	}
	

	waitpid(child2, &status, 0);                                                if (WIFEXITED(status)){
                printf("Child 2 exited normally with status = %d\n", WEXITSTATUS(status));
	}else{
                printf("Child 2 did not exit normally.");
        }
	
	return 0;
}
