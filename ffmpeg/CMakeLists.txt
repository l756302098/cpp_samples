cmake_minimum_required(VERSION 3.5)

# Set the project name
project (ff_samples)

find_package(OpenCV 3.4 REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    /home/li/ffmpeg/
    #/home/li/ffmpeg-master/include
)

add_executable(ff_samples main.cpp)

target_link_libraries(ff_samples
pthread 
${OpenCV_LIBS}
/home/li/ffmpeg/libavcodec.so
/home/li/ffmpeg/libavdevice.so
/home/li/ffmpeg/libavfilter.so
/home/li/ffmpeg/libavformat.so
/home/li/ffmpeg/libavutil.so
/home/li/ffmpeg/libswresample.so
/home/li/ffmpeg/libswscale.so
)