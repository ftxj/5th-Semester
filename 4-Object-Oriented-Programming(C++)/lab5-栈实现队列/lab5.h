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