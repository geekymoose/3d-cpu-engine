// =============================================================================
// INLINE
// Contains matrix function common to all kind of optimization (SSE, FPU etc)
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Special class members
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF4 MatrixF4::IDENTITY() {
    return MatrixF4(
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1);
}

FORCE_INLINE MatrixF4 MatrixF4::ZERO() {
    return MatrixF4(
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0);
}


// -----------------------------------------------------------------------------
// Add function specific to optimization type
// -----------------------------------------------------------------------------
#ifdef __SSE4_1__
#   include "MatrixF4_FPU.inl" //TODO Tmp: For now, only FPU exists
#else
#   include "MatrixF4_FPU.inl"
#endif
