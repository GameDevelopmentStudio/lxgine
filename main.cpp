#include "Derai.h"
#include "LXPoint3D.h"
#include "Level.h"
#include "LXShader.h"

#include "stdlib.h" 
#include <iostream>

#define STRINGIFY(A) #A


int main(int argc, char **argv) {
    Derai *game = new Derai();
    game->init(argc, argv);

    game->run();

    
    return 1;
}
