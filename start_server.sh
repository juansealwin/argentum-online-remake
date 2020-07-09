#!/bin/bash

sudo apt update && sudo apt upgrade && sudo apt install -y build-essential cmake libudev-dev* libsdl2-dev \
libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev qt5-default libmsgpack*

if [ ! -d "build" ]; then
  mkdir build && cd build && cmake .. && make && make install && cd ..
fi

cd build/server
./server ${1:-8080} ../../server/cfg/entities/entities.json