// See LICENSE for license details.

//**************************************************************************
// Scalar index of maximum
//--------------------------------------------------------------------------
#include "imax.h"
#include <math.h>

size_t imax(size_t n, const float x[])
{
  size_t k, idx;
  float max;

  max = -INFINITY;
  idx = 0;

  for (k = 0 ; k < n ; k++) {
    float elt;
    int gt;

    elt = x[k];
    gt = elt > max;
    max = gt ? elt : max; // infer fmax.s
    idx = gt ? k : idx;
  }
  return idx;
}
