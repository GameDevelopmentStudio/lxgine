#ifndef __PARTICLEUPDATER_H__
#define __PARTICLEUPDATER_H__

#include "TypeDefinitions.h"

class ParticleData;

class ParticleUpdater {
public:
    
    ParticleUpdater();
    virtual ~ParticleUpdater();
    
    virtual void update(real timeDelta, ParticleData& particles) const = 0;
};
#endif