/*
 * adder.c - a minimal CGI program that adds two numbers together
 */
/* $begin adder */
#include "csapp.h"
#include <stdio.h>
#include <string.h>

char *replace(char *st, char *orig, char *repl) {
  static char buffer[4096];
  char *ch;
  if (!(ch = strstr(st, orig)))
     return st;
    strncpy(buffer, st, ch-st);  
    buffer[ch-st] = 0;
    sprintf(buffer+(ch-st), "%s%s", repl, ch+strlen(orig));
    return buffer;
}



int main(void) {
  char *buf, *p;
  char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
  int n1=0, n2=0;

  // 두 정수 추출
  if((buf=getenv("QUERY_STRING")) != NULL){
    p = strchr(buf,'&');
    *p = '\0';
    // strcpy(arg1, buf);
    // strcpy(arg2, p+1);
    strcpy(arg1, replace(buf,"n1=",""));
    strcpy(arg2, replace(p+1,"n2=",""));
    n1 = atoi(arg1);
    n2 = atoi(arg2);
  }

  // 응답 바디 만들기
  sprintf(content, "QUERY_STRING=%s", buf);
  sprintf(content, "Welcome to add.com: ");
  sprintf(content, "%sTHE Internet addition portal. \r\n<p>", content);
  sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>", content,n1,n2,n1+n2);
  sprintf(content, "%sThanks for visiting!\r\n", content);

  // HTTP 응답 만들기
  printf("Connection: close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n\r\n");
  printf("%s", content);
  fflush(stdout);

  exit(0);
}
/* $end adder */
