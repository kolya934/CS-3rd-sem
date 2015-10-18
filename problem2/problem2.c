/*
	Problem2 "interpreter"
	Protas Nikolay, 456gr.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	
	
	pid_t cPID;
	char command[100];
	char**vector;
	int n,i;
	char* quit="quit";																			//
	
	printf("	 ↓ ↓ ↓ Syntax ↓ ↓ ↓\n[path] [num of args] [arg1] [arg2] etc.\n \"quit\" for quit\n\n>");
	
	scanf ("%s",command);
	while (strcmp(command,quit)!=0){
		scanf ("%d",&n);
		if((vector=(char**)malloc(n*sizeof(char*)))==NULL) {
    	perror("malloc");
    	exit(-1);
  	};
		
		if((vector[0]=(char*)malloc(100*sizeof(char)))==NULL) {
    	perror("malloc");
    	exit(-1);
  	};
		
		
		
		vector[0]=command;
		for(i=1;i<=n;i++){			
			if((vector[i]=(char*)malloc(100*sizeof(char)))==NULL) {
    		perror("malloc");
    		exit(-1);
  		};
			
			scanf("%s",vector[i]);
		}
		
		vector[n+1]=NULL;
			
		cPID=fork();
		
		if(cPID<0) {
			perror("fork");
			exit(-1);
		}
		if(cPID==0) {
			execvp(command,vector);
			perror("execvp");
			exit(-1);
		} 
		wait();
		printf("\n>");
		scanf ("%s",command);
		
	}

	return 0;
}
