// =============================================================================
// INLINE.
// General inlined definitions for Vector. (Common for SSE, FPU etc).
// Author: Constantin Masson
// =============================================================================


#ifdef __SSE4_1__
#   include "VectF4_SSE.inl"
#else
#   include "VectF4_FPU.inl"
#endif


FORCE_INLINE std::ostream& operator<<(std::ostream &os, VectF4 const& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}


