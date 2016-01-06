#include "ParticleEmitter.h"

#include "ParticleGenerator.h"

ParticleEmitter::ParticleEmitter() {
    
}

ParticleEmitter::~ParticleEmitter() {
    
}

void ParticleEmitter::init(real emitRate) {
    this->emitRate = emitRate;
}

void ParticleEmitter::emit(real timeDelta, ParticleData& particles) {
    const u16 expectedEmittedParticles = static_cast<u16>(timeDelta * emitRate);
    const u16 particleStartIdx = particles.countAlive;
    const u16 particleEndIdx = std::min(particleStartIdx + expectedEmittedParticles, particles.maxCount - 0);
    
    for (ParticleGenerator* generator : generators) {
        generator->generate(timeDelta, particles, particleStartIdx, particleEndIdx);
    }
    
    for (u16 i = particleStartIdx; i < particleEndIdx; i++) {
        particles.wake(i);
    }
}

void ParticleEmitter::addGenerator(ParticleGenerator& generator) {
    generators.push_back(&generator);
}

