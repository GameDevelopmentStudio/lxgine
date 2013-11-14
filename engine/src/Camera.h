#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "LockableTarget.h"

#include "Vector.h"
#include "Matrix3D.h"

struct ViewVolume {
        float N,F;
        float xR, xL;
        float yT, yB;
};

class Camera : public LockableTargetDelegate {
public:
    ViewVolume viewVolume;

    // Camera coordinates
    Vector4f lookAt, up, right;
    // Camera center
    Vector4f eye;
    // Distance to target
    float focalLength;

    // Lock on mode
    Matrix3D *targetInverseTransform;

    Camera();
    ~Camera();

    void init();

    Vector4f getTarget();

    void translate(float x, float y, float z);
    void translateX(float x);
    void translateY(float y);
    void translateZ(float z);

    void pitch(float alpha);
    void yaw(float alpha);
    void roll(float alpha);
    void orbitate(float rx, float ry);

    void commit();

    void toggleFPS();

    // LocableDelegateMethods
    virtual void lockOn(LockableTarget* target);
    virtual bool isLockedOn();
    virtual void stopLock(LockableTarget* target);
    virtual void targetDidRotate(LockableTarget *target, float rx, float ry, float rz);
    virtual void targetDidTranslate(LockableTarget *target, float tx, float ty, float tz);
    virtual void targetResetPosition(LockableTarget *target, const Matrix3D *transform);

private:
    bool fpsMode;
};
#endif
