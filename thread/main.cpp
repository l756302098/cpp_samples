#include <iostream>
#include <thread>
#include <exception>
#include <unistd.h>
void threadFunction() {
    
    try {
        std::cout << "子线程正在运行..." << std::endl;
        //throw std::runtime_error("子线程崩溃");
        
        int *a;
        *a = 10;
        std::cout << "子线程结束" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "捕获异常：" << e.what() << std::endl;
        // 进行适当的清理工作
    }
}

int main() {
  std::thread t(threadFunction);

  // 分离子线程
  t.detach();

  sleep(5);
  // 主线程正常退出
  std::cout << "主线程结束" << std::endl;

  return 0;
}