FROM ubuntu:18.04

WORKDIR /home

RUN apt update && apt install -y build-essential cmake libudev-dev* libsdl2-dev \ 
                                libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev \ 
                                qt5-default libmsgpack*

COPY . .

RUN rm -rf build && mkdir build && cd build && cmake .. && make && make install && cd server

ARG SERVER_HOST="localhost"
ARG SERVER_PORT=8080

# ENTRYPOINT ["/home/build/client/client", ${SERVER_HOST}, ${SERVER_PORT}}]
ENTRYPOINT ["echo", "hola"]