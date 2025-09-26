/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_FK_simul_coleta_dados_sfun.h"
#include "c8_modelo_FK_simul_coleta_dados.h"
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
static const char * c8_debug_family_names[12] = { "rho", "phi", "lambda",
  "T_inv", "S_inv", "nargin", "nargout", "ur", "vsh", "vah", "voh",
  "u_recuperado" };

/* Function Declarations */
static void initialize_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void initialize_params_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void enable_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void disable_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c8_update_debugger_state_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void set_sim_state_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_st);
static void finalize_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void sf_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c8_chartstep_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void initSimStructsc8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void registerMessagesc8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static void c8_emlrt_marshallIn(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *
  chartInstance, const mxArray *c8_u_recuperado, const char_T *c8_identifier,
  real_T c8_y[3]);
static void c8_b_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId, real_T c8_y[3]);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static real_T c8_c_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static void c8_d_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId, real_T c8_y[9]);
static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[45]);
static void c8_diag(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
                    *chartInstance, real_T c8_v[3], real_T c8_d[9]);
static void c8_inv(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
                   *chartInstance, real_T c8_x[9], real_T c8_y[9]);
static void c8_inv3x3(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c8_x[9], real_T c8_y[9]);
static real_T c8_norm(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c8_x[9]);
static void c8_eml_warning(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c8_b_eml_warning(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, char_T c8_varargin_2[14]);
static void c8_eml_scalar_eg(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c8_b_eml_scalar_eg(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c8_e_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_sprintf, const char_T *c8_identifier, char_T c8_y[14]);
static void c8_f_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId, char_T c8_y[14]);
static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_g_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static uint8_T c8_h_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_b_is_active_c8_modelo_FK_simul_coleta_dados, const char_T *c8_identifier);
static uint8_T c8_i_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void init_dsm_address_info
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  chartInstance->c8_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c8_is_active_c8_modelo_FK_simul_coleta_dados = 0U;
}

static void initialize_params_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void enable_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c8_update_debugger_state_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  const mxArray *c8_st;
  const mxArray *c8_y = NULL;
  int32_T c8_i0;
  real_T c8_u[3];
  const mxArray *c8_b_y = NULL;
  uint8_T c8_hoistedGlobal;
  uint8_T c8_b_u;
  const mxArray *c8_c_y = NULL;
  real_T (*c8_u_recuperado)[3];
  c8_u_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellarray(2), FALSE);
  for (c8_i0 = 0; c8_i0 < 3; c8_i0++) {
    c8_u[c8_i0] = (*c8_u_recuperado)[c8_i0];
  }

  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c8_y, 0, c8_b_y);
  c8_hoistedGlobal = chartInstance->c8_is_active_c8_modelo_FK_simul_coleta_dados;
  c8_b_u = c8_hoistedGlobal;
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 1, c8_c_y);
  sf_mex_assign(&c8_st, c8_y, FALSE);
  return c8_st;
}

