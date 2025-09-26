/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_FK_trial_2_testes_sfun.h"
#include "c13_modelo_FK_trial_2_testes.h"
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
static const char * c13_debug_family_names[8] = { "S_inv", "nargin", "nargout",
  "wr", "vsh", "voh", "vnh", "w_recuperado" };

/* Function Declarations */
static void initialize_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void initialize_params_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void enable_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void disable_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void c13_update_debugger_state_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void set_sim_state_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c13_st);
static void finalize_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void sf_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void c13_chartstep_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void initSimStructsc13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void registerMessagesc13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber);
static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_emlrt_marshallIn(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c13_w_recuperado, const char_T *c13_identifier,
  real_T c13_y[3]);
static void c13_b_emlrt_marshallIn(SFc13_modelo_FK_trial_2_testesInstanceStruct *
  chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[3]);
static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static real_T c13_c_emlrt_marshallIn
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_d_emlrt_marshallIn(SFc13_modelo_FK_trial_2_testesInstanceStruct *
  chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[9]);
static void c13_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static void c13_info_helper(c13_ResolvedFunctionInfo c13_info[37]);
static void c13_inv3x3(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, real_T c13_x[9], real_T c13_y[9]);
static real_T c13_norm(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, real_T c13_x[9]);
static void c13_eml_warning(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance);
static void c13_b_eml_warning(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, char_T c13_varargin_2[14]);
static void c13_eml_scalar_eg(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance);
static void c13_e_emlrt_marshallIn(SFc13_modelo_FK_trial_2_testesInstanceStruct *
  chartInstance, const mxArray *c13_sprintf, const char_T *c13_identifier,
  char_T c13_y[14]);
static void c13_f_emlrt_marshallIn(SFc13_modelo_FK_trial_2_testesInstanceStruct *
  chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  char_T c13_y[14]);
static const mxArray *c13_d_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static int32_T c13_g_emlrt_marshallIn
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static uint8_T c13_h_emlrt_marshallIn
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c13_b_is_active_c13_modelo_FK_trial_2_testes, const char_T *c13_identifier);
static uint8_T c13_i_emlrt_marshallIn
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void init_dsm_address_info(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  chartInstance->c13_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c13_is_active_c13_modelo_FK_trial_2_testes = 0U;
}

static void initialize_params_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
}

static void enable_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c13_update_debugger_state_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  const mxArray *c13_st;
  const mxArray *c13_y = NULL;
  int32_T c13_i0;
  real_T c13_u[3];
  const mxArray *c13_b_y = NULL;
  uint8_T c13_hoistedGlobal;
  uint8_T c13_b_u;
  const mxArray *c13_c_y = NULL;
  real_T (*c13_w_recuperado)[3];
  c13_w_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_st = NULL;
  c13_st = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_createcellarray(2), FALSE);
  for (c13_i0 = 0; c13_i0 < 3; c13_i0++) {
    c13_u[c13_i0] = (*c13_w_recuperado)[c13_i0];
  }

  c13_b_y = NULL;
  sf_mex_assign(&c13_b_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c13_y, 0, c13_b_y);
  c13_hoistedGlobal = chartInstance->c13_is_active_c13_modelo_FK_trial_2_testes;
  c13_b_u = c13_hoistedGlobal;
  c13_c_y = NULL;
  sf_mex_assign(&c13_c_y, sf_mex_create("y", &c13_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c13_y, 1, c13_c_y);
  sf_mex_assign(&c13_st, c13_y, FALSE);
  return c13_st;
}

static void set_sim_state_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c13_st)
{
  const mxArray *c13_u;
  real_T c13_dv0[3];
  int32_T c13_i1;
  real_T (*c13_w_recuperado)[3];
  c13_w_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c13_doneDoubleBufferReInit = TRUE;
  c13_u = sf_mex_dup(c13_st);
  c13_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 0)),
                       "w_recuperado", c13_dv0);
  for (c13_i1 = 0; c13_i1 < 3; c13_i1++) {
    (*c13_w_recuperado)[c13_i1] = c13_dv0[c13_i1];
  }

  chartInstance->c13_is_active_c13_modelo_FK_trial_2_testes =
    c13_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 1)),
    "is_active_c13_modelo_FK_trial_2_testes");
  sf_mex_destroy(&c13_u);
  c13_update_debugger_state_c13_modelo_FK_trial_2_testes(chartInstance);
  sf_mex_destroy(&c13_st);
}

static void finalize_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
}

