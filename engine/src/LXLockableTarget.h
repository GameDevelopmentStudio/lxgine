#ifndef __LXLOCABLE_H__
#define __LXLOCABLE_H__

class LXLockableTargetDelegate;
class LXMatrix3D;
/* class LXPoint3D; */

class LXLockableTarget {
 public:
  LXLockableTarget() {};
  virtual ~LXLockableTarget() {};

  virtual void setDelegate(LXLockableTargetDelegate *delegate);
  virtual LXLockableTargetDelegate *getDelegate();

 protected:
  LXLockableTargetDelegate *delegate;
};

class LXLockableTargetDelegate {
 public: 
  LXLockableTargetDelegate() {};
  virtual ~LXLockableTargetDelegate() {};

  virtual void lockOn(LXLockableTarget* target);
  virtual bool isLockedOn() = 0;
  virtual void stopLock(LXLockableTarget* target);
  virtual void targetDidRotate(LXLockableTarget *target, double rx, double ry, double rz) = 0;
  virtual void targetDidTranslate(LXLockableTarget *target, double tx, double ty, double tz) = 0;
  virtual void targetResetPosition(LXLockableTarget *target, const LXMatrix3D *transform) = 0;
};

#endif
