/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_FK_pratico_coleta_dados_v2_sfun.h"
#include "c12_modelo_FK_pratico_coleta_dados_v2.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "modelo_FK_pratico_coleta_dados_v2_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c12_debug_family_names[10] = { "s_12", "s_23", "s_31",
  "s_456", "S", "H", "nargin", "nargout", "w_gyros", "w_saida" };

/* Function Declarations */
static void initialize_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void initialize_params_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void enable_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void disable_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void c12_update_debugger_state_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void set_sim_state_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_st);
static void finalize_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void sf_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void c12_chartstep_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void initSimStructsc12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void registerMessagesc12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber);
static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_w_saida, const char_T *c12_identifier, real_T c12_y[3]);
static void c12_b_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, real_T c12_y[3]);
static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static real_T c12_c_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_d_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, real_T c12_y[4]);
static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static void c12_info_helper(c12_ResolvedFunctionInfo c12_info[38]);
static void c12_inv(SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct
                    *chartInstance, real_T c12_x[9], real_T c12_y[9]);
static void c12_inv3x3(SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct
  *chartInstance, real_T c12_x[9], real_T c12_y[9]);
static real_T c12_norm(SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct
  *chartInstance, real_T c12_x[9]);
static void c12_eml_warning
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void c12_b_eml_warning
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, char_T
   c12_varargin_2[14]);
static void c12_eml_scalar_eg
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void c12_b_eml_scalar_eg
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);
static void c12_e_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_sprintf, const char_T *c12_identifier, char_T c12_y[14]);
static void c12_f_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, char_T c12_y[14]);
static const mxArray *c12_e_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static int32_T c12_g_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static uint8_T c12_h_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_b_is_active_c12_modelo_FK_pratico_coleta_dados_v2, const char_T *
   c12_identifier);
static uint8_T c12_i_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void init_dsm_address_info
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
  chartInstance->c12_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c12_is_active_c12_modelo_FK_pratico_coleta_dados_v2 = 0U;
}

static void initialize_params_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
}

static void enable_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c12_update_debugger_state_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
  const mxArray *c12_st;
  const mxArray *c12_y = NULL;
  int32_T c12_i0;
  real_T c12_u[3];
  const mxArray *c12_b_y = NULL;
  uint8_T c12_hoistedGlobal;
  uint8_T c12_b_u;
  const mxArray *c12_c_y = NULL;
  real_T (*c12_w_saida)[3];
  c12_w_saida = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_st = NULL;
  c12_st = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_createcellarray(2), FALSE);
  for (c12_i0 = 0; c12_i0 < 3; c12_i0++) {
    c12_u[c12_i0] = (*c12_w_saida)[c12_i0];
  }

  c12_b_y = NULL;
  sf_mex_assign(&c12_b_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c12_y, 0, c12_b_y);
  c12_hoistedGlobal =
    chartInstance->c12_is_active_c12_modelo_FK_pratico_coleta_dados_v2;
  c12_b_u = c12_hoistedGlobal;
  c12_c_y = NULL;
  sf_mex_assign(&c12_c_y, sf_mex_create("y", &c12_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c12_y, 1, c12_c_y);
  sf_mex_assign(&c12_st, c12_y, FALSE);
  return c12_st;
}

static void set_sim_state_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_st)
{
  const mxArray *c12_u;
  real_T c12_dv0[3];
  int32_T c12_i1;
  real_T (*c12_w_saida)[3];
  c12_w_saida = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c12_doneDoubleBufferReInit = TRUE;
  c12_u = sf_mex_dup(c12_st);
  c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 0)),
                       "w_saida", c12_dv0);
  for (c12_i1 = 0; c12_i1 < 3; c12_i1++) {
    (*c12_w_saida)[c12_i1] = c12_dv0[c12_i1];
  }

  chartInstance->c12_is_active_c12_modelo_FK_pratico_coleta_dados_v2 =
    c12_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 1)),
    "is_active_c12_modelo_FK_pratico_coleta_dados_v2");
  sf_mex_destroy(&c12_u);
  c12_update_debugger_state_c12_modelo_FK_pratico_coleta_dados_v2(chartInstance);
  sf_mex_destroy(&c12_st);
}

static void finalize_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
}

