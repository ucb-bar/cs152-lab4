// See LICENSE for license details.

//**************************************************************************
// Scalar DGEMM
//--------------------------------------------------------------------------
#include "dgemm.h"

void dgemm_remainder(size_t n, double A[], double B[], double C[])
{
  size_t j, k;
  double c0;
  double b0, b1, b2, b3;
  double a00, a01, a02, a03;

  for (j = 0; j < n; j++) {
    c0 = C[j]; // C[i][j]

    for (k = 0; k < (n/4)*4; k += 4) {
      b0 = B[(k+0)*n + j]; // B[k][j]
      b1 = B[(k+1)*n + j]; // B[k+1][j]
      b2 = B[(k+2)*n + j]; // B[k+2][j]
      b3 = B[(k+3)*n + j]; // B[k+3][j]

      a00 = A[k+0]; // A[i][k]
      a01 = A[k+1]; // A[i][k+1]
      a02 = A[k+2]; // A[i][k+2]
      a03 = A[k+3]; // A[i][k+3]

      // C[i][j] = sum k { A[i][k] * B[k][j] }
      c0 += (a00 * b0) + (a01 * b1) + (a02 * b2) + (a03 * b3);
    }

    for (; k < n; k++) {
      b0 = B[k*n + j]; // B[k][j]
      a00 = A[k]; // A[i][k]
      c0 += a00 * b0;
    }

    C[j] = c0; // C[i][j]
  }
}