static void sf_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  int32_T c13_i2;
  int32_T c13_i3;
  int32_T c13_i4;
  int32_T c13_i5;
  int32_T c13_i6;
  real_T (*c13_vnh)[3];
  real_T (*c13_voh)[3];
  real_T (*c13_vsh)[3];
  real_T (*c13_w_recuperado)[3];
  real_T (*c13_wr)[3];
  c13_vnh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c13_voh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c13_vsh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c13_w_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_wr = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 11U, chartInstance->c13_sfEvent);
  for (c13_i2 = 0; c13_i2 < 3; c13_i2++) {
    _SFD_DATA_RANGE_CHECK((*c13_wr)[c13_i2], 0U);
  }

  for (c13_i3 = 0; c13_i3 < 3; c13_i3++) {
    _SFD_DATA_RANGE_CHECK((*c13_w_recuperado)[c13_i3], 1U);
  }

  for (c13_i4 = 0; c13_i4 < 3; c13_i4++) {
    _SFD_DATA_RANGE_CHECK((*c13_vsh)[c13_i4], 2U);
  }

  for (c13_i5 = 0; c13_i5 < 3; c13_i5++) {
    _SFD_DATA_RANGE_CHECK((*c13_voh)[c13_i5], 3U);
  }

  for (c13_i6 = 0; c13_i6 < 3; c13_i6++) {
    _SFD_DATA_RANGE_CHECK((*c13_vnh)[c13_i6], 4U);
  }

  chartInstance->c13_sfEvent = CALL_EVENT;
  c13_chartstep_c13_modelo_FK_trial_2_testes(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_modelo_FK_trial_2_testesMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c13_chartstep_c13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
  int32_T c13_i7;
  real_T c13_wr[3];
  int32_T c13_i8;
  real_T c13_vsh[3];
  int32_T c13_i9;
  real_T c13_voh[3];
  int32_T c13_i10;
  real_T c13_vnh[3];
  uint32_T c13_debug_family_var_map[8];
  real_T c13_S_inv[9];
  real_T c13_nargin = 4.0;
  real_T c13_nargout = 1.0;
  real_T c13_w_recuperado[3];
  int32_T c13_i11;
  real_T c13_v[3];
  int32_T c13_i12;
  real_T c13_d[9];
  int32_T c13_j;
  int32_T c13_b_j;
  int32_T c13_a;
  int32_T c13_c;
  int32_T c13_i13;
  real_T c13_b_d[9];
  real_T c13_dv1[9];
  int32_T c13_i14;
  int32_T c13_i15;
  real_T c13_xinv[9];
  int32_T c13_i16;
  real_T c13_c_d[9];
  real_T c13_n1x;
  int32_T c13_i17;
  real_T c13_b_xinv[9];
  real_T c13_n1xinv;
  real_T c13_b_a;
  real_T c13_b;
  real_T c13_y;
  real_T c13_rc;
  real_T c13_x;
  boolean_T c13_b_b;
  real_T c13_b_x;
  int32_T c13_i18;
  static char_T c13_cv0[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  char_T c13_u[8];
  const mxArray *c13_b_y = NULL;
  real_T c13_b_u;
  const mxArray *c13_c_y = NULL;
  real_T c13_c_u;
  const mxArray *c13_d_y = NULL;
  real_T c13_d_u;
  const mxArray *c13_e_y = NULL;
  char_T c13_str[14];
  int32_T c13_i19;
  char_T c13_b_str[14];
  int32_T c13_i20;
  int32_T c13_i21;
  int32_T c13_i22;
  int32_T c13_i23;
  int32_T c13_i24;
  real_T c13_C[3];
  int32_T c13_i25;
  int32_T c13_i26;
  int32_T c13_i27;
  int32_T c13_i28;
  int32_T c13_i29;
  int32_T c13_i30;
  int32_T c13_i31;
  real_T (*c13_b_w_recuperado)[3];
  real_T (*c13_b_vnh)[3];
  real_T (*c13_b_voh)[3];
  real_T (*c13_b_vsh)[3];
  real_T (*c13_b_wr)[3];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  c13_b_vnh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c13_b_voh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c13_b_vsh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c13_b_w_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_b_wr = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 11U, chartInstance->c13_sfEvent);
  for (c13_i7 = 0; c13_i7 < 3; c13_i7++) {
    c13_wr[c13_i7] = (*c13_b_wr)[c13_i7];
  }

  for (c13_i8 = 0; c13_i8 < 3; c13_i8++) {
    c13_vsh[c13_i8] = (*c13_b_vsh)[c13_i8];
  }

  for (c13_i9 = 0; c13_i9 < 3; c13_i9++) {
    c13_voh[c13_i9] = (*c13_b_voh)[c13_i9];
  }

  for (c13_i10 = 0; c13_i10 < 3; c13_i10++) {
    c13_vnh[c13_i10] = (*c13_b_vnh)[c13_i10];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c13_debug_family_names,
    c13_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_S_inv, 0U, c13_c_sf_marshallOut,
    c13_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargin, 1U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargout, 2U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_wr, 3U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_vsh, 4U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_voh, 5U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_vnh, 6U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_w_recuperado, 7U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 4);
  for (c13_i11 = 0; c13_i11 < 3; c13_i11++) {
    c13_v[c13_i11] = c13_vsh[c13_i11];
  }

  for (c13_i12 = 0; c13_i12 < 9; c13_i12++) {
    c13_d[c13_i12] = 0.0;
  }

  for (c13_j = 1; c13_j < 4; c13_j++) {
    c13_b_j = c13_j;
    c13_a = c13_b_j;
    c13_c = c13_a;
    c13_d[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c13_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c13_c), 1, 3, 2, 0) - 1)) -
      1] = c13_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c13_b_j), 1, 3, 1, 0) - 1];
  }

  for (c13_i13 = 0; c13_i13 < 9; c13_i13++) {
    c13_b_d[c13_i13] = c13_d[c13_i13];
  }

  c13_inv3x3(chartInstance, c13_b_d, c13_dv1);
  for (c13_i14 = 0; c13_i14 < 9; c13_i14++) {
    c13_S_inv[c13_i14] = c13_dv1[c13_i14];
  }

  for (c13_i15 = 0; c13_i15 < 9; c13_i15++) {
    c13_xinv[c13_i15] = c13_S_inv[c13_i15];
  }

  for (c13_i16 = 0; c13_i16 < 9; c13_i16++) {
    c13_c_d[c13_i16] = c13_d[c13_i16];
  }

  c13_n1x = c13_norm(chartInstance, c13_c_d);
  for (c13_i17 = 0; c13_i17 < 9; c13_i17++) {
    c13_b_xinv[c13_i17] = c13_xinv[c13_i17];
  }

  c13_n1xinv = c13_norm(chartInstance, c13_b_xinv);
  c13_b_a = c13_n1x;
  c13_b = c13_n1xinv;
  c13_y = c13_b_a * c13_b;
  c13_rc = 1.0 / c13_y;
  guard1 = FALSE;
  guard2 = FALSE;
  if (c13_n1x == 0.0) {
    guard2 = TRUE;
  } else if (c13_n1xinv == 0.0) {
    guard2 = TRUE;
  } else if (c13_rc == 0.0) {
    guard1 = TRUE;
  } else {
    c13_x = c13_rc;
    c13_b_b = muDoubleScalarIsNaN(c13_x);
    guard3 = FALSE;
    if (c13_b_b) {
      guard3 = TRUE;
    } else {
      if (c13_rc < 2.2204460492503131E-16) {
        guard3 = TRUE;
      }
    }

    if (guard3 == TRUE) {
      c13_b_x = c13_rc;
      for (c13_i18 = 0; c13_i18 < 8; c13_i18++) {
        c13_u[c13_i18] = c13_cv0[c13_i18];
      }

      c13_b_y = NULL;
      sf_mex_assign(&c13_b_y, sf_mex_create("y", c13_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    FALSE);
      c13_b_u = 14.0;
      c13_c_y = NULL;
      sf_mex_assign(&c13_c_y, sf_mex_create("y", &c13_b_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c13_c_u = 6.0;
      c13_d_y = NULL;
      sf_mex_assign(&c13_d_y, sf_mex_create("y", &c13_c_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c13_d_u = c13_b_x;
      c13_e_y = NULL;
      sf_mex_assign(&c13_e_y, sf_mex_create("y", &c13_d_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c13_e_emlrt_marshallIn(chartInstance, sf_mex_call_debug("sprintf", 1U, 2U,
        14, sf_mex_call_debug("sprintf", 1U, 3U, 14, c13_b_y, 14, c13_c_y, 14,
        c13_d_y), 14, c13_e_y), "sprintf", c13_str);
      for (c13_i19 = 0; c13_i19 < 14; c13_i19++) {
        c13_b_str[c13_i19] = c13_str[c13_i19];
      }

      c13_b_eml_warning(chartInstance, c13_b_str);
    }
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c13_eml_warning(chartInstance);
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 6);
  for (c13_i20 = 0; c13_i20 < 9; c13_i20++) {
    c13_d[c13_i20] = c13_S_inv[c13_i20];
  }

  for (c13_i21 = 0; c13_i21 < 3; c13_i21++) {
    c13_v[c13_i21] = c13_wr[c13_i21] - c13_voh[c13_i21];
  }

  c13_eml_scalar_eg(chartInstance);
  c13_eml_scalar_eg(chartInstance);
  for (c13_i22 = 0; c13_i22 < 3; c13_i22++) {
    c13_w_recuperado[c13_i22] = 0.0;
  }

  for (c13_i23 = 0; c13_i23 < 3; c13_i23++) {
    c13_w_recuperado[c13_i23] = 0.0;
  }

  for (c13_i24 = 0; c13_i24 < 3; c13_i24++) {
    c13_C[c13_i24] = c13_w_recuperado[c13_i24];
  }

  for (c13_i25 = 0; c13_i25 < 3; c13_i25++) {
    c13_w_recuperado[c13_i25] = c13_C[c13_i25];
  }

  for (c13_i26 = 0; c13_i26 < 3; c13_i26++) {
    c13_C[c13_i26] = c13_w_recuperado[c13_i26];
  }

  for (c13_i27 = 0; c13_i27 < 3; c13_i27++) {
    c13_w_recuperado[c13_i27] = c13_C[c13_i27];
  }

  for (c13_i28 = 0; c13_i28 < 3; c13_i28++) {
    c13_w_recuperado[c13_i28] = 0.0;
    c13_i29 = 0;
    for (c13_i30 = 0; c13_i30 < 3; c13_i30++) {
      c13_w_recuperado[c13_i28] += c13_d[c13_i29 + c13_i28] * c13_v[c13_i30];
      c13_i29 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, -6);
  _SFD_SYMBOL_SCOPE_POP();
  for (c13_i31 = 0; c13_i31 < 3; c13_i31++) {
    (*c13_b_w_recuperado)[c13_i31] = c13_w_recuperado[c13_i31];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c13_sfEvent);
}

static void initSimStructsc13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
}

static void registerMessagesc13_modelo_FK_trial_2_testes
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber)
{
}

static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i32;
  real_T c13_b_inData[3];
  int32_T c13_i33;
  real_T c13_u[3];
  const mxArray *c13_y = NULL;
  SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc13_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  for (c13_i32 = 0; c13_i32 < 3; c13_i32++) {
    c13_b_inData[c13_i32] = (*(real_T (*)[3])c13_inData)[c13_i32];
  }

  for (c13_i33 = 0; c13_i33 < 3; c13_i33++) {
    c13_u[c13_i33] = c13_b_inData[c13_i33];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_emlrt_marshallIn(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, const mxArray *c13_w_recuperado, const char_T *c13_identifier,
  real_T c13_y[3])
{
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_w_recuperado),
    &c13_thisId, c13_y);
  sf_mex_destroy(&c13_w_recuperado);
}

static void c13_b_emlrt_marshallIn(SFc13_modelo_FK_trial_2_testesInstanceStruct *
  chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[3])
{
  real_T c13_dv2[3];
  int32_T c13_i34;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c13_i34 = 0; c13_i34 < 3; c13_i34++) {
    c13_y[c13_i34] = c13_dv2[c13_i34];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_w_recuperado;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y[3];
  int32_T c13_i35;
  SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc13_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c13_w_recuperado = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_w_recuperado),
    &c13_thisId, c13_y);
  sf_mex_destroy(&c13_w_recuperado);
  for (c13_i35 = 0; c13_i35 < 3; c13_i35++) {
    (*(real_T (*)[3])c13_outData)[c13_i35] = c13_y[c13_i35];
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  real_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc13_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(real_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static real_T c13_c_emlrt_marshallIn
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  real_T c13_y;
  real_T c13_d0;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_d0, 1, 0, 0U, 0, 0U, 0);
  c13_y = c13_d0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_nargout;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y;
  SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc13_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c13_nargout = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_nargout),
    &c13_thisId);
  sf_mex_destroy(&c13_nargout);
  *(real_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i36;
  int32_T c13_i37;
  int32_T c13_i38;
  real_T c13_b_inData[9];
  int32_T c13_i39;
  int32_T c13_i40;
  int32_T c13_i41;
  real_T c13_u[9];
  const mxArray *c13_y = NULL;
  SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc13_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_i36 = 0;
  for (c13_i37 = 0; c13_i37 < 3; c13_i37++) {
    for (c13_i38 = 0; c13_i38 < 3; c13_i38++) {
      c13_b_inData[c13_i38 + c13_i36] = (*(real_T (*)[9])c13_inData)[c13_i38 +
        c13_i36];
    }

    c13_i36 += 3;
  }

  c13_i39 = 0;
  for (c13_i40 = 0; c13_i40 < 3; c13_i40++) {
    for (c13_i41 = 0; c13_i41 < 3; c13_i41++) {
      c13_u[c13_i41 + c13_i39] = c13_b_inData[c13_i41 + c13_i39];
    }

    c13_i39 += 3;
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_d_emlrt_marshallIn(SFc13_modelo_FK_trial_2_testesInstanceStruct *
  chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[9])
{
  real_T c13_dv3[9];
  int32_T c13_i42;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv3, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c13_i42 = 0; c13_i42 < 9; c13_i42++) {
    c13_y[c13_i42] = c13_dv3[c13_i42];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_S_inv;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y[9];
  int32_T c13_i43;
  int32_T c13_i44;
  int32_T c13_i45;
  SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc13_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c13_S_inv = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_S_inv), &c13_thisId,
    c13_y);
  sf_mex_destroy(&c13_S_inv);
  c13_i43 = 0;
  for (c13_i44 = 0; c13_i44 < 3; c13_i44++) {
    for (c13_i45 = 0; c13_i45 < 3; c13_i45++) {
      (*(real_T (*)[9])c13_outData)[c13_i45 + c13_i43] = c13_y[c13_i45 + c13_i43];
    }

    c13_i43 += 3;
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

const mxArray *sf_c13_modelo_FK_trial_2_testes_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c13_nameCaptureInfo;
  c13_ResolvedFunctionInfo c13_info[37];
  const mxArray *c13_m0 = NULL;
  int32_T c13_i46;
  c13_ResolvedFunctionInfo *c13_r0;
  c13_nameCaptureInfo = NULL;
  c13_nameCaptureInfo = NULL;
  c13_info_helper(c13_info);
  sf_mex_assign(&c13_m0, sf_mex_createstruct("nameCaptureInfo", 1, 37), FALSE);
  for (c13_i46 = 0; c13_i46 < 37; c13_i46++) {
    c13_r0 = &c13_info[c13_i46];
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c13_r0->context)), "context", "nameCaptureInfo",
                    c13_i46);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c13_r0->name)), "name", "nameCaptureInfo",
                    c13_i46);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      c13_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c13_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c13_i46);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c13_r0->resolved)), "resolved",
                    "nameCaptureInfo", c13_i46);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", &c13_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c13_i46);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", &c13_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c13_i46);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      &c13_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c13_i46);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      &c13_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c13_i46);
  }

  sf_mex_assign(&c13_nameCaptureInfo, c13_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c13_nameCaptureInfo);
  return c13_nameCaptureInfo;
}

