#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Glut.h"

class Player : public Entity {
public:
    GLuint vertexArray;
    GLuint vertexBuffer;
    
    Player();
    ~Player();

    void init();
    void update();
    void render();
};

#endif
