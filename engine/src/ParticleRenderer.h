#ifndef __PARTICLERENDERER_H__
#define __PARTICLERENDERER_H__

#include "TypeDefinitions.h"

class ParticleData;

class ParticleRenderer {
public:
    
    ParticleRenderer();
    virtual ~ParticleRenderer();
    
//    virtual void generate(real timeDelta, ParticleData* particles, u16 particleStartIdx, u16 particleEndIdx) const = 0;
//    virtual void destroy() const = 0;
//    virtual void update() const = 0;
    
    // TODO: for now
    virtual void render(ParticleData& particles) const = 0;
};
#endif
