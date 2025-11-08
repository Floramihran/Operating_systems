#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(){


	const char *filename = "numbers.txt";
	int fd;
	char buffer[4096];
	int bytes_read;
	int line4_offset = 0;
	int line_count = 0;
	char new_line[] = "100\n";

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1){
		perror("open for write");
		return 1;
	}

	for (int i = 1; i <= 10; i++){
		char line[16];
		int len = snprintf(line, sizeof(line), "%d\n", i);
		write(fd, line, len);
	}
	close(fd);

	fd = open(filename, O_RDWR);
	if(fd = -1){
		perror("open for read/ write");
		return 1;
	
	}

	bytes_read = read(fd, buffer, sizeof(buffer) -1);
	if (bytes_read <= 0){
	
		perror("read");
		close(fd);
	       	return 1;	
	
	}

	buffer[bytes_read] = '\0';

	for (int i = 0; i < bytes_read && line_count < 3; i++){
        	if (buffer[i] == '\n'){
            		line_count++;
            		if (line_count == 3){
                		line4_offset = i + 1;// Position after 3rd line
                		break;
            		}
        	}
    	}

   	 if (line4_offset == 0){
        	write(STDOUT_FILENO, "Could not find line 4\n", 22);
        	close(fd);
        	return 1;
    	}

    	lseek(fd, line4_offset, SEEK_SET);

    	int remainder_start = line4_offset;
    	int original_line4_len = 0;

    	for (int i = line4_offset; i < bytes_read; i++){
		
	        if (buffer[i] == '\n'){
            		original_line4_len = i - line4_offset + 1;
            		break;
                }
    	}

    	if (original_line4_len == 0){
       		 write(STDOUT_FILENO, "Could not determine line 4 length\n", 34);
        	 close(fd);
        	 return 1;
        }

   	int remainder_offset = line4_offset + original_line4_len;
    	int remainder_size = bytes_read - remainder_offset;

    	char remainder[4096];
    	lseek(fd, remainder_offset, SEEK_SET);
    	int remainder_read = read(fd, remainder, sizeof(remainder));

    	lseek(fd, line4_offset, SEEK_SET);
    	write(fd, new_line, strlen(new_line));

    	if (remainder_read > 0){
        	write(fd, remainder, remainder_read);
   	}

    	int new_size = line4_offset + strlen(new_line) + remainder_read;
    	ftruncate(fd, new_size);

    	lseek(fd, 0, SEEK_SET);
    	write(STDOUT_FILENO, "Final file content:\n", 20);
    	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0){
        	write(STDOUT_FILENO, buffer, bytes_read);
    
	}

    	close(fd);

    	return 0;

}
 

