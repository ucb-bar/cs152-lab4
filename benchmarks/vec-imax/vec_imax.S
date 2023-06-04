// See LICENSE for license details.

//**************************************************************************
// Vectorized index of maximum
//--------------------------------------------------------------------------

    .text
    .align 2

    .global imax
    .type imax,@function
/*
 * unsigned int imax(unsigned int n, const float x[]);
 *
 * Calling convention:
 *     a0: unsigned int n
 *     a1: const float *x
 * Return value:
 *     a0: index
 */
imax:
1:  auipc t0, %pcrel_hi(input_inf)
    flw fa0, %pcrel_lo(1b)(t0)          # load -infinity

    vsetvli t0, a0, e32, m4, ta, mu     # configure SEW=32 LMUL=4
    vmv.v.i v4, 0                       # set initial indices to 0 (don't cares)
    vfmv.v.f v8, fa0                    # set initial maximum values to -infinity
    vid.v v12                           # initialize sequential indices
    mv t1, t0                           # save original VL

    # HINT: stripmine loop performs parallel reduction
    #       v8[i] = max(x[i], x[VLMAX+i], x[2*VLMAX+i], ...)
imax_loop:

    # TODO: load x[k] vector
    # TODO: compare against previous maximum values
    # TODO: update maximum vector
    # TODO: update index vector

    sub a0, a0, t0                      # decrement n
    slli t0, t0, 2                      # scale VL to byte offset
    add a1, a1, t0                      # bump pointer x

    vsetvli t0, a0, e32, m4, tu, mu     # configure VL for next iteration

    # TODO: increment sequential indices by VLMAX

    bnez a0, imax_loop                  # loop

    li t0, -1
    vsetvli zero, t1, e32, m4, ta, ma   # restore original VL
    vmv.s.x v28, t0                     # move UINT_MAX to scalar in v28
                                        # HINT: may be useful for reductions

    # TODO: find maximum value within v8
    # TODO: determine element position(s) of maximum
    # TODO: find lowest index among indicated positions (HINT: masked reduction)
    # TODO: set return value

    ret

    .section .rodata
input_inf:
    .float -inf
