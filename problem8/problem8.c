/*
	Problem8 "deadlock"
	Protas Nikolay, 456gr.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM_NAME_1 "/mysem1"
#define SEM_NAME_2 "/mysem2"

int main()
{
    sem_t *sem1;     //semaphore struct
    sem_t *sem2;
    int pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(-1);
    }
    int i = 0;
    if (pid > 0)
    {
        //parent
        if ( (sem1 = sem_open(SEM_NAME_1, O_CREAT, 0777, 1)) == SEM_FAILED )
        {
            perror("parent: sem_open");
            exit(-1);
        }

        if ( (sem2 = sem_open(SEM_NAME_2, O_CREAT, 0777, 1)) == SEM_FAILED )
        {
            perror("parent: sem_open");
            exit(-1);
        }

        //critical section   
        if (sem_wait(sem1) < 0)      //p(s)
        {
            perror("parent: sem_wait");
            exit(-1);
        }

        for (i = 0; i < 500; i++)
      	{
      		printf("Parent 	#%d\n",i);
        	if (i==250)
	       	{	
	       		printf("PARENT READY\n");
	       		sem_wait(sem2);
	       	}
	    }
        sem_post(sem1);      //v(s)
        //end of critical section
    }
    
    if (0 == pid)
    {
        //child
        if ( (sem1 = sem_open(SEM_NAME_1, O_CREAT, 0777, 1)) == SEM_FAILED )
        {
            perror("parent: sem_open");
            exit(-1);
        }

        if ( (sem2 = sem_open(SEM_NAME_2, O_CREAT, 0777, 1)) == SEM_FAILED )
        {
            perror("parent: sem_open");
            exit(-1);
        }

        //critical section   
        if (sem_wait(sem2) < 0)      //p(s)
        {
            perror("child: sem_wait");
            exit(-1);
        }
        for (i = 0; i < 500; i++)
        {
			printf("Child 	#%d\n",i);
	    	if (i == 250)
	       	{
    			printf("CHILD READY\n");
   				sem_wait(sem1);
   			}
       	}
        sem_post(sem2);      //v(s)
        //end of critical section
    }
    
    return 0;
}
