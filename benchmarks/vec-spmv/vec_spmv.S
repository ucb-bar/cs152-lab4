// See LICENSE for license details.

//**************************************************************************
// Vectorized sparse matrix-vector multiply
//--------------------------------------------------------------------------

    .text
    .align 2

    .global vec_spmv
    .type vec_spmv,@function
/*
 * void vec_spmv(size_t r, const double* val, const int* idx, const double* x,
 *               const int* ptr, double* y, double* tmp)
 *
 * Calling convention:
 *     a0: size_t r
 *     a1: double *val
 *     a2: int *idx
 *     a3: double *x
 *     a4: int *ptr
 *     a5: double *y
 *     a6: double *tmp
 */
vec_spmv:
    # TODO: prologue

    # TODO: initialize loop-invariant values
vec_spmv_loop_i:

    # TODO: stripmine
vec_spmv_loop_k:

    # TODO: compute SpMV

    # TODO: loop arithmetic

    # TODO: epilogue
    ret
