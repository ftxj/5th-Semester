#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <vector>
#include <string>
#include <iterator>
class STACK{
public:
  STACK(int m);		//初始化栈：最多m个元素
  STACK(const STACK&s); //用栈s拷贝初始化栈
  int  size ( ) const;		//返回栈的最大元素个数max
  int  howMany ( ) const;	//返回栈的实际元素个数pos
  int  getelem (int x) const;	//取下标x处的栈元素
  STACK& push(int e); 	//将e入栈,并返回栈
  STACK& pop(int &e); 	//出栈到e,并返回栈
  STACK& assign(const STACK&s); //赋s给栈,并返回被赋值的栈
  void print() const;		//打印栈
  ~STACK( );				//销毁栈
private:
  int  *const  elems;	//申请内存用于存放栈的元素
  const  int   max;	//栈能存放的最大元素个数
  int   pos;			//栈实际已有元素个数，栈空时pos=0;
};

STACK::STACK(int m) : elems(new int [m]), max(m), pos(0) {}
STACK::STACK(const STACK& s) :elems(new int [s.size()]), max(s.size()), pos(s.howMany()){
  for(int i = 0; i < s.howMany(); ++i){
    elems[i] = s.getelem(i);
  }
}
int STACK::size() const {
  return max;
}
int STACK::howMany() const{
  return pos;
}
int STACK::getelem(int x) const{
  if(x < pos)
    return elems[x];
  return -1;
}
STACK& STACK::push(int e){
  elems[pos++] = e;
  return *this;
}
STACK& STACK::pop(int &e){
  e = elems[--pos];
  return *this;
}
STACK& STACK::assign(const STACK& s){
  delete elems;
  const_cast<int &>(max) = s.size();
  const_cast<int *&>(elems) = new int [max];  
  for(int i = 0; i < s.howMany(); ++i){
    push(s.getelem(i));
  }
  return *this;
}
void STACK::print() const{
  for(int i = 0; i < howMany(); ++i){
    std::cout << getelem(i) << "  ";
  }
}
STACK::~STACK(){
  delete elems;
  const_cast<int &>(max) = 0; 
  const_cast<int *&>(elems) = nullptr;
  pos = 0;
}
bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}
int main(int argc, char* argv[]){
  std::vector<std::string> v(argv, argv + argc);
  STACK* s = nullptr;  
  for(int i = 1; i < v.size(); ++i){
    if(v[i] == "-S"){
      std::cout << "S  " << v[i + 1] << "  ";
      s = new STACK(std::stoi(v[++i]));
    }
    else if(v[i] == "-I"){
      std::cout << "I  ";
      while(i + 1 < v.size() && is_digits(v[i + 1])){
        if(s->howMany() >= s->size()){
            std::cout << "E  ";
            return 0;
        }
        s->push(std::stoi(v[++i])); 
      }
      s->print();
    }
    else if(v[i] == "-O"){
      int x;
      std::cout << "O  ";
      if(i + 1 < v.size() && is_digits(v[i + 1])){
        int sizeSub = std::stoi(v[i + 1]);
        if(sizeSub > s->howMany()){
          std::cout << "E";
          return 0;
        }
        for(int j = 0; j < sizeSub; ++j)
          s->pop(x); 
      }
      s->print();
    }
    else if(v[i] == "-A"){
      std::cout << "A  ";
      STACK *t = new STACK(std::stoi(v[++i]));
      t->assign(*s);
      s->~STACK();
      s = t;
      s->print();
    }
    else if(v[i] == "-C"){
      std::cout << "C  ";
      STACK *t = new STACK(*s);
      s->~STACK();
      s = t;
      s->print();
    }
    else if(v[i] == "-G"){
      std::cout << "G  ";
      if(i + 1 > v.size() || std::stoi(v[++i]) >= s->howMany()){
        std::cout << "E";
        return 0;
      }
      std::cout << s->getelem(std::stoi(v[i])) << "  ";
    }
    else if(v[i] == "-N"){
      std::cout << "N  " << s->howMany() << "  ";
    }
  }
  return 0;
}

