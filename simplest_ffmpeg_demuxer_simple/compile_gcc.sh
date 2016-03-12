#! /bin/sh
gcc simplest_ffmpeg_demuxer_simple.cpp -g -o simplest_ffmpeg_demuxer_simple.out \
-I /usr/local/include -L /usr/local/lib -lavformat -lavcodec -lavutil