static void sf_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
  int32_T c12_i2;
  int32_T c12_i3;
  real_T (*c12_w_saida)[3];
  real_T (*c12_w_gyros)[4];
  c12_w_saida = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_w_gyros = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  for (c12_i2 = 0; c12_i2 < 4; c12_i2++) {
    _SFD_DATA_RANGE_CHECK((*c12_w_gyros)[c12_i2], 0U);
  }

  for (c12_i3 = 0; c12_i3 < 3; c12_i3++) {
    _SFD_DATA_RANGE_CHECK((*c12_w_saida)[c12_i3], 1U);
  }

  chartInstance->c12_sfEvent = CALL_EVENT;
  c12_chartstep_c12_modelo_FK_pratico_coleta_dados_v2(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY
    (_modelo_FK_pratico_coleta_dados_v2MachineNumber_,
     chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c12_chartstep_c12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
  int32_T c12_i4;
  real_T c12_w_gyros[4];
  uint32_T c12_debug_family_var_map[10];
  real_T c12_s_12;
  real_T c12_s_23;
  real_T c12_s_31;
  real_T c12_s_456;
  real_T c12_S[4];
  real_T c12_H[12];
  real_T c12_nargin = 1.0;
  real_T c12_nargout = 1.0;
  real_T c12_w_saida[3];
  int32_T c12_i5;
  static real_T c12_dv1[12] = { 0.0, -0.81649658092772592, 0.81649658092772592,
    0.0, 0.94280904158206347, -0.47140452079103173, -0.47140452079103173, 0.0,
    0.33333333333333331, 0.33333333333333331, 0.33333333333333331, -1.0 };

  int32_T c12_i6;
  static real_T c12_dv2[9] = { 1.333333333333333, 0.0, 0.0, 0.0,
    1.3333333333333337, 0.0, 0.0, 0.0, 1.3333333333333333 };

  real_T c12_dv3[9];
  real_T c12_a[9];
  int32_T c12_i7;
  int32_T c12_i8;
  int32_T c12_i9;
  real_T c12_y[12];
  int32_T c12_i10;
  int32_T c12_i11;
  static real_T c12_b[12] = { 0.0, 0.94280904158206347, 0.33333333333333331,
    -0.81649658092772592, -0.47140452079103173, 0.33333333333333331,
    0.81649658092772592, -0.47140452079103173, 0.33333333333333331, 0.0, 0.0,
    -1.0 };

  int32_T c12_i12;
  real_T c12_b_b[4];
  int32_T c12_i13;
  int32_T c12_i14;
  int32_T c12_i15;
  real_T c12_C[3];
  int32_T c12_i16;
  int32_T c12_i17;
  int32_T c12_i18;
  int32_T c12_i19;
  int32_T c12_i20;
  int32_T c12_i21;
  int32_T c12_i22;
  real_T (*c12_b_w_saida)[3];
  real_T (*c12_b_w_gyros)[4];
  c12_b_w_saida = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_b_w_gyros = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  for (c12_i4 = 0; c12_i4 < 4; c12_i4++) {
    c12_w_gyros[c12_i4] = (*c12_b_w_gyros)[c12_i4];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c12_debug_family_names,
    c12_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_s_12, 0U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_s_23, 1U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_s_31, 2U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_s_456, 3U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_S, 4U, c12_b_sf_marshallOut,
    c12_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_H, 5U, c12_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargin, 6U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargout, 7U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_w_gyros, 8U, c12_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_w_saida, 9U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 4);
  c12_s_12 = c12_w_gyros[3];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 5);
  c12_s_23 = c12_w_gyros[2];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 6);
  c12_s_31 = c12_w_gyros[1];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 7);
  c12_s_456 = c12_w_gyros[0];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 9);
  c12_S[0] = c12_s_12;
  c12_S[1] = c12_s_23;
  c12_S[2] = c12_s_31;
  c12_S[3] = c12_s_456;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 11);
  for (c12_i5 = 0; c12_i5 < 12; c12_i5++) {
    c12_H[c12_i5] = c12_dv1[c12_i5];
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 14);
  for (c12_i6 = 0; c12_i6 < 9; c12_i6++) {
    c12_dv3[c12_i6] = c12_dv2[c12_i6];
  }

  c12_inv(chartInstance, c12_dv3, c12_a);
  c12_eml_scalar_eg(chartInstance);
  c12_eml_scalar_eg(chartInstance);
  for (c12_i7 = 0; c12_i7 < 3; c12_i7++) {
    c12_i8 = 0;
    for (c12_i9 = 0; c12_i9 < 4; c12_i9++) {
      c12_y[c12_i8 + c12_i7] = 0.0;
      c12_i10 = 0;
      for (c12_i11 = 0; c12_i11 < 3; c12_i11++) {
        c12_y[c12_i8 + c12_i7] += c12_a[c12_i10 + c12_i7] * c12_b[c12_i11 +
          c12_i8];
        c12_i10 += 3;
      }

      c12_i8 += 3;
    }
  }

  for (c12_i12 = 0; c12_i12 < 4; c12_i12++) {
    c12_b_b[c12_i12] = c12_S[c12_i12];
  }

  c12_b_eml_scalar_eg(chartInstance);
  c12_b_eml_scalar_eg(chartInstance);
  for (c12_i13 = 0; c12_i13 < 3; c12_i13++) {
    c12_w_saida[c12_i13] = 0.0;
  }

  for (c12_i14 = 0; c12_i14 < 3; c12_i14++) {
    c12_w_saida[c12_i14] = 0.0;
  }

  for (c12_i15 = 0; c12_i15 < 3; c12_i15++) {
    c12_C[c12_i15] = c12_w_saida[c12_i15];
  }

  for (c12_i16 = 0; c12_i16 < 3; c12_i16++) {
    c12_w_saida[c12_i16] = c12_C[c12_i16];
  }

  for (c12_i17 = 0; c12_i17 < 3; c12_i17++) {
    c12_C[c12_i17] = c12_w_saida[c12_i17];
  }

  for (c12_i18 = 0; c12_i18 < 3; c12_i18++) {
    c12_w_saida[c12_i18] = c12_C[c12_i18];
  }

  for (c12_i19 = 0; c12_i19 < 3; c12_i19++) {
    c12_w_saida[c12_i19] = 0.0;
    c12_i20 = 0;
    for (c12_i21 = 0; c12_i21 < 4; c12_i21++) {
      c12_w_saida[c12_i19] += c12_y[c12_i20 + c12_i19] * c12_b_b[c12_i21];
      c12_i20 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, -14);
  _SFD_SYMBOL_SCOPE_POP();
  for (c12_i22 = 0; c12_i22 < 3; c12_i22++) {
    (*c12_b_w_saida)[c12_i22] = c12_w_saida[c12_i22];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
}

static void initSimStructsc12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
}

static void registerMessagesc12_modelo_FK_pratico_coleta_dados_v2
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber)
{
}

static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i23;
  real_T c12_b_inData[3];
  int32_T c12_i24;
  real_T c12_u[3];
  const mxArray *c12_y = NULL;
  SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
    chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i23 = 0; c12_i23 < 3; c12_i23++) {
    c12_b_inData[c12_i23] = (*(real_T (*)[3])c12_inData)[c12_i23];
  }

  for (c12_i24 = 0; c12_i24 < 3; c12_i24++) {
    c12_u[c12_i24] = c12_b_inData[c12_i24];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static void c12_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_w_saida, const char_T *c12_identifier, real_T c12_y[3])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_w_saida), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_w_saida);
}

