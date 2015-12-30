#include "CameraLens.h"

CameraLens::CameraLens() {
}

CameraLens::~CameraLens() {
}

CameraLens::Frustrum& CameraLens::setFrustrumRaw() {
    type = CameraLensTypeFrustrum;
    return frustrum;
}

CameraLens::Perspective& CameraLens::setFrustrumWithPerspective() {
    type = CameraLensTypePerspective;
    return perspective;
}
