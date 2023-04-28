cmake_minimum_required(VERSION 3.5)

# Set the project name
project (uvc_samples)

find_package(OpenCV 3.4 REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
#    /usr/local/include/libuvc/libuvc.h
)

add_executable(uvc_samples main.cpp)

target_link_libraries(uvc_samples
pthread 
${OpenCV_LIBS}
uvc
)