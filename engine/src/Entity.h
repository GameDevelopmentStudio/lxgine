#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Vector.h"
#include "Transform3D.h"

class Game;
class GameState;

class Entity {
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
    virtual void translate(real tx, real ty, real tz);
    virtual void rotate(real rx, real ry, real rz);

    // Transformation getters
    const Vec4& getPos() const;
    Vec4& getPos();
    
    double getPitch();
    double getYaw();
    double getRoll();
    
    const Transform getTransform() const;
    Transform getTransform();

    double pitch, yaw, roll;
 protected:
    Vec4 pos;
    Transform transform;
};

#endif
