#include "ParticlePointRenderer.h"
#include "ParticleData.h"
#include "Glut.h"

ParticlePointRenderer::ParticlePointRenderer() {
}

ParticlePointRenderer::~ParticlePointRenderer() {
    
}

void ParticlePointRenderer::render(ParticleData& particles) const {
    glBegin(GL_LINES);
    glColor4f(1.0, 1.0, 0.0, 1.0);
    
    for (u16 i = 0; i < particles.countAlive; i++) {
        const Vec3 position = particles.positions[i].getXYZ();
        glVertex3f(position.getX(), position.getY(), position.getZ());
        glVertex3f(position.getX(), position.getY() + 0.1, position.getZ());
    }

    glEnd();
}