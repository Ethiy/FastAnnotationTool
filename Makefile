# Determine platform
UNAME := $(shell uname -s)
ifeq ($(UNAME), Linux)
	LINUX := 1
else ifeq ($(UNAME), Darwin)
	OSX := 1
endif

boost_l := -lboost_system-mt -lboost_program_options-mt -lboost_filesystem-mt
opencv_l := -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

# Linux
ifeq ($(LINUX), 1)
  compiler = g++ -std=c++11 -Wall -pedantic
  lib_flags := -L/usr/local/lib/ $(boost_l) $(opencv_l)
  include_flags := -I/usr/local/include/opencv2
else
# OSX
  compiler = clang++ -std=c++11 -Wall -pedantic
  lib_flags := -L/usr/local/lib $(boost_l) $(opencv_l)
  include_flags := -I/usr/local/include
endif

tools = src/image/Image.cpp src/annotation/Annotation.cpp src/annotation/Annotations.cpp src/tools/tools.cpp

all: $(tools)
	$(compiler) -o bin/annotate $(include_flags) $(tools) src/run/annotate.cpp $(lib_flags)

annotation: $(tools)
	$(compiler) -o bin/annotate $(include_flags) $(tools) src/run/annotate.cpp $(lib_flags)

clean_tests:
	rm tests/*

clean:
	rm bin/*
