#include "Derai.h"
#include "Level.h"

Derai::Derai() : LXGame() {
}

Derai::~Derai() {
}

#pragma mark - Initialization Methods

void Derai::init(int argc, char **argv) {
  LXGame::init(argc, argv);

  Level *world = new Level();
  changeWorld(world);
}

#pragma mark - Main Virtual Methods

void Derai::initSettings() {
  width = 640;
  height = 480;
}
