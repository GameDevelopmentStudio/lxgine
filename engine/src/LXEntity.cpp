#include "LXEntity.h"
#include "LXMatrix3D.h"
#include "LXPoint3D.h"
#include "LXGlut.h"
#include "LXGame.h"

LXEntity::LXEntity() {
  // no camera has locked on this entity yet
  delegate = NULL;

  transform = new LXMatrix3D();
  pos = new LXPoint3D();
  pitch = yaw = roll = 0;
}

LXEntity::~LXEntity() {
  delete transform;
}

void LXEntity::init() {
  transform->init();

  if (delegate) {
    delegate->targetResetPosition(this, transform);
  }
}

void LXEntity::update() {

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

  if (delegate) {
    delegate->targetDidTranslate(this, tx, ty, tz);
  }
}

void LXEntity::rotate(double rx, double ry, double rz) {

  if (ry == 0) {
    transform->rotate(-pitch, 0.0, 0.0);
    transform->rotate(rx, ry, rz);
    transform->rotate(pitch, 0.0, 0.0);
  } else {
    transform->rotate(rx, ry, rz);
  }


  if (rx) {
    pitch += rx;
  }
  if (ry) {
    roll += ry;
  }
  if (rz) {
    yaw += rz;
  }
  
  if (delegate) {
    delegate->targetDidRotate(this, rx, ry, rz);
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

void LXEntity::setDelegate(LXLockableTargetDelegate *delegate) {
  LXLockableTarget::setDelegate(delegate);

  if (delegate) {
    delegate->targetResetPosition(this, transform);
  }
}
