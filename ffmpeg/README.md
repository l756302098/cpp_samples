# ffmpeg-samples
ffmpeg-samples

# Install ffmpeg

``` bash
git clone https://github.com/FFmpeg/FFmpeg.git
cd FFmpeg
./configure --disable-x86asm --disable-static --enable-shared \
  --prefix=/home/li/ffmpeg --shlibdir=/home/li/ffmpeg \
  --libdir=/home/li/ffmpeg --incdir=/home/li/ffmpeg
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/li/ffmpeg
```

# Complier

``` bash
mkdir build && cd build
cmake ..
make
```
