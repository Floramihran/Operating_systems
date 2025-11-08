#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){

	char file_path[256];
	int fd;
	int file_size;
	int bytes_read;
	char buffer[1];

	write(STDOUT_FILENO, "Enter file path:   ", 19);
	bytes_read = read(STDIN_FILENO, file_path, sizeof(file_path) -1);
	if (bytes_read <= 0){
		perror("read file path");
		return 1; 
	}
	file_path[bytes_read -1] = '\0';

	fd = open(file_path, O_RDONLY);
	if (fd == -1){
		perror("open failed");
		return 1;
	}

	file_size = lseek(fd, 0, SEEK_END);
	if(file_size == -1){
		perror("lseek failed");
		close(fd);
		return 1;
	}

	for (int i = file_size -1; i >= 0; i--){
		if (lseek(fd, i, SEEK_SET) == -1){
		
			perror("lseek failed");
			break;
		}
		if (read(fd, buffer, 1) == 1){
			write(STDOUT_FILENO, buffer, 1);
		
		}
		write(STDOUT_FILENO, "\n", 1);

		close(fd);

		return 0;
	
	}
}
