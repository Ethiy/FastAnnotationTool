#! /usr/bin/env bash

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    brew update
    brew outdated
    brew upgrade
    brew install cmake
    brew tap homebrew/science
    brew install opencv3
else
    # GCC 6
    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
    sudo apt-get -qq update
    sudo apt-get install -y build-essential gcc-6 g++-6 software-properties-common
    export CXX="g++-6"

    # 3rdParty
    mkdir 3rdParty && cd 3rdParty

    # Boost 1.61
    wget http://downloads.sourceforge.net/boost/boost_1_61_0.tar.bz2
    tar jxf boost_1_61_0.tar.bz2
    rm boost_1_61_0.tar.bz2
    cd boost_1_61_0
    sudo ./bootstrap.sh --prefix=/usr
    sudo ./b2 stage threading=multi link=shared -j4
    cd ..

    # OpenCV instalation
    sudo add-apt-repository -y ppa:george-edison55/cmake-3.x
    sudo apt-get -qq update
    sudo apt-get install -y cmake
    sudo apt-get install -y libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
    sudo apt-get install -y python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev
    git clone https://github.com/opencv/opencv.git 
    mkdir opencv/build && cd opencv/build
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
    make -j4
    sudo make install
    sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
    sudo ldconfig
    cd ../../..
fi