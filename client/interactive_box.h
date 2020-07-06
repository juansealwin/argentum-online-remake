#ifndef INTERACTIVE_BOX_H
#define INTERACTIVE_BOX_H

#include "SDL2/SDL.h"
//borrame
#include <iostream>

class InteractiveBox {
 private:
  SDL_Rect box_dimensions;

 public:
  InteractiveBox();
  InteractiveBox(int, int, int, int);
  ~InteractiveBox();
  bool mouse_click_in(int, int);
  int get_item_clicked(int, int);
};



#endif