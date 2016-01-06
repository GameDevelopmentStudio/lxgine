#ifndef __PARTICLEDATA_H__
#define __PARTICLEDATA_H__

#include "BitSet.h"
#include "Vector.h"

class ParticleData {
public:
    
    enum ParticleFlags : u8 {
        ParticleFlagsAlive = 1 << 0,
    };
    
    Vec4* positions;
    Vec4* velocities;
    Vec4* accelerations;
    real* times;
    BitSet8* masks;
    
    u16 maxCount;
    u16 countAlive;
    
    ParticleData();
    ~ParticleData();
    
    void init(u32 maxCount);
    void kill(u16 particleIdx);
    void wake(u16 particleIdx);
    void swap(u16 particleAIdx, u16 particleBIdx);
};
#endif
