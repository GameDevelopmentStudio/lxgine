#include "Player.h"

#include "LXGlut.h"
#include "LXPoint3D.h"

#include "LXMesh.h"
#include "LXFace.h"

#include <stdio.h>
#include <math.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))


LXMesh *m;

int i = 0;

GLfloat gCubeVertexData[216] = 
{
    // Data layout for each line below is:
    // positionX, positionY, positionZ,     normalX, normalY, normalZ,
    0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f,          1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
    
    0.5f, 0.5f, -0.5f,         0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,         0.0f, 1.0f, 0.0f,
    
    -0.5f, 0.5f, -0.5f,        -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,        -1.0f, 0.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,       0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,         0.0f, -1.0f, 0.0f,
    
    0.5f, 0.5f, 0.5f,          0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,        0.0f, 0.0f, 1.0f,
    
    0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f,        0.0f, 0.0f, -1.0f
};

Player::Player() : LXEntity() {
  
}

Player::~Player() {
  /* glDeleteBuffers(1, &vertexBuffer); */
  /* glDeleteVertexArrays(1, &vertexArray); */
}

void Player::init() {
  LXEntity::init();

  m = new LXMesh();
  m->init(8, 16);
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
  
  // Tetrahedron 
  /* m->init(4, 4); */
  /* m->vertexPool[0] = LXPoint3D(0, 0, 0, 1); */
  /* m->vertexPool[1] = LXPoint3D(1, 0, 0, 1); */
  /* m->vertexPool[2] = LXPoint3D(0, 1, 0, 1); */
  /* m->vertexPool[3] = LXPoint3D(0, 0, 1, 1); */
 
  /* m->faces[0].init(3); */
  /* m->faces[0].vertexNormalPairs[0].vertex = 1; */
  /* m->faces[0].vertexNormalPairs[1].vertex = 2; */
  /* m->faces[0].vertexNormalPairs[2].vertex = 3; */
  
  /* m->faces[1].init(3); */
  /* m->faces[1].vertexNormalPairs[0].vertex = 3; */
  /* m->faces[1].vertexNormalPairs[1].vertex = 0; */
  /* m->faces[1].vertexNormalPairs[2].vertex = 1; */
  
  /* m->faces[1].init(3); */
  /* m->faces[1].vertexNormalPairs[0].vertex = 1; */
  /* m->faces[1].vertexNormalPairs[1].vertex = 0; */
  /* m->faces[1].vertexNormalPairs[2].vertex = 2; */

  /* m->faces[3].init(3); */
  /* m->faces[3].vertexNormalPairs[0].vertex = 2; */
  /* m->faces[3].vertexNormalPairs[1].vertex = 0; */
  /* m->faces[3].vertexNormalPairs[2].vertex = 3; */

  
  m->computeNormals();
  m->compile();
}

void Player::update() {
  // TODO: unhardcode this
  double idlation = 0.03*sin(0.1*i);
  translate(0, idlation, 0);
  i++;
}

void Player::render() {
  LXEntity::render();
  
  glColor3f(0.34, 0.32, 1.0);

  m->render();
  /* glEnableClientState(GL_NORMAL_ARRAY); */
  /* glEnableClientState(GL_VERTEX_ARRAY); */

  /* glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat), gCubeVertexData + 3); */
  /* glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), gCubeVertexData); */

  /* glDrawArrays(GL_TRIANGLES, 0, 36); */
  /* glDisableClientState(GL_VERTEX_ARRAY); */
  /* glDisableClientState(GL_NORMAL_ARRAY); */
}
