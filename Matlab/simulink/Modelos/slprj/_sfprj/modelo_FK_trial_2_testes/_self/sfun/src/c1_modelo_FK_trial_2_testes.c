/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_FK_trial_2_testes_sfun.h"
#include "c1_modelo_FK_trial_2_testes.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "modelo_FK_trial_2_testes_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[13] = { "wx", "wy", "wz", "qteta",
  "qx", "qy", "qz", "W", "nargin", "nargout", "w", "q", "dq" };

/* Function Declarations */
static void initialize_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void initialize_params_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void enable_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void disable_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void set_sim_state_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c1_st);
static void finalize_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void sf_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void c1_chartstep_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void initSimStructsc1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void registerMessagesc1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_dq, const char_T *c1_identifier, real_T
  c1_y[4]);
static void c1_b_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[4]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_c_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct *
  chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_d_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[16]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[33]);
static real_T c1_norm(SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance,
                      real_T c1_x[4]);
static void c1_eml_scalar_eg(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_e_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_f_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_modelo_FK_trial_2_testes,
  const char_T *c1_identifier);
static uint8_T c1_g_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_modelo_FK_trial_2_testes = 0U;
}

static void initialize_params_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
}

static void enable_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  real_T c1_u[4];
  const mxArray *c1_b_y = NULL;
  uint8_T c1_hoistedGlobal;
  uint8_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T (*c1_dq)[4];
  c1_dq = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(2), FALSE);
  for (c1_i0 = 0; c1_i0 < 4; c1_i0++) {
    c1_u[c1_i0] = (*c1_dq)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = chartInstance->c1_is_active_c1_modelo_FK_trial_2_testes;
  c1_b_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[4];
  int32_T c1_i1;
  real_T (*c1_dq)[4];
  c1_dq = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)), "dq",
                      c1_dv0);
  for (c1_i1 = 0; c1_i1 < 4; c1_i1++) {
    (*c1_dq)[c1_i1] = c1_dv0[c1_i1];
  }

  chartInstance->c1_is_active_c1_modelo_FK_trial_2_testes =
    c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
    "is_active_c1_modelo_FK_trial_2_testes");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_modelo_FK_trial_2_testes(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
}

