// See LICENSE for license details.

//**************************************************************************
// Scalar index of maximum
//--------------------------------------------------------------------------
#include "imax.h"
#include <math.h>

unsigned int imax(unsigned int n, const float x[])
{
  unsigned int k, idx;
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