static void set_sim_state_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_st)
{
  const mxArray *c8_u;
  real_T c8_dv0[3];
  int32_T c8_i1;
  real_T (*c8_u_recuperado)[3];
  c8_u_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c8_doneDoubleBufferReInit = TRUE;
  c8_u = sf_mex_dup(c8_st);
  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 0)),
                      "u_recuperado", c8_dv0);
  for (c8_i1 = 0; c8_i1 < 3; c8_i1++) {
    (*c8_u_recuperado)[c8_i1] = c8_dv0[c8_i1];
  }

  chartInstance->c8_is_active_c8_modelo_FK_simul_coleta_dados =
    c8_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 1)),
    "is_active_c8_modelo_FK_simul_coleta_dados");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_modelo_FK_simul_coleta_dados(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void sf_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  int32_T c8_i2;
  int32_T c8_i3;
  int32_T c8_i4;
  int32_T c8_i5;
  int32_T c8_i6;
  real_T (*c8_voh)[3];
  real_T (*c8_vah)[3];
  real_T (*c8_vsh)[3];
  real_T (*c8_u_recuperado)[3];
  real_T (*c8_ur)[3];
  c8_voh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c8_vah = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c8_vsh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c8_u_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_ur = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  for (c8_i2 = 0; c8_i2 < 3; c8_i2++) {
    _SFD_DATA_RANGE_CHECK((*c8_ur)[c8_i2], 0U);
  }

  for (c8_i3 = 0; c8_i3 < 3; c8_i3++) {
    _SFD_DATA_RANGE_CHECK((*c8_u_recuperado)[c8_i3], 1U);
  }

  for (c8_i4 = 0; c8_i4 < 3; c8_i4++) {
    _SFD_DATA_RANGE_CHECK((*c8_vsh)[c8_i4], 2U);
  }

  for (c8_i5 = 0; c8_i5 < 3; c8_i5++) {
    _SFD_DATA_RANGE_CHECK((*c8_vah)[c8_i5], 3U);
  }

  for (c8_i6 = 0; c8_i6 < 3; c8_i6++) {
    _SFD_DATA_RANGE_CHECK((*c8_voh)[c8_i6], 4U);
  }

  chartInstance->c8_sfEvent = CALL_EVENT;
  c8_chartstep_c8_modelo_FK_simul_coleta_dados(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_modelo_FK_simul_coleta_dadosMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c8_chartstep_c8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  int32_T c8_i7;
  real_T c8_ur[3];
  int32_T c8_i8;
  real_T c8_vsh[3];
  int32_T c8_i9;
  real_T c8_vah[3];
  int32_T c8_i10;
  real_T c8_voh[3];
  uint32_T c8_debug_family_var_map[12];
  real_T c8_rho;
  real_T c8_phi;
  real_T c8_lambda;
  real_T c8_T_inv[9];
  real_T c8_S_inv[9];
  real_T c8_nargin = 4.0;
  real_T c8_nargout = 1.0;
  real_T c8_u_recuperado[3];
  real_T c8_x;
  real_T c8_b_x;
  real_T c8_c_x;
  real_T c8_d_x;
  real_T c8_B;
  real_T c8_y;
  real_T c8_b_y;
  real_T c8_c_y;
  real_T c8_e_x;
  real_T c8_f_x;
  real_T c8_g_x;
  real_T c8_h_x;
  real_T c8_a;
  real_T c8_b;
  real_T c8_d_y;
  real_T c8_i_x;
  real_T c8_j_x;
  real_T c8_k_x;
  real_T c8_l_x;
  real_T c8_m_x;
  real_T c8_n_x;
  real_T c8_A;
  real_T c8_b_B;
  real_T c8_o_x;
  real_T c8_e_y;
  real_T c8_p_x;
  real_T c8_f_y;
  real_T c8_g_y;
  real_T c8_q_x;
  real_T c8_r_x;
  real_T c8_s_x;
  real_T c8_t_x;
  real_T c8_b_a;
  real_T c8_b_b;
  real_T c8_h_y;
  real_T c8_c_B;
  real_T c8_i_y;
  real_T c8_j_y;
  real_T c8_k_y;
  int32_T c8_i11;
  int32_T c8_i12;
  static real_T c8_dv1[3] = { 1.0, 0.0, 0.0 };

  int32_T c8_i13;
  real_T c8_b_vsh[3];
  real_T c8_c_a[9];
  int32_T c8_i14;
  real_T c8_d_a[9];
  real_T c8_dv2[9];
  int32_T c8_i15;
  int32_T c8_i16;
  int32_T c8_i17;
  real_T c8_c_b[9];
  int32_T c8_i18;
  int32_T c8_i19;
  int32_T c8_i20;
  real_T c8_l_y[9];
  int32_T c8_i21;
  int32_T c8_i22;
  int32_T c8_i23;
  real_T c8_d_b[3];
  int32_T c8_i24;
  int32_T c8_i25;
  int32_T c8_i26;
  real_T c8_C[3];
  int32_T c8_i27;
  int32_T c8_i28;
  int32_T c8_i29;
  int32_T c8_i30;
  int32_T c8_i31;
  int32_T c8_i32;
  int32_T c8_i33;
  real_T (*c8_b_u_recuperado)[3];
  real_T (*c8_b_voh)[3];
  real_T (*c8_b_vah)[3];
  real_T (*c8_c_vsh)[3];
  real_T (*c8_b_ur)[3];
  c8_b_voh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c8_b_vah = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c8_c_vsh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c8_b_u_recuperado = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_b_ur = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  for (c8_i7 = 0; c8_i7 < 3; c8_i7++) {
    c8_ur[c8_i7] = (*c8_b_ur)[c8_i7];
  }

  for (c8_i8 = 0; c8_i8 < 3; c8_i8++) {
    c8_vsh[c8_i8] = (*c8_c_vsh)[c8_i8];
  }

  for (c8_i9 = 0; c8_i9 < 3; c8_i9++) {
    c8_vah[c8_i9] = (*c8_b_vah)[c8_i9];
  }

  for (c8_i10 = 0; c8_i10 < 3; c8_i10++) {
    c8_voh[c8_i10] = (*c8_b_voh)[c8_i10];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c8_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_rho, 0U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_phi, 1U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_lambda, 2U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_T_inv, 3U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_S_inv, 4U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 5U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 6U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_ur, 7U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_vsh, 8U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_vah, 9U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_voh, 10U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_u_recuperado, 11U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 4);
  c8_rho = c8_vah[0];
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 5);
  c8_phi = c8_vah[1];
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 6);
  c8_lambda = c8_vah[2];
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 8);
  c8_x = c8_rho;
  c8_b_x = c8_x;
  c8_b_x = muDoubleScalarTan(c8_b_x);
  c8_c_x = c8_rho;
  c8_d_x = c8_c_x;
  c8_d_x = muDoubleScalarCos(c8_d_x);
  c8_B = c8_d_x;
  c8_y = c8_B;
  c8_b_y = c8_y;
  c8_c_y = 1.0 / c8_b_y;
  c8_e_x = c8_rho;
  c8_f_x = c8_e_x;
  c8_f_x = muDoubleScalarTan(c8_f_x);
  c8_g_x = c8_lambda;
  c8_h_x = c8_g_x;
  c8_h_x = muDoubleScalarTan(c8_h_x);
  c8_a = c8_f_x;
  c8_b = c8_h_x;
  c8_d_y = c8_a * c8_b;
  c8_i_x = c8_phi;
  c8_j_x = c8_i_x;
  c8_j_x = muDoubleScalarTan(c8_j_x);
  c8_k_x = c8_lambda;
  c8_l_x = c8_k_x;
  c8_l_x = muDoubleScalarTan(c8_l_x);
  c8_m_x = c8_rho;
  c8_n_x = c8_m_x;
  c8_n_x = muDoubleScalarCos(c8_n_x);
  c8_A = -c8_l_x;
  c8_b_B = c8_n_x;
  c8_o_x = c8_A;
  c8_e_y = c8_b_B;
  c8_p_x = c8_o_x;
  c8_f_y = c8_e_y;
  c8_g_y = c8_p_x / c8_f_y;
  c8_q_x = c8_lambda;
  c8_r_x = c8_q_x;
  c8_r_x = muDoubleScalarCos(c8_r_x);
  c8_s_x = c8_phi;
  c8_t_x = c8_s_x;
  c8_t_x = muDoubleScalarCos(c8_t_x);
  c8_b_a = c8_r_x;
  c8_b_b = c8_t_x;
  c8_h_y = c8_b_a * c8_b_b;
  c8_c_B = c8_h_y;
  c8_i_y = c8_c_B;
  c8_j_y = c8_i_y;
  c8_k_y = 1.0 / c8_j_y;
  c8_i11 = 0;
  for (c8_i12 = 0; c8_i12 < 3; c8_i12++) {
    c8_T_inv[c8_i11] = c8_dv1[c8_i12];
    c8_i11 += 3;
  }

  c8_T_inv[1] = -c8_b_x;
  c8_T_inv[4] = c8_c_y;
  c8_T_inv[7] = 0.0;
  c8_T_inv[2] = c8_d_y - c8_j_x;
  c8_T_inv[5] = c8_g_y;
  c8_T_inv[8] = c8_k_y;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 10);
  for (c8_i13 = 0; c8_i13 < 3; c8_i13++) {
    c8_b_vsh[c8_i13] = c8_vsh[c8_i13];
  }

  c8_diag(chartInstance, c8_b_vsh, c8_c_a);
  for (c8_i14 = 0; c8_i14 < 9; c8_i14++) {
    c8_d_a[c8_i14] = c8_c_a[c8_i14];
  }

  c8_inv(chartInstance, c8_d_a, c8_dv2);
  for (c8_i15 = 0; c8_i15 < 9; c8_i15++) {
    c8_S_inv[c8_i15] = c8_dv2[c8_i15];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 12);
  for (c8_i16 = 0; c8_i16 < 9; c8_i16++) {
    c8_c_a[c8_i16] = c8_T_inv[c8_i16];
  }

  for (c8_i17 = 0; c8_i17 < 9; c8_i17++) {
    c8_c_b[c8_i17] = c8_S_inv[c8_i17];
  }

  c8_eml_scalar_eg(chartInstance);
  c8_eml_scalar_eg(chartInstance);
  for (c8_i18 = 0; c8_i18 < 3; c8_i18++) {
    c8_i19 = 0;
    for (c8_i20 = 0; c8_i20 < 3; c8_i20++) {
      c8_l_y[c8_i19 + c8_i18] = 0.0;
      c8_i21 = 0;
      for (c8_i22 = 0; c8_i22 < 3; c8_i22++) {
        c8_l_y[c8_i19 + c8_i18] += c8_c_a[c8_i21 + c8_i18] * c8_c_b[c8_i22 +
          c8_i19];
        c8_i21 += 3;
      }

      c8_i19 += 3;
    }
  }

  for (c8_i23 = 0; c8_i23 < 3; c8_i23++) {
    c8_d_b[c8_i23] = c8_ur[c8_i23] - c8_voh[c8_i23];
  }

  c8_b_eml_scalar_eg(chartInstance);
  c8_b_eml_scalar_eg(chartInstance);
  for (c8_i24 = 0; c8_i24 < 3; c8_i24++) {
    c8_u_recuperado[c8_i24] = 0.0;
  }

  for (c8_i25 = 0; c8_i25 < 3; c8_i25++) {
    c8_u_recuperado[c8_i25] = 0.0;
  }

  for (c8_i26 = 0; c8_i26 < 3; c8_i26++) {
    c8_C[c8_i26] = c8_u_recuperado[c8_i26];
  }

  for (c8_i27 = 0; c8_i27 < 3; c8_i27++) {
    c8_u_recuperado[c8_i27] = c8_C[c8_i27];
  }

  for (c8_i28 = 0; c8_i28 < 3; c8_i28++) {
    c8_C[c8_i28] = c8_u_recuperado[c8_i28];
  }

  for (c8_i29 = 0; c8_i29 < 3; c8_i29++) {
    c8_u_recuperado[c8_i29] = c8_C[c8_i29];
  }

  for (c8_i30 = 0; c8_i30 < 3; c8_i30++) {
    c8_u_recuperado[c8_i30] = 0.0;
    c8_i31 = 0;
    for (c8_i32 = 0; c8_i32 < 3; c8_i32++) {
      c8_u_recuperado[c8_i30] += c8_l_y[c8_i31 + c8_i30] * c8_d_b[c8_i32];
      c8_i31 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, -12);
  _SFD_SYMBOL_SCOPE_POP();
  for (c8_i33 = 0; c8_i33 < 3; c8_i33++) {
    (*c8_b_u_recuperado)[c8_i33] = c8_u_recuperado[c8_i33];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
}

static void initSimStructsc8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void registerMessagesc8_modelo_FK_simul_coleta_dados
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber)
{
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i34;
  real_T c8_b_inData[3];
  int32_T c8_i35;
  real_T c8_u[3];
  const mxArray *c8_y = NULL;
  SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i34 = 0; c8_i34 < 3; c8_i34++) {
    c8_b_inData[c8_i34] = (*(real_T (*)[3])c8_inData)[c8_i34];
  }

  for (c8_i35 = 0; c8_i35 < 3; c8_i35++) {
    c8_u[c8_i35] = c8_b_inData[c8_i35];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static void c8_emlrt_marshallIn(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *
  chartInstance, const mxArray *c8_u_recuperado, const char_T *c8_identifier,
  real_T c8_y[3])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_u_recuperado), &c8_thisId,
                        c8_y);
  sf_mex_destroy(&c8_u_recuperado);
}

