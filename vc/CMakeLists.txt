cmake_minimum_required(VERSION 3.5)

# Set the project name
project (cv_samples)

find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(OpenCV 3.4 REQUIRED)

# check if boost was found
if(Boost_FOUND)
    message ("boost found")
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

include_directories(
    ${Boost_INCLUDE_DIRS} 
    ${OpenCV_INCLUDE_DIRS}
    )
add_executable(cv_samples main.cpp)

target_link_libraries(cv_samples
${Boost_LIBRARIES}
${OpenCV_LIBS}
pthread rt)
