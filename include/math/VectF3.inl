// =============================================================================
// INLINE.
// General inlined definitions for Vector. (Common for SSE, FPU etc).
// Author: Constantin Masson
// =============================================================================


#ifdef __SSE4_1__
#   include "VectF3_SSE.inl"
#else
#   include "VectF3_FPU.inl"
#endif


FORCE_INLINE std::ostream& operator<<(std::ostream &os, VectF3 const& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}


