#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "LockableTarget.h"

#include "Vector.h"
#include "Transform3D.h"

struct ViewVolume {
    real N,F;
    real xR, xL;
    real yT, yB;
};

class Camera : public LockableTargetDelegate {
public:
    ViewVolume viewVolume;

    // Camera coordinates
    Vec4 lookAt, up, right;
    // Camera center
    Vec4 eye;
    // Distance to target
    real focalLength;

    // Lock on mode
    Transform* targetInverseTransform;

    Camera();
    ~Camera();

    void init();

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
