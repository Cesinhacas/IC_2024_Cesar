/* Include files */

#include <stddef.h>
#include "blas.h"
#include "untitled_sfun.h"
#include "c18_untitled.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "untitled_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c18_debug_family_names[6] = { "v", "ang", "nargin",
  "nargout", "q", "qr" };

/* Function Declarations */
static void initialize_c18_untitled(SFc18_untitledInstanceStruct *chartInstance);
static void initialize_params_c18_untitled(SFc18_untitledInstanceStruct
  *chartInstance);
static void enable_c18_untitled(SFc18_untitledInstanceStruct *chartInstance);
static void disable_c18_untitled(SFc18_untitledInstanceStruct *chartInstance);
static void c18_update_debugger_state_c18_untitled(SFc18_untitledInstanceStruct *
  chartInstance);
static const mxArray *get_sim_state_c18_untitled(SFc18_untitledInstanceStruct
  *chartInstance);
static void set_sim_state_c18_untitled(SFc18_untitledInstanceStruct
  *chartInstance, const mxArray *c18_st);
static void finalize_c18_untitled(SFc18_untitledInstanceStruct *chartInstance);
static void sf_c18_untitled(SFc18_untitledInstanceStruct *chartInstance);
static void c18_chartstep_c18_untitled(SFc18_untitledInstanceStruct
  *chartInstance);
static void initSimStructsc18_untitled(SFc18_untitledInstanceStruct
  *chartInstance);
static void registerMessagesc18_untitled(SFc18_untitledInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c18_machineNumber, uint32_T
  c18_chartNumber);
static const mxArray *c18_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static void c18_emlrt_marshallIn(SFc18_untitledInstanceStruct *chartInstance,
  const mxArray *c18_qr, const char_T *c18_identifier, real_T c18_y[4]);
static void c18_b_emlrt_marshallIn(SFc18_untitledInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[4]);
static void c18_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static const mxArray *c18_b_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static const mxArray *c18_c_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static real_T c18_c_emlrt_marshallIn(SFc18_untitledInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId);
static void c18_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static const mxArray *c18_d_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static void c18_d_emlrt_marshallIn(SFc18_untitledInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[3]);
static void c18_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static void c18_info_helper(c18_ResolvedFunctionInfo c18_info[28]);
static void c18_realmin(SFc18_untitledInstanceStruct *chartInstance);
static void c18_eml_error(SFc18_untitledInstanceStruct *chartInstance);
static const mxArray *c18_e_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static int32_T c18_e_emlrt_marshallIn(SFc18_untitledInstanceStruct
  *chartInstance, const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId);
static void c18_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static uint8_T c18_f_emlrt_marshallIn(SFc18_untitledInstanceStruct
  *chartInstance, const mxArray *c18_b_is_active_c18_untitled, const char_T
  *c18_identifier);
static uint8_T c18_g_emlrt_marshallIn(SFc18_untitledInstanceStruct
  *chartInstance, const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId);
static void init_dsm_address_info(SFc18_untitledInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c18_untitled(SFc18_untitledInstanceStruct *chartInstance)
{
  chartInstance->c18_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c18_is_active_c18_untitled = 0U;
}

static void initialize_params_c18_untitled(SFc18_untitledInstanceStruct
  *chartInstance)
{
}

static void enable_c18_untitled(SFc18_untitledInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c18_untitled(SFc18_untitledInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c18_update_debugger_state_c18_untitled(SFc18_untitledInstanceStruct *
  chartInstance)
{
}

static const mxArray *get_sim_state_c18_untitled(SFc18_untitledInstanceStruct
  *chartInstance)
{
  const mxArray *c18_st;
  const mxArray *c18_y = NULL;
  int32_T c18_i0;
  real_T c18_u[4];
  const mxArray *c18_b_y = NULL;
  uint8_T c18_hoistedGlobal;
  uint8_T c18_b_u;
  const mxArray *c18_c_y = NULL;
  real_T (*c18_qr)[4];
  c18_qr = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c18_st = NULL;
  c18_st = NULL;
  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_createcellarray(2), FALSE);
  for (c18_i0 = 0; c18_i0 < 4; c18_i0++) {
    c18_u[c18_i0] = (*c18_qr)[c18_i0];
  }

  c18_b_y = NULL;
  sf_mex_assign(&c18_b_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 2, 1, 4),
                FALSE);
  sf_mex_setcell(c18_y, 0, c18_b_y);
  c18_hoistedGlobal = chartInstance->c18_is_active_c18_untitled;
  c18_b_u = c18_hoistedGlobal;
  c18_c_y = NULL;
  sf_mex_assign(&c18_c_y, sf_mex_create("y", &c18_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c18_y, 1, c18_c_y);
  sf_mex_assign(&c18_st, c18_y, FALSE);
  return c18_st;
}

static void set_sim_state_c18_untitled(SFc18_untitledInstanceStruct
  *chartInstance, const mxArray *c18_st)
{
  const mxArray *c18_u;
  real_T c18_dv0[4];
  int32_T c18_i1;
  real_T (*c18_qr)[4];
  c18_qr = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c18_doneDoubleBufferReInit = TRUE;
  c18_u = sf_mex_dup(c18_st);
  c18_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c18_u, 0)), "qr",
                       c18_dv0);
  for (c18_i1 = 0; c18_i1 < 4; c18_i1++) {
    (*c18_qr)[c18_i1] = c18_dv0[c18_i1];
  }

  chartInstance->c18_is_active_c18_untitled = c18_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c18_u, 1)),
     "is_active_c18_untitled");
  sf_mex_destroy(&c18_u);
  c18_update_debugger_state_c18_untitled(chartInstance);
  sf_mex_destroy(&c18_st);
}

