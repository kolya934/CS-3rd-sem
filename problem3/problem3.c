/*
	Problem3 "pipe"
	Protas Nikolay, 456gr.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
	if (argc != 2){
		printf("Wrong args\n");
		exit(0);
	}
	
	int     fd[2];
	pid_t   childpid;
	char    readbuffer[100];
        
	pipe(fd);
        
	if((childpid = fork()) == -1){
		perror("fork");
		exit(-1);
		}

	if(childpid == 0){
		close(fd[1]);
		if (read(fd[0], readbuffer, sizeof(readbuffer)) < 0){
			perror("read");
			exit(-1);};
			
		printf("> %s\n", readbuffer);}
	
	else{
		close(fd[0]); 
		if (write(fd[1], argv[1], (strlen(argv[1])+1)) < 0){
			perror("write"); exit(-1);};
		}
        
	return 0 ;
}