static void c8_b_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId, real_T c8_y[3])
{
  real_T c8_dv3[3];
  int32_T c8_i36;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c8_i36 = 0; c8_i36 < 3; c8_i36++) {
    c8_y[c8_i36] = c8_dv3[c8_i36];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_u_recuperado;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[3];
  int32_T c8_i37;
  SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c8_u_recuperado = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_u_recuperado), &c8_thisId,
                        c8_y);
  sf_mex_destroy(&c8_u_recuperado);
  for (c8_i37 = 0; c8_i37 < 3; c8_i37++) {
    (*(real_T (*)[3])c8_outData)[c8_i37] = c8_y[c8_i37];
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static real_T c8_c_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_d0, 1, 0, 0U, 0, 0U, 0);
  c8_y = c8_d0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_nargout;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y;
  SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c8_nargout = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_nargout), &c8_thisId);
  sf_mex_destroy(&c8_nargout);
  *(real_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i38;
  int32_T c8_i39;
  int32_T c8_i40;
  real_T c8_b_inData[9];
  int32_T c8_i41;
  int32_T c8_i42;
  int32_T c8_i43;
  real_T c8_u[9];
  const mxArray *c8_y = NULL;
  SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_i38 = 0;
  for (c8_i39 = 0; c8_i39 < 3; c8_i39++) {
    for (c8_i40 = 0; c8_i40 < 3; c8_i40++) {
      c8_b_inData[c8_i40 + c8_i38] = (*(real_T (*)[9])c8_inData)[c8_i40 + c8_i38];
    }

    c8_i38 += 3;
  }

  c8_i41 = 0;
  for (c8_i42 = 0; c8_i42 < 3; c8_i42++) {
    for (c8_i43 = 0; c8_i43 < 3; c8_i43++) {
      c8_u[c8_i43 + c8_i41] = c8_b_inData[c8_i43 + c8_i41];
    }

    c8_i41 += 3;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static void c8_d_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId, real_T c8_y[9])
{
  real_T c8_dv4[9];
  int32_T c8_i44;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv4, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c8_i44 = 0; c8_i44 < 9; c8_i44++) {
    c8_y[c8_i44] = c8_dv4[c8_i44];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_S_inv;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[9];
  int32_T c8_i45;
  int32_T c8_i46;
  int32_T c8_i47;
  SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c8_S_inv = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_S_inv), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_S_inv);
  c8_i45 = 0;
  for (c8_i46 = 0; c8_i46 < 3; c8_i46++) {
    for (c8_i47 = 0; c8_i47 < 3; c8_i47++) {
      (*(real_T (*)[9])c8_outData)[c8_i47 + c8_i45] = c8_y[c8_i47 + c8_i45];
    }

    c8_i45 += 3;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

const mxArray
  *sf_c8_modelo_FK_simul_coleta_dados_get_eml_resolved_functions_info(void)
{
  const mxArray *c8_nameCaptureInfo;
  c8_ResolvedFunctionInfo c8_info[45];
  const mxArray *c8_m0 = NULL;
  int32_T c8_i48;
  c8_ResolvedFunctionInfo *c8_r0;
  c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  c8_info_helper(c8_info);
  sf_mex_assign(&c8_m0, sf_mex_createstruct("nameCaptureInfo", 1, 45), FALSE);
  for (c8_i48 = 0; c8_i48 < 45; c8_i48++) {
    c8_r0 = &c8_info[c8_i48];
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->context)), "context", "nameCaptureInfo",
                    c8_i48);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c8_r0->name)), "name", "nameCaptureInfo", c8_i48);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c8_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c8_i48);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->resolved)), "resolved", "nameCaptureInfo",
                    c8_i48);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c8_i48);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c8_i48);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c8_i48);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c8_i48);
  }

  sf_mex_assign(&c8_nameCaptureInfo, c8_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c8_nameCaptureInfo);
  return c8_nameCaptureInfo;
}

