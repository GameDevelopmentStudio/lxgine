#include "SphereAttractorUpdater.h"

#include "ParticleData.h"

#include <math.h>

SphereAttractorParticleUpdater::SphereAttractorParticleUpdater() {
}

SphereAttractorParticleUpdater::~SphereAttractorParticleUpdater() {
}

void SphereAttractorParticleUpdater::update(real timeDelta, ParticleData& particles) const {
 
    for (u16 i = 0; i < particles.countAlive; i++) {
        Vec4& position = particles.positions[i];
        
        Vec4 positionToCenter = attractorCenter - position;
        real distanceToCenter = fmax(positionToCenter.module() - radius, 0.0);
        if (distanceToCenter > 0.0) {
            Vec4 directionToCenter = positionToCenter / distanceToCenter;
            
            // 0 -> max force / inf -> min force
            real attractionForce = (1.0 - fmin(distanceToCenter / distanceThreshold, 1.0)) * maxAttractionForce;
            position += directionToCenter * attractionForce;
        }
    }
}