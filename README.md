# Remake del Argentum

## Para correr app:
  - Pararse en el root y correr: mkdir build && cd build && cmake .. && make && make install
  - Para levantar el server pararse en root y correr: ./build/server/server 8080 server/cfg/map/mapa.json server/cfg/entities/entities.json
  - Para levantar el client pararse en root y correr: ./build/client/client localhost 8080

## Con Valgrind (desde el root):  
valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all ./build/server/server 8080 server/cfg/map/mapa.json server/cfg/entities/entities.json

valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=client/suppressions.txt ./build/client/client localhost 8080
