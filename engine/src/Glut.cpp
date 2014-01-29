// Check this one
/* #define GLUT_DISABLE_ATEXIT_HACK */

#include "Glut.h"
#include "Game.h"
#include "Input.h"

#include <stdio.h>

#include <stdlib.h>

// Static Initializations

Glut *Glut::instance = 0;
int Glut::retainCount = 0;

// Memory Management
// TODO: make threadsafe

Glut *Glut::sharedInstance() {
    if (!instance) {
        instance = new Glut();
    }
    return instance;
}

void Glut::retain() {
    Glut::retainCount++;
}

void Glut::release() {
    if (retainCount > 0) {
        Glut::retainCount--;
        if (retainCount == 0) {
            delete instance;
        }
    }
}

Glut::Glut() {
    input = new Input();
}

Glut::~Glut() {
    delete input;
}

void Glut::init(int argc, char **argv) {
    // Initialize GLUT state - glut will take any command line arguments that pertain to it
    glutInit(&argc, argv);    

    // Select type of Display mode:     
    // Double buffer 
    // RGBA color
    // Alpha components supported 
    // Depth buffer
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

    glutInitWindowSize(game->getWidth(), game->getHeight());
    glutInitWindowPosition(0, 0);    
    window = glutCreateWindow("Batman was not here");
    fullscreen = false;

    glewExperimental = GL_TRUE;
    glewInit();

    // Register the callback to do all our OpenGL drawing.
    glutDisplayFunc(&renderWindow);    
    // Register the callback when our window is resized.
    glutReshapeFunc(&resizeWindow);
    // Register input callbacks
    glutKeyboardFunc(&keyPressed);
    glutKeyboardUpFunc(&keyReleased);
    glutSpecialFunc(&specialKeyPressed);
    glutSpecialUpFunc(&specialKeyReleased);
}

// Runloop Methods

void Glut::run() {
    // Set up the runloop
    glutTimerFunc(33.3f, &step, 0);
    glutMainLoop();
}

void Glut::step(int frame) {
    instance->game->Update();
    instance->game->Render();
    
    glutTimerFunc(33.3f, &Glut::step, frame + 1);
}

// Window methods

void Glut::resizeWindow(int width, int height) {
    instance->game->Resize(width, height);
}

void Glut::renderWindow() {
    instance->game->Render();
}

void Glut::close() {
    // Shut down the window
    glutDestroyWindow(instance->window); 
    
    // Exit application with normal termination
    exit(0);
}

void Glut::toggleFullscreen() {
    if (fullscreen)
        glutReshapeWindow(game->getWidth(), game->getHeight());
    else
        glutFullScreen();

    fullscreen = !fullscreen;
}

bool Glut::isFullscreen() {
    return fullscreen;
}

// Input Methods

void Glut::specialKeyReleased(int key, int x, int y) {
    instance->input->onSpecialKeyReleased(key);
}

void Glut::specialKeyPressed(int key, int x, int y) {
    instance->input->onSpecialKeyPressed(key);
}

void Glut::keyReleased(unsigned char key, int x, int y) {
    instance->input->onKeyReleased(key);
}

void Glut::keyPressed(unsigned char key, int x, int y) {
    instance->input->onKeyPressed(key);
}
