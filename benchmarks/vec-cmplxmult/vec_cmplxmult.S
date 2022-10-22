// See LICENSE for license details.

//**************************************************************************
// Vectorized complex multiply
//--------------------------------------------------------------------------

    .text
    .align 2

    .global cmplxmult
    .type cmplxmult,@function
/*
 * void cmplxmult(size_t n, const struct Complex a[], const struct Complex b[], struct Complex c[]);
 *
 * Calling convention:
 *     a0: size_t n
 *     a1: struct Complex *a
 *     a2: struct Complex *b
 *     a3: struct Complex *c
 */
cmplxmult:
    vsetvli t0, a0, e32, m4, ta, ma   # configure SEW=32 LMUL=4

    # TODO: load a[i].real and a[i].imag
    # TODO: load b[i].real and b[i].imag

    # TODO: compute c[i].real = (a[i].real * b[i].real) - (a[i].imag * b[i].imag)
    # HINT: 2 instructions needed

    # TODO: compute c[i].imag = (a[i].real * b[i].imag) + (a[i].imag * b[i].real)
    # HINT: 2 instructions needed

    # TODO: store c[i].real and c[i].real

    # TODO: decrement n (a0)
    # TODO: bump pointers
    # TODO: loop

    ret
