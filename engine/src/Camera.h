#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "LockableTarget.h"
#include "Point3D.h"

class Matrix3D;

struct ViewVolume {
        double N,F;
        double xR, xL;
        double yT, yB;
};

class Camera : public LockableTargetDelegate {
public:
    ViewVolume viewVolume;

    // Camera coordinates
    Point3D lookAt, up, right;
    // Camera center
    Point3D eye;
    // Distance to target
    double focalLength;

    // Lock on mode
    Matrix3D *targetInverseTransform;

    Camera();
    ~Camera();

    void init();

    Point3D getTarget();

    void translate(double x, double y, double z);
    void translateX(double x);
    void translateY(double y);
    void translateZ(double z);

    void pitch(double alpha);
    void yaw(double alpha);
    void roll(double alpha);
    void orbitate(double rx, double ry);

    void commit();

    void toggleFPS();

    // LocableDelegateMethods
    virtual void lockOn(LockableTarget* target);
    virtual bool isLockedOn();
    virtual void stopLock(LockableTarget* target);
    virtual void targetDidRotate(LockableTarget *target, double rx, double ry, double rz);
    virtual void targetDidTranslate(LockableTarget *target, double tx, double ty, double tz);
    virtual void targetResetPosition(LockableTarget *target, const Matrix3D *transform);

private:
    bool fpsMode;
};
#endif