static void c12_b_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, real_T c12_y[3])
{
  real_T c12_dv4[3];
  int32_T c12_i25;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv4, 1, 0, 0U, 1, 0U, 1, 3);
  for (c12_i25 = 0; c12_i25 < 3; c12_i25++) {
    c12_y[c12_i25] = c12_dv4[c12_i25];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_w_saida;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y[3];
  int32_T c12_i26;
  SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
    chartInstanceVoid;
  c12_w_saida = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_w_saida), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_w_saida);
  for (c12_i26 = 0; c12_i26 < 3; c12_i26++) {
    (*(real_T (*)[3])c12_outData)[c12_i26] = c12_y[c12_i26];
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i27;
  real_T c12_b_inData[4];
  int32_T c12_i28;
  real_T c12_u[4];
  const mxArray *c12_y = NULL;
  SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
    chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i27 = 0; c12_i27 < 4; c12_i27++) {
    c12_b_inData[c12_i27] = (*(real_T (*)[4])c12_inData)[c12_i27];
  }

  for (c12_i28 = 0; c12_i28 < 4; c12_i28++) {
    c12_u[c12_i28] = c12_b_inData[c12_i28];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  real_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
    chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(real_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static real_T c12_c_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  real_T c12_y;
  real_T c12_d0;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_d0, 1, 0, 0U, 0, 0U, 0);
  c12_y = c12_d0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_nargout;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y;
  SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
    chartInstanceVoid;
  c12_nargout = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_nargout),
    &c12_thisId);
  sf_mex_destroy(&c12_nargout);
  *(real_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i29;
  int32_T c12_i30;
  int32_T c12_i31;
  real_T c12_b_inData[12];
  int32_T c12_i32;
  int32_T c12_i33;
  int32_T c12_i34;
  real_T c12_u[12];
  const mxArray *c12_y = NULL;
  SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
    chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_i29 = 0;
  for (c12_i30 = 0; c12_i30 < 3; c12_i30++) {
    for (c12_i31 = 0; c12_i31 < 4; c12_i31++) {
      c12_b_inData[c12_i31 + c12_i29] = (*(real_T (*)[12])c12_inData)[c12_i31 +
        c12_i29];
    }

    c12_i29 += 4;
  }

  c12_i32 = 0;
  for (c12_i33 = 0; c12_i33 < 3; c12_i33++) {
    for (c12_i34 = 0; c12_i34 < 4; c12_i34++) {
      c12_u[c12_i34 + c12_i32] = c12_b_inData[c12_i34 + c12_i32];
    }

    c12_i32 += 4;
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 2, 4, 3), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static void c12_d_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, real_T c12_y[4])
{
  real_T c12_dv5[4];
  int32_T c12_i35;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv5, 1, 0, 0U, 1, 0U, 1, 4);
  for (c12_i35 = 0; c12_i35 < 4; c12_i35++) {
    c12_y[c12_i35] = c12_dv5[c12_i35];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_S;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y[4];
  int32_T c12_i36;
  SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
    chartInstanceVoid;
  c12_S = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_S), &c12_thisId, c12_y);
  sf_mex_destroy(&c12_S);
  for (c12_i36 = 0; c12_i36 < 4; c12_i36++) {
    (*(real_T (*)[4])c12_outData)[c12_i36] = c12_y[c12_i36];
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

const mxArray
  *sf_c12_modelo_FK_pratico_coleta_dados_v2_get_eml_resolved_functions_info(void)
{
  const mxArray *c12_nameCaptureInfo;
  c12_ResolvedFunctionInfo c12_info[38];
  const mxArray *c12_m0 = NULL;
  int32_T c12_i37;
  c12_ResolvedFunctionInfo *c12_r0;
  c12_nameCaptureInfo = NULL;
  c12_nameCaptureInfo = NULL;
  c12_info_helper(c12_info);
  sf_mex_assign(&c12_m0, sf_mex_createstruct("nameCaptureInfo", 1, 38), FALSE);
  for (c12_i37 = 0; c12_i37 < 38; c12_i37++) {
    c12_r0 = &c12_info[c12_i37];
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c12_r0->context)), "context", "nameCaptureInfo",
                    c12_i37);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c12_r0->name)), "name", "nameCaptureInfo",
                    c12_i37);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      c12_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c12_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c12_i37);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c12_r0->resolved)), "resolved",
                    "nameCaptureInfo", c12_i37);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", &c12_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c12_i37);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", &c12_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c12_i37);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      &c12_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c12_i37);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      &c12_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c12_i37);
  }

  sf_mex_assign(&c12_nameCaptureInfo, c12_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c12_nameCaptureInfo);
  return c12_nameCaptureInfo;
}

