#ifndef __LXENTITY_H__
#define __LXENTITY_H__

class LXMatrix3D;

class LXEntity {
 public:
  LXMatrix3D *transform;

 public:
  LXEntity();
  virtual ~LXEntity();

  virtual void init();
  virtual void render();
  
  virtual void Render();
};

#endif
