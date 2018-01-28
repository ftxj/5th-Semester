#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <iterator>
class QUEUE{
  int  *const  elems;	//申请内存用于存放队列的元素
  const  int   max;	//elems能存放的最大元素个数
  int   head, tail;		//队列头和尾，队列空时head=tail;初始时head=tail=0
public:
  QUEUE(int m);		//初始化循环队列：elems有m个元素
  QUEUE(const QUEUE&s); 			//用队列s拷贝初始化队列
  virtual operator int ( ) const;			//返回队列的实际元素个数
  virtual int full ( ) const;		       //返回队列是否已满，满返回1，否则返回0
  virtual int operator[ ](int x)const;   //取下标为x的元素,第1个元素下标为0
  virtual QUEUE& operator<<(int e); 	//将e入队列,并返回队列
  virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
  virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
  virtual void print( ) const;			//打印队列
  virtual ~QUEUE( );					//销毁队列
};
QUEUE::QUEUE(int m) : elems(new int [m]), max(m), head(0), tail(0){}
QUEUE::QUEUE(const QUEUE&s):elems(new int [s.max]), max(s.max), head(s.head), tail(s.tail){
  for(int i = 0; i < max; ++i){
    elems[i] = s[i];
  }
}
QUEUE::operator int()const{
  return head <= tail? tail - head : max - head + tail;
}
int QUEUE::full() const{
  return (tail + 1) % max == head;
}
int QUEUE::operator[] (int x)const{
  return elems[x];
}

QUEUE& QUEUE::operator << (int e){
  elems[tail] = e;
  tail = (tail + 1) % max;
}
QUEUE& QUEUE::operator >> (int &e){
  head = (head + 1) % max;
  e = elems[head];
}
QUEUE& QUEUE::operator=(const QUEUE&s){
  delete [] elems;
  const_cast<int &>(max) = (s.max > max)? s.max : max;
  const_cast<int *&>(elems) = new int [max];  
  tail = s.tail;
  head = s.head;
  for(int i = 0; i < s.max; ++i){
    elems[i] = s[i];
  }
  return *this;
}

void QUEUE::print() const{
  for(int i = head; i != tail; i = (i + 1) % max){
    std::cout << elems[i] << "  ";
  }
}

QUEUE::~QUEUE(){
  delete [] elems;
  const_cast<int &>(max) = 0;
  head = tail = 0;
}
bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}
int main(int argc, char* argv[]){
  std::vector<std::string> v(argv, argv + argc);
  QUEUE* s = nullptr;  
  for(int i = 1; i < v.size(); ++i){
    if(v[i] == "-S"){
      std::cout << "S  " << v[i + 1] << "  ";
      s = new QUEUE(std::stoi(v[++i]));
    }
    else if(v[i] == "-I"){
      std::cout << "I  ";
      while(i + 1 < v.size() && is_digits(v[i + 1])){
        if(s->full()){
            std::cout << "E  ";
            return 0;
        }
        *s << std::stoi(v[++i]); 
      }
      s->print();
    }
    else if(v[i] == "-O"){
      int x;
      std::cout << "O  ";
      if(i + 1 < v.size() && is_digits(v[i + 1])){
        int sizeSub = std::stoi(v[i + 1]);
        if(sizeSub > (int)*s){
          std::cout << "E";
          return 0;
        }
        for(int j = 0; j < sizeSub; ++j)
          *s >> x; 
      }
      s->print();
    }
    else if(v[i] == "-A"){
      std::cout << "A  ";
      QUEUE *t = new QUEUE(std::stoi(v[++i]));
      *t = *s;
      s->~QUEUE();
      s = t;
      s->print();
    }
    else if(v[i] == "-C"){
      std::cout << "C  ";
      QUEUE *t = new QUEUE(*s);
      s = t;
      s->print();
    }
    else if(v[i] == "-G"){
      std::cout << "G  ";
      if(i + 1 > v.size() || std::stoi(v[++i]) >= (int)*s){
        std::cout << "E";
        return 0;
      }
      std::cout << (*s)[std::stoi(v[i])] << "  ";
    }
    else if(v[i] == "-N"){
      std::cout << "N  " << (int)*s << "  ";
    }
  }
  return 0;
}