static void c13_info_helper(c13_ResolvedFunctionInfo c13_info[37])
{
  c13_info[0].context = "";
  c13_info[0].name = "diag";
  c13_info[0].dominantType = "double";
  c13_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c13_info[0].fileTimeLo = 1286836686U;
  c13_info[0].fileTimeHi = 0U;
  c13_info[0].mFileTimeLo = 0U;
  c13_info[0].mFileTimeHi = 0U;
  c13_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c13_info[1].name = "eml_index_class";
  c13_info[1].dominantType = "";
  c13_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[1].fileTimeLo = 1323181378U;
  c13_info[1].fileTimeHi = 0U;
  c13_info[1].mFileTimeLo = 0U;
  c13_info[1].mFileTimeHi = 0U;
  c13_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c13_info[2].name = "eml_index_plus";
  c13_info[2].dominantType = "coder.internal.indexInt";
  c13_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c13_info[2].fileTimeLo = 1286836778U;
  c13_info[2].fileTimeHi = 0U;
  c13_info[2].mFileTimeLo = 0U;
  c13_info[2].mFileTimeHi = 0U;
  c13_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c13_info[3].name = "eml_index_class";
  c13_info[3].dominantType = "";
  c13_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[3].fileTimeLo = 1323181378U;
  c13_info[3].fileTimeHi = 0U;
  c13_info[3].mFileTimeLo = 0U;
  c13_info[3].mFileTimeHi = 0U;
  c13_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c13_info[4].name = "eml_scalar_eg";
  c13_info[4].dominantType = "double";
  c13_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c13_info[4].fileTimeLo = 1286836796U;
  c13_info[4].fileTimeHi = 0U;
  c13_info[4].mFileTimeLo = 0U;
  c13_info[4].mFileTimeHi = 0U;
  c13_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c13_info[5].name = "eml_int_forloop_overflow_check";
  c13_info[5].dominantType = "";
  c13_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c13_info[5].fileTimeLo = 1346528340U;
  c13_info[5].fileTimeHi = 0U;
  c13_info[5].mFileTimeLo = 0U;
  c13_info[5].mFileTimeHi = 0U;
  c13_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c13_info[6].name = "intmax";
  c13_info[6].dominantType = "char";
  c13_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c13_info[6].fileTimeLo = 1311273316U;
  c13_info[6].fileTimeHi = 0U;
  c13_info[6].mFileTimeLo = 0U;
  c13_info[6].mFileTimeHi = 0U;
  c13_info[7].context = "";
  c13_info[7].name = "inv";
  c13_info[7].dominantType = "double";
  c13_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c13_info[7].fileTimeLo = 1305336000U;
  c13_info[7].fileTimeHi = 0U;
  c13_info[7].mFileTimeLo = 0U;
  c13_info[7].mFileTimeHi = 0U;
  c13_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c13_info[8].name = "eml_index_class";
  c13_info[8].dominantType = "";
  c13_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[8].fileTimeLo = 1323181378U;
  c13_info[8].fileTimeHi = 0U;
  c13_info[8].mFileTimeLo = 0U;
  c13_info[8].mFileTimeHi = 0U;
  c13_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c13_info[9].name = "abs";
  c13_info[9].dominantType = "double";
  c13_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c13_info[9].fileTimeLo = 1343848366U;
  c13_info[9].fileTimeHi = 0U;
  c13_info[9].mFileTimeLo = 0U;
  c13_info[9].mFileTimeHi = 0U;
  c13_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c13_info[10].name = "eml_scalar_abs";
  c13_info[10].dominantType = "double";
  c13_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c13_info[10].fileTimeLo = 1286836712U;
  c13_info[10].fileTimeHi = 0U;
  c13_info[10].mFileTimeLo = 0U;
  c13_info[10].mFileTimeHi = 0U;
  c13_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c13_info[11].name = "eml_div";
  c13_info[11].dominantType = "double";
  c13_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c13_info[11].fileTimeLo = 1313365810U;
  c13_info[11].fileTimeHi = 0U;
  c13_info[11].mFileTimeLo = 0U;
  c13_info[11].mFileTimeHi = 0U;
  c13_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c13_info[12].name = "mtimes";
  c13_info[12].dominantType = "double";
  c13_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[12].fileTimeLo = 1289530492U;
  c13_info[12].fileTimeHi = 0U;
  c13_info[12].mFileTimeLo = 0U;
  c13_info[12].mFileTimeHi = 0U;
  c13_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c13_info[13].name = "eml_index_plus";
  c13_info[13].dominantType = "double";
  c13_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c13_info[13].fileTimeLo = 1286836778U;
  c13_info[13].fileTimeHi = 0U;
  c13_info[13].mFileTimeLo = 0U;
  c13_info[13].mFileTimeHi = 0U;
  c13_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c13_info[14].name = "norm";
  c13_info[14].dominantType = "double";
  c13_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c13_info[14].fileTimeLo = 1336540094U;
  c13_info[14].fileTimeHi = 0U;
  c13_info[14].mFileTimeLo = 0U;
  c13_info[14].mFileTimeHi = 0U;
  c13_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c13_info[15].name = "abs";
  c13_info[15].dominantType = "double";
  c13_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c13_info[15].fileTimeLo = 1343848366U;
  c13_info[15].fileTimeHi = 0U;
  c13_info[15].mFileTimeLo = 0U;
  c13_info[15].mFileTimeHi = 0U;
  c13_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c13_info[16].name = "isnan";
  c13_info[16].dominantType = "double";
  c13_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c13_info[16].fileTimeLo = 1286836760U;
  c13_info[16].fileTimeHi = 0U;
  c13_info[16].mFileTimeLo = 0U;
  c13_info[16].mFileTimeHi = 0U;
  c13_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c13_info[17].name = "eml_guarded_nan";
  c13_info[17].dominantType = "char";
  c13_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c13_info[17].fileTimeLo = 1286836776U;
  c13_info[17].fileTimeHi = 0U;
  c13_info[17].mFileTimeLo = 0U;
  c13_info[17].mFileTimeHi = 0U;
  c13_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c13_info[18].name = "eml_is_float_class";
  c13_info[18].dominantType = "char";
  c13_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c13_info[18].fileTimeLo = 1286836782U;
  c13_info[18].fileTimeHi = 0U;
  c13_info[18].mFileTimeLo = 0U;
  c13_info[18].mFileTimeHi = 0U;
  c13_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c13_info[19].name = "mtimes";
  c13_info[19].dominantType = "double";
  c13_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[19].fileTimeLo = 1289530492U;
  c13_info[19].fileTimeHi = 0U;
  c13_info[19].mFileTimeLo = 0U;
  c13_info[19].mFileTimeHi = 0U;
  c13_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c13_info[20].name = "eml_warning";
  c13_info[20].dominantType = "char";
  c13_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c13_info[20].fileTimeLo = 1286836802U;
  c13_info[20].fileTimeHi = 0U;
  c13_info[20].mFileTimeLo = 0U;
  c13_info[20].mFileTimeHi = 0U;
  c13_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c13_info[21].name = "isnan";
  c13_info[21].dominantType = "double";
  c13_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c13_info[21].fileTimeLo = 1286836760U;
  c13_info[21].fileTimeHi = 0U;
  c13_info[21].mFileTimeLo = 0U;
  c13_info[21].mFileTimeHi = 0U;
  c13_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c13_info[22].name = "eps";
  c13_info[22].dominantType = "char";
  c13_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c13_info[22].fileTimeLo = 1326738796U;
  c13_info[22].fileTimeHi = 0U;
  c13_info[22].mFileTimeLo = 0U;
  c13_info[22].mFileTimeHi = 0U;
  c13_info[23].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c13_info[23].name = "eml_is_float_class";
  c13_info[23].dominantType = "char";
  c13_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c13_info[23].fileTimeLo = 1286836782U;
  c13_info[23].fileTimeHi = 0U;
  c13_info[23].mFileTimeLo = 0U;
  c13_info[23].mFileTimeHi = 0U;
  c13_info[24].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c13_info[24].name = "eml_eps";
  c13_info[24].dominantType = "char";
  c13_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c13_info[24].fileTimeLo = 1326738796U;
  c13_info[24].fileTimeHi = 0U;
  c13_info[24].mFileTimeLo = 0U;
  c13_info[24].mFileTimeHi = 0U;
  c13_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c13_info[25].name = "eml_float_model";
  c13_info[25].dominantType = "char";
  c13_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c13_info[25].fileTimeLo = 1326738796U;
  c13_info[25].fileTimeHi = 0U;
  c13_info[25].mFileTimeLo = 0U;
  c13_info[25].mFileTimeHi = 0U;
  c13_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c13_info[26].name = "eml_flt2str";
  c13_info[26].dominantType = "double";
  c13_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c13_info[26].fileTimeLo = 1309469196U;
  c13_info[26].fileTimeHi = 0U;
  c13_info[26].mFileTimeLo = 0U;
  c13_info[26].mFileTimeHi = 0U;
  c13_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c13_info[27].name = "char";
  c13_info[27].dominantType = "double";
  c13_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m";
  c13_info[27].fileTimeLo = 1319744368U;
  c13_info[27].fileTimeHi = 0U;
  c13_info[27].mFileTimeLo = 0U;
  c13_info[27].mFileTimeHi = 0U;
  c13_info[28].context = "";
  c13_info[28].name = "mtimes";
  c13_info[28].dominantType = "double";
  c13_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[28].fileTimeLo = 1289530492U;
  c13_info[28].fileTimeHi = 0U;
  c13_info[28].mFileTimeLo = 0U;
  c13_info[28].mFileTimeHi = 0U;
  c13_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[29].name = "eml_index_class";
  c13_info[29].dominantType = "";
  c13_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[29].fileTimeLo = 1323181378U;
  c13_info[29].fileTimeHi = 0U;
  c13_info[29].mFileTimeLo = 0U;
  c13_info[29].mFileTimeHi = 0U;
  c13_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[30].name = "eml_scalar_eg";
  c13_info[30].dominantType = "double";
  c13_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c13_info[30].fileTimeLo = 1286836796U;
  c13_info[30].fileTimeHi = 0U;
  c13_info[30].mFileTimeLo = 0U;
  c13_info[30].mFileTimeHi = 0U;
  c13_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[31].name = "eml_xgemm";
  c13_info[31].dominantType = "char";
  c13_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c13_info[31].fileTimeLo = 1299091172U;
  c13_info[31].fileTimeHi = 0U;
  c13_info[31].mFileTimeLo = 0U;
  c13_info[31].mFileTimeHi = 0U;
  c13_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c13_info[32].name = "eml_blas_inline";
  c13_info[32].dominantType = "";
  c13_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c13_info[32].fileTimeLo = 1299091168U;
  c13_info[32].fileTimeHi = 0U;
  c13_info[32].mFileTimeLo = 0U;
  c13_info[32].mFileTimeHi = 0U;
  c13_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c13_info[33].name = "mtimes";
  c13_info[33].dominantType = "double";
  c13_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[33].fileTimeLo = 1289530492U;
  c13_info[33].fileTimeHi = 0U;
  c13_info[33].mFileTimeLo = 0U;
  c13_info[33].mFileTimeHi = 0U;
  c13_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c13_info[34].name = "eml_index_class";
  c13_info[34].dominantType = "";
  c13_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[34].fileTimeLo = 1323181378U;
  c13_info[34].fileTimeHi = 0U;
  c13_info[34].mFileTimeLo = 0U;
  c13_info[34].mFileTimeHi = 0U;
  c13_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c13_info[35].name = "eml_scalar_eg";
  c13_info[35].dominantType = "double";
  c13_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c13_info[35].fileTimeLo = 1286836796U;
  c13_info[35].fileTimeHi = 0U;
  c13_info[35].mFileTimeLo = 0U;
  c13_info[35].mFileTimeHi = 0U;
  c13_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c13_info[36].name = "eml_refblas_xgemm";
  c13_info[36].dominantType = "char";
  c13_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c13_info[36].fileTimeLo = 1299091174U;
  c13_info[36].fileTimeHi = 0U;
  c13_info[36].mFileTimeLo = 0U;
  c13_info[36].mFileTimeHi = 0U;
}

