# tp_final_taller

Remake del Argentum

| Librería | Versión mínima         |
|--------|---------------------------|
| libsdl2-dev | 2.0.8 |
| libsdl2-image-dev | 2.0.3 |
| qt5-default | 5.9.5 |
| gcc | 7.3.0 |

valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all ./server 8080 ../../server/cfg/map/mapa.json  
valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --gen-suppressions=all --suppressions=./suppressions.txt ./client localhost 8080