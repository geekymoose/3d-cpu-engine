// =============================================================================
// INLINE
// Contains matrix function common to all kind of optimization (SSE, FPU etc)
// Author: Constantin Masson
// =============================================================================

#ifdef __SSE4_1__
#   include "MatrixF4_FPU.inl" // For now, only FPU exists
#else
#   include "MatrixF4_FPU.inl"
#endif



