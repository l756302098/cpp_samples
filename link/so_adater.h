#ifndef  __SO_ADATER_H_
#define  __SO_ADATER_H_
#include <iostream>
#include "test_demo.h"
#include <dlfcn.h>
#include <errno.h>

class testSoAdater{
public:
  std::string mTag = "[testSoAdater]" ;
  testSoAdater();
  ~testSoAdater();

private:
  bool  isInit = false;
  void* libHandle = NULL;
  ShowWraper* (*testcreateShowWraper)(void) {NULL};
  void (*testdestroyShowWraper)(void) {NULL};

public:
  void setShowWraper();
  void soDisplay(const char *data);
  void soDisplayByNum(int num);
public:
  class ShowWraper *mShowWraper = NULL;
};

#endif
