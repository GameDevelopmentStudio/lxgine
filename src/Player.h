#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Glut.h"

class Player : public Entity {
public:
    
    Player();
    ~Player();

    virtual void init();
    virtual void update();
    virtual void render();
};

#endif
