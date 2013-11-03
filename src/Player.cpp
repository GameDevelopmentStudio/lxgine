#include "Player.h"

#include "LXGlut.h"
#include "LXPoint3D.h"
#include "LXMesh.h"
#include "LXFace.h"
#include "LXGameState.h"
#include "LXGame.h"
#include "LXCamera.h"
#include "LXInput.h"

#include <stdio.h>
#include <math.h>

GLuint vaoID2[1];
GLuint vboID2[1];
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

LXMesh *m;

int i = 0;

Player::Player() : LXEntity() {
}

Player::~Player() {
  /* glDeleteBuffers(1, &vertexBuffer); */
  /* glDeleteVertexArrays(1, &vertexArray); */
}

void Player::init() {
  LXEntity::init();

  m = new LXMesh();
  m->init(8, 12);
  m->vertexPool[0] = LXPoint3D(-0.5, -0.5, -0.5, 1);
  m->vertexPool[1] = LXPoint3D(-0.5, -0.5, 0.5, 1);
  m->vertexPool[2] = LXPoint3D(-0.5, 0.5, -0.5, 1);
  m->vertexPool[3] = LXPoint3D(-0.5, 0.5, 0.5, 1);
  m->vertexPool[4] = LXPoint3D(0.5, -0.5, -0.5, 1);
  m->vertexPool[5] = LXPoint3D(0.5, -0.5, 0.5, 1);
  m->vertexPool[6] = LXPoint3D(0.5, 0.5, -0.5, 1);
  m->vertexPool[7] = LXPoint3D(0.5, 0.5, 0.5, 1);
  
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
  if (world->camera->isLockedOn()) {
    if (game->input->specialKeyPressed(GLUT_KEY_LEFT)) {
      translate(-0.5, 0, 0);
    } else if (game->input->specialKeyPressed(GLUT_KEY_RIGHT)) {
      translate(0.5, 0, 0);
    }
    
    if (game->input->specialKeyPressed(GLUT_KEY_UP)) {
      translate(0, 0, -0.5);
    } else if (game->input->specialKeyPressed(GLUT_KEY_DOWN)) {
      translate(0, 0, 0.5);
    }
    
    if (game->input->keyPressed('a')) {
      rotate(0, 0, 3.5f);
    } else if (game->input->keyPressed('d')) {
      rotate(0, 0, -3.5f);
    }
    
    if (game->input->keyPressed('w')) {
      rotate(3.5f, 0, 0);
    } else if (game->input->keyPressed('s')) {
      rotate(-3.5f, 0, 0);
    }
    
    if (game->input->keyPressed('y')) {
      rotate(2.0, 0, 0);
    } else if (game->input->keyPressed('u')) {
      rotate(-2.0, 0, 0);
    }
    
    if (game->input->keyPressed('i')) {
      rotate(0, 2.0, 0);
    } else if (game->input->keyPressed('o')) {
      rotate(0, -2.0, 0);
    }
    
    if (game->input->keyPressed('j')) {
      rotate(0, 0, 2.0);
    } else if (game->input->keyPressed('k')) {
      rotate(.0, 0, -2.0);
    }
    
    if (game->input->keyPressed('p')) {
      world->camera->toggleFPS();
    }
  }

  // TODO: unhardcode this
  double idlation = 0.03*sin(0.1*i);
  translate(0, idlation, 0);
  i++;
}

void Player::render() {
  LXEntity::render();
  
  glColor3f(0.34, 0.32, 1.0);

  m->render();
}
