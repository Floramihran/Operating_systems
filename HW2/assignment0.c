#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int ret1 = fork();
    if(ret1 == 0){
	    printf("After 1st fork, Child: PID=%d , PPID=%d\n", getpid(), getppid());
	}else{
	    printf("After 1st fork, Parent: PID=%d , ChildPID=%d\n", getpid(), ret1);
	}

	int ret2 = fork();
     if(ret2 == 0){       
		printf("After 2nd fork, Child: PID=%d , PPID=%d\n", getpid(), getppid()); 
	}else{
        printf("After 2nd fork, Parent: PID=%d , ChildPID=%d\n", getpid(), ret2);
        }
	
	int ret3 = fork();
    if(ret3 == 0){              
		printf("After 3rd fork, Child: PID=%d , PPID=%d\n", getpid(), getppid());   
	}else{
         printf("After 3rd fork, Parent: PID=%d , ChildPID=%d\n", getpid(), ret3);
        }
	
	return 0;

}
