/*
	Problem7 "msg"
	Protas Nikolay, 456gr.
*/

#include<stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/msg.h>

typedef struct msgbuf
	{
		long type;	
	} message_buf;	

int main(int argc,char** argv){
	
	int msqid;
	char *path ="key.path";
	key_t key;
	message_buf sbuf;
	
	if((key = ftok(path,0))<0){
		perror("ftok");
		exit (-1);
	}
	
	if((msqid = msgget(key,0666|IPC_CREAT))<0){
		
		//if (errno !=EEXIST){perror("can't create msg");exit (-1);}else{
		//if ((msgid = msgget(key,0)) <0){perror("cant find msg");exit(-1);}}
		perror("msgget"); exit(1);
	}

	//number of messages
	sbuf.type = argc-1;
		if ((msgsnd(msqid,&sbuf,0,IPC_NOWAIT))< 0)
		{
			perror("msgsnd");
		}else{printf("SENT!\ntype = %ld\n",sbuf.type);};


	int i;
	/*for (int i = 1; i < argc; ++i)
	{
		sbuf.type = i;
		if ((msgsnd(msqid,&sbuf,0,IPC_NOWAIT))< 0)
		{
			perror("msgsnd");
		}else{printf("SENT!\ntype = %ld\n",sbuf.type);};
	
	}*/

	for (int i = 1; i < 201; ++i)
	{
		for (int j = 1; j < argc; ++j)
		{	
			if (atoi(argv[j])>200) //?? argv[] > 200 ??
			{
				printf("Wrong args!\nExecution stopped\n");
				sbuf.type = 201;
				if ((msgsnd(msqid,&sbuf,0,IPC_NOWAIT))< 0)
				{
					perror("msgsnd");
				}else{printf("Sent error #201.\n");}
				exit(1);
			}
			
			if (atoi(argv[j])==i)
			{	
				sbuf.type = i;
				if ((msgsnd(msqid,&sbuf,0,IPC_NOWAIT))< 0)
				{
					perror("msgsnd");
				}else{printf("SENT: type = %ld\n",sbuf.type);};
			}
		}
	}
	
	

	
	

	return 0;
	
}
