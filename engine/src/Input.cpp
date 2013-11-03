#include "Input.h"

#pragma mark - Memory Management

Input::Input() {
    keyStates = new bool[256]();
    specialKeyStates = new bool[246]();    
}

Input::~Input() {
    delete []keyStates;
    delete []specialKeyStates;
}

#pragma mark - Runloop Update

void Input::update() {
    // TODO
}

#pragma mark - Keyboards Methods

bool Input::keyPressed(unsigned char key) {
    return keyStates[key]; 
}

bool Input::specialKeyPressed(int key) {
    return specialKeyStates[key];
}
