/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_FK_simul_coleta_dados_sfun.h"
#include "c7_modelo_FK_simul_coleta_dados.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "modelo_FK_simul_coleta_dados_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c7_debug_family_names[12] = { "rho", "phi", "lambda",
  "T_inv", "S_inv", "nargin", "nargout", "ur", "vsh", "vah", "voh",
  "u_recuperado" };

/* Function Declarations */
static void initialize_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void initialize_params_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void enable_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void disable_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c7_update_debugger_state_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void set_sim_state_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_st);
static void finalize_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void sf_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c7_chartstep_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void initSimStructsc7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void registerMessagesc7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber);
static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData);
static void c7_emlrt_marshallIn(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *
  chartInstance, const mxArray *c7_u_recuperado, const char_T *c7_identifier,
  real_T c7_y[3]);
static void c7_b_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[3]);
static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static real_T c7_c_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_d_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[9]);
static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static void c7_info_helper(c7_ResolvedFunctionInfo c7_info[45]);
static void c7_diag(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
                    *chartInstance, real_T c7_v[3], real_T c7_d[9]);
static void c7_inv(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
                   *chartInstance, real_T c7_x[9], real_T c7_y[9]);
static void c7_inv3x3(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c7_x[9], real_T c7_y[9]);
static real_T c7_norm(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c7_x[9]);
static void c7_eml_warning(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c7_b_eml_warning(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, char_T c7_varargin_2[14]);
static void c7_eml_scalar_eg(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c7_b_eml_scalar_eg(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c7_e_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_sprintf, const char_T *c7_identifier, char_T c7_y[14]);
static void c7_f_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId, char_T c7_y[14]);
static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static int32_T c7_g_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static uint8_T c7_h_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_b_is_active_c7_modelo_FK_simul_coleta_dados, const char_T *c7_identifier);
static uint8_T c7_i_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void init_dsm_address_info
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  chartInstance->c7_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c7_is_active_c7_modelo_FK_simul_coleta_dados = 0U;
}

static void initialize_params_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void enable_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c7_update_debugger_state_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  const mxArray *c7_st;
  const mxArray *c7_y = NULL;
  int32_T c7_i0;
  real_T c7_u[3];
  const mxArray *c7_b_y = NULL;
  uint8_T c7_hoistedGlobal;
  uint8_T c7_b_u;
  const mxArray *c7_c_y = NULL;
  real_T (*c7_u_recuperado)[3];
  c7_u_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_st = NULL;
  c7_st = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_createcellarray(2), FALSE);
  for (c7_i0 = 0; c7_i0 < 3; c7_i0++) {
    c7_u[c7_i0] = (*c7_u_recuperado)[c7_i0];
  }

  c7_b_y = NULL;
  sf_mex_assign(&c7_b_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c7_y, 0, c7_b_y);
  c7_hoistedGlobal = chartInstance->c7_is_active_c7_modelo_FK_simul_coleta_dados;
  c7_b_u = c7_hoistedGlobal;
  c7_c_y = NULL;
  sf_mex_assign(&c7_c_y, sf_mex_create("y", &c7_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c7_y, 1, c7_c_y);
  sf_mex_assign(&c7_st, c7_y, FALSE);
  return c7_st;
}

static void set_sim_state_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_st)
{
  const mxArray *c7_u;
  real_T c7_dv0[3];
  int32_T c7_i1;
  real_T (*c7_u_recuperado)[3];
  c7_u_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c7_doneDoubleBufferReInit = TRUE;
  c7_u = sf_mex_dup(c7_st);
  c7_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 0)),
                      "u_recuperado", c7_dv0);
  for (c7_i1 = 0; c7_i1 < 3; c7_i1++) {
    (*c7_u_recuperado)[c7_i1] = c7_dv0[c7_i1];
  }

  chartInstance->c7_is_active_c7_modelo_FK_simul_coleta_dados =
    c7_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 1)),
    "is_active_c7_modelo_FK_simul_coleta_dados");
  sf_mex_destroy(&c7_u);
  c7_update_debugger_state_c7_modelo_FK_simul_coleta_dados(chartInstance);
  sf_mex_destroy(&c7_st);
}

