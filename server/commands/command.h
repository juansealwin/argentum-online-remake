#ifndef COMMAND_H
#define COMMAND_H
//#include "argentum_game.h" <- incluir devuelta si hay problemas con
// dependencia circular
class ArgentumGame;  // por dependencia circular

class Command {
 public:
  Command();
  //uid es el identificador unico del jugador
  explicit Command(const unsigned int uid);
  virtual ~Command();
  Command(const Command &) = delete;
  // Ejecuta cambios en el juego
  virtual void execute(ArgentumGame *game) = 0;
 protected:
  unsigned int uid;
};
#endif
