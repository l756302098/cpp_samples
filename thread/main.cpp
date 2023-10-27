// condition_variable::wait_for example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <chrono>             // std::chrono::seconds
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable, std::cv_status
#include <unistd.h>

std::unique_ptr<std::thread> checkThread;
bool checking;

int main ()
{
  std::cout << "main start \n";
  checking = true;
  //check battery
  checkThread.reset(new std::thread([](){
      std::cout << "start thread \n";
      while (checking)
      {
        std::cout << "loop... \n";
        usleep(1e6);
      }
  }));
  checkThread->detach();

  usleep(1e6);
  checking = false;
  checkThread.reset();
  std::cout << "exit... \n";

  return 0;
}