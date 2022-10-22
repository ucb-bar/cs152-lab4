// See LICENSE for license details.

//**************************************************************************
// Vectorized DGEMM
//--------------------------------------------------------------------------

    .text
    .align 2

    .global dgemm_remainder
    .type dgemv_remainder,@function
/*
 * void dgemm_remainder(size_t n, const double A[], const double B[], const double C[])
 *
 * Calling convention:
 *     a0: size_t n
 *     a1: double *A
 *     a2: double *B
 *     a3: double *C
 *
 * Pseudocode:
 *     for (j = 0; j < n; j++) {
 *         for (k = 0; k < (n/4)*4; k += 4) {
 *             C[i][j] += A[i][k]   * B[k][j];
 *             C[i][j] += A[i][k+1] * B[k+1][j];
 *             C[i][j] += A[i][k+2] * B[k+2][j];
 *             C[i][j] += A[i][k+3] * B[k+3][j];
 *         }
 *         for (; k < n; k++) {
 *             C[i][j] += A[i][k] * B[k][j];
 *         }
 *     }
 */
dgemm_remainder:
    slli t1, a0, 3                  # scale n to bytes
    add t2, a1, t1                  # compute pointer to A[i][n]

    andi t3, a0, ~0x3               # (n / 4) * 4
    slli t3, t3, 3                  # scale to byte offset
    add t3, a1, t3                  # compute pointer to A[i][(n/4)*4]

dgemm_remainder_loop_j:
    vsetvli t0, a0, e64, m4, ta, ma # configure SEW=64 LMUL=4
    sub a0, a0, t0                  # decrement n
    slli t0, t0, 3                  # scale VL to byte offset

    # TODO: load C[i][j]

    mv t4, a1                       # copy temporary pointer to A
    mv t5, a2                       # copy temporary pointer to B

    bgeu a1, t3, 1f                 # skip if (n / 4) == 0

dgemm_remainder_loop_k:
    # TODO: load B[k][j]
    add t5, t5, t1                  # bump pointer B by row stride
    # TODO: load B[k+1][j]
    add t5, t5, t1                  # bump pointer B by row stride
    # TODO: load B[k+2][j]
    add t5, t5, t1                  # bump pointer B by row stride
    # TODO: load B[k+3][j]

    # HINT: treat A as scalars
    # TODO: load A[i][k]
    # TODO: load A[i][k+1]
    # TODO: load A[i][k+2]
    # TODO: load A[i][k+3]

    # TODO: compute partial C[i][j] unrolled 4 times

    addi t4, t4, 8*4                # bump pointer A by 4*sizeof(double)
    add t5, t5, t1                  # bump pointer B by row stride
    bltu t4, t3, dgemm_remainder_loop_k

1:
    beq t3, t2, 2f                  # skip if (n % 4) == 0

dgemm_remainder_loop_k_tail:

    # TODO: compute partial C[i][j] for remainder

    addi t4, t4, 8                  # bump pointer A by sizeof(double)
    add t5, t5, t1                  # bump pointer B by row stride
    bltu t4, t2, dgemm_remainder_loop_k_tail

2:
    # TODO: store C[i][j]

    add a2, a2, t0                  # bump pointer B by VL
    add a3, a3, t0                  # bump pointer C by VL
    bnez a0, dgemm_remainder_loop_j

    ret
