// =============================================================================
// INLINE.
// General inlined definitions for Vector. (Common for SSE, FPU etc).
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE std::ostream& operator<<(std::ostream &os, VectF3 const& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

FORCE_INLINE float VectF3::operator[](const size_t index) const {
    return (&x)[index];
}

FORCE_INLINE float& VectF3::operator[](const size_t index){
    return *(&x+index);
}


// -----------------------------------------------------------------------------
// Add implementation specific to an optimization
// -----------------------------------------------------------------------------
#ifdef __SSE4_1__
#   include "VectF3_SSE.inl"
#else
#   include "VectF3_FPU.inl"
#endif