static void finalize_c18_untitled(SFc18_untitledInstanceStruct *chartInstance)
{
}

static void sf_c18_untitled(SFc18_untitledInstanceStruct *chartInstance)
{
  int32_T c18_i2;
  int32_T c18_i3;
  real_T (*c18_qr)[4];
  real_T (*c18_q)[4];
  c18_qr = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c18_q = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c18_sfEvent);
  for (c18_i2 = 0; c18_i2 < 4; c18_i2++) {
    _SFD_DATA_RANGE_CHECK((*c18_q)[c18_i2], 0U);
  }

  for (c18_i3 = 0; c18_i3 < 4; c18_i3++) {
    _SFD_DATA_RANGE_CHECK((*c18_qr)[c18_i3], 1U);
  }

  chartInstance->c18_sfEvent = CALL_EVENT;
  c18_chartstep_c18_untitled(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_untitledMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c18_chartstep_c18_untitled(SFc18_untitledInstanceStruct
  *chartInstance)
{
  int32_T c18_i4;
  real_T c18_q[4];
  uint32_T c18_debug_family_var_map[6];
  real_T c18_v[3];
  real_T c18_ang;
  real_T c18_nargin = 1.0;
  real_T c18_nargout = 1.0;
  real_T c18_qr[4];
  int32_T c18_i5;
  real_T c18_x[4];
  real_T c18_y;
  real_T c18_scale;
  int32_T c18_k;
  int32_T c18_b_k;
  real_T c18_b_x;
  real_T c18_c_x;
  real_T c18_absxk;
  real_T c18_t;
  int32_T c18_i6;
  real_T c18_B;
  real_T c18_b_y;
  real_T c18_c_y;
  int32_T c18_i7;
  real_T c18_d_x[3];
  real_T c18_d_y;
  real_T c18_b_scale;
  int32_T c18_c_k;
  int32_T c18_d_k;
  real_T c18_e_x;
  real_T c18_f_x;
  real_T c18_b_absxk;
  real_T c18_b_t;
  real_T c18_b_B;
  real_T c18_e_y;
  real_T c18_f_y;
  int32_T c18_i8;
  real_T c18_g_x;
  real_T c18_h_x;
  real_T c18_a;
  int32_T c18_i9;
  int32_T c18_i10;
  real_T (*c18_b_qr)[4];
  real_T (*c18_b_q)[4];
  boolean_T guard1 = FALSE;
  c18_b_qr = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c18_b_q = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c18_sfEvent);
  for (c18_i4 = 0; c18_i4 < 4; c18_i4++) {
    c18_q[c18_i4] = (*c18_b_q)[c18_i4];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c18_debug_family_names,
    c18_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_v, 0U, c18_d_sf_marshallOut,
    c18_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_ang, 1U, c18_c_sf_marshallOut,
    c18_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_nargin, 2U, c18_c_sf_marshallOut,
    c18_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_nargout, 3U, c18_c_sf_marshallOut,
    c18_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c18_q, 4U, c18_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_qr, 5U, c18_sf_marshallOut,
    c18_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c18_sfEvent, 4);
  for (c18_i5 = 0; c18_i5 < 4; c18_i5++) {
    c18_x[c18_i5] = c18_q[c18_i5];
  }

  c18_y = 0.0;
  c18_realmin(chartInstance);
  c18_scale = 2.2250738585072014E-308;
  for (c18_k = 1; c18_k < 5; c18_k++) {
    c18_b_k = c18_k;
    c18_b_x = c18_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
      "", (real_T)c18_b_k), 1, 4, 1, 0) - 1];
    c18_c_x = c18_b_x;
    c18_absxk = muDoubleScalarAbs(c18_c_x);
    if (c18_absxk > c18_scale) {
      c18_t = c18_scale / c18_absxk;
      c18_y = 1.0 + c18_y * c18_t * c18_t;
      c18_scale = c18_absxk;
    } else {
      c18_t = c18_absxk / c18_scale;
      c18_y += c18_t * c18_t;
    }
  }

  c18_y = c18_scale * muDoubleScalarSqrt(c18_y);
  for (c18_i6 = 0; c18_i6 < 4; c18_i6++) {
    c18_x[c18_i6] = c18_q[c18_i6];
  }

  c18_B = c18_y;
  c18_b_y = c18_B;
  c18_c_y = c18_b_y;
  for (c18_i7 = 0; c18_i7 < 4; c18_i7++) {
    c18_q[c18_i7] = c18_x[c18_i7] / c18_c_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c18_sfEvent, 5);
  c18_d_x[0] = c18_q[1];
  c18_d_x[1] = c18_q[2];
  c18_d_x[2] = c18_q[3];
  c18_d_y = 0.0;
  c18_realmin(chartInstance);
  c18_b_scale = 2.2250738585072014E-308;
  for (c18_c_k = 1; c18_c_k < 4; c18_c_k++) {
    c18_d_k = c18_c_k;
    c18_e_x = c18_d_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c18_d_k), 1, 3, 1, 0) - 1];
    c18_f_x = c18_e_x;
    c18_b_absxk = muDoubleScalarAbs(c18_f_x);
    if (c18_b_absxk > c18_b_scale) {
      c18_b_t = c18_b_scale / c18_b_absxk;
      c18_d_y = 1.0 + c18_d_y * c18_b_t * c18_b_t;
      c18_b_scale = c18_b_absxk;
    } else {
      c18_b_t = c18_b_absxk / c18_b_scale;
      c18_d_y += c18_b_t * c18_b_t;
    }
  }

  c18_d_y = c18_b_scale * muDoubleScalarSqrt(c18_d_y);
  c18_d_x[0] = c18_q[1];
  c18_d_x[1] = c18_q[2];
  c18_d_x[2] = c18_q[3];
  c18_b_B = c18_d_y;
  c18_e_y = c18_b_B;
  c18_f_y = c18_e_y;
  for (c18_i8 = 0; c18_i8 < 3; c18_i8++) {
    c18_v[c18_i8] = c18_d_x[c18_i8] / c18_f_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c18_sfEvent, 6);
  c18_g_x = c18_q[0];
  c18_h_x = c18_g_x;
  guard1 = FALSE;
  if (c18_h_x < -1.0) {
    guard1 = TRUE;
  } else {
    if (1.0 < c18_h_x) {
      guard1 = TRUE;
    }
  }

  if (guard1 == TRUE) {
    c18_eml_error(chartInstance);
  }

  c18_h_x = muDoubleScalarAcos(c18_h_x);
  c18_a = c18_h_x;
  c18_ang = c18_a * 2.0;
  _SFD_EML_CALL(0U, chartInstance->c18_sfEvent, 8);
  for (c18_i9 = 0; c18_i9 < 3; c18_i9++) {
    c18_qr[c18_i9] = c18_v[c18_i9];
  }

  c18_qr[3] = c18_ang;
  _SFD_EML_CALL(0U, chartInstance->c18_sfEvent, -8);
  _SFD_SYMBOL_SCOPE_POP();
  for (c18_i10 = 0; c18_i10 < 4; c18_i10++) {
    (*c18_b_qr)[c18_i10] = c18_qr[c18_i10];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c18_sfEvent);
}

