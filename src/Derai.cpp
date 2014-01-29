#include "Derai.h"
#include "Level.h"

Derai::Derai() : Game() {
}

Derai::~Derai() {
}

// Initialization Methods

void Derai::init(int argc, char **argv) {
    Game::init(argc, argv);

    Level *world = new Level();
    changeWorld(world);
}

// Main Virtual Methods

void Derai::initSettings() {
    width = 640;
    height = 480;
}
