#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(){
	
	char src_file[256];
	char dest_file[256];
	char buffer[4*1024];	
	int read_count, write_count;
	int src_fd, dest_fd;
	int total_bytes = 0;

	write(STDOUT_FILENO, "Enter source file path:       ", 30);
	read_count = read(STDIN_FILENO, src_file, sizeof(src_file) - 1);
	if (read_count <= 0){
		perror("reading source path");
		return 1;
	}
	src_file[read_count - 1] = '\0';

	write(STDOUT_FILENO, "Enter destination file path:       ", 30);
	read_count = read (STDIN_FILENO, dest_file, sizeof(dest_file) - 1);
	if (read_count <= 0){
		perror("reading destination path");
		return 1;
	}	
	dest_file [read_count - 1] = '\0';

	src_fd = open(src_file, O_RDONLY);
	if (src_fd == -1){
		perror("opening source file");
		return 1;
	}

	dest_fd =open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dest_fd == -1){
		perror("operm error");
		close(src_fd);
		return 1;
	}

	while((read_count = read(src_fd, buffer, sizeof(buffer))) > 0){
		char *ptr = buffer;
		int remaining = read_count;

		while (remaining > 0){
			
			write_count = write(dest_fd, ptr, remaining);
			if (write_count == -1){
				
				perror("write error");
				close(src_fd);
				close(dest_fd);
				return 1;
			}
			remaining -= write_count;
			ptr += write_count;
			total_bytes += write_count;
		}
	}
	

	if (read_count == -1){
		perror("read error");
		return 1;
	}

	printf("Total bytes transferred: %d\n", total_bytes);

	close(src_fd);
	close(dest_fd);

	return 0;	


}
