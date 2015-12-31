#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Vector.h"
#include "Transform3D.h"
#include "CameraLens.h"

class CameraMovement;

class Camera {
public:
    
    // Lens parameters
    CameraLens cameraLens;

    // Camera coordinates
    Vec4 lookAt, up, right;
    // Camera center
    Vec4 eye;
    // Distance to target
    real focalLength;

    Camera();
    ~Camera();

    void init();
    
    void lookAtPosition(Vec4 target);
    void lookInDirection(Vec4 lookAt, real focalLength);
    
    void SetCameraMovement(CameraMovement* cameraMovement);
    CameraMovement* GetCameraMovement();
    
    Vec4 getTarget();

    void translate(real x, real y, real z);
    void translateX(real x);
    void translateY(real y);
    void translateZ(real z);

    void pitch(real alpha);
    void yaw(real alpha);
    void roll(real alpha);
    void orbitate(real rx, real ry);

    void commit();
    
protected:
    CameraMovement* cameraMovement;
};
#endif
