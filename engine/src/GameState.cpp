#include "GameState.h"
#include "Game.h"
#include "Camera.h"

GameState::GameState() {
    camera = new Camera();
}

GameState::~GameState() {
    delete camera;
}

void GameState::init() {
    camera->init();
}

void GameState::render() {
}

void GameState::update() {
}