static void sf_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  real_T (*c1_q)[4];
  real_T (*c1_dq)[4];
  real_T (*c1_w)[3];
  c1_q = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c1_dq = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_w = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i2 = 0; c1_i2 < 3; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*c1_w)[c1_i2], 0U);
  }

  for (c1_i3 = 0; c1_i3 < 4; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((*c1_dq)[c1_i3], 1U);
  }

  for (c1_i4 = 0; c1_i4 < 4; c1_i4++) {
    _SFD_DATA_RANGE_CHECK((*c1_q)[c1_i4], 2U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_modelo_FK_trial_2_testes(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_modelo_FK_trial_2_testesMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  int32_T c1_i5;
  real_T c1_w[3];
  int32_T c1_i6;
  real_T c1_q[4];
  uint32_T c1_debug_family_var_map[13];
  real_T c1_wx;
  real_T c1_wy;
  real_T c1_wz;
  real_T c1_qteta;
  real_T c1_qx;
  real_T c1_qy;
  real_T c1_qz;
  real_T c1_W[16];
  real_T c1_nargin = 2.0;
  real_T c1_nargout = 1.0;
  real_T c1_dq[4];
  int32_T c1_i7;
  real_T c1_A[4];
  int32_T c1_i8;
  real_T c1_b_q[4];
  real_T c1_B;
  real_T c1_y;
  real_T c1_b_y;
  int32_T c1_i9;
  int32_T c1_i10;
  real_T c1_b[16];
  int32_T c1_i11;
  real_T c1_b_qteta[4];
  int32_T c1_i12;
  int32_T c1_i13;
  int32_T c1_i14;
  int32_T c1_i15;
  real_T c1_C[4];
  int32_T c1_i16;
  int32_T c1_i17;
  int32_T c1_i18;
  int32_T c1_i19;
  int32_T c1_i20;
  int32_T c1_i21;
  int32_T c1_i22;
  real_T (*c1_b_dq)[4];
  real_T (*c1_c_q)[4];
  real_T (*c1_b_w)[3];
  c1_c_q = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_dq = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_w = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i5 = 0; c1_i5 < 3; c1_i5++) {
    c1_w[c1_i5] = (*c1_b_w)[c1_i5];
  }

  for (c1_i6 = 0; c1_i6 < 4; c1_i6++) {
    c1_q[c1_i6] = (*c1_c_q)[c1_i6];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_wx, 0U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_wy, 1U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_wz, 2U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_qteta, 3U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_qx, 4U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_qy, 5U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_qz, 6U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_W, 7U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 8U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 9U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_w, 10U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_q, 11U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_dq, 12U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 3);
  c1_wx = c1_w[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  c1_wy = c1_w[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
  c1_wz = c1_w[2];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
  for (c1_i7 = 0; c1_i7 < 4; c1_i7++) {
    c1_A[c1_i7] = c1_q[c1_i7];
  }

  for (c1_i8 = 0; c1_i8 < 4; c1_i8++) {
    c1_b_q[c1_i8] = c1_q[c1_i8];
  }

  c1_B = c1_norm(chartInstance, c1_b_q);
  c1_y = c1_B;
  c1_b_y = c1_y;
  for (c1_i9 = 0; c1_i9 < 4; c1_i9++) {
    c1_q[c1_i9] = c1_A[c1_i9] / c1_b_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
  c1_qteta = c1_q[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  c1_qx = c1_q[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  c1_qy = c1_q[2];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  c1_qz = c1_q[3];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
  c1_W[0] = 0.0;
  c1_W[4] = -c1_wx;
  c1_W[8] = -c1_wy;
  c1_W[12] = -c1_wz;
  c1_W[1] = c1_wx;
  c1_W[5] = 0.0;
  c1_W[9] = c1_wz;
  c1_W[13] = -c1_wy;
  c1_W[2] = c1_wy;
  c1_W[6] = -c1_wz;
  c1_W[10] = 0.0;
  c1_W[14] = c1_wx;
  c1_W[3] = c1_wz;
  c1_W[7] = c1_wy;
  c1_W[11] = -c1_wx;
  c1_W[15] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  for (c1_i10 = 0; c1_i10 < 16; c1_i10++) {
    c1_b[c1_i10] = c1_W[c1_i10];
  }

  for (c1_i11 = 0; c1_i11 < 16; c1_i11++) {
    c1_b[c1_i11] *= 0.5;
  }

  c1_b_qteta[0] = c1_qteta;
  c1_b_qteta[1] = c1_qx;
  c1_b_qteta[2] = c1_qy;
  c1_b_qteta[3] = c1_qz;
  for (c1_i12 = 0; c1_i12 < 4; c1_i12++) {
    c1_A[c1_i12] = c1_b_qteta[c1_i12];
  }

  c1_eml_scalar_eg(chartInstance);
  c1_eml_scalar_eg(chartInstance);
  for (c1_i13 = 0; c1_i13 < 4; c1_i13++) {
    c1_dq[c1_i13] = 0.0;
  }

  for (c1_i14 = 0; c1_i14 < 4; c1_i14++) {
    c1_dq[c1_i14] = 0.0;
  }

  for (c1_i15 = 0; c1_i15 < 4; c1_i15++) {
    c1_C[c1_i15] = c1_dq[c1_i15];
  }

  for (c1_i16 = 0; c1_i16 < 4; c1_i16++) {
    c1_dq[c1_i16] = c1_C[c1_i16];
  }

  for (c1_i17 = 0; c1_i17 < 4; c1_i17++) {
    c1_C[c1_i17] = c1_dq[c1_i17];
  }

  for (c1_i18 = 0; c1_i18 < 4; c1_i18++) {
    c1_dq[c1_i18] = c1_C[c1_i18];
  }

  for (c1_i19 = 0; c1_i19 < 4; c1_i19++) {
    c1_dq[c1_i19] = 0.0;
    c1_i20 = 0;
    for (c1_i21 = 0; c1_i21 < 4; c1_i21++) {
      c1_dq[c1_i19] += c1_b[c1_i20 + c1_i19] * c1_A[c1_i21];
      c1_i20 += 4;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -16);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i22 = 0; c1_i22 < 4; c1_i22++) {
    (*c1_b_dq)[c1_i22] = c1_dq[c1_i22];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
}

static void registerMessagesc1_modelo_FK_trial_2_testes
  (SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i23;
  real_T c1_b_inData[4];
  int32_T c1_i24;
  real_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i23 = 0; c1_i23 < 4; c1_i23++) {
    c1_b_inData[c1_i23] = (*(real_T (*)[4])c1_inData)[c1_i23];
  }

  for (c1_i24 = 0; c1_i24 < 4; c1_i24++) {
    c1_u[c1_i24] = c1_b_inData[c1_i24];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_dq, const char_T *c1_identifier, real_T
  c1_y[4])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_dq), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_dq);
}

static void c1_b_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[4])
{
  real_T c1_dv1[4];
  int32_T c1_i25;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv1, 1, 0, 0U, 1, 0U, 1, 4);
  for (c1_i25 = 0; c1_i25 < 4; c1_i25++) {
    c1_y[c1_i25] = c1_dv1[c1_i25];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_dq;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[4];
  int32_T c1_i26;
  SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c1_dq = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_dq), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_dq);
  for (c1_i26 = 0; c1_i26 < 4; c1_i26++) {
    (*(real_T (*)[4])c1_outData)[c1_i26] = c1_y[c1_i26];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i27;
  real_T c1_b_inData[3];
  int32_T c1_i28;
  real_T c1_u[3];
  const mxArray *c1_y = NULL;
  SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i27 = 0; c1_i27 < 3; c1_i27++) {
    c1_b_inData[c1_i27] = (*(real_T (*)[3])c1_inData)[c1_i27];
  }

  for (c1_i28 = 0; c1_i28 < 3; c1_i28++) {
    c1_u[c1_i28] = c1_b_inData[c1_i28];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_c_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct *
  chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i29;
  int32_T c1_i30;
  int32_T c1_i31;
  real_T c1_b_inData[16];
  int32_T c1_i32;
  int32_T c1_i33;
  int32_T c1_i34;
  real_T c1_u[16];
  const mxArray *c1_y = NULL;
  SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i29 = 0;
  for (c1_i30 = 0; c1_i30 < 4; c1_i30++) {
    for (c1_i31 = 0; c1_i31 < 4; c1_i31++) {
      c1_b_inData[c1_i31 + c1_i29] = (*(real_T (*)[16])c1_inData)[c1_i31 +
        c1_i29];
    }

    c1_i29 += 4;
  }

  c1_i32 = 0;
  for (c1_i33 = 0; c1_i33 < 4; c1_i33++) {
    for (c1_i34 = 0; c1_i34 < 4; c1_i34++) {
      c1_u[c1_i34 + c1_i32] = c1_b_inData[c1_i34 + c1_i32];
    }

    c1_i32 += 4;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 4, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_d_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[16])
{
  real_T c1_dv2[16];
  int32_T c1_i35;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv2, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c1_i35 = 0; c1_i35 < 16; c1_i35++) {
    c1_y[c1_i35] = c1_dv2[c1_i35];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_W;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[16];
  int32_T c1_i36;
  int32_T c1_i37;
  int32_T c1_i38;
  SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c1_W = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_W), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_W);
  c1_i36 = 0;
  for (c1_i37 = 0; c1_i37 < 4; c1_i37++) {
    for (c1_i38 = 0; c1_i38 < 4; c1_i38++) {
      (*(real_T (*)[16])c1_outData)[c1_i38 + c1_i36] = c1_y[c1_i38 + c1_i36];
    }

    c1_i36 += 4;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_modelo_FK_trial_2_testes_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[33];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i39;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 33), FALSE);
  for (c1_i39 = 0; c1_i39 < 33; c1_i39++) {
    c1_r0 = &c1_info[c1_i39];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i39);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i39);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i39);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i39);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i39);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i39);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i39);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i39);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[33])
{
  c1_info[0].context = "";
  c1_info[0].name = "norm";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c1_info[0].fileTimeLo = 1336540094U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c1_info[1].name = "eml_index_class";
  c1_info[1].dominantType = "";
  c1_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[1].fileTimeLo = 1323181378U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c1_info[2].name = "eml_xnrm2";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c1_info[2].fileTimeLo = 1299091176U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c1_info[3].name = "eml_blas_inline";
  c1_info[3].dominantType = "";
  c1_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c1_info[3].fileTimeLo = 1299091168U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c1_info[4].name = "eml_index_class";
  c1_info[4].dominantType = "";
  c1_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[4].fileTimeLo = 1323181378U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c1_info[5].name = "eml_refblas_xnrm2";
  c1_info[5].dominantType = "double";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[5].fileTimeLo = 1299091184U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[6].name = "realmin";
  c1_info[6].dominantType = "char";
  c1_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c1_info[6].fileTimeLo = 1307669242U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c1_info[7].name = "eml_realmin";
  c1_info[7].dominantType = "char";
  c1_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c1_info[7].fileTimeLo = 1307669244U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c1_info[8].name = "eml_float_model";
  c1_info[8].dominantType = "char";
  c1_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[8].fileTimeLo = 1326738796U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[9].name = "eml_index_class";
  c1_info[9].dominantType = "";
  c1_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[9].fileTimeLo = 1323181378U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[10].name = "eml_index_minus";
  c1_info[10].dominantType = "double";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[10].fileTimeLo = 1286836778U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[11].name = "eml_index_class";
  c1_info[11].dominantType = "";
  c1_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[11].fileTimeLo = 1323181378U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[12].name = "eml_index_times";
  c1_info[12].dominantType = "coder.internal.indexInt";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[12].fileTimeLo = 1286836780U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[13].name = "eml_index_class";
  c1_info[13].dominantType = "";
  c1_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[13].fileTimeLo = 1323181378U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[14].name = "eml_index_plus";
  c1_info[14].dominantType = "coder.internal.indexInt";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[14].fileTimeLo = 1286836778U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[15].name = "eml_index_class";
  c1_info[15].dominantType = "";
  c1_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[15].fileTimeLo = 1323181378U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[16].name = "eml_int_forloop_overflow_check";
  c1_info[16].dominantType = "";
  c1_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[16].fileTimeLo = 1346528340U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c1_info[17].name = "intmax";
  c1_info[17].dominantType = "char";
  c1_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[17].fileTimeLo = 1311273316U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 0U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[18].name = "abs";
  c1_info[18].dominantType = "double";
  c1_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[18].fileTimeLo = 1343848366U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[19].name = "eml_scalar_abs";
  c1_info[19].dominantType = "double";
  c1_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[19].fileTimeLo = 1286836712U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context = "";
  c1_info[20].name = "mrdivide";
  c1_info[20].dominantType = "double";
  c1_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[20].fileTimeLo = 1357962348U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 1319744366U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[21].name = "rdivide";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[21].fileTimeLo = 1346528388U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
  c1_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[22].name = "eml_scalexp_compatible";
  c1_info[22].dominantType = "double";
  c1_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c1_info[22].fileTimeLo = 1286836796U;
  c1_info[22].fileTimeHi = 0U;
  c1_info[22].mFileTimeLo = 0U;
  c1_info[22].mFileTimeHi = 0U;
  c1_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[23].name = "eml_div";
  c1_info[23].dominantType = "double";
  c1_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[23].fileTimeLo = 1313365810U;
  c1_info[23].fileTimeHi = 0U;
  c1_info[23].mFileTimeLo = 0U;
  c1_info[23].mFileTimeHi = 0U;
  c1_info[24].context = "";
  c1_info[24].name = "mtimes";
  c1_info[24].dominantType = "double";
  c1_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[24].fileTimeLo = 1289530492U;
  c1_info[24].fileTimeHi = 0U;
  c1_info[24].mFileTimeLo = 0U;
  c1_info[24].mFileTimeHi = 0U;
  c1_info[25].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[25].name = "eml_index_class";
  c1_info[25].dominantType = "";
  c1_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[25].fileTimeLo = 1323181378U;
  c1_info[25].fileTimeHi = 0U;
  c1_info[25].mFileTimeLo = 0U;
  c1_info[25].mFileTimeHi = 0U;
  c1_info[26].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[26].name = "eml_scalar_eg";
  c1_info[26].dominantType = "double";
  c1_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[26].fileTimeLo = 1286836796U;
  c1_info[26].fileTimeHi = 0U;
  c1_info[26].mFileTimeLo = 0U;
  c1_info[26].mFileTimeHi = 0U;
  c1_info[27].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[27].name = "eml_xgemm";
  c1_info[27].dominantType = "char";
  c1_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c1_info[27].fileTimeLo = 1299091172U;
  c1_info[27].fileTimeHi = 0U;
  c1_info[27].mFileTimeLo = 0U;
  c1_info[27].mFileTimeHi = 0U;
  c1_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c1_info[28].name = "eml_blas_inline";
  c1_info[28].dominantType = "";
  c1_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c1_info[28].fileTimeLo = 1299091168U;
  c1_info[28].fileTimeHi = 0U;
  c1_info[28].mFileTimeLo = 0U;
  c1_info[28].mFileTimeHi = 0U;
  c1_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c1_info[29].name = "mtimes";
  c1_info[29].dominantType = "double";
  c1_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[29].fileTimeLo = 1289530492U;
  c1_info[29].fileTimeHi = 0U;
  c1_info[29].mFileTimeLo = 0U;
  c1_info[29].mFileTimeHi = 0U;
  c1_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[30].name = "eml_index_class";
  c1_info[30].dominantType = "";
  c1_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[30].fileTimeLo = 1323181378U;
  c1_info[30].fileTimeHi = 0U;
  c1_info[30].mFileTimeLo = 0U;
  c1_info[30].mFileTimeHi = 0U;
  c1_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[31].name = "eml_scalar_eg";
  c1_info[31].dominantType = "double";
  c1_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[31].fileTimeLo = 1286836796U;
  c1_info[31].fileTimeHi = 0U;
  c1_info[31].mFileTimeLo = 0U;
  c1_info[31].mFileTimeHi = 0U;
  c1_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[32].name = "eml_refblas_xgemm";
  c1_info[32].dominantType = "char";
  c1_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[32].fileTimeLo = 1299091174U;
  c1_info[32].fileTimeHi = 0U;
  c1_info[32].mFileTimeLo = 0U;
  c1_info[32].mFileTimeHi = 0U;
}