static void c12_info_helper(c12_ResolvedFunctionInfo c12_info[38])
{
  c12_info[0].context = "";
  c12_info[0].name = "sqrt";
  c12_info[0].dominantType = "double";
  c12_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c12_info[0].fileTimeLo = 1343848386U;
  c12_info[0].fileTimeHi = 0U;
  c12_info[0].mFileTimeLo = 0U;
  c12_info[0].mFileTimeHi = 0U;
  c12_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c12_info[1].name = "eml_error";
  c12_info[1].dominantType = "char";
  c12_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c12_info[1].fileTimeLo = 1343848358U;
  c12_info[1].fileTimeHi = 0U;
  c12_info[1].mFileTimeLo = 0U;
  c12_info[1].mFileTimeHi = 0U;
  c12_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c12_info[2].name = "eml_scalar_sqrt";
  c12_info[2].dominantType = "double";
  c12_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c12_info[2].fileTimeLo = 1286836738U;
  c12_info[2].fileTimeHi = 0U;
  c12_info[2].mFileTimeLo = 0U;
  c12_info[2].mFileTimeHi = 0U;
  c12_info[3].context = "";
  c12_info[3].name = "mtimes";
  c12_info[3].dominantType = "double";
  c12_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[3].fileTimeLo = 1289530492U;
  c12_info[3].fileTimeHi = 0U;
  c12_info[3].mFileTimeLo = 0U;
  c12_info[3].mFileTimeHi = 0U;
  c12_info[4].context = "";
  c12_info[4].name = "mrdivide";
  c12_info[4].dominantType = "double";
  c12_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c12_info[4].fileTimeLo = 1357962348U;
  c12_info[4].fileTimeHi = 0U;
  c12_info[4].mFileTimeLo = 1319744366U;
  c12_info[4].mFileTimeHi = 0U;
  c12_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c12_info[5].name = "rdivide";
  c12_info[5].dominantType = "double";
  c12_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c12_info[5].fileTimeLo = 1346528388U;
  c12_info[5].fileTimeHi = 0U;
  c12_info[5].mFileTimeLo = 0U;
  c12_info[5].mFileTimeHi = 0U;
  c12_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c12_info[6].name = "eml_scalexp_compatible";
  c12_info[6].dominantType = "double";
  c12_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c12_info[6].fileTimeLo = 1286836796U;
  c12_info[6].fileTimeHi = 0U;
  c12_info[6].mFileTimeLo = 0U;
  c12_info[6].mFileTimeHi = 0U;
  c12_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c12_info[7].name = "eml_div";
  c12_info[7].dominantType = "double";
  c12_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c12_info[7].fileTimeLo = 1313365810U;
  c12_info[7].fileTimeHi = 0U;
  c12_info[7].mFileTimeLo = 0U;
  c12_info[7].mFileTimeHi = 0U;
  c12_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[8].name = "eml_index_class";
  c12_info[8].dominantType = "";
  c12_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c12_info[8].fileTimeLo = 1323181378U;
  c12_info[8].fileTimeHi = 0U;
  c12_info[8].mFileTimeLo = 0U;
  c12_info[8].mFileTimeHi = 0U;
  c12_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[9].name = "eml_scalar_eg";
  c12_info[9].dominantType = "double";
  c12_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c12_info[9].fileTimeLo = 1286836796U;
  c12_info[9].fileTimeHi = 0U;
  c12_info[9].mFileTimeLo = 0U;
  c12_info[9].mFileTimeHi = 0U;
  c12_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[10].name = "eml_xgemm";
  c12_info[10].dominantType = "char";
  c12_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c12_info[10].fileTimeLo = 1299091172U;
  c12_info[10].fileTimeHi = 0U;
  c12_info[10].mFileTimeLo = 0U;
  c12_info[10].mFileTimeHi = 0U;
  c12_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c12_info[11].name = "eml_blas_inline";
  c12_info[11].dominantType = "";
  c12_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c12_info[11].fileTimeLo = 1299091168U;
  c12_info[11].fileTimeHi = 0U;
  c12_info[11].mFileTimeLo = 0U;
  c12_info[11].mFileTimeHi = 0U;
  c12_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c12_info[12].name = "mtimes";
  c12_info[12].dominantType = "double";
  c12_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[12].fileTimeLo = 1289530492U;
  c12_info[12].fileTimeHi = 0U;
  c12_info[12].mFileTimeLo = 0U;
  c12_info[12].mFileTimeHi = 0U;
  c12_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c12_info[13].name = "eml_index_class";
  c12_info[13].dominantType = "";
  c12_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c12_info[13].fileTimeLo = 1323181378U;
  c12_info[13].fileTimeHi = 0U;
  c12_info[13].mFileTimeLo = 0U;
  c12_info[13].mFileTimeHi = 0U;
  c12_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c12_info[14].name = "eml_scalar_eg";
  c12_info[14].dominantType = "double";
  c12_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c12_info[14].fileTimeLo = 1286836796U;
  c12_info[14].fileTimeHi = 0U;
  c12_info[14].mFileTimeLo = 0U;
  c12_info[14].mFileTimeHi = 0U;
  c12_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c12_info[15].name = "eml_refblas_xgemm";
  c12_info[15].dominantType = "char";
  c12_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c12_info[15].fileTimeLo = 1299091174U;
  c12_info[15].fileTimeHi = 0U;
  c12_info[15].mFileTimeLo = 0U;
  c12_info[15].mFileTimeHi = 0U;
  c12_info[16].context = "";
  c12_info[16].name = "inv";
  c12_info[16].dominantType = "double";
  c12_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c12_info[16].fileTimeLo = 1305336000U;
  c12_info[16].fileTimeHi = 0U;
  c12_info[16].mFileTimeLo = 0U;
  c12_info[16].mFileTimeHi = 0U;
  c12_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c12_info[17].name = "eml_index_class";
  c12_info[17].dominantType = "";
  c12_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c12_info[17].fileTimeLo = 1323181378U;
  c12_info[17].fileTimeHi = 0U;
  c12_info[17].mFileTimeLo = 0U;
  c12_info[17].mFileTimeHi = 0U;
  c12_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c12_info[18].name = "abs";
  c12_info[18].dominantType = "double";
  c12_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c12_info[18].fileTimeLo = 1343848366U;
  c12_info[18].fileTimeHi = 0U;
  c12_info[18].mFileTimeLo = 0U;
  c12_info[18].mFileTimeHi = 0U;
  c12_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c12_info[19].name = "eml_scalar_abs";
  c12_info[19].dominantType = "double";
  c12_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c12_info[19].fileTimeLo = 1286836712U;
  c12_info[19].fileTimeHi = 0U;
  c12_info[19].mFileTimeLo = 0U;
  c12_info[19].mFileTimeHi = 0U;
  c12_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c12_info[20].name = "eml_div";
  c12_info[20].dominantType = "double";
  c12_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c12_info[20].fileTimeLo = 1313365810U;
  c12_info[20].fileTimeHi = 0U;
  c12_info[20].mFileTimeLo = 0U;
  c12_info[20].mFileTimeHi = 0U;
  c12_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c12_info[21].name = "mtimes";
  c12_info[21].dominantType = "double";
  c12_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[21].fileTimeLo = 1289530492U;
  c12_info[21].fileTimeHi = 0U;
  c12_info[21].mFileTimeLo = 0U;
  c12_info[21].mFileTimeHi = 0U;
  c12_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c12_info[22].name = "eml_index_plus";
  c12_info[22].dominantType = "double";
  c12_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c12_info[22].fileTimeLo = 1286836778U;
  c12_info[22].fileTimeHi = 0U;
  c12_info[22].mFileTimeLo = 0U;
  c12_info[22].mFileTimeHi = 0U;
  c12_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c12_info[23].name = "eml_index_class";
  c12_info[23].dominantType = "";
  c12_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c12_info[23].fileTimeLo = 1323181378U;
  c12_info[23].fileTimeHi = 0U;
  c12_info[23].mFileTimeLo = 0U;
  c12_info[23].mFileTimeHi = 0U;
  c12_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c12_info[24].name = "norm";
  c12_info[24].dominantType = "double";
  c12_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c12_info[24].fileTimeLo = 1336540094U;
  c12_info[24].fileTimeHi = 0U;
  c12_info[24].mFileTimeLo = 0U;
  c12_info[24].mFileTimeHi = 0U;
  c12_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c12_info[25].name = "abs";
  c12_info[25].dominantType = "double";
  c12_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c12_info[25].fileTimeLo = 1343848366U;
  c12_info[25].fileTimeHi = 0U;
  c12_info[25].mFileTimeLo = 0U;
  c12_info[25].mFileTimeHi = 0U;
  c12_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c12_info[26].name = "isnan";
  c12_info[26].dominantType = "double";
  c12_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c12_info[26].fileTimeLo = 1286836760U;
  c12_info[26].fileTimeHi = 0U;
  c12_info[26].mFileTimeLo = 0U;
  c12_info[26].mFileTimeHi = 0U;
  c12_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c12_info[27].name = "eml_guarded_nan";
  c12_info[27].dominantType = "char";
  c12_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c12_info[27].fileTimeLo = 1286836776U;
  c12_info[27].fileTimeHi = 0U;
  c12_info[27].mFileTimeLo = 0U;
  c12_info[27].mFileTimeHi = 0U;
  c12_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c12_info[28].name = "eml_is_float_class";
  c12_info[28].dominantType = "char";
  c12_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c12_info[28].fileTimeLo = 1286836782U;
  c12_info[28].fileTimeHi = 0U;
  c12_info[28].mFileTimeLo = 0U;
  c12_info[28].mFileTimeHi = 0U;
  c12_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c12_info[29].name = "mtimes";
  c12_info[29].dominantType = "double";
  c12_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[29].fileTimeLo = 1289530492U;
  c12_info[29].fileTimeHi = 0U;
  c12_info[29].mFileTimeLo = 0U;
  c12_info[29].mFileTimeHi = 0U;
  c12_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c12_info[30].name = "eml_warning";
  c12_info[30].dominantType = "char";
  c12_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c12_info[30].fileTimeLo = 1286836802U;
  c12_info[30].fileTimeHi = 0U;
  c12_info[30].mFileTimeLo = 0U;
  c12_info[30].mFileTimeHi = 0U;
  c12_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c12_info[31].name = "isnan";
  c12_info[31].dominantType = "double";
  c12_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c12_info[31].fileTimeLo = 1286836760U;
  c12_info[31].fileTimeHi = 0U;
  c12_info[31].mFileTimeLo = 0U;
  c12_info[31].mFileTimeHi = 0U;
  c12_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c12_info[32].name = "eps";
  c12_info[32].dominantType = "char";
  c12_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c12_info[32].fileTimeLo = 1326738796U;
  c12_info[32].fileTimeHi = 0U;
  c12_info[32].mFileTimeLo = 0U;
  c12_info[32].mFileTimeHi = 0U;
  c12_info[33].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c12_info[33].name = "eml_is_float_class";
  c12_info[33].dominantType = "char";
  c12_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c12_info[33].fileTimeLo = 1286836782U;
  c12_info[33].fileTimeHi = 0U;
  c12_info[33].mFileTimeLo = 0U;
  c12_info[33].mFileTimeHi = 0U;
  c12_info[34].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c12_info[34].name = "eml_eps";
  c12_info[34].dominantType = "char";
  c12_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c12_info[34].fileTimeLo = 1326738796U;
  c12_info[34].fileTimeHi = 0U;
  c12_info[34].mFileTimeLo = 0U;
  c12_info[34].mFileTimeHi = 0U;
  c12_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c12_info[35].name = "eml_float_model";
  c12_info[35].dominantType = "char";
  c12_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c12_info[35].fileTimeLo = 1326738796U;
  c12_info[35].fileTimeHi = 0U;
  c12_info[35].mFileTimeLo = 0U;
  c12_info[35].mFileTimeHi = 0U;
  c12_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c12_info[36].name = "eml_flt2str";
  c12_info[36].dominantType = "double";
  c12_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c12_info[36].fileTimeLo = 1309469196U;
  c12_info[36].fileTimeHi = 0U;
  c12_info[36].mFileTimeLo = 0U;
  c12_info[36].mFileTimeHi = 0U;
  c12_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c12_info[37].name = "char";
  c12_info[37].dominantType = "double";
  c12_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m";
  c12_info[37].fileTimeLo = 1319744368U;
  c12_info[37].fileTimeHi = 0U;
  c12_info[37].mFileTimeLo = 0U;
  c12_info[37].mFileTimeHi = 0U;
}

