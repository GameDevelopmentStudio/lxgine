#include "Level.h"
#include "LXGame.h"
#include "LXCamera.h"
#include "Player.h"
#include "LXInput.h"
#include "LXMatrix3D.h"

#include <time.h>
#include "LXGlut.h"

#include <iostream>
#include "LXShader.h"

#include "LXUtils.h"
#include "LXTexture.h"

const char *floorVS = "engine/assets/shaders/diffuseTextureLighting.vsh";
const char *floorPS = "engine/assets/shaders/diffuseTextureLighting.fsh";
const char *floorTexPath = "assets/textures/floortile.ppm";

Level::Level(): LXGameState() {
  exampleEntity = new Player();
}

Level::~Level() {
  delete exampleEntity;
  delete floorProg;
}

void Level::init() {
  LXGameState::init();
  exampleEntity->init();

  // Set up 3d view
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_LIGHT0);
  GLfloat diffuseLight[]={1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  GLfloat ambientLight[]={0.3, 0.3, 0.3, 1.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  light0Pos[0] = 10.0; light0Pos[1] = 5.0; 
  light0Pos[2] = -5.0; light0Pos[3] = 1.0;
  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

  glEnable(GL_COLOR_MATERIAL);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);
 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60.0, 1.0, 1.0, 200.0);

  /* glFrustum(camera->viewVolume.xL, camera->viewVolume.xR, */
  /*           camera->viewVolume.yB, camera->viewVolume.yT, */
  /*           camera->viewVolume.N, camera-> viewVolume.F); */


  floorProg = new LXShader();
  floorProg->init(floorVS, floorPS);
  floorTex = loadTexture(floorTexPath);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
}

void Level::render() {
  LXGameState::render();

  camera->commit();

  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
  // Applies camera changes to the scene

  glBegin(GL_LINES);

  glColor3f(0.2, 0.7, 0.95);

  glVertex3f(0.f, 0.f, -6.f);
  glVertex3f(10.f, 0.f, -6.f);

  glVertex3f(0.f, 0.f, -6.f);
  glVertex3f(0.f, 10.f, -6.f);

  glVertex3f(0.f, 0.f, -6.f);
  glVertex3f(0.f, 0.f, 4.f);
  
  glEnd();

  floorProg->enable();
  floorProg->bindTexture("tex", floorTex, GL_TEXTURE_2D, 0);
  GLfloat light0Color[]={1.0, 1.0, 0.8};
  floorProg->setUniformfv("lightColor", light0Color, 3);
  glColor3f(1.0, 1.0, 1.0);
  glNormal3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  {
      float s = 20.f;
      float rep = 20.f;
      glTexCoord2f(0.f, 0.f);
      glVertex3f(-s, -5, -s);
      glTexCoord2f(rep, 0.f);
      glVertex3f(s, -5, -s);
      glTexCoord2f(rep, rep);
      glVertex3f(s, -5, s);
      glTexCoord2f(0.f, rep);
      glVertex3f(-s, -5, s);
  }
  glEnd();
  floorProg->disable();

  exampleEntity->Render();
  
}
  
void Level::update() {
  LXGameState::update();

  if (game->input->specialKeyPressed(GLUT_KEY_LEFT)) {
    camera->translateX(-0.2);
  } else if (game->input->specialKeyPressed(GLUT_KEY_RIGHT)) {
    camera->translateX(0.2);
  }
  
  if (game->input->specialKeyPressed(GLUT_KEY_UP)) {
    camera->translateZ(-1.0);
      /* glMatrixMode(GL_MODELVIEW); */
      /* glTranslated(1.0, 0, 1.0); */
  
  } else if (game->input->specialKeyPressed(GLUT_KEY_DOWN)) {
    camera->translateZ(1.0);
  }

  if (game->input->keyPressed('a')) {
    camera->yaw(-0.05);
  } else if (game->input->keyPressed('d')) {
    camera->yaw(0.05);
  }
  
  if (game->input->keyPressed('w')) {
    camera->pitch(0.05);
  } else if (game->input->keyPressed('s')) {
    camera->pitch(-0.05);
  }

  if (game->input->keyPressed('y')) {
    exampleEntity->transform->rotate(2.0, 0, 0);
  } else if (game->input->keyPressed('u')) {
    exampleEntity->transform->rotate(-2.0, 0, 0);
  }

  if (game->input->keyPressed('i')) {
    exampleEntity->transform->rotate(0, 2.0, 0);
  } else if (game->input->keyPressed('o')) {
    exampleEntity->transform->rotate(0, -2.0, 0);
  }

  if (game->input->keyPressed('j')) {
    exampleEntity->transform->rotate(0, 0, 2.0);
  } else if (game->input->keyPressed('k')) {
    exampleEntity->transform->rotate(.0, 0, -2.0);
  }  
}
