#ifndef GNOME_H
#define GNOME_H

#include <string>
#define PATH_GNOME_BODY "gnomo.png"
#define PATH_GNOME_HEAD "cabeza_gnomo.png"
#include "move.h"
#include "character.h"
#include "texture.h"

class Gnome : public Character {
 public:
  Gnome(SDL_Renderer*, int, int);
  ~Gnome();
};

#endif
