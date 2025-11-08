#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(){

	const char *filename = "log.txt";
	char input[256];
	char output[512];
	int fd;
	int bytes_read;
	int offset;


	fd = open(filename, O_WRONLY | O_CREAT| O_APPEND, 0644);
	if(fd == -1){
		perror("open failed");
		return 1;
	}

	write(STDOUT_FILENO, "Enter log message:   ", 20);
	bytes_read = read(STDIN_FILENO, input, sizeof(input) - 1);
	if (bytes_read <= 0){
		perror("read input");
		close(fd);
		return 1;
	}
	input[bytes_read] = '\0';

	int len = snprintf(output, sizeof(output), "PID = %d ", getpid());

	strncpy(output + len, input, sizeof(output) - len -1);
	output[sizeof(output) -1] = '\0';

	int total_len = len + bytes_read;
	if (output[sizeof(output) - 1] != '\n'){
		output[total_len] = '\n';
		output[total_len + 1] = '\0';
		total_len++;
	}

	if (write(fd, output, total_len) == -1){
		perror("write failed");
		close(fd);
		return 1;
	}

	offset = lseek(fd, 0, SEEK_CUR);
	if(offset == -1){
	
		perror("lseek failes");
	
	} else {
		printf("Final file offset: %d\n", offset);
	
	}

	close(fd);
	return 0;

}

/*
* Explanation: O_APPEND forces writes to the end, but doesn't prevent the file position from being updated.
* After each write(), the file position moves to the new end of file.
* lseek(SEEK_CUR) reads this updated position, showing the correct file size growth.
*/


