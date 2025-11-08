#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){

	const char *filename = "sparse.bin";
	const char *start_data = "START";
	const char *end_data = "END";
	int fd;
	int file_size;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1){
		perror("open for write");
		return 1;
	}
	write(fd, start_data, 5);

	if (lseek(fd, 1024 * 1024, SEEK_CUR) == -1){
		perror("lseek failed");
		close(fd);
		return 1;
	
	}	

	write(fd, end_data, 3);
	close(fd);

	fd = open(filename, O_RDONLY);
	if(fd == -1){
		perror("open for read");
		return 1;
	}

	file_size = lseek(fd, 0, SEEK_END);
	printf("Apparent file size: %d bytes\n", file_size);
	printf("Expected size : greater than or equal %d bytes\n", 5 + 1024*1024 + 3);
	close(fd);

	return 0;
}


/*
* Explanation: The file appears large but uses little disk space because:
* - The 1 MiB gap is a "hole" that contains no actual data
* - Filesystems don't store zeros for holes, just metadata
* - Only "START" and "END" portions use real disk blocks
* - du shows actual disk usage, ls shows total file size including holes
*/