static void initSimStructsc18_untitled(SFc18_untitledInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc18_untitled(SFc18_untitledInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c18_machineNumber, uint32_T
  c18_chartNumber)
{
}

static const mxArray *c18_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_i11;
  real_T c18_b_inData[4];
  int32_T c18_i12;
  real_T c18_u[4];
  const mxArray *c18_y = NULL;
  SFc18_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc18_untitledInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  for (c18_i11 = 0; c18_i11 < 4; c18_i11++) {
    c18_b_inData[c18_i11] = (*(real_T (*)[4])c18_inData)[c18_i11];
  }

  for (c18_i12 = 0; c18_i12 < 4; c18_i12++) {
    c18_u[c18_i12] = c18_b_inData[c18_i12];
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 2, 1, 4), FALSE);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, FALSE);
  return c18_mxArrayOutData;
}

static void c18_emlrt_marshallIn(SFc18_untitledInstanceStruct *chartInstance,
  const mxArray *c18_qr, const char_T *c18_identifier, real_T c18_y[4])
{
  emlrtMsgIdentifier c18_thisId;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_qr), &c18_thisId, c18_y);
  sf_mex_destroy(&c18_qr);
}

static void c18_b_emlrt_marshallIn(SFc18_untitledInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[4])
{
  real_T c18_dv1[4];
  int32_T c18_i13;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), c18_dv1, 1, 0, 0U, 1, 0U, 2, 1,
                4);
  for (c18_i13 = 0; c18_i13 < 4; c18_i13++) {
    c18_y[c18_i13] = c18_dv1[c18_i13];
  }

  sf_mex_destroy(&c18_u);
}

