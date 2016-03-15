#ifndef __POINTATTRACTORPARTICLEUPDATER_H__
#define __POINTATTRACTORPARTICLEUPDATER_H__

#include "ParticleUpdater.h"
#include "Vector.h"

class SphereAttractorParticleUpdater : public ParticleUpdater {
public:
    
    Vec4 attractorCenter;
    real maxAttractionForce;
    real distanceThreshold;
    real radius;
    
    SphereAttractorParticleUpdater();
    virtual ~SphereAttractorParticleUpdater();
    
    virtual void update(real timeDelta, ParticleData& particles) const;
    
    virtual void debug(const ParticleData& particles) const;
    
    Vec4 computeAttractionAcceleration(const ParticleData& particles, const u16 idx) const;
};
#endif