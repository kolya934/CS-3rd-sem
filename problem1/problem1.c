/*
	Problem1 "zombie"
	Protas Nikolay, 456gr.
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main ()
{
  int child_pid;

  child_pid = fork ();

	if (child_pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}  

  if (child_pid > 0) {
		printf("Child PID = %d\n",child_pid);    
		sleep (15);	
		//wait(NULL);
		//waitpid(child_pid, NULL, 0);
  }
  else {
    printf("I'm a child.\n");
    sleep(10);
		printf("Child: exit.\n");
		exit (0);
  }
  return 0;
}
