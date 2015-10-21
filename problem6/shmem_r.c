/*
	Problem6 "Shared memory"
	Protas Nikolay, 456gr.
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<errno.h>

int main(){
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

	printf("SUM= %d\n",arr[1]+arr[0]);	

	if(shmdt(arr)<0){perror("shmdt");exit(-1);};
	return 0;
	
}
