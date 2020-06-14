#ifndef GNOME_H
#define GNOME_H

#include <string>

#include "move.h"
#include "player.h"
#include "texture.h"

class Gnome : public Player {
 public:
  Gnome(std::string, std::string, SDL_Renderer*, int, int);
  ~Gnome();
  //virtual void render();
};

#endif
