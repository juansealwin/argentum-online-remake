#include "human.h"

Human::Human() {
  body_w = 25;
  body_h = 45;
  head_w = 17;
  head_h = 16;
  animation_move = new Move(body_w, body_h, total_clips);
}

Human::~Human() {}