static real_T c1_norm(SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance,
                      real_T c1_x[4])
{
  real_T c1_y;
  real_T c1_scale;
  int32_T c1_k;
  int32_T c1_b_k;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_absxk;
  real_T c1_t;
  c1_y = 0.0;
  c1_scale = 2.2250738585072014E-308;
  for (c1_k = 1; c1_k < 5; c1_k++) {
    c1_b_k = c1_k;
    c1_b_x = c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c1_b_k), 1, 4, 1, 0) - 1];
    c1_c_x = c1_b_x;
    c1_absxk = muDoubleScalarAbs(c1_c_x);
    if (c1_absxk > c1_scale) {
      c1_t = c1_scale / c1_absxk;
      c1_y = 1.0 + c1_y * c1_t * c1_t;
      c1_scale = c1_absxk;
    } else {
      c1_t = c1_absxk / c1_scale;
      c1_y += c1_t * c1_t;
    }
  }

  return c1_scale * muDoubleScalarSqrt(c1_y);
}

static void c1_eml_scalar_eg(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance)
{
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_e_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i40;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i40, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i40;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_f_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_modelo_FK_trial_2_testes,
  const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_modelo_FK_trial_2_testes), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_modelo_FK_trial_2_testes);
  return c1_y;
}

static uint8_T c1_g_emlrt_marshallIn(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance)
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

