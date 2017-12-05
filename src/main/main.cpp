#include "ffmpeg_decoder.hpp"
#include <iostream>
#include <string>
#include <sstream>

const int frame_counter = 50;
const std::string output_file_prefix = "./data/image/";
const std::string output_file_suffix = ".jpg";

int main(int argc, char ** argv){
	if(argc < 2){
		std::cout << "Please input video file.";
		return 0;
	}

	FFmpegDecoder decoder;
	if (decoder.OpenFile(argv[1])){
		int w = decoder.GetWidth();
		int h = decoder.GetHeight();
		std::cout << "Video width: " << w << ", video height: " << h << std::endl;

		for (int i = 0; i < frame_counter; i++){
			AVFrame * frame = decoder.GetNextFrame();
			if (frame){
				std::stringstream img_output_name;
				img_output_name << output_file_prefix << i << output_file_suffix;
				std::cout << "Save " << img_output_name.str() << std::endl;
				if (!Save(img_output_name.str(), frame, w, h)){
					std::cout << "Can not save file \n" << img_output_name.str() << std::endl;
				}
				av_free(frame->data[0]);
				av_free(frame);
				img_output_name.clear();
			}
		}
		decoder.CloseFile();
	}
	else{
		std::cout << "Can't open video file " << argv[1] << std::endl;
	}
	return 0;
}

