#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
typedef void (*signalHandler)(int);

pid_t pid_1, pid_2;

void sigFun_int(int cls){
  kill(pid_1, SIGUSR1);
  kill(pid_2, SIGUSR2);
}
void sigFun_ch1(int cls){
  printf("Child1 has stoped\n");
}
void sigFun_ch2(int cls){
  printf("Child2 has stoped\n");
}

int main(){
  int pipefd[2];
  pipe(pipefd);
  pid_1 = fork();
  if(pid_1 == 0){
    signal(SIGUSR1, sigFun_ch1);
    int count = 0;
    char buf[255];
    close(pipefd[0]);
    while(true){
      count++;
      sprintf(buf, "I send you %d times\n", count);
      write(pipefd[1], buf, strlen(buf) + 1);
      sleep(1);
    }
  }
  else{
    pid_2 = fork();
    if(pid_2 == 0){
      signal(SIGUSR2, sigFun_ch2);
      int recvLen = 0;
      char buf[255];
      close(pipefd[1]);
      while(true){
        recvLen = read(pipefd[0], buf, 255);
        write(STDOUT_FILENO, buf, recvLen);
      }
    }
    else{
      signal(SIGINT, sigFun_int);
      pause();
      close(pipefd[0]);
      close(pipefd[1]);
    }
  }
}
