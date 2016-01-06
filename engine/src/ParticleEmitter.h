#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

#include "TypeDefinitions.h"
#include <vector>

#include "ParticleData.h"

class ParticleGenerator;

class ParticleEmitter {
public:
    
    ParticleEmitter();
    ~ParticleEmitter();
    
    void init(real emitRate);
    
    void emit(real timeDelta, ParticleData& particles);
    void addGenerator(ParticleGenerator& generator);
    
protected:
    
    std::vector<ParticleGenerator*> generators;
    real emitRate;
};

#endif