static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[45])
{
  c8_info[0].context = "";
  c8_info[0].name = "tan";
  c8_info[0].dominantType = "double";
  c8_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/tan.m";
  c8_info[0].fileTimeLo = 1343848386U;
  c8_info[0].fileTimeHi = 0U;
  c8_info[0].mFileTimeLo = 0U;
  c8_info[0].mFileTimeHi = 0U;
  c8_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/tan.m";
  c8_info[1].name = "eml_scalar_tan";
  c8_info[1].dominantType = "double";
  c8_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_tan.m";
  c8_info[1].fileTimeLo = 1286836738U;
  c8_info[1].fileTimeHi = 0U;
  c8_info[1].mFileTimeLo = 0U;
  c8_info[1].mFileTimeHi = 0U;
  c8_info[2].context = "";
  c8_info[2].name = "cos";
  c8_info[2].dominantType = "double";
  c8_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c8_info[2].fileTimeLo = 1343848372U;
  c8_info[2].fileTimeHi = 0U;
  c8_info[2].mFileTimeLo = 0U;
  c8_info[2].mFileTimeHi = 0U;
  c8_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c8_info[3].name = "eml_scalar_cos";
  c8_info[3].dominantType = "double";
  c8_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c8_info[3].fileTimeLo = 1286836722U;
  c8_info[3].fileTimeHi = 0U;
  c8_info[3].mFileTimeLo = 0U;
  c8_info[3].mFileTimeHi = 0U;
  c8_info[4].context = "";
  c8_info[4].name = "mrdivide";
  c8_info[4].dominantType = "double";
  c8_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c8_info[4].fileTimeLo = 1357962348U;
  c8_info[4].fileTimeHi = 0U;
  c8_info[4].mFileTimeLo = 1319744366U;
  c8_info[4].mFileTimeHi = 0U;
  c8_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c8_info[5].name = "rdivide";
  c8_info[5].dominantType = "double";
  c8_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c8_info[5].fileTimeLo = 1346528388U;
  c8_info[5].fileTimeHi = 0U;
  c8_info[5].mFileTimeLo = 0U;
  c8_info[5].mFileTimeHi = 0U;
  c8_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c8_info[6].name = "eml_scalexp_compatible";
  c8_info[6].dominantType = "double";
  c8_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c8_info[6].fileTimeLo = 1286836796U;
  c8_info[6].fileTimeHi = 0U;
  c8_info[6].mFileTimeLo = 0U;
  c8_info[6].mFileTimeHi = 0U;
  c8_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c8_info[7].name = "eml_div";
  c8_info[7].dominantType = "double";
  c8_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c8_info[7].fileTimeLo = 1313365810U;
  c8_info[7].fileTimeHi = 0U;
  c8_info[7].mFileTimeLo = 0U;
  c8_info[7].mFileTimeHi = 0U;
  c8_info[8].context = "";
  c8_info[8].name = "mtimes";
  c8_info[8].dominantType = "double";
  c8_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[8].fileTimeLo = 1289530492U;
  c8_info[8].fileTimeHi = 0U;
  c8_info[8].mFileTimeLo = 0U;
  c8_info[8].mFileTimeHi = 0U;
  c8_info[9].context = "";
  c8_info[9].name = "diag";
  c8_info[9].dominantType = "double";
  c8_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c8_info[9].fileTimeLo = 1286836686U;
  c8_info[9].fileTimeHi = 0U;
  c8_info[9].mFileTimeLo = 0U;
  c8_info[9].mFileTimeHi = 0U;
  c8_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c8_info[10].name = "eml_index_class";
  c8_info[10].dominantType = "";
  c8_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[10].fileTimeLo = 1323181378U;
  c8_info[10].fileTimeHi = 0U;
  c8_info[10].mFileTimeLo = 0U;
  c8_info[10].mFileTimeHi = 0U;
  c8_info[11].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c8_info[11].name = "eml_index_plus";
  c8_info[11].dominantType = "coder.internal.indexInt";
  c8_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c8_info[11].fileTimeLo = 1286836778U;
  c8_info[11].fileTimeHi = 0U;
  c8_info[11].mFileTimeLo = 0U;
  c8_info[11].mFileTimeHi = 0U;
  c8_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c8_info[12].name = "eml_index_class";
  c8_info[12].dominantType = "";
  c8_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[12].fileTimeLo = 1323181378U;
  c8_info[12].fileTimeHi = 0U;
  c8_info[12].mFileTimeLo = 0U;
  c8_info[12].mFileTimeHi = 0U;
  c8_info[13].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c8_info[13].name = "eml_scalar_eg";
  c8_info[13].dominantType = "double";
  c8_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[13].fileTimeLo = 1286836796U;
  c8_info[13].fileTimeHi = 0U;
  c8_info[13].mFileTimeLo = 0U;
  c8_info[13].mFileTimeHi = 0U;
  c8_info[14].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c8_info[14].name = "eml_int_forloop_overflow_check";
  c8_info[14].dominantType = "";
  c8_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c8_info[14].fileTimeLo = 1346528340U;
  c8_info[14].fileTimeHi = 0U;
  c8_info[14].mFileTimeLo = 0U;
  c8_info[14].mFileTimeHi = 0U;
  c8_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c8_info[15].name = "intmax";
  c8_info[15].dominantType = "char";
  c8_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c8_info[15].fileTimeLo = 1311273316U;
  c8_info[15].fileTimeHi = 0U;
  c8_info[15].mFileTimeLo = 0U;
  c8_info[15].mFileTimeHi = 0U;
  c8_info[16].context = "";
  c8_info[16].name = "inv";
  c8_info[16].dominantType = "double";
  c8_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c8_info[16].fileTimeLo = 1305336000U;
  c8_info[16].fileTimeHi = 0U;
  c8_info[16].mFileTimeLo = 0U;
  c8_info[16].mFileTimeHi = 0U;
  c8_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c8_info[17].name = "eml_index_class";
  c8_info[17].dominantType = "";
  c8_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[17].fileTimeLo = 1323181378U;
  c8_info[17].fileTimeHi = 0U;
  c8_info[17].mFileTimeLo = 0U;
  c8_info[17].mFileTimeHi = 0U;
  c8_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c8_info[18].name = "abs";
  c8_info[18].dominantType = "double";
  c8_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c8_info[18].fileTimeLo = 1343848366U;
  c8_info[18].fileTimeHi = 0U;
  c8_info[18].mFileTimeLo = 0U;
  c8_info[18].mFileTimeHi = 0U;
  c8_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c8_info[19].name = "eml_scalar_abs";
  c8_info[19].dominantType = "double";
  c8_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c8_info[19].fileTimeLo = 1286836712U;
  c8_info[19].fileTimeHi = 0U;
  c8_info[19].mFileTimeLo = 0U;
  c8_info[19].mFileTimeHi = 0U;
  c8_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c8_info[20].name = "eml_div";
  c8_info[20].dominantType = "double";
  c8_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c8_info[20].fileTimeLo = 1313365810U;
  c8_info[20].fileTimeHi = 0U;
  c8_info[20].mFileTimeLo = 0U;
  c8_info[20].mFileTimeHi = 0U;
  c8_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c8_info[21].name = "mtimes";
  c8_info[21].dominantType = "double";
  c8_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[21].fileTimeLo = 1289530492U;
  c8_info[21].fileTimeHi = 0U;
  c8_info[21].mFileTimeLo = 0U;
  c8_info[21].mFileTimeHi = 0U;
  c8_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c8_info[22].name = "eml_index_plus";
  c8_info[22].dominantType = "double";
  c8_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c8_info[22].fileTimeLo = 1286836778U;
  c8_info[22].fileTimeHi = 0U;
  c8_info[22].mFileTimeLo = 0U;
  c8_info[22].mFileTimeHi = 0U;
  c8_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c8_info[23].name = "norm";
  c8_info[23].dominantType = "double";
  c8_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c8_info[23].fileTimeLo = 1336540094U;
  c8_info[23].fileTimeHi = 0U;
  c8_info[23].mFileTimeLo = 0U;
  c8_info[23].mFileTimeHi = 0U;
  c8_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c8_info[24].name = "abs";
  c8_info[24].dominantType = "double";
  c8_info[24].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c8_info[24].fileTimeLo = 1343848366U;
  c8_info[24].fileTimeHi = 0U;
  c8_info[24].mFileTimeLo = 0U;
  c8_info[24].mFileTimeHi = 0U;
  c8_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c8_info[25].name = "isnan";
  c8_info[25].dominantType = "double";
  c8_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c8_info[25].fileTimeLo = 1286836760U;
  c8_info[25].fileTimeHi = 0U;
  c8_info[25].mFileTimeLo = 0U;
  c8_info[25].mFileTimeHi = 0U;
  c8_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c8_info[26].name = "eml_guarded_nan";
  c8_info[26].dominantType = "char";
  c8_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c8_info[26].fileTimeLo = 1286836776U;
  c8_info[26].fileTimeHi = 0U;
  c8_info[26].mFileTimeLo = 0U;
  c8_info[26].mFileTimeHi = 0U;
  c8_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c8_info[27].name = "eml_is_float_class";
  c8_info[27].dominantType = "char";
  c8_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c8_info[27].fileTimeLo = 1286836782U;
  c8_info[27].fileTimeHi = 0U;
  c8_info[27].mFileTimeLo = 0U;
  c8_info[27].mFileTimeHi = 0U;
  c8_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c8_info[28].name = "mtimes";
  c8_info[28].dominantType = "double";
  c8_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[28].fileTimeLo = 1289530492U;
  c8_info[28].fileTimeHi = 0U;
  c8_info[28].mFileTimeLo = 0U;
  c8_info[28].mFileTimeHi = 0U;
  c8_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c8_info[29].name = "eml_warning";
  c8_info[29].dominantType = "char";
  c8_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c8_info[29].fileTimeLo = 1286836802U;
  c8_info[29].fileTimeHi = 0U;
  c8_info[29].mFileTimeLo = 0U;
  c8_info[29].mFileTimeHi = 0U;
  c8_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c8_info[30].name = "isnan";
  c8_info[30].dominantType = "double";
  c8_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c8_info[30].fileTimeLo = 1286836760U;
  c8_info[30].fileTimeHi = 0U;
  c8_info[30].mFileTimeLo = 0U;
  c8_info[30].mFileTimeHi = 0U;
  c8_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c8_info[31].name = "eps";
  c8_info[31].dominantType = "char";
  c8_info[31].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c8_info[31].fileTimeLo = 1326738796U;
  c8_info[31].fileTimeHi = 0U;
  c8_info[31].mFileTimeLo = 0U;
  c8_info[31].mFileTimeHi = 0U;
  c8_info[32].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c8_info[32].name = "eml_is_float_class";
  c8_info[32].dominantType = "char";
  c8_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c8_info[32].fileTimeLo = 1286836782U;
  c8_info[32].fileTimeHi = 0U;
  c8_info[32].mFileTimeLo = 0U;
  c8_info[32].mFileTimeHi = 0U;
  c8_info[33].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c8_info[33].name = "eml_eps";
  c8_info[33].dominantType = "char";
  c8_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c8_info[33].fileTimeLo = 1326738796U;
  c8_info[33].fileTimeHi = 0U;
  c8_info[33].mFileTimeLo = 0U;
  c8_info[33].mFileTimeHi = 0U;
  c8_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c8_info[34].name = "eml_float_model";
  c8_info[34].dominantType = "char";
  c8_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c8_info[34].fileTimeLo = 1326738796U;
  c8_info[34].fileTimeHi = 0U;
  c8_info[34].mFileTimeLo = 0U;
  c8_info[34].mFileTimeHi = 0U;
  c8_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c8_info[35].name = "eml_flt2str";
  c8_info[35].dominantType = "double";
  c8_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c8_info[35].fileTimeLo = 1309469196U;
  c8_info[35].fileTimeHi = 0U;
  c8_info[35].mFileTimeLo = 0U;
  c8_info[35].mFileTimeHi = 0U;
  c8_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c8_info[36].name = "char";
  c8_info[36].dominantType = "double";
  c8_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m";
  c8_info[36].fileTimeLo = 1319744368U;
  c8_info[36].fileTimeHi = 0U;
  c8_info[36].mFileTimeLo = 0U;
  c8_info[36].mFileTimeHi = 0U;
  c8_info[37].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[37].name = "eml_index_class";
  c8_info[37].dominantType = "";
  c8_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[37].fileTimeLo = 1323181378U;
  c8_info[37].fileTimeHi = 0U;
  c8_info[37].mFileTimeLo = 0U;
  c8_info[37].mFileTimeHi = 0U;
  c8_info[38].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[38].name = "eml_scalar_eg";
  c8_info[38].dominantType = "double";
  c8_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[38].fileTimeLo = 1286836796U;
  c8_info[38].fileTimeHi = 0U;
  c8_info[38].mFileTimeLo = 0U;
  c8_info[38].mFileTimeHi = 0U;
  c8_info[39].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[39].name = "eml_xgemm";
  c8_info[39].dominantType = "char";
  c8_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c8_info[39].fileTimeLo = 1299091172U;
  c8_info[39].fileTimeHi = 0U;
  c8_info[39].mFileTimeLo = 0U;
  c8_info[39].mFileTimeHi = 0U;
  c8_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c8_info[40].name = "eml_blas_inline";
  c8_info[40].dominantType = "";
  c8_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c8_info[40].fileTimeLo = 1299091168U;
  c8_info[40].fileTimeHi = 0U;
  c8_info[40].mFileTimeLo = 0U;
  c8_info[40].mFileTimeHi = 0U;
  c8_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c8_info[41].name = "mtimes";
  c8_info[41].dominantType = "double";
  c8_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[41].fileTimeLo = 1289530492U;
  c8_info[41].fileTimeHi = 0U;
  c8_info[41].mFileTimeLo = 0U;
  c8_info[41].mFileTimeHi = 0U;
  c8_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c8_info[42].name = "eml_index_class";
  c8_info[42].dominantType = "";
  c8_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[42].fileTimeLo = 1323181378U;
  c8_info[42].fileTimeHi = 0U;
  c8_info[42].mFileTimeLo = 0U;
  c8_info[42].mFileTimeHi = 0U;
  c8_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c8_info[43].name = "eml_scalar_eg";
  c8_info[43].dominantType = "double";
  c8_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[43].fileTimeLo = 1286836796U;
  c8_info[43].fileTimeHi = 0U;
  c8_info[43].mFileTimeLo = 0U;
  c8_info[43].mFileTimeHi = 0U;
  c8_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c8_info[44].name = "eml_refblas_xgemm";
  c8_info[44].dominantType = "char";
  c8_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c8_info[44].fileTimeLo = 1299091174U;
  c8_info[44].fileTimeHi = 0U;
  c8_info[44].mFileTimeLo = 0U;
  c8_info[44].mFileTimeHi = 0U;
}

