#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "Glut.h"
#include "GameState.h"

class Entity;
class Shader;
class Texture;

class Level : public GameState {
public:     
    Shader *floorProg;
    Shader *objProg;
    Texture *floorTex;
    
    Entity *exampleEntity;
    GLfloat light0Pos[4];

    Level();
    ~Level();

    void init();

    void render();
    void update();
};

#endif