static void finalize_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void sf_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  int32_T c7_i2;
  int32_T c7_i3;
  int32_T c7_i4;
  int32_T c7_i5;
  int32_T c7_i6;
  real_T (*c7_voh)[3];
  real_T (*c7_vah)[3];
  real_T (*c7_vsh)[3];
  real_T (*c7_u_recuperado)[3];
  real_T (*c7_ur)[3];
  c7_voh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c7_vah = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c7_vsh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c7_u_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_ur = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 6U, chartInstance->c7_sfEvent);
  for (c7_i2 = 0; c7_i2 < 3; c7_i2++) {
    _SFD_DATA_RANGE_CHECK((*c7_ur)[c7_i2], 0U);
  }

  for (c7_i3 = 0; c7_i3 < 3; c7_i3++) {
    _SFD_DATA_RANGE_CHECK((*c7_u_recuperado)[c7_i3], 1U);
  }

  for (c7_i4 = 0; c7_i4 < 3; c7_i4++) {
    _SFD_DATA_RANGE_CHECK((*c7_vsh)[c7_i4], 2U);
  }

  for (c7_i5 = 0; c7_i5 < 3; c7_i5++) {
    _SFD_DATA_RANGE_CHECK((*c7_vah)[c7_i5], 3U);
  }

  for (c7_i6 = 0; c7_i6 < 3; c7_i6++) {
    _SFD_DATA_RANGE_CHECK((*c7_voh)[c7_i6], 4U);
  }

  chartInstance->c7_sfEvent = CALL_EVENT;
  c7_chartstep_c7_modelo_FK_simul_coleta_dados(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_modelo_FK_simul_coleta_dadosMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c7_chartstep_c7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  int32_T c7_i7;
  real_T c7_ur[3];
  int32_T c7_i8;
  real_T c7_vsh[3];
  int32_T c7_i9;
  real_T c7_vah[3];
  int32_T c7_i10;
  real_T c7_voh[3];
  uint32_T c7_debug_family_var_map[12];
  real_T c7_rho;
  real_T c7_phi;
  real_T c7_lambda;
  real_T c7_T_inv[9];
  real_T c7_S_inv[9];
  real_T c7_nargin = 4.0;
  real_T c7_nargout = 1.0;
  real_T c7_u_recuperado[3];
  real_T c7_x;
  real_T c7_b_x;
  real_T c7_c_x;
  real_T c7_d_x;
  real_T c7_B;
  real_T c7_y;
  real_T c7_b_y;
  real_T c7_c_y;
  real_T c7_e_x;
  real_T c7_f_x;
  real_T c7_g_x;
  real_T c7_h_x;
  real_T c7_a;
  real_T c7_b;
  real_T c7_d_y;
  real_T c7_i_x;
  real_T c7_j_x;
  real_T c7_k_x;
  real_T c7_l_x;
  real_T c7_m_x;
  real_T c7_n_x;
  real_T c7_A;
  real_T c7_b_B;
  real_T c7_o_x;
  real_T c7_e_y;
  real_T c7_p_x;
  real_T c7_f_y;
  real_T c7_g_y;
  real_T c7_q_x;
  real_T c7_r_x;
  real_T c7_s_x;
  real_T c7_t_x;
  real_T c7_b_a;
  real_T c7_b_b;
  real_T c7_h_y;
  real_T c7_c_B;
  real_T c7_i_y;
  real_T c7_j_y;
  real_T c7_k_y;
  int32_T c7_i11;
  int32_T c7_i12;
  static real_T c7_dv1[3] = { 1.0, 0.0, 0.0 };

  int32_T c7_i13;
  real_T c7_b_vsh[3];
  real_T c7_c_a[9];
  int32_T c7_i14;
  real_T c7_d_a[9];
  real_T c7_dv2[9];
  int32_T c7_i15;
  int32_T c7_i16;
  int32_T c7_i17;
  real_T c7_c_b[9];
  int32_T c7_i18;
  int32_T c7_i19;
  int32_T c7_i20;
  real_T c7_l_y[9];
  int32_T c7_i21;
  int32_T c7_i22;
  int32_T c7_i23;
  real_T c7_d_b[3];
  int32_T c7_i24;
  int32_T c7_i25;
  int32_T c7_i26;
  real_T c7_C[3];
  int32_T c7_i27;
  int32_T c7_i28;
  int32_T c7_i29;
  int32_T c7_i30;
  int32_T c7_i31;
  int32_T c7_i32;
  int32_T c7_i33;
  real_T (*c7_b_u_recuperado)[3];
  real_T (*c7_b_voh)[3];
  real_T (*c7_b_vah)[3];
  real_T (*c7_c_vsh)[3];
  real_T (*c7_b_ur)[3];
  c7_b_voh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c7_b_vah = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c7_c_vsh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c7_b_u_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_b_ur = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 6U, chartInstance->c7_sfEvent);
  for (c7_i7 = 0; c7_i7 < 3; c7_i7++) {
    c7_ur[c7_i7] = (*c7_b_ur)[c7_i7];
  }

  for (c7_i8 = 0; c7_i8 < 3; c7_i8++) {
    c7_vsh[c7_i8] = (*c7_c_vsh)[c7_i8];
  }

  for (c7_i9 = 0; c7_i9 < 3; c7_i9++) {
    c7_vah[c7_i9] = (*c7_b_vah)[c7_i9];
  }

  for (c7_i10 = 0; c7_i10 < 3; c7_i10++) {
    c7_voh[c7_i10] = (*c7_b_voh)[c7_i10];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c7_debug_family_names,
    c7_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_rho, 0U, c7_b_sf_marshallOut,
    c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_phi, 1U, c7_b_sf_marshallOut,
    c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_lambda, 2U, c7_b_sf_marshallOut,
    c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_T_inv, 3U, c7_c_sf_marshallOut,
    c7_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_S_inv, 4U, c7_c_sf_marshallOut,
    c7_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargin, 5U, c7_b_sf_marshallOut,
    c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargout, 6U, c7_b_sf_marshallOut,
    c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c7_ur, 7U, c7_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c7_vsh, 8U, c7_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c7_vah, 9U, c7_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c7_voh, 10U, c7_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_u_recuperado, 11U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 4);
  c7_rho = c7_vah[0];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 5);
  c7_phi = c7_vah[1];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 6);
  c7_lambda = c7_vah[2];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 8);
  c7_x = c7_rho;
  c7_b_x = c7_x;
  c7_b_x = muDoubleScalarTan(c7_b_x);
  c7_c_x = c7_rho;
  c7_d_x = c7_c_x;
  c7_d_x = muDoubleScalarCos(c7_d_x);
  c7_B = c7_d_x;
  c7_y = c7_B;
  c7_b_y = c7_y;
  c7_c_y = 1.0 / c7_b_y;
  c7_e_x = c7_rho;
  c7_f_x = c7_e_x;
  c7_f_x = muDoubleScalarTan(c7_f_x);
  c7_g_x = c7_lambda;
  c7_h_x = c7_g_x;
  c7_h_x = muDoubleScalarTan(c7_h_x);
  c7_a = c7_f_x;
  c7_b = c7_h_x;
  c7_d_y = c7_a * c7_b;
  c7_i_x = c7_phi;
  c7_j_x = c7_i_x;
  c7_j_x = muDoubleScalarTan(c7_j_x);
  c7_k_x = c7_lambda;
  c7_l_x = c7_k_x;
  c7_l_x = muDoubleScalarTan(c7_l_x);
  c7_m_x = c7_rho;
  c7_n_x = c7_m_x;
  c7_n_x = muDoubleScalarCos(c7_n_x);
  c7_A = -c7_l_x;
  c7_b_B = c7_n_x;
  c7_o_x = c7_A;
  c7_e_y = c7_b_B;
  c7_p_x = c7_o_x;
  c7_f_y = c7_e_y;
  c7_g_y = c7_p_x / c7_f_y;
  c7_q_x = c7_lambda;
  c7_r_x = c7_q_x;
  c7_r_x = muDoubleScalarCos(c7_r_x);
  c7_s_x = c7_phi;
  c7_t_x = c7_s_x;
  c7_t_x = muDoubleScalarCos(c7_t_x);
  c7_b_a = c7_r_x;
  c7_b_b = c7_t_x;
  c7_h_y = c7_b_a * c7_b_b;
  c7_c_B = c7_h_y;
  c7_i_y = c7_c_B;
  c7_j_y = c7_i_y;
  c7_k_y = 1.0 / c7_j_y;
  c7_i11 = 0;
  for (c7_i12 = 0; c7_i12 < 3; c7_i12++) {
    c7_T_inv[c7_i11] = c7_dv1[c7_i12];
    c7_i11 += 3;
  }

  c7_T_inv[1] = -c7_b_x;
  c7_T_inv[4] = c7_c_y;
  c7_T_inv[7] = 0.0;
  c7_T_inv[2] = c7_d_y - c7_j_x;
  c7_T_inv[5] = c7_g_y;
  c7_T_inv[8] = c7_k_y;
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 10);
  for (c7_i13 = 0; c7_i13 < 3; c7_i13++) {
    c7_b_vsh[c7_i13] = c7_vsh[c7_i13];
  }

  c7_diag(chartInstance, c7_b_vsh, c7_c_a);
  for (c7_i14 = 0; c7_i14 < 9; c7_i14++) {
    c7_d_a[c7_i14] = c7_c_a[c7_i14];
  }

  c7_inv(chartInstance, c7_d_a, c7_dv2);
  for (c7_i15 = 0; c7_i15 < 9; c7_i15++) {
    c7_S_inv[c7_i15] = c7_dv2[c7_i15];
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 12);
  for (c7_i16 = 0; c7_i16 < 9; c7_i16++) {
    c7_c_a[c7_i16] = c7_T_inv[c7_i16];
  }

  for (c7_i17 = 0; c7_i17 < 9; c7_i17++) {
    c7_c_b[c7_i17] = c7_S_inv[c7_i17];
  }

  c7_eml_scalar_eg(chartInstance);
  c7_eml_scalar_eg(chartInstance);
  for (c7_i18 = 0; c7_i18 < 3; c7_i18++) {
    c7_i19 = 0;
    for (c7_i20 = 0; c7_i20 < 3; c7_i20++) {
      c7_l_y[c7_i19 + c7_i18] = 0.0;
      c7_i21 = 0;
      for (c7_i22 = 0; c7_i22 < 3; c7_i22++) {
        c7_l_y[c7_i19 + c7_i18] += c7_c_a[c7_i21 + c7_i18] * c7_c_b[c7_i22 +
          c7_i19];
        c7_i21 += 3;
      }

      c7_i19 += 3;
    }
  }

  for (c7_i23 = 0; c7_i23 < 3; c7_i23++) {
    c7_d_b[c7_i23] = c7_ur[c7_i23] - c7_voh[c7_i23];
  }

  c7_b_eml_scalar_eg(chartInstance);
  c7_b_eml_scalar_eg(chartInstance);
  for (c7_i24 = 0; c7_i24 < 3; c7_i24++) {
    c7_u_recuperado[c7_i24] = 0.0;
  }

  for (c7_i25 = 0; c7_i25 < 3; c7_i25++) {
    c7_u_recuperado[c7_i25] = 0.0;
  }

  for (c7_i26 = 0; c7_i26 < 3; c7_i26++) {
    c7_C[c7_i26] = c7_u_recuperado[c7_i26];
  }

  for (c7_i27 = 0; c7_i27 < 3; c7_i27++) {
    c7_u_recuperado[c7_i27] = c7_C[c7_i27];
  }

  for (c7_i28 = 0; c7_i28 < 3; c7_i28++) {
    c7_C[c7_i28] = c7_u_recuperado[c7_i28];
  }

  for (c7_i29 = 0; c7_i29 < 3; c7_i29++) {
    c7_u_recuperado[c7_i29] = c7_C[c7_i29];
  }

  for (c7_i30 = 0; c7_i30 < 3; c7_i30++) {
    c7_u_recuperado[c7_i30] = 0.0;
    c7_i31 = 0;
    for (c7_i32 = 0; c7_i32 < 3; c7_i32++) {
      c7_u_recuperado[c7_i30] += c7_l_y[c7_i31 + c7_i30] * c7_d_b[c7_i32];
      c7_i31 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, -12);
  _SFD_SYMBOL_SCOPE_POP();
  for (c7_i33 = 0; c7_i33 < 3; c7_i33++) {
    (*c7_b_u_recuperado)[c7_i33] = c7_u_recuperado[c7_i33];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c7_sfEvent);
}

