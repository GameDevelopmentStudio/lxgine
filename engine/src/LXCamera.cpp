#include "LXCamera.h"
#include "LXMatrix3D.h"
#include "LXGlut.h"

#include <math.h>
#include <iostream>

LXCamera::LXCamera() {
}

LXCamera::~LXCamera() {
}

void LXCamera::init() {
  eye.x = 100.0; eye.y = 100.0; 
  eye.z = 100.0; eye.v = 1;
  LXPoint3D target = LXPoint3D(0.0, 0.0, 0.0, 1);
  lookAt = eye - target;
  focalLength = lookAt.module();
  lookAt = normalizedVector(lookAt);
  up = normalizedVector(LXPoint3D(-100, 200, -100, 0));
  right = crossProduct(up, lookAt);

  viewVolume.N = 2;
  viewVolume.F = 10000;
  viewVolume.xR = 0.2;
  viewVolume.xL = -viewVolume.xR;
  viewVolume.yT = 0.2;
  viewVolume.yB = -viewVolume.yT;
}

LXPoint3D LXCamera::getTarget() {
  return eye - focalLength*lookAt;
}

void LXCamera::translate(double x, double y, double z) {

  LXPoint3D trans = LXPoint3D(x, y, z, 0.0);

  /* // first we get camera.eye system of coordinates */
  /* LXPoint3D n = eye - look; */
  /* n = normalizedVector(n); */

  /* LXPoint3D u = crossProduct(up, n); */
  /* LXPoint3D v = crossProduct(n, u); */

  // then we transform it (resulting matrix is kinda simple
  // so let's put the multiplication output here
  // notice how no eye vars appear here, that's because
  // desp is a vector and so desp.v is 0
  LXPoint3D desp = LXPoint3D(right.x*trans.x + up.x*trans.y + lookAt.x*trans.z,
                             right.y*trans.x + up.y*trans.y + lookAt.y*trans.z, right.z*trans.x + up.z*trans.y + lookAt.z*trans.z, 0); 
  eye = eye + desp;
}

void LXCamera::translateX(double x) {
  translate(x, 0.0, 0.0);
}

void LXCamera::translateY(double y) {
  translate(0.0, y, 0.0);
}

void LXCamera::translateZ(double z) {
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
 *    these transformations:
 *    
 *    - transform camera.target into camera.eye's system of coordinates
 *    - rotate transformed point in the desired axis (easier computation)
 *    - return transformed and rotated camera.target to global coordinates.
 *  
 *    See code history for this implementation
 *
 * 2. To rotate a camera point around an orbitrary axis, transform the
 *    correspondent vector (easier computation than rotating a point) around
 *    the desired axis. Then recompute the point with the newly rotated vector.
 *    This is the current implementation.
 */

void LXCamera::pitch(double alpha) {
  // Rotate lookAt vector around right vector
  LXMatrix3D pitch = matrixWithRotationOnAxis(alpha, right);
  // lookAt pitch modification implies changes on target point, 
  // and also on the up vector
  lookAt = transformPoint(pitch, lookAt);
  up = crossProduct(lookAt, right);
}

void LXCamera::yaw(double alpha) {
  // Rotate look over up-like vector
  // We don't rotate directly around the up vector, but on the projection
  // of the up vector agains the plane defined by the right vector and the 
  // vertical axis. This way the camera rotates as if it were standing on a
  // pole.

  // planeNormal is the normal vector of the plane
  LXPoint3D planeNormal = crossProduct(right, LXPoint3D(0,1,0,0));
  // v_axis is the projection of up agains the plane
  // v_axis is computed by substraction to up the projection of up in the 
  // planeNormalVector. Said projection has the same direction as planeNormal,
  // and scalarDot(placeNormal,up) as module (since we're dealing with 
  // normalized vectors, we can just multiply these values)
  LXPoint3D v_axis = up - scalarDot(planeNormal,up)*planeNormal;
  v_axis = normalizedVector(v_axis);

  // Rotate around the computed axis
  LXMatrix3D yaw = matrixWithRotationOnAxis(alpha, -v_axis);
  lookAt = transformPoint(yaw, lookAt);
  up = transformPoint(yaw, up);
  right = crossProduct(up, lookAt);
}

void LXCamera::roll(double alpha) {
  // Rotate up vector arount lookAt
  LXMatrix3D roll = matrixWithRotationOnAxis(alpha, lookAt);
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

void LXCamera::orbitate(double rx, double ry) {
  if (rx != 0) {
    // Yaw orbitation
    // See LXCamera::yaw for further explanation
    
    LXPoint3D target = getTarget();
    LXPoint3D planeNormal = crossProduct(right, LXPoint3D(0,1,0,0));
    LXPoint3D v_axis = up - scalarDot(planeNormal,up)*planeNormal;
    v_axis = normalizedVector(v_axis);

    // Rotate eye around the computed camera axis
    LXMatrix3D yaw = matrixWithRotationOnAxis(rx, v_axis);
    lookAt = transformPoint(yaw, lookAt);
    eye = target + focalLength*lookAt;
    up = transformPoint(yaw, up);
    right = crossProduct(up, lookAt);
  }
  if (ry != 0) {
    // Pitch orbitation
    // See LXCamera::Pitch for further explanation

    // Rotate eye vector around right vector
    LXMatrix3D pitch = matrixWithRotationOnAxis(ry, right);
    LXPoint3D target = getTarget();
    lookAt = transformPoint(pitch, lookAt);
    eye = target + focalLength*lookAt;
    up = crossProduct(lookAt, right);
  }
}

#pragma mark - Apply changes

void LXCamera::commit() {
  LXPoint3D target = getTarget();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye.x, eye.y, eye.z,
            target.x, target.y, target.z,
            up.x, up.y, up.z);
}
