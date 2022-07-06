cmake_minimum_required(VERSION 3.5)

# Set the project name
project (cxx_samples)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DMY_DEBUG")

add_executable(cxx_samples main.cpp)

target_link_libraries(cxx_samples
pthread)