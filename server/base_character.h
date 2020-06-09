#include "stdint.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter {
public:
    BaseCharacter(int x, int y);
    ~BaseCharacter();
    char char_representation();
    void set_x_y_position(int x, int y);
    int x_position;
    int y_position;

private:
    char representation = 'g';
};

#endif //BASE_CHARACTER_H