void sf_c1_modelo_FK_trial_2_testes_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3829568654U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1377471113U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2990145211U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(501585055U);
}

mxArray *sf_c1_modelo_FK_trial_2_testes_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("2HPNXlZ05B6D4npywqwmxF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_modelo_FK_trial_2_testes_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c1_modelo_FK_trial_2_testes(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"dq\",},{M[8],M[0],T\"is_active_c1_modelo_FK_trial_2_testes\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_modelo_FK_trial_2_testes_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
    chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modelo_FK_trial_2_testesMachineNumber_,
           1,
           1,
           1,
           3,
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
          init_script_number_translation(_modelo_FK_trial_2_testesMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_modelo_FK_trial_2_testesMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _modelo_FK_trial_2_testesMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"w");
          _SFD_SET_DATA_PROPS(1,2,0,1,"dq");
          _SFD_SET_DATA_PROPS(2,1,1,0,"q");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,282);
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
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c1_w)[3];
          real_T (*c1_dq)[4];
          real_T (*c1_q)[4];
          c1_q = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
          c1_dq = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
          c1_w = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_w);
          _SFD_SET_DATA_VALUE_PTR(1U, *c1_dq);
          _SFD_SET_DATA_VALUE_PTR(2U, *c1_q);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _modelo_FK_trial_2_testesMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "JBWkLM5DSWFXDV8UVz6i1C";
}

