#ifndef _FFMPEG_DECODER_HPP_
#define _FFMPEG_DECODER_HPP_

#include "ffmpeg_include.hpp"
#include <string>

bool Save(const std::string & pFileName, AVFrame * frame, const int & w, const int & h);

class FFmpegDecoder{ 
	// constructor.
	public: 
		FFmpegDecoder() : pImgConvertCtx(NULL), audioBaseTime(0.0), videoBaseTime(0.0),
		videoFramePerSecond(0.0), isOpen(false), audioStreamIndex(-1), videoStreamIndex(-1),
		pAudioCodec(NULL), pAudioCodecCtx(NULL), pVideoCodec(NULL), pVideoCodecCtx(NULL),
		pFormatCtx(NULL) {;}

		// destructor.
		virtual ~FFmpegDecoder(){
			CloseFile();
		}

		// Open file
		virtual bool OpenFile(const std::string& inputFile);

		// Close file and free resourses.
		virtual bool CloseFile();

		// Return next frame FFmpeg.
		virtual AVFrame * GetNextFrame();

		int GetWidth(){
			return width;
		}
		int GetHeight(){
			return height;
		}

	private: 
		// open video stream.
		bool OpenVideo();

		// open audio stream.
		bool OpenAudio();

		// close video stream.
		void CloseVideo();

		// close audio stream.
		void CloseAudio();

		// return rgb image 
		AVFrame * GetRGBAFrame(AVFrame *pFrameYuv);

		// Decode audio from packet.
		int DecodeAudio(int nStreamIndex, const AVPacket *avpkt, 
				 uint8_t* pOutBuffer, size_t nOutBufferSize);

		// Decode video buffer.
		bool DecodeVideo(const AVPacket *avpkt, AVFrame * pOutFrame);

		// FFmpeg file format.
		AVFormatContext* pFormatCtx;  

		// FFmpeg codec context.
		AVCodecContext* pVideoCodecCtx;

		// FFmpeg codec for video.
		AVCodec* pVideoCodec;

		// FFmpeg codec context for audio.
		AVCodecContext* pAudioCodecCtx;

		// FFmpeg codec for audio.
		AVCodec* pAudioCodec;

		// Video stream number in file.
		int videoStreamIndex;

		// Audio stream number in file.
		int audioStreamIndex;

		// File is open or not.
		bool isOpen;

		// Video frame per seconds.
		double videoFramePerSecond;

		// FFmpeg timebase for video.
		double videoBaseTime;

		// FFmpeg timebase for audio.
		double audioBaseTime;

		// FFmpeg context convert image.
		struct SwsContext *pImgConvertCtx;

		// Width of image
		int width;

		// Height of image
		int height;
};

#endif
