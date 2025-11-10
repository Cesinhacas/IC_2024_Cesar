/*
 * File: propagador_FK.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 04-Nov-2025 17:35:10
 */

#ifndef PROPAGADOR_FK_H
#define PROPAGADOR_FK_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void propagador_FK(const double u_gyro[3], double Dt,
                          const double PT_est[36], const double x_est[7],
                          const double Q[36], double i_in, double x_prop[7],
                          double PT_prop[36], double *i_out);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for propagador_FK.h
 *
 * [EOF]
 */
