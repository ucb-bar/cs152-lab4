// See LICENSE for license details.

//**************************************************************************
// Scalar conditional SAXPY
//--------------------------------------------------------------------------
#include "csaxpy.h"

void csaxpy(size_t n, const bool cond[], float a, const float x[], float y[])
{
  size_t i;
  for (i = 0 ; i < n ; i++) {
    if (cond[i]) {
      y[i] = (a * x[i]) + y[i];
    }
  }
}
