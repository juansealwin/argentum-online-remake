#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "common_socket.h"
#include "game.h"
#include "protocol.h"
#include "texture.h"
#define FRAME_DELAY 5000 / 60

class Client {
 private:
  Socket socket;
  /*Devuelve True si el usuario esta intentando pedir ayuda,
  rendirse o enviar un numero al servidor.
  Si no, devuelve False ya que no es un comando soportado.*/
  const bool valid_request(std::string& request);

 public:
  Client(const char* host, const char* port);
  ~Client();
  void play();
};

#endif
