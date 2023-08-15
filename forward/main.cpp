#include <iostream>
#include <dlfcn.h>
#include <errno.h>
#include <utility>      // std::forward
#include <iostream>     // std::cout

void overload(const int& x)
{
  std::cout << "[lvalue] " << x << std::endl;
}

void overload(int&& x)
{
  std::cout << "[rvalue] " << x << std::endl;
}

template <typename T>
void fn(T&& a){
  overload(a);
  overload(std::forward<T>(a));
}

struct Table
{
  int a;
};

void mod_table(Table &t){
    t.a++;
}

void increase(int &v){
    v++;
}

int main() 
{
  int a = 1;
  fn(a);

  fn(2);

  // error
  // double s = 1.3;
  // increase(s);
  // std::cout << "s:" << s << std::endl;

  Table table;
  mod_table(table);
  std::cout << "table value:" << table.a << std::endl;

  return 0;
}