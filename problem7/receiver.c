#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/msg.h>

typedef struct msgbuf
	{
		long mtype;	
	} message_buf;	

int main(int argc,char** argv){

	int msqid;
	char *path ="key.path";
	key_t key;
	message_buf rbuf;

	if((key = ftok(path,0))<0){
		perror("ftok");
		exit (-1);
	}
	

	if((msqid = msgget(key,0666))<0){
		
		//if (errno !=EEXIST){perror("can't create msg");exit (-1);}else{
		//if ((msgid = msgget(key,0)) <0){perror("cant find msg");exit(-1);}}
		perror("msgget"); exit(1);
	}	
	


	if ((msgrcv(msqid,&rbuf,0,0,0))<0) {perror("msgrcv");}
	printf("Number of messages  %ld \n",rbuf.mtype);
	int count = rbuf.mtype;

	for (int i = 1; i < count; ++i)
	{
		if ((msgrcv(msqid,&rbuf,0,0,0))<0) {perror("msgrcv");}
		if (rbuf.mtype != 201){
			printf("Message %d received: %ld \n",i,rbuf.mtype);}
		else{
			printf("Received error code #201(Wrong args)\nExecution stopped\n");
			if (msgctl(msqid,IPC_RMID,NULL) < 0)
			{
				perror("msgctl");
				exit(1);
			}
			exit(1);
		}
	}
	
	if (msgctl(msqid,IPC_RMID,NULL) < 0)
	{
		perror("msgctl");
		exit(1);
	}

	return 0;
	
}



