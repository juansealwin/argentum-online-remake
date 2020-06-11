#include "argentum_game.h"

int main(int argc, char *argv[]) {
	ArgentumGame game(3);
	game.start();
	usleep(60000000/7);
	game.kill();
    return 0;
}