static void sf_opaque_initialize_c1_modelo_FK_trial_2_testes(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_modelo_FK_trial_2_testesInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_modelo_FK_trial_2_testes
    ((SFc1_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
  initialize_c1_modelo_FK_trial_2_testes
    ((SFc1_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_modelo_FK_trial_2_testes(void *chartInstanceVar)
{
  enable_c1_modelo_FK_trial_2_testes
    ((SFc1_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_modelo_FK_trial_2_testes(void *chartInstanceVar)
{
  disable_c1_modelo_FK_trial_2_testes
    ((SFc1_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_modelo_FK_trial_2_testes(void *chartInstanceVar)
{
  sf_c1_modelo_FK_trial_2_testes((SFc1_modelo_FK_trial_2_testesInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_modelo_FK_trial_2_testes
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_modelo_FK_trial_2_testes
    ((SFc1_modelo_FK_trial_2_testesInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_modelo_FK_trial_2_testes();/* state var info */
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

extern void sf_internal_set_sim_state_c1_modelo_FK_trial_2_testes(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_modelo_FK_trial_2_testes();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_modelo_FK_trial_2_testes
    ((SFc1_modelo_FK_trial_2_testesInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_modelo_FK_trial_2_testes
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c1_modelo_FK_trial_2_testes(S);
}

static void sf_opaque_set_sim_state_c1_modelo_FK_trial_2_testes(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c1_modelo_FK_trial_2_testes(S, st);
}

static void sf_opaque_terminate_c1_modelo_FK_trial_2_testes(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_modelo_FK_trial_2_testesInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_FK_trial_2_testes_optimization_info();
    }

    finalize_c1_modelo_FK_trial_2_testes
      ((SFc1_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_modelo_FK_trial_2_testes
    ((SFc1_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_modelo_FK_trial_2_testes(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_modelo_FK_trial_2_testes
      ((SFc1_modelo_FK_trial_2_testesInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_modelo_FK_trial_2_testes(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_modelo_FK_trial_2_testes_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1583644521U));
  ssSetChecksum1(S,(3087570467U));
  ssSetChecksum2(S,(3589176232U));
  ssSetChecksum3(S,(1748326344U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_modelo_FK_trial_2_testes(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_modelo_FK_trial_2_testes(SimStruct *S)
{
  SFc1_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc1_modelo_FK_trial_2_testesInstanceStruct *)utMalloc(sizeof
    (SFc1_modelo_FK_trial_2_testesInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_modelo_FK_trial_2_testesInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c1_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c1_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_modelo_FK_trial_2_testes;
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

void c1_modelo_FK_trial_2_testes_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_modelo_FK_trial_2_testes(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_modelo_FK_trial_2_testes(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_modelo_FK_trial_2_testes(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_modelo_FK_trial_2_testes_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
