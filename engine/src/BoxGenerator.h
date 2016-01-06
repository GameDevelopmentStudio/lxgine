#ifndef __BOXPOSPARTICLEGENERATOR_H__
#define __BOXPOSPARTICLEGENERATOR_H__

#include "ParticleGenerator.h"
#include "Vector.h"

class BoxPosParticleGenerator : public ParticleGenerator {
public:
    
    BoxPosParticleGenerator();
    ~BoxPosParticleGenerator();
    
    void init(Vec4 centerPosition, Vec4 maxStartOffset);
    
    virtual void generate(real timeDelta, ParticleData& particles, u16 particleStartIdx, u16 particleEndIdx) const;
    
protected:
    Vec4 centerPosition;
    Vec4 maxStartOffset;
};
#endif
