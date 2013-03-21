#ifndef __LXCAMERA_H__
#define __LXCAMERA_H__

#include "LXPoint3D.h"

struct LXViewVolume {
    double N,F;
    double xR, xL;
    double yT, yB;
};

class LXCamera 
{
 public:
  LXViewVolume viewVolume;

  // Camera coordinates
  LXPoint3D lookAt, up, right;
  // Camera center
  LXPoint3D eye;
  // Distance to target
  double focalLength;

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
};

#endif
