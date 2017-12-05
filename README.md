
**AN FFMPEG DECODER ON LINUX PLATFORM** 

Modify FFMPEG_LIB_DIR，FFMPEG_INCLUDE_DIR，OPENCV_INCLUDE_DIR and OPENCV_LIB_DIR to your path, ant then:

	cd FFmpeg-Decoder-Linux
	make
	mkdir -p ./data/image
	./bin/main /video/path

Images should save to ./data/image/.

