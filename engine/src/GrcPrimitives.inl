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