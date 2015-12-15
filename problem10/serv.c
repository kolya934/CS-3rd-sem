#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUF_SIZE 1000

int main(int argc, char** argv) {
	struct sockaddr_in servaddr, cliaddr;

	srand ( time(NULL) );
	int port = rand() % 10000 + 10000;
	printf("Port %d\n",port);

	int sockfd;
	int n, clilen;
	char sendline[BUF_SIZE], recvline[BUF_SIZE];

	if ( ( sockfd = socket(PF_INET, SOCK_DGRAM, 0) ) < 0 ) {
		perror("socket");
		exit(-1);
	}

	//client
	bzero(&servaddr, sizeof(servaddr));
	servaddr. sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind (sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		perror("bind");
		exit(-1);
	}

	while(1){
		if ((n = recvfrom(sockfd, recvline, BUF_SIZE, 0,  (struct sockaddr*) &cliaddr, &clilen)) < 0) {			perror("rcvfrom");
			close(sockfd);
			exit(-1);
}	

	printf("%s", recvline);
	
		if ((sendto(sockfd, recvline, BUF_SIZE, 0,  (struct sockaddr*) &cliaddr, clilen)) < 0) {			perror("rcvfrom");
			close(sockfd);
			exit(-1);
	}	
	
}
	close(sockfd);
	return 0;
}
