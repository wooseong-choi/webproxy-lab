#include "csapp.h"

void echo(int connfd);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; /* Enough space for any address */
    char client_hostname[MAXLINE], client_port[MAXLINE];

    // printf("what is argvs %s %s \n" , argv[0],argv[1]);
    // 파일이름, 포트 인자로 받는다. 인자가 하나라도없다면 종료
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    // 소켓 열고 바인드 하고 리슨까지 한다.
    listenfd = Open_listenfd(argv[1]);
    while(1){
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s, %s )\n", client_hostname, client_port);
        echo(connfd);
        Close(connfd);
    }
    exit(0);
}

