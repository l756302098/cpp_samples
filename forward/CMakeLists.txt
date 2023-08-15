cmake_minimum_required(VERSION 3.5)

# Set the project name
project (forward)

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

add_executable(forward main.cpp)

target_link_libraries(forward
${Boost_LIBRARIES}
pthread
dl)
