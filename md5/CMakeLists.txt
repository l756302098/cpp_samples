cmake_minimum_required(VERSION 3.5)

# Set the project name
project (md5_samples)
# coverage option
# OPTION (ENABLE_COVERAGE "Use gcov" OFF)
# MESSAGE(STATUS ENABLE_COVERAGE=${ENABLE_COVERAGE})
# IF(ENABLE_COVERAGE)
#     SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
#     SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
#     # 其中 -fprofile-arcs 用来生成 gcno 文件； -ftest-coverage 用来在统计时生成 gcda 文件
#     SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage") 
# ENDIF()
find_package(Boost REQUIRED COMPONENTS filesystem system)

# check if boost was found
if(Boost_FOUND)
    message ("boost found")
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

include_directories(${Boost_INCLUDE_DIRS})
add_executable(md5_samples main.cpp)

target_link_libraries(md5_samples ${Boost_LIBRARIES} pthread)
