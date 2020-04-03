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

void sort(size_t n, type* arrIn, type* scratchIn)
{
  size_t log_exp = 0;
  size_t buckets[BASE];
  size_t *bucket = buckets;
  asm("":"+r"(bucket));
  type *arr = arrIn, *scratch = scratchIn, *p;
  size_t *b;

  while (log_exp < CHAR_BIT * sizeof(type))
  {
    for (b = bucket; b < bucket + BASE; b++)
      *b = 0;

    for (p = arr; p < &arr[n-3]; p += 4)
    {
      type a0 = p[0];
      type a1 = p[1];
      type a2 = p[2];
      type a3 = p[3];
      bucket[(a0 >> log_exp) % BASE]++;
      bucket[(a1 >> log_exp) % BASE]++;
      bucket[(a2 >> log_exp) % BASE]++;
      bucket[(a3 >> log_exp) % BASE]++;
    }
    for ( ; p < &arr[n]; p++)
      bucket[(*p >> log_exp) % BASE]++;

    size_t prev = 0;
    for (b = bucket; b < bucket + BASE; b ++)
    {
      prev += *b;
      *b = prev;
    }

    for (p = &arr[n-1]; p >= &arr[3]; p -= 4)
    {
      type a0 = p[-0];
      type a1 = p[-1];
      type a2 = p[-2];
      type a3 = p[-3];
      scratch[--bucket[(a0 >> log_exp) % BASE]] = a0;
      scratch[--bucket[(a1 >> log_exp) % BASE]] = a1;
      scratch[--bucket[(a2 >> log_exp) % BASE]] = a2;
      scratch[--bucket[(a3 >> log_exp) % BASE]] = a3;
    }
    for ( ; p >= &arr[0]; p--)
      scratch[--bucket[(*p >> log_exp) % BASE]] = *p;
    type* tmp = arr;
    arr = scratch;
    scratch = tmp;

    log_exp += LOG_BASE;
  }
  if (arrIn != arr)
    memcpy(arrIn, arr, n*sizeof(type));
}

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  static type scratch[DATA_SIZE];

  // Do the sort
  setStats(1);
  sort(DATA_SIZE, input_data, scratch);
  setStats(0);

  // Check the results
  return verify( DATA_SIZE, input_data, verify_data );
}
