// See LICENSE for license details.

//**************************************************************************
// Scalar complex multiply
//--------------------------------------------------------------------------
#include "cmplxmult.h"

void cmplxmult(size_t n, const struct Complex a[], const struct Complex b[], struct Complex c[])
{
  size_t i;
  for (i = 0; i < n; i++ ) {
    c[i].real = (a[i].real * b[i].real) - (a[i].imag * b[i].imag);
    c[i].imag = (a[i].imag * b[i].real) + (a[i].real * b[i].imag);
  }
}
