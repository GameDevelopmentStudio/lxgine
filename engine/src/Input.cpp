#include "Input.h"
#include <stdio.h> 

#pragma mark - Memory Management

Input::Input() {
    nDirtyKeys = nDirtySpecialKeys = 0;
    
    // Init them dynamically with values as false
    keyStates = new bool[NUM_KEYS]();
    specialKeyStates = new bool[NUM_SPECIAL_KEYS]();
    
    prevKeyStates = new bool[NUM_KEYS]();
    prevSpecialKeyStates = new bool[NUM_SPECIAL_KEYS]();
    currKeyStates = new bool[NUM_KEYS]();
    currSpecialKeyStates = new bool[NUM_SPECIAL_KEYS]();
}

Input::~Input() {
    delete []keyStates;
    delete []specialKeyStates;
    
    delete []prevKeyStates;
    delete []prevSpecialKeyStates;
    delete []currKeyStates;
    delete []currSpecialKeyStates;
}

#pragma mark - Runloop Update

void Input::update() {
    // Update only the keys that have changed
    
    int nextNumDirtyKeys = 0;
    for (int i = 0; i < nDirtyKeys; i++) {
        int idx = dirtyKeys[i];
        prevKeyStates[idx] = currKeyStates[idx];
        currKeyStates[idx] = keyStates[idx];
        
        // If value has changed, consider them as dirty for next step
        if (currKeyStates[idx] ^ prevKeyStates[idx]) {
            dirtyKeys[nextNumDirtyKeys++] = idx;
        }
    }
    nDirtyKeys = nextNumDirtyKeys;

    int nextNumDirtySpecialKeys = 0;
    for (int i = 0; i < nDirtySpecialKeys; i++) {
        int idx = dirtySpecialKeys[i];
        prevSpecialKeyStates[idx] = currSpecialKeyStates[idx];
        currSpecialKeyStates[idx] = specialKeyStates[idx];
        
        // If value has changed, consider them as dirty for next tick
        if (currSpecialKeyStates[idx] ^ prevSpecialKeyStates[idx]) {
            dirtyKeys[nextNumDirtySpecialKeys++] = idx;
        }
    }

    nDirtySpecialKeys = nextNumDirtySpecialKeys;
}

void Input::onKeyPressed(unsigned char key) {
    keyStates[key] = true;
    dirtyKeys[nDirtyKeys++] = key;
}

void Input::onKeyReleased(unsigned char key) {
    keyStates[key] = false;
    dirtyKeys[nDirtyKeys++] = key;
}

void Input::onSpecialKeyPressed(int key) {
    specialKeyStates[key] = true;
    dirtySpecialKeys[nDirtySpecialKeys++] = key;
}

void Input::onSpecialKeyReleased(int key) {
    specialKeyStates[key] = false;
    dirtySpecialKeys[nDirtySpecialKeys++] = key;
}

#pragma mark - Keyboards Methods

bool Input::keyCheck(unsigned char key) {
    return currKeyStates[key];
}

bool Input::specialKeyCheck(int key) {
    return currSpecialKeyStates[key];
}

bool Input::keyPressed(unsigned char key) {
    return currKeyStates[key] && !prevKeyStates[key];
}

bool Input::specialKeyPressed(int key) {
    return currSpecialKeyStates[key] && !prevSpecialKeyStates[key];
}

bool Input::keyReleased(unsigned char key) {
    return !currKeyStates[key] && prevKeyStates[key];
}

bool Input::specialKeyReleased(int key) {
    return !currSpecialKeyStates[key] && prevSpecialKeyStates[key];
}