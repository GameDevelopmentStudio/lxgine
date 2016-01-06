#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "Glut.h"
#include "GameState.h"

#include "ParticleSystem.h"
#include "BoxGenerator.h"
#include "EulerUpdater.h"
#include "SphereAttractorUpdater.h"

class Entity;
class Shader;
class Texture;
class CameraMovementMatchTarget;
class CameraMovementFirstPerson;

class Level : public GameState {
public:     
    Shader *floorProg;
    Shader *objProg;
    Texture *floorTex;
    CameraMovementMatchTarget* cameraMovement3rdPerson;
    CameraMovementFirstPerson* cameraMovement1stPerson;
    
    ParticleSystem particleSystem;
    BoxPosParticleGenerator particleGenerator;
    EulerParticleUpdater eulerParticleUpdater;
    SphereAttractorParticleUpdater attractorParticleUpdater;
    
    Entity *exampleEntity;
    GLfloat light0Pos[4];

    Level();
    ~Level();

    void init();

    void render();
    void update();
};

#endif
