# Determine platform
UNAME := $(shell uname -s)
ifeq ($(UNAME), Linux)
	LINUX := 1
else ifeq ($(UNAME), Darwin)
	OSX := 1
endif

boost_l := -lboost_system-mt -lboost_program_options-mt -lboost_filesystem-mt
opencv_l := -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videoio -lopencv_videostab

# Linux
ifeq ($(LINUX), 1)
  compiler = g++ -std=c++11 -Wall -pedantic
  lib_flags := -L/usr/local/lib/ $(boost_l) $(opencv_l)
  include_flags := -I/usr/local/include/opencv2
else
  compiler = clang++ -std=c++11 -Wall -pedantic
  lib_flags := -L/opt/local/lib $(boost_l) $(opencv_l)
  include_flags := -I/opt/local/include
endif

tools = src/image/Image.cpp src/tools/tools.cpp

all: $(tools)
#	$(compiler) -o bin/extractRect $(include_flags) $(tools) src/Output.cpp src/extractRect.cpp $(lib_flags) $(lgflags)
#	$(compiler) -o bin/annotateRect $(include_flags) $(tools) src/annotateRect.cpp $(lgflags) -lglog $(lib_flags)
	$(compiler) -o tests/test_image $(include_flags) src/image/Image.cpp src/image/test.cpp $(lib_flags)
	$(compiler) -o bin/annotate $(include_flags) $(tools) src/annotate.cpp $(lib_flags)

test_image: src/image/Image.cpp
	$(compiler) -o tests/test_image $(include_flags) src/image/Image.cpp src/image/test.cpp $(lib_flags)

annotation: $(tools)
	$(compiler) -o bin/annotate $(include_flags) $(tools) src/annotate.cpp $(lib_flags)

clean_tests:
	rm tests/*

clean:
	rm bin/*