static void initSimStructsc7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void registerMessagesc7_modelo_FK_simul_coleta_dados
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber)
{
}

static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i34;
  real_T c7_b_inData[3];
  int32_T c7_i35;
  real_T c7_u[3];
  const mxArray *c7_y = NULL;
  SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  for (c7_i34 = 0; c7_i34 < 3; c7_i34++) {
    c7_b_inData[c7_i34] = (*(real_T (*)[3])c7_inData)[c7_i34];
  }

  for (c7_i35 = 0; c7_i35 < 3; c7_i35++) {
    c7_u[c7_i35] = c7_b_inData[c7_i35];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static void c7_emlrt_marshallIn(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *
  chartInstance, const mxArray *c7_u_recuperado, const char_T *c7_identifier,
  real_T c7_y[3])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_u_recuperado), &c7_thisId,
                        c7_y);
  sf_mex_destroy(&c7_u_recuperado);
}

static void c7_b_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[3])
{
  real_T c7_dv3[3];
  int32_T c7_i36;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c7_i36 = 0; c7_i36 < 3; c7_i36++) {
    c7_y[c7_i36] = c7_dv3[c7_i36];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_u_recuperado;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[3];
  int32_T c7_i37;
  SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c7_u_recuperado = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_u_recuperado), &c7_thisId,
                        c7_y);
  sf_mex_destroy(&c7_u_recuperado);
  for (c7_i37 = 0; c7_i37 < 3; c7_i37++) {
    (*(real_T (*)[3])c7_outData)[c7_i37] = c7_y[c7_i37];
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  real_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(real_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static real_T c7_c_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  real_T c7_y;
  real_T c7_d0;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_d0, 1, 0, 0U, 0, 0U, 0);
  c7_y = c7_d0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_nargout;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y;
  SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c7_nargout = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_nargout), &c7_thisId);
  sf_mex_destroy(&c7_nargout);
  *(real_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i38;
  int32_T c7_i39;
  int32_T c7_i40;
  real_T c7_b_inData[9];
  int32_T c7_i41;
  int32_T c7_i42;
  int32_T c7_i43;
  real_T c7_u[9];
  const mxArray *c7_y = NULL;
  SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_i38 = 0;
  for (c7_i39 = 0; c7_i39 < 3; c7_i39++) {
    for (c7_i40 = 0; c7_i40 < 3; c7_i40++) {
      c7_b_inData[c7_i40 + c7_i38] = (*(real_T (*)[9])c7_inData)[c7_i40 + c7_i38];
    }

    c7_i38 += 3;
  }

  c7_i41 = 0;
  for (c7_i42 = 0; c7_i42 < 3; c7_i42++) {
    for (c7_i43 = 0; c7_i43 < 3; c7_i43++) {
      c7_u[c7_i43 + c7_i41] = c7_b_inData[c7_i43 + c7_i41];
    }

    c7_i41 += 3;
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static void c7_d_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[9])
{
  real_T c7_dv4[9];
  int32_T c7_i44;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv4, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c7_i44 = 0; c7_i44 < 9; c7_i44++) {
    c7_y[c7_i44] = c7_dv4[c7_i44];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_S_inv;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[9];
  int32_T c7_i45;
  int32_T c7_i46;
  int32_T c7_i47;
  SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c7_S_inv = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_S_inv), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_S_inv);
  c7_i45 = 0;
  for (c7_i46 = 0; c7_i46 < 3; c7_i46++) {
    for (c7_i47 = 0; c7_i47 < 3; c7_i47++) {
      (*(real_T (*)[9])c7_outData)[c7_i47 + c7_i45] = c7_y[c7_i47 + c7_i45];
    }

    c7_i45 += 3;
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

const mxArray
  *sf_c7_modelo_FK_simul_coleta_dados_get_eml_resolved_functions_info(void)
{
  const mxArray *c7_nameCaptureInfo;
  c7_ResolvedFunctionInfo c7_info[45];
  const mxArray *c7_m0 = NULL;
  int32_T c7_i48;
  c7_ResolvedFunctionInfo *c7_r0;
  c7_nameCaptureInfo = NULL;
  c7_nameCaptureInfo = NULL;
  c7_info_helper(c7_info);
  sf_mex_assign(&c7_m0, sf_mex_createstruct("nameCaptureInfo", 1, 45), FALSE);
  for (c7_i48 = 0; c7_i48 < 45; c7_i48++) {
    c7_r0 = &c7_info[c7_i48];
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", c7_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c7_r0->context)), "context", "nameCaptureInfo",
                    c7_i48);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", c7_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c7_r0->name)), "name", "nameCaptureInfo", c7_i48);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", c7_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c7_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c7_i48);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", c7_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c7_r0->resolved)), "resolved", "nameCaptureInfo",
                    c7_i48);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", &c7_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c7_i48);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", &c7_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c7_i48);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", &c7_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c7_i48);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", &c7_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c7_i48);
  }

  sf_mex_assign(&c7_nameCaptureInfo, c7_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c7_nameCaptureInfo);
  return c7_nameCaptureInfo;
}

