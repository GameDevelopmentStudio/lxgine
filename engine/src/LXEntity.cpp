#include "LXEntity.h"
#include "LXMatrix3D.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

LXEntity::LXEntity() {
  transform = new LXMatrix3D();
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
