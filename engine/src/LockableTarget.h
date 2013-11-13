#ifndef __LOCABLE_H__
#define __LOCABLE_H__

class LockableTargetDelegate;
class Matrix3D;
/* class Vector3; */

class LockableTarget {
public:
    LockableTarget() {};
    virtual ~LockableTarget() {};

    virtual void setDelegate(LockableTargetDelegate *delegate);
    virtual LockableTargetDelegate *getDelegate();

 protected:
    LockableTargetDelegate *delegate;
};

class LockableTargetDelegate {
public: 
    LockableTargetDelegate() {};
    virtual ~LockableTargetDelegate() {};

    virtual void lockOn(LockableTarget* target);
    virtual bool isLockedOn() = 0;
    virtual void stopLock(LockableTarget* target);
    virtual void targetDidRotate(LockableTarget *target, double rx, double ry, double rz) = 0;
    virtual void targetDidTranslate(LockableTarget *target, double tx, double ty, double tz) = 0;
    virtual void targetResetPosition(LockableTarget *target, const Matrix3D *transform) = 0;
};

#endif
