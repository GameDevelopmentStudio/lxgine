#ifndef __LOCABLE_H__
#define __LOCABLE_H__

class LockableTargetDelegate;

#include "Matrix3D.h"

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
    virtual void targetDidRotate(LockableTarget *target, float rx, float ry, float rz) = 0;
    virtual void targetDidTranslate(LockableTarget *target, float tx, float ty, float tz) = 0;
    virtual void targetResetPosition(LockableTarget *target, const Matrix3D *transform) = 0;
};

#endif