static void c12_inv(SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct
                    *chartInstance, real_T c12_x[9], real_T c12_y[9])
{
  int32_T c12_i38;
  real_T c12_b_x[9];
  int32_T c12_i39;
  real_T c12_c_x[9];
  real_T c12_n1x;
  int32_T c12_i40;
  real_T c12_b_y[9];
  real_T c12_n1xinv;
  real_T c12_a;
  real_T c12_b;
  real_T c12_c_y;
  real_T c12_rc;
  real_T c12_d_x;
  boolean_T c12_b_b;
  real_T c12_e_x;
  int32_T c12_i41;
  static char_T c12_cv0[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  char_T c12_u[8];
  const mxArray *c12_d_y = NULL;
  real_T c12_b_u;
  const mxArray *c12_e_y = NULL;
  real_T c12_c_u;
  const mxArray *c12_f_y = NULL;
  real_T c12_d_u;
  const mxArray *c12_g_y = NULL;
  char_T c12_str[14];
  int32_T c12_i42;
  char_T c12_b_str[14];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  for (c12_i38 = 0; c12_i38 < 9; c12_i38++) {
    c12_b_x[c12_i38] = c12_x[c12_i38];
  }

  c12_inv3x3(chartInstance, c12_b_x, c12_y);
  for (c12_i39 = 0; c12_i39 < 9; c12_i39++) {
    c12_c_x[c12_i39] = c12_x[c12_i39];
  }

  c12_n1x = c12_norm(chartInstance, c12_c_x);
  for (c12_i40 = 0; c12_i40 < 9; c12_i40++) {
    c12_b_y[c12_i40] = c12_y[c12_i40];
  }

  c12_n1xinv = c12_norm(chartInstance, c12_b_y);
  c12_a = c12_n1x;
  c12_b = c12_n1xinv;
  c12_c_y = c12_a * c12_b;
  c12_rc = 1.0 / c12_c_y;
  guard1 = FALSE;
  guard2 = FALSE;
  if (c12_n1x == 0.0) {
    guard2 = TRUE;
  } else if (c12_n1xinv == 0.0) {
    guard2 = TRUE;
  } else if (c12_rc == 0.0) {
    guard1 = TRUE;
  } else {
    c12_d_x = c12_rc;
    c12_b_b = muDoubleScalarIsNaN(c12_d_x);
    guard3 = FALSE;
    if (c12_b_b) {
      guard3 = TRUE;
    } else {
      if (c12_rc < 2.2204460492503131E-16) {
        guard3 = TRUE;
      }
    }

    if (guard3 == TRUE) {
      c12_e_x = c12_rc;
      for (c12_i41 = 0; c12_i41 < 8; c12_i41++) {
        c12_u[c12_i41] = c12_cv0[c12_i41];
      }

      c12_d_y = NULL;
      sf_mex_assign(&c12_d_y, sf_mex_create("y", c12_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    FALSE);
      c12_b_u = 14.0;
      c12_e_y = NULL;
      sf_mex_assign(&c12_e_y, sf_mex_create("y", &c12_b_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c12_c_u = 6.0;
      c12_f_y = NULL;
      sf_mex_assign(&c12_f_y, sf_mex_create("y", &c12_c_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c12_d_u = c12_e_x;
      c12_g_y = NULL;
      sf_mex_assign(&c12_g_y, sf_mex_create("y", &c12_d_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c12_e_emlrt_marshallIn(chartInstance, sf_mex_call_debug("sprintf", 1U, 2U,
        14, sf_mex_call_debug("sprintf", 1U, 3U, 14, c12_d_y, 14, c12_e_y, 14,
        c12_f_y), 14, c12_g_y), "sprintf", c12_str);
      for (c12_i42 = 0; c12_i42 < 14; c12_i42++) {
        c12_b_str[c12_i42] = c12_str[c12_i42];
      }

      c12_b_eml_warning(chartInstance, c12_b_str);
    }
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c12_eml_warning(chartInstance);
  }
}

static void c12_inv3x3(SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct
  *chartInstance, real_T c12_x[9], real_T c12_y[9])
{
  int32_T c12_p1;
  int32_T c12_p2;
  int32_T c12_p3;
  real_T c12_b_x;
  real_T c12_c_x;
  real_T c12_absx11;
  real_T c12_d_x;
  real_T c12_e_x;
  real_T c12_absx21;
  real_T c12_f_x;
  real_T c12_g_x;
  real_T c12_absx31;
  real_T c12_t1;
  real_T c12_h_x;
  real_T c12_b_y;
  real_T c12_z;
  real_T c12_i_x;
  real_T c12_c_y;
  real_T c12_b_z;
  real_T c12_a;
  real_T c12_b;
  real_T c12_d_y;
  real_T c12_b_a;
  real_T c12_b_b;
  real_T c12_e_y;
  real_T c12_c_a;
  real_T c12_c_b;
  real_T c12_f_y;
  real_T c12_d_a;
  real_T c12_d_b;
  real_T c12_g_y;
  real_T c12_j_x;
  real_T c12_k_x;
  real_T c12_h_y;
  real_T c12_l_x;
  real_T c12_m_x;
  real_T c12_i_y;
  int32_T c12_itmp;
  real_T c12_n_x;
  real_T c12_j_y;
  real_T c12_c_z;
  real_T c12_e_a;
  real_T c12_e_b;
  real_T c12_k_y;
  real_T c12_f_a;
  real_T c12_f_b;
  real_T c12_l_y;
  real_T c12_o_x;
  real_T c12_m_y;
  real_T c12_t3;
  real_T c12_g_a;
  real_T c12_g_b;
  real_T c12_n_y;
  real_T c12_p_x;
  real_T c12_o_y;
  real_T c12_t2;
  int32_T c12_h_a;
  int32_T c12_c;
  real_T c12_i_a;
  real_T c12_h_b;
  real_T c12_p_y;
  real_T c12_j_a;
  real_T c12_i_b;
  real_T c12_q_y;
  real_T c12_q_x;
  real_T c12_r_y;
  real_T c12_d_z;
  int32_T c12_k_a;
  int32_T c12_b_c;
  int32_T c12_l_a;
  int32_T c12_c_c;
  real_T c12_r_x;
  real_T c12_s_y;
  real_T c12_m_a;
  real_T c12_j_b;
  real_T c12_t_y;
  real_T c12_s_x;
  real_T c12_u_y;
  int32_T c12_n_a;
  int32_T c12_d_c;
  real_T c12_o_a;
  real_T c12_k_b;
  real_T c12_v_y;
  real_T c12_p_a;
  real_T c12_l_b;
  real_T c12_w_y;
  real_T c12_t_x;
  real_T c12_x_y;
  real_T c12_e_z;
  int32_T c12_q_a;
  int32_T c12_e_c;
  int32_T c12_r_a;
  int32_T c12_f_c;
  real_T c12_y_y;
  real_T c12_s_a;
  real_T c12_m_b;
  real_T c12_ab_y;
  real_T c12_u_x;
  real_T c12_bb_y;
  int32_T c12_t_a;
  int32_T c12_g_c;
  real_T c12_u_a;
  real_T c12_n_b;
  real_T c12_cb_y;
  real_T c12_v_a;
  real_T c12_o_b;
  real_T c12_db_y;
  real_T c12_v_x;
  real_T c12_eb_y;
  real_T c12_f_z;
  int32_T c12_w_a;
  int32_T c12_h_c;
  int32_T c12_x_a;
  int32_T c12_i_c;
  boolean_T guard1 = FALSE;
  c12_p1 = 0;
  c12_p2 = 3;
  c12_p3 = 6;
  c12_b_x = c12_x[0];
  c12_c_x = c12_b_x;
  c12_absx11 = muDoubleScalarAbs(c12_c_x);
  c12_d_x = c12_x[1];
  c12_e_x = c12_d_x;
  c12_absx21 = muDoubleScalarAbs(c12_e_x);
  c12_f_x = c12_x[2];
  c12_g_x = c12_f_x;
  c12_absx31 = muDoubleScalarAbs(c12_g_x);
  guard1 = FALSE;
  if (c12_absx21 > c12_absx11) {
    if (c12_absx21 > c12_absx31) {
      c12_p1 = 3;
      c12_p2 = 0;
      c12_t1 = c12_x[0];
      c12_x[0] = c12_x[1];
      c12_x[1] = c12_t1;
      c12_t1 = c12_x[3];
      c12_x[3] = c12_x[4];
      c12_x[4] = c12_t1;
      c12_t1 = c12_x[6];
      c12_x[6] = c12_x[7];
      c12_x[7] = c12_t1;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    if (c12_absx31 > c12_absx11) {
      c12_p1 = 6;
      c12_p3 = 0;
      c12_t1 = c12_x[0];
      c12_x[0] = c12_x[2];
      c12_x[2] = c12_t1;
      c12_t1 = c12_x[3];
      c12_x[3] = c12_x[5];
      c12_x[5] = c12_t1;
      c12_t1 = c12_x[6];
      c12_x[6] = c12_x[8];
      c12_x[8] = c12_t1;
    }
  }

  c12_h_x = c12_x[1];
  c12_b_y = c12_x[0];
  c12_z = c12_h_x / c12_b_y;
  c12_x[1] = c12_z;
  c12_i_x = c12_x[2];
  c12_c_y = c12_x[0];
  c12_b_z = c12_i_x / c12_c_y;
  c12_x[2] = c12_b_z;
  c12_a = c12_x[1];
  c12_b = c12_x[3];
  c12_d_y = c12_a * c12_b;
  c12_x[4] -= c12_d_y;
  c12_b_a = c12_x[2];
  c12_b_b = c12_x[3];
  c12_e_y = c12_b_a * c12_b_b;
  c12_x[5] -= c12_e_y;
  c12_c_a = c12_x[1];
  c12_c_b = c12_x[6];
  c12_f_y = c12_c_a * c12_c_b;
  c12_x[7] -= c12_f_y;
  c12_d_a = c12_x[2];
  c12_d_b = c12_x[6];
  c12_g_y = c12_d_a * c12_d_b;
  c12_x[8] -= c12_g_y;
  c12_j_x = c12_x[5];
  c12_k_x = c12_j_x;
  c12_h_y = muDoubleScalarAbs(c12_k_x);
  c12_l_x = c12_x[4];
  c12_m_x = c12_l_x;
  c12_i_y = muDoubleScalarAbs(c12_m_x);
  if (c12_h_y > c12_i_y) {
    c12_itmp = c12_p2;
    c12_p2 = c12_p3;
    c12_p3 = c12_itmp;
    c12_t1 = c12_x[1];
    c12_x[1] = c12_x[2];
    c12_x[2] = c12_t1;
    c12_t1 = c12_x[4];
    c12_x[4] = c12_x[5];
    c12_x[5] = c12_t1;
    c12_t1 = c12_x[7];
    c12_x[7] = c12_x[8];
    c12_x[8] = c12_t1;
  }

  c12_n_x = c12_x[5];
  c12_j_y = c12_x[4];
  c12_c_z = c12_n_x / c12_j_y;
  c12_x[5] = c12_c_z;
  c12_e_a = c12_x[5];
  c12_e_b = c12_x[7];
  c12_k_y = c12_e_a * c12_e_b;
  c12_x[8] -= c12_k_y;
  c12_f_a = c12_x[5];
  c12_f_b = c12_x[1];
  c12_l_y = c12_f_a * c12_f_b;
  c12_o_x = c12_l_y - c12_x[2];
  c12_m_y = c12_x[8];
  c12_t3 = c12_o_x / c12_m_y;
  c12_g_a = c12_x[7];
  c12_g_b = c12_t3;
  c12_n_y = c12_g_a * c12_g_b;
  c12_p_x = -(c12_x[1] + c12_n_y);
  c12_o_y = c12_x[4];
  c12_t2 = c12_p_x / c12_o_y;
  c12_h_a = c12_p1 + 1;
  c12_c = c12_h_a;
  c12_i_a = c12_x[3];
  c12_h_b = c12_t2;
  c12_p_y = c12_i_a * c12_h_b;
  c12_j_a = c12_x[6];
  c12_i_b = c12_t3;
  c12_q_y = c12_j_a * c12_i_b;
  c12_q_x = (1.0 - c12_p_y) - c12_q_y;
  c12_r_y = c12_x[0];
  c12_d_z = c12_q_x / c12_r_y;
  c12_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c12_c), 1, 9, 1, 0) - 1] = c12_d_z;
  c12_k_a = c12_p1 + 2;
  c12_b_c = c12_k_a;
  c12_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c12_b_c), 1, 9, 1, 0) - 1] = c12_t2;
  c12_l_a = c12_p1 + 3;
  c12_c_c = c12_l_a;
  c12_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c12_c_c), 1, 9, 1, 0) - 1] = c12_t3;
  c12_r_x = -c12_x[5];
  c12_s_y = c12_x[8];
  c12_t3 = c12_r_x / c12_s_y;
  c12_m_a = c12_x[7];
  c12_j_b = c12_t3;
  c12_t_y = c12_m_a * c12_j_b;
  c12_s_x = 1.0 - c12_t_y;
  c12_u_y = c12_x[4];
  c12_t2 = c12_s_x / c12_u_y;
  c12_n_a = c12_p2 + 1;
  c12_d_c = c12_n_a;
  c12_o_a = c12_x[3];
  c12_k_b = c12_t2;
  c12_v_y = c12_o_a * c12_k_b;
  c12_p_a = c12_x[6];
  c12_l_b = c12_t3;
  c12_w_y = c12_p_a * c12_l_b;
  c12_t_x = -(c12_v_y + c12_w_y);
  c12_x_y = c12_x[0];
  c12_e_z = c12_t_x / c12_x_y;
  c12_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c12_d_c), 1, 9, 1, 0) - 1] = c12_e_z;
  c12_q_a = c12_p2 + 2;
  c12_e_c = c12_q_a;
  c12_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c12_e_c), 1, 9, 1, 0) - 1] = c12_t2;
  c12_r_a = c12_p2 + 3;
  c12_f_c = c12_r_a;
  c12_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c12_f_c), 1, 9, 1, 0) - 1] = c12_t3;
  c12_y_y = c12_x[8];
  c12_t3 = 1.0 / c12_y_y;
  c12_s_a = -c12_x[7];
  c12_m_b = c12_t3;
  c12_ab_y = c12_s_a * c12_m_b;
  c12_u_x = c12_ab_y;
  c12_bb_y = c12_x[4];
  c12_t2 = c12_u_x / c12_bb_y;
  c12_t_a = c12_p3 + 1;
  c12_g_c = c12_t_a;
  c12_u_a = c12_x[3];
  c12_n_b = c12_t2;
  c12_cb_y = c12_u_a * c12_n_b;
  c12_v_a = c12_x[6];
  c12_o_b = c12_t3;
  c12_db_y = c12_v_a * c12_o_b;
  c12_v_x = -(c12_cb_y + c12_db_y);
  c12_eb_y = c12_x[0];
  c12_f_z = c12_v_x / c12_eb_y;
  c12_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c12_g_c), 1, 9, 1, 0) - 1] = c12_f_z;
  c12_w_a = c12_p3 + 2;
  c12_h_c = c12_w_a;
  c12_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c12_h_c), 1, 9, 1, 0) - 1] = c12_t2;
  c12_x_a = c12_p3 + 3;
  c12_i_c = c12_x_a;
  c12_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c12_i_c), 1, 9, 1, 0) - 1] = c12_t3;
}

