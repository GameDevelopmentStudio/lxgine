#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include "TypeDefinitions.h"

#include "ParticleEmitter.h"
#include "ParticleData.h"

class ParticleUpdater;
class ParticleRenderer;

class ParticleSystem {
public:
    
    ParticleData particleData;
    ParticleEmitter particleEmitter;
    
    // TMP
    ParticleRenderer* renderer;
    
    ParticleSystem();
    ~ParticleSystem();
    
    void update(real timeDelta);
    void addUpdater(ParticleUpdater& updater);
    
    void render();
    
protected:
    std::vector<ParticleUpdater*> updaters;
};
#endif