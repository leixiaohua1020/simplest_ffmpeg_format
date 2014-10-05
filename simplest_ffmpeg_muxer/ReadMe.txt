最简单的基于FFmpeg的视音频复用器
Simplest FFmpeg Muxer

雷霄骅 Lei Xiaohua
leixiaohua1020@126.com
中国传媒大学/数字电视技术
Communication University of China / Digital TV Technology
http://blog.csdn.net/leixiaohua1020

本程序可以将视频码流和音频码流打包到一种封装格式中。
程序中将AAC编码的音频码流和H.264编码的视频码流打包成
MPEG2TS封装格式的文件。
需要注意的是本程序并不改变视音频的编码格式。

This software mux a video bitstream and a audio bitstream 
together into a file.
In this example, it mux a H.264 bitstream (in MPEG2TS) and 
a AAC bitstream file together into MP4 format file.