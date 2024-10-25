/*
 * File: _coder_test1_api.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Oct-2024 09:49:55
 */

/* Include Files */
#include "_coder_test1_api.h"
#include "_coder_test1_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131627U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "test1",                                              /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3336];

static const mxArray *b_emlrt_marshallOut(const real_T u[9]);

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3336];

static real_T (*emlrt_marshallIn(const emlrtStack *sp,
                                 const mxArray *Dados_Corrompido,
                                 const char_T *identifier))[3336];

static const mxArray *emlrt_marshallOut(const real_T u);

/* Function Definitions */
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[3336]
 */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3336]
{
  real_T(*y)[3336];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const real_T u[9]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real_T u[9])
{
  static const int32_T i = 0;
  static const int32_T i1 = 9;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[3336]
 */
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3336]
{
  static const int32_T dims[2] = {3, 1112};
  real_T(*ret)[3336];
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 2U,
                          (const void *)&dims[0]);
  ret = (real_T(*)[3336])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *Dados_Corrompido
 *                const char_T *identifier
 * Return Type  : real_T (*)[3336]
 */
static real_T (*emlrt_marshallIn(const emlrtStack *sp,
                                 const mxArray *Dados_Corrompido,
                                 const char_T *identifier))[3336]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[3336];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(Dados_Corrompido), &thisId);
  emlrtDestroyArray(&Dados_Corrompido);
  return y;
}

/*
 * Arguments    : const real_T u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const mxArray *prhs
 *                int32_T nlhs
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void test1_api(const mxArray *prhs, int32_T nlhs, const mxArray *plhs[2])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  real_T(*Dados_Corrompido)[3336];
  real_T(*p1)[9];
  real_T Time;
  st.tls = emlrtRootTLSGlobal;
  p1 = (real_T(*)[9])mxMalloc(sizeof(real_T[9]));
  /* Marshall function inputs */
  Dados_Corrompido =
      emlrt_marshallIn(&st, emlrtAlias(prhs), "Dados_Corrompido");
  /* Invoke the target function */
  test1(*Dados_Corrompido, &Time, *p1);
  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(Time);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*p1);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void test1_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  test1_xil_terminate();
  test1_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void test1_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void test1_terminate(void)
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_test1_api.c
 *
 * [EOF]
 */