static void c13_inv3x3(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, real_T c13_x[9], real_T c13_y[9])
{
  int32_T c13_p1;
  int32_T c13_p2;
  int32_T c13_p3;
  real_T c13_b_x;
  real_T c13_c_x;
  real_T c13_absx11;
  real_T c13_d_x;
  real_T c13_e_x;
  real_T c13_absx21;
  real_T c13_f_x;
  real_T c13_g_x;
  real_T c13_absx31;
  real_T c13_t1;
  real_T c13_h_x;
  real_T c13_b_y;
  real_T c13_z;
  real_T c13_i_x;
  real_T c13_c_y;
  real_T c13_b_z;
  real_T c13_a;
  real_T c13_b;
  real_T c13_d_y;
  real_T c13_b_a;
  real_T c13_b_b;
  real_T c13_e_y;
  real_T c13_c_a;
  real_T c13_c_b;
  real_T c13_f_y;
  real_T c13_d_a;
  real_T c13_d_b;
  real_T c13_g_y;
  real_T c13_j_x;
  real_T c13_k_x;
  real_T c13_h_y;
  real_T c13_l_x;
  real_T c13_m_x;
  real_T c13_i_y;
  int32_T c13_itmp;
  real_T c13_n_x;
  real_T c13_j_y;
  real_T c13_c_z;
  real_T c13_e_a;
  real_T c13_e_b;
  real_T c13_k_y;
  real_T c13_f_a;
  real_T c13_f_b;
  real_T c13_l_y;
  real_T c13_o_x;
  real_T c13_m_y;
  real_T c13_t3;
  real_T c13_g_a;
  real_T c13_g_b;
  real_T c13_n_y;
  real_T c13_p_x;
  real_T c13_o_y;
  real_T c13_t2;
  int32_T c13_h_a;
  int32_T c13_c;
  real_T c13_i_a;
  real_T c13_h_b;
  real_T c13_p_y;
  real_T c13_j_a;
  real_T c13_i_b;
  real_T c13_q_y;
  real_T c13_q_x;
  real_T c13_r_y;
  real_T c13_d_z;
  int32_T c13_k_a;
  int32_T c13_b_c;
  int32_T c13_l_a;
  int32_T c13_c_c;
  real_T c13_r_x;
  real_T c13_s_y;
  real_T c13_m_a;
  real_T c13_j_b;
  real_T c13_t_y;
  real_T c13_s_x;
  real_T c13_u_y;
  int32_T c13_n_a;
  int32_T c13_d_c;
  real_T c13_o_a;
  real_T c13_k_b;
  real_T c13_v_y;
  real_T c13_p_a;
  real_T c13_l_b;
  real_T c13_w_y;
  real_T c13_t_x;
  real_T c13_x_y;
  real_T c13_e_z;
  int32_T c13_q_a;
  int32_T c13_e_c;
  int32_T c13_r_a;
  int32_T c13_f_c;
  real_T c13_y_y;
  real_T c13_s_a;
  real_T c13_m_b;
  real_T c13_ab_y;
  real_T c13_u_x;
  real_T c13_bb_y;
  int32_T c13_t_a;
  int32_T c13_g_c;
  real_T c13_u_a;
  real_T c13_n_b;
  real_T c13_cb_y;
  real_T c13_v_a;
  real_T c13_o_b;
  real_T c13_db_y;
  real_T c13_v_x;
  real_T c13_eb_y;
  real_T c13_f_z;
  int32_T c13_w_a;
  int32_T c13_h_c;
  int32_T c13_x_a;
  int32_T c13_i_c;
  boolean_T guard1 = FALSE;
  c13_p1 = 0;
  c13_p2 = 3;
  c13_p3 = 6;
  c13_b_x = c13_x[0];
  c13_c_x = c13_b_x;
  c13_absx11 = muDoubleScalarAbs(c13_c_x);
  c13_d_x = c13_x[1];
  c13_e_x = c13_d_x;
  c13_absx21 = muDoubleScalarAbs(c13_e_x);
  c13_f_x = c13_x[2];
  c13_g_x = c13_f_x;
  c13_absx31 = muDoubleScalarAbs(c13_g_x);
  guard1 = FALSE;
  if (c13_absx21 > c13_absx11) {
    if (c13_absx21 > c13_absx31) {
      c13_p1 = 3;
      c13_p2 = 0;
      c13_t1 = c13_x[0];
      c13_x[0] = c13_x[1];
      c13_x[1] = c13_t1;
      c13_t1 = c13_x[3];
      c13_x[3] = c13_x[4];
      c13_x[4] = c13_t1;
      c13_t1 = c13_x[6];
      c13_x[6] = c13_x[7];
      c13_x[7] = c13_t1;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    if (c13_absx31 > c13_absx11) {
      c13_p1 = 6;
      c13_p3 = 0;
      c13_t1 = c13_x[0];
      c13_x[0] = c13_x[2];
      c13_x[2] = c13_t1;
      c13_t1 = c13_x[3];
      c13_x[3] = c13_x[5];
      c13_x[5] = c13_t1;
      c13_t1 = c13_x[6];
      c13_x[6] = c13_x[8];
      c13_x[8] = c13_t1;
    }
  }

  c13_h_x = c13_x[1];
  c13_b_y = c13_x[0];
  c13_z = c13_h_x / c13_b_y;
  c13_x[1] = c13_z;
  c13_i_x = c13_x[2];
  c13_c_y = c13_x[0];
  c13_b_z = c13_i_x / c13_c_y;
  c13_x[2] = c13_b_z;
  c13_a = c13_x[1];
  c13_b = c13_x[3];
  c13_d_y = c13_a * c13_b;
  c13_x[4] -= c13_d_y;
  c13_b_a = c13_x[2];
  c13_b_b = c13_x[3];
  c13_e_y = c13_b_a * c13_b_b;
  c13_x[5] -= c13_e_y;
  c13_c_a = c13_x[1];
  c13_c_b = c13_x[6];
  c13_f_y = c13_c_a * c13_c_b;
  c13_x[7] -= c13_f_y;
  c13_d_a = c13_x[2];
  c13_d_b = c13_x[6];
  c13_g_y = c13_d_a * c13_d_b;
  c13_x[8] -= c13_g_y;
  c13_j_x = c13_x[5];
  c13_k_x = c13_j_x;
  c13_h_y = muDoubleScalarAbs(c13_k_x);
  c13_l_x = c13_x[4];
  c13_m_x = c13_l_x;
  c13_i_y = muDoubleScalarAbs(c13_m_x);
  if (c13_h_y > c13_i_y) {
    c13_itmp = c13_p2;
    c13_p2 = c13_p3;
    c13_p3 = c13_itmp;
    c13_t1 = c13_x[1];
    c13_x[1] = c13_x[2];
    c13_x[2] = c13_t1;
    c13_t1 = c13_x[4];
    c13_x[4] = c13_x[5];
    c13_x[5] = c13_t1;
    c13_t1 = c13_x[7];
    c13_x[7] = c13_x[8];
    c13_x[8] = c13_t1;
  }

  c13_n_x = c13_x[5];
  c13_j_y = c13_x[4];
  c13_c_z = c13_n_x / c13_j_y;
  c13_x[5] = c13_c_z;
  c13_e_a = c13_x[5];
  c13_e_b = c13_x[7];
  c13_k_y = c13_e_a * c13_e_b;
  c13_x[8] -= c13_k_y;
  c13_f_a = c13_x[5];
  c13_f_b = c13_x[1];
  c13_l_y = c13_f_a * c13_f_b;
  c13_o_x = c13_l_y - c13_x[2];
  c13_m_y = c13_x[8];
  c13_t3 = c13_o_x / c13_m_y;
  c13_g_a = c13_x[7];
  c13_g_b = c13_t3;
  c13_n_y = c13_g_a * c13_g_b;
  c13_p_x = -(c13_x[1] + c13_n_y);
  c13_o_y = c13_x[4];
  c13_t2 = c13_p_x / c13_o_y;
  c13_h_a = c13_p1 + 1;
  c13_c = c13_h_a;
  c13_i_a = c13_x[3];
  c13_h_b = c13_t2;
  c13_p_y = c13_i_a * c13_h_b;
  c13_j_a = c13_x[6];
  c13_i_b = c13_t3;
  c13_q_y = c13_j_a * c13_i_b;
  c13_q_x = (1.0 - c13_p_y) - c13_q_y;
  c13_r_y = c13_x[0];
  c13_d_z = c13_q_x / c13_r_y;
  c13_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c13_c), 1, 9, 1, 0) - 1] = c13_d_z;
  c13_k_a = c13_p1 + 2;
  c13_b_c = c13_k_a;
  c13_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c13_b_c), 1, 9, 1, 0) - 1] = c13_t2;
  c13_l_a = c13_p1 + 3;
  c13_c_c = c13_l_a;
  c13_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c13_c_c), 1, 9, 1, 0) - 1] = c13_t3;
  c13_r_x = -c13_x[5];
  c13_s_y = c13_x[8];
  c13_t3 = c13_r_x / c13_s_y;
  c13_m_a = c13_x[7];
  c13_j_b = c13_t3;
  c13_t_y = c13_m_a * c13_j_b;
  c13_s_x = 1.0 - c13_t_y;
  c13_u_y = c13_x[4];
  c13_t2 = c13_s_x / c13_u_y;
  c13_n_a = c13_p2 + 1;
  c13_d_c = c13_n_a;
  c13_o_a = c13_x[3];
  c13_k_b = c13_t2;
  c13_v_y = c13_o_a * c13_k_b;
  c13_p_a = c13_x[6];
  c13_l_b = c13_t3;
  c13_w_y = c13_p_a * c13_l_b;
  c13_t_x = -(c13_v_y + c13_w_y);
  c13_x_y = c13_x[0];
  c13_e_z = c13_t_x / c13_x_y;
  c13_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c13_d_c), 1, 9, 1, 0) - 1] = c13_e_z;
  c13_q_a = c13_p2 + 2;
  c13_e_c = c13_q_a;
  c13_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c13_e_c), 1, 9, 1, 0) - 1] = c13_t2;
  c13_r_a = c13_p2 + 3;
  c13_f_c = c13_r_a;
  c13_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c13_f_c), 1, 9, 1, 0) - 1] = c13_t3;
  c13_y_y = c13_x[8];
  c13_t3 = 1.0 / c13_y_y;
  c13_s_a = -c13_x[7];
  c13_m_b = c13_t3;
  c13_ab_y = c13_s_a * c13_m_b;
  c13_u_x = c13_ab_y;
  c13_bb_y = c13_x[4];
  c13_t2 = c13_u_x / c13_bb_y;
  c13_t_a = c13_p3 + 1;
  c13_g_c = c13_t_a;
  c13_u_a = c13_x[3];
  c13_n_b = c13_t2;
  c13_cb_y = c13_u_a * c13_n_b;
  c13_v_a = c13_x[6];
  c13_o_b = c13_t3;
  c13_db_y = c13_v_a * c13_o_b;
  c13_v_x = -(c13_cb_y + c13_db_y);
  c13_eb_y = c13_x[0];
  c13_f_z = c13_v_x / c13_eb_y;
  c13_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c13_g_c), 1, 9, 1, 0) - 1] = c13_f_z;
  c13_w_a = c13_p3 + 2;
  c13_h_c = c13_w_a;
  c13_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c13_h_c), 1, 9, 1, 0) - 1] = c13_t2;
  c13_x_a = c13_p3 + 3;
  c13_i_c = c13_x_a;
  c13_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c13_i_c), 1, 9, 1, 0) - 1] = c13_t3;
}

