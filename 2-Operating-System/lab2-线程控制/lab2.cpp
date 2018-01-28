#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>

int a = 0, semR, semW;

union semun{
  int val;
  struct semid_ds* buf;
  unsigned short *array;
};

void P(int semid, int index){
  struct sembuf sem;
  sem.sem_num = index;
  sem.sem_op = -1;
  sem.sem_flg = 0;
  semop(semid, &sem, 1);
  return;
}

void V(int semid, int index){
  struct sembuf sem;
  sem.sem_num = index;
  sem.sem_op = 1;
  sem.sem_flg = 0;
  semop(semid, &sem, 1);
  return;
}

void* thread_fun_add(void *arg){
  int temp = 0;
  while(temp < 101){
    temp++;
    P(semW, 0);
    a += temp;
    V(semR, 0);
  }
  return ((void*)0);
}

void* thread_fun_print(void *arg){
  int temp = 0;
  while(temp < 101){
    printf("a is %d, times = %d\n", a, temp);
    V(semW, 0);
    P(semR, 0);
    temp+=1;
  }
  return ((void*)0);
}

int main(){
  void* tret = NULL;
  void* tret2 = NULL;
  pthread_t thid_R, thid_W;
  semun initSemaphoreStu;
  initSemaphoreStu.val = 0;
  semW = semget(IPC_PRIVATE, 1, IPC_CREAT);
  semctl(semW, 0,SETVAL,  initSemaphoreStu);

  initSemaphoreStu.val = 0;
  semR = semget(IPC_PRIVATE, 1, IPC_CREAT);
  semctl(semR, 0, SETVAL, initSemaphoreStu);

  pthread_create(&thid_R, NULL, thread_fun_add, NULL);
  pthread_create(&thid_W, NULL, thread_fun_print, NULL);
  pthread_join(thid_R, &tret);
  pthread_join(thid_W, &tret2);
  return 0;
}
