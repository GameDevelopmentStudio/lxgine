#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "LockableTarget.h"

#include "Vector.h"
#include "Transform3D.h"

struct ViewVolume {
    float N,F;
    float xR, xL;
    float yT, yB;
};

class Camera : public LockableTargetDelegate {
public:
    ViewVolume viewVolume;

    // Camera coordinates
    Vec4 lookAt, up, right;
    // Camera center
    Vec4 eye;
    // Distance to target
    float focalLength;

    // Lock on mode
    Transform* targetInverseTransform;

    Camera();
    ~Camera();

    void init();

    Vec4 getTarget();

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
    virtual void lockOn(LockableTarget* target, const Transform& transform);
    virtual bool isLockedOn();
    virtual void stopLock(LockableTarget* target);
    virtual void targetDidRotate(LockableTarget* target, real rx, real ry, real rz);
    virtual void targetDidTranslate(LockableTarget* target, real tx, real ty, real tz);
    virtual void targetResetPosition(LockableTarget* target, const Transform& transform);

private:
    bool fpsMode;
};
#endif
