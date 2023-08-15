#include <iostream>
#include <dlfcn.h>
#include <errno.h>
#include "so_adater.h"

int main() 
{
  class testSoAdater *mTest_Demo = new testSoAdater();
  const char * data = "this is a demo so test!";
  mTest_Demo->setShowWraper();
  mTest_Demo->soDisplay(data);
  mTest_Demo->soDisplayByNum(10);
  return 0;
}