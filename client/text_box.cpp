#include "text_box.h"

TextBox::TextBox(text_box_t type, std::string new_text) {
  /*x = 15;
  y = 116;
  width = 0;        // El ancho dependera del texto
  height = height;  // El alto del rectangulo es configurable*/

  set_mesures_box(type);

  text = new_text;

  // Text color default blanco
  text_color = {255, 255, 255, 0};

  // Background color default negro
  background_color = {0, 0, 0, 0};

  padding = 2;

  font = TTF_OpenFont("alagard.ttf", height);
}

TextBox::~TextBox() { TTF_CloseFont(font); }

void TextBox::set_texture(SDL_Renderer* renderer) {
  text_texture.load_from_rendered_text(renderer, font, text, text_color);
  width = text_texture.get_width() + padding * 2;
}

void TextBox::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  // Background rect
  SDL_Rect background_rect = {x - x_rel, y - y_rel, width, height};

  // SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
  // background_color.b, background_color.a);

  // No quiero que rellene el text_box
  // SDL_RenderFillRect(renderer, &background_rect);

  // Render text
  text_texture.render(renderer, x + padding - x_rel, y + padding - y_rel);
}

void TextBox::set_text_color(SDL_Color& color) { text_color = color; }

void TextBox::set_background_color(SDL_Color& color) {
  background_color = color;
}

/*
void TextBox::set_x(int x) { x = x - width / 2; }

void TextBox::set_y(int y) { y = y - height / 2; }
*/

void TextBox::set_mesures_box(text_box_t box_type) {
  // Depende del ancho del texto
  width = 0;

  switch (box_type) {
    case MESSAGE_1:
      x = 15;
      y = 13;
      height = 20;
      break;

    case MESSAGE_2:
      x = 15;
      y = 35;
      height = 20;
      break;

    case MESSAGE_3:
      x = 15;
      y = 57;
      height = 20;
      break;

    case MESSAGE_4:
      x = 15;
      y = 79;
      height = 20;
      break;

    case NAME:
      x = 620;
      y = 52;
      height = 25;
      break;

    case LEVEL:
      x = 650;
      y = 23;
      height = 20;
      break;

    case EXP:
      x = 670;
      y = 92;
      height = 20;
      break;

    case GOLD_QUANTITY:
      x = 665;
      y = 376;
      height = 15;
      break;

    case HEALTH:
      x = 660;
      y = 411;
      height = 15;
      break;

    case MANA:
      x = 660;
      y = 436;
      height = 15;
      break;
  }
}