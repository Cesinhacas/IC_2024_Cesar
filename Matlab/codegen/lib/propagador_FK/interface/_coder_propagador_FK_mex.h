/*
 * File: _coder_propagador_FK_mex.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 04-Nov-2025 17:35:10
 */

#ifndef _CODER_PROPAGADOR_FK_MEX_H
#define _CODER_PROPAGADOR_FK_MEX_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS(void);

void unsafe_propagador_FK_mexFunction(int32_T nlhs, mxArray *plhs[3],
                                      int32_T nrhs, const mxArray *prhs[6]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_propagador_FK_mex.h
 *
 * [EOF]
 */
