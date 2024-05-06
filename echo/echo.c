#include "csapp.h"

void echo(int connfd){
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    // rio에 connfd 연결
    Rio_readinitb(&rio, connfd);
    // 클라가 rio에 써준거 읽기
    // w-.
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
        printf("server received %d bytes\n", (int)n);
        // a. 읽은거 그대로 전송( 써주기 ) client의 a- 실행
        Rio_writen(connfd, buf, n);
        if((int)n == 1){
            printf("no input connection close\n");
            break;
        }
    }
}