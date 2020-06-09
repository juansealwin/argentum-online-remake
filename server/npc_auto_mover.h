
#ifndef NPC_AUTO_MOVER_H
#define NPC_AUTO_MOVER_H
#include "map.h"
#include "../util/thread.h"
#include <unistd.h>
#define QUIET_TIME 1000000
class NpcAutoMover : public Thread {
public:
    NpcAutoMover(BaseCharacter *npc, Map& map);
    ~NpcAutoMover() override;
    void run() override;

private:
	BaseCharacter *npc;
	Map& map;
	bool alive = true;
};

#endif //NPC_AUTO_MOVER_H