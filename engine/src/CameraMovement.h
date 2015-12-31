#ifndef __CAMERAMOVEMENT_H__
#define __CAMERAMOVEMENT_H__

class CameraMovement {
public:
    
    CameraMovement();
    ~CameraMovement();
    
    // Should be update!! With the camera as a param
    virtual void commit() = 0;
};

#endif