#include "Entity.h"
#include "Matrix44.h"
#include "Vector4.h"
#include "Glut.h"

Entity::Entity() {
    game = NULL;
    world = NULL;

    pitch = yaw = roll = 0;
}

Entity::~Entity() {
}

void Entity::init() {
    transform.init();
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
        transform.commit();

        render();

    //pop
    glPopMatrix();
}

void Entity::translate(real tx, real ty, real tz) {
    transform.translate(tx, ty, tz);
    
    if (tx) {
        pos.getX() += tx;
    }
    if (ty) {
        pos.getY() += ty;
    }
    if (tz) {
        pos.getZ() += tz;
    }
}

void Entity::rotate(real rx, real ry, real rz) {

    if (ry == 0) {
        transform.rotate(-pitch, 0.0, 0.0);
        transform.rotate(rx, ry, rz);
        transform.rotate(pitch, 0.0, 0.0);
    } else {
        transform.rotate(rx, ry, rz);
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
}

const Vec4& Entity::getPos() const {
    return pos;
}

Vec4& Entity::getPos() {
    return pos;
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

const Transform Entity::getTransform() const {
    return transform;
}

Transform Entity::getTransform() {
    return transform;
}