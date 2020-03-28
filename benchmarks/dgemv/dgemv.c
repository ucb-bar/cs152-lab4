// See LICENSE for license details.

//**************************************************************************
// Scalar DGEMV
//--------------------------------------------------------------------------
#include "dgemv.h"

void dgemv(size_t m, size_t n, const double A[], const double x[], double y[])
{
  size_t i, j;
  for (i = 0 ; i < m ; i++, A += n) {
    double k = y[i];
    for (j = 0; j < n; j++) {
      k += A[j] * x[j];
    }
    y[i] = k;
  }
}
