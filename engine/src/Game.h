#ifndef __GAME_H__
#define __GAME_H__

#include "Glut.h"

class GameState;

class Game {
 public:        
    // Not owned pointers
    Input *input;
    //
    // Owned pointers
    GameState *world;
    
    // Getters
    int getWidth();
    int getHeight();

    Game();
    virtual ~Game();

    virtual void initSettings();
    virtual void render();
    virtual void update();

    virtual void init(int argc, char **argv);
    virtual void run();
    virtual void changeWorld(GameState *newWorld);
    virtual void screenshot();

    // Event calls from glut
    virtual void Render();
    virtual void Update();
    virtual void Resize(int width, int height);

 protected:
    int width;
    int height;
    // OpenGL's window manager
    Glut *glut;
};

#endif
