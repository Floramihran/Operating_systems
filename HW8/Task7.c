#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){

    	char file1_path[256];
    	char file2_path[256];
    	int fd1, fd2;
    	char buf1[4096];
    	char buf2[4096];
    	int bytes_read1, bytes_read2;
    	int byte_index = 0;
    	int found_difference = 0;

    	write(STDOUT_FILENO, "Enter first file path:  ", 24);
    	bytes_read1 = read(STDIN_FILENO, file1_path, sizeof(file1_path) - 1);
    	if (bytes_read1 <= 0){

        	perror("read file1 path");
        	return 1;
    	}
    
	file1_path[bytes_read1 - 1] = '\0';

    	write(STDOUT_FILENO, "Enter second file path: ", 24);
    	bytes_read2 = read(STDIN_FILENO, file2_path, sizeof(file2_path) - 1);
    	if (bytes_read2 <= 0){

        	perror("read file2 path");
        	return 1;
	}
    
	file2_path[bytes_read2 - 1] = '\0';

    	fd1 = open(file1_path, O_RDONLY);
    	
	if (fd1 == -1){
		
        	perror("open file1");
        	return 1;
	}

    	fd2 = open(file2_path, O_RDONLY);
    	if (fd2 == -1){

        	perror("open file2");
        	close(fd1);
        	return 1;
	}

    	while (1){
		
        	bytes_read1 = read(fd1, buf1, sizeof(buf1));
        	bytes_read2 = read(fd2, buf2, sizeof(buf2));

        if (bytes_read1 == -1 || bytes_read2 == -1){
            perror("read");
            break;
        }

        if (bytes_read1 != bytes_read2){
            int diff_pos = byte_index + (bytes_read1 < bytes_read2 ? bytes_read1 : bytes_read2);
            char msg[64];
            int len = snprintf(msg, sizeof(msg), "Files differ at byte %d (different sizes)\n", diff_pos);
            write(STDOUT_FILENO, msg, len);
            found_difference = 1;
            break;
        }

        if (bytes_read1 == 0) {
            break;
        }

        for (int i = 0; i < bytes_read1; i++){
            if (buf1[i] != buf2[i]){
                char msg[64];
                int len = snprintf(msg, sizeof(msg), "Files differ at byte %d\n", byte_index + i);
                write(STDOUT_FILENO, msg, len);
                found_difference = 1;
                break;
            }
        }

        if (found_difference) {
            break;
        }

        byte_index += bytes_read1;
    }

    if (!found_difference && bytes_read1 == 0 && bytes_read2 == 0){
        write(STDOUT_FILENO, "Files are identical\n", 20);
    }

    close(fd1);
    close(fd2);

    return 0;
}