static void c18_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_qr;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  real_T c18_y[4];
  int32_T c18_i14;
  SFc18_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc18_untitledInstanceStruct *)chartInstanceVoid;
  c18_qr = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_qr), &c18_thisId, c18_y);
  sf_mex_destroy(&c18_qr);
  for (c18_i14 = 0; c18_i14 < 4; c18_i14++) {
    (*(real_T (*)[4])c18_outData)[c18_i14] = c18_y[c18_i14];
  }

  sf_mex_destroy(&c18_mxArrayInData);
}

static const mxArray *c18_b_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_i15;
  real_T c18_b_inData[4];
  int32_T c18_i16;
  real_T c18_u[4];
  const mxArray *c18_y = NULL;
  SFc18_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc18_untitledInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  for (c18_i15 = 0; c18_i15 < 4; c18_i15++) {
    c18_b_inData[c18_i15] = (*(real_T (*)[4])c18_inData)[c18_i15];
  }

  for (c18_i16 = 0; c18_i16 < 4; c18_i16++) {
    c18_u[c18_i16] = c18_b_inData[c18_i16];
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, FALSE);
  return c18_mxArrayOutData;
}

static const mxArray *c18_c_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  real_T c18_u;
  const mxArray *c18_y = NULL;
  SFc18_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc18_untitledInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  c18_u = *(real_T *)c18_inData;
  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", &c18_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, FALSE);
  return c18_mxArrayOutData;
}

static real_T c18_c_emlrt_marshallIn(SFc18_untitledInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId)
{
  real_T c18_y;
  real_T c18_d0;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), &c18_d0, 1, 0, 0U, 0, 0U, 0);
  c18_y = c18_d0;
  sf_mex_destroy(&c18_u);
  return c18_y;
}

static void c18_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_nargout;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  real_T c18_y;
  SFc18_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc18_untitledInstanceStruct *)chartInstanceVoid;
  c18_nargout = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_y = c18_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_nargout),
    &c18_thisId);
  sf_mex_destroy(&c18_nargout);
  *(real_T *)c18_outData = c18_y;
  sf_mex_destroy(&c18_mxArrayInData);
}

static const mxArray *c18_d_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_i17;
  real_T c18_b_inData[3];
  int32_T c18_i18;
  real_T c18_u[3];
  const mxArray *c18_y = NULL;
  SFc18_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc18_untitledInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  for (c18_i17 = 0; c18_i17 < 3; c18_i17++) {
    c18_b_inData[c18_i17] = (*(real_T (*)[3])c18_inData)[c18_i17];
  }

  for (c18_i18 = 0; c18_i18 < 3; c18_i18++) {
    c18_u[c18_i18] = c18_b_inData[c18_i18];
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, FALSE);
  return c18_mxArrayOutData;
}

static void c18_d_emlrt_marshallIn(SFc18_untitledInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[3])
{
  real_T c18_dv2[3];
  int32_T c18_i19;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), c18_dv2, 1, 0, 0U, 1, 0U, 2, 1,
                3);
  for (c18_i19 = 0; c18_i19 < 3; c18_i19++) {
    c18_y[c18_i19] = c18_dv2[c18_i19];
  }

  sf_mex_destroy(&c18_u);
}

