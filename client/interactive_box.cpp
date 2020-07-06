#include "interactive_box.h"

InteractiveBox::InteractiveBox() { box_dimensions = {0, 0, 0, 0}; }

InteractiveBox::InteractiveBox(int x, int y, int width, int height) {
  box_dimensions = {x, y, width, height};
}

InteractiveBox::~InteractiveBox() {}

bool InteractiveBox::mouse_click_in(int mouse_x, int mouse_y) {
  return ((box_dimensions.x < mouse_x) &&
          (mouse_x < box_dimensions.x + box_dimensions.w) &&
          (box_dimensions.y < mouse_y) &&
          (mouse_y < box_dimensions.y + box_dimensions.h));
}

// Esta función es solo para el inventario
int InteractiveBox::get_item_clicked(int m_x, int m_y) {
  int item = 0;

  // Chequeamos en que columna esta
  if (m_x > box_dimensions.x + box_dimensions.w * 3 / 4)
    item = 3;
  else if (m_x > box_dimensions.x + box_dimensions.w / 2)
    item = 2;
  else if (m_x > box_dimensions.x + box_dimensions.w / 4)
    item = 1;

  // Cheuqeamos en que fila esta (cada fila son 4 items mas)
  if (m_y > box_dimensions.y + box_dimensions.h * 4 / 5)
    item += 16;
  else if (m_y > box_dimensions.y + box_dimensions.h * 3 / 5)
    item += 12;
  else if (m_y > box_dimensions.y + box_dimensions.h * 2 / 5)
    item += 8;
  else if (m_y > box_dimensions.y + box_dimensions.h / 5)
    item += 4;

  return item;
}