static void c8_diag(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
                    *chartInstance, real_T c8_v[3], real_T c8_d[9])
{
  int32_T c8_i49;
  int32_T c8_j;
  int32_T c8_b_j;
  int32_T c8_a;
  int32_T c8_c;
  for (c8_i49 = 0; c8_i49 < 9; c8_i49++) {
    c8_d[c8_i49] = 0.0;
  }

  for (c8_j = 1; c8_j < 4; c8_j++) {
    c8_b_j = c8_j;
    c8_a = c8_b_j;
    c8_c = c8_a;
    c8_d[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c8_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c8_c), 1, 3, 2, 0) - 1)) - 1]
      = c8_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c8_b_j), 1, 3, 1, 0) - 1];
  }
}

static void c8_inv(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
                   *chartInstance, real_T c8_x[9], real_T c8_y[9])
{
  int32_T c8_i50;
  real_T c8_b_x[9];
  int32_T c8_i51;
  real_T c8_c_x[9];
  real_T c8_n1x;
  int32_T c8_i52;
  real_T c8_b_y[9];
  real_T c8_n1xinv;
  real_T c8_a;
  real_T c8_b;
  real_T c8_c_y;
  real_T c8_rc;
  real_T c8_d_x;
  boolean_T c8_b_b;
  real_T c8_e_x;
  int32_T c8_i53;
  static char_T c8_cv0[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  char_T c8_u[8];
  const mxArray *c8_d_y = NULL;
  real_T c8_b_u;
  const mxArray *c8_e_y = NULL;
  real_T c8_c_u;
  const mxArray *c8_f_y = NULL;
  real_T c8_d_u;
  const mxArray *c8_g_y = NULL;
  char_T c8_str[14];
  int32_T c8_i54;
  char_T c8_b_str[14];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  for (c8_i50 = 0; c8_i50 < 9; c8_i50++) {
    c8_b_x[c8_i50] = c8_x[c8_i50];
  }

  c8_inv3x3(chartInstance, c8_b_x, c8_y);
  for (c8_i51 = 0; c8_i51 < 9; c8_i51++) {
    c8_c_x[c8_i51] = c8_x[c8_i51];
  }

  c8_n1x = c8_norm(chartInstance, c8_c_x);
  for (c8_i52 = 0; c8_i52 < 9; c8_i52++) {
    c8_b_y[c8_i52] = c8_y[c8_i52];
  }

  c8_n1xinv = c8_norm(chartInstance, c8_b_y);
  c8_a = c8_n1x;
  c8_b = c8_n1xinv;
  c8_c_y = c8_a * c8_b;
  c8_rc = 1.0 / c8_c_y;
  guard1 = FALSE;
  guard2 = FALSE;
  if (c8_n1x == 0.0) {
    guard2 = TRUE;
  } else if (c8_n1xinv == 0.0) {
    guard2 = TRUE;
  } else if (c8_rc == 0.0) {
    guard1 = TRUE;
  } else {
    c8_d_x = c8_rc;
    c8_b_b = muDoubleScalarIsNaN(c8_d_x);
    guard3 = FALSE;
    if (c8_b_b) {
      guard3 = TRUE;
    } else {
      if (c8_rc < 2.2204460492503131E-16) {
        guard3 = TRUE;
      }
    }

    if (guard3 == TRUE) {
      c8_e_x = c8_rc;
      for (c8_i53 = 0; c8_i53 < 8; c8_i53++) {
        c8_u[c8_i53] = c8_cv0[c8_i53];
      }

      c8_d_y = NULL;
      sf_mex_assign(&c8_d_y, sf_mex_create("y", c8_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    FALSE);
      c8_b_u = 14.0;
      c8_e_y = NULL;
      sf_mex_assign(&c8_e_y, sf_mex_create("y", &c8_b_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c8_c_u = 6.0;
      c8_f_y = NULL;
      sf_mex_assign(&c8_f_y, sf_mex_create("y", &c8_c_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c8_d_u = c8_e_x;
      c8_g_y = NULL;
      sf_mex_assign(&c8_g_y, sf_mex_create("y", &c8_d_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c8_e_emlrt_marshallIn(chartInstance, sf_mex_call_debug("sprintf", 1U, 2U,
        14, sf_mex_call_debug("sprintf", 1U, 3U, 14, c8_d_y, 14, c8_e_y, 14,
        c8_f_y), 14, c8_g_y), "sprintf", c8_str);
      for (c8_i54 = 0; c8_i54 < 14; c8_i54++) {
        c8_b_str[c8_i54] = c8_str[c8_i54];
      }

      c8_b_eml_warning(chartInstance, c8_b_str);
    }
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c8_eml_warning(chartInstance);
  }
}

static void c8_inv3x3(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c8_x[9], real_T c8_y[9])
{
  int32_T c8_p1;
  int32_T c8_p2;
  int32_T c8_p3;
  real_T c8_b_x;
  real_T c8_c_x;
  real_T c8_absx11;
  real_T c8_d_x;
  real_T c8_e_x;
  real_T c8_absx21;
  real_T c8_f_x;
  real_T c8_g_x;
  real_T c8_absx31;
  real_T c8_t1;
  real_T c8_h_x;
  real_T c8_b_y;
  real_T c8_z;
  real_T c8_i_x;
  real_T c8_c_y;
  real_T c8_b_z;
  real_T c8_a;
  real_T c8_b;
  real_T c8_d_y;
  real_T c8_b_a;
  real_T c8_b_b;
  real_T c8_e_y;
  real_T c8_c_a;
  real_T c8_c_b;
  real_T c8_f_y;
  real_T c8_d_a;
  real_T c8_d_b;
  real_T c8_g_y;
  real_T c8_j_x;
  real_T c8_k_x;
  real_T c8_h_y;
  real_T c8_l_x;
  real_T c8_m_x;
  real_T c8_i_y;
  int32_T c8_itmp;
  real_T c8_n_x;
  real_T c8_j_y;
  real_T c8_c_z;
  real_T c8_e_a;
  real_T c8_e_b;
  real_T c8_k_y;
  real_T c8_f_a;
  real_T c8_f_b;
  real_T c8_l_y;
  real_T c8_o_x;
  real_T c8_m_y;
  real_T c8_t3;
  real_T c8_g_a;
  real_T c8_g_b;
  real_T c8_n_y;
  real_T c8_p_x;
  real_T c8_o_y;
  real_T c8_t2;
  int32_T c8_h_a;
  int32_T c8_c;
  real_T c8_i_a;
  real_T c8_h_b;
  real_T c8_p_y;
  real_T c8_j_a;
  real_T c8_i_b;
  real_T c8_q_y;
  real_T c8_q_x;
  real_T c8_r_y;
  real_T c8_d_z;
  int32_T c8_k_a;
  int32_T c8_b_c;
  int32_T c8_l_a;
  int32_T c8_c_c;
  real_T c8_r_x;
  real_T c8_s_y;
  real_T c8_m_a;
  real_T c8_j_b;
  real_T c8_t_y;
  real_T c8_s_x;
  real_T c8_u_y;
  int32_T c8_n_a;
  int32_T c8_d_c;
  real_T c8_o_a;
  real_T c8_k_b;
  real_T c8_v_y;
  real_T c8_p_a;
  real_T c8_l_b;
  real_T c8_w_y;
  real_T c8_t_x;
  real_T c8_x_y;
  real_T c8_e_z;
  int32_T c8_q_a;
  int32_T c8_e_c;
  int32_T c8_r_a;
  int32_T c8_f_c;
  real_T c8_y_y;
  real_T c8_s_a;
  real_T c8_m_b;
  real_T c8_ab_y;
  real_T c8_u_x;
  real_T c8_bb_y;
  int32_T c8_t_a;
  int32_T c8_g_c;
  real_T c8_u_a;
  real_T c8_n_b;
  real_T c8_cb_y;
  real_T c8_v_a;
  real_T c8_o_b;
  real_T c8_db_y;
  real_T c8_v_x;
  real_T c8_eb_y;
  real_T c8_f_z;
  int32_T c8_w_a;
  int32_T c8_h_c;
  int32_T c8_x_a;
  int32_T c8_i_c;
  boolean_T guard1 = FALSE;
  c8_p1 = 0;
  c8_p2 = 3;
  c8_p3 = 6;
  c8_b_x = c8_x[0];
  c8_c_x = c8_b_x;
  c8_absx11 = muDoubleScalarAbs(c8_c_x);
  c8_d_x = c8_x[1];
  c8_e_x = c8_d_x;
  c8_absx21 = muDoubleScalarAbs(c8_e_x);
  c8_f_x = c8_x[2];
  c8_g_x = c8_f_x;
  c8_absx31 = muDoubleScalarAbs(c8_g_x);
  guard1 = FALSE;
  if (c8_absx21 > c8_absx11) {
    if (c8_absx21 > c8_absx31) {
      c8_p1 = 3;
      c8_p2 = 0;
      c8_t1 = c8_x[0];
      c8_x[0] = c8_x[1];
      c8_x[1] = c8_t1;
      c8_t1 = c8_x[3];
      c8_x[3] = c8_x[4];
      c8_x[4] = c8_t1;
      c8_t1 = c8_x[6];
      c8_x[6] = c8_x[7];
      c8_x[7] = c8_t1;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    if (c8_absx31 > c8_absx11) {
      c8_p1 = 6;
      c8_p3 = 0;
      c8_t1 = c8_x[0];
      c8_x[0] = c8_x[2];
      c8_x[2] = c8_t1;
      c8_t1 = c8_x[3];
      c8_x[3] = c8_x[5];
      c8_x[5] = c8_t1;
      c8_t1 = c8_x[6];
      c8_x[6] = c8_x[8];
      c8_x[8] = c8_t1;
    }
  }

  c8_h_x = c8_x[1];
  c8_b_y = c8_x[0];
  c8_z = c8_h_x / c8_b_y;
  c8_x[1] = c8_z;
  c8_i_x = c8_x[2];
  c8_c_y = c8_x[0];
  c8_b_z = c8_i_x / c8_c_y;
  c8_x[2] = c8_b_z;
  c8_a = c8_x[1];
  c8_b = c8_x[3];
  c8_d_y = c8_a * c8_b;
  c8_x[4] -= c8_d_y;
  c8_b_a = c8_x[2];
  c8_b_b = c8_x[3];
  c8_e_y = c8_b_a * c8_b_b;
  c8_x[5] -= c8_e_y;
  c8_c_a = c8_x[1];
  c8_c_b = c8_x[6];
  c8_f_y = c8_c_a * c8_c_b;
  c8_x[7] -= c8_f_y;
  c8_d_a = c8_x[2];
  c8_d_b = c8_x[6];
  c8_g_y = c8_d_a * c8_d_b;
  c8_x[8] -= c8_g_y;
  c8_j_x = c8_x[5];
  c8_k_x = c8_j_x;
  c8_h_y = muDoubleScalarAbs(c8_k_x);
  c8_l_x = c8_x[4];
  c8_m_x = c8_l_x;
  c8_i_y = muDoubleScalarAbs(c8_m_x);
  if (c8_h_y > c8_i_y) {
    c8_itmp = c8_p2;
    c8_p2 = c8_p3;
    c8_p3 = c8_itmp;
    c8_t1 = c8_x[1];
    c8_x[1] = c8_x[2];
    c8_x[2] = c8_t1;
    c8_t1 = c8_x[4];
    c8_x[4] = c8_x[5];
    c8_x[5] = c8_t1;
    c8_t1 = c8_x[7];
    c8_x[7] = c8_x[8];
    c8_x[8] = c8_t1;
  }

  c8_n_x = c8_x[5];
  c8_j_y = c8_x[4];
  c8_c_z = c8_n_x / c8_j_y;
  c8_x[5] = c8_c_z;
  c8_e_a = c8_x[5];
  c8_e_b = c8_x[7];
  c8_k_y = c8_e_a * c8_e_b;
  c8_x[8] -= c8_k_y;
  c8_f_a = c8_x[5];
  c8_f_b = c8_x[1];
  c8_l_y = c8_f_a * c8_f_b;
  c8_o_x = c8_l_y - c8_x[2];
  c8_m_y = c8_x[8];
  c8_t3 = c8_o_x / c8_m_y;
  c8_g_a = c8_x[7];
  c8_g_b = c8_t3;
  c8_n_y = c8_g_a * c8_g_b;
  c8_p_x = -(c8_x[1] + c8_n_y);
  c8_o_y = c8_x[4];
  c8_t2 = c8_p_x / c8_o_y;
  c8_h_a = c8_p1 + 1;
  c8_c = c8_h_a;
  c8_i_a = c8_x[3];
  c8_h_b = c8_t2;
  c8_p_y = c8_i_a * c8_h_b;
  c8_j_a = c8_x[6];
  c8_i_b = c8_t3;
  c8_q_y = c8_j_a * c8_i_b;
  c8_q_x = (1.0 - c8_p_y) - c8_q_y;
  c8_r_y = c8_x[0];
  c8_d_z = c8_q_x / c8_r_y;
  c8_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c8_c), 1, 9, 1, 0) - 1] = c8_d_z;
  c8_k_a = c8_p1 + 2;
  c8_b_c = c8_k_a;
  c8_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c8_b_c), 1, 9, 1, 0) - 1] = c8_t2;
  c8_l_a = c8_p1 + 3;
  c8_c_c = c8_l_a;
  c8_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c8_c_c), 1, 9, 1, 0) - 1] = c8_t3;
  c8_r_x = -c8_x[5];
  c8_s_y = c8_x[8];
  c8_t3 = c8_r_x / c8_s_y;
  c8_m_a = c8_x[7];
  c8_j_b = c8_t3;
  c8_t_y = c8_m_a * c8_j_b;
  c8_s_x = 1.0 - c8_t_y;
  c8_u_y = c8_x[4];
  c8_t2 = c8_s_x / c8_u_y;
  c8_n_a = c8_p2 + 1;
  c8_d_c = c8_n_a;
  c8_o_a = c8_x[3];
  c8_k_b = c8_t2;
  c8_v_y = c8_o_a * c8_k_b;
  c8_p_a = c8_x[6];
  c8_l_b = c8_t3;
  c8_w_y = c8_p_a * c8_l_b;
  c8_t_x = -(c8_v_y + c8_w_y);
  c8_x_y = c8_x[0];
  c8_e_z = c8_t_x / c8_x_y;
  c8_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c8_d_c), 1, 9, 1, 0) - 1] = c8_e_z;
  c8_q_a = c8_p2 + 2;
  c8_e_c = c8_q_a;
  c8_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c8_e_c), 1, 9, 1, 0) - 1] = c8_t2;
  c8_r_a = c8_p2 + 3;
  c8_f_c = c8_r_a;
  c8_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c8_f_c), 1, 9, 1, 0) - 1] = c8_t3;
  c8_y_y = c8_x[8];
  c8_t3 = 1.0 / c8_y_y;
  c8_s_a = -c8_x[7];
  c8_m_b = c8_t3;
  c8_ab_y = c8_s_a * c8_m_b;
  c8_u_x = c8_ab_y;
  c8_bb_y = c8_x[4];
  c8_t2 = c8_u_x / c8_bb_y;
  c8_t_a = c8_p3 + 1;
  c8_g_c = c8_t_a;
  c8_u_a = c8_x[3];
  c8_n_b = c8_t2;
  c8_cb_y = c8_u_a * c8_n_b;
  c8_v_a = c8_x[6];
  c8_o_b = c8_t3;
  c8_db_y = c8_v_a * c8_o_b;
  c8_v_x = -(c8_cb_y + c8_db_y);
  c8_eb_y = c8_x[0];
  c8_f_z = c8_v_x / c8_eb_y;
  c8_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c8_g_c), 1, 9, 1, 0) - 1] = c8_f_z;
  c8_w_a = c8_p3 + 2;
  c8_h_c = c8_w_a;
  c8_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c8_h_c), 1, 9, 1, 0) - 1] = c8_t2;
  c8_x_a = c8_p3 + 3;
  c8_i_c = c8_x_a;
  c8_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c8_i_c), 1, 9, 1, 0) - 1] = c8_t3;
}

