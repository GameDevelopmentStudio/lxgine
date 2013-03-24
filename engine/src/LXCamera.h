#ifndef __LXCAMERA_H__
#define __LXCAMERA_H__

#include "LXLockableTarget.h"
#include "LXPoint3D.h"

class LXMatrix3D;

struct LXViewVolume {
    double N,F;
    double xR, xL;
    double yT, yB;
};

class LXCamera : public LXLockableTargetDelegate {
 public:
  LXViewVolume viewVolume;

  // Camera coordinates
  LXPoint3D lookAt, up, right;
  // Camera center
  LXPoint3D eye;
  // Distance to target
  double focalLength;

  // Lock on mode
  LXMatrix3D *targetInverseTransform;

  LXCamera();
  ~LXCamera();

  void init();

  LXPoint3D getTarget();

  void translate(double x, double y, double z);
  void translateX(double x);
  void translateY(double y);
  void translateZ(double z);

  void pitch(double alpha);
  void yaw(double alpha);
  void roll(double alpha);
  void orbitate(double rx, double ry);

  void commit();

  // LXLocableDelegateMethods
  virtual void lockOn(LXLockableTarget* target);
  virtual void targetDidRotate(LXLockableTarget *target, double rx, double ry, double rz);
  virtual void targetDidTranslate(LXLockableTarget *target, double tx, double ty, double tz);
  virtual void targetResetPosition(LXLockableTarget *target, const LXMatrix3D *transform);
};
#endif
