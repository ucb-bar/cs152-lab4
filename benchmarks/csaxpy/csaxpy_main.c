// See LICENSE for license details.

//**************************************************************************
// csaxpy benchmark
//--------------------------------------------------------------------------
//

#include "util.h"
#include "csaxpy.h"

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset1.h"

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  // Do the SAXPY
  setStats(1);
  csaxpy(DATA_SIZE, input_cond, input_data_a, input_data_X, input_data_Y);
  setStats(0);

  // Check the results
  return verifyFloat(DATA_SIZE, input_data_Y, verify_data);
}
