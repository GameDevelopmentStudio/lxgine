#include "Level.h"
#include "Game.h"
#include "Camera.h"
#include "CameraMovementFirstPerson.h"
#include "CameraMovementMatchTarget.h"
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

#include "BitSet.h"

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
    delete cameraMovement3rdPerson;
    delete cameraMovement1stPerson;
}

void Level::init() {
    GameState::init();

    // Set up 3d view
//    glClearColor(0.9f, 0.85f, 1.0f, 1.0f);
    glClearColor(0.009f, 0.0085f, 0.0f, 1.0f);
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

    // Camera
    CameraLens::Perspective& perspective = camera->cameraLens.setFrustrumWithPerspective();
    perspective.fov = 60.0;
    perspective.aspect = 1.0;
    perspective.N = 1.0;
    perspective.F = 200.0;
    camera->eye = Vec4(10.0, 10.0, 10.0, 1.0);
    camera->lookAtPosition(Vec4(0.0, 0.0, 0.0, 1.0));
    camera->init();

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
    
    // Cameras
    cameraMovement3rdPerson = new CameraMovementMatchTarget();
    cameraMovement3rdPerson->followAtOffset(exampleEntity, Vec4(0.0, -5.0, -5.0));
    
    cameraMovement1stPerson = new CameraMovementFirstPerson();
    cameraMovement1stPerson->followTarget(exampleEntity);

    // TODO: not really working
//    BitSet32 bitset;
//    bitset.set(1<<2, true);
//    bitset.set(1<<0, true);
//    bitset.set(1<<3, true);
//    bitset.set(1<<0, false);
//    if (bitset.get(1<<2)) {
//        bitset.set(1<<2, false);
//        if (bitset.get(1<<2)) {
//            printf("hi");
//        }
//    }
    
    Vec4 boxCenter(1.0, 10.0, 1.0, 1.0);
    Vec4 offset(10.0, 10.0, 10.0, 0.0);
    particleGenerator.init(boxCenter, offset);
    particleSystem.particleEmitter.addGenerator(particleGenerator);
    
    eulerParticleUpdater.globalAcceleration = Vec4(0.0, 0.40, 0.0, 0.0);
    particleSystem.addUpdater(eulerParticleUpdater);
    
    attractorParticleUpdater.attractorCenter = Vec4(0.0, 10.0, 0.0, 0.0);
    attractorParticleUpdater.distanceThreshold = 15.0;
    attractorParticleUpdater.maxAttractionForce = 0.5;
    attractorParticleUpdater.radius = 2.0;
    particleSystem.addUpdater(attractorParticleUpdater);
}

void Level::render() {
    GameState::render();

    camera->commit();

    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    // Applies camera changes to the scene

    /*Col axisX(0.8f, 0.15f, 0.25f, 0.7f);
    Col axisY(0.25f, 0.8f, 0.15f, 0.7f);
    Col axisZ(0.15f, 0.25f, 0.8f, 0.7f);
    GrcPrimitives::segment(Vec3(0, 0, 0), Vec3(10, 0, 0), axisX);
    GrcPrimitives::segment(Vec3(0, 0, 0), Vec3(0, 10, 0), axisY);
    GrcPrimitives::segment(Vec3(0, 0, 0), Vec3(0, 0, 10), axisZ);
    
    GrcPrimitives::ray(exampleEntity->getTransform().getPosition(), exampleEntity->getTransform().getForward(), axisZ);
    GrcPrimitives::ray(exampleEntity->getTransform().getPosition(), exampleEntity->getTransform().getRight(), axisX);
    GrcPrimitives::ray(exampleEntity->getTransform().getPosition(), exampleEntity->getTransform().getUp(), axisY);
    */
    
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

    //objProg->enable();
    //objProg->setUniformfv("lightColor", light0Color, 3);
    //exampleEntity->Render();
    //objProg->disable();
    
    particleSystem.render();
}
    
void Level::update() {
    GameState::update();

    if (game->input->keyPressed('v')) {
        if (camera->GetCameraMovement()) {
            camera->SetCameraMovement(NULL);
        } else {
            camera->SetCameraMovement(cameraMovement3rdPerson);
        }
    }

    if (!camera->GetCameraMovement()) {
        // Manually move the camera
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
        
        if (game->input->keyCheck('o')) {
            camera->translate(0, 0.5, 0);
        } else if (game->input->keyCheck('l')) {
            camera->translate(0, -0.5, 0);
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
    else {
        // Toggle FPS
        if (game->input->keyPressed('p')) {
            if (camera->GetCameraMovement() == cameraMovement3rdPerson) {
                camera->SetCameraMovement(cameraMovement1stPerson);
            } else {
                camera->SetCameraMovement(cameraMovement3rdPerson);
            }
        }
    }
    
    //exampleEntity->update();
    
    particleSystem.update(0.16);
}
