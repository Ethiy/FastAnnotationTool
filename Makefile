# Determine platform
UNAME := $(shell uname -s)
ifeq ($(UNAME), Linux)
	LINUX := 1
else ifeq ($(UNAME), Darwin)
	OSX := 1
endif

opencv_l := -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videoio -lopencv_videostab

# Linux
ifeq ($(LINUX), 1)
	compiler = g++ -std=c++11
  opencv_lib := -L/usr/local/lib/ $(opencv_l)
  opencv_flags := -I/usr/local/include/opencv2
else
	compiler = clang++ -std=c++11
  opencv_lib := -L/opt/local/lib $(opencv_l)
  opencv_flags := -I/opt/local/include
endif

utils = src//image/Image.cpp src/Utils.cpp
lgflags = -lglog -lgflags -lpthread

all: $(utils)
	$(compiler) -o bin/extractRect $(opencv_flags) $(utils) src/Output.cpp src/extractRect.cpp $(opencv_lib) $(lgflags)
	$(compiler) -o bin/annotateRect $(opencv_flags) $(utils) src/annotateRect.cpp $(lgflags) -lglog $(opencv_lib)

test_image: src/image/Image.cpp
	$(compiler) -o tests/test_image $(opencv_flags) src/image/Image.cpp src/image/test.cpp $(opencv_lib)

extraction: $(utils) src/Output.cpp
	$(compiler) -o bin/extractRect $(opencv_flags) $(utils) src/Output.cpp src/extractRect.cpp $(opencv_lib) $(lgflags)

annotation: $(utils)
	$(compiler) -o bin/annotateRect $(opencv_flags) $(utils) src/annotateRect.cpp $(lgflags) -lglog $(opencv_lib)

clean_tests:
	rm tests/*

clean:
	rm bin/*
