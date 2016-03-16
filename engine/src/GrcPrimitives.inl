#include "MathPrimitives.h"

namespace Private
{
    const u8 kDebugCircleVertexCount = 16;
    const u8 kDebugSphereSectionCount = 16;
}

template <class T> void GrcPrimitives::ray(const Vector3<T>& vStart, const Vector3<T>& vDir, Col color) {
    openSegment(vStart, vDir, color);
}

template <class T> void GrcPrimitives::openSegment(const Vector3<T>& vStart, const Vector3<T>& vDir, Col color) {
    const T fLargeValue = 10000;
    const Vector3<T> vEnd = vStart + fLargeValue * vDir;
    segment(vStart, vEnd, color);
}

template <class T> void GrcPrimitives::line(const Vector3<T>& vPos, const Vector3<T>& vDir, Col color) {
    const T fLargeValue = 10000;
    const Vector3<T> vStart = vPos - fLargeValue * vDir;
    const Vector3<T> vEnd = vPos + fLargeValue * vDir;
    segment(vStart, vEnd, color);
}

template <class T> void GrcPrimitives::poly(const Vector3<T>* aPos, const u8 count, Col color) {
    for (s8 i = 0; i < count; i++) {
        const Vector3<T> vPrev = aPos[i];
        const Vector3<T> vNext = (i < count - 1) ? aPos[i + 1] : aPos[0];
        segment(vPrev, vNext, color);
    }
}

template <class T> void GrcPrimitives::circle(const Vector3<T>& vPos, const Vector3<T> vAxis, const T radius, const Col color) {

    const Vector3<T> zero(0, 0, 0);
    const Vector3<T> expectedForward = Vector3<T>(0, 0, -1);
    const Vector3<T> up = normalizedVector(vAxis);
    Vector3<T> right = normalizedVector(crossProduct(up, expectedForward));
    if (right == zero)
    {
        right = Vector3<T>(1, 0, 0);
    }
    const Vector3<T> forward = normalizedVector(crossProduct(up, right));
    
    Vector3<T> aPos[Private::kDebugCircleVertexCount];
    for (u8 i = 0; i < Private::kDebugCircleVertexCount; i++) {
        
        const T angle = i * 2 * M_PI / (T) Private::kDebugCircleVertexCount;
        const Vector3<T> normalizedOffset = ((T) cos(angle)) * right + ((T) sin(angle)) * forward;
        
        aPos[i] = vPos + radius * normalizedOffset;
    }
    
    poly(aPos, Private::kDebugCircleVertexCount, color);
}

template <class T> void GrcPrimitives::sphere(const Vector3<T>& vPos, const T radius, const Col color) {
    
    const Col colorVariation(0.25f, 0.25f, 0.25f, 0.f);
    const Vector3<T> sectionXAxis(1, 0, 0);
    const Vector3<T> sectionYAxis(0, 1, 0);
    for (u8 i = 0; i < Private::kDebugSphereSectionCount; i++) {


        const T angle = i * M_PI / (T) Private::kDebugSphereSectionCount;
        const T sinAngle = sin(angle);
        const T cosAngle = cos(angle);
        const T sectionRadius = radius * sinAngle;
        const T sectionOffset = radius * cosAngle;
        const Vector3<T> sectionXPos = vPos + sectionOffset * sectionXAxis;
        const Vector3<T> sectionYPos = vPos + sectionOffset * sectionYAxis;
        
        const Col colorOffset = (1.f - sinAngle) * colorVariation;
        const Col sectionColor = color + colorOffset;
        
        circle(sectionXPos, sectionXAxis, sectionRadius, sectionColor);
        circle(sectionYPos, sectionYAxis, sectionRadius, sectionColor);
    }
    
}
