#include "ParticleSystem.h"

#include "ParticleUpdater.h"
#include "ParticlePointRenderer.h"

ParticleSystem::ParticleSystem() {
    // tmp
    particleData.init(400);
    particleEmitter.init(200);
    
    // tmp
    renderer = new ParticlePointRenderer();
}

ParticleSystem::~ParticleSystem() {
    if (renderer) {
        delete renderer;
    }
}

void ParticleSystem::update(real timeDelta) {
    
    particleEmitter.emit(timeDelta, particleData);

    // Update time
    for (u16 i = 0; i < particleData.countAlive; i++) {
        particleData.times[i] -= timeDelta;
    }
    
    for (ParticleUpdater* updater : updaters) {
        updater->update(timeDelta, particleData);
    }
    
    for (u16 i = 0; i < particleData.countAlive; i++) {
        particleData.positions[i] += timeDelta * particleData.velocities[i];
    }
    
    for (u16 i = 0; i < particleData.countAlive; i++) {
        
        // tmp
        if (particleData.times[i] < 0.0) {
            particleData.kill(i);
        }
    }
}

void ParticleSystem::addUpdater(ParticleUpdater& updater) {
    updaters.push_back(&updater);
}

void ParticleSystem::render() {
    if (renderer) {
        renderer->render(particleData);
    }
}

void ParticleSystem::debug() const {
    // particleEmitter.debug();
    // particleData.debug();
    
    for (ParticleUpdater* updater : updaters) {
        updater->debug(particleData);
    }
}