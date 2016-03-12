#! /bin/sh
g++ simplest_ffmpeg_muxer.cpp -g -o simplest_ffmpeg_muxer.exe \
-I /usr/local/include -L /usr/local/lib -lavformat -lavcodec -lavutil
