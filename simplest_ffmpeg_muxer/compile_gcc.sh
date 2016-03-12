#! /bin/sh
gcc simplest_ffmpeg_muxer.cpp -g -o simplest_ffmpeg_muxer.out -I /usr/local/include -L /usr/local/lib \
-lavformat -lavcodec -lavutil
