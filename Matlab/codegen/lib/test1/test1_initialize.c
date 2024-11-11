/*
 * File: test1_initialize.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Oct-2024 09:49:55
 */

/* Include Files */
#include "test1_initialize.h"
#include "CoderTimeAPI.h"
#include "rt_nonfinite.h"
#include "test1_data.h"
#include "timeKeeper.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void test1_initialize(void)
{
  rt_InitInfAndNaN();
  savedTime_not_empty_init();
  freq_not_empty_init();
  isInitialized_test1 = true;
}

/*
 * File trailer for test1_initialize.c
 *
 * [EOF]
 */
