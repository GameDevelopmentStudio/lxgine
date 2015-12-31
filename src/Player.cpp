#include "Player.h"

#include "Glut.h"
#include "Vector.h"
#include "Mesh.h"
#include "Face.h"
#include "GameState.h"
#include "Game.h"
#include "Camera.h"
#include "Input.h"

#include <stdio.h>
#include <math.h>

Mesh *m;

int i = 0;

Player::Player() : Entity() {
}

Player::~Player() {
}

void Player::init() {
    Entity::init();

    m = new Mesh();
    m->init(8, 12);
    m->vertexPool[0] = Vec4(-0.5, -0.5, -0.5, 1);
    m->vertexPool[1] = Vec4(-0.5, -0.5, 0.5, 1);
    m->vertexPool[2] = Vec4(-0.5, 0.5, -0.5, 1);
    m->vertexPool[3] = Vec4(-0.5, 0.5, 0.5, 1);
    m->vertexPool[4] = Vec4(0.5, -0.5, -0.5, 1);
    m->vertexPool[5] = Vec4(0.5, -0.5, 0.5, 1);
    m->vertexPool[6] = Vec4(0.5, 0.5, -0.5, 1);
    m->vertexPool[7] = Vec4(0.5, 0.5, 0.5, 1);
    
    m->faces[0].init(3);
    m->faces[0].vertexNormalPairs[0].vertex = 4;
    m->faces[0].vertexNormalPairs[1].vertex = 6;
    m->faces[0].vertexNormalPairs[2].vertex = 5;
    m->faces[1].init(3);
    m->faces[1].vertexNormalPairs[0].vertex = 5;
    m->faces[1].vertexNormalPairs[1].vertex = 6;
    m->faces[1].vertexNormalPairs[2].vertex = 7;

    m->faces[2].init(3);
    m->faces[2].vertexNormalPairs[0].vertex = 6;
    m->faces[2].vertexNormalPairs[1].vertex = 2;
    m->faces[2].vertexNormalPairs[2].vertex = 7;
    m->faces[3].init(3);
    m->faces[3].vertexNormalPairs[0].vertex = 7;
    m->faces[3].vertexNormalPairs[1].vertex = 2;
    m->faces[3].vertexNormalPairs[2].vertex = 3;

    m->faces[4].init(3);
    m->faces[4].vertexNormalPairs[0].vertex = 2;
    m->faces[4].vertexNormalPairs[1].vertex = 0;
    m->faces[4].vertexNormalPairs[2].vertex = 3;
    m->faces[5].init(3);
    m->faces[5].vertexNormalPairs[0].vertex = 3;
    m->faces[5].vertexNormalPairs[1].vertex = 0;
    m->faces[5].vertexNormalPairs[2].vertex = 1;

    m->faces[6].init(3);
    m->faces[6].vertexNormalPairs[0].vertex = 0;
    m->faces[6].vertexNormalPairs[1].vertex = 4;
    m->faces[6].vertexNormalPairs[2].vertex = 1;
    m->faces[7].init(3);
    m->faces[7].vertexNormalPairs[0].vertex = 1;
    m->faces[7].vertexNormalPairs[1].vertex = 4;
    m->faces[7].vertexNormalPairs[2].vertex = 5;

    m->faces[8].init(3);
    m->faces[8].vertexNormalPairs[0].vertex = 7;
    m->faces[8].vertexNormalPairs[1].vertex = 3;
    m->faces[8].vertexNormalPairs[2].vertex = 5;
    m->faces[9].init(3);
    m->faces[9].vertexNormalPairs[0].vertex = 5;
    m->faces[9].vertexNormalPairs[1].vertex = 3;
    m->faces[9].vertexNormalPairs[2].vertex = 1;

    m->faces[10].init(3);
    m->faces[10].vertexNormalPairs[0].vertex = 4;
    m->faces[10].vertexNormalPairs[1].vertex = 0;
    m->faces[10].vertexNormalPairs[2].vertex = 6;
    m->faces[11].init(3);
    m->faces[11].vertexNormalPairs[0].vertex = 6;
    m->faces[11].vertexNormalPairs[1].vertex = 0;
    m->faces[11].vertexNormalPairs[2].vertex = 2;
    
    m->computeNormals();
    m->compile();
}

void Player::update() {
    if (world->camera->GetCameraMovement()) {
        if (game->input->specialKeyCheck(GLUT_KEY_LEFT)) {
            translate(-0.5, 0, 0);
        } else if (game->input->specialKeyCheck(GLUT_KEY_RIGHT)) {
            translate(0.5, 0, 0);
        }
        
        if (game->input->specialKeyCheck(GLUT_KEY_UP)) {
            translate(0, 0, -0.5);
        } else if (game->input->specialKeyCheck(GLUT_KEY_DOWN)) {
            translate(0, 0, 0.5);
        }
        
        if (game->input->keyCheck('a')) {
            rotate(0, 0, 3.5f);
        } else if (game->input->keyCheck('d')) {
            rotate(0, 0, -3.5f);
        }
        
        if (game->input->keyCheck('w')) {
            rotate(3.5f, 0, 0);
        } else if (game->input->keyCheck('s')) {
            rotate(-3.5f, 0, 0);
        }
        
        if (game->input->keyCheck('y')) {
            rotate(2.0, 0, 0);
        } else if (game->input->keyCheck('u')) {
            rotate(-2.0, 0, 0);
        }
        
        if (game->input->keyCheck('i')) {
            rotate(0, 2.0, 0);
        } else if (game->input->keyCheck('o')) {
            rotate(0, -2.0, 0);
        }
        
        if (game->input->keyCheck('j')) {
            rotate(0, 0, 2.0);
        } else if (game->input->keyCheck('k')) {
            rotate(.0, 0, -2.0);
        }
    }

    // TODO: unhardcode this
    float idlation = 0.03f*sin(0.1f*i);
    translate(0, idlation, 0);
    i++;
}

void Player::render() {
    Entity::render();
    
    glColor3f(0.34f, 0.32f, 1.0f);

    m->render();
}
