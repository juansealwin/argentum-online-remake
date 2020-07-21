#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SDL2/SDL.h>

#include <string>

#include "drawable.h"
#include "texture_manager.h"
#include "algorithm"

// No es el ñ ASCII pero por alguna razón lo identifica con este numero
#define ENIE_ASCII -61
#define ENIE 241

class TextBox : public Drawable {
 private:
  Texture text_texture;
  std::string text;
  TTF_Font *font;
  SDL_Color text_color;
  SDL_Color background_color;
  int padding;

 public:
  TextBox(text_box_t, std::string);
  ~TextBox();
  virtual void render(SDL_Renderer *, int, int);
  void set_texture(SDL_Renderer *);
  void set_text(std::string);
  void set_text_color(SDL_Color &);
  void set_background_color(SDL_Color &);
  // virtual void set_x(int);
  // virtual void set_y(int);
  void set_mesures_box(text_box_t);
};

#endif