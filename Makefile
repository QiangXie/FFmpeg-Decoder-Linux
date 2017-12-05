PROJECT := FFMpeg_decoder
ORIGIN := \$$ORIGIN
BUILD_DIR := .build_release
BUILD_DIR_LINK := build
BIN_DIR := bin
LIB_DIR := lib
INCLUDE_DIR := include
MAIN_SRC := src/main/main.cpp
UTIL_SRC := src/util/ffmpeg_decoder.cpp

FFMPEG_LIB_DIR := /home/xqiang/.local/ffmpeg/lib
FFMPEG_INCLUDE_DIR := /home/xqiang/.local/ffmpeg/include
OPENCV_INCLUDE_DIR := /usr/local/include
OPENCV_LIB_DIR := /usr/local/lib

ALL_BUILD_DIRS := $(BUILD_DIR)/src/main $(BUILD_DIR)/src/util
MAIN_OBJ := $(BUILD_DIR)/src/main/main.o
UTIL_OBJ := $(BUILD_DIR)/src/util/ffmpeg_decoder.o
EXECUTABLE_PROGRAM := $(BUILD_DIR)/src/main/main.bin

CXX := /usr/bin/g++

INCLUDE_DIRS := $(INCLUDE_DIR) $(FFMPEG_INCLUDE_DIR)
LIBRARY_DIRS := $(FFMPEG_LIB_DIR) $(LIB_DIR)

LIBRARIES := avcodec avformat swscale avdevice avutil opencv_highgui opencv_core

WARNINGS := -Wall -Wno-sign-compare -Wno-uninitialized
COMMON_FLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))
LINKFLAGS += -pthread -fPIC $(COMMON_FLAGS) $(WARNINGS)
CXXFLAGS := -MMD -MP -pthread -fPIC $(COMMON_FLAGS) $(WARNINGS)
LDFLAGS := $(foreach librarydir,$(LIBRARY_DIRS),-L$(librarydir)) \
	$(foreach library,$(LIBRARIES),-l$(library))

.PHONY: all clean bin

all: bin

bin: $(EXECUTABLE_PROGRAM)

$(BUILD_DIR_LINK): $(BUILD_DIR)/.linked

$(BUILD_DIR)/.linked:
	@ mkdir -p $(BUILD_DIR)
	@ $(RM) -r $(BUILD_DIR_LINK)
	@ ln -s $(BUILD_DIR) $(BUILD_DIR_LINK)
	@ touch $@

$(ALL_BUILD_DIRS): | $(BUILD_DIR_LINK)
	@ mkdir -p $@

$(BUILD_DIR)/%.o: %.cpp | $(ALL_BUILD_DIRS)
	@ echo CXX $<
	@ $(CXX) -g $< $(CXXFLAGS) -c -o $@

$(UTIL_OBJ): $(UTIL_SRC)
	@ echo CXX $<
	@ $(CXX) -g $< $(CXXFLAGS) -c -o $@
	

$(EXECUTABLE_PROGRAM): %.bin : %.o $(UTIL_OBJ)
	@ echo CXX/LD -o $@
	@ $(CXX) -g  $< $(UTIL_OBJ)  -o $@ $(LINKFLAGS) $(LDFLAGS) \
		-Wl,-rpath,$(ORIGIN)/../lib
	@ cd bin;ln -s ../build/src/main/main.bin main

clean:
	@ rm -rf $(BUILD_DIR)
	@ rm -rf $(BUILD_DIR_LINK)
	@ rm -rf bin/*


