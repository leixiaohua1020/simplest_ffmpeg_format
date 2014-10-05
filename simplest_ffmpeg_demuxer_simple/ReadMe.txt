最简单的基于FFmpeg的视音频分离器（简化版）
Simplest FFmpeg Demuxer Simple

雷霄骅 Lei Xiaohua
leixiaohua1020@126.com
中国传媒大学/数字电视技术
Communication University of China / Digital TV Technology
http://blog.csdn.net/leixiaohua1020

本程序可以将封装格式中的视频码流数据和音频码流数据分离出来。
在该例子中， 将MPEG2TS的文件分离得到H.264视频码流文件和MP3
音频码流文件。

注意：
这个是简化版的视音频分离器。与原版的不同在于，没有初始化输出
视频流和音频流的AVFormatContext。而是直接将解码后的得到的
AVPacket中的的数据通过fwrite()写入文件。这样做的好处是流程比
较简单。坏处是对一些格式的视音频码流是不适用的，比如说
FLV/MP4/MKV等格式中的AAC码流（上述封装格式中的AAC的AVPacket中
的数据缺失了7字节的ADTS文件头）。


This software split a media file (in Container such as 
MKV, FLV, AVI...) to video and audio bitstream.
In this example, it demux a MPEG2TS file to H.264 bitstream
and MP3 bitstream.
Note:
This is a simple version of "Simplest FFmpeg Demuxer". It is 
more simple because it doesn't init Output Video/Audio stream's
AVFormatContext. It write AVPacket's data to files directly.
The advantages of this method is simple. The disadvantages of
this method is it's not suitable for some kind of bitstreams. For
example, AAC bitstream in FLV/MP4/MKV Container Format(data in
AVPacket lack of 7 bytes of ADTS header).
