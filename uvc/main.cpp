#include "libuvc/libuvc.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "uvc.hpp"


int main(int argc, char **argv) {
  
  uvc::camera camera;
  camera.Start();
  sleep(10);
  camera.Stop();
  return 0;
}
 
