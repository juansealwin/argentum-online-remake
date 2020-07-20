#ifndef EXCEPTION_MESSAGES_H
#define EXCEPTION_MESSAGES_H

/*** ARGUMENTS ERRORS ***/
#define MSG_ERROR_QUANTITY_ARGS "Error: Cantidad inválida de argumentos"

#define MSG_ERROR_INVALID_FILE_NAME \
  "Nombre de archivo inválido, el nombre debe ser \"server.list\""

#define MSG_ERROR_OPENING_FILE "No se puedo abrir el archivo"

#define MSG_ERROR_NULL_POINTER "Error: Punteros nulos"

/*** SOCKETS ERRORS ***/
#define MSG_ERROR_ADDRESS_INFO "Error en address info al crear el socket"

#define MSG_ERROR_CREATING_SOCKET "Error: No se pudo crear un socket"

#define MSG_ERROR_SOCKET_CONNECTION "Error: Fallo en la conexión del socket"

#define MSG_ERROR_NO_ADDRESS "Error: No hay direcciones validas disponibles"

#define MSG_ERROR_BIND_SOCKET "Error: No se puedo enlazar al socket"

#define MSG_ERROR_LISTEN_SOCKET \
  "Error: No se pudo esperar a conexiones con clientes"

#define MSG_ERROR_NEW_CONNECTION "Error: No se pudo crear una conexión nueva"

#define MSG_ERROR_INVALID_IP "Error: IP de servidor inválida"

#define MSG_ERROR_SOCKET_CLOSED \
  "Error: No se puede transmitir datos, socket cerrado"

#define MSG_ERROR_RECIVING_DATA "Error: No se pudo recibir datos por el socket"

#define MSG_ERROR_SENDING_DATA "Error: No se pudo enviar datos por el socket"

#define MSG_ERROR_CONNECTING_SERVER \
  "Error: No hay servidores disponibles o bien fallo la conexión"

/*** SDL ERRORS ***/
#define MSG_ERROR_SDL_INIT_WINDOW "Error: No se pudo inicializar una ventana"

#define MSG_ERROR_SDL_INIT_RENDERER "Error: No se pudo inicializar el renderer"

#define MSG_ERROR_SDL_IMG_INIT "Error: IMG_Init no definida"

#define MSG_ERROR_SDL_MIXER_INIT \
  "Error: No se pudo inicializar el mixer de audio"

#define MSG_ERROR_SDL_TTF_INIT \
  "Error: No se pudo inicializar el renderizador de fuentes"

#define MSG_ERROR_LOAD_MUSIC "Error: No se pudo cargar la musica "

#define MSG_ERROR_LOAD_SOUND "Error: No se pudo cargar el sonido "

#define MSG_ERROR_LOAD_TEXTURE "Error: No se pudo cargar la textura "

#define MSG_ERROR_LOAD_TEXTURE_TEXT \
  "Error: No se puedo cargar la textura desde el texto"

#endif
