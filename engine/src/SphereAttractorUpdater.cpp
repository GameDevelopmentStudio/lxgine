#include "SphereAttractorUpdater.h"

#include "ParticleData.h"
#include "GrcPrimitives.h"
#include "Color.h"

#include <math.h>

SphereAttractorParticleUpdater::SphereAttractorParticleUpdater() {
}

SphereAttractorParticleUpdater::~SphereAttractorParticleUpdater() {
}

void SphereAttractorParticleUpdater::update(real timeDelta, ParticleData& particles) const {
 
    for (u16 i = 0; i < particles.countAlive; i++) {
        Vec4& velocity = particles.velocities[i];
        const Vec4 attractionAcceleration = computeAttractionAcceleration(particles, i);
        velocity += attractionAcceleration * timeDelta;
    }
}

Vec4 SphereAttractorParticleUpdater::computeAttractionAcceleration(const ParticleData& particles, const u16 idx) const {
    const Vec4& position = particles.positions[idx];
    const Vec4& velocity = particles.velocities[idx];
    
    Vec4 attractionAcceleration(0.0, 0.0, 0.0, 0.0);
    const Vec4 positionToCenter = attractorCenter - position;
    const real distanceToCenter = fmax(positionToCenter.module() - radius, 0.0);
    if (distanceToCenter > 0.0) {
        Vec4 directionToCenter = positionToCenter / positionToCenter.module();
        
        // 0 -> max force / inf -> min force
        real attractionForce = (1.0 - fmin(distanceToCenter / distanceThreshold, 1.0)) * maxAttractionForce;
        
        // direction
        Vec4 attractorDir(0.0, 0.0, 1.0, 0.0); // test
        Vec4 positionToCenterDir = normalizedVector(positionToCenter);
        Vec4 tangent = crossProduct(positionToCenter, positionToCenterDir);
        
        if (scalarDot(tangent, velocity) < 0.0) {
            tangent = -tangent;
        }
        
        Vec4 desiredPos = (position + directionToCenter * distanceToCenter) +  tangent * attractionForce;
        attractionAcceleration = desiredPos - position;
    }
    
    return attractionAcceleration;
}

void SphereAttractorParticleUpdater::debug(const ParticleData& particles) const {
    
    return;
    Col red(1.0f, 0.0f, 0.0f);
    Col green(0.0f, 1.0f, 0.0f);
    for (u16 i = 0; i < particles.countAlive; i++) {
        Vec4& position = particles.positions[i];
        Vec4& velocity = particles.velocities[i];
        
        GrcPrimitives::segment(position.getXYZ(), (position + velocity).getXYZ(), red);
        
        const Vec4 attractionAcceleration = computeAttractionAcceleration(particles, i);
        GrcPrimitives::segment(position.getXYZ(), attractionAcceleration.getXYZ(), green);
    }
}