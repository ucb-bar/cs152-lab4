// See LICENSE for license details.

//**************************************************************************
// Scalar DGEMM
//--------------------------------------------------------------------------
#include "dgemm.h"

void dgemm_inner(size_t n, double A[], double B[], double C[])
{
  size_t j, k;
  double c0, c1, c2, c3;
  double b0, b1, b2, b3;
  double a00, a01, a02, a03;
  double a10, a11, a12, a13;
  double a20, a21, a22, a23;
  double a30, a31, a32, a33;

  for (j = 0; j < n; j++) {
    c0 = C[j];       // C[i][j]
    c1 = C[n + j];   // C[i+1][j]
    c2 = C[2*n + j]; // C[i+2][j]
    c3 = C[3*n + j]; // C[i+3][j]

    for (k = 0; k < (n/4)*4; k += 4) {
      b0 = B[(k+0)*n + j]; // B[k][j]
      b1 = B[(k+1)*n + j]; // B[k+1][j]
      b2 = B[(k+2)*n + j]; // B[k+2][j]
      b3 = B[(k+3)*n + j]; // B[k+3][j]

      a00 = A[k+0]; // A[i][k]
      a01 = A[k+1]; // A[i][k+1]
      a02 = A[k+2]; // A[i][k+2]
      a03 = A[k+3]; // A[i][k+3]

      a10 = A[n + k+0]; // A[i+1][k]
      a11 = A[n + k+1]; // A[i+1][k+1]
      a12 = A[n + k+2]; // A[i+1][k+2]
      a13 = A[n + k+3]; // A[i+1][k+3]

      a20 = A[2*n + k+0]; // A[i+2][k]
      a21 = A[2*n + k+1]; // A[i+2][k+1]
      a22 = A[2*n + k+2]; // A[i+2][k+2]
      a23 = A[2*n + k+3]; // A[i+2][k+3]

      a30 = A[3*n + k+0]; // A[i+3][k]
      a31 = A[3*n + k+1]; // A[i+3][k+1]
      a32 = A[3*n + k+2]; // A[i+3][k+2]
      a33 = A[3*n + k+3]; // A[i+3][k+3]

      // C[i][j] = sum k { A[i][k] * B[k][j] }
      c0 += (a00 * b0) + (a01 * b1) + (a02 * b2) + (a03 * b3);
      // C[i+1][j] = sum k { A[i+1][k] * B[k][j] }
      c1 += (a10 * b0) + (a11 * b1) + (a12 * b2) + (a13 * b3);
      // C[i+2][j] = sum k { A[i+2][k] * B[k][j] }
      c2 += (a20 * b0) + (a21 * b1) + (a22 * b2) + (a23 * b3);
      // C[i+3][j] = sum k { A[i+3][k] * B[k][j] }
      c3 += (a30 * b0) + (a31 * b1) + (a32 * b2) + (a33 * b3);
    }

    for (; k < n; k++) {
      b0 = B[k*n + j]; // B[k][j]

      a00 = A[k];       // A[i][k]
      a10 = A[n + k];   // A[i+1][k]
      a20 = A[2*n + k]; // A[i+2][k]
      a30 = A[3*n + k]; // A[i+3][k]

      c0 += a00 * b0;
      c1 += a10 * b0;
      c2 += a20 * b0;
      c3 += a30 * b0;
    }

    C[j] = c0;       // C[i][j]
    C[n + j] = c1;   // C[i+1][j]
    C[2*n + j] = c2; // C[i+2][j]
    C[3*n + j] = c3; // C[i+3][j]
  }
}
