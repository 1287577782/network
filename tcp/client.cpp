#include <iostream>
#include <iostream>
#include <arpa/inet.h> //inet_addr , inet_ntoa , ntohs etc
#include <netinet/in.h>
#include <unistd.h>    //getpid
#include <sys/socket.h>    //you know what this is for
#include <string.h>
#include <stdio.h>
#define MAXLINE 1024

int main(int argc,char *argv[])
{
    int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	if (argc != 2)
		std::cout<<"usage: a.out <IPaddress>";

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		std::cout<<"socket error";

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(888);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		std::cout<<"inet_pton error for "<<argv[1];

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		std::cout<<"connect error";

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) 
    {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			std::cout<<"fputs error";
	}
	if (n < 0)
		std::cout<<"read error";
    
    return 0;
}