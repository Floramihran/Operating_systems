#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid = fork();
	if(pid < 0){
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0){
		execl("/bin/ls", "ls", NULL);
		perror("execl failed");
		exit(1);
	}
	else{
		waitpid(pid, NULL, 0);
		printf("Parent process done\n");
	}
	
	return 0;
	}