static void c7_info_helper(c7_ResolvedFunctionInfo c7_info[45])
{
  c7_info[0].context = "";
  c7_info[0].name = "tan";
  c7_info[0].dominantType = "double";
  c7_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/tan.m";
  c7_info[0].fileTimeLo = 1343848386U;
  c7_info[0].fileTimeHi = 0U;
  c7_info[0].mFileTimeLo = 0U;
  c7_info[0].mFileTimeHi = 0U;
  c7_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/tan.m";
  c7_info[1].name = "eml_scalar_tan";
  c7_info[1].dominantType = "double";
  c7_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_tan.m";
  c7_info[1].fileTimeLo = 1286836738U;
  c7_info[1].fileTimeHi = 0U;
  c7_info[1].mFileTimeLo = 0U;
  c7_info[1].mFileTimeHi = 0U;
  c7_info[2].context = "";
  c7_info[2].name = "cos";
  c7_info[2].dominantType = "double";
  c7_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c7_info[2].fileTimeLo = 1343848372U;
  c7_info[2].fileTimeHi = 0U;
  c7_info[2].mFileTimeLo = 0U;
  c7_info[2].mFileTimeHi = 0U;
  c7_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c7_info[3].name = "eml_scalar_cos";
  c7_info[3].dominantType = "double";
  c7_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c7_info[3].fileTimeLo = 1286836722U;
  c7_info[3].fileTimeHi = 0U;
  c7_info[3].mFileTimeLo = 0U;
  c7_info[3].mFileTimeHi = 0U;
  c7_info[4].context = "";
  c7_info[4].name = "mrdivide";
  c7_info[4].dominantType = "double";
  c7_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c7_info[4].fileTimeLo = 1357962348U;
  c7_info[4].fileTimeHi = 0U;
  c7_info[4].mFileTimeLo = 1319744366U;
  c7_info[4].mFileTimeHi = 0U;
  c7_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c7_info[5].name = "rdivide";
  c7_info[5].dominantType = "double";
  c7_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c7_info[5].fileTimeLo = 1346528388U;
  c7_info[5].fileTimeHi = 0U;
  c7_info[5].mFileTimeLo = 0U;
  c7_info[5].mFileTimeHi = 0U;
  c7_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c7_info[6].name = "eml_scalexp_compatible";
  c7_info[6].dominantType = "double";
  c7_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c7_info[6].fileTimeLo = 1286836796U;
  c7_info[6].fileTimeHi = 0U;
  c7_info[6].mFileTimeLo = 0U;
  c7_info[6].mFileTimeHi = 0U;
  c7_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c7_info[7].name = "eml_div";
  c7_info[7].dominantType = "double";
  c7_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c7_info[7].fileTimeLo = 1313365810U;
  c7_info[7].fileTimeHi = 0U;
  c7_info[7].mFileTimeLo = 0U;
  c7_info[7].mFileTimeHi = 0U;
  c7_info[8].context = "";
  c7_info[8].name = "mtimes";
  c7_info[8].dominantType = "double";
  c7_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c7_info[8].fileTimeLo = 1289530492U;
  c7_info[8].fileTimeHi = 0U;
  c7_info[8].mFileTimeLo = 0U;
  c7_info[8].mFileTimeHi = 0U;
  c7_info[9].context = "";
  c7_info[9].name = "diag";
  c7_info[9].dominantType = "double";
  c7_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c7_info[9].fileTimeLo = 1286836686U;
  c7_info[9].fileTimeHi = 0U;
  c7_info[9].mFileTimeLo = 0U;
  c7_info[9].mFileTimeHi = 0U;
  c7_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c7_info[10].name = "eml_index_class";
  c7_info[10].dominantType = "";
  c7_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c7_info[10].fileTimeLo = 1323181378U;
  c7_info[10].fileTimeHi = 0U;
  c7_info[10].mFileTimeLo = 0U;
  c7_info[10].mFileTimeHi = 0U;
  c7_info[11].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c7_info[11].name = "eml_index_plus";
  c7_info[11].dominantType = "coder.internal.indexInt";
  c7_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c7_info[11].fileTimeLo = 1286836778U;
  c7_info[11].fileTimeHi = 0U;
  c7_info[11].mFileTimeLo = 0U;
  c7_info[11].mFileTimeHi = 0U;
  c7_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c7_info[12].name = "eml_index_class";
  c7_info[12].dominantType = "";
  c7_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c7_info[12].fileTimeLo = 1323181378U;
  c7_info[12].fileTimeHi = 0U;
  c7_info[12].mFileTimeLo = 0U;
  c7_info[12].mFileTimeHi = 0U;
  c7_info[13].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c7_info[13].name = "eml_scalar_eg";
  c7_info[13].dominantType = "double";
  c7_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c7_info[13].fileTimeLo = 1286836796U;
  c7_info[13].fileTimeHi = 0U;
  c7_info[13].mFileTimeLo = 0U;
  c7_info[13].mFileTimeHi = 0U;
  c7_info[14].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c7_info[14].name = "eml_int_forloop_overflow_check";
  c7_info[14].dominantType = "";
  c7_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c7_info[14].fileTimeLo = 1346528340U;
  c7_info[14].fileTimeHi = 0U;
  c7_info[14].mFileTimeLo = 0U;
  c7_info[14].mFileTimeHi = 0U;
  c7_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c7_info[15].name = "intmax";
  c7_info[15].dominantType = "char";
  c7_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c7_info[15].fileTimeLo = 1311273316U;
  c7_info[15].fileTimeHi = 0U;
  c7_info[15].mFileTimeLo = 0U;
  c7_info[15].mFileTimeHi = 0U;
  c7_info[16].context = "";
  c7_info[16].name = "inv";
  c7_info[16].dominantType = "double";
  c7_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c7_info[16].fileTimeLo = 1305336000U;
  c7_info[16].fileTimeHi = 0U;
  c7_info[16].mFileTimeLo = 0U;
  c7_info[16].mFileTimeHi = 0U;
  c7_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c7_info[17].name = "eml_index_class";
  c7_info[17].dominantType = "";
  c7_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c7_info[17].fileTimeLo = 1323181378U;
  c7_info[17].fileTimeHi = 0U;
  c7_info[17].mFileTimeLo = 0U;
  c7_info[17].mFileTimeHi = 0U;
  c7_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c7_info[18].name = "abs";
  c7_info[18].dominantType = "double";
  c7_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c7_info[18].fileTimeLo = 1343848366U;
  c7_info[18].fileTimeHi = 0U;
  c7_info[18].mFileTimeLo = 0U;
  c7_info[18].mFileTimeHi = 0U;
  c7_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c7_info[19].name = "eml_scalar_abs";
  c7_info[19].dominantType = "double";
  c7_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c7_info[19].fileTimeLo = 1286836712U;
  c7_info[19].fileTimeHi = 0U;
  c7_info[19].mFileTimeLo = 0U;
  c7_info[19].mFileTimeHi = 0U;
  c7_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c7_info[20].name = "eml_div";
  c7_info[20].dominantType = "double";
  c7_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c7_info[20].fileTimeLo = 1313365810U;
  c7_info[20].fileTimeHi = 0U;
  c7_info[20].mFileTimeLo = 0U;
  c7_info[20].mFileTimeHi = 0U;
  c7_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c7_info[21].name = "mtimes";
  c7_info[21].dominantType = "double";
  c7_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c7_info[21].fileTimeLo = 1289530492U;
  c7_info[21].fileTimeHi = 0U;
  c7_info[21].mFileTimeLo = 0U;
  c7_info[21].mFileTimeHi = 0U;
  c7_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c7_info[22].name = "eml_index_plus";
  c7_info[22].dominantType = "double";
  c7_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c7_info[22].fileTimeLo = 1286836778U;
  c7_info[22].fileTimeHi = 0U;
  c7_info[22].mFileTimeLo = 0U;
  c7_info[22].mFileTimeHi = 0U;
  c7_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c7_info[23].name = "norm";
  c7_info[23].dominantType = "double";
  c7_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c7_info[23].fileTimeLo = 1336540094U;
  c7_info[23].fileTimeHi = 0U;
  c7_info[23].mFileTimeLo = 0U;
  c7_info[23].mFileTimeHi = 0U;
  c7_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c7_info[24].name = "abs";
  c7_info[24].dominantType = "double";
  c7_info[24].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c7_info[24].fileTimeLo = 1343848366U;
  c7_info[24].fileTimeHi = 0U;
  c7_info[24].mFileTimeLo = 0U;
  c7_info[24].mFileTimeHi = 0U;
  c7_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c7_info[25].name = "isnan";
  c7_info[25].dominantType = "double";
  c7_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c7_info[25].fileTimeLo = 1286836760U;
  c7_info[25].fileTimeHi = 0U;
  c7_info[25].mFileTimeLo = 0U;
  c7_info[25].mFileTimeHi = 0U;
  c7_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c7_info[26].name = "eml_guarded_nan";
  c7_info[26].dominantType = "char";
  c7_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c7_info[26].fileTimeLo = 1286836776U;
  c7_info[26].fileTimeHi = 0U;
  c7_info[26].mFileTimeLo = 0U;
  c7_info[26].mFileTimeHi = 0U;
  c7_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c7_info[27].name = "eml_is_float_class";
  c7_info[27].dominantType = "char";
  c7_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c7_info[27].fileTimeLo = 1286836782U;
  c7_info[27].fileTimeHi = 0U;
  c7_info[27].mFileTimeLo = 0U;
  c7_info[27].mFileTimeHi = 0U;
  c7_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c7_info[28].name = "mtimes";
  c7_info[28].dominantType = "double";
  c7_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c7_info[28].fileTimeLo = 1289530492U;
  c7_info[28].fileTimeHi = 0U;
  c7_info[28].mFileTimeLo = 0U;
  c7_info[28].mFileTimeHi = 0U;
  c7_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c7_info[29].name = "eml_warning";
  c7_info[29].dominantType = "char";
  c7_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c7_info[29].fileTimeLo = 1286836802U;
  c7_info[29].fileTimeHi = 0U;
  c7_info[29].mFileTimeLo = 0U;
  c7_info[29].mFileTimeHi = 0U;
  c7_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c7_info[30].name = "isnan";
  c7_info[30].dominantType = "double";
  c7_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c7_info[30].fileTimeLo = 1286836760U;
  c7_info[30].fileTimeHi = 0U;
  c7_info[30].mFileTimeLo = 0U;
  c7_info[30].mFileTimeHi = 0U;
  c7_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c7_info[31].name = "eps";
  c7_info[31].dominantType = "char";
  c7_info[31].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c7_info[31].fileTimeLo = 1326738796U;
  c7_info[31].fileTimeHi = 0U;
  c7_info[31].mFileTimeLo = 0U;
  c7_info[31].mFileTimeHi = 0U;
  c7_info[32].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c7_info[32].name = "eml_is_float_class";
  c7_info[32].dominantType = "char";
  c7_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c7_info[32].fileTimeLo = 1286836782U;
  c7_info[32].fileTimeHi = 0U;
  c7_info[32].mFileTimeLo = 0U;
  c7_info[32].mFileTimeHi = 0U;
  c7_info[33].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c7_info[33].name = "eml_eps";
  c7_info[33].dominantType = "char";
  c7_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c7_info[33].fileTimeLo = 1326738796U;
  c7_info[33].fileTimeHi = 0U;
  c7_info[33].mFileTimeLo = 0U;
  c7_info[33].mFileTimeHi = 0U;
  c7_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c7_info[34].name = "eml_float_model";
  c7_info[34].dominantType = "char";
  c7_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c7_info[34].fileTimeLo = 1326738796U;
  c7_info[34].fileTimeHi = 0U;
  c7_info[34].mFileTimeLo = 0U;
  c7_info[34].mFileTimeHi = 0U;
  c7_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c7_info[35].name = "eml_flt2str";
  c7_info[35].dominantType = "double";
  c7_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c7_info[35].fileTimeLo = 1309469196U;
  c7_info[35].fileTimeHi = 0U;
  c7_info[35].mFileTimeLo = 0U;
  c7_info[35].mFileTimeHi = 0U;
  c7_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c7_info[36].name = "char";
  c7_info[36].dominantType = "double";
  c7_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m";
  c7_info[36].fileTimeLo = 1319744368U;
  c7_info[36].fileTimeHi = 0U;
  c7_info[36].mFileTimeLo = 0U;
  c7_info[36].mFileTimeHi = 0U;
  c7_info[37].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c7_info[37].name = "eml_index_class";
  c7_info[37].dominantType = "";
  c7_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c7_info[37].fileTimeLo = 1323181378U;
  c7_info[37].fileTimeHi = 0U;
  c7_info[37].mFileTimeLo = 0U;
  c7_info[37].mFileTimeHi = 0U;
  c7_info[38].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c7_info[38].name = "eml_scalar_eg";
  c7_info[38].dominantType = "double";
  c7_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c7_info[38].fileTimeLo = 1286836796U;
  c7_info[38].fileTimeHi = 0U;
  c7_info[38].mFileTimeLo = 0U;
  c7_info[38].mFileTimeHi = 0U;
  c7_info[39].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c7_info[39].name = "eml_xgemm";
  c7_info[39].dominantType = "char";
  c7_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c7_info[39].fileTimeLo = 1299091172U;
  c7_info[39].fileTimeHi = 0U;
  c7_info[39].mFileTimeLo = 0U;
  c7_info[39].mFileTimeHi = 0U;
  c7_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c7_info[40].name = "eml_blas_inline";
  c7_info[40].dominantType = "";
  c7_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c7_info[40].fileTimeLo = 1299091168U;
  c7_info[40].fileTimeHi = 0U;
  c7_info[40].mFileTimeLo = 0U;
  c7_info[40].mFileTimeHi = 0U;
  c7_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c7_info[41].name = "mtimes";
  c7_info[41].dominantType = "double";
  c7_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c7_info[41].fileTimeLo = 1289530492U;
  c7_info[41].fileTimeHi = 0U;
  c7_info[41].mFileTimeLo = 0U;
  c7_info[41].mFileTimeHi = 0U;
  c7_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c7_info[42].name = "eml_index_class";
  c7_info[42].dominantType = "";
  c7_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c7_info[42].fileTimeLo = 1323181378U;
  c7_info[42].fileTimeHi = 0U;
  c7_info[42].mFileTimeLo = 0U;
  c7_info[42].mFileTimeHi = 0U;
  c7_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c7_info[43].name = "eml_scalar_eg";
  c7_info[43].dominantType = "double";
  c7_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c7_info[43].fileTimeLo = 1286836796U;
  c7_info[43].fileTimeHi = 0U;
  c7_info[43].mFileTimeLo = 0U;
  c7_info[43].mFileTimeHi = 0U;
  c7_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c7_info[44].name = "eml_refblas_xgemm";
  c7_info[44].dominantType = "char";
  c7_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c7_info[44].fileTimeLo = 1299091174U;
  c7_info[44].fileTimeHi = 0U;
  c7_info[44].mFileTimeLo = 0U;
  c7_info[44].mFileTimeHi = 0U;
}

