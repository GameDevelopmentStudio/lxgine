#include "Player.h"
#include "LXGlut.h"

Player::Player() : LXEntity() {
  
}

Player::~Player() {

}

void Player::init() {
  LXEntity::init();
}

void Player::render() {
  LXEntity::render();
  
  /* glColor3f(1.0, 1.0, 1.0); */
  
  // HARCODED TEST
  glRotatef(45, -1, 0, 0);
  glTranslatef(-1.5f,0.0f,0.0f);   // Move Left 1.5 Units And Into The Screen 6.0
  glNormal3f(0.0, 0.0, 1.0);
  // draw a triangle
  glBegin(GL_POLYGON);    // start drawing a polygon
  glVertex3f( 0.0f, 1.0f, 0.0f);  // Top
  glVertex3f( 1.0f,-1.0f, 0.0f);  // Bottom Right
  glVertex3f(-1.0f,-1.0f, 0.0f);  // Bottom Left  
  glEnd();      // we're done with the polygon

  glTranslatef(3.0f,0.0f,0.0f);       // Move Right 3 Units
  
  // draw a square (quadrilateral)
  glBegin(GL_QUADS);    // start drawing a polygon (4 sided)
  glVertex3f(-1.0f, 1.0f, 0.0f);  // Top Left
  glVertex3f( 1.0f, 1.0f, 0.0f);  // Top Right
  glVertex3f( 1.0f,-1.0f, 0.0f);  // Bottom Right
  glVertex3f(-1.0f,-1.0f, 0.0f);  // Bottom Left  
  glEnd();
}
