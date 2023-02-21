# Base for a multi-threaded video player #

## References ##

The idea came from the excellent ffmepg + SDL tutorial
http://dranger.com/ffmpeg/ 

This videoplayer does not use ffmpeg but libogg, libtheora and
libvorbis. It uses also SDL2 for the rendering and playing sound.

The ogg/vorbis ogg/theora tutorials of
https://bluishcoder.co.nz/tags/ogg/index.html
are a very good material for understanding of the libraries.

The synchronization is quite different. This code uses 1 thread per stream and
common real-time deadline to set up synchronization. The sound playing
is mostly managed by SDL2. The displayed frame is used with an
additional thread and producer/consumer algorithms to synchronize
stream reading and displaying.

## Compilation and unit testing ##

The compilation process use Cmake

To compile:
	```sh
	cd build
	cmake ..
	make
	```

## Goal ##

The goal is to complete and parallelize the provided code using the
hints of the subject.

### Actions that threads managed ###

1. reading initialization packet in ogg file; init the sdl (video and audio)
2. initializing the theora stream
3. initializing the vorbis stream
4. reading packets in ogg file (twice, each stream reading thread) 
5. decoding theora
6. decoding vorbis
7. displaying the video stream with the sdl
8. playing the sound with the sdl

### Threads ###

1. Thread 1: main thread; init the sdl
2. Thread 2: theora stream reading and decoding video, write texture
3. Thread 3: vorbis stream reading and decoding sound
4. Thread 4: displaying video frame
