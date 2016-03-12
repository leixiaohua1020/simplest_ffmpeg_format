#! /bin/sh
gcc simplest_ffmpeg_demuxer.cpp -g -o simplest_ffmpeg_demuxer.out \
-I /usr/local/include -L /usr/local/lib -lavformat -lavcodec -lavutil
