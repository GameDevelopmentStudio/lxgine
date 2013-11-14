#include "Entity.h"
#include "Matrix3D.h"
#include "Vector4.h"
#include "Glut.h"

Entity::Entity() {
    game = NULL;
    world = NULL;
    
    // no camera has locked on this entity yet
    delegate = NULL;

    transform = new Matrix3D();
    pos = new Vector4f();
    pitch = yaw = roll = 0;
}

Entity::~Entity() {
    delete transform;
    delete pos;
}

void Entity::init() {
    transform->init();

    if (delegate) {
        delegate->targetResetPosition(this, transform);
    }
}

void Entity::update() {

}

void Entity::render() {
}

void Entity::Render() {
    //push apply transform
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

        // Apply expected transforms
        transform->commit();

        render();

    //pop
    glPopMatrix();
}

void Entity::translate(float tx, float ty, float tz) {
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

void Entity::rotate(float rx, float ry, float rz) {

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

Vector4f Entity::getPos() {
    return Vector4f(*pos);
}

double Entity::getPitch() {
    return pitch;
}

double Entity::getYaw() {
    return yaw;
}

double Entity::getRoll() {
    return roll;
}

void Entity::setDelegate(LockableTargetDelegate *delegate) {
    LockableTarget::setDelegate(delegate);

    if (delegate) {
        delegate->targetResetPosition(this, transform);
    }
}
