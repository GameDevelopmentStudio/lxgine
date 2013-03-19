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

  LXPoint3D *eye;
  LXPoint3D *look;
  LXPoint3D *up;
  
  LXCamera();
  ~LXCamera();

  void init();

  void translate(double x, double y, double z);
  void translateX(double x);
  void translateY(double y);
  void translateZ(double z);

  void rotate(double dx, double dy, double dz);
  void orbitate(double dx, double dy, double dz);
};

#endif
