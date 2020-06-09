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
        map.move_character(npc->x_position,npc->y_position,npc->x_position + 1, npc->y_position);
    }
}