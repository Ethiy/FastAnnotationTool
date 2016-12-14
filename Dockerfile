FROM ubuntu:16.04
RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get install -y \
            gcc-5-base\
            libgcc-5-dev\
            g++\
            cmake\
            git
RUN apt-get install -y \
            libboost-filesystem-dev\
            libboost-system-dev\
            libcgal-qt5-dev
WORKDIR /home
RUN mkdir 3rdParty
WORKDIR 3rdParty
RUN git clone https://github.com/opencv/opencv.git
WORKDIR opencv/
RUN git checkout tags/3.1.0
RUN mkdir build
WORKDIR build
RUN cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
RUN make -j8 all && make install
WORKDIR /home
RUN git clone https://github.com/Ethiy/FastImageAnnotationTool.git
WORKDIR FastImageAnnotationTool/
RUN mkdir build && mkdir build/linux
WORKDIR build/linux
RUN cmake ../..
RUN make -j4 all