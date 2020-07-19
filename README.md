# Remake del Argentum

## Para correr la app:
  - Para levantar el server pararse en root y ejecutar el bash `start_server.sh`
  - Para levantar el client pararse en root y ejecutar el bash `start_client.sh` 

## Con Valgrind (desde el root):  
`valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all ./build/server/server 8080 server/cfg/entities/entities.json`

`valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=client/suppressions.txt ./build/client/client localhost 8080`

## Para levantar el server con Docker:
`docker build -t "server:1.0.0" -f server.Dockerfile .`  
`docker run --net=host <id imagen>`  
Luego levantar el cliente en localhost con el puerto 8080