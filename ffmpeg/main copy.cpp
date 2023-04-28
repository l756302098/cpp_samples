
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#ifdef __cplusplus
extern "C"
{
#endif
    #include "libavdevice/avdevice.h"
    #include "libavutil/pixfmt.h"
    #include "libswscale/swscale.h"
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libavutil/time.h"
    #include "libswresample/swresample.h"
#ifdef __cplusplus
}
#endif


char* input_name= "video4linux2";
char* file_name = "/dev/video0";
char* out_file  = "test.jpeg";

int main(int argc, char **argv) {
    AVFormatContext *fmtCtx = NULL;    
    AVPacket *packet; 
    AVInputFormat *inputFmt;
    AVFormatContext *ifmtCtx = NULL;
    FILE *fp; 
    int ret;

    avdevice_register_all();
    avformat_network_init();
    ifmtCtx = avformat_alloc_context();
    ifmtCtx->probesize = 20000000;
    ifmtCtx->max_analyze_duration = 2000;

    AVDictionary* options = NULL;
    av_dict_set(&options, "fflags", "nobuffer", 0);
    av_dict_set(&options, "max_delay", "100000", 0);
    av_dict_set(&options, "framerate", "30", 0);
    av_dict_set(&options, "input_format", "mjpeg", 0);
    av_dict_set(&options, "video_size", "1920x1080", 0);  
 
    if (avformat_open_input ( &fmtCtx, file_name, 0, &options) < 0){
        printf("can not open_input_file\n");
        return -1; 
    }
    /* print device information*/
    av_dump_format(fmtCtx, 0, file_name, 0);

    packet = (AVPacket *)av_malloc(sizeof(AVPacket));    
    av_read_frame(fmtCtx, packet); 
    printf("data length = %d\n",packet->size);   
 
    fp = fopen(out_file, "wb");    
    if (fp < 0)    {        
        printf("open frame data file failed\n");        
        return -1;
    }    
    
    fwrite(packet->data, 1, packet->size, fp);    
 
    fclose(fp);
    av_free(packet);  
    avformat_close_input(&fmtCtx);
 
    return 0;
}
 
