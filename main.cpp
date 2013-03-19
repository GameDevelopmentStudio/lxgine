#include "Derai.h"

int main(int argc, char **argv) {
    Derai *game = new Derai();
    game->init(argc, argv);

    game->run();

    return 1;
}
