// See LICENSE for license details.

//**************************************************************************
// Radix sort benchmark
//--------------------------------------------------------------------------
//

#include "util.h"
#include <string.h>
#include <limits.h>

//--------------------------------------------------------------------------
// Input/Reference Data

#define type unsigned int
#include "dataset1.h"
//#include "dataset2.h" // Smaller test dataset

#define LOG_BASE 3
#define BASE (1 << LOG_BASE)

extern void vec_rsort(size_t n, type* arrIn, type* scratchIn, int* buckets);

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  static type scratch[DATA_SIZE];
  static int buckets[BASE];

  // Do the sort
  setStats(1);
  vec_rsort(DATA_SIZE, input_data, scratch, buckets);
  setStats(0);

  // Check the results
  return verify( DATA_SIZE, input_data, verify_data );
}
