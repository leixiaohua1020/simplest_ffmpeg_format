#! /bin/sh
#最简单的基于FFmpeg的视音频分离器（简化版）----命令行编译
#Simplest FFmpeg Demuxer Simple----Compile in Shell 
#
#雷霄骅 Lei Xiaohua
#leixiaohua1020@126.com
#中国传媒大学/数字电视技术
#Communication University of China / Digital TV Technology
#http://blog.csdn.net/leixiaohua1020
#
#compile
gcc simplest_ffmpeg_demuxer_simple.cpp -g -o simplest_ffmpeg_demuxer_simple.out -lavformat -lavcodec -lavutil
