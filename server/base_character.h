#include "stdint.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter {
public:
    BaseCharacter(int x, int y);
    ~BaseCharacter();
    char char_representation();
    void set_x_position(int x);
    void set_y_position(int y);

private:
    char representation = 'g';
    int x_position;
    int y_position;
};

#endif //BASE_CHARACTER_H