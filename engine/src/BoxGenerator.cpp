#include "BoxGenerator.h"

#include "ParticleData.h"
#include <random>

BoxPosParticleGenerator::BoxPosParticleGenerator() {
    
}

BoxPosParticleGenerator::~BoxPosParticleGenerator() {
    
}

void BoxPosParticleGenerator::init(Vec4 centerPosition, Vec4 maxStartOffset) {
    this->centerPosition = centerPosition;
    this->maxStartOffset = maxStartOffset;
}

void BoxPosParticleGenerator::generate(real timeDelta, ParticleData& particles, u16 particleStartIdx, u16 particleEndIdx) const {

    Vec4 minPos = Vec4(centerPosition.getX() - maxStartOffset.getX()
                     , centerPosition.getX() - maxStartOffset.getY()
                     , centerPosition.getX() - maxStartOffset.getZ()
                     , 1.0);
    
    Vec4 maxPos = Vec4(centerPosition.getX() + maxStartOffset.getX()
                     , centerPosition.getX() + maxStartOffset.getY()
                     , centerPosition.getX() + maxStartOffset.getZ()
                     , 1.0);
    
    for (u16 i = particleStartIdx; i < particleEndIdx; i++) {
        // TODO: do this properly
        
        Vec4 position((rand() / (real) RAND_MAX) * (maxPos.getX() - minPos.getX()) + minPos.getX()
                    , (rand() / (real) RAND_MAX) * (maxPos.getY() - minPos.getY()) + minPos.getY()
                    , (rand() / (real) RAND_MAX) * (maxPos.getZ() - minPos.getZ()) + minPos.getZ()
                    , 1.0);
        
        particles.positions[i] = position;
    }
}