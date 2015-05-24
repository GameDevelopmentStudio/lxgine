#ifndef __LOCABLE_H__
#define __LOCABLE_H__

class LockableTargetDelegate;

#include "Transform3D.h"

class LockableTarget {
public:
    LockableTarget() {};
    virtual ~LockableTarget() {};

    virtual void setDelegate(LockableTargetDelegate* delegate);
    virtual LockableTargetDelegate* getDelegate();

 protected:
    LockableTargetDelegate *delegate;
};

class LockableTargetDelegate {
public: 
    LockableTargetDelegate() {};
    virtual ~LockableTargetDelegate() {};

    virtual void lockOn(LockableTarget* target, const Transform& transform);
    virtual bool isLockedOn() = 0;
    virtual void stopLock(LockableTarget* target);
    virtual void targetDidRotate(LockableTarget* target, real rx, real ry, real rz) = 0;
    virtual void targetDidTranslate(LockableTarget* target, real tx, real ty, real tz) = 0;
    virtual void targetResetPosition(LockableTarget* target, const Transform& transform) = 0;
};

#endif
