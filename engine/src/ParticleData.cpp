#include "ParticleData.h"

// TODO: need this as a hack to get std:: , but we should only include the necessary header
#include <fstream>
#include <random>

ParticleData::ParticleData() {
}

ParticleData::~ParticleData() {
}

void ParticleData::init(u32 maxCount) {
    this->maxCount = maxCount;
    countAlive = 0;
    
    positions = new Vec4[maxCount];
    velocities = new Vec4[maxCount];
    accelerations = new Vec4[maxCount];
    times = new real[maxCount];
    masks = new BitSet8[maxCount]();
}

void ParticleData::kill(u16 particleIdx) {
//    assert(particleIdx >= 0 && particleIdx < maxCount, "Tried to kill a particle outside the max range");
    
    if (countAlive > 0) {
        masks[particleIdx].set(ParticleFlagsAlive, false);
        swap(particleIdx, countAlive - 1);
        countAlive--;
    }
}

void ParticleData::wake(u16 particleIdx) {
    //    assert(particleIdx >= 0 && particleIdx < maxCount, "Tried to wake a particle outside the max range");
    
    if (countAlive < maxCount) {
        
        // todo: should be in a generator
        real time = (rand() / (real) RAND_MAX) * 3.0 + 2.0;
        
        masks[particleIdx].set(ParticleFlagsAlive, true);
        times[particleIdx] = time;
        accelerations[particleIdx] = 0.0;
        velocities[particleIdx] = 0.0;
        swap(particleIdx, countAlive);
        countAlive++;
    }
}

void ParticleData::swap(u16 particleAIdx, u16 particleBIdx) {
    std::swap(positions[particleAIdx], positions[particleBIdx]);
    std::swap(velocities[particleAIdx], velocities[particleBIdx]);
    std::swap(accelerations[particleAIdx], accelerations[particleBIdx]);
    std::swap(times[particleAIdx], times[particleBIdx]);
    std::swap(masks[particleAIdx], masks[particleBIdx]);
}