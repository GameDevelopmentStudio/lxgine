#ifndef __CAMERALENS_H__
#define __CAMERALENS_H__

#include "Vector.h"

class CameraLens {
public:
    
    struct Perspective {
        real N, F;
        real fov, aspect;
    };
    
    struct Frustrum {
        real N, F;
        real xR, xL;
        real yT, yB;
    };
    
    enum LensType {
        CameraLensTypePerspective,
        CameraLensTypeFrustrum,
        CameraLensTypeCount
    };
    
    CameraLens();
    ~CameraLens();
    
    // Frustrum
    Frustrum& setFrustrumRaw();
    Perspective& setFrustrumWithPerspective();
    
    // Frustrum params
    union
    {
        Frustrum frustrum;
        Perspective perspective;
    };
    LensType type;
};

#endif