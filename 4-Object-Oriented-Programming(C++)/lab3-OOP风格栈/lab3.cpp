#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <iterator>
class STACK{
public:
  STACK(int m);		//初始化栈：最多存m个元素
  STACK(const STACK&s); 			//用栈s拷贝初始化栈
  virtual int  size ( ) const;			//返回栈的最大元素个数max
  virtual operator int ( ) const;			//返回栈的实际元素个数pos
  virtual int operator[ ] (int x) const;	//取下标x处的栈元素，第1个元素x=0
  virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
  virtual STACK& operator>>(int &e);	//出栈到e,并返回栈
  virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
  virtual void print( ) const;			//打印栈
  virtual ~STACK( );					//销毁栈
private:
  int  *const  elems;	//申请内存用于存放栈的元素
  const  int   max;	//栈能存放的最大元素个数
  int   pos;			//栈实际已有元素个数，栈空时pos=0;
};

STACK::STACK(int m) : elems(new int [m]), max(m), pos(0){}
STACK::STACK(const STACK& s) :elems(new int [s.size()]), max(s.size()), pos((int)s){
  for(int i = 0; i < (int)s; ++i){
    elems[i] = s[i];
  }
}
STACK& STACK::operator =(const STACK& s){
  delete [] elems;
  const_cast<int &>(max) = (s.size() > max)? s.size() : max;
  const_cast<int *&>(elems) = new int [max];  
  pos = (int)s;
  for(int i = 0; i < (int)s; ++i){
    elems[i] = s[i];
  }
  return *this;
}
STACK::~STACK(){
  delete [] elems;
  const_cast<int &>(max) = 0;
  pos = 0;  
}
int STACK::size() const{
  return max;
}
STACK::operator int() const{
  return pos;
}
int STACK::operator [] (int x)const{
  return elems[x];
}
STACK& STACK::operator <<(int e){
  elems[pos++] = e;
  return *this;
}
STACK& STACK::operator>>(int &e){
  e = elems[--pos];
  return *this;
}
void STACK::print()const{
  for(int i = 0; i < pos; ++i){
    std::cout << elems[i] << "  ";
  }
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
        if((int)*s >= s->size()){
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
      STACK *t = new STACK(std::stoi(v[++i]));
      *t = *s;
      s->~STACK();
      s = t;
      s->print();
    }
    else if(v[i] == "-C"){
      std::cout << "C  ";
      STACK *t = new STACK(*s);
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
