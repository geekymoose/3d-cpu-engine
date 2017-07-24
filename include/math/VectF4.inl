// =============================================================================
// INLINE.
// General inlined definitions for Vector. (Common for SSE, FPU etc).
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE std::ostream& operator<<(std::ostream &os, VectF4 const& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}

FORCE_INLINE float VectF4::operator[](const size_t index) const {
    return (&x)[index];
}

FORCE_INLINE float& VectF4::operator[](const size_t index){
    return *(&x+index);
}


// -----------------------------------------------------------------------------
// Add implementation specific to an optimization
// -----------------------------------------------------------------------------
#ifdef __SSE4_1__
#   include "VectF4_SSE.inl"
#else
#   include "VectF4_FPU.inl"
#endif

