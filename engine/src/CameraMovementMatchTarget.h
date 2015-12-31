#ifndef __CAMERAMOVEMENTMATCHTARGET_H__
#define __CAMERAMOVEMENTMATCHTARGET_H__

#include "CameraMovement.h"
#include "Vector.h"

class Entity;

class CameraMovementMatchTarget : public CameraMovement {
public:
    
    CameraMovementMatchTarget();
    ~CameraMovementMatchTarget();
    
    void followAtOffset(Entity* target, Vec4 offset);
    void followAtCenter(Entity* target);
    
    // Should be update!!
    virtual void commit();

protected:
    Entity* target;
    Vec4 offsetFromTarget;
    real tiltAngleY; // degrees
    real tiltAngleX; // degrees
};

#endif