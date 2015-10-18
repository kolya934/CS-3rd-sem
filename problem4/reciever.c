/*
	Problem4 "fifo"
	Protas Nikolay, 456gr.
*/
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{	
	int fd;
	char	readbuffer[100];
	
	if ( (fd = open("my.fifo", O_RDONLY)) < 0 ) {
		perror("open");
    exit(-1);
    }
    
	printf("FIFO opened!\n");
	
	read(fd, readbuffer, 100);
	printf("Received: %s\n", readbuffer);
	
	if (close(fd) < 0 ) {
		perror("close");
    exit(-1);
    }
    
	printf("FIFO closed!\n");
	
return 0;
}
