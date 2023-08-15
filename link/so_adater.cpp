#include "so_adater.h"
#include <iostream>
#include <string>

testSoAdater::testSoAdater() {
  if (isInit) {
    std::cout << mTag << "so have load" << std::endl;
    return;
  }

  if (!libHandle) {
    //确定打开方式，调用dlopen打开so的句柄，之后拿到句柄做下一步操作
    libHandle = dlopen("libtest_plugin.so",RTLD_NOW);
    if (libHandle == NULL) {
      std::cout << mTag << "unable to dlopen libtest_plugin." << std::endl;
      return;
    }
  }

  typedef ShowWraper* (*create)(void);
  //定义相同的接口，打开So并获取对象。
  testcreateShowWraper = (create)dlsym(libHandle, "createShowWraper");
  if (testcreateShowWraper == NULL) {
    std::cout << mTag << "unable to find createShowWraper" << std::endl << dlerror();
    return;
  }

  typedef void (*destroy)(void);
  //定义相同的接口，打开So并拿到释放对象接口。
  testdestroyShowWraper = (destroy)dlsym(libHandle, "destroyShowWraper");
  if (testdestroyShowWraper == NULL) {
    std::cout << mTag << "unable to find destroyShowWraper" << std::endl;
    return;
  }
  isInit = true;
}

testSoAdater::~testSoAdater() {
  if (libHandle) {
    //关闭打开的SO。
    dlclose(libHandle);
    libHandle = NULL;
  }
}

void testSoAdater::setShowWraper() {
  std::cout << __FUNCTION__ << "\t" << mShowWraper << std::endl;
  mShowWraper = testcreateShowWraper();
  std::cout << __FUNCTION__<< "\t"  << mShowWraper << std::endl;
}

//传Char数据，并打印
void testSoAdater::soDisplay(const char * data) {
  if (mShowWraper) {
    mShowWraper->Display(data);
  }
}

//传BOOL数据，并打印
void testSoAdater::soDisplayByNum(int num) {
  if (mShowWraper) {
    mShowWraper->DisplayByNum(num);
  }
}