static real_T c13_norm(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, real_T c13_x[9])
{
  real_T c13_y;
  int32_T c13_j;
  real_T c13_b_j;
  real_T c13_s;
  int32_T c13_i;
  real_T c13_b_i;
  real_T c13_b_x;
  real_T c13_c_x;
  real_T c13_b_y;
  real_T c13_d_x;
  boolean_T c13_b;
  boolean_T exitg1;
  c13_y = 0.0;
  c13_j = 0;
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (c13_j < 3)) {
    c13_b_j = 1.0 + (real_T)c13_j;
    c13_s = 0.0;
    for (c13_i = 0; c13_i < 3; c13_i++) {
      c13_b_i = 1.0 + (real_T)c13_i;
      c13_b_x = c13_x[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c13_b_i), 1, 3, 1, 0) + 3 * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c13_b_j),
        1, 3, 2, 0) - 1)) - 1];
      c13_c_x = c13_b_x;
      c13_b_y = muDoubleScalarAbs(c13_c_x);
      c13_s += c13_b_y;
    }

    c13_d_x = c13_s;
    c13_b = muDoubleScalarIsNaN(c13_d_x);
    if (c13_b) {
      c13_y = rtNaN;
      exitg1 = TRUE;
    } else {
      if (c13_s > c13_y) {
        c13_y = c13_s;
      }

      c13_j++;
    }
  }

  return c13_y;
}

