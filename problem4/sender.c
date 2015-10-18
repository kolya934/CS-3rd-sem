/*
	Problem5 "fifo"
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
	char	writebuffer[100];
	if (mkfifo("my.fifo", 0777) < 0){
		perror("mkfifo");
		exit (-1);
	}
	
	printf("FIFO created!\n");
	
	if ( (fd = open("my.fifo", O_WRONLY)) < 0 ) {
		perror("open");
    exit(-1);
    }
    
	printf("FIFO opened!\nEnter your message > ");
	
	scanf("%s",writebuffer);
	
	write(fd, writebuffer, 100);
	
	if (close(fd) < 0 ) {
		perror("close");
    exit(-1);
    }
	printf("FIFO closed!\n");
	
	if (remove("my.fifo")<0) {
		perror("remove");
    exit(-1);
		}
	printf("FIFO removed!\n");
	
return 0;
}
