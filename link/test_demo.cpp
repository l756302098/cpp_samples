#include "test_demo.h"

static  ShowWraper *g_ShowWraper = NULL;

ShowWraper::ShowWraper() {
  std::cout << mTag << __FUNCTION__ << std::endl;
}
ShowWraper::~ShowWraper() {
  std::cout << mTag << __FUNCTION__ << std::endl;
}

void ShowWraper::Display(const char * data ) {
  std::cout << mTag << __FUNCTION__ << std::endl;
  std::cout << mTag << data << std::endl;
}
void ShowWraper::DisplayByNum(int num) {
  for ( int i = 0;i < num; i++) {
    std::cout << mTag << __FUNCTION__ << std::endl;
  }
}

ShowWraper* createShowWraper(void) {
  std::cout << __FUNCTION__ << std::endl;
  if (g_ShowWraper == NULL) {
    g_ShowWraper = new ShowWraper();
  }
  return g_ShowWraper;
}

void destroyShowWraper(void) {
  std::cout << __FUNCTION__ << std::endl;
  if (!g_ShowWraper) {
    delete g_ShowWraper;
    g_ShowWraper = NULL;
  }
}
