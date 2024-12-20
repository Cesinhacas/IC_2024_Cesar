/*
 * File: toc.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Oct-2024 09:49:55
 */

/* Include Files */
#include "toc.h"
#include "rt_nonfinite.h"
#include "test1_data.h"
#include "timeKeeper.h"
#include "coder_posix_time.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : double
 */
double toc(void)
{
  coderTimespec b_timespec;
  double tstart_tv_nsec;
  double tstart_tv_sec;
  b_timeKeeper(&tstart_tv_sec, &tstart_tv_nsec);
  if (!freq_not_empty) {
    freq_not_empty = true;
    coderInitTimeFunctions(&freq);
  }
  coderTimeClockGettimeMonotonic(&b_timespec, freq);
  return (b_timespec.tv_sec - tstart_tv_sec) +
         (b_timespec.tv_nsec - tstart_tv_nsec) / 1.0E+9;
}

/*
 * File trailer for toc.c
 *
 * [EOF]
 */
