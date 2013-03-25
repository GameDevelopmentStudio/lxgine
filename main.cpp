#include "Derai.h"
#include "LXPoint3D.h"
#include "Level.h"
#include "LXShader.h"

int main(int argc, char **argv) {
    Derai *game = new Derai();
    game->init(argc, argv);

    game->run();

    return 1;
}
