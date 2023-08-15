cmake_minimum_required(VERSION 3.5)

# Set the project name
project (linkos)

set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

find_package(Boost REQUIRED COMPONENTS filesystem system)

# check if boost was found
if(Boost_FOUND)
    message ("boost found")
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

include_directories(${Boost_INCLUDE_DIRS})

add_executable(linkos main.cpp so_adater.cpp test_demo.cpp)

target_link_libraries(linkos
${Boost_LIBRARIES}
pthread
dl)


add_library(test_plugin SHARED
    test_demo.cpp
)

target_link_libraries(test_plugin
    pthread
    glog
    boost_system
    ${OpenCV_LIBS}
)

INSTALL(TARGETS linkos 
RUNTIME DESTINATION /usr/local/bin
)