static void c7_diag(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
                    *chartInstance, real_T c7_v[3], real_T c7_d[9])
{
  int32_T c7_i49;
  int32_T c7_j;
  int32_T c7_b_j;
  int32_T c7_a;
  int32_T c7_c;
  for (c7_i49 = 0; c7_i49 < 9; c7_i49++) {
    c7_d[c7_i49] = 0.0;
  }

  for (c7_j = 1; c7_j < 4; c7_j++) {
    c7_b_j = c7_j;
    c7_a = c7_b_j;
    c7_c = c7_a;
    c7_d[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c7_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c7_c), 1, 3, 2, 0) - 1)) - 1]
      = c7_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c7_b_j), 1, 3, 1, 0) - 1];
  }
}

static void c7_inv(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
                   *chartInstance, real_T c7_x[9], real_T c7_y[9])
{
  int32_T c7_i50;
  real_T c7_b_x[9];
  int32_T c7_i51;
  real_T c7_c_x[9];
  real_T c7_n1x;
  int32_T c7_i52;
  real_T c7_b_y[9];
  real_T c7_n1xinv;
  real_T c7_a;
  real_T c7_b;
  real_T c7_c_y;
  real_T c7_rc;
  real_T c7_d_x;
  boolean_T c7_b_b;
  real_T c7_e_x;
  int32_T c7_i53;
  static char_T c7_cv0[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  char_T c7_u[8];
  const mxArray *c7_d_y = NULL;
  real_T c7_b_u;
  const mxArray *c7_e_y = NULL;
  real_T c7_c_u;
  const mxArray *c7_f_y = NULL;
  real_T c7_d_u;
  const mxArray *c7_g_y = NULL;
  char_T c7_str[14];
  int32_T c7_i54;
  char_T c7_b_str[14];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  for (c7_i50 = 0; c7_i50 < 9; c7_i50++) {
    c7_b_x[c7_i50] = c7_x[c7_i50];
  }

  c7_inv3x3(chartInstance, c7_b_x, c7_y);
  for (c7_i51 = 0; c7_i51 < 9; c7_i51++) {
    c7_c_x[c7_i51] = c7_x[c7_i51];
  }

  c7_n1x = c7_norm(chartInstance, c7_c_x);
  for (c7_i52 = 0; c7_i52 < 9; c7_i52++) {
    c7_b_y[c7_i52] = c7_y[c7_i52];
  }

  c7_n1xinv = c7_norm(chartInstance, c7_b_y);
  c7_a = c7_n1x;
  c7_b = c7_n1xinv;
  c7_c_y = c7_a * c7_b;
  c7_rc = 1.0 / c7_c_y;
  guard1 = FALSE;
  guard2 = FALSE;
  if (c7_n1x == 0.0) {
    guard2 = TRUE;
  } else if (c7_n1xinv == 0.0) {
    guard2 = TRUE;
  } else if (c7_rc == 0.0) {
    guard1 = TRUE;
  } else {
    c7_d_x = c7_rc;
    c7_b_b = muDoubleScalarIsNaN(c7_d_x);
    guard3 = FALSE;
    if (c7_b_b) {
      guard3 = TRUE;
    } else {
      if (c7_rc < 2.2204460492503131E-16) {
        guard3 = TRUE;
      }
    }

    if (guard3 == TRUE) {
      c7_e_x = c7_rc;
      for (c7_i53 = 0; c7_i53 < 8; c7_i53++) {
        c7_u[c7_i53] = c7_cv0[c7_i53];
      }

      c7_d_y = NULL;
      sf_mex_assign(&c7_d_y, sf_mex_create("y", c7_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    FALSE);
      c7_b_u = 14.0;
      c7_e_y = NULL;
      sf_mex_assign(&c7_e_y, sf_mex_create("y", &c7_b_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c7_c_u = 6.0;
      c7_f_y = NULL;
      sf_mex_assign(&c7_f_y, sf_mex_create("y", &c7_c_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c7_d_u = c7_e_x;
      c7_g_y = NULL;
      sf_mex_assign(&c7_g_y, sf_mex_create("y", &c7_d_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c7_e_emlrt_marshallIn(chartInstance, sf_mex_call_debug("sprintf", 1U, 2U,
        14, sf_mex_call_debug("sprintf", 1U, 3U, 14, c7_d_y, 14, c7_e_y, 14,
        c7_f_y), 14, c7_g_y), "sprintf", c7_str);
      for (c7_i54 = 0; c7_i54 < 14; c7_i54++) {
        c7_b_str[c7_i54] = c7_str[c7_i54];
      }

      c7_b_eml_warning(chartInstance, c7_b_str);
    }
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c7_eml_warning(chartInstance);
  }
}

static void c7_inv3x3(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c7_x[9], real_T c7_y[9])
{
  int32_T c7_p1;
  int32_T c7_p2;
  int32_T c7_p3;
  real_T c7_b_x;
  real_T c7_c_x;
  real_T c7_absx11;
  real_T c7_d_x;
  real_T c7_e_x;
  real_T c7_absx21;
  real_T c7_f_x;
  real_T c7_g_x;
  real_T c7_absx31;
  real_T c7_t1;
  real_T c7_h_x;
  real_T c7_b_y;
  real_T c7_z;
  real_T c7_i_x;
  real_T c7_c_y;
  real_T c7_b_z;
  real_T c7_a;
  real_T c7_b;
  real_T c7_d_y;
  real_T c7_b_a;
  real_T c7_b_b;
  real_T c7_e_y;
  real_T c7_c_a;
  real_T c7_c_b;
  real_T c7_f_y;
  real_T c7_d_a;
  real_T c7_d_b;
  real_T c7_g_y;
  real_T c7_j_x;
  real_T c7_k_x;
  real_T c7_h_y;
  real_T c7_l_x;
  real_T c7_m_x;
  real_T c7_i_y;
  int32_T c7_itmp;
  real_T c7_n_x;
  real_T c7_j_y;
  real_T c7_c_z;
  real_T c7_e_a;
  real_T c7_e_b;
  real_T c7_k_y;
  real_T c7_f_a;
  real_T c7_f_b;
  real_T c7_l_y;
  real_T c7_o_x;
  real_T c7_m_y;
  real_T c7_t3;
  real_T c7_g_a;
  real_T c7_g_b;
  real_T c7_n_y;
  real_T c7_p_x;
  real_T c7_o_y;
  real_T c7_t2;
  int32_T c7_h_a;
  int32_T c7_c;
  real_T c7_i_a;
  real_T c7_h_b;
  real_T c7_p_y;
  real_T c7_j_a;
  real_T c7_i_b;
  real_T c7_q_y;
  real_T c7_q_x;
  real_T c7_r_y;
  real_T c7_d_z;
  int32_T c7_k_a;
  int32_T c7_b_c;
  int32_T c7_l_a;
  int32_T c7_c_c;
  real_T c7_r_x;
  real_T c7_s_y;
  real_T c7_m_a;
  real_T c7_j_b;
  real_T c7_t_y;
  real_T c7_s_x;
  real_T c7_u_y;
  int32_T c7_n_a;
  int32_T c7_d_c;
  real_T c7_o_a;
  real_T c7_k_b;
  real_T c7_v_y;
  real_T c7_p_a;
  real_T c7_l_b;
  real_T c7_w_y;
  real_T c7_t_x;
  real_T c7_x_y;
  real_T c7_e_z;
  int32_T c7_q_a;
  int32_T c7_e_c;
  int32_T c7_r_a;
  int32_T c7_f_c;
  real_T c7_y_y;
  real_T c7_s_a;
  real_T c7_m_b;
  real_T c7_ab_y;
  real_T c7_u_x;
  real_T c7_bb_y;
  int32_T c7_t_a;
  int32_T c7_g_c;
  real_T c7_u_a;
  real_T c7_n_b;
  real_T c7_cb_y;
  real_T c7_v_a;
  real_T c7_o_b;
  real_T c7_db_y;
  real_T c7_v_x;
  real_T c7_eb_y;
  real_T c7_f_z;
  int32_T c7_w_a;
  int32_T c7_h_c;
  int32_T c7_x_a;
  int32_T c7_i_c;
  boolean_T guard1 = FALSE;
  c7_p1 = 0;
  c7_p2 = 3;
  c7_p3 = 6;
  c7_b_x = c7_x[0];
  c7_c_x = c7_b_x;
  c7_absx11 = muDoubleScalarAbs(c7_c_x);
  c7_d_x = c7_x[1];
  c7_e_x = c7_d_x;
  c7_absx21 = muDoubleScalarAbs(c7_e_x);
  c7_f_x = c7_x[2];
  c7_g_x = c7_f_x;
  c7_absx31 = muDoubleScalarAbs(c7_g_x);
  guard1 = FALSE;
  if (c7_absx21 > c7_absx11) {
    if (c7_absx21 > c7_absx31) {
      c7_p1 = 3;
      c7_p2 = 0;
      c7_t1 = c7_x[0];
      c7_x[0] = c7_x[1];
      c7_x[1] = c7_t1;
      c7_t1 = c7_x[3];
      c7_x[3] = c7_x[4];
      c7_x[4] = c7_t1;
      c7_t1 = c7_x[6];
      c7_x[6] = c7_x[7];
      c7_x[7] = c7_t1;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    if (c7_absx31 > c7_absx11) {
      c7_p1 = 6;
      c7_p3 = 0;
      c7_t1 = c7_x[0];
      c7_x[0] = c7_x[2];
      c7_x[2] = c7_t1;
      c7_t1 = c7_x[3];
      c7_x[3] = c7_x[5];
      c7_x[5] = c7_t1;
      c7_t1 = c7_x[6];
      c7_x[6] = c7_x[8];
      c7_x[8] = c7_t1;
    }
  }

  c7_h_x = c7_x[1];
  c7_b_y = c7_x[0];
  c7_z = c7_h_x / c7_b_y;
  c7_x[1] = c7_z;
  c7_i_x = c7_x[2];
  c7_c_y = c7_x[0];
  c7_b_z = c7_i_x / c7_c_y;
  c7_x[2] = c7_b_z;
  c7_a = c7_x[1];
  c7_b = c7_x[3];
  c7_d_y = c7_a * c7_b;
  c7_x[4] -= c7_d_y;
  c7_b_a = c7_x[2];
  c7_b_b = c7_x[3];
  c7_e_y = c7_b_a * c7_b_b;
  c7_x[5] -= c7_e_y;
  c7_c_a = c7_x[1];
  c7_c_b = c7_x[6];
  c7_f_y = c7_c_a * c7_c_b;
  c7_x[7] -= c7_f_y;
  c7_d_a = c7_x[2];
  c7_d_b = c7_x[6];
  c7_g_y = c7_d_a * c7_d_b;
  c7_x[8] -= c7_g_y;
  c7_j_x = c7_x[5];
  c7_k_x = c7_j_x;
  c7_h_y = muDoubleScalarAbs(c7_k_x);
  c7_l_x = c7_x[4];
  c7_m_x = c7_l_x;
  c7_i_y = muDoubleScalarAbs(c7_m_x);
  if (c7_h_y > c7_i_y) {
    c7_itmp = c7_p2;
    c7_p2 = c7_p3;
    c7_p3 = c7_itmp;
    c7_t1 = c7_x[1];
    c7_x[1] = c7_x[2];
    c7_x[2] = c7_t1;
    c7_t1 = c7_x[4];
    c7_x[4] = c7_x[5];
    c7_x[5] = c7_t1;
    c7_t1 = c7_x[7];
    c7_x[7] = c7_x[8];
    c7_x[8] = c7_t1;
  }

  c7_n_x = c7_x[5];
  c7_j_y = c7_x[4];
  c7_c_z = c7_n_x / c7_j_y;
  c7_x[5] = c7_c_z;
  c7_e_a = c7_x[5];
  c7_e_b = c7_x[7];
  c7_k_y = c7_e_a * c7_e_b;
  c7_x[8] -= c7_k_y;
  c7_f_a = c7_x[5];
  c7_f_b = c7_x[1];
  c7_l_y = c7_f_a * c7_f_b;
  c7_o_x = c7_l_y - c7_x[2];
  c7_m_y = c7_x[8];
  c7_t3 = c7_o_x / c7_m_y;
  c7_g_a = c7_x[7];
  c7_g_b = c7_t3;
  c7_n_y = c7_g_a * c7_g_b;
  c7_p_x = -(c7_x[1] + c7_n_y);
  c7_o_y = c7_x[4];
  c7_t2 = c7_p_x / c7_o_y;
  c7_h_a = c7_p1 + 1;
  c7_c = c7_h_a;
  c7_i_a = c7_x[3];
  c7_h_b = c7_t2;
  c7_p_y = c7_i_a * c7_h_b;
  c7_j_a = c7_x[6];
  c7_i_b = c7_t3;
  c7_q_y = c7_j_a * c7_i_b;
  c7_q_x = (1.0 - c7_p_y) - c7_q_y;
  c7_r_y = c7_x[0];
  c7_d_z = c7_q_x / c7_r_y;
  c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c7_c), 1, 9, 1, 0) - 1] = c7_d_z;
  c7_k_a = c7_p1 + 2;
  c7_b_c = c7_k_a;
  c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c7_b_c), 1, 9, 1, 0) - 1] = c7_t2;
  c7_l_a = c7_p1 + 3;
  c7_c_c = c7_l_a;
  c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c7_c_c), 1, 9, 1, 0) - 1] = c7_t3;
  c7_r_x = -c7_x[5];
  c7_s_y = c7_x[8];
  c7_t3 = c7_r_x / c7_s_y;
  c7_m_a = c7_x[7];
  c7_j_b = c7_t3;
  c7_t_y = c7_m_a * c7_j_b;
  c7_s_x = 1.0 - c7_t_y;
  c7_u_y = c7_x[4];
  c7_t2 = c7_s_x / c7_u_y;
  c7_n_a = c7_p2 + 1;
  c7_d_c = c7_n_a;
  c7_o_a = c7_x[3];
  c7_k_b = c7_t2;
  c7_v_y = c7_o_a * c7_k_b;
  c7_p_a = c7_x[6];
  c7_l_b = c7_t3;
  c7_w_y = c7_p_a * c7_l_b;
  c7_t_x = -(c7_v_y + c7_w_y);
  c7_x_y = c7_x[0];
  c7_e_z = c7_t_x / c7_x_y;
  c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c7_d_c), 1, 9, 1, 0) - 1] = c7_e_z;
  c7_q_a = c7_p2 + 2;
  c7_e_c = c7_q_a;
  c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c7_e_c), 1, 9, 1, 0) - 1] = c7_t2;
  c7_r_a = c7_p2 + 3;
  c7_f_c = c7_r_a;
  c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c7_f_c), 1, 9, 1, 0) - 1] = c7_t3;
  c7_y_y = c7_x[8];
  c7_t3 = 1.0 / c7_y_y;
  c7_s_a = -c7_x[7];
  c7_m_b = c7_t3;
  c7_ab_y = c7_s_a * c7_m_b;
  c7_u_x = c7_ab_y;
  c7_bb_y = c7_x[4];
  c7_t2 = c7_u_x / c7_bb_y;
  c7_t_a = c7_p3 + 1;
  c7_g_c = c7_t_a;
  c7_u_a = c7_x[3];
  c7_n_b = c7_t2;
  c7_cb_y = c7_u_a * c7_n_b;
  c7_v_a = c7_x[6];
  c7_o_b = c7_t3;
  c7_db_y = c7_v_a * c7_o_b;
  c7_v_x = -(c7_cb_y + c7_db_y);
  c7_eb_y = c7_x[0];
  c7_f_z = c7_v_x / c7_eb_y;
  c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c7_g_c), 1, 9, 1, 0) - 1] = c7_f_z;
  c7_w_a = c7_p3 + 2;
  c7_h_c = c7_w_a;
  c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c7_h_c), 1, 9, 1, 0) - 1] = c7_t2;
  c7_x_a = c7_p3 + 3;
  c7_i_c = c7_x_a;
  c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c7_i_c), 1, 9, 1, 0) - 1] = c7_t3;
}

