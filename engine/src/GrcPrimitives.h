#ifndef __DEBUGDRAW_H__
#define __DEBUGDRAW_H__

#include "Color.h"

template <class T> class Vector3;

namespace GrcPrimitives
{
    template <class T> void segment(const Vector3<T>& vStart, const Vector3<T>& vEnd, const Col color);
    template <class T> void ray(const Vector3<T>& vStart, const Vector3<T>& vDir, Col color);
    template <class T> void openSegment(const Vector3<T>& vStart, const Vector3<T>& vDir, const Col color);
    template <class T> void line(const Vector3<T>& vPos, const Vector3<T>& vDir, const Col color);
};

/*******************
 * Implementation
 ******************/

#include "GrcPrimitives.inl"

#endif