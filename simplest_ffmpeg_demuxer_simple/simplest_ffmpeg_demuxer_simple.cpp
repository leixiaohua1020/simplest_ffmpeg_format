/**
 * 最简单的基于FFmpeg的视音频分离器（简化版）
 * Simplest FFmpeg Demuxer Simple
 *
 * 雷霄骅 Lei Xiaohua
 * leixiaohua1020@126.com
 * 中国传媒大学/数字电视技术
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 * 本程序可以将封装格式中的视频码流数据和音频码流数据分离出来。
 * 在该例子中， 将MPEG2TS的文件分离得到H.264视频码流文件和MP3
 * 音频码流文件。
 *
 * 注意：
 * 这个是简化版的视音频分离器。与原版的不同在于，没有初始化输出
 * 视频流和音频流的AVFormatContext。而是直接将解码后的得到的
 * AVPacket中的的数据通过fwrite()写入文件。这样做的好处是流程比
 * 较简单。坏处是对一些格式的视音频码流是不适用的，比如说
 * FLV/MP4/MKV等格式中的AAC码流（上述封装格式中的AAC的AVPacket中
 * 的数据缺失了7字节的ADTS文件头）。
 * 
 *
 * This software split a media file (in Container such as 
 * MKV, FLV, AVI...) to video and audio bitstream.
 * In this example, it demux a MPEG2TS file to H.264 bitstream
 * and MP3 bitstream.
 * Note:
 * This is a simple version of "Simplest FFmpeg Demuxer". It is 
 * more simple because it doesn't init Output Video/Audio stream's
 * AVFormatContext. It write AVPacket's data to files directly.
 * The advantages of this method is simple. The disadvantages of
 * this method is it's not suitable for some kind of bitstreams. For
 * example, AAC bitstream in FLV/MP4/MKV Container Format(data in
 * AVPacket lack of 7 bytes of ADTS header).
 *
 */

#include <stdio.h>

extern "C"
{
#include "libavformat/avformat.h"
};
//'1': Use H.264 Bitstream Filter 
#define USE_H264BSF 1

int main(int argc, char* argv[])
{
	AVFormatContext *ifmt_ctx = NULL;
	AVPacket pkt;
	int ret, i;
	int videoindex=-1,audioindex=-1;
	char *in_filename  = "cuc_ieschool.flv";//输入文件名（Input file URL）
	char *out_filename_v = "cuc_ieschool.h264";//输出文件名（Output file URL）
	char *out_filename_a = "cuc_ieschool.mp3";

	av_register_all();
	//输入（Input）
	if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0)) < 0) {
		printf( "Could not open input file.");
		return -1;
	}
	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {
		printf( "Failed to retrieve input stream information");
		return -1;
	}

	videoindex=-1;
	for(i=0; i<ifmt_ctx->nb_streams; i++) {
		if(ifmt_ctx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
			videoindex=i;
		}else if(ifmt_ctx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO){
			audioindex=i;
		}
	}
	//Dump Format------------------
	printf("\nInput Video===========================\n");
	av_dump_format(ifmt_ctx, 0, in_filename, 0);
	printf("\n======================================\n");

	FILE *fp_audio=fopen(out_filename_a,"wb+");  
	FILE *fp_video=fopen(out_filename_v,"wb+");  

	/*
	FIX: H.264 in some container format (FLV, MP4, MKV etc.) need 
	"h264_mp4toannexb" bitstream filter (BSF)
	  *Add SPS,PPS in front of IDR frame
	  *Add start code ("0,0,0,1") in front of NALU
	H.264 in some container (MPEG2TS) don't need this BSF.
	*/
#if USE_H264BSF
	AVBitStreamFilterContext* h264bsfc =  av_bitstream_filter_init("h264_mp4toannexb"); 
#endif

	while(av_read_frame(ifmt_ctx, &pkt)>=0){
		if(pkt.stream_index==videoindex){
#if USE_H264BSF
			av_bitstream_filter_filter(h264bsfc, ifmt_ctx->streams[videoindex]->codec, NULL, &pkt.data, &pkt.size, pkt.data, pkt.size, 0);
#endif
			printf("Write Video Packet. size:%d\tpts:%d\n",pkt.size,pkt.pts);
			fwrite(pkt.data,1,pkt.size,fp_video);
		}else if(pkt.stream_index==audioindex){
			/*
			AAC in some container format (FLV, MP4, MKV etc.) need to add 7 Bytes
			ADTS Header in front of AVPacket data manually.
			Other Audio Codec (MP3...) works well.
			*/
			printf("Write Audio Packet. size:%d\tpts:%d\n",pkt.size,pkt.pts);
			fwrite(pkt.data,1,pkt.size,fp_audio);
		}
		av_free_packet(&pkt);
	}

#if USE_H264BSF
	av_bitstream_filter_close(h264bsfc);  
#endif

	fclose(fp_video);
	fclose(fp_audio);

	avformat_close_input(&ifmt_ctx);

	if (ret < 0 && ret != AVERROR_EOF) {
		printf( "Error occurred.\n");
		return -1;
	}
	return 0;
}


