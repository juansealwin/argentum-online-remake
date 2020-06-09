
#ifndef NPC_AUTO_MOVER_H
#define NPC_AUTO_MOVER_H
#include "map.h"
#include "../util/thread.h"
#include <unistd.h>
#include <cstdlib> 
//Se queda quieto un segundo.
#define QUIET_TIME 1000000
class NpcAutoMover : public Thread {
public:
    NpcAutoMover(BaseCharacter *npc, Map& map);
    ~NpcAutoMover() override;
    void run() override;

private:
	int next_x_position = 0;
	int next_y_position = 0;
	BaseCharacter *npc;
	Map& map;
	bool alive = true;
};

#endif //NPC_AUTO_MOVER_H