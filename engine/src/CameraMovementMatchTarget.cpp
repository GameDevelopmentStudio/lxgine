#include "CameraMovementMatchTarget.h"

#include "Entity.h"
#include "Glut.h"
#include "Transform3D.h"
#include "MathPrimitives.h"

CameraMovementMatchTarget::CameraMovementMatchTarget() {
}

CameraMovementMatchTarget::~CameraMovementMatchTarget() {
}

void CameraMovementMatchTarget::followAtOffset(Entity* target, Vec4 offset) {
    this->target = target;
    
    offsetFromTarget = offset;
    tiltAngleY = atan(offset.getX() / offset.getZ()) * kRadToDeg;
    tiltAngleX = atan(offset.getY() / offset.getZ()) * kRadToDeg;
}

void CameraMovementMatchTarget::followAtCenter(Entity* target) {
    this->target = target;
    
    offsetFromTarget.setZ(0.0);
}

// Should be update!!
void CameraMovementMatchTarget::commit() {
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (offsetFromTarget.getZ() != 0.0) {
        glRotated(tiltAngleY, 0, 1, 0);
        glRotated(tiltAngleX, 1, 0, 0);
        glTranslated(offsetFromTarget.getX(), offsetFromTarget.getY(), offsetFromTarget.getZ());
    }

    Transform3D<real> transform = target->getTransform().getAsArray().inverse();
    transform.commit();
}