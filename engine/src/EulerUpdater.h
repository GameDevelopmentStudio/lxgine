#ifndef __EULERPARTICLEUPDATER_H__
#define __EULERPARTICLEUPDATER_H__

#include "ParticleUpdater.h"
#include "Vector.h"

class EulerParticleUpdater : public ParticleUpdater {
public:
    
    Vec4 globalAcceleration;
    
    EulerParticleUpdater();
    virtual ~EulerParticleUpdater();
    
    virtual void update(real timeDelta, ParticleData& particles) const;
};
#endif