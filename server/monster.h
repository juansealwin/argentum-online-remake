#include "stdint.h"
#ifndef MONSTER_H
#define MONSTER_H
#include "base_character.h"
class Monster : public BaseCharacter {
public:
    Monster(int x, int y, int id, char repr);
    bool is_movable() override;
    ~Monster();

private:
};

#endif //MONSTER_H