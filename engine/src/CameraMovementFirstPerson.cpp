#include "CameraMovementFirstPerson.h"

#include "Entity.h"
#include "Glut.h"
#include "Transform3D.h"

CameraMovementFirstPerson::CameraMovementFirstPerson() {
}

CameraMovementFirstPerson::~CameraMovementFirstPerson() {
}

void CameraMovementFirstPerson::followTarget(Entity* target) {
    this->target = target;
}

// Should be update!!
void CameraMovementFirstPerson::commit() {
    // If lockOn is activated, targetInverseTransform contains
    // the necessary transform to follow the target
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Transform3D<real> transform = target->getTransform().getAsArray().inverse();
    transform.commit();
}