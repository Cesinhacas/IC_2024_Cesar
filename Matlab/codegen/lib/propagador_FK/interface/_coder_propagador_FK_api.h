/*
 * File: _coder_propagador_FK_api.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 04-Nov-2025 17:35:10
 */

#ifndef _CODER_PROPAGADOR_FK_API_H
#define _CODER_PROPAGADOR_FK_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void propagador_FK(real_T u_gyro[3], real_T Dt, real_T PT_est[36],
                   real_T x_est[7], real_T Q[36], real_T i_in, real_T x_prop[7],
                   real_T PT_prop[36], real_T *i_out);

void propagador_FK_api(const mxArray *const prhs[6], int32_T nlhs,
                       const mxArray *plhs[3]);

void propagador_FK_atexit(void);

void propagador_FK_initialize(void);

void propagador_FK_terminate(void);

void propagador_FK_xil_shutdown(void);

void propagador_FK_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_propagador_FK_api.h
 *
 * [EOF]
 */
