#include <iostream>
#include<sys/socket.h>    //you know what this is for
#include<arpa/inet.h> //inet_addr , inet_ntoa , ntohs etc
#include<netinet/in.h>
#include<unistd.h>    //getpid
int main(int argc,char* argv[])
{
    int sock;
    // 创建sock
    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct sockaddr_in sin;
    sin.sin_family=AF_INET;
    sin.sin_port=htons(888);
    sin.sin_addr.s_addr=htonl(INADDR_ANY);
    //端口绑定
    bind(sock,(struct sockaddr*)&sin,sizeof(sin));
    // 监听端口
    listen(sock,5);

    // 等待连接
    sockaddr_in client;
    int len=sizeof(sockaddr_in);
    int sock_in=accept(sock,(struct sockaddr *) &client,(socklen_t *) &len);
    char msg[]="hello";
    send(sock_in,msg,sizeof(msg),0);
    close(sock_in);
    close(sock);
    return 0;
}