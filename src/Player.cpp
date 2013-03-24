#include "Player.h"

#include "LXGlut.h"
#include "LXPoint3D.h"


#include <stdio.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

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
  glDeleteBuffers(1, &vertexBuffer);
  glDeleteVertexArrays(1, &vertexArray);
}

void Player::init() {
  LXEntity::init();

  /* glGenVertexArrays(1, &vertexArray); */
  /* glBindVertexArray(vertexArray); */
  
  /* glGenBuffers(1, &vertexBuffer); */
  /* glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); */
  /* glBufferData(GL_ARRAY_BUFFER, sizeof(gCubeVertexData), gCubeVertexData, GL_STATIC_DRAW); */

  /* printf("%d", BUFFER_OFFSET(12)); */

  /* size_t colorDataOffset = sizeof(float) * 3; */

  /* glEnableVertexAttribArray(0); // pos */
  /* glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, colorDataOffset, 0); */
  /* glEnableVertexAttribArray(1);// normal */
  /* glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, colorDataOffset, (void*)colorDataOffset); */
  
  /* glBindVertexArray(0); */
  /* glBindBuffer(GL_ARRAY_BUFFER, 0); */
}

void Player::render() {
  LXEntity::render();
  
  glColor3f(0.34, 0.32, 1.0);


  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  /* glBindVertexArray(vertexArray); */

  glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat), gCubeVertexData + 3);
  glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), gCubeVertexData);

  glDrawArrays(GL_TRIANGLES, 0, 36);
  /* glBindVertexArray(0); */
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

  // HARCODED TEST
  /* glNormal3f(0.0, 0.0, 1.0); */
  /* glRotatef(45, -1, 0, 0); */
  /* glTranslatef(-1.5f,0.0f,0.0f);   // Move Left 1.5 Units And Into The Screen 6.0 */
  /* // draw a triangle */
  /* glBegin(GL_POLYGON);    // start drawing a polygon */
  /* glVertex3f( 0.0f, 1.0f, 0.0f);  // Top */
  /* glVertex3f( 1.0f,-1.0f, 0.0f);  // Bottom Right */
  /* glVertex3f(-1.0f,-1.0f, 0.0f);  // Bottom Left */  
  /* glEnd();      // we're done with the polygon */

  /* glTranslatef(3.0f,0.0f,0.0f);       // Move Right 3 Units */
  
  /* // draw a square (quadrilateral) */
  /* glBegin(GL_QUADS);    // start drawing a polygon (4 sided) */
  /* glVertex3f(-1.0f, 1.0f, 0.0f);  // Top Left */
  /* glVertex3f( 1.0f, 1.0f, 0.0f);  // Top Right */
  /* glVertex3f( 1.0f,-1.0f, 0.0f);  // Bottom Right */
  /* glVertex3f(-1.0f,-1.0f, 0.0f);  // Bottom Left */  
  /* glEnd(); */
}
