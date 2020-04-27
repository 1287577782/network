#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include "dns.h"
#define BUF_SIZE 1024
#define SER_PORT 53
const char srvip[]="8.8.8.8";
int main(int argc ,char **argv)
{
    char buf[BUF_SIZE];
    int serverfd,clientfd,len=0,i;
    struct sockaddr_in serveraddr,addr;
    if( (clientfd = socket(AF_INET,SOCK_DGRAM,0)) < 0 )
    {
        printf("create socket failed , error : %d \n",errno);
        return -1;
    }
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(SER_PORT);
    inet_aton(srvip,&serveraddr.sin_addr);
    memset(buf,0,BUF_SIZE);

    DNSHeader * head = (DNSHeader *)buf;
    head->id=(unsigned short )1;
    head->rd=1;
    head->ra=1;
    head->q_count=htons(1);
    strcpy(buf+sizeof(DNSHeader)+1,argv[1]);
    char *p = nullptr;
    p=buf+sizeof(DNSHeader)+1;
    while (p < ( buf +sizeof(DNSHeader)+strlen(argv[1]) ))
    {
        if( *p == '.')
        {
            *(p-i-1)=i;
            i=0;
        }
        else
        {
            i++;
        }
        p++;
    }
    *(p-i-1)=i;

    DNSQuery * dnsqurey=(DNSQuery *) (buf+sizeof(DNSHeader)+2+strlen(argv[1]));
    dnsqurey->classes=htons(1);
    dnsqurey->type=htons(1);
    len=sendto(clientfd,buf,sizeof(DNSHeader)+2+sizeof(DNSQuery)+strlen(argv[1]),0,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    i=sizeof(struct sockaddr_in);
    len=recvfrom(clientfd,buf,BUF_SIZE,0,(struct sockaddr*)&serveraddr,(socklen_t *)&i);
    if(len<0)
    {
        
    }




    return 0;
}
