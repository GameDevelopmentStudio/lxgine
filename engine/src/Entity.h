#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "LockableTarget.h"

class Matrix3D;
class Vector3;
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
    virtual void translate(double tx, double ty, double tz);
    virtual void rotate(double rx, double ry, double rz);

    // Transformation getters
    Vector3 getPos();
    double getPitch();
    double getYaw();
    double getRoll();

    // LockableTarget
    virtual void setDelegate(LockableTargetDelegate *delegate);

    double pitch, yaw, roll;
 protected:
    Vector3 *pos;    
    Matrix3D *transform;
};

#endif
