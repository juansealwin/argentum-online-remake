#ifndef INTERACTIVE_BOX_H
#define INTERACTIVE_BOX_H

#include "SDL2/SDL.h"

class InteractiveBox {
 private:
  SDL_Rect box_dimensions;
  int rows;
  int cols;

 public:
  InteractiveBox();
  // Constructor: x, y, ancho y alto, filas y columnas
  InteractiveBox(int, int, int, int, int=1, int=1);
  ~InteractiveBox();
  bool mouse_click_in(int, int);
  int get_item_clicked(int, int);
};



#endif