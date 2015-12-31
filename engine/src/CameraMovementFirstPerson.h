#ifndef __CAMERAMOVEMENTFIRSTPERSON_H__
#define __CAMERAMOVEMENTFIRSTPERSON_H__

#include "CameraMovement.h"

class Entity;

class CameraMovementFirstPerson : public CameraMovement {
public:
    
    CameraMovementFirstPerson();
    ~CameraMovementFirstPerson();
    
    void followTarget(Entity* target);
    
    // Should be update!!
    virtual void commit();

protected:
    Entity* target;
};

#endif