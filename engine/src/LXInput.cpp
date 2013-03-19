#include "LXInput.h"

#pragma mark - Memory Management

LXInput::LXInput() {
  keyStates = new bool[256]();
  specialKeyStates = new bool[246]();  
}

LXInput::~LXInput() {
  delete []keyStates;
  delete []specialKeyStates;
}

#pragma mark - Runloop Update

void LXInput::update() {
  // TODO
}

#pragma mark - Keyboards Methods

bool LXInput::keyPressed(unsigned char key) {
  return keyStates[key]; 
}

bool LXInput::specialKeyPressed(int key) {
  return specialKeyStates[key];
}