static real_T c12_norm(SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct
  *chartInstance, real_T c12_x[9])
{
  real_T c12_y;
  int32_T c12_j;
  real_T c12_b_j;
  real_T c12_s;
  int32_T c12_i;
  real_T c12_b_i;
  real_T c12_b_x;
  real_T c12_c_x;
  real_T c12_b_y;
  real_T c12_d_x;
  boolean_T c12_b;
  boolean_T exitg1;
  c12_y = 0.0;
  c12_j = 0;
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (c12_j < 3)) {
    c12_b_j = 1.0 + (real_T)c12_j;
    c12_s = 0.0;
    for (c12_i = 0; c12_i < 3; c12_i++) {
      c12_b_i = 1.0 + (real_T)c12_i;
      c12_b_x = c12_x[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c12_b_i), 1, 3, 1, 0) + 3 * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c12_b_j),
        1, 3, 2, 0) - 1)) - 1];
      c12_c_x = c12_b_x;
      c12_b_y = muDoubleScalarAbs(c12_c_x);
      c12_s += c12_b_y;
    }

    c12_d_x = c12_s;
    c12_b = muDoubleScalarIsNaN(c12_d_x);
    if (c12_b) {
      c12_y = rtNaN;
      exitg1 = TRUE;
    } else {
      if (c12_s > c12_y) {
        c12_y = c12_s;
      }

      c12_j++;
    }
  }

  return c12_y;
}

