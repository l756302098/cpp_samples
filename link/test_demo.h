#ifndef  __TEST_DEMO_H_
#define  __TEST_DEMO_H_
#include <iostream>
#include <string>
using namespace std;

class ShowWraper
{
public:
  std::string mTag = "[ShowWrapper]";
public:
  ShowWraper(/* args */);
  ~ShowWraper();
  void DisplayByNum(int num);
  void Display(const char * data);
};

extern "C" ShowWraper* createShowWraper(void);
extern "C" void destroyShowWraper();

#endif
