#include "LXGameState.h"
#include "LXGame.h"
#include "LXCamera.h"

LXGameState::LXGameState() {
  camera = new LXCamera();
}

LXGameState::~LXGameState() {
  delete camera;
}

void LXGameState::init() {
  camera->init();
}

void LXGameState::render() {
}

void LXGameState::update() {
}
