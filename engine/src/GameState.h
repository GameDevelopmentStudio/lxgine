#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

class Game;
class Camera;

class GameState {
 public:        
    // Not owned pointers
    Game *game;
    //
    // Owned pointers
    Camera *camera;
     
    int width;
    int height;

    GameState();
    virtual ~GameState();

    virtual void init();

    virtual void render();
    virtual void update();
};

#endif