static real_T c8_norm(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c8_x[9])
{
  real_T c8_y;
  int32_T c8_j;
  real_T c8_b_j;
  real_T c8_s;
  int32_T c8_i;
  real_T c8_b_i;
  real_T c8_b_x;
  real_T c8_c_x;
  real_T c8_b_y;
  real_T c8_d_x;
  boolean_T c8_b;
  boolean_T exitg1;
  c8_y = 0.0;
  c8_j = 0;
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (c8_j < 3)) {
    c8_b_j = 1.0 + (real_T)c8_j;
    c8_s = 0.0;
    for (c8_i = 0; c8_i < 3; c8_i++) {
      c8_b_i = 1.0 + (real_T)c8_i;
      c8_b_x = c8_x[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c8_b_i), 1, 3, 1, 0) + 3 * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c8_b_j),
        1, 3, 2, 0) - 1)) - 1];
      c8_c_x = c8_b_x;
      c8_b_y = muDoubleScalarAbs(c8_c_x);
      c8_s += c8_b_y;
    }

    c8_d_x = c8_s;
    c8_b = muDoubleScalarIsNaN(c8_d_x);
    if (c8_b) {
      c8_y = rtNaN;
      exitg1 = TRUE;
    } else {
      if (c8_s > c8_y) {
        c8_y = c8_s;
      }

      c8_j++;
    }
  }

  return c8_y;
}