static void c13_eml_warning(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance)
{
  int32_T c13_i47;
  static char_T c13_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c13_u[27];
  const mxArray *c13_y = NULL;
  for (c13_i47 = 0; c13_i47 < 27; c13_i47++) {
    c13_u[c13_i47] = c13_varargin_1[c13_i47];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 10, 0U, 1U, 0U, 2, 1, 27),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c13_y));
}

static void c13_b_eml_warning(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance, char_T c13_varargin_2[14])
{
  int32_T c13_i48;
  static char_T c13_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c13_u[33];
  const mxArray *c13_y = NULL;
  int32_T c13_i49;
  char_T c13_b_u[14];
  const mxArray *c13_b_y = NULL;
  for (c13_i48 = 0; c13_i48 < 33; c13_i48++) {
    c13_u[c13_i48] = c13_varargin_1[c13_i48];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 10, 0U, 1U, 0U, 2, 1, 33),
                FALSE);
  for (c13_i49 = 0; c13_i49 < 14; c13_i49++) {
    c13_b_u[c13_i49] = c13_varargin_2[c13_i49];
  }

  c13_b_y = NULL;
  sf_mex_assign(&c13_b_y, sf_mex_create("y", c13_b_u, 10, 0U, 1U, 0U, 2, 1, 14),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
    14, c13_y, 14, c13_b_y));
}

