#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H

class ArgentumGame {
 public:
  // Instancia una nueva sala de Argentum
  explicit ArgentumGame(const unsigned int room);
  ~ArgentumGame();
  const unsigned int get_room();

 private:
  unsigned int room = 0;
};

#endif  // ARGENTUMGAME_H
