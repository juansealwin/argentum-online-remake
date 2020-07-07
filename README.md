# Remake del Argentum

## Para correr app:
  - Clonar repositorio en master
  - Pararse en el root y correr: mkdir build && cd build && cmake .. && make && make install
  - Para levantar el server pararse en root y correr: ./build/server/server 8080 server/cfg/map/mapa.json server/cfg/entities/entities.json
  - Para levantar el client pararse en root y correr: ./build/client/client localhost 8080

## Con Valgrind:  
valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all ./server 8080 mapa.json entities.json

valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=../../client/suppressions.txt ./client localhost 8080

## Con docker:
`docker build -t "server:1.0.0" -f server.Dockerfile .`  
`docker build -t "client:1.0.0" -f client.Dockerfile .`