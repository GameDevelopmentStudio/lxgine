#include "Level.h"
#include "Game.h"
#include "Camera.h"
#include "Player.h"
#include "Input.h"
#include "Matrix44.h"

#include <time.h>
#include "Glut.h"

#include <iostream>
#include "Shader.h"

#include "Utils.h"
#include "TextureLoader.h"

#include "GrcPrimitives.h"

const char *diffuseTexFS = "engine/assets/shaders/diffuseTextureLighting.fsh";
const char *diffuseVS = "engine/assets/shaders/diffuseLighting.vsh";
const char *diffuseFS = "engine/assets/shaders/diffuseLighting.fsh";
const char *floorTexPath = "assets/textures/floortile.tga";

Level::Level(): GameState() {
    exampleEntity = new Player();
}

Level::~Level() {
    delete exampleEntity;
    delete floorProg;
    delete objProg;
    delete floorTex;
}

void Level::init() {
    GameState::init();

    // Set up 3d view
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_LIGHT0);
    GLfloat diffuseLight[]={1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    GLfloat ambientLight[]={0.3f, 0.3f, 0.3f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    light0Pos[0] = 0.0f; light0Pos[1] = 5.0f; 
    light0Pos[2] = -0.0f; light0Pos[3] = 1.0f;
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // TODO: refactor with camera params
    gluPerspective(60.0, 1.0, 1.0, 200.0);
    /* glFrustum(camera->viewVolume.xL, camera->viewVolume.xR, */
    /*                     camera->viewVolume.yB, camera->viewVolume.yT, */
    /*                     camera->viewVolume.N, camera-> viewVolume.F); */


    objProg = new Shader();
    objProg->init(diffuseVS, diffuseFS);
    floorProg = new Shader();
    floorProg->init(diffuseVS, diffuseTexFS);
    floorTex = TextureLoader::newTextureAtPath(floorTexPath);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
    
    exampleEntity->world = this;
    exampleEntity->game = this->game;
    exampleEntity->init();
}

void Level::render() {
    GameState::render();

    camera->commit();

    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    // Applies camera changes to the scene

    Col axisColor(0.2f, 0.7f, 0.95f, 0.7f);
    //ColExp1 axisColor1(0.2f, 0.7f, 0.95f, 0.7f);
    //ColExp2 axisColor2(0.2f, 0.7f, 0.95f, 0.7f);
    GrcPrimitives::segment(Vec3(0, 0, 0), Vec3(10, 0, 0), axisColor);
    GrcPrimitives::segment(Vec3(0, 0, 0), Vec3(0, 10, 0), axisColor);
    GrcPrimitives::segment(Vec3(0, 0, 0), Vec3(0, 0, 10), axisColor);
    
    GrcPrimitives::ray(exampleEntity->getTransform().getPosition(), exampleEntity->getTransform().getForward(), Col(1.0f, 1.0f, 1.0f, 1.0f));
    GrcPrimitives::ray(exampleEntity->getTransform().getPosition(), exampleEntity->getTransform().getRight(), Col(1.0f, 1.0f, 1.0f, 1.0f));
    GrcPrimitives::ray(exampleEntity->getTransform().getPosition(), exampleEntity->getTransform().getUp(), Col(1.0f, 1.0f, 1.0f, 1.0f));
    
    floorProg->enable();
    floorProg->bindTexture("tex", floorTex->index, GL_TEXTURE_2D, 0);
    GLfloat light0Color[]={1.0f, 1.0f, 0.8f};
    floorProg->setUniformfv("lightColor", light0Color, 3);
    glColor3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    {
        float s = 20.f;
        float rep = 20.f;
        glTexCoord2f(0.f, 0.f);
        glVertex3f(-s, -5, -s);
        glTexCoord2f(rep, 0.f);
        glVertex3f(s, -5.f, -s);
        glTexCoord2f(rep, rep);
        glVertex3f(s, -5.f, s);
        glTexCoord2f(0.f, rep);
        glVertex3f(-s, -5.f, s);
    }
    glEnd();
    floorProg->disable();

    objProg->enable();
    objProg->setUniformfv("lightColor", light0Color, 3);
    exampleEntity->Render();
    objProg->disable();
}
    
void Level::update() {
    GameState::update();

    if (game->input->keyPressed('v')) {
        if (camera->isLockedOn()) {
            camera->stopLock(exampleEntity);
        } else {
            camera->lockOn(exampleEntity, exampleEntity->getTransform());
        }
    }

    if (!camera->isLockedOn()) {
        if (game->input->specialKeyCheck(GLUT_KEY_LEFT)) {
            camera->translate(-0.5, 0, 0);
        } else if (game->input->specialKeyCheck(GLUT_KEY_RIGHT)) {
            camera->translate(0.5, 0, 0);
        }
        
        if (game->input->specialKeyCheck(GLUT_KEY_UP)) {
            camera->translate(0, 0, -0.5);
        } else if (game->input->specialKeyCheck(GLUT_KEY_DOWN)) {
            camera->translate(0, 0, 0.5);
        }

        if (game->input->keyCheck('a')) {
            camera->yaw(-0.05f);
        } else if (game->input->keyCheck('d')) {
            camera->yaw(0.05f);
        }
        
        if (game->input->keyCheck('w')) {
            camera->pitch(0.05f);
        } else if (game->input->keyCheck('s')) {
            camera->pitch(-0.05f);
        }
    }
    
    exampleEntity->update();
}