static void c8_eml_warning(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
  int32_T c8_i55;
  static char_T c8_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c8_u[27];
  const mxArray *c8_y = NULL;
  for (c8_i55 = 0; c8_i55 < 27; c8_i55++) {
    c8_u[c8_i55] = c8_varargin_1[c8_i55];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 10, 0U, 1U, 0U, 2, 1, 27), FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c8_y));
}

static void c8_b_eml_warning(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, char_T c8_varargin_2[14])
{
  int32_T c8_i56;
  static char_T c8_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c8_u[33];
  const mxArray *c8_y = NULL;
  int32_T c8_i57;
  char_T c8_b_u[14];
  const mxArray *c8_b_y = NULL;
  for (c8_i56 = 0; c8_i56 < 33; c8_i56++) {
    c8_u[c8_i56] = c8_varargin_1[c8_i56];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 10, 0U, 1U, 0U, 2, 1, 33), FALSE);
  for (c8_i57 = 0; c8_i57 < 14; c8_i57++) {
    c8_b_u[c8_i57] = c8_varargin_2[c8_i57];
  }

  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", c8_b_u, 10, 0U, 1U, 0U, 2, 1, 14),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
    14, c8_y, 14, c8_b_y));
}

static void c8_eml_scalar_eg(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c8_b_eml_scalar_eg(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c8_e_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_sprintf, const char_T *c8_identifier, char_T c8_y[14])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_sprintf), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_sprintf);
}

