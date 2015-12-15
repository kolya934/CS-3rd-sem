#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1000

int main(int argc, char  **argv)
{	
	struct sockaddr_in servaddr, cliaddr;

	int sockfd;
	int n;
	char sendline[BUF_SIZE], receiveline[BUF_SIZE];

	if (argc!=3)
	{
		printf("Insert <IP> <port>\n");
		exit(-1);
	}

	if ((sockfd = socket(PF_INET, SOCK_DGRAM,0))<0)
	{
		perror("socket");
		exit(-1);
	}

	// client
	bzero(&cliaddr,sizeof(cliaddr)); //обнуляем

	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(0);
	cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd,(struct sockaddr *)&cliaddr , sizeof(cliaddr))<0)
	{
		perror("bind");
		exit(-1);
	}

	//server

	bzero(&servaddr,sizeof(servaddr)); //обнуляем

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);



	if (inet_aton(argv[1],&servaddr.sin_addr) == 0)
	{
		printf("Ivalid IP\n");
		close(sockfd);
		exit(-1);
	}
	
	printf("Insert strings:\n");
	while(1){
	fgets(sendline, BUF_SIZE, stdin);

	if (sendto(sockfd,sendline, strlen(sendline)+1,0, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
		{
			perror("sendto");
			close(sockfd);
			exit(-1);
		}	
		}
	if (recvfrom(sockfd,receiveline,BUF_SIZE,0, (struct sockaddr*)NULL,NULL)<0)
		{
			perror("recvfrom");
			close(sockfd);
			exit(-1);
		}

	printf("%s\n", receiveline);
	close(sockfd);

	return 0;
}