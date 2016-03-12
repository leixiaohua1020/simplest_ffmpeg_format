#! /bin/sh
g++ simplest_ffmpeg_demuxer_simple.cpp -g -o simplest_ffmpeg_demuxer_simple.exe \
-I /usr/local/include -L /usr/local/lib -lavformat -lavcodec -lavutil
