#include "interactive_box.h"

InteractiveBox::InteractiveBox() { box_dimensions = {0, 0, 0, 0}; }

InteractiveBox::InteractiveBox(int x, int y, int width, int height, int r = 1,
                               int c = 1) {
  box_dimensions = {x, y, width, height};
  rows = r;
  cols = c;
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
  for (int i = box_dimensions.x; i < m_x; i += box_dimensions.w / cols) {
    item++;
  }

  for (int i = box_dimensions.y + box_dimensions.h / rows; i < m_y;
       i += box_dimensions.h / rows) {
    item += cols;
  }

  return item;
}