#ifndef __PARTICLEPOINTRENDERER_H__
#define __PARTICLEPOINTRENDERER_H__

#include "ParticleRenderer.h"

class ParticleData;

class ParticlePointRenderer : public ParticleRenderer {
public:
    
    ParticlePointRenderer();
    virtual ~ParticlePointRenderer();

    virtual void render(ParticleData& particles) const;
};
#endif