static real_T c7_norm(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c7_x[9])
{
  real_T c7_y;
  int32_T c7_j;
  real_T c7_b_j;
  real_T c7_s;
  int32_T c7_i;
  real_T c7_b_i;
  real_T c7_b_x;
  real_T c7_c_x;
  real_T c7_b_y;
  real_T c7_d_x;
  boolean_T c7_b;
  boolean_T exitg1;
  c7_y = 0.0;
  c7_j = 0;
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (c7_j < 3)) {
    c7_b_j = 1.0 + (real_T)c7_j;
    c7_s = 0.0;
    for (c7_i = 0; c7_i < 3; c7_i++) {
      c7_b_i = 1.0 + (real_T)c7_i;
      c7_b_x = c7_x[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c7_b_i), 1, 3, 1, 0) + 3 * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c7_b_j),
        1, 3, 2, 0) - 1)) - 1];
      c7_c_x = c7_b_x;
      c7_b_y = muDoubleScalarAbs(c7_c_x);
      c7_s += c7_b_y;
    }

    c7_d_x = c7_s;
    c7_b = muDoubleScalarIsNaN(c7_d_x);
    if (c7_b) {
      c7_y = rtNaN;
      exitg1 = TRUE;
    } else {
      if (c7_s > c7_y) {
        c7_y = c7_s;
      }

      c7_j++;
    }
  }

  return c7_y;
}

