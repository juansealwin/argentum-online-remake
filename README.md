# tp_final_taller

Remake del Argentum

| Librería | Versión mínima         |
|--------|---------------------------|
| libsdl2-dev | 2.0.8 |
| libsdl2-image-dev | 2.0.3 |
| qt5-default | 5.9.5 |
| gcc | 7.3.0 |
| libmsgpack* | 3.3.0 |

## Para correr app:  
valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --leak-check=full --leak-resolution=med --show-reachable=yes --track-origins=yes ./server 8081 ../../server/cfg/map/mapa.json ../../server/cfg/entities/entities.json

valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=../../client/suppressions.txt ./client localhost 8080
