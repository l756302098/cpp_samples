cmake_minimum_required(VERSION 3.5)

# Set the project name
project (compress_samples)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(compress_samples main.cpp)

target_link_libraries(compress_samples
pthread)