static void c7_eml_warning(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
  int32_T c7_i55;
  static char_T c7_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c7_u[27];
  const mxArray *c7_y = NULL;
  for (c7_i55 = 0; c7_i55 < 27; c7_i55++) {
    c7_u[c7_i55] = c7_varargin_1[c7_i55];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 10, 0U, 1U, 0U, 2, 1, 27), FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c7_y));
}

static void c7_b_eml_warning(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, char_T c7_varargin_2[14])
{
  int32_T c7_i56;
  static char_T c7_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c7_u[33];
  const mxArray *c7_y = NULL;
  int32_T c7_i57;
  char_T c7_b_u[14];
  const mxArray *c7_b_y = NULL;
  for (c7_i56 = 0; c7_i56 < 33; c7_i56++) {
    c7_u[c7_i56] = c7_varargin_1[c7_i56];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 10, 0U, 1U, 0U, 2, 1, 33), FALSE);
  for (c7_i57 = 0; c7_i57 < 14; c7_i57++) {
    c7_b_u[c7_i57] = c7_varargin_2[c7_i57];
  }

  c7_b_y = NULL;
  sf_mex_assign(&c7_b_y, sf_mex_create("y", c7_b_u, 10, 0U, 1U, 0U, 2, 1, 14),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
    14, c7_y, 14, c7_b_y));
}

