// See LICENSE for license details.

//**************************************************************************
// Vectorized DGEMV
//--------------------------------------------------------------------------

    .text
    .align 2

    .global dgemv
    .type dgemv,@function
/*
 * void dgemv(size_t m, size_t n, const double A[], const double x[], double y[])
 *
 * Calling convention:
 *     a0: size_t m
 *     a1: size_t n
 *     a2: double *A
 *     a3: double *x
 *     a4: double *y
 *
 * Pseudocode:
 *     for (i = 0; i < m; i++) {
 *         for (j = 0; j < n; j++) {
 *             y[i] += A[i][j] * x[j]
 *         }
 *     }
 */
dgemv:
    slli a5, a0, 3                  # scale m to byte offset
    add a5, a4, a5                  # initialize pointer to end of y

    fmv.d.x ft0, zero               # initialize 0.0 constant

dgemv_loop_i:
    vsetvli t0, a1, e64, m8, ta, ma # configure SEW=64 LMUL=8
    vfmv.v.f v0, ft0                # initialize v0 to 0.0
    fld ft1, (a4)                   # load y[i]

    mv t1, a1                       # copy n to temporary counter
    mv t2, a3                       # initialize temporary pointer to x

dgemv_loop_j:

    # TODO: load A[i][j]
    # TODO: load x[j]
    # TODO: accumulate A[i][j] * x[j] into v0

    sub t1, t1, t0                  # decrement counter
    slli t0, t0, 3                  # scale VL to byte offset
    add a2, a2, t0                  # bump pointer A
    add t2, t2, t0                  # bump pointer x
    vsetvli t0, t1, e64, m8         # update VL; maintain SEW and LMUL
    bnez t1, dgemv_loop_j           # loop

    vsetvli zero, a1, e64, m8       # restore original VL

    # TODO: perform final reduction on v0

    fsd ft1, (a4)                   # store y[i]
    addi a4, a4, 8                  # bump pointer y

    bltu a4, a5, dgemv_loop_i       # loop until end of y

    ret