static void c12_eml_warning
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
  int32_T c12_i43;
  static char_T c12_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c12_u[27];
  const mxArray *c12_y = NULL;
  for (c12_i43 = 0; c12_i43 < 27; c12_i43++) {
    c12_u[c12_i43] = c12_varargin_1[c12_i43];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 10, 0U, 1U, 0U, 2, 1, 27),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c12_y));
}

static void c12_b_eml_warning
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, char_T
   c12_varargin_2[14])
{
  int32_T c12_i44;
  static char_T c12_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c12_u[33];
  const mxArray *c12_y = NULL;
  int32_T c12_i45;
  char_T c12_b_u[14];
  const mxArray *c12_b_y = NULL;
  for (c12_i44 = 0; c12_i44 < 33; c12_i44++) {
    c12_u[c12_i44] = c12_varargin_1[c12_i44];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 10, 0U, 1U, 0U, 2, 1, 33),
                FALSE);
  for (c12_i45 = 0; c12_i45 < 14; c12_i45++) {
    c12_b_u[c12_i45] = c12_varargin_2[c12_i45];
  }

  c12_b_y = NULL;
  sf_mex_assign(&c12_b_y, sf_mex_create("y", c12_b_u, 10, 0U, 1U, 0U, 2, 1, 14),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
    14, c12_y, 14, c12_b_y));
}

static void c12_eml_scalar_eg
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
}

static void c12_b_eml_scalar_eg
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
{
}

static void c12_e_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_sprintf, const char_T *c12_identifier, char_T c12_y[14])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_sprintf), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_sprintf);
}

static void c12_f_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, char_T c12_y[14])
{
  char_T c12_cv1[14];
  int32_T c12_i46;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_cv1, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c12_i46 = 0; c12_i46 < 14; c12_i46++) {
    c12_y[c12_i46] = c12_cv1[c12_i46];
  }

  sf_mex_destroy(&c12_u);
}

