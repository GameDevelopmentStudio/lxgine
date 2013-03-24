#include "LXEntity.h"
#include "LXMatrix3D.h"
#include "LXPoint3D.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

LXEntity::LXEntity() {
  transform = new LXMatrix3D();
  pos = new LXPoint3D();
  pitch = yaw = roll = 0;
}

LXEntity::~LXEntity() {
  delete transform;
}

void LXEntity::init() {
  transform->init();
}

void LXEntity::render() {
}

void LXEntity::Render() {
  //push apply transform
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

    // Apply expected transforms
    transform->commit();

    render();

  //pop
  glPopMatrix();
}

void LXEntity::translate(double tx, double ty, double tz) {
  transform->translate(tx, ty, tz);
  
  if (tx) {
    pos->x += tx;
  }
  if (ty) {
    pos->y += ty;
  }
  if (tz) {
    pos->z += tz;
  }
}

void LXEntity::rotate(double rx, double ry, double rz) {
  transform->rotate(rx, ry, rz);

  if (rx) {
    pitch += rx;
  }
  if (ry) {
    yaw += ry;
  }
  if (rz) {
    roll += rz;
  }
}

LXPoint3D LXEntity::getPos() {
  return LXPoint3D(*pos);
}

double LXEntity::getPitch() {
  return pitch;
}

double LXEntity::getYaw() {
  return yaw;
}

double LXEntity::getRoll() {
  return roll;
}

