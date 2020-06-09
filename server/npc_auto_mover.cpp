#include "npc_auto_mover.h"
#include <iostream>
NpcAutoMover::NpcAutoMover(BaseCharacter *npc, Map& map) :
    npc(npc), map(map) {}


NpcAutoMover::~NpcAutoMover() {
    alive = false;
    this->join();
}

void NpcAutoMover::run() {
    while (alive) {
        usleep(QUIET_TIME);
        int x_step = rand() % 2; //Si es 0, se queda quieto. Si es 1, se mueve.
        int y_step = rand() % 2;
        int y_top = rand() % 2;
        if (y_top == 1) {
        	y_step*= -1;
        }
        int x_left = rand() % 2;
        if (x_left == 1) {
        	x_step *= -1;
        }
        map.move_character(npc->x_position,npc->y_position,npc->x_position + x_step, npc->y_position + y_step);
    }
}