static void c7_eml_scalar_eg(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c7_b_eml_scalar_eg(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c7_e_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_sprintf, const char_T *c7_identifier, char_T c7_y[14])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_sprintf), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_sprintf);
}

static void c7_f_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId, char_T c7_y[14])
{
  char_T c7_cv1[14];
  int32_T c7_i58;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_cv1, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c7_i58 = 0; c7_i58 < 14; c7_i58++) {
    c7_y[c7_i58] = c7_cv1[c7_i58];
  }

  sf_mex_destroy(&c7_u);
}

static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(int32_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static int32_T c7_g_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  int32_T c7_y;
  int32_T c7_i59;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_i59, 1, 6, 0U, 0, 0U, 0);
  c7_y = c7_i59;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_b_sfEvent;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  int32_T c7_y;
  SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c7_b_sfEvent = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_sfEvent),
    &c7_thisId);
  sf_mex_destroy(&c7_b_sfEvent);
  *(int32_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static uint8_T c7_h_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_b_is_active_c7_modelo_FK_simul_coleta_dados, const char_T *c7_identifier)
{
  uint8_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c7_b_is_active_c7_modelo_FK_simul_coleta_dados), &c7_thisId);
  sf_mex_destroy(&c7_b_is_active_c7_modelo_FK_simul_coleta_dados);
  return c7_y;
}

static uint8_T c7_i_emlrt_marshallIn
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint8_T c7_y;
  uint8_T c7_u0;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_u0, 1, 3, 0U, 0, 0U, 0);
  c7_y = c7_u0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void init_dsm_address_info
  (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
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

void sf_c7_modelo_FK_simul_coleta_dados_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(592820378U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2337282146U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3323011737U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2613818944U);
}

mxArray *sf_c7_modelo_FK_simul_coleta_dados_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("MsEQmWqqQd8xJ4XfbdzCkG");
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

mxArray *sf_c7_modelo_FK_simul_coleta_dados_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c7_modelo_FK_simul_coleta_dados(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"u_recuperado\",},{M[8],M[0],T\"is_active_c7_modelo_FK_simul_coleta_dados\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c7_modelo_FK_simul_coleta_dados_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
    chartInstance = (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modelo_FK_simul_coleta_dadosMachineNumber_,
           7,
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
          init_script_number_translation
            (_modelo_FK_simul_coleta_dadosMachineNumber_,
             chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,
             _modelo_FK_simul_coleta_dadosMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _modelo_FK_simul_coleta_dadosMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"ur");
          _SFD_SET_DATA_PROPS(1,2,0,1,"u_recuperado");
          _SFD_SET_DATA_PROPS(2,1,1,0,"vsh");
          _SFD_SET_DATA_PROPS(3,1,1,0,"vah");
          _SFD_SET_DATA_PROPS(4,1,1,0,"voh");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,299);
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
            1.0,0,0,(MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)
            c7_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c7_ur)[3];
          real_T (*c7_u_recuperado)[3];
          real_T (*c7_vsh)[3];
          real_T (*c7_vah)[3];
          real_T (*c7_voh)[3];
          c7_voh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c7_vah = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c7_vsh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c7_u_recuperado = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c7_ur = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c7_ur);
          _SFD_SET_DATA_VALUE_PTR(1U, *c7_u_recuperado);
          _SFD_SET_DATA_VALUE_PTR(2U, *c7_vsh);
          _SFD_SET_DATA_VALUE_PTR(3U, *c7_vah);
          _SFD_SET_DATA_VALUE_PTR(4U, *c7_voh);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _modelo_FK_simul_coleta_dadosMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "I2djRvfs42haF39lbGcrKE";
}

static void sf_opaque_initialize_c7_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c7_modelo_FK_simul_coleta_dados
    ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
  initialize_c7_modelo_FK_simul_coleta_dados
    ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c7_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  enable_c7_modelo_FK_simul_coleta_dados
    ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c7_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  disable_c7_modelo_FK_simul_coleta_dados
    ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c7_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  sf_c7_modelo_FK_simul_coleta_dados
    ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c7_modelo_FK_simul_coleta_dados
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c7_modelo_FK_simul_coleta_dados
    ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c7_modelo_FK_simul_coleta_dados();/* state var info */
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

extern void sf_internal_set_sim_state_c7_modelo_FK_simul_coleta_dados(SimStruct*
  S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c7_modelo_FK_simul_coleta_dados();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c7_modelo_FK_simul_coleta_dados
    ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c7_modelo_FK_simul_coleta_dados
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c7_modelo_FK_simul_coleta_dados(S);
}

static void sf_opaque_set_sim_state_c7_modelo_FK_simul_coleta_dados(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c7_modelo_FK_simul_coleta_dados(S, st);
}

static void sf_opaque_terminate_c7_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_FK_simul_coleta_dados_optimization_info();
    }

    finalize_c7_modelo_FK_simul_coleta_dados
      ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc7_modelo_FK_simul_coleta_dados
    ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c7_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c7_modelo_FK_simul_coleta_dados
      ((SFc7_modelo_FK_simul_coleta_dadosInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c7_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_modelo_FK_simul_coleta_dados_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      7);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,7,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,7,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,7);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,7,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,7,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,7);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3593500727U));
  ssSetChecksum1(S,(714037860U));
  ssSetChecksum2(S,(4231058730U));
  ssSetChecksum3(S,(976238721U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c7_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c7_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct *)utMalloc
    (sizeof(SFc7_modelo_FK_simul_coleta_dadosInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc7_modelo_FK_simul_coleta_dadosInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c7_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c7_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c7_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c7_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c7_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c7_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c7_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c7_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c7_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.mdlStart = mdlStart_c7_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c7_modelo_FK_simul_coleta_dados;
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

void c7_modelo_FK_simul_coleta_dados_method_dispatcher(SimStruct *S, int_T
  method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c7_modelo_FK_simul_coleta_dados(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c7_modelo_FK_simul_coleta_dados(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c7_modelo_FK_simul_coleta_dados(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c7_modelo_FK_simul_coleta_dados_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
