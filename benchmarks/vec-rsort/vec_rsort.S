// See LICENSE for license details.

//**************************************************************************
// Vectorized radix sort
//--------------------------------------------------------------------------

    .text
    .align 2

#define LOG_BASE 3

    .global vec_rsort
    .type vec_rsort,@function
/*
 * void vec_rsort(size_t n, type* arrIn, type* scratchIn, int* buckets)
 *
 * Calling convention:
 *     a0: size_t n
 *     a1: type *arrIn
 *     a2: type *scrachIn
 *     a3: int *buckets
 */
vec_rsort:
    # TODO: prologue
    addi sp, sp, -16
    sd s0, 8(sp)
    sd ra, 0(sp)

    mv s0, a1                       # save arrIn pointer
    # NOTE: DO NOT clobber s0; use a1 as arr pointer

    # NOTE: change code structure if necessary
vec_rsort_loop:

vec_rsort_reset:
    # TODO: clear buckets

vec_rsort_histogram:
    # TODO: extract digits
    # TODO: assign to buckets
    # TODO: increment buckets

vec_rsort_scan:
    # TODO: prefix sum over buckets

vec_rsort_permute:
    # TODO: extract digits
    # TODO: obtain offset from buckets
    # TODO: decrement buckets
    # TODO: place entries into scratch array

    # TODO: swap arr and scratch

    # TODO: loop arithmetic

    # copy scratch to arrIn if necessary
    beq a1, s0, vec_rsort_done
    slli a2, a0, 2                  # n * sizeof(type)
    mv a0, s0                       # arrIn
    call memcpy

vec_rsort_done:
    # TODO: epilogue
    ld ra, 0(sp)
    ld s0, 8(sp)
    addi sp, sp, 16
    ret
