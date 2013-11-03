#include "Camera.h"
#include "Point3D.h"
#include "Matrix3D.h"
#include "Glut.h"
#include "Entity.h"

#include <math.h>
#include <iostream>

Camera::Camera() {
    targetInverseTransform = NULL;
}

Camera::~Camera() {
    if (targetInverseTransform)
        delete targetInverseTransform;
}

void Camera::init() {
    eye.x = 10.0; eye.y = 10.0; 
    eye.z = 10.0; eye.v = 1;
    Point3D target = Point3D(0.0, 0.0, 0.0, 1);
    lookAt = eye - target;
    focalLength = lookAt.module();
    lookAt = normalizedVector(lookAt);
    up = normalizedVector(Point3D(-100, 200, -100, 0));
    /* up = Point3D(0,1,0,0); */
    right = crossProduct(up, lookAt);

    viewVolume.N = 2;
    viewVolume.F = 10000;
    viewVolume.xR = 0.2;
    viewVolume.xL = -viewVolume.xR;
    viewVolume.yT = 0.2;
    viewVolume.yB = -viewVolume.yT;

    fpsMode = false;

    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

Point3D Camera::getTarget() {
    return eye - focalLength*lookAt;
}

void Camera::translate(double x, double y, double z) {

    Point3D trans = Point3D(x, y, z, 0.0);

    /* // first we get camera.eye system of coordinates */
    /* Point3D n = eye - look; */
    /* n = normalizedVector(n); */

    /* Point3D u = crossProduct(up, n); */
    /* Point3D v = crossProduct(n, u); */

    // then we transform it (resulting matrix is kinda simple
    // so let's put the multiplication output here
    // notice how no eye vars appear here, that's because
    // desp is a vector and so desp.v is 0
    Point3D desp = Point3D(right.x*trans.x + up.x*trans.y + lookAt.x*trans.z,
                                                         right.y*trans.x + up.y*trans.y + lookAt.y*trans.z, right.z*trans.x + up.z*trans.y + lookAt.z*trans.z, 0); 
    eye = eye + desp;
}

void Camera::translateX(double x) {
    translate(x, 0.0, 0.0);
}

void Camera::translateY(double y) {
    translate(0.0, y, 0.0);
}

void Camera::translateZ(double z) {
    translate(0.0, 0.0, z);
}

# pragma mark - Rotations

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

void Camera::pitch(double alpha) {
    // Rotate lookAt vector around right vector
    Matrix3D pitch = matrixWithRotationOnAxis(alpha, right);
    // lookAt pitch modification implies changes on target point, 
    // and also on the up vector
    lookAt = transformPoint(pitch, lookAt);
    up = crossProduct(lookAt, right);
}

void Camera::yaw(double alpha) {
    // Rotate look over up-like vector
    // We don't rotate directly around the up vector, but on the projection
    // of the up vector agains the plane defined by the right vector and the 
    // vertical axis. This way the camera rotates as if it were standing on a
    // pole.

    // planeNormal is the normal vector of the plane
    Point3D planeNormal = crossProduct(right, Point3D(0,1,0,0));
    // v_axis is the projection of up agains the plane
    // v_axis is computed by substraction to up the projection of up in the 
    // planeNormalVector. Said projection has the same direction as planeNormal,
    // and scalarDot(placeNormal,up) as module (since we're dealing with 
    // normalized vectors, we can just multiply these values)
    Point3D v_axis = up - scalarDot(planeNormal,up)*planeNormal;
    v_axis = normalizedVector(v_axis);

    // Rotate around the computed axis
    Matrix3D yaw = matrixWithRotationOnAxis(alpha, -v_axis);
    /* Matrix3D yaw = matrixWithRotationOnAxis(alpha, up); */
    lookAt = transformPoint(yaw, lookAt);
    up = transformPoint(yaw, up);
    right = crossProduct(up, lookAt);
}

void Camera::roll(double alpha) {
    // Rotate up vector arount lookAt
    Matrix3D roll = matrixWithRotationOnAxis(alpha, lookAt);
    // Only up and right vectors are modified after the operation
    up = transformPoint(roll, up);
    right = crossProduct(up, lookAt);
}

# pragma mark - Rotations

/**
 * Orbitations are similar to rotations, except eye is changed instead
 * of target.
 *
 * Notice there is no roll in orbitations, as it's the same as in rotations.
 */

void Camera::orbitate(double rx, double ry) {
    if (rx != 0) {
        // Yaw orbitation
        // See Camera::yaw for further explanation
        
        Point3D target = getTarget();
        Point3D planeNormal = crossProduct(right, Point3D(0,1,0,0));
        Point3D v_axis = up - scalarDot(planeNormal,up)*planeNormal;
        v_axis = normalizedVector(v_axis);

        // Rotate eye around the computed camera axis
        Matrix3D yaw = matrixWithRotationOnAxis(rx, v_axis);
        lookAt = transformPoint(yaw, lookAt);
        eye = target + focalLength*lookAt;
        up = transformPoint(yaw, up);
        right = crossProduct(up, lookAt);
    }
    if (ry != 0) {
        // Pitch orbitation
        // See Camera::Pitch for further explanation

        // Rotate eye vector around right vector
        Matrix3D pitch = matrixWithRotationOnAxis(ry, right);
        Point3D target = getTarget();
        lookAt = transformPoint(pitch, lookAt);
        eye = target + focalLength*lookAt;
        up = crossProduct(lookAt, right);
    }
}

#pragma mark - LockableTargetDelegate Methods

void Camera::lockOn(LockableTarget* target) {
    targetInverseTransform = new Matrix3D();

    LockableTargetDelegate::lockOn(target);
}

bool Camera::isLockedOn() {
    return targetInverseTransform;
}

void Camera::stopLock(LockableTarget* target) {
    if (isLockedOn()) {
        delete targetInverseTransform;
        targetInverseTransform = NULL;

        LockableTargetDelegate::stopLock(target);
    }
}

void Camera::targetDidRotate(LockableTarget *target, double rx, double ry, double rz) {

    if (ry == 0) {
        targetInverseTransform->rotate(((Entity *) target)->pitch, 0.0, 0.0, false);
        targetInverseTransform->rotate(-rx, -ry, -rz, false);
        targetInverseTransform->rotate(-((Entity *) target)->pitch, 0.0, 0.0, false);
    } else {
        targetInverseTransform->rotate(-rx, -ry, -rz, false);
    }

    /* targetInverseTransform->rotate(-rx, -ry, -rz, false); */
}

void Camera::targetDidTranslate(LockableTarget *target, double tx, double ty, double tz) {
    targetInverseTransform->translate(-tx, -ty, -tz, false);
}

void Camera::targetResetPosition(LockableTarget *target, const Matrix3D *transform) {
    *targetInverseTransform = transform->inverse();
}

void Camera::toggleFPS() {
    fpsMode = !fpsMode;
}

#pragma mark - Apply changes

void Camera::commit() {
    if (targetInverseTransform) {
        // If lockOn is activated, targetInverseTransform contains
        // the necessary transform to follow the target
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    
        if (!fpsMode) {
            glRotated(45, 1, 0, 0);
            glTranslated(0, -5, -5);
        }
        targetInverseTransform->commit();
    } else {
        // If mode is not lockOn, set up view with our coordinates
        // TODO: update our coordinates during lockOn
        Point3D target = getTarget();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye.x, eye.y, eye.z,
                            target.x, target.y, target.z,
                            up.x, up.y, up.z);
    }
}
