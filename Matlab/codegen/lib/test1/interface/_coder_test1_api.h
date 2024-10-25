/*
 * File: _coder_test1_api.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Oct-2024 09:49:55
 */

#ifndef _CODER_TEST1_API_H
#define _CODER_TEST1_API_H

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
void test1(real_T Dados_Corrompido[3336], real_T *Time, real_T p1[9]);

void test1_api(const mxArray *prhs, int32_T nlhs, const mxArray *plhs[2]);

void test1_atexit(void);

void test1_initialize(void);

void test1_terminate(void);

void test1_xil_shutdown(void);

void test1_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_test1_api.h
 *
 * [EOF]
 */