static void c18_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_v;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  real_T c18_y[3];
  int32_T c18_i20;
  SFc18_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc18_untitledInstanceStruct *)chartInstanceVoid;
  c18_v = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_v), &c18_thisId, c18_y);
  sf_mex_destroy(&c18_v);
  for (c18_i20 = 0; c18_i20 < 3; c18_i20++) {
    (*(real_T (*)[3])c18_outData)[c18_i20] = c18_y[c18_i20];
  }

  sf_mex_destroy(&c18_mxArrayInData);
}

const mxArray *sf_c18_untitled_get_eml_resolved_functions_info(void)
{
  const mxArray *c18_nameCaptureInfo;
  c18_ResolvedFunctionInfo c18_info[28];
  const mxArray *c18_m0 = NULL;
  int32_T c18_i21;
  c18_ResolvedFunctionInfo *c18_r0;
  c18_nameCaptureInfo = NULL;
  c18_nameCaptureInfo = NULL;
  c18_info_helper(c18_info);
  sf_mex_assign(&c18_m0, sf_mex_createstruct("nameCaptureInfo", 1, 28), FALSE);
  for (c18_i21 = 0; c18_i21 < 28; c18_i21++) {
    c18_r0 = &c18_info[c18_i21];
    sf_mex_addfield(c18_m0, sf_mex_create("nameCaptureInfo", c18_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c18_r0->context)), "context", "nameCaptureInfo",
                    c18_i21);
    sf_mex_addfield(c18_m0, sf_mex_create("nameCaptureInfo", c18_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c18_r0->name)), "name", "nameCaptureInfo",
                    c18_i21);
    sf_mex_addfield(c18_m0, sf_mex_create("nameCaptureInfo",
      c18_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c18_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c18_i21);
    sf_mex_addfield(c18_m0, sf_mex_create("nameCaptureInfo", c18_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c18_r0->resolved)), "resolved",
                    "nameCaptureInfo", c18_i21);
    sf_mex_addfield(c18_m0, sf_mex_create("nameCaptureInfo", &c18_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c18_i21);
    sf_mex_addfield(c18_m0, sf_mex_create("nameCaptureInfo", &c18_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c18_i21);
    sf_mex_addfield(c18_m0, sf_mex_create("nameCaptureInfo",
      &c18_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c18_i21);
    sf_mex_addfield(c18_m0, sf_mex_create("nameCaptureInfo",
      &c18_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c18_i21);
  }

  sf_mex_assign(&c18_nameCaptureInfo, c18_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c18_nameCaptureInfo);
  return c18_nameCaptureInfo;
}

static void c18_info_helper(c18_ResolvedFunctionInfo c18_info[28])
{
  c18_info[0].context = "";
  c18_info[0].name = "norm";
  c18_info[0].dominantType = "double";
  c18_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c18_info[0].fileTimeLo = 1336540094U;
  c18_info[0].fileTimeHi = 0U;
  c18_info[0].mFileTimeLo = 0U;
  c18_info[0].mFileTimeHi = 0U;
  c18_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c18_info[1].name = "eml_index_class";
  c18_info[1].dominantType = "";
  c18_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c18_info[1].fileTimeLo = 1323181378U;
  c18_info[1].fileTimeHi = 0U;
  c18_info[1].mFileTimeLo = 0U;
  c18_info[1].mFileTimeHi = 0U;
  c18_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c18_info[2].name = "eml_xnrm2";
  c18_info[2].dominantType = "double";
  c18_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c18_info[2].fileTimeLo = 1299091176U;
  c18_info[2].fileTimeHi = 0U;
  c18_info[2].mFileTimeLo = 0U;
  c18_info[2].mFileTimeHi = 0U;
  c18_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c18_info[3].name = "eml_blas_inline";
  c18_info[3].dominantType = "";
  c18_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c18_info[3].fileTimeLo = 1299091168U;
  c18_info[3].fileTimeHi = 0U;
  c18_info[3].mFileTimeLo = 0U;
  c18_info[3].mFileTimeHi = 0U;
  c18_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c18_info[4].name = "eml_index_class";
  c18_info[4].dominantType = "";
  c18_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c18_info[4].fileTimeLo = 1323181378U;
  c18_info[4].fileTimeHi = 0U;
  c18_info[4].mFileTimeLo = 0U;
  c18_info[4].mFileTimeHi = 0U;
  c18_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c18_info[5].name = "eml_refblas_xnrm2";
  c18_info[5].dominantType = "double";
  c18_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c18_info[5].fileTimeLo = 1299091184U;
  c18_info[5].fileTimeHi = 0U;
  c18_info[5].mFileTimeLo = 0U;
  c18_info[5].mFileTimeHi = 0U;
  c18_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c18_info[6].name = "realmin";
  c18_info[6].dominantType = "char";
  c18_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c18_info[6].fileTimeLo = 1307669242U;
  c18_info[6].fileTimeHi = 0U;
  c18_info[6].mFileTimeLo = 0U;
  c18_info[6].mFileTimeHi = 0U;
  c18_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c18_info[7].name = "eml_realmin";
  c18_info[7].dominantType = "char";
  c18_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c18_info[7].fileTimeLo = 1307669244U;
  c18_info[7].fileTimeHi = 0U;
  c18_info[7].mFileTimeLo = 0U;
  c18_info[7].mFileTimeHi = 0U;
  c18_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c18_info[8].name = "eml_float_model";
  c18_info[8].dominantType = "char";
  c18_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c18_info[8].fileTimeLo = 1326738796U;
  c18_info[8].fileTimeHi = 0U;
  c18_info[8].mFileTimeLo = 0U;
  c18_info[8].mFileTimeHi = 0U;
  c18_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c18_info[9].name = "eml_index_class";
  c18_info[9].dominantType = "";
  c18_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c18_info[9].fileTimeLo = 1323181378U;
  c18_info[9].fileTimeHi = 0U;
  c18_info[9].mFileTimeLo = 0U;
  c18_info[9].mFileTimeHi = 0U;
  c18_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c18_info[10].name = "eml_index_minus";
  c18_info[10].dominantType = "double";
  c18_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c18_info[10].fileTimeLo = 1286836778U;
  c18_info[10].fileTimeHi = 0U;
  c18_info[10].mFileTimeLo = 0U;
  c18_info[10].mFileTimeHi = 0U;
  c18_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c18_info[11].name = "eml_index_class";
  c18_info[11].dominantType = "";
  c18_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c18_info[11].fileTimeLo = 1323181378U;
  c18_info[11].fileTimeHi = 0U;
  c18_info[11].mFileTimeLo = 0U;
  c18_info[11].mFileTimeHi = 0U;
  c18_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c18_info[12].name = "eml_index_times";
  c18_info[12].dominantType = "coder.internal.indexInt";
  c18_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c18_info[12].fileTimeLo = 1286836780U;
  c18_info[12].fileTimeHi = 0U;
  c18_info[12].mFileTimeLo = 0U;
  c18_info[12].mFileTimeHi = 0U;
  c18_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c18_info[13].name = "eml_index_class";
  c18_info[13].dominantType = "";
  c18_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c18_info[13].fileTimeLo = 1323181378U;
  c18_info[13].fileTimeHi = 0U;
  c18_info[13].mFileTimeLo = 0U;
  c18_info[13].mFileTimeHi = 0U;
  c18_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c18_info[14].name = "eml_index_plus";
  c18_info[14].dominantType = "coder.internal.indexInt";
  c18_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c18_info[14].fileTimeLo = 1286836778U;
  c18_info[14].fileTimeHi = 0U;
  c18_info[14].mFileTimeLo = 0U;
  c18_info[14].mFileTimeHi = 0U;
  c18_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c18_info[15].name = "eml_index_class";
  c18_info[15].dominantType = "";
  c18_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c18_info[15].fileTimeLo = 1323181378U;
  c18_info[15].fileTimeHi = 0U;
  c18_info[15].mFileTimeLo = 0U;
  c18_info[15].mFileTimeHi = 0U;
  c18_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c18_info[16].name = "eml_int_forloop_overflow_check";
  c18_info[16].dominantType = "";
  c18_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c18_info[16].fileTimeLo = 1346528340U;
  c18_info[16].fileTimeHi = 0U;
  c18_info[16].mFileTimeLo = 0U;
  c18_info[16].mFileTimeHi = 0U;
  c18_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c18_info[17].name = "intmax";
  c18_info[17].dominantType = "char";
  c18_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c18_info[17].fileTimeLo = 1311273316U;
  c18_info[17].fileTimeHi = 0U;
  c18_info[17].mFileTimeLo = 0U;
  c18_info[17].mFileTimeHi = 0U;
  c18_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c18_info[18].name = "abs";
  c18_info[18].dominantType = "double";
  c18_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c18_info[18].fileTimeLo = 1343848366U;
  c18_info[18].fileTimeHi = 0U;
  c18_info[18].mFileTimeLo = 0U;
  c18_info[18].mFileTimeHi = 0U;
  c18_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c18_info[19].name = "eml_scalar_abs";
  c18_info[19].dominantType = "double";
  c18_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c18_info[19].fileTimeLo = 1286836712U;
  c18_info[19].fileTimeHi = 0U;
  c18_info[19].mFileTimeLo = 0U;
  c18_info[19].mFileTimeHi = 0U;
  c18_info[20].context = "";
  c18_info[20].name = "mrdivide";
  c18_info[20].dominantType = "double";
  c18_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c18_info[20].fileTimeLo = 1357962348U;
  c18_info[20].fileTimeHi = 0U;
  c18_info[20].mFileTimeLo = 1319744366U;
  c18_info[20].mFileTimeHi = 0U;
  c18_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c18_info[21].name = "rdivide";
  c18_info[21].dominantType = "double";
  c18_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c18_info[21].fileTimeLo = 1346528388U;
  c18_info[21].fileTimeHi = 0U;
  c18_info[21].mFileTimeLo = 0U;
  c18_info[21].mFileTimeHi = 0U;
  c18_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c18_info[22].name = "eml_scalexp_compatible";
  c18_info[22].dominantType = "double";
  c18_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c18_info[22].fileTimeLo = 1286836796U;
  c18_info[22].fileTimeHi = 0U;
  c18_info[22].mFileTimeLo = 0U;
  c18_info[22].mFileTimeHi = 0U;
  c18_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c18_info[23].name = "eml_div";
  c18_info[23].dominantType = "double";
  c18_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c18_info[23].fileTimeLo = 1313365810U;
  c18_info[23].fileTimeHi = 0U;
  c18_info[23].mFileTimeLo = 0U;
  c18_info[23].mFileTimeHi = 0U;
  c18_info[24].context = "";
  c18_info[24].name = "acos";
  c18_info[24].dominantType = "double";
  c18_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/acos.m";
  c18_info[24].fileTimeLo = 1343848366U;
  c18_info[24].fileTimeHi = 0U;
  c18_info[24].mFileTimeLo = 0U;
  c18_info[24].mFileTimeHi = 0U;
  c18_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/acos.m";
  c18_info[25].name = "eml_error";
  c18_info[25].dominantType = "char";
  c18_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c18_info[25].fileTimeLo = 1343848358U;
  c18_info[25].fileTimeHi = 0U;
  c18_info[25].mFileTimeLo = 0U;
  c18_info[25].mFileTimeHi = 0U;
  c18_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/acos.m";
  c18_info[26].name = "eml_scalar_acos";
  c18_info[26].dominantType = "double";
  c18_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_acos.m";
  c18_info[26].fileTimeLo = 1343848376U;
  c18_info[26].fileTimeHi = 0U;
  c18_info[26].mFileTimeLo = 0U;
  c18_info[26].mFileTimeHi = 0U;
  c18_info[27].context = "";
  c18_info[27].name = "mtimes";
  c18_info[27].dominantType = "double";
  c18_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c18_info[27].fileTimeLo = 1289530492U;
  c18_info[27].fileTimeHi = 0U;
  c18_info[27].mFileTimeLo = 0U;
  c18_info[27].mFileTimeHi = 0U;
}

static void c18_realmin(SFc18_untitledInstanceStruct *chartInstance)
{
}

static void c18_eml_error(SFc18_untitledInstanceStruct *chartInstance)
{
  int32_T c18_i22;
  static char_T c18_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c18_u[30];
  const mxArray *c18_y = NULL;
  int32_T c18_i23;
  static char_T c18_cv1[4] = { 'a', 'c', 'o', 's' };

  char_T c18_b_u[4];
  const mxArray *c18_b_y = NULL;
  for (c18_i22 = 0; c18_i22 < 30; c18_i22++) {
    c18_u[c18_i22] = c18_cv0[c18_i22];
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 10, 0U, 1U, 0U, 2, 1, 30),
                FALSE);
  for (c18_i23 = 0; c18_i23 < 4; c18_i23++) {
    c18_b_u[c18_i23] = c18_cv1[c18_i23];
  }

  c18_b_y = NULL;
  sf_mex_assign(&c18_b_y, sf_mex_create("y", c18_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U, 14,
    c18_y, 14, c18_b_y));
}

static const mxArray *c18_e_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_u;
  const mxArray *c18_y = NULL;
  SFc18_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc18_untitledInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  c18_u = *(int32_T *)c18_inData;
  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", &c18_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, FALSE);
  return c18_mxArrayOutData;
}

