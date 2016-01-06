#ifndef __PARTICLEGENERATOR_H__
#define __PARTICLEGENERATOR_H__

#include "TypeDefinitions.h"

class ParticleData;

class ParticleGenerator {
public:
    
    ParticleGenerator();
    ~ParticleGenerator();
    
    virtual void generate(real timeDelta, ParticleData& particles, u16 particleStartIdx, u16 particleEndIdx) const = 0;
    
};
#endif
