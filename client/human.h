#ifndef HUMAN_H
#define HUMAN_H

#include "drawable.h"
#include "texture.h"
#include <string>

class Human : public Drawable {
  private:
    std::string image_path;
    Texture texture;

  public:
    Human();
    ~Human();
};

#endif