static int32_T c18_e_emlrt_marshallIn(SFc18_untitledInstanceStruct
  *chartInstance, const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId)
{
  int32_T c18_y;
  int32_T c18_i24;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), &c18_i24, 1, 6, 0U, 0, 0U, 0);
  c18_y = c18_i24;
  sf_mex_destroy(&c18_u);
  return c18_y;
}

static void c18_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_b_sfEvent;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  int32_T c18_y;
  SFc18_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc18_untitledInstanceStruct *)chartInstanceVoid;
  c18_b_sfEvent = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_y = c18_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_b_sfEvent),
    &c18_thisId);
  sf_mex_destroy(&c18_b_sfEvent);
  *(int32_T *)c18_outData = c18_y;
  sf_mex_destroy(&c18_mxArrayInData);
}

static uint8_T c18_f_emlrt_marshallIn(SFc18_untitledInstanceStruct
  *chartInstance, const mxArray *c18_b_is_active_c18_untitled, const char_T
  *c18_identifier)
{
  uint8_T c18_y;
  emlrtMsgIdentifier c18_thisId;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_y = c18_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c18_b_is_active_c18_untitled), &c18_thisId);
  sf_mex_destroy(&c18_b_is_active_c18_untitled);
  return c18_y;
}

static uint8_T c18_g_emlrt_marshallIn(SFc18_untitledInstanceStruct
  *chartInstance, const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId)
{
  uint8_T c18_y;
  uint8_T c18_u0;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), &c18_u0, 1, 3, 0U, 0, 0U, 0);
  c18_y = c18_u0;
  sf_mex_destroy(&c18_u);
  return c18_y;
}

