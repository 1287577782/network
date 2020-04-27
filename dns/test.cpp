#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#define BUF_SIZE 1024
#define SER_PORT 53
int main(int argc ,char **argv)
{
    unsigned char buf[BUF_SIZE];
    int serverfd,clientfd,len=0,i;
    struct sockaddr_in serveraddr,addr;

    return 0;
}
