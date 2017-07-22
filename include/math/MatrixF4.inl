// =============================================================================
// INLINE
// Contains matrix function common to all kind of optimization (SSE, FPU etc)
// Author: Constantin Masson
// =============================================================================

const MatrixF4 MatrixF4::IDENTITY(
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1);

const MatrixF4 MatrixF4::ZERO(
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0);


// -----------------------------------------------------------------------------
// Add function specific to optimization type
// -----------------------------------------------------------------------------
#ifdef __SSE4_1__
#   include "MatrixF4_FPU.inl" // For now, only FPU exists
#else
#   include "MatrixF4_FPU.inl"
#endif