static void init_dsm_address_info(SFc18_untitledInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c18_untitled_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(662071341U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1879152U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(110994478U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4171181714U);
}

mxArray *sf_c18_untitled_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("p6peyDa4LZBW4ujGt4Y1AF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(4);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c18_untitled_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c18_untitled(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"qr\",},{M[8],M[0],T\"is_active_c18_untitled\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c18_untitled_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc18_untitledInstanceStruct *chartInstance;
    chartInstance = (SFc18_untitledInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _untitledMachineNumber_,
           18,
           1,
           1,
           2,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_untitledMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_untitledMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _untitledMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"q");
          _SFD_SET_DATA_PROPS(1,2,0,1,"qr");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,132);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c18_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c18_sf_marshallOut,(MexInFcnForType)
            c18_sf_marshallIn);
        }

        {
          real_T (*c18_q)[4];
          real_T (*c18_qr)[4];
          c18_qr = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
          c18_q = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c18_q);
          _SFD_SET_DATA_VALUE_PTR(1U, *c18_qr);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _untitledMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "6RILy90kegE0msbIE8qFsD";
}

static void sf_opaque_initialize_c18_untitled(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc18_untitledInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c18_untitled((SFc18_untitledInstanceStruct*)
    chartInstanceVar);
  initialize_c18_untitled((SFc18_untitledInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c18_untitled(void *chartInstanceVar)
{
  enable_c18_untitled((SFc18_untitledInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c18_untitled(void *chartInstanceVar)
{
  disable_c18_untitled((SFc18_untitledInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c18_untitled(void *chartInstanceVar)
{
  sf_c18_untitled((SFc18_untitledInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c18_untitled(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c18_untitled((SFc18_untitledInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c18_untitled();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c18_untitled(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c18_untitled();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c18_untitled((SFc18_untitledInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c18_untitled(SimStruct* S)
{
  return sf_internal_get_sim_state_c18_untitled(S);
}

static void sf_opaque_set_sim_state_c18_untitled(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c18_untitled(S, st);
}

static void sf_opaque_terminate_c18_untitled(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc18_untitledInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_untitled_optimization_info();
    }

    finalize_c18_untitled((SFc18_untitledInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc18_untitled((SFc18_untitledInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c18_untitled(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c18_untitled((SFc18_untitledInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c18_untitled(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_untitled_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      18);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,18,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,18,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,18);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,18,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,18,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,18);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3008507530U));
  ssSetChecksum1(S,(673201665U));
  ssSetChecksum2(S,(1675415352U));
  ssSetChecksum3(S,(274125522U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c18_untitled(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c18_untitled(SimStruct *S)
{
  SFc18_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc18_untitledInstanceStruct *)utMalloc(sizeof
    (SFc18_untitledInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc18_untitledInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c18_untitled;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c18_untitled;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c18_untitled;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c18_untitled;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c18_untitled;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c18_untitled;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c18_untitled;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c18_untitled;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c18_untitled;
  chartInstance->chartInfo.mdlStart = mdlStart_c18_untitled;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c18_untitled;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c18_untitled_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c18_untitled(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c18_untitled(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c18_untitled(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c18_untitled_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
