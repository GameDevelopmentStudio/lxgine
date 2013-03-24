#ifndef __LXENTITY_H__
#define __LXENTITY_H__

#include "LXLockableTarget.h"

class LXMatrix3D;
class LXPoint3D;

class LXEntity : public LXLockableTarget {
 public:
  LXEntity();
  virtual ~LXEntity();

  virtual void init();
  virtual void render();
  
  virtual void Render();

  virtual void translate(double tx, double ty, double tz);
  virtual void rotate(double rx, double ry, double rz);

  LXPoint3D getPos();
  double getPitch();
  double getYaw();
  double getRoll();

  // LXLockableTarget
  virtual void setDelegate(LXLockableTargetDelegate *delegate);

 protected:
  LXPoint3D *pos;
  double pitch, yaw, roll;
  
  LXMatrix3D *transform;
};

#endif
