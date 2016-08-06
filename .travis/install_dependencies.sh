#! /usr/bin/env bash

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    brew update
    brew outdated
    brew upgrade
    brew install cmake boost
    brew tap homebrew/science
    brew install opencv
else
    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
    sudo apt-get -qq update
    sudo apt-get install -y build-essential g++-5 software-properties-common libboost-all-dev
    sudo add-apt-repository -y ppa:boost-latest/ppa
    sudo apt-get update && sudo apt-get -y upgrade
    export CXX="g++-5"
    sudo add-apt-repository -y ppa:george-edison55/cmake-3.x
    sudo apt-get -qq update
    sudo apt-get install -y cmake
    sudo apt-get install -y libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
    sudo apt-get install -y python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev
    mkdir 3rdParty && cd 3rdParty
    git clone https://github.com/opencv/opencv.git 
    mkdir opencv/build && cd opencv/build
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
    make -j4
    sudo make install
    sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
    sudo ldconfig
    cd ../../..
fi