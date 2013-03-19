#include "Level.h"
#include "LXGame.h"
#include "LXCamera.h"
#include "Player.h"
#include "LXInput.h"
#include "LXMatrix3D.h"

Level::Level(): LXGameState() {
  exampleEntity = new Player();
}

Level::~Level() {
  delete exampleEntity;
}

void Level::init() {
  LXGameState::init();
  exampleEntity->init();

  // Set up 3d view
  glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_LIGHT0);
  GLfloat diffuseLight[]={1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  GLfloat ambientLight[]={0.3, 0.3, 0.3, 1.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  light0Pos[0] = 25.0; light0Pos[1] = 25.0; 
  light0Pos[2] = 0.0; light0Pos[3] = 1.0;
  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

  glEnable(GL_COLOR_MATERIAL);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);
 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glFrustum(camera->viewVolume.xL, camera->viewVolume.xR,
            camera->viewVolume.yB, camera->viewVolume.yT,
            camera->viewVolume.N, camera-> viewVolume.F);

}

void Level::render() {
  LXGameState::render();

  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camera->eye->x, camera->eye->y, camera->eye->z,
        camera->look->x, camera->look->y, camera->look->z,
        camera->up->x, camera->up->y, camera->up->z);

  glBegin(GL_LINES);

  glColor3f(0.2, 0.7, 0.95);

  glVertex3f(0.f, 0.f, -6.f);
  glVertex3f(10.f, 0.f, -6.f);

  glVertex3f(0.f, 0.f, -6.f);
  glVertex3f(0.f, 10.f, -6.f);

  glVertex3f(0.f, 0.f, -6.f);
  glVertex3f(0.f, 0.f, 4.f);
  
  glEnd();

  exampleEntity->Render();
}
  
void Level::update() {
  LXGameState::update();

  if (game->input->specialKeyPressed(GLUT_KEY_LEFT)) {
    camera->translateX(-0.5);
  } else if (game->input->specialKeyPressed(GLUT_KEY_RIGHT)) {
    camera->translateX(0.5);
  }
  
  if (game->input->specialKeyPressed(GLUT_KEY_UP)) {
    camera->translateZ(-3.0);
  } else if (game->input->specialKeyPressed(GLUT_KEY_DOWN)) {
    camera->translateZ(3.0);
  }

  if (game->input->keyPressed('a')) {
    camera->rotate(2.0, 0, 0);
  } else if (game->input->keyPressed('d')) {
    camera->rotate(-2.0, 0, 0);
  }
  
  if (game->input->keyPressed('w')) {
    camera->rotate(0, 2.0, 0);
  } else if (game->input->keyPressed('s')) {
    camera->rotate(0, -2.0, 0);
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
