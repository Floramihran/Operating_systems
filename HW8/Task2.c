#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(){

	const char *filename = "data.txt";
	const char *data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char buffer[32];
	int fd;
	int size;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1){
		
		perror ("open for write");
		return 1;
	}
	write(fd, data, 26);
	close(fd);

	fd = open(filename, O_RDWR);
	if (fd == -1){
		perror("open for read/write");
		return 1;
	}

	size = lseek(fd, 0, SEEK_END);
	printf("Initial size: %d bytes\n", size);

	if (ftruncate(fd, 10) == -1){
		perror("ftruncate failed");
		close(fd);
		return 1;
	}

	size = lseek(fd, 0, SEEK_END);
        printf("New size after truncation: %d bytes\n", size);
		
	lseek(fd, 0, SEEK_SET);
	int bytes_read = read(fd, buffer, 10);
	if (bytes_read > 0){
		write(STDOUT_FILENO, "reamining content:  ", 20);
		write(STDOUT_FILENO, buffer, bytes_read);
		write(STDOUT_FILENO, "\n", 1);
	}

	close(fd);

	return 0;
}