static void c8_f_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId, char_T c8_y[14])
{
  char_T c8_cv1[14];
  int32_T c8_i58;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_cv1, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c8_i58 = 0; c8_i58 < 14; c8_i58++) {
    c8_y[c8_i58] = c8_cv1[c8_i58];
  }

  sf_mex_destroy(&c8_u);
}

static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static int32_T c8_g_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i59;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i59, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i59;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_sfEvent;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int32_T c8_y;
  SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c8_b_sfEvent = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_sfEvent),
    &c8_thisId);
  sf_mex_destroy(&c8_b_sfEvent);
  *(int32_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static uint8_T c8_h_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_b_is_active_c8_modelo_FK_simul_coleta_dados, const char_T *c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c8_b_is_active_c8_modelo_FK_simul_coleta_dados), &c8_thisId);
  sf_mex_destroy(&c8_b_is_active_c8_modelo_FK_simul_coleta_dados);
  return c8_y;
}

static uint8_T c8_i_emlrt_marshallIn
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_u0, 1, 3, 0U, 0, 0U, 0);
  c8_y = c8_u0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void init_dsm_address_info
  (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
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

void sf_c8_modelo_FK_simul_coleta_dados_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(592820378U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2337282146U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3323011737U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2613818944U);
}

mxArray *sf_c8_modelo_FK_simul_coleta_dados_get_autoinheritance_info(void)
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

mxArray *sf_c8_modelo_FK_simul_coleta_dados_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c8_modelo_FK_simul_coleta_dados(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"u_recuperado\",},{M[8],M[0],T\"is_active_c8_modelo_FK_simul_coleta_dados\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_modelo_FK_simul_coleta_dados_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
    chartInstance = (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modelo_FK_simul_coleta_dadosMachineNumber_,
           8,
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
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c8_ur)[3];
          real_T (*c8_u_recuperado)[3];
          real_T (*c8_vsh)[3];
          real_T (*c8_vah)[3];
          real_T (*c8_voh)[3];
          c8_voh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c8_vah = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c8_vsh = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c8_u_recuperado = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c8_ur = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c8_ur);
          _SFD_SET_DATA_VALUE_PTR(1U, *c8_u_recuperado);
          _SFD_SET_DATA_VALUE_PTR(2U, *c8_vsh);
          _SFD_SET_DATA_VALUE_PTR(3U, *c8_vah);
          _SFD_SET_DATA_VALUE_PTR(4U, *c8_voh);
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

static void sf_opaque_initialize_c8_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c8_modelo_FK_simul_coleta_dados
    ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
  initialize_c8_modelo_FK_simul_coleta_dados
    ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c8_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  enable_c8_modelo_FK_simul_coleta_dados
    ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c8_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  disable_c8_modelo_FK_simul_coleta_dados
    ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c8_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  sf_c8_modelo_FK_simul_coleta_dados
    ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c8_modelo_FK_simul_coleta_dados
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c8_modelo_FK_simul_coleta_dados
    ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_modelo_FK_simul_coleta_dados();/* state var info */
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

extern void sf_internal_set_sim_state_c8_modelo_FK_simul_coleta_dados(SimStruct*
  S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_modelo_FK_simul_coleta_dados();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c8_modelo_FK_simul_coleta_dados
    ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c8_modelo_FK_simul_coleta_dados
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c8_modelo_FK_simul_coleta_dados(S);
}

static void sf_opaque_set_sim_state_c8_modelo_FK_simul_coleta_dados(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c8_modelo_FK_simul_coleta_dados(S, st);
}

static void sf_opaque_terminate_c8_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_FK_simul_coleta_dados_optimization_info();
    }

    finalize_c8_modelo_FK_simul_coleta_dados
      ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc8_modelo_FK_simul_coleta_dados
    ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c8_modelo_FK_simul_coleta_dados
      ((SFc8_modelo_FK_simul_coleta_dadosInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c8_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_modelo_FK_simul_coleta_dados_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      8);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,8,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,8,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,8);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,8,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,8,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,8);
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

static void mdlRTW_c8_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct *)utMalloc
    (sizeof(SFc8_modelo_FK_simul_coleta_dadosInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc8_modelo_FK_simul_coleta_dadosInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c8_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c8_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c8_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c8_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c8_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c8_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c8_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c8_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c8_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.mdlStart = mdlStart_c8_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c8_modelo_FK_simul_coleta_dados;
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

void c8_modelo_FK_simul_coleta_dados_method_dispatcher(SimStruct *S, int_T
  method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_modelo_FK_simul_coleta_dados(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_modelo_FK_simul_coleta_dados(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_modelo_FK_simul_coleta_dados(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_modelo_FK_simul_coleta_dados_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
