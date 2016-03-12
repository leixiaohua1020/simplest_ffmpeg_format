#! /bin/sh
g++ simplest_ffmpeg_remuxer.cpp -g -o simplest_ffmpeg_remuxer.exe \
-I /usr/local/include -L /usr/local/lib -lavformat -lavcodec -lavutil
