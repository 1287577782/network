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
const char srvip[]="101.226.4.6";
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
    head->id=htons(1234);
    head->flags=htons(0x0100);
    head->q_count=htons(1);
    strcpy(buf+sizeof(DNSHeader)+1,argv[1]);
    char *p = nullptr;
    p=&buf[0]+sizeof(DNSHeader)+1;
    while (p < ( buf +sizeof(DNSHeader)+1+strlen(argv[1]) ))
    {
        if( *p == '.')
        {
            *(p-i-1)=char(i);
            i=0;
        }
        else  
        {
            i++;
        }
        p++;
    }
    *(p-i-1)=char(i);
    *(p+1)='\0';
    printf("%d\n",int('\001'));

    DNSQuery * dnsqurey=(DNSQuery *) (buf+sizeof(DNSHeader)+2+strlen(argv[1]));
    dnsqurey->classes=htons(1);
    dnsqurey->type=htons(1);
    len=sendto(clientfd,buf,sizeof(DNSHeader)+2+sizeof(DNSQuery)+strlen(argv[1]),0,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    i=sizeof(struct sockaddr_in);
    memset(buf,0,BUF_SIZE);
    len=recvfrom(clientfd,buf,BUF_SIZE,0,(struct sockaddr*)&serveraddr,(socklen_t *)&i);
    printf("len:%d\n",len);
    if(len<0)
    {
        printf("recv error, errno:%d\n",errno);
        return -1;
    }
    // if(head->ans_count==0)
    // {
    //     printf("answer error\n");
    //     return -1;
    // }
    p=buf+len-4;
    printf("%s ==> %u.%u.%u.%u\n", argv[1], (unsigned char)*p, (unsigned char)*(p + 1), (unsigned char)*(p + 2), (unsigned char)*(p + 3));
    return 0;
}
