#! /bin/sh
g++ simplest_ffmpeg_demuxer.cpp -g -o simplest_ffmpeg_demuxer.exe \
-I /usr/local/include -L /usr/local/lib -lavformat -lavcodec -lavutil