static const mxArray *c12_e_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
    chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(int32_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static int32_T c12_g_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  int32_T c12_y;
  int32_T c12_i47;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_i47, 1, 6, 0U, 0, 0U, 0);
  c12_y = c12_i47;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_b_sfEvent;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  int32_T c12_y;
  SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
    chartInstanceVoid;
  c12_b_sfEvent = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_b_sfEvent),
    &c12_thisId);
  sf_mex_destroy(&c12_b_sfEvent);
  *(int32_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

static uint8_T c12_h_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_b_is_active_c12_modelo_FK_pratico_coleta_dados_v2, const char_T *
   c12_identifier)
{
  uint8_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c12_b_is_active_c12_modelo_FK_pratico_coleta_dados_v2), &c12_thisId);
  sf_mex_destroy(&c12_b_is_active_c12_modelo_FK_pratico_coleta_dados_v2);
  return c12_y;
}

static uint8_T c12_i_emlrt_marshallIn
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint8_T c12_y;
  uint8_T c12_u0;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u0, 1, 3, 0U, 0, 0U, 0);
  c12_y = c12_u0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void init_dsm_address_info
  (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance)
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

void sf_c12_modelo_FK_pratico_coleta_dados_v2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(364748258U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(659165167U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2817325626U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1266072847U);
}

mxArray *sf_c12_modelo_FK_pratico_coleta_dados_v2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("DZ3FHJjRwExWUgZIm09uu");
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

mxArray *sf_c12_modelo_FK_pratico_coleta_dados_v2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray
  *sf_get_sim_state_info_c12_modelo_FK_pratico_coleta_dados_v2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"w_saida\",},{M[8],M[0],T\"is_active_c12_modelo_FK_pratico_coleta_dados_v2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c12_modelo_FK_pratico_coleta_dados_v2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
    chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modelo_FK_pratico_coleta_dados_v2MachineNumber_,
           12,
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
          init_script_number_translation
            (_modelo_FK_pratico_coleta_dados_v2MachineNumber_,
             chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,
             _modelo_FK_pratico_coleta_dados_v2MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _modelo_FK_pratico_coleta_dados_v2MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"w_gyros");
          _SFD_SET_DATA_PROPS(1,2,0,1,"w_saida");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,290);
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
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)
            c12_sf_marshallIn);
        }

        {
          real_T (*c12_w_gyros)[4];
          real_T (*c12_w_saida)[3];
          c12_w_saida = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c12_w_gyros = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c12_w_gyros);
          _SFD_SET_DATA_VALUE_PTR(1U, *c12_w_saida);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _modelo_FK_pratico_coleta_dados_v2MachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "CbW6DA46D6jIAaeEtXxk5E";
}

static void sf_opaque_initialize_c12_modelo_FK_pratico_coleta_dados_v2(void
  *chartInstanceVar)
{
  chart_debug_initialization
    (((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*) chartInstanceVar
     )->S,0);
  initialize_params_c12_modelo_FK_pratico_coleta_dados_v2
    ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*) chartInstanceVar);
  initialize_c12_modelo_FK_pratico_coleta_dados_v2
    ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c12_modelo_FK_pratico_coleta_dados_v2(void
  *chartInstanceVar)
{
  enable_c12_modelo_FK_pratico_coleta_dados_v2
    ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c12_modelo_FK_pratico_coleta_dados_v2(void
  *chartInstanceVar)
{
  disable_c12_modelo_FK_pratico_coleta_dados_v2
    ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c12_modelo_FK_pratico_coleta_dados_v2(void
  *chartInstanceVar)
{
  sf_c12_modelo_FK_pratico_coleta_dados_v2
    ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*) chartInstanceVar);
}

extern const mxArray*
  sf_internal_get_sim_state_c12_modelo_FK_pratico_coleta_dados_v2(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c12_modelo_FK_pratico_coleta_dados_v2
    ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*)
     chartInfo->chartInstance);        /* raw sim ctx */
  prhs[3] = (mxArray*)
    sf_get_sim_state_info_c12_modelo_FK_pratico_coleta_dados_v2();/* state var info */
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

extern void sf_internal_set_sim_state_c12_modelo_FK_pratico_coleta_dados_v2
  (SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*)
    sf_get_sim_state_info_c12_modelo_FK_pratico_coleta_dados_v2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c12_modelo_FK_pratico_coleta_dados_v2
    ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*)
     chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray*
  sf_opaque_get_sim_state_c12_modelo_FK_pratico_coleta_dados_v2(SimStruct* S)
{
  return sf_internal_get_sim_state_c12_modelo_FK_pratico_coleta_dados_v2(S);
}

static void sf_opaque_set_sim_state_c12_modelo_FK_pratico_coleta_dados_v2
  (SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c12_modelo_FK_pratico_coleta_dados_v2(S, st);
}

static void sf_opaque_terminate_c12_modelo_FK_pratico_coleta_dados_v2(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_FK_pratico_coleta_dados_v2_optimization_info();
    }

    finalize_c12_modelo_FK_pratico_coleta_dados_v2
      ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc12_modelo_FK_pratico_coleta_dados_v2
    ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c12_modelo_FK_pratico_coleta_dados_v2(SimStruct
  *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c12_modelo_FK_pratico_coleta_dados_v2
      ((SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct*)
       (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c12_modelo_FK_pratico_coleta_dados_v2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct =
      load_modelo_FK_pratico_coleta_dados_v2_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      12);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,12,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,12,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,12);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,12,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,12,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,12);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1961848224U));
  ssSetChecksum1(S,(3066228168U));
  ssSetChecksum2(S,(733987971U));
  ssSetChecksum3(S,(2434147789U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c12_modelo_FK_pratico_coleta_dados_v2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c12_modelo_FK_pratico_coleta_dados_v2(SimStruct *S)
{
  SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct *)
    utMalloc(sizeof(SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc12_modelo_FK_pratico_coleta_dados_v2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c12_modelo_FK_pratico_coleta_dados_v2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c12_modelo_FK_pratico_coleta_dados_v2;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c12_modelo_FK_pratico_coleta_dados_v2;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c12_modelo_FK_pratico_coleta_dados_v2;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c12_modelo_FK_pratico_coleta_dados_v2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c12_modelo_FK_pratico_coleta_dados_v2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c12_modelo_FK_pratico_coleta_dados_v2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c12_modelo_FK_pratico_coleta_dados_v2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c12_modelo_FK_pratico_coleta_dados_v2;
  chartInstance->chartInfo.mdlStart =
    mdlStart_c12_modelo_FK_pratico_coleta_dados_v2;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c12_modelo_FK_pratico_coleta_dados_v2;
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

void c12_modelo_FK_pratico_coleta_dados_v2_method_dispatcher(SimStruct *S, int_T
  method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c12_modelo_FK_pratico_coleta_dados_v2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c12_modelo_FK_pratico_coleta_dados_v2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c12_modelo_FK_pratico_coleta_dados_v2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c12_modelo_FK_pratico_coleta_dados_v2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
