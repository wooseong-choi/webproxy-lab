#include "csapp.h"

int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;
    
    // 파일이름, 호스트 주소, 포트번호를 인자로 받는다.
    printf("what is argvs %s %s %s \n" , argv[0],argv[1],argv[2]);
    // 전달받은 인자가 하나라도 빈다면 종료
    if(argc != 3){
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];
    
    // 소켓 열고 커넥트
    clientfd = Open_clientfd(host, port);
    // Rio 버퍼와 파일fd 연결
    Rio_readinitb(&rio, clientfd);
    // 표준입력으로 파일 읽어 buf 에 저장
    while (Fgets(buf, MAXLINE, stdin) != NULL){
        // buf에서 바이트를 읽어 clientfd에 쓰기
        // 서버에 보내기 위해 fd에 씀
        // echo에 버퍼에 들어있는걸 전송
        // w. echo의 w- 실행
        Rio_writen(clientfd ,buf, strlen(buf));

        // a-. 서버가 rio에 echo줄을 쓰면 rio를 읽어 buf에 쓰기
        Rio_readlineb(&rio, buf, MAXLINE);
        // buf에 받은 값을 표준출력으로 출력
        Fputs(buf, stdout);
    }

    // 클라이언트 fd 닫기
    Close(clientfd);
    // 클라이언트 종료
    exit(0);
}
