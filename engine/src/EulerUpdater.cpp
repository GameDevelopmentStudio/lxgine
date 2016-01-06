#include "EulerUpdater.h"

#include "ParticleData.h"

#include <math.h>

EulerParticleUpdater::EulerParticleUpdater() {
}

EulerParticleUpdater::~EulerParticleUpdater() {
}

void EulerParticleUpdater::update(real timeDelta, ParticleData& particles) const {
 
    const Vec4 globalAcceleration = this->globalAcceleration * timeDelta;
    
    for (u16 i = 0; i < particles.countAlive; i++) {
        particles.accelerations[i] += globalAcceleration;
    }
    
    for (u16 i = 0; i < particles.countAlive; i++) {
        particles.velocities[i] += timeDelta * particles.accelerations[i];
    }
    
    for (u16 i = 0; i < particles.countAlive; i++) {
        particles.positions[i] += timeDelta * particles.velocities[i];
    }
}