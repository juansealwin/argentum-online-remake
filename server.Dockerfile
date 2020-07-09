FROM ubuntu:18.04

WORKDIR /home

RUN apt update && apt install -y build-essential cmake libudev-dev* libsdl2-dev \ 
  libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev \ 
  qt5-default libmsgpack*

COPY . .

RUN rm -rf build && mkdir build && cd build && cmake .. && make && make install

ENTRYPOINT ["/home/build/server/server", "8080", "/home/server/cfg/entities/entities.json"]