#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "LockableTarget.h"
#include "Vector.h"
#include "Matrix3D.h"

class Game;
class GameState;

class Entity : public LockableTarget {
 public:
    // Not owned pointers
    Game *game;
    GameState *world;
    
    Entity();
    virtual ~Entity();

    virtual void init();

    virtual void update();
    virtual void render();
    virtual void Render();

    // Transformation setters
    virtual void translate(float tx, float ty, float tz);
    virtual void rotate(float rx, float ry, float rz);

    // Transformation getters
    Vector4f getPos();
    double getPitch();
    double getYaw();
    double getRoll();
    const Matrix3D *getTransform();

    // LockableTarget
    virtual void setDelegate(LockableTargetDelegate *delegate);

    double pitch, yaw, roll;
 protected:
    Vector4f *pos;
    Matrix3D *transform;
};

#endif
