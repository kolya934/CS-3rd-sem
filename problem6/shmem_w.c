/*
	Problem6 "Shared memory"
	Protas Nikolay, 456gr.
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<errno.h>

int main(int argc,char** argv){
	int *arr;
	int shmid;
	char *path ="key.path";
	key_t key;
	
	if((key = ftok(path,0))<0){
		perror("ftok");
		exit (-1);
	}
	
	if((shmid = shmget(key, 2*sizeof(int),0666|IPC_CREAT|IPC_EXCL))<0){
		
		if (errno !=EEXIST){perror("can't create shmem");exit (-1);}else{
		if ((shmid = shmget(key, 2*sizeof(int),0)) <0){perror("cant find shmem");exit(-1);}}
	}

	if((arr = (int*)shmat(shmid,NULL,0)) == (int*)(-1)){ perror("shamt"); exit(-1); };
	
	if (argc !=3){printf("wrong args!\n");exit(-1);}

	arr[0]=atoi(argv[1]);
	arr[1]=atoi(argv[2]);


	if(shmdt(arr)<0){perror("shmdt");exit(-1);};
	return 0;
	
}
