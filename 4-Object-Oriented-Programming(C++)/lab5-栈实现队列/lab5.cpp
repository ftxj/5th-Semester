#include "U201514593_5.h"

class QUEUE{
  STACK s1, s2;
public:
  QUEUE(int m); //每个栈最多m个元素，要求实现的队列最多能入2m个元素
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

QUEUE::QUEUE(int m) : s1(STACK(m)), s2(STACK(m)){}
QUEUE::QUEUE(const QUEUE&s) : s1(s.s1), s2(s.s2){}
QUEUE::operator int()const{
  return (int)s1 + (int)s2;
}
int QUEUE::full()const{
  return (int)s2 == 0? 0 : (s1.size() == (int)s1); 
}
int QUEUE::operator[] (int x)const{
  return (int)s2 > x? s2[(int)s2 - 1 - x] : s1[x - (int)s2]; 
}
QUEUE& QUEUE::operator <<(int e){
  int i;
  if((int)s1 == s1.size()){
    int size = (int)s1;
    for(int j = 0; j < size; ++j){
      s1 >> i;
      s2 << i;
    }
  }
  s1 << e;
  return *this;
}
QUEUE& QUEUE::operator >> (int &e){
  if((int)s2 == 0){
    int size = (int)s1;
    for(int i = 0; i < size; ++i){
      s1 >> e;
      s2 << e;
    }
  }
  s2 >> e;
  return *this;
}
QUEUE& QUEUE::operator=(const QUEUE&s){
  s1 = s.s1;
  s2 = s.s2;
}

void QUEUE::print( ) const{
  for(int i = 0; i <(int)s2; ++i){
    std::cout << s2[(int)s2 - i - 1] << "  ";
  }
  s1.print();
}
QUEUE::~QUEUE() {}

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
