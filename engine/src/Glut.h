#ifndef __GLUT_H__
#define __GLUT_H__

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

class Game;
class Input;

class Glut {
public:
    // Not owned pointers
    // Pointer to the current game that's using the window
    Game *game;
    //
    // Owned pointers
    // Input
    Input *input;

    // Singleton methods
    // Glut's live cycle is loosely inspired in objective-c's retain count
    //
    // Returns (or create and returns) and instance of Glut
    static Glut *sharedInstance();
    // Retain claims ownership on the current Glut instance. By calling it, 
    // Glut will ensure the object is alive in the caller's scope until release
    // is called. At that point the object may or may not be deleted, depending 
    // on how many other owners there are
    static void retain();
    static void release();

    // Init takes command like arguments, if any
    void init(int argc, char **argv);
    // Starts the run loop
    void run();
    // Closes the application
    void close();
    void toggleFullscreen();
    bool isFullscreen();

private:
    static Glut *instance;
    static int retainCount;

    int window; 
    bool fullscreen;

    // Memory management
    Glut();
    ~Glut();

    // Glut callbacks
    //
    // Scene & view update
    static void resizeWindow(int width, int height);
    static void renderWindow();
    static void step(int frame);
    // Input TODO: move to another class
    static void specialKeyReleased(int key, int x, int y);
    static void specialKeyPressed(int key, int x, int y);
    static void keyReleased(unsigned char key, int x, int y);
    static void keyPressed(unsigned char key, int x, int y);
};

#endif