static void c13_eml_scalar_eg(SFc13_modelo_FK_trial_2_testesInstanceStruct
  *chartInstance)
{
}

static void c13_e_emlrt_marshallIn(SFc13_modelo_FK_trial_2_testesInstanceStruct *
  chartInstance, const mxArray *c13_sprintf, const char_T *c13_identifier,
  char_T c13_y[14])
{
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_sprintf), &c13_thisId,
    c13_y);
  sf_mex_destroy(&c13_sprintf);
}

static void c13_f_emlrt_marshallIn(SFc13_modelo_FK_trial_2_testesInstanceStruct *
  chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  char_T c13_y[14])
{
  char_T c13_cv1[14];
  int32_T c13_i50;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_cv1, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c13_i50 = 0; c13_i50 < 14; c13_i50++) {
    c13_y[c13_i50] = c13_cv1[c13_i50];
  }

  sf_mex_destroy(&c13_u);
}

static const mxArray *c13_d_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc13_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(int32_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static int32_T c13_g_emlrt_marshallIn
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  int32_T c13_y;
  int32_T c13_i51;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_i51, 1, 6, 0U, 0, 0U, 0);
  c13_y = c13_i51;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_b_sfEvent;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  int32_T c13_y;
  SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc13_modelo_FK_trial_2_testesInstanceStruct *)
    chartInstanceVoid;
  c13_b_sfEvent = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_b_sfEvent),
    &c13_thisId);
  sf_mex_destroy(&c13_b_sfEvent);
  *(int32_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static uint8_T c13_h_emlrt_marshallIn
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c13_b_is_active_c13_modelo_FK_trial_2_testes, const char_T *c13_identifier)
{
  uint8_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c13_b_is_active_c13_modelo_FK_trial_2_testes), &c13_thisId);
  sf_mex_destroy(&c13_b_is_active_c13_modelo_FK_trial_2_testes);
  return c13_y;
}

