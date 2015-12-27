#include "Camera.h"
#include "Glut.h"
#include "Entity.h"

#include <math.h>
#include <iostream>
LockableTarget *target2;
Camera::Camera() {
    targetInverseTransform = NULL;
}

Camera::~Camera() {
    if (targetInverseTransform) {
        delete targetInverseTransform;
    }
}

void Camera::init() {
    eye.getX() = 10.0; eye.getY() = 10.0;
    eye.getZ() = 10.0; eye.getW() = 1;
    Vec4 target = Vec4(0.0, 0.0, 0.0, 1);
    lookAt = eye - target;
    focalLength = lookAt.module();
    lookAt = normalizedVector(lookAt);
    up = Vec4(0.0, 1.0, 0.0, 0.0);
    right = crossProduct(up, lookAt);

    viewVolume.N = 2;
    viewVolume.F = 10000;
    viewVolume.xR = 0.2f;
    viewVolume.xL = -viewVolume.xR;
    viewVolume.yT = 0.2f;
    viewVolume.yB = -viewVolume.yT;

    fpsMode = false;

    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

Vec4 Camera::getTarget() {
    return eye - focalLength*lookAt;
}

void Camera::translate(real x, real y, real z) {

    Vec4 trans = Vec4(x, y, z, 0.0);

    /* // first we get camera.eye system of coordinates */
    /* Vec4 n = eye - look; */
    /* n = normalizedVector(n); */

    /* Vec4 u = crossProduct(up, n); */
    /* Vec4 v = crossProduct(n, u); */

    // then we transform it (resulting matrix is kinda simple
    // so let's put the multiplication output here
    // notice how no eye vars appear here, that's because
    // desp is a vector and so desp.v is 0
    Vec4 desp = Vec4(right.getX()*trans.getX() + up.getX()*trans.getY() + lookAt.getX()*trans.getZ(),
                     right.getY()*trans.getX() + up.getY()*trans.getY() + lookAt.getY()*trans.getZ(),
                     right.getZ()*trans.getX() + up.getZ()*trans.getY() + lookAt.getZ()*trans.getZ(), 0);
    eye = eye + desp;
}

void Camera::translateX(real x) {
    translate(x, 0.0, 0.0);
}

void Camera::translateY(real y) {
    translate(0.0, y, 0.0);
}

void Camera::translateZ(real z) {
    translate(0.0, 0.0, z);
}

// Rotations

/**
 * Some notes about rotations:
 *
 * Rotations can be achieved in several ways. Some of the ones implemented here
 * (present or past) are:
 *
 * 1. To rotate a camera point (i.e., target) around an orbitrary axis, perform 
 *        these transformations:
 *        
 *        - transform camera.target into camera.eye's system of coordinates
 *        - rotate transformed point in the desired axis (easier computation)
 *        - return transformed and rotated camera.target to global coordinates.
 *    
 *        See code history for this implementation
 *
 * 2. To rotate a camera point around an orbitrary axis, transform the
 *        correspondent vector (easier computation than rotating a point) around
 *        the desired axis. Then recompute the point with the newly rotated vector.
 *        This is the current implementation.
 */

void Camera::pitch(real alpha) {
    // Rotate lookAt vector around right vector
    Mat44 pitch = matrixWithRotationOnAxis(alpha, right);
    // lookAt pitch modification implies changes on target point, 
    // and also on the up vector
    lookAt = pitch * lookAt;
    up = crossProduct(lookAt, right);
}

void Camera::yaw(real alpha) {
    // Rotate look over up-like vector
    // We don't rotate directly around the up vector, but on the projection
    // of the up vector agains the plane defined by the right vector and the 
    // vertical axis. This way the camera rotates as if it were standing on a
    // pole.

    // planeNormal is the normal vector of the plane
    Vec4 planeNormal = crossProduct(right, Vec4(0,1,0,0));
    // v_axis is the projection of up agains the plane
    // v_axis is computed by substraction to up the projection of up in the 
    // planeNormalVector. Said projection has the same direction as planeNormal,
    // and scalarDot(placeNormal,up) as module (since we're dealing with 
    // normalized vectors, we can just multiply these values)
    Vec4 v_axis = up - scalarDot(planeNormal,up)*planeNormal;
    v_axis = normalizedVector(v_axis);

    // Rotate around the computed axis
    Mat44 yaw = matrixWithRotationOnAxis(alpha, -v_axis);
    /* Mat44 yaw = matrixWithRotationOnAxis(alpha, up); */
    lookAt = yaw * lookAt;
    up = yaw * up;
    right = crossProduct(up, lookAt);
}

void Camera::roll(real alpha) {
    // Rotate up vector arount lookAt
    Mat44 roll = matrixWithRotationOnAxis(alpha, lookAt);
    // Only up and right vectors are modified after the operation
    up = roll * up;
    right = crossProduct(up, lookAt);
}

// Rotations

/**
 * Orbitations are similar to rotations, except eye is changed instead
 * of target.
 *
 * Notice there is no roll in orbitations, as it's the same as in rotations.
 */

void Camera::orbitate(real rx, real ry) {
    if (rx != 0) {
        // Yaw orbitation
        // See Camera::yaw for further explanation
        
        Vec4 target = getTarget();
        Vec4 planeNormal = crossProduct(right, Vec4(0,1,0,0));
        Vec4 v_axis = up - scalarDot(planeNormal,up)*planeNormal;
        v_axis = normalizedVector(v_axis);

        // Rotate eye around the computed camera axis
        Mat44 yaw = matrixWithRotationOnAxis(rx, v_axis);
        lookAt = yaw * lookAt;
        eye = target + focalLength*lookAt;
        up = yaw * up;
        right = crossProduct(up, lookAt);
    }
    if (ry != 0) {
        // Pitch orbitation
        // See Camera::Pitch for further explanation

        // Rotate eye vector around right vector
        Mat44 pitch = matrixWithRotationOnAxis(ry, right);
        Vec4 target = getTarget();
        lookAt = pitch * lookAt;
        eye = target + focalLength*lookAt;
        up = crossProduct(lookAt, right);
    }
}

// LockableTargetDelegate Methods

void Camera::lockOn(LockableTarget* target, const Transform& transform) {
    targetInverseTransform = new Transform();
    
    // Init position
    target2 = target;
    *targetInverseTransform = transform.getAsArray().inverse();
    LockableTargetDelegate::lockOn(target, transform);
}

bool Camera::isLockedOn() {
    return targetInverseTransform != NULL;
}

void Camera::stopLock(LockableTarget* target) {
    if (isLockedOn()) {
        delete targetInverseTransform;
        targetInverseTransform = NULL;

        LockableTargetDelegate::stopLock(target);
    }
}

void Camera::targetDidRotate(LockableTarget *target, real rx, real ry, real rz) {return;

    if (ry == 0) {
        targetInverseTransform->rotate(((Entity *) target)->pitch, 0.0f, 0.0f, false);
        targetInverseTransform->rotate(-rx, -ry, -rz, false);
        targetInverseTransform->rotate(-((Entity *) target)->pitch, 0.0f, 0.0f, false);
    } else {
        targetInverseTransform->rotate(-rx, -ry, -rz, false);
    }

    /* targetInverseTransform->rotate(-rx, -ry, -rz, false); */
}

void Camera::targetDidTranslate(LockableTarget *target, real tx, real ty, real tz) {return;
    targetInverseTransform->translate(-tx, -ty, -tz, false);
}

void Camera::targetResetPosition(LockableTarget* target, const Transform& transform) {return;
    targetInverseTransform->setMatrix(transform.getAsArray().inverse());
}

void Camera::toggleFPS() {
    fpsMode = !fpsMode;
}

// Apply changes

void Camera::commit() {
    Mat44 transform;
    glGetFloatv(GL_MODELVIEW_MATRIX, transform.getAsArray());
    if (targetInverseTransform) {
        // If lockOn is activated, targetInverseTransform contains
        // the necessary transform to follow the target
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    
        if (!fpsMode) {
            glRotated(45, 1, 0, 0);
            glTranslated(0, -5, -5);
        }
        *targetInverseTransform = ((Entity *) target2)->getTransform().getAsArray().inverse();
        targetInverseTransform->commit();
    } else {
        // If mode is not lockOn, set up view with our coordinates
        // TODO: update our coordinates during lockOn
        Vec4 target = getTarget();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye.getX(), eye.getY(), eye.getZ(),
                  target.getX(), target.getY(), target.getZ(),
                  up.getX(), up.getY(), up.getZ());
    }
}
