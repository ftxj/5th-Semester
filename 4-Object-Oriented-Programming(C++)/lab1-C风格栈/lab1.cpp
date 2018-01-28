#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
struct STACK{
  int  *elems;	//申请内存用于存放栈的元素
  int   max;	//栈能存放的最大元素个数
  int   pos;	//栈实际已有元素个数，栈空时pos=0;
};

void initSTACK(STACK *const p, int m){//初始化p指向的栈：最多m个元素
  p->max = m;
  p->pos = 0;
  p->elems = (int *)malloc(sizeof(int) * m);
  return;
}

void initSTACK(STACK *const p, const STACK&s){//用栈s初始化p指向的栈
  p->elems = (int *)malloc(sizeof(int) * s.max);
  p->max = s.max;
  int i = 0;
  for(; i < s.pos; ++i){
    p->elems[i] = s.elems[i];
  }
  p->pos = s.pos;
  return;
}

int size (const STACK *const p){		//返回p指向的栈的最大元素个数max
  return p->max;
}

int howMany (const STACK *const p){	//返回p指向的栈的实际元素个数pos
  return p->pos;
}

int getelem (const STACK *const p, int x){//取下标x处的栈元素
  if(x < p->pos)
    return p->elems[x];
  else
    return -1;
}

STACK *const push(STACK *const p, int e){//将e入栈，并返回p
  if(p->pos + 1 <= p->max){
    p->pos += 1;
    p->elems[p->pos - 1] = e;
    return p;
  }
  else{
    STACK* tempStack = (STACK *)malloc(sizeof(STACK));
    initSTACK(tempStack, *p);
    p->elems = (int *)malloc(sizeof(int) * (p->max == 0? 1 : (p->max * 2)));
    int i = 0, oldsize = howMany(tempStack);
    for(; i < oldsize; ++i){
      p->elems[i] = getelem(tempStack, i);
    }
    free(tempStack->elems);
    free(tempStack);
    return p;
  }
}

STACK *const pop(STACK *const p, int &e){ 	//出栈到e，并返回p
  if(p->pos == 0){
    return 0;
  }
  e = getelem(p, p->pos - 1);
  p->pos -= 1;
  return p;
}

STACK *const assign(STACK*const p, const STACK&s){ //赋s给p指的栈,并返回p
  free(p->elems);
  p->elems = (int *)malloc(sizeof(s.max));
  p->max = s.max;
  p->pos = s.pos;
  int i = 0;
  for(; i < s.pos; ++i){
    p->elems[i] = s.elems[i];
  }
  return p;
}
void print(const STACK*const p){			//打印p指向的栈
  int i = 0;
  for(; i < p->pos; ++i){
    printf("%d  ",p->elems[i]);
  }
}
void destroySTACK(STACK*const p){		//销毁p指向的栈
  free(p->elems);
  p->max = 0;
  p->pos = 0;
}

int main(int argc, char* argv[]){
  int i = 1;
  STACK testStack;
  for(;i < argc; ++i){
    if(strcmp(argv[i], "-S") == 0){
      ++i;
      int size = atoi(argv[i]);
      initSTACK(&testStack, size);
      printf("S  %d  ",testStack.max);
    }
    else if(strcmp(argv[i], "-I") == 0){
      ++i;
      printf("I  ");
      while(i < argc && isdigit(argv[i][0])){
        if(testStack.max == testStack.pos){
          printf("E");
          return 0;
        }
        push(&testStack, atoi(argv[i]));
        ++i;
      }
      print(&testStack);
      --i;
    }
    else if(strcmp(argv[i], "-O") == 0){
      ++i;
      int popSize = atoi(argv[i]);
      int tempValue = 0;
      int j = 0;
      printf("O  ");
      for(; j < popSize; ++j){
        if(testStack.pos == 0){
          printf("E");
          return 0;
        }
        pop(&testStack, tempValue);
      }
      print(&testStack);
    }
    else if(strcmp(argv[i], "-A") == 0){
      printf("A  ");
      i++;
      int size = atoi(argv[i]);
      STACK newStack;
      initSTACK(&newStack, size);
      assign(&newStack, testStack);
      destroySTACK(&testStack);
      initSTACK(&testStack, newStack);
      destroySTACK(&newStack);
      print(&testStack);
    }
    else if(strcmp(argv[i], "-C") == 0){
      STACK newStack;
      initSTACK(&newStack, testStack);
      destroySTACK(&testStack);
      initSTACK(&testStack, newStack);
      destroySTACK(&newStack);
      printf("C  ");
      print(&testStack);
    }
    else if(strcmp(argv[i], "-N") == 0){
      printf("N  %d  ", howMany(&testStack));
    }
    else if(strcmp(argv[i], "-G") == 0){
      i++;
      int th = atoi(argv[i]);
      if(th >= testStack.pos){
        printf("G  E");
        return 0;
      }
      printf("G  %d  ", getelem(&testStack,th));
    }
  }
  return 0;
}