static uint8_T c13_i_emlrt_marshallIn
  (SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance, const mxArray
   *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  uint8_T c13_y;
  uint8_T c13_u0;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_u0, 1, 3, 0U, 0, 0U, 0);
  c13_y = c13_u0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void init_dsm_address_info(SFc13_modelo_FK_trial_2_testesInstanceStruct
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

void sf_c13_modelo_FK_trial_2_testes_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2508642265U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1177694228U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(642323671U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(511602719U);
}

mxArray *sf_c13_modelo_FK_trial_2_testes_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("FOdAJ1DfbaFyVzgi3rjGNB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
      pr[0] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c13_modelo_FK_trial_2_testes_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c13_modelo_FK_trial_2_testes(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"w_recuperado\",},{M[8],M[0],T\"is_active_c13_modelo_FK_trial_2_testes\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c13_modelo_FK_trial_2_testes_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
    chartInstance = (SFc13_modelo_FK_trial_2_testesInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modelo_FK_trial_2_testesMachineNumber_,
           13,
           1,
           1,
           5,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"wr");
          _SFD_SET_DATA_PROPS(1,2,0,1,"w_recuperado");
          _SFD_SET_DATA_PROPS(2,1,1,0,"vsh");
          _SFD_SET_DATA_PROPS(3,1,1,0,"voh");
          _SFD_SET_DATA_PROPS(4,1,1,0,"vnh");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,120);
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
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)
            c13_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c13_wr)[3];
          real_T (*c13_w_recuperado)[3];
          real_T (*c13_vsh)[3];
          real_T (*c13_voh)[3];
          real_T (*c13_vnh)[3];
          c13_vnh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c13_voh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c13_vsh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c13_w_recuperado = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c13_wr = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c13_wr);
          _SFD_SET_DATA_VALUE_PTR(1U, *c13_w_recuperado);
          _SFD_SET_DATA_VALUE_PTR(2U, *c13_vsh);
          _SFD_SET_DATA_VALUE_PTR(3U, *c13_voh);
          _SFD_SET_DATA_VALUE_PTR(4U, *c13_vnh);
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
  return "lS2G5inCjeIvzh5TZdLJSH";
}

static void sf_opaque_initialize_c13_modelo_FK_trial_2_testes(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc13_modelo_FK_trial_2_testesInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c13_modelo_FK_trial_2_testes
    ((SFc13_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
  initialize_c13_modelo_FK_trial_2_testes
    ((SFc13_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c13_modelo_FK_trial_2_testes(void *chartInstanceVar)
{
  enable_c13_modelo_FK_trial_2_testes
    ((SFc13_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c13_modelo_FK_trial_2_testes(void
  *chartInstanceVar)
{
  disable_c13_modelo_FK_trial_2_testes
    ((SFc13_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c13_modelo_FK_trial_2_testes(void
  *chartInstanceVar)
{
  sf_c13_modelo_FK_trial_2_testes((SFc13_modelo_FK_trial_2_testesInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c13_modelo_FK_trial_2_testes
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c13_modelo_FK_trial_2_testes
    ((SFc13_modelo_FK_trial_2_testesInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_modelo_FK_trial_2_testes();/* state var info */
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

extern void sf_internal_set_sim_state_c13_modelo_FK_trial_2_testes(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_modelo_FK_trial_2_testes();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c13_modelo_FK_trial_2_testes
    ((SFc13_modelo_FK_trial_2_testesInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c13_modelo_FK_trial_2_testes
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c13_modelo_FK_trial_2_testes(S);
}

static void sf_opaque_set_sim_state_c13_modelo_FK_trial_2_testes(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c13_modelo_FK_trial_2_testes(S, st);
}

static void sf_opaque_terminate_c13_modelo_FK_trial_2_testes(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc13_modelo_FK_trial_2_testesInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_FK_trial_2_testes_optimization_info();
    }

    finalize_c13_modelo_FK_trial_2_testes
      ((SFc13_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc13_modelo_FK_trial_2_testes
    ((SFc13_modelo_FK_trial_2_testesInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c13_modelo_FK_trial_2_testes(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c13_modelo_FK_trial_2_testes
      ((SFc13_modelo_FK_trial_2_testesInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c13_modelo_FK_trial_2_testes(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_modelo_FK_trial_2_testes_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      13);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,13,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,13,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,13);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,13,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,13,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,13);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(255842431U));
  ssSetChecksum1(S,(3868391597U));
  ssSetChecksum2(S,(464801761U));
  ssSetChecksum3(S,(2638590940U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c13_modelo_FK_trial_2_testes(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c13_modelo_FK_trial_2_testes(SimStruct *S)
{
  SFc13_modelo_FK_trial_2_testesInstanceStruct *chartInstance;
  chartInstance = (SFc13_modelo_FK_trial_2_testesInstanceStruct *)utMalloc
    (sizeof(SFc13_modelo_FK_trial_2_testesInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc13_modelo_FK_trial_2_testesInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c13_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c13_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c13_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c13_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c13_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c13_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c13_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c13_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c13_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.mdlStart = mdlStart_c13_modelo_FK_trial_2_testes;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c13_modelo_FK_trial_2_testes;
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

void c13_modelo_FK_trial_2_testes_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c13_modelo_FK_trial_2_testes(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c13_modelo_FK_trial_2_testes(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c13_modelo_FK_trial_2_testes(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c13_modelo_FK_trial_2_testes_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
