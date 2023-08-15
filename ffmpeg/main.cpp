
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

#define INBUF_SIZE 4096

static void pgm_save(unsigned char *buf, int wrap, int xsize, int ysize,
                     char *filename)
{
    FILE *f;
    int i;

    f = fopen(filename,"wb");
    fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);
    for (i = 0; i < ysize; i++)
        fwrite(buf + i * wrap, 1, xsize, f);
    fclose(f);
}

static void decode(AVCodecContext *dec_ctx, AVFrame *frame, AVPacket *pkt,
                   const char *filename)
{
    char buf[1024];
    int ret;

    ret = avcodec_send_packet(dec_ctx, pkt);
    if (ret < 0) {
        fprintf(stderr, "Error sending a packet for decoding\n");
        exit(1);
    }

    while (ret >= 0) {
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret == AVERROR(EAGAIN))
        {
            fprintf(stderr, "Error during decoding 0\n");
            continue;
        }
        else if(ret == AVERROR_EOF)
        {
            fprintf(stderr, "Error during decoding 1\n");
            return;
        }
        else if (ret < 0) {
            fprintf(stderr, "Error during decoding\n");
            exit(1);
        }

        printf("saving frame %3"PRId64"\n", dec_ctx->frame_num);
        fflush(stdout);

        /* the picture is allocated by the decoder. no need to
           free it */
        snprintf(buf, sizeof(buf), "%s-%"PRId64, filename, dec_ctx->frame_num);
        pgm_save(frame->data[0], frame->linesize[0],
                 frame->width, frame->height, buf);
    }
}

int main(int argc, char **argv) {
    AVFormatContext *fmtCtx = NULL; 
    AVFrame *frame;   
    AVPacket *packet; 
    AVInputFormat *inputFmt;
    AVFormatContext *ifmtCtx = NULL;
    FILE *fp; 
    int ret;

    avdevice_register_all();
    avformat_network_init();


    const AVCodec *codec;
    AVCodecParserContext *parser;
    AVCodecContext *c= NULL;
    //get coder
    codec = avcodec_find_decoder(AV_CODEC_ID_MJPEG);
    if (!codec) {
        fprintf(stderr, "Codec not found\n");
        exit(1);
    }

    parser = av_parser_init(codec->id);
    if (!parser) {
        fprintf(stderr, "parser not found\n");
        exit(1);
    }

    c = avcodec_alloc_context3(codec);
    if (!c) {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }

    /* open it */
    if (avcodec_open2(c, codec, NULL) < 0) {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }

    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }

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

    do
    {
        packet = (AVPacket *)av_malloc(sizeof(AVPacket));    
        av_read_frame(fmtCtx, packet); 
        printf("data length = %d\n",packet->size);   
    
        decode(c, frame, packet, out_file);
        
        av_free(packet);  
    } while (1);
    
    avformat_close_input(&fmtCtx);
 
    return 0;
}
 
