/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_FK_simul_coleta_dados_sfun.h"
#include "c21_modelo_FK_simul_coleta_dados.h"
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
static const char * c21_debug_family_names[22] = { "q", "q_prop", "b_prop", "E",
  "S", "H", "HT", "Ptt_prop", "Pbt_prop", "KT", "K", "n", "nargin", "nargout",
  "x_prop", "PT_prop", "q_obs", "R", "i", "x_est", "P_est", "PT_est" };

/* Function Declarations */
static void initialize_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void initialize_params_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void enable_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void disable_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c21_update_debugger_state_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void set_sim_state_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_st);
static void finalize_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void sf_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c21_chartstep_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void initSimStructsc21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void registerMessagesc21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c21_machineNumber, uint32_T
  c21_chartNumber);
static const mxArray *c21_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static void c21_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_PT_est, const char_T *c21_identifier, real_T c21_y[36]);
static void c21_b_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[36]);
static void c21_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static const mxArray *c21_b_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static void c21_c_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_P_est, const char_T *c21_identifier, real_T c21_y[49]);
static void c21_d_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[49]);
static void c21_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static const mxArray *c21_c_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static void c21_e_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_x_est, const char_T *c21_identifier, real_T c21_y[7]);
static void c21_f_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[7]);
static void c21_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static const mxArray *c21_d_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static const mxArray *c21_e_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static const mxArray *c21_f_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static real_T c21_g_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId);
static void c21_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static const mxArray *c21_g_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static void c21_h_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[28]);
static void c21_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static const mxArray *c21_h_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static void c21_i_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[24]);
static void c21_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static void c21_j_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[9]);
static void c21_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static const mxArray *c21_i_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static void c21_k_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[24]);
static void c21_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static const mxArray *c21_j_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static void c21_l_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[28]);
static void c21_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static const mxArray *c21_k_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static void c21_m_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[42]);
static void c21_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static const mxArray *c21_l_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static void c21_n_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[12]);
static void c21_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static const mxArray *c21_m_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static void c21_o_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[3]);
static void c21_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static void c21_p_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[4]);
static void c21_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static void c21_info_helper(c21_ResolvedFunctionInfo c21_info[97]);
static void c21_b_info_helper(c21_ResolvedFunctionInfo c21_info[97]);
static void c21_eye(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                    *chartInstance, real_T c21_I[9]);
static void c21_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static real_T c21_mod(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c21_x, real_T c21_y);
static void c21_eps(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                    *chartInstance);
static void c21_b_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c21_c_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c21_b_eye(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c21_I[16]);
static void c21_inv(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                    *chartInstance, real_T c21_x[9], real_T c21_y[9]);
static void c21_inv3x3(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, real_T c21_x[9], real_T c21_y[9]);
static real_T c21_norm(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, real_T c21_x[9]);
static void c21_eml_warning(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c21_b_eml_warning(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, char_T c21_varargin_2[14]);
static void c21_d_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c21_e_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c21_f_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c21_g_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c21_h_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static real_T c21_dot(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c21_a[4], real_T c21_b[4]);
static void c21_i_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c21_j_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c21_q_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_sprintf, const char_T *c21_identifier, char_T c21_y[14]);
static void c21_r_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, char_T c21_y[14]);
static const mxArray *c21_n_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData);
static int32_T c21_s_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId);
static void c21_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData);
static uint8_T c21_t_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_b_is_active_c21_modelo_FK_simul_coleta_dados, const char_T
   *c21_identifier);
static uint8_T c21_u_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId);
static void init_dsm_address_info
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  chartInstance->c21_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c21_is_active_c21_modelo_FK_simul_coleta_dados = 0U;
}

static void initialize_params_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void enable_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c21_update_debugger_state_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  const mxArray *c21_st;
  const mxArray *c21_y = NULL;
  int32_T c21_i0;
  real_T c21_u[36];
  const mxArray *c21_b_y = NULL;
  int32_T c21_i1;
  real_T c21_b_u[49];
  const mxArray *c21_c_y = NULL;
  int32_T c21_i2;
  real_T c21_c_u[7];
  const mxArray *c21_d_y = NULL;
  uint8_T c21_hoistedGlobal;
  uint8_T c21_d_u;
  const mxArray *c21_e_y = NULL;
  real_T (*c21_x_est)[7];
  real_T (*c21_P_est)[49];
  real_T (*c21_PT_est)[36];
  c21_PT_est = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c21_P_est = (real_T (*)[49])ssGetOutputPortSignal(chartInstance->S, 2);
  c21_x_est = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  c21_st = NULL;
  c21_st = NULL;
  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_createcellarray(4), FALSE);
  for (c21_i0 = 0; c21_i0 < 36; c21_i0++) {
    c21_u[c21_i0] = (*c21_PT_est)[c21_i0];
  }

  c21_b_y = NULL;
  sf_mex_assign(&c21_b_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 2, 6, 6),
                FALSE);
  sf_mex_setcell(c21_y, 0, c21_b_y);
  for (c21_i1 = 0; c21_i1 < 49; c21_i1++) {
    c21_b_u[c21_i1] = (*c21_P_est)[c21_i1];
  }

  c21_c_y = NULL;
  sf_mex_assign(&c21_c_y, sf_mex_create("y", c21_b_u, 0, 0U, 1U, 0U, 2, 7, 7),
                FALSE);
  sf_mex_setcell(c21_y, 1, c21_c_y);
  for (c21_i2 = 0; c21_i2 < 7; c21_i2++) {
    c21_c_u[c21_i2] = (*c21_x_est)[c21_i2];
  }

  c21_d_y = NULL;
  sf_mex_assign(&c21_d_y, sf_mex_create("y", c21_c_u, 0, 0U, 1U, 0U, 1, 7),
                FALSE);
  sf_mex_setcell(c21_y, 2, c21_d_y);
  c21_hoistedGlobal =
    chartInstance->c21_is_active_c21_modelo_FK_simul_coleta_dados;
  c21_d_u = c21_hoistedGlobal;
  c21_e_y = NULL;
  sf_mex_assign(&c21_e_y, sf_mex_create("y", &c21_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c21_y, 3, c21_e_y);
  sf_mex_assign(&c21_st, c21_y, FALSE);
  return c21_st;
}

static void set_sim_state_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_st)
{
  const mxArray *c21_u;
  real_T c21_dv0[36];
  int32_T c21_i3;
  real_T c21_dv1[49];
  int32_T c21_i4;
  real_T c21_dv2[7];
  int32_T c21_i5;
  real_T (*c21_PT_est)[36];
  real_T (*c21_P_est)[49];
  real_T (*c21_x_est)[7];
  c21_PT_est = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c21_P_est = (real_T (*)[49])ssGetOutputPortSignal(chartInstance->S, 2);
  c21_x_est = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c21_doneDoubleBufferReInit = TRUE;
  c21_u = sf_mex_dup(c21_st);
  c21_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c21_u, 0)),
                       "PT_est", c21_dv0);
  for (c21_i3 = 0; c21_i3 < 36; c21_i3++) {
    (*c21_PT_est)[c21_i3] = c21_dv0[c21_i3];
  }

  c21_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c21_u, 1)),
    "P_est", c21_dv1);
  for (c21_i4 = 0; c21_i4 < 49; c21_i4++) {
    (*c21_P_est)[c21_i4] = c21_dv1[c21_i4];
  }

  c21_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c21_u, 2)),
    "x_est", c21_dv2);
  for (c21_i5 = 0; c21_i5 < 7; c21_i5++) {
    (*c21_x_est)[c21_i5] = c21_dv2[c21_i5];
  }

  chartInstance->c21_is_active_c21_modelo_FK_simul_coleta_dados =
    c21_t_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c21_u, 3)),
    "is_active_c21_modelo_FK_simul_coleta_dados");
  sf_mex_destroy(&c21_u);
  c21_update_debugger_state_c21_modelo_FK_simul_coleta_dados(chartInstance);
  sf_mex_destroy(&c21_st);
}

static void finalize_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void sf_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  int32_T c21_i6;
  int32_T c21_i7;
  int32_T c21_i8;
  int32_T c21_i9;
  int32_T c21_i10;
  int32_T c21_i11;
  int32_T c21_i12;
  real_T *c21_i;
  real_T (*c21_PT_est)[36];
  real_T (*c21_P_est)[49];
  real_T (*c21_R)[9];
  real_T (*c21_q_obs)[4];
  real_T (*c21_PT_prop)[36];
  real_T (*c21_x_est)[7];
  real_T (*c21_x_prop)[7];
  c21_i = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c21_PT_est = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c21_P_est = (real_T (*)[49])ssGetOutputPortSignal(chartInstance->S, 2);
  c21_R = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 3);
  c21_q_obs = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
  c21_PT_prop = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 1);
  c21_x_est = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  c21_x_prop = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 17U, chartInstance->c21_sfEvent);
  for (c21_i6 = 0; c21_i6 < 7; c21_i6++) {
    _SFD_DATA_RANGE_CHECK((*c21_x_prop)[c21_i6], 0U);
  }

  for (c21_i7 = 0; c21_i7 < 7; c21_i7++) {
    _SFD_DATA_RANGE_CHECK((*c21_x_est)[c21_i7], 1U);
  }

  for (c21_i8 = 0; c21_i8 < 36; c21_i8++) {
    _SFD_DATA_RANGE_CHECK((*c21_PT_prop)[c21_i8], 2U);
  }

  for (c21_i9 = 0; c21_i9 < 4; c21_i9++) {
    _SFD_DATA_RANGE_CHECK((*c21_q_obs)[c21_i9], 3U);
  }

  for (c21_i10 = 0; c21_i10 < 9; c21_i10++) {
    _SFD_DATA_RANGE_CHECK((*c21_R)[c21_i10], 4U);
  }

  for (c21_i11 = 0; c21_i11 < 49; c21_i11++) {
    _SFD_DATA_RANGE_CHECK((*c21_P_est)[c21_i11], 5U);
  }

  for (c21_i12 = 0; c21_i12 < 36; c21_i12++) {
    _SFD_DATA_RANGE_CHECK((*c21_PT_est)[c21_i12], 6U);
  }

  _SFD_DATA_RANGE_CHECK(*c21_i, 7U);
  chartInstance->c21_sfEvent = CALL_EVENT;
  c21_chartstep_c21_modelo_FK_simul_coleta_dados(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_modelo_FK_simul_coleta_dadosMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c21_chartstep_c21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  real_T c21_hoistedGlobal;
  int32_T c21_i13;
  real_T c21_x_prop[7];
  int32_T c21_i14;
  real_T c21_PT_prop[36];
  int32_T c21_i15;
  real_T c21_q_obs[4];
  int32_T c21_i16;
  real_T c21_R[9];
  real_T c21_i;
  uint32_T c21_debug_family_var_map[22];
  real_T c21_q[4];
  real_T c21_q_prop[4];
  real_T c21_b_prop[3];
  real_T c21_E[12];
  real_T c21_S[42];
  real_T c21_H[28];
  real_T c21_HT[24];
  real_T c21_Ptt_prop[9];
  real_T c21_Pbt_prop[9];
  real_T c21_KT[24];
  real_T c21_K[28];
  real_T c21_n;
  real_T c21_nargin = 5.0;
  real_T c21_nargout = 3.0;
  real_T c21_x_est[7];
  real_T c21_P_est[49];
  real_T c21_PT_est[36];
  int32_T c21_i17;
  int32_T c21_i18;
  int32_T c21_i19;
  real_T c21_b[9];
  int32_T c21_i20;
  int32_T c21_i21;
  int32_T c21_i22;
  int32_T c21_i23;
  int32_T c21_i24;
  int32_T c21_i25;
  int32_T c21_i26;
  int32_T c21_i27;
  int32_T c21_i28;
  int32_T c21_i29;
  int32_T c21_i30;
  int32_T c21_i31;
  int32_T c21_i32;
  int32_T c21_i33;
  int32_T c21_i34;
  int32_T c21_i35;
  int32_T c21_i36;
  real_T c21_a[42];
  int32_T c21_i37;
  real_T c21_b_b[36];
  int32_T c21_i38;
  int32_T c21_i39;
  int32_T c21_i40;
  int32_T c21_i41;
  real_T c21_y[42];
  int32_T c21_i42;
  int32_T c21_i43;
  int32_T c21_i44;
  int32_T c21_i45;
  int32_T c21_i46;
  int32_T c21_i47;
  real_T c21_c_b[42];
  int32_T c21_i48;
  int32_T c21_i49;
  int32_T c21_i50;
  real_T c21_C[49];
  int32_T c21_i51;
  int32_T c21_i52;
  int32_T c21_i53;
  int32_T c21_i54;
  int32_T c21_i55;
  int32_T c21_i56;
  int32_T c21_i57;
  int32_T c21_i58;
  int32_T c21_i59;
  real_T c21_dv3[16];
  int32_T c21_i60;
  int32_T c21_i61;
  int32_T c21_i62;
  int32_T c21_i63;
  int32_T c21_i64;
  int32_T c21_i65;
  int32_T c21_i66;
  int32_T c21_i67;
  int32_T c21_i68;
  int32_T c21_i69;
  int32_T c21_i70;
  int32_T c21_i71;
  int32_T c21_i72;
  int32_T c21_i73;
  int32_T c21_i74;
  int32_T c21_i75;
  int32_T c21_i76;
  int32_T c21_i77;
  int32_T c21_i78;
  int32_T c21_i79;
  int32_T c21_i80;
  int32_T c21_i81;
  int32_T c21_i82;
  int32_T c21_i83;
  real_T c21_b_a[18];
  int32_T c21_i84;
  int32_T c21_i85;
  int32_T c21_i86;
  int32_T c21_i87;
  int32_T c21_i88;
  real_T c21_b_Ptt_prop[9];
  int32_T c21_i89;
  int32_T c21_i90;
  int32_T c21_i91;
  int32_T c21_i92;
  real_T c21_b_y[18];
  int32_T c21_i93;
  int32_T c21_i94;
  int32_T c21_i95;
  int32_T c21_i96;
  int32_T c21_i97;
  int32_T c21_i98;
  real_T c21_d_b[12];
  int32_T c21_i99;
  int32_T c21_i100;
  int32_T c21_i101;
  real_T c21_b_C[24];
  int32_T c21_i102;
  int32_T c21_i103;
  int32_T c21_i104;
  int32_T c21_i105;
  int32_T c21_i106;
  int32_T c21_i107;
  int32_T c21_i108;
  int32_T c21_i109;
  int32_T c21_i110;
  int32_T c21_i111;
  int32_T c21_i112;
  real_T c21_e_b[24];
  int32_T c21_i113;
  int32_T c21_i114;
  int32_T c21_i115;
  int32_T c21_i116;
  real_T c21_c_y[36];
  int32_T c21_i117;
  int32_T c21_i118;
  int32_T c21_i119;
  int32_T c21_i120;
  int32_T c21_i121;
  int32_T c21_i122;
  real_T c21_d_y[36];
  int32_T c21_i123;
  int32_T c21_i124;
  int32_T c21_i125;
  int32_T c21_i126;
  int32_T c21_i127;
  int32_T c21_i128;
  int32_T c21_i129;
  int32_T c21_i130;
  int32_T c21_i131;
  int32_T c21_i132;
  int32_T c21_i133;
  int32_T c21_i134;
  int32_T c21_i135;
  int32_T c21_i136;
  int32_T c21_i137;
  int32_T c21_i138;
  int32_T c21_i139;
  int32_T c21_i140;
  int32_T c21_i141;
  int32_T c21_i142;
  int32_T c21_i143;
  int32_T c21_i144;
  int32_T c21_i145;
  int32_T c21_i146;
  int32_T c21_i147;
  int32_T c21_i148;
  int32_T c21_i149;
  int32_T c21_i150;
  int32_T c21_i151;
  int32_T c21_i152;
  int32_T c21_i153;
  int32_T c21_i154;
  real_T c21_c_C[28];
  int32_T c21_i155;
  int32_T c21_i156;
  int32_T c21_i157;
  int32_T c21_i158;
  int32_T c21_i159;
  int32_T c21_i160;
  int32_T c21_i161;
  int32_T c21_i162;
  int32_T c21_i163;
  int32_T c21_i164;
  real_T c21_b_q_prop[4];
  int32_T c21_i165;
  real_T c21_b_q_obs[4];
  int32_T c21_i166;
  int32_T c21_i167;
  int32_T c21_i168;
  real_T c21_f_b[4];
  int32_T c21_i169;
  real_T c21_e_y[7];
  int32_T c21_i170;
  int32_T c21_i171;
  int32_T c21_i172;
  int32_T c21_i173;
  real_T c21_scale;
  int32_T c21_k;
  int32_T c21_b_k;
  real_T c21_x;
  real_T c21_b_x;
  real_T c21_absxk;
  real_T c21_t;
  int32_T c21_i174;
  real_T c21_B;
  real_T c21_f_y;
  real_T c21_g_y;
  int32_T c21_i175;
  int32_T c21_i176;
  int32_T c21_i177;
  int32_T c21_i178;
  int32_T c21_i179;
  real_T *c21_b_i;
  real_T (*c21_b_x_est)[7];
  real_T (*c21_b_P_est)[49];
  real_T (*c21_b_PT_est)[36];
  real_T (*c21_b_R)[9];
  real_T (*c21_c_q_obs)[4];
  real_T (*c21_b_PT_prop)[36];
  real_T (*c21_b_x_prop)[7];
  c21_b_i = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c21_b_PT_est = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c21_b_P_est = (real_T (*)[49])ssGetOutputPortSignal(chartInstance->S, 2);
  c21_b_R = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 3);
  c21_c_q_obs = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
  c21_b_PT_prop = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 1);
  c21_b_x_est = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  c21_b_x_prop = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 17U, chartInstance->c21_sfEvent);
  c21_hoistedGlobal = *c21_b_i;
  for (c21_i13 = 0; c21_i13 < 7; c21_i13++) {
    c21_x_prop[c21_i13] = (*c21_b_x_prop)[c21_i13];
  }

  for (c21_i14 = 0; c21_i14 < 36; c21_i14++) {
    c21_PT_prop[c21_i14] = (*c21_b_PT_prop)[c21_i14];
  }

  for (c21_i15 = 0; c21_i15 < 4; c21_i15++) {
    c21_q_obs[c21_i15] = (*c21_c_q_obs)[c21_i15];
  }

  for (c21_i16 = 0; c21_i16 < 9; c21_i16++) {
    c21_R[c21_i16] = (*c21_b_R)[c21_i16];
  }

  c21_i = c21_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 22U, 22U, c21_debug_family_names,
    c21_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_q, 0U, c21_f_sf_marshallOut,
    c21_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_q_prop, 1U, c21_f_sf_marshallOut,
    c21_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_b_prop, 2U, c21_m_sf_marshallOut,
    c21_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_E, 3U, c21_l_sf_marshallOut,
    c21_k_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_S, 4U, c21_k_sf_marshallOut,
    c21_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_H, 5U, c21_j_sf_marshallOut,
    c21_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_HT, 6U, c21_i_sf_marshallOut,
    c21_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_Ptt_prop, 7U, c21_e_sf_marshallOut,
    c21_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_Pbt_prop, 8U, c21_e_sf_marshallOut,
    c21_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_KT, 9U, c21_h_sf_marshallOut,
    c21_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_K, 10U, c21_g_sf_marshallOut,
    c21_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c21_n, 11U, c21_d_sf_marshallOut,
    c21_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c21_nargin, 12U, c21_d_sf_marshallOut,
    c21_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c21_nargout, 13U, c21_d_sf_marshallOut,
    c21_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c21_x_prop, 14U, c21_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c21_PT_prop, 15U, c21_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c21_q_obs, 16U, c21_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c21_R, 17U, c21_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c21_i, 18U, c21_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_x_est, 19U, c21_c_sf_marshallOut,
    c21_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_P_est, 20U, c21_b_sf_marshallOut,
    c21_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c21_PT_est, 21U, c21_sf_marshallOut,
    c21_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 3);
  for (c21_i17 = 0; c21_i17 < 4; c21_i17++) {
    c21_q[c21_i17] = c21_q_obs[c21_i17];
  }

  _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 4);
  c21_q_obs[0] = c21_q[1];
  c21_q_obs[1] = c21_q[2];
  c21_q_obs[2] = c21_q[3];
  c21_q_obs[3] = c21_q[0];
  _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 7);
  for (c21_i18 = 0; c21_i18 < 4; c21_i18++) {
    c21_q_prop[c21_i18] = c21_x_prop[c21_i18];
  }

  _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 8);
  for (c21_i19 = 0; c21_i19 < 3; c21_i19++) {
    c21_b_prop[c21_i19] = c21_x_prop[c21_i19 + 4];
  }

  _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 12);
  c21_E[0] = c21_q_prop[3];
  c21_E[4] = -c21_q_prop[2];
  c21_E[8] = c21_q_prop[1];
  c21_E[1] = c21_q_prop[2];
  c21_E[5] = c21_q_prop[3];
  c21_E[9] = -c21_q_prop[0];
  c21_E[2] = -c21_q_prop[1];
  c21_E[6] = c21_q_prop[0];
  c21_E[10] = c21_q_prop[3];
  c21_E[3] = -c21_q_prop[0];
  c21_E[7] = -c21_q_prop[1];
  c21_E[11] = -c21_q_prop[2];
  _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 18);
  c21_eye(chartInstance, c21_b);
  c21_i20 = 0;
  c21_i21 = 0;
  for (c21_i22 = 0; c21_i22 < 3; c21_i22++) {
    for (c21_i23 = 0; c21_i23 < 4; c21_i23++) {
      c21_S[c21_i23 + c21_i20] = c21_E[c21_i23 + c21_i21];
    }

    c21_i20 += 7;
    c21_i21 += 4;
  }

  c21_i24 = 0;
  for (c21_i25 = 0; c21_i25 < 3; c21_i25++) {
    for (c21_i26 = 0; c21_i26 < 4; c21_i26++) {
      c21_S[(c21_i26 + c21_i24) + 21] = 0.0;
    }

    c21_i24 += 7;
  }

  c21_i27 = 0;
  for (c21_i28 = 0; c21_i28 < 3; c21_i28++) {
    for (c21_i29 = 0; c21_i29 < 3; c21_i29++) {
      c21_S[(c21_i29 + c21_i27) + 4] = 0.0;
    }

    c21_i27 += 7;
  }

  c21_i30 = 0;
  c21_i31 = 0;
  for (c21_i32 = 0; c21_i32 < 3; c21_i32++) {
    for (c21_i33 = 0; c21_i33 < 3; c21_i33++) {
      c21_S[(c21_i33 + c21_i30) + 25] = c21_b[c21_i33 + c21_i31];
    }

    c21_i30 += 7;
    c21_i31 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 20);
  if (CV_EML_IF(0, 1, 0, c21_mod(chartInstance, c21_i, 2.0) != 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 21);
    for (c21_i34 = 0; c21_i34 < 7; c21_i34++) {
      c21_x_est[c21_i34] = c21_x_prop[c21_i34];
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 22);
    for (c21_i35 = 0; c21_i35 < 36; c21_i35++) {
      c21_PT_est[c21_i35] = c21_PT_prop[c21_i35];
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 23);
    for (c21_i36 = 0; c21_i36 < 42; c21_i36++) {
      c21_a[c21_i36] = c21_S[c21_i36];
    }

    for (c21_i37 = 0; c21_i37 < 36; c21_i37++) {
      c21_b_b[c21_i37] = c21_PT_est[c21_i37];
    }

    c21_b_eml_scalar_eg(chartInstance);
    c21_b_eml_scalar_eg(chartInstance);
    for (c21_i38 = 0; c21_i38 < 7; c21_i38++) {
      c21_i39 = 0;
      c21_i40 = 0;
      for (c21_i41 = 0; c21_i41 < 6; c21_i41++) {
        c21_y[c21_i39 + c21_i38] = 0.0;
        c21_i42 = 0;
        for (c21_i43 = 0; c21_i43 < 6; c21_i43++) {
          c21_y[c21_i39 + c21_i38] += c21_a[c21_i42 + c21_i38] * c21_b_b[c21_i43
            + c21_i40];
          c21_i42 += 7;
        }

        c21_i39 += 7;
        c21_i40 += 6;
      }
    }

    c21_i44 = 0;
    for (c21_i45 = 0; c21_i45 < 7; c21_i45++) {
      c21_i46 = 0;
      for (c21_i47 = 0; c21_i47 < 6; c21_i47++) {
        c21_c_b[c21_i47 + c21_i44] = c21_S[c21_i46 + c21_i45];
        c21_i46 += 7;
      }

      c21_i44 += 6;
    }

    c21_c_eml_scalar_eg(chartInstance);
    c21_c_eml_scalar_eg(chartInstance);
    for (c21_i48 = 0; c21_i48 < 49; c21_i48++) {
      c21_P_est[c21_i48] = 0.0;
    }

    for (c21_i49 = 0; c21_i49 < 49; c21_i49++) {
      c21_P_est[c21_i49] = 0.0;
    }

    for (c21_i50 = 0; c21_i50 < 49; c21_i50++) {
      c21_C[c21_i50] = c21_P_est[c21_i50];
    }

    for (c21_i51 = 0; c21_i51 < 49; c21_i51++) {
      c21_P_est[c21_i51] = c21_C[c21_i51];
    }

    for (c21_i52 = 0; c21_i52 < 49; c21_i52++) {
      c21_C[c21_i52] = c21_P_est[c21_i52];
    }

    for (c21_i53 = 0; c21_i53 < 49; c21_i53++) {
      c21_P_est[c21_i53] = c21_C[c21_i53];
    }

    for (c21_i54 = 0; c21_i54 < 7; c21_i54++) {
      c21_i55 = 0;
      c21_i56 = 0;
      for (c21_i57 = 0; c21_i57 < 7; c21_i57++) {
        c21_P_est[c21_i55 + c21_i54] = 0.0;
        c21_i58 = 0;
        for (c21_i59 = 0; c21_i59 < 6; c21_i59++) {
          c21_P_est[c21_i55 + c21_i54] += c21_y[c21_i58 + c21_i54] *
            c21_c_b[c21_i59 + c21_i56];
          c21_i58 += 7;
        }

        c21_i55 += 7;
        c21_i56 += 6;
      }
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 27);
    c21_b_eye(chartInstance, c21_dv3);
    c21_i60 = 0;
    for (c21_i61 = 0; c21_i61 < 4; c21_i61++) {
      for (c21_i62 = 0; c21_i62 < 4; c21_i62++) {
        c21_H[c21_i62 + c21_i60] = c21_dv3[c21_i62 + c21_i60];
      }

      c21_i60 += 4;
    }

    c21_i63 = 0;
    for (c21_i64 = 0; c21_i64 < 3; c21_i64++) {
      for (c21_i65 = 0; c21_i65 < 4; c21_i65++) {
        c21_H[(c21_i65 + c21_i63) + 16] = 0.0;
      }

      c21_i63 += 4;
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 28);
    c21_i66 = 0;
    for (c21_i67 = 0; c21_i67 < 3; c21_i67++) {
      for (c21_i68 = 0; c21_i68 < 4; c21_i68++) {
        c21_HT[c21_i68 + c21_i66] = c21_E[c21_i68 + c21_i66];
      }

      c21_i66 += 4;
    }

    c21_i69 = 0;
    for (c21_i70 = 0; c21_i70 < 3; c21_i70++) {
      for (c21_i71 = 0; c21_i71 < 4; c21_i71++) {
        c21_HT[(c21_i71 + c21_i69) + 12] = 0.0;
      }

      c21_i69 += 4;
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 31);
    c21_i72 = 0;
    c21_i73 = 0;
    for (c21_i74 = 0; c21_i74 < 3; c21_i74++) {
      for (c21_i75 = 0; c21_i75 < 3; c21_i75++) {
        c21_Ptt_prop[c21_i75 + c21_i72] = c21_PT_prop[c21_i75 + c21_i73];
      }

      c21_i72 += 3;
      c21_i73 += 6;
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 32);
    c21_i76 = 0;
    c21_i77 = 0;
    for (c21_i78 = 0; c21_i78 < 3; c21_i78++) {
      for (c21_i79 = 0; c21_i79 < 3; c21_i79++) {
        c21_Pbt_prop[c21_i79 + c21_i76] = c21_PT_prop[(c21_i79 + c21_i77) + 3];
      }

      c21_i76 += 3;
      c21_i77 += 6;
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 35);
    c21_i80 = 0;
    c21_i81 = 0;
    for (c21_i82 = 0; c21_i82 < 3; c21_i82++) {
      for (c21_i83 = 0; c21_i83 < 3; c21_i83++) {
        c21_b_a[c21_i83 + c21_i80] = c21_Ptt_prop[c21_i83 + c21_i81];
      }

      c21_i80 += 6;
      c21_i81 += 3;
    }

    c21_i84 = 0;
    c21_i85 = 0;
    for (c21_i86 = 0; c21_i86 < 3; c21_i86++) {
      for (c21_i87 = 0; c21_i87 < 3; c21_i87++) {
        c21_b_a[(c21_i87 + c21_i84) + 3] = c21_Pbt_prop[c21_i87 + c21_i85];
      }

      c21_i84 += 6;
      c21_i85 += 3;
    }

    for (c21_i88 = 0; c21_i88 < 9; c21_i88++) {
      c21_b_Ptt_prop[c21_i88] = c21_Ptt_prop[c21_i88] + c21_R[c21_i88];
    }

    c21_inv(chartInstance, c21_b_Ptt_prop, c21_b);
    c21_d_eml_scalar_eg(chartInstance);
    c21_d_eml_scalar_eg(chartInstance);
    for (c21_i89 = 0; c21_i89 < 6; c21_i89++) {
      c21_i90 = 0;
      c21_i91 = 0;
      for (c21_i92 = 0; c21_i92 < 3; c21_i92++) {
        c21_b_y[c21_i90 + c21_i89] = 0.0;
        c21_i93 = 0;
        for (c21_i94 = 0; c21_i94 < 3; c21_i94++) {
          c21_b_y[c21_i90 + c21_i89] += c21_b_a[c21_i93 + c21_i89] *
            c21_b[c21_i94 + c21_i91];
          c21_i93 += 6;
        }

        c21_i90 += 6;
        c21_i91 += 3;
      }
    }

    c21_i95 = 0;
    for (c21_i96 = 0; c21_i96 < 4; c21_i96++) {
      c21_i97 = 0;
      for (c21_i98 = 0; c21_i98 < 3; c21_i98++) {
        c21_d_b[c21_i98 + c21_i95] = c21_E[c21_i97 + c21_i96];
        c21_i97 += 4;
      }

      c21_i95 += 3;
    }

    c21_e_eml_scalar_eg(chartInstance);
    c21_e_eml_scalar_eg(chartInstance);
    for (c21_i99 = 0; c21_i99 < 24; c21_i99++) {
      c21_KT[c21_i99] = 0.0;
    }

    for (c21_i100 = 0; c21_i100 < 24; c21_i100++) {
      c21_KT[c21_i100] = 0.0;
    }

    for (c21_i101 = 0; c21_i101 < 24; c21_i101++) {
      c21_b_C[c21_i101] = c21_KT[c21_i101];
    }

    for (c21_i102 = 0; c21_i102 < 24; c21_i102++) {
      c21_KT[c21_i102] = c21_b_C[c21_i102];
    }

    for (c21_i103 = 0; c21_i103 < 24; c21_i103++) {
      c21_b_C[c21_i103] = c21_KT[c21_i103];
    }

    for (c21_i104 = 0; c21_i104 < 24; c21_i104++) {
      c21_KT[c21_i104] = c21_b_C[c21_i104];
    }

    for (c21_i105 = 0; c21_i105 < 6; c21_i105++) {
      c21_i106 = 0;
      c21_i107 = 0;
      for (c21_i108 = 0; c21_i108 < 4; c21_i108++) {
        c21_KT[c21_i106 + c21_i105] = 0.0;
        c21_i109 = 0;
        for (c21_i110 = 0; c21_i110 < 3; c21_i110++) {
          c21_KT[c21_i106 + c21_i105] += c21_b_y[c21_i109 + c21_i105] *
            c21_d_b[c21_i110 + c21_i107];
          c21_i109 += 6;
        }

        c21_i106 += 6;
        c21_i107 += 3;
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 40);
    for (c21_i111 = 0; c21_i111 < 24; c21_i111++) {
      c21_b_C[c21_i111] = c21_KT[c21_i111];
    }

    for (c21_i112 = 0; c21_i112 < 24; c21_i112++) {
      c21_e_b[c21_i112] = c21_HT[c21_i112];
    }

    c21_f_eml_scalar_eg(chartInstance);
    c21_f_eml_scalar_eg(chartInstance);
    for (c21_i113 = 0; c21_i113 < 6; c21_i113++) {
      c21_i114 = 0;
      c21_i115 = 0;
      for (c21_i116 = 0; c21_i116 < 6; c21_i116++) {
        c21_c_y[c21_i114 + c21_i113] = 0.0;
        c21_i117 = 0;
        for (c21_i118 = 0; c21_i118 < 4; c21_i118++) {
          c21_c_y[c21_i114 + c21_i113] += c21_b_C[c21_i117 + c21_i113] *
            c21_e_b[c21_i118 + c21_i115];
          c21_i117 += 6;
        }

        c21_i114 += 6;
        c21_i115 += 4;
      }
    }

    for (c21_i119 = 0; c21_i119 < 36; c21_i119++) {
      c21_b_b[c21_i119] = c21_PT_prop[c21_i119];
    }

    c21_g_eml_scalar_eg(chartInstance);
    c21_g_eml_scalar_eg(chartInstance);
    for (c21_i120 = 0; c21_i120 < 6; c21_i120++) {
      c21_i121 = 0;
      for (c21_i122 = 0; c21_i122 < 6; c21_i122++) {
        c21_d_y[c21_i121 + c21_i120] = 0.0;
        c21_i123 = 0;
        for (c21_i124 = 0; c21_i124 < 6; c21_i124++) {
          c21_d_y[c21_i121 + c21_i120] += c21_c_y[c21_i123 + c21_i120] *
            c21_b_b[c21_i124 + c21_i121];
          c21_i123 += 6;
        }

        c21_i121 += 6;
      }
    }

    for (c21_i125 = 0; c21_i125 < 36; c21_i125++) {
      c21_PT_est[c21_i125] = c21_PT_prop[c21_i125] - c21_d_y[c21_i125];
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 43);
    for (c21_i126 = 0; c21_i126 < 42; c21_i126++) {
      c21_a[c21_i126] = c21_S[c21_i126];
    }

    for (c21_i127 = 0; c21_i127 < 36; c21_i127++) {
      c21_b_b[c21_i127] = c21_PT_est[c21_i127];
    }

    c21_b_eml_scalar_eg(chartInstance);
    c21_b_eml_scalar_eg(chartInstance);
    for (c21_i128 = 0; c21_i128 < 7; c21_i128++) {
      c21_i129 = 0;
      c21_i130 = 0;
      for (c21_i131 = 0; c21_i131 < 6; c21_i131++) {
        c21_y[c21_i129 + c21_i128] = 0.0;
        c21_i132 = 0;
        for (c21_i133 = 0; c21_i133 < 6; c21_i133++) {
          c21_y[c21_i129 + c21_i128] += c21_a[c21_i132 + c21_i128] *
            c21_b_b[c21_i133 + c21_i130];
          c21_i132 += 7;
        }

        c21_i129 += 7;
        c21_i130 += 6;
      }
    }

    c21_i134 = 0;
    for (c21_i135 = 0; c21_i135 < 7; c21_i135++) {
      c21_i136 = 0;
      for (c21_i137 = 0; c21_i137 < 6; c21_i137++) {
        c21_c_b[c21_i137 + c21_i134] = c21_S[c21_i136 + c21_i135];
        c21_i136 += 7;
      }

      c21_i134 += 6;
    }

    c21_c_eml_scalar_eg(chartInstance);
    c21_c_eml_scalar_eg(chartInstance);
    for (c21_i138 = 0; c21_i138 < 49; c21_i138++) {
      c21_P_est[c21_i138] = 0.0;
    }

    for (c21_i139 = 0; c21_i139 < 49; c21_i139++) {
      c21_P_est[c21_i139] = 0.0;
    }

    for (c21_i140 = 0; c21_i140 < 49; c21_i140++) {
      c21_C[c21_i140] = c21_P_est[c21_i140];
    }

    for (c21_i141 = 0; c21_i141 < 49; c21_i141++) {
      c21_P_est[c21_i141] = c21_C[c21_i141];
    }

    for (c21_i142 = 0; c21_i142 < 49; c21_i142++) {
      c21_C[c21_i142] = c21_P_est[c21_i142];
    }

    for (c21_i143 = 0; c21_i143 < 49; c21_i143++) {
      c21_P_est[c21_i143] = c21_C[c21_i143];
    }

    for (c21_i144 = 0; c21_i144 < 7; c21_i144++) {
      c21_i145 = 0;
      c21_i146 = 0;
      for (c21_i147 = 0; c21_i147 < 7; c21_i147++) {
        c21_P_est[c21_i145 + c21_i144] = 0.0;
        c21_i148 = 0;
        for (c21_i149 = 0; c21_i149 < 6; c21_i149++) {
          c21_P_est[c21_i145 + c21_i144] += c21_y[c21_i148 + c21_i144] *
            c21_c_b[c21_i149 + c21_i146];
          c21_i148 += 7;
        }

        c21_i145 += 7;
        c21_i146 += 6;
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 46);
    for (c21_i150 = 0; c21_i150 < 42; c21_i150++) {
      c21_a[c21_i150] = c21_S[c21_i150];
    }

    for (c21_i151 = 0; c21_i151 < 24; c21_i151++) {
      c21_b_C[c21_i151] = c21_KT[c21_i151];
    }

    c21_h_eml_scalar_eg(chartInstance);
    c21_h_eml_scalar_eg(chartInstance);
    for (c21_i152 = 0; c21_i152 < 28; c21_i152++) {
      c21_K[c21_i152] = 0.0;
    }

    for (c21_i153 = 0; c21_i153 < 28; c21_i153++) {
      c21_K[c21_i153] = 0.0;
    }

    for (c21_i154 = 0; c21_i154 < 28; c21_i154++) {
      c21_c_C[c21_i154] = c21_K[c21_i154];
    }

    for (c21_i155 = 0; c21_i155 < 28; c21_i155++) {
      c21_K[c21_i155] = c21_c_C[c21_i155];
    }

    for (c21_i156 = 0; c21_i156 < 28; c21_i156++) {
      c21_c_C[c21_i156] = c21_K[c21_i156];
    }

    for (c21_i157 = 0; c21_i157 < 28; c21_i157++) {
      c21_K[c21_i157] = c21_c_C[c21_i157];
    }

    for (c21_i158 = 0; c21_i158 < 7; c21_i158++) {
      c21_i159 = 0;
      c21_i160 = 0;
      for (c21_i161 = 0; c21_i161 < 4; c21_i161++) {
        c21_K[c21_i159 + c21_i158] = 0.0;
        c21_i162 = 0;
        for (c21_i163 = 0; c21_i163 < 6; c21_i163++) {
          c21_K[c21_i159 + c21_i158] += c21_a[c21_i162 + c21_i158] *
            c21_b_C[c21_i163 + c21_i160];
          c21_i162 += 7;
        }

        c21_i159 += 7;
        c21_i160 += 6;
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 49);
    for (c21_i164 = 0; c21_i164 < 4; c21_i164++) {
      c21_b_q_prop[c21_i164] = c21_q_prop[c21_i164];
    }

    for (c21_i165 = 0; c21_i165 < 4; c21_i165++) {
      c21_b_q_obs[c21_i165] = c21_q_obs[c21_i165];
    }

    if (CV_EML_IF(0, 1, 1, c21_dot(chartInstance, c21_b_q_prop, c21_b_q_obs) >
                  0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 50);
    } else {
      _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 52);
      for (c21_i166 = 0; c21_i166 < 4; c21_i166++) {
        c21_q_obs[c21_i166] = -c21_q_obs[c21_i166];
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 55);
    for (c21_i167 = 0; c21_i167 < 28; c21_i167++) {
      c21_c_C[c21_i167] = c21_K[c21_i167];
    }

    for (c21_i168 = 0; c21_i168 < 4; c21_i168++) {
      c21_f_b[c21_i168] = c21_q_obs[c21_i168] - c21_q_prop[c21_i168];
    }

    c21_j_eml_scalar_eg(chartInstance);
    c21_j_eml_scalar_eg(chartInstance);
    for (c21_i169 = 0; c21_i169 < 7; c21_i169++) {
      c21_e_y[c21_i169] = 0.0;
      c21_i170 = 0;
      for (c21_i171 = 0; c21_i171 < 4; c21_i171++) {
        c21_e_y[c21_i169] += c21_c_C[c21_i170 + c21_i169] * c21_f_b[c21_i171];
        c21_i170 += 7;
      }
    }

    for (c21_i172 = 0; c21_i172 < 7; c21_i172++) {
      c21_x_est[c21_i172] = c21_x_prop[c21_i172] + c21_e_y[c21_i172];
    }

    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 58);
    for (c21_i173 = 0; c21_i173 < 4; c21_i173++) {
      c21_f_b[c21_i173] = c21_x_est[c21_i173];
    }

    c21_n = 0.0;
    c21_scale = 2.2250738585072014E-308;
    for (c21_k = 1; c21_k < 5; c21_k++) {
      c21_b_k = c21_k;
      c21_x = c21_f_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c21_b_k), 1, 4, 1, 0) - 1];
      c21_b_x = c21_x;
      c21_absxk = muDoubleScalarAbs(c21_b_x);
      if (c21_absxk > c21_scale) {
        c21_t = c21_scale / c21_absxk;
        c21_n = 1.0 + c21_n * c21_t * c21_t;
        c21_scale = c21_absxk;
      } else {
        c21_t = c21_absxk / c21_scale;
        c21_n += c21_t * c21_t;
      }
    }

    c21_n = c21_scale * muDoubleScalarSqrt(c21_n);
    _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, 59);
    for (c21_i174 = 0; c21_i174 < 4; c21_i174++) {
      c21_f_b[c21_i174] = c21_x_est[c21_i174];
    }

    c21_B = c21_n;
    c21_f_y = c21_B;
    c21_g_y = c21_f_y;
    for (c21_i175 = 0; c21_i175 < 4; c21_i175++) {
      c21_f_b[c21_i175] /= c21_g_y;
    }

    for (c21_i176 = 0; c21_i176 < 4; c21_i176++) {
      c21_x_est[c21_i176] = c21_f_b[c21_i176];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c21_sfEvent, -59);
  _SFD_SYMBOL_SCOPE_POP();
  for (c21_i177 = 0; c21_i177 < 7; c21_i177++) {
    (*c21_b_x_est)[c21_i177] = c21_x_est[c21_i177];
  }

  for (c21_i178 = 0; c21_i178 < 49; c21_i178++) {
    (*c21_b_P_est)[c21_i178] = c21_P_est[c21_i178];
  }

  for (c21_i179 = 0; c21_i179 < 36; c21_i179++) {
    (*c21_b_PT_est)[c21_i179] = c21_PT_est[c21_i179];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c21_sfEvent);
}

static void initSimStructsc21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void registerMessagesc21_modelo_FK_simul_coleta_dados
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c21_machineNumber, uint32_T
  c21_chartNumber)
{
}

static const mxArray *c21_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i180;
  int32_T c21_i181;
  int32_T c21_i182;
  real_T c21_b_inData[36];
  int32_T c21_i183;
  int32_T c21_i184;
  int32_T c21_i185;
  real_T c21_u[36];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_i180 = 0;
  for (c21_i181 = 0; c21_i181 < 6; c21_i181++) {
    for (c21_i182 = 0; c21_i182 < 6; c21_i182++) {
      c21_b_inData[c21_i182 + c21_i180] = (*(real_T (*)[36])c21_inData)[c21_i182
        + c21_i180];
    }

    c21_i180 += 6;
  }

  c21_i183 = 0;
  for (c21_i184 = 0; c21_i184 < 6; c21_i184++) {
    for (c21_i185 = 0; c21_i185 < 6; c21_i185++) {
      c21_u[c21_i185 + c21_i183] = c21_b_inData[c21_i185 + c21_i183];
    }

    c21_i183 += 6;
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 2, 6, 6), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static void c21_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_PT_est, const char_T *c21_identifier, real_T c21_y[36])
{
  emlrtMsgIdentifier c21_thisId;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_PT_est), &c21_thisId,
    c21_y);
  sf_mex_destroy(&c21_PT_est);
}

static void c21_b_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[36])
{
  real_T c21_dv4[36];
  int32_T c21_i186;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv4, 1, 0, 0U, 1, 0U, 2, 6,
                6);
  for (c21_i186 = 0; c21_i186 < 36; c21_i186++) {
    c21_y[c21_i186] = c21_dv4[c21_i186];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_PT_est;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[36];
  int32_T c21_i187;
  int32_T c21_i188;
  int32_T c21_i189;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_PT_est = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_PT_est), &c21_thisId,
    c21_y);
  sf_mex_destroy(&c21_PT_est);
  c21_i187 = 0;
  for (c21_i188 = 0; c21_i188 < 6; c21_i188++) {
    for (c21_i189 = 0; c21_i189 < 6; c21_i189++) {
      (*(real_T (*)[36])c21_outData)[c21_i189 + c21_i187] = c21_y[c21_i189 +
        c21_i187];
    }

    c21_i187 += 6;
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static const mxArray *c21_b_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i190;
  int32_T c21_i191;
  int32_T c21_i192;
  real_T c21_b_inData[49];
  int32_T c21_i193;
  int32_T c21_i194;
  int32_T c21_i195;
  real_T c21_u[49];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_i190 = 0;
  for (c21_i191 = 0; c21_i191 < 7; c21_i191++) {
    for (c21_i192 = 0; c21_i192 < 7; c21_i192++) {
      c21_b_inData[c21_i192 + c21_i190] = (*(real_T (*)[49])c21_inData)[c21_i192
        + c21_i190];
    }

    c21_i190 += 7;
  }

  c21_i193 = 0;
  for (c21_i194 = 0; c21_i194 < 7; c21_i194++) {
    for (c21_i195 = 0; c21_i195 < 7; c21_i195++) {
      c21_u[c21_i195 + c21_i193] = c21_b_inData[c21_i195 + c21_i193];
    }

    c21_i193 += 7;
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 2, 7, 7), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static void c21_c_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_P_est, const char_T *c21_identifier, real_T c21_y[49])
{
  emlrtMsgIdentifier c21_thisId;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_P_est), &c21_thisId,
    c21_y);
  sf_mex_destroy(&c21_P_est);
}

static void c21_d_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[49])
{
  real_T c21_dv5[49];
  int32_T c21_i196;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv5, 1, 0, 0U, 1, 0U, 2, 7,
                7);
  for (c21_i196 = 0; c21_i196 < 49; c21_i196++) {
    c21_y[c21_i196] = c21_dv5[c21_i196];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_P_est;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[49];
  int32_T c21_i197;
  int32_T c21_i198;
  int32_T c21_i199;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_P_est = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_P_est), &c21_thisId,
    c21_y);
  sf_mex_destroy(&c21_P_est);
  c21_i197 = 0;
  for (c21_i198 = 0; c21_i198 < 7; c21_i198++) {
    for (c21_i199 = 0; c21_i199 < 7; c21_i199++) {
      (*(real_T (*)[49])c21_outData)[c21_i199 + c21_i197] = c21_y[c21_i199 +
        c21_i197];
    }

    c21_i197 += 7;
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static const mxArray *c21_c_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i200;
  real_T c21_b_inData[7];
  int32_T c21_i201;
  real_T c21_u[7];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  for (c21_i200 = 0; c21_i200 < 7; c21_i200++) {
    c21_b_inData[c21_i200] = (*(real_T (*)[7])c21_inData)[c21_i200];
  }

  for (c21_i201 = 0; c21_i201 < 7; c21_i201++) {
    c21_u[c21_i201] = c21_b_inData[c21_i201];
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 1, 7), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static void c21_e_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_x_est, const char_T *c21_identifier, real_T c21_y[7])
{
  emlrtMsgIdentifier c21_thisId;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_x_est), &c21_thisId,
    c21_y);
  sf_mex_destroy(&c21_x_est);
}

static void c21_f_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[7])
{
  real_T c21_dv6[7];
  int32_T c21_i202;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv6, 1, 0, 0U, 1, 0U, 1, 7);
  for (c21_i202 = 0; c21_i202 < 7; c21_i202++) {
    c21_y[c21_i202] = c21_dv6[c21_i202];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_x_est;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[7];
  int32_T c21_i203;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_x_est = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_x_est), &c21_thisId,
    c21_y);
  sf_mex_destroy(&c21_x_est);
  for (c21_i203 = 0; c21_i203 < 7; c21_i203++) {
    (*(real_T (*)[7])c21_outData)[c21_i203] = c21_y[c21_i203];
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static const mxArray *c21_d_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  real_T c21_u;
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_u = *(real_T *)c21_inData;
  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", &c21_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static const mxArray *c21_e_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i204;
  int32_T c21_i205;
  int32_T c21_i206;
  real_T c21_b_inData[9];
  int32_T c21_i207;
  int32_T c21_i208;
  int32_T c21_i209;
  real_T c21_u[9];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_i204 = 0;
  for (c21_i205 = 0; c21_i205 < 3; c21_i205++) {
    for (c21_i206 = 0; c21_i206 < 3; c21_i206++) {
      c21_b_inData[c21_i206 + c21_i204] = (*(real_T (*)[9])c21_inData)[c21_i206
        + c21_i204];
    }

    c21_i204 += 3;
  }

  c21_i207 = 0;
  for (c21_i208 = 0; c21_i208 < 3; c21_i208++) {
    for (c21_i209 = 0; c21_i209 < 3; c21_i209++) {
      c21_u[c21_i209 + c21_i207] = c21_b_inData[c21_i209 + c21_i207];
    }

    c21_i207 += 3;
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static const mxArray *c21_f_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i210;
  real_T c21_b_inData[4];
  int32_T c21_i211;
  real_T c21_u[4];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  for (c21_i210 = 0; c21_i210 < 4; c21_i210++) {
    c21_b_inData[c21_i210] = (*(real_T (*)[4])c21_inData)[c21_i210];
  }

  for (c21_i211 = 0; c21_i211 < 4; c21_i211++) {
    c21_u[c21_i211] = c21_b_inData[c21_i211];
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static real_T c21_g_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId)
{
  real_T c21_y;
  real_T c21_d0;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), &c21_d0, 1, 0, 0U, 0, 0U, 0);
  c21_y = c21_d0;
  sf_mex_destroy(&c21_u);
  return c21_y;
}

static void c21_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_nargout;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_nargout = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_y = c21_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_nargout),
    &c21_thisId);
  sf_mex_destroy(&c21_nargout);
  *(real_T *)c21_outData = c21_y;
  sf_mex_destroy(&c21_mxArrayInData);
}

static const mxArray *c21_g_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i212;
  int32_T c21_i213;
  int32_T c21_i214;
  real_T c21_b_inData[28];
  int32_T c21_i215;
  int32_T c21_i216;
  int32_T c21_i217;
  real_T c21_u[28];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_i212 = 0;
  for (c21_i213 = 0; c21_i213 < 4; c21_i213++) {
    for (c21_i214 = 0; c21_i214 < 7; c21_i214++) {
      c21_b_inData[c21_i214 + c21_i212] = (*(real_T (*)[28])c21_inData)[c21_i214
        + c21_i212];
    }

    c21_i212 += 7;
  }

  c21_i215 = 0;
  for (c21_i216 = 0; c21_i216 < 4; c21_i216++) {
    for (c21_i217 = 0; c21_i217 < 7; c21_i217++) {
      c21_u[c21_i217 + c21_i215] = c21_b_inData[c21_i217 + c21_i215];
    }

    c21_i215 += 7;
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 2, 7, 4), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static void c21_h_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[28])
{
  real_T c21_dv7[28];
  int32_T c21_i218;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv7, 1, 0, 0U, 1, 0U, 2, 7,
                4);
  for (c21_i218 = 0; c21_i218 < 28; c21_i218++) {
    c21_y[c21_i218] = c21_dv7[c21_i218];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_K;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[28];
  int32_T c21_i219;
  int32_T c21_i220;
  int32_T c21_i221;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_K = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_K), &c21_thisId, c21_y);
  sf_mex_destroy(&c21_K);
  c21_i219 = 0;
  for (c21_i220 = 0; c21_i220 < 4; c21_i220++) {
    for (c21_i221 = 0; c21_i221 < 7; c21_i221++) {
      (*(real_T (*)[28])c21_outData)[c21_i221 + c21_i219] = c21_y[c21_i221 +
        c21_i219];
    }

    c21_i219 += 7;
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static const mxArray *c21_h_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i222;
  int32_T c21_i223;
  int32_T c21_i224;
  real_T c21_b_inData[24];
  int32_T c21_i225;
  int32_T c21_i226;
  int32_T c21_i227;
  real_T c21_u[24];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_i222 = 0;
  for (c21_i223 = 0; c21_i223 < 4; c21_i223++) {
    for (c21_i224 = 0; c21_i224 < 6; c21_i224++) {
      c21_b_inData[c21_i224 + c21_i222] = (*(real_T (*)[24])c21_inData)[c21_i224
        + c21_i222];
    }

    c21_i222 += 6;
  }

  c21_i225 = 0;
  for (c21_i226 = 0; c21_i226 < 4; c21_i226++) {
    for (c21_i227 = 0; c21_i227 < 6; c21_i227++) {
      c21_u[c21_i227 + c21_i225] = c21_b_inData[c21_i227 + c21_i225];
    }

    c21_i225 += 6;
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 2, 6, 4), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static void c21_i_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[24])
{
  real_T c21_dv8[24];
  int32_T c21_i228;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv8, 1, 0, 0U, 1, 0U, 2, 6,
                4);
  for (c21_i228 = 0; c21_i228 < 24; c21_i228++) {
    c21_y[c21_i228] = c21_dv8[c21_i228];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_KT;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[24];
  int32_T c21_i229;
  int32_T c21_i230;
  int32_T c21_i231;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_KT = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_KT), &c21_thisId, c21_y);
  sf_mex_destroy(&c21_KT);
  c21_i229 = 0;
  for (c21_i230 = 0; c21_i230 < 4; c21_i230++) {
    for (c21_i231 = 0; c21_i231 < 6; c21_i231++) {
      (*(real_T (*)[24])c21_outData)[c21_i231 + c21_i229] = c21_y[c21_i231 +
        c21_i229];
    }

    c21_i229 += 6;
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static void c21_j_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[9])
{
  real_T c21_dv9[9];
  int32_T c21_i232;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv9, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c21_i232 = 0; c21_i232 < 9; c21_i232++) {
    c21_y[c21_i232] = c21_dv9[c21_i232];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_Pbt_prop;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[9];
  int32_T c21_i233;
  int32_T c21_i234;
  int32_T c21_i235;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_Pbt_prop = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_Pbt_prop), &c21_thisId,
    c21_y);
  sf_mex_destroy(&c21_Pbt_prop);
  c21_i233 = 0;
  for (c21_i234 = 0; c21_i234 < 3; c21_i234++) {
    for (c21_i235 = 0; c21_i235 < 3; c21_i235++) {
      (*(real_T (*)[9])c21_outData)[c21_i235 + c21_i233] = c21_y[c21_i235 +
        c21_i233];
    }

    c21_i233 += 3;
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static const mxArray *c21_i_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i236;
  int32_T c21_i237;
  int32_T c21_i238;
  real_T c21_b_inData[24];
  int32_T c21_i239;
  int32_T c21_i240;
  int32_T c21_i241;
  real_T c21_u[24];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_i236 = 0;
  for (c21_i237 = 0; c21_i237 < 6; c21_i237++) {
    for (c21_i238 = 0; c21_i238 < 4; c21_i238++) {
      c21_b_inData[c21_i238 + c21_i236] = (*(real_T (*)[24])c21_inData)[c21_i238
        + c21_i236];
    }

    c21_i236 += 4;
  }

  c21_i239 = 0;
  for (c21_i240 = 0; c21_i240 < 6; c21_i240++) {
    for (c21_i241 = 0; c21_i241 < 4; c21_i241++) {
      c21_u[c21_i241 + c21_i239] = c21_b_inData[c21_i241 + c21_i239];
    }

    c21_i239 += 4;
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 2, 4, 6), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static void c21_k_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[24])
{
  real_T c21_dv10[24];
  int32_T c21_i242;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv10, 1, 0, 0U, 1, 0U, 2, 4,
                6);
  for (c21_i242 = 0; c21_i242 < 24; c21_i242++) {
    c21_y[c21_i242] = c21_dv10[c21_i242];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_HT;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[24];
  int32_T c21_i243;
  int32_T c21_i244;
  int32_T c21_i245;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_HT = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_HT), &c21_thisId, c21_y);
  sf_mex_destroy(&c21_HT);
  c21_i243 = 0;
  for (c21_i244 = 0; c21_i244 < 6; c21_i244++) {
    for (c21_i245 = 0; c21_i245 < 4; c21_i245++) {
      (*(real_T (*)[24])c21_outData)[c21_i245 + c21_i243] = c21_y[c21_i245 +
        c21_i243];
    }

    c21_i243 += 4;
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static const mxArray *c21_j_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i246;
  int32_T c21_i247;
  int32_T c21_i248;
  real_T c21_b_inData[28];
  int32_T c21_i249;
  int32_T c21_i250;
  int32_T c21_i251;
  real_T c21_u[28];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_i246 = 0;
  for (c21_i247 = 0; c21_i247 < 7; c21_i247++) {
    for (c21_i248 = 0; c21_i248 < 4; c21_i248++) {
      c21_b_inData[c21_i248 + c21_i246] = (*(real_T (*)[28])c21_inData)[c21_i248
        + c21_i246];
    }

    c21_i246 += 4;
  }

  c21_i249 = 0;
  for (c21_i250 = 0; c21_i250 < 7; c21_i250++) {
    for (c21_i251 = 0; c21_i251 < 4; c21_i251++) {
      c21_u[c21_i251 + c21_i249] = c21_b_inData[c21_i251 + c21_i249];
    }

    c21_i249 += 4;
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 2, 4, 7), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static void c21_l_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[28])
{
  real_T c21_dv11[28];
  int32_T c21_i252;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv11, 1, 0, 0U, 1, 0U, 2, 4,
                7);
  for (c21_i252 = 0; c21_i252 < 28; c21_i252++) {
    c21_y[c21_i252] = c21_dv11[c21_i252];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_H;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[28];
  int32_T c21_i253;
  int32_T c21_i254;
  int32_T c21_i255;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_H = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_H), &c21_thisId, c21_y);
  sf_mex_destroy(&c21_H);
  c21_i253 = 0;
  for (c21_i254 = 0; c21_i254 < 7; c21_i254++) {
    for (c21_i255 = 0; c21_i255 < 4; c21_i255++) {
      (*(real_T (*)[28])c21_outData)[c21_i255 + c21_i253] = c21_y[c21_i255 +
        c21_i253];
    }

    c21_i253 += 4;
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static const mxArray *c21_k_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i256;
  int32_T c21_i257;
  int32_T c21_i258;
  real_T c21_b_inData[42];
  int32_T c21_i259;
  int32_T c21_i260;
  int32_T c21_i261;
  real_T c21_u[42];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_i256 = 0;
  for (c21_i257 = 0; c21_i257 < 6; c21_i257++) {
    for (c21_i258 = 0; c21_i258 < 7; c21_i258++) {
      c21_b_inData[c21_i258 + c21_i256] = (*(real_T (*)[42])c21_inData)[c21_i258
        + c21_i256];
    }

    c21_i256 += 7;
  }

  c21_i259 = 0;
  for (c21_i260 = 0; c21_i260 < 6; c21_i260++) {
    for (c21_i261 = 0; c21_i261 < 7; c21_i261++) {
      c21_u[c21_i261 + c21_i259] = c21_b_inData[c21_i261 + c21_i259];
    }

    c21_i259 += 7;
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 2, 7, 6), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static void c21_m_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[42])
{
  real_T c21_dv12[42];
  int32_T c21_i262;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv12, 1, 0, 0U, 1, 0U, 2, 7,
                6);
  for (c21_i262 = 0; c21_i262 < 42; c21_i262++) {
    c21_y[c21_i262] = c21_dv12[c21_i262];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_S;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[42];
  int32_T c21_i263;
  int32_T c21_i264;
  int32_T c21_i265;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_S = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_S), &c21_thisId, c21_y);
  sf_mex_destroy(&c21_S);
  c21_i263 = 0;
  for (c21_i264 = 0; c21_i264 < 6; c21_i264++) {
    for (c21_i265 = 0; c21_i265 < 7; c21_i265++) {
      (*(real_T (*)[42])c21_outData)[c21_i265 + c21_i263] = c21_y[c21_i265 +
        c21_i263];
    }

    c21_i263 += 7;
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static const mxArray *c21_l_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i266;
  int32_T c21_i267;
  int32_T c21_i268;
  real_T c21_b_inData[12];
  int32_T c21_i269;
  int32_T c21_i270;
  int32_T c21_i271;
  real_T c21_u[12];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_i266 = 0;
  for (c21_i267 = 0; c21_i267 < 3; c21_i267++) {
    for (c21_i268 = 0; c21_i268 < 4; c21_i268++) {
      c21_b_inData[c21_i268 + c21_i266] = (*(real_T (*)[12])c21_inData)[c21_i268
        + c21_i266];
    }

    c21_i266 += 4;
  }

  c21_i269 = 0;
  for (c21_i270 = 0; c21_i270 < 3; c21_i270++) {
    for (c21_i271 = 0; c21_i271 < 4; c21_i271++) {
      c21_u[c21_i271 + c21_i269] = c21_b_inData[c21_i271 + c21_i269];
    }

    c21_i269 += 4;
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 2, 4, 3), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static void c21_n_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[12])
{
  real_T c21_dv13[12];
  int32_T c21_i272;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv13, 1, 0, 0U, 1, 0U, 2, 4,
                3);
  for (c21_i272 = 0; c21_i272 < 12; c21_i272++) {
    c21_y[c21_i272] = c21_dv13[c21_i272];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_E;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[12];
  int32_T c21_i273;
  int32_T c21_i274;
  int32_T c21_i275;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_E = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_E), &c21_thisId, c21_y);
  sf_mex_destroy(&c21_E);
  c21_i273 = 0;
  for (c21_i274 = 0; c21_i274 < 3; c21_i274++) {
    for (c21_i275 = 0; c21_i275 < 4; c21_i275++) {
      (*(real_T (*)[12])c21_outData)[c21_i275 + c21_i273] = c21_y[c21_i275 +
        c21_i273];
    }

    c21_i273 += 4;
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static const mxArray *c21_m_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_i276;
  real_T c21_b_inData[3];
  int32_T c21_i277;
  real_T c21_u[3];
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  for (c21_i276 = 0; c21_i276 < 3; c21_i276++) {
    c21_b_inData[c21_i276] = (*(real_T (*)[3])c21_inData)[c21_i276];
  }

  for (c21_i277 = 0; c21_i277 < 3; c21_i277++) {
    c21_u[c21_i277] = c21_b_inData[c21_i277];
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static void c21_o_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[3])
{
  real_T c21_dv14[3];
  int32_T c21_i278;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv14, 1, 0, 0U, 1, 0U, 1, 3);
  for (c21_i278 = 0; c21_i278 < 3; c21_i278++) {
    c21_y[c21_i278] = c21_dv14[c21_i278];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_b_prop;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[3];
  int32_T c21_i279;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_b_prop = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_b_prop), &c21_thisId,
    c21_y);
  sf_mex_destroy(&c21_b_prop);
  for (c21_i279 = 0; c21_i279 < 3; c21_i279++) {
    (*(real_T (*)[3])c21_outData)[c21_i279] = c21_y[c21_i279];
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

static void c21_p_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, real_T c21_y[4])
{
  real_T c21_dv15[4];
  int32_T c21_i280;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_dv15, 1, 0, 0U, 1, 0U, 1, 4);
  for (c21_i280 = 0; c21_i280 < 4; c21_i280++) {
    c21_y[c21_i280] = c21_dv15[c21_i280];
  }

  sf_mex_destroy(&c21_u);
}

static void c21_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_q_prop;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  real_T c21_y[4];
  int32_T c21_i281;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_q_prop = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_q_prop), &c21_thisId,
    c21_y);
  sf_mex_destroy(&c21_q_prop);
  for (c21_i281 = 0; c21_i281 < 4; c21_i281++) {
    (*(real_T (*)[4])c21_outData)[c21_i281] = c21_y[c21_i281];
  }

  sf_mex_destroy(&c21_mxArrayInData);
}

const mxArray
  *sf_c21_modelo_FK_simul_coleta_dados_get_eml_resolved_functions_info(void)
{
  const mxArray *c21_nameCaptureInfo;
  c21_ResolvedFunctionInfo c21_info[97];
  const mxArray *c21_m0 = NULL;
  int32_T c21_i282;
  c21_ResolvedFunctionInfo *c21_r0;
  c21_nameCaptureInfo = NULL;
  c21_nameCaptureInfo = NULL;
  c21_info_helper(c21_info);
  c21_b_info_helper(c21_info);
  sf_mex_assign(&c21_m0, sf_mex_createstruct("nameCaptureInfo", 1, 97), FALSE);
  for (c21_i282 = 0; c21_i282 < 97; c21_i282++) {
    c21_r0 = &c21_info[c21_i282];
    sf_mex_addfield(c21_m0, sf_mex_create("nameCaptureInfo", c21_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c21_r0->context)), "context", "nameCaptureInfo",
                    c21_i282);
    sf_mex_addfield(c21_m0, sf_mex_create("nameCaptureInfo", c21_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c21_r0->name)), "name", "nameCaptureInfo",
                    c21_i282);
    sf_mex_addfield(c21_m0, sf_mex_create("nameCaptureInfo",
      c21_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c21_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c21_i282);
    sf_mex_addfield(c21_m0, sf_mex_create("nameCaptureInfo", c21_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c21_r0->resolved)), "resolved",
                    "nameCaptureInfo", c21_i282);
    sf_mex_addfield(c21_m0, sf_mex_create("nameCaptureInfo", &c21_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c21_i282);
    sf_mex_addfield(c21_m0, sf_mex_create("nameCaptureInfo", &c21_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c21_i282);
    sf_mex_addfield(c21_m0, sf_mex_create("nameCaptureInfo",
      &c21_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c21_i282);
    sf_mex_addfield(c21_m0, sf_mex_create("nameCaptureInfo",
      &c21_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c21_i282);
  }

  sf_mex_assign(&c21_nameCaptureInfo, c21_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c21_nameCaptureInfo);
  return c21_nameCaptureInfo;
}

static void c21_info_helper(c21_ResolvedFunctionInfo c21_info[97])
{
  c21_info[0].context = "";
  c21_info[0].name = "eye";
  c21_info[0].dominantType = "double";
  c21_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m";
  c21_info[0].fileTimeLo = 1286836688U;
  c21_info[0].fileTimeHi = 0U;
  c21_info[0].mFileTimeLo = 0U;
  c21_info[0].mFileTimeHi = 0U;
  c21_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c21_info[1].name = "eml_assert_valid_size_arg";
  c21_info[1].dominantType = "double";
  c21_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c21_info[1].fileTimeLo = 1286836694U;
  c21_info[1].fileTimeHi = 0U;
  c21_info[1].mFileTimeLo = 0U;
  c21_info[1].mFileTimeHi = 0U;
  c21_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c21_info[2].name = "isinf";
  c21_info[2].dominantType = "double";
  c21_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c21_info[2].fileTimeLo = 1286836760U;
  c21_info[2].fileTimeHi = 0U;
  c21_info[2].mFileTimeLo = 0U;
  c21_info[2].mFileTimeHi = 0U;
  c21_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c21_info[3].name = "mtimes";
  c21_info[3].dominantType = "double";
  c21_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c21_info[3].fileTimeLo = 1289530492U;
  c21_info[3].fileTimeHi = 0U;
  c21_info[3].mFileTimeLo = 0U;
  c21_info[3].mFileTimeHi = 0U;
  c21_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c21_info[4].name = "eml_index_class";
  c21_info[4].dominantType = "";
  c21_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[4].fileTimeLo = 1323181378U;
  c21_info[4].fileTimeHi = 0U;
  c21_info[4].mFileTimeLo = 0U;
  c21_info[4].mFileTimeHi = 0U;
  c21_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c21_info[5].name = "intmax";
  c21_info[5].dominantType = "char";
  c21_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c21_info[5].fileTimeLo = 1311273316U;
  c21_info[5].fileTimeHi = 0U;
  c21_info[5].mFileTimeLo = 0U;
  c21_info[5].mFileTimeHi = 0U;
  c21_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c21_info[6].name = "eml_is_float_class";
  c21_info[6].dominantType = "char";
  c21_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c21_info[6].fileTimeLo = 1286836782U;
  c21_info[6].fileTimeHi = 0U;
  c21_info[6].mFileTimeLo = 0U;
  c21_info[6].mFileTimeHi = 0U;
  c21_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c21_info[7].name = "min";
  c21_info[7].dominantType = "double";
  c21_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c21_info[7].fileTimeLo = 1311273318U;
  c21_info[7].fileTimeHi = 0U;
  c21_info[7].mFileTimeLo = 0U;
  c21_info[7].mFileTimeHi = 0U;
  c21_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c21_info[8].name = "eml_min_or_max";
  c21_info[8].dominantType = "char";
  c21_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c21_info[8].fileTimeLo = 1334089490U;
  c21_info[8].fileTimeHi = 0U;
  c21_info[8].mFileTimeLo = 0U;
  c21_info[8].mFileTimeHi = 0U;
  c21_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c21_info[9].name = "eml_scalar_eg";
  c21_info[9].dominantType = "double";
  c21_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c21_info[9].fileTimeLo = 1286836796U;
  c21_info[9].fileTimeHi = 0U;
  c21_info[9].mFileTimeLo = 0U;
  c21_info[9].mFileTimeHi = 0U;
  c21_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c21_info[10].name = "eml_scalexp_alloc";
  c21_info[10].dominantType = "double";
  c21_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c21_info[10].fileTimeLo = 1352435660U;
  c21_info[10].fileTimeHi = 0U;
  c21_info[10].mFileTimeLo = 0U;
  c21_info[10].mFileTimeHi = 0U;
  c21_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c21_info[11].name = "eml_index_class";
  c21_info[11].dominantType = "";
  c21_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[11].fileTimeLo = 1323181378U;
  c21_info[11].fileTimeHi = 0U;
  c21_info[11].mFileTimeLo = 0U;
  c21_info[11].mFileTimeHi = 0U;
  c21_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c21_info[12].name = "eml_scalar_eg";
  c21_info[12].dominantType = "double";
  c21_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c21_info[12].fileTimeLo = 1286836796U;
  c21_info[12].fileTimeHi = 0U;
  c21_info[12].mFileTimeLo = 0U;
  c21_info[12].mFileTimeHi = 0U;
  c21_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c21_info[13].name = "eml_index_class";
  c21_info[13].dominantType = "";
  c21_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[13].fileTimeLo = 1323181378U;
  c21_info[13].fileTimeHi = 0U;
  c21_info[13].mFileTimeLo = 0U;
  c21_info[13].mFileTimeHi = 0U;
  c21_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c21_info[14].name = "eml_int_forloop_overflow_check";
  c21_info[14].dominantType = "";
  c21_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c21_info[14].fileTimeLo = 1346528340U;
  c21_info[14].fileTimeHi = 0U;
  c21_info[14].mFileTimeLo = 0U;
  c21_info[14].mFileTimeHi = 0U;
  c21_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c21_info[15].name = "intmax";
  c21_info[15].dominantType = "char";
  c21_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c21_info[15].fileTimeLo = 1311273316U;
  c21_info[15].fileTimeHi = 0U;
  c21_info[15].mFileTimeLo = 0U;
  c21_info[15].mFileTimeHi = 0U;
  c21_info[16].context = "";
  c21_info[16].name = "mod";
  c21_info[16].dominantType = "double";
  c21_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  c21_info[16].fileTimeLo = 1343848382U;
  c21_info[16].fileTimeHi = 0U;
  c21_info[16].mFileTimeLo = 0U;
  c21_info[16].mFileTimeHi = 0U;
  c21_info[17].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  c21_info[17].name = "eml_scalar_eg";
  c21_info[17].dominantType = "double";
  c21_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c21_info[17].fileTimeLo = 1286836796U;
  c21_info[17].fileTimeHi = 0U;
  c21_info[17].mFileTimeLo = 0U;
  c21_info[17].mFileTimeHi = 0U;
  c21_info[18].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  c21_info[18].name = "eml_scalexp_alloc";
  c21_info[18].dominantType = "double";
  c21_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c21_info[18].fileTimeLo = 1352435660U;
  c21_info[18].fileTimeHi = 0U;
  c21_info[18].mFileTimeLo = 0U;
  c21_info[18].mFileTimeHi = 0U;
  c21_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c21_info[19].name = "eml_scalar_eg";
  c21_info[19].dominantType = "double";
  c21_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c21_info[19].fileTimeLo = 1286836796U;
  c21_info[19].fileTimeHi = 0U;
  c21_info[19].mFileTimeLo = 0U;
  c21_info[19].mFileTimeHi = 0U;
  c21_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c21_info[20].name = "eml_scalar_floor";
  c21_info[20].dominantType = "double";
  c21_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c21_info[20].fileTimeLo = 1286836726U;
  c21_info[20].fileTimeHi = 0U;
  c21_info[20].mFileTimeLo = 0U;
  c21_info[20].mFileTimeHi = 0U;
  c21_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c21_info[21].name = "eml_scalar_round";
  c21_info[21].dominantType = "double";
  c21_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m";
  c21_info[21].fileTimeLo = 1307669238U;
  c21_info[21].fileTimeHi = 0U;
  c21_info[21].mFileTimeLo = 0U;
  c21_info[21].mFileTimeHi = 0U;
  c21_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c21_info[22].name = "eml_scalar_abs";
  c21_info[22].dominantType = "double";
  c21_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c21_info[22].fileTimeLo = 1286836712U;
  c21_info[22].fileTimeHi = 0U;
  c21_info[22].mFileTimeLo = 0U;
  c21_info[22].mFileTimeHi = 0U;
  c21_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c21_info[23].name = "eps";
  c21_info[23].dominantType = "char";
  c21_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c21_info[23].fileTimeLo = 1326738796U;
  c21_info[23].fileTimeHi = 0U;
  c21_info[23].mFileTimeLo = 0U;
  c21_info[23].mFileTimeHi = 0U;
  c21_info[24].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c21_info[24].name = "eml_is_float_class";
  c21_info[24].dominantType = "char";
  c21_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c21_info[24].fileTimeLo = 1286836782U;
  c21_info[24].fileTimeHi = 0U;
  c21_info[24].mFileTimeLo = 0U;
  c21_info[24].mFileTimeHi = 0U;
  c21_info[25].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c21_info[25].name = "eml_eps";
  c21_info[25].dominantType = "char";
  c21_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c21_info[25].fileTimeLo = 1326738796U;
  c21_info[25].fileTimeHi = 0U;
  c21_info[25].mFileTimeLo = 0U;
  c21_info[25].mFileTimeHi = 0U;
  c21_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c21_info[26].name = "eml_float_model";
  c21_info[26].dominantType = "char";
  c21_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c21_info[26].fileTimeLo = 1326738796U;
  c21_info[26].fileTimeHi = 0U;
  c21_info[26].mFileTimeLo = 0U;
  c21_info[26].mFileTimeHi = 0U;
  c21_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c21_info[27].name = "mtimes";
  c21_info[27].dominantType = "double";
  c21_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c21_info[27].fileTimeLo = 1289530492U;
  c21_info[27].fileTimeHi = 0U;
  c21_info[27].mFileTimeLo = 0U;
  c21_info[27].mFileTimeHi = 0U;
  c21_info[28].context = "";
  c21_info[28].name = "mtimes";
  c21_info[28].dominantType = "double";
  c21_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c21_info[28].fileTimeLo = 1289530492U;
  c21_info[28].fileTimeHi = 0U;
  c21_info[28].mFileTimeLo = 0U;
  c21_info[28].mFileTimeHi = 0U;
  c21_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c21_info[29].name = "eml_index_class";
  c21_info[29].dominantType = "";
  c21_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[29].fileTimeLo = 1323181378U;
  c21_info[29].fileTimeHi = 0U;
  c21_info[29].mFileTimeLo = 0U;
  c21_info[29].mFileTimeHi = 0U;
  c21_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c21_info[30].name = "eml_scalar_eg";
  c21_info[30].dominantType = "double";
  c21_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c21_info[30].fileTimeLo = 1286836796U;
  c21_info[30].fileTimeHi = 0U;
  c21_info[30].mFileTimeLo = 0U;
  c21_info[30].mFileTimeHi = 0U;
  c21_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c21_info[31].name = "eml_xgemm";
  c21_info[31].dominantType = "char";
  c21_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c21_info[31].fileTimeLo = 1299091172U;
  c21_info[31].fileTimeHi = 0U;
  c21_info[31].mFileTimeLo = 0U;
  c21_info[31].mFileTimeHi = 0U;
  c21_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c21_info[32].name = "eml_blas_inline";
  c21_info[32].dominantType = "";
  c21_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c21_info[32].fileTimeLo = 1299091168U;
  c21_info[32].fileTimeHi = 0U;
  c21_info[32].mFileTimeLo = 0U;
  c21_info[32].mFileTimeHi = 0U;
  c21_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c21_info[33].name = "mtimes";
  c21_info[33].dominantType = "double";
  c21_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c21_info[33].fileTimeLo = 1289530492U;
  c21_info[33].fileTimeHi = 0U;
  c21_info[33].mFileTimeLo = 0U;
  c21_info[33].mFileTimeHi = 0U;
  c21_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c21_info[34].name = "eml_index_class";
  c21_info[34].dominantType = "";
  c21_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[34].fileTimeLo = 1323181378U;
  c21_info[34].fileTimeHi = 0U;
  c21_info[34].mFileTimeLo = 0U;
  c21_info[34].mFileTimeHi = 0U;
  c21_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c21_info[35].name = "eml_scalar_eg";
  c21_info[35].dominantType = "double";
  c21_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c21_info[35].fileTimeLo = 1286836796U;
  c21_info[35].fileTimeHi = 0U;
  c21_info[35].mFileTimeLo = 0U;
  c21_info[35].mFileTimeHi = 0U;
  c21_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c21_info[36].name = "eml_refblas_xgemm";
  c21_info[36].dominantType = "char";
  c21_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c21_info[36].fileTimeLo = 1299091174U;
  c21_info[36].fileTimeHi = 0U;
  c21_info[36].mFileTimeLo = 0U;
  c21_info[36].mFileTimeHi = 0U;
  c21_info[37].context = "";
  c21_info[37].name = "inv";
  c21_info[37].dominantType = "double";
  c21_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c21_info[37].fileTimeLo = 1305336000U;
  c21_info[37].fileTimeHi = 0U;
  c21_info[37].mFileTimeLo = 0U;
  c21_info[37].mFileTimeHi = 0U;
  c21_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c21_info[38].name = "eml_index_class";
  c21_info[38].dominantType = "";
  c21_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[38].fileTimeLo = 1323181378U;
  c21_info[38].fileTimeHi = 0U;
  c21_info[38].mFileTimeLo = 0U;
  c21_info[38].mFileTimeHi = 0U;
  c21_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c21_info[39].name = "abs";
  c21_info[39].dominantType = "double";
  c21_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c21_info[39].fileTimeLo = 1343848366U;
  c21_info[39].fileTimeHi = 0U;
  c21_info[39].mFileTimeLo = 0U;
  c21_info[39].mFileTimeHi = 0U;
  c21_info[40].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c21_info[40].name = "eml_scalar_abs";
  c21_info[40].dominantType = "double";
  c21_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c21_info[40].fileTimeLo = 1286836712U;
  c21_info[40].fileTimeHi = 0U;
  c21_info[40].mFileTimeLo = 0U;
  c21_info[40].mFileTimeHi = 0U;
  c21_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c21_info[41].name = "eml_div";
  c21_info[41].dominantType = "double";
  c21_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c21_info[41].fileTimeLo = 1313365810U;
  c21_info[41].fileTimeHi = 0U;
  c21_info[41].mFileTimeLo = 0U;
  c21_info[41].mFileTimeHi = 0U;
  c21_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c21_info[42].name = "mtimes";
  c21_info[42].dominantType = "double";
  c21_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c21_info[42].fileTimeLo = 1289530492U;
  c21_info[42].fileTimeHi = 0U;
  c21_info[42].mFileTimeLo = 0U;
  c21_info[42].mFileTimeHi = 0U;
  c21_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c21_info[43].name = "eml_index_plus";
  c21_info[43].dominantType = "double";
  c21_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c21_info[43].fileTimeLo = 1286836778U;
  c21_info[43].fileTimeHi = 0U;
  c21_info[43].mFileTimeLo = 0U;
  c21_info[43].mFileTimeHi = 0U;
  c21_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c21_info[44].name = "eml_index_class";
  c21_info[44].dominantType = "";
  c21_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[44].fileTimeLo = 1323181378U;
  c21_info[44].fileTimeHi = 0U;
  c21_info[44].mFileTimeLo = 0U;
  c21_info[44].mFileTimeHi = 0U;
  c21_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c21_info[45].name = "norm";
  c21_info[45].dominantType = "double";
  c21_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c21_info[45].fileTimeLo = 1336540094U;
  c21_info[45].fileTimeHi = 0U;
  c21_info[45].mFileTimeLo = 0U;
  c21_info[45].mFileTimeHi = 0U;
  c21_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c21_info[46].name = "abs";
  c21_info[46].dominantType = "double";
  c21_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c21_info[46].fileTimeLo = 1343848366U;
  c21_info[46].fileTimeHi = 0U;
  c21_info[46].mFileTimeLo = 0U;
  c21_info[46].mFileTimeHi = 0U;
  c21_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c21_info[47].name = "isnan";
  c21_info[47].dominantType = "double";
  c21_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c21_info[47].fileTimeLo = 1286836760U;
  c21_info[47].fileTimeHi = 0U;
  c21_info[47].mFileTimeLo = 0U;
  c21_info[47].mFileTimeHi = 0U;
  c21_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c21_info[48].name = "eml_guarded_nan";
  c21_info[48].dominantType = "char";
  c21_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c21_info[48].fileTimeLo = 1286836776U;
  c21_info[48].fileTimeHi = 0U;
  c21_info[48].mFileTimeLo = 0U;
  c21_info[48].mFileTimeHi = 0U;
  c21_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c21_info[49].name = "eml_is_float_class";
  c21_info[49].dominantType = "char";
  c21_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c21_info[49].fileTimeLo = 1286836782U;
  c21_info[49].fileTimeHi = 0U;
  c21_info[49].mFileTimeLo = 0U;
  c21_info[49].mFileTimeHi = 0U;
  c21_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c21_info[50].name = "mtimes";
  c21_info[50].dominantType = "double";
  c21_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c21_info[50].fileTimeLo = 1289530492U;
  c21_info[50].fileTimeHi = 0U;
  c21_info[50].mFileTimeLo = 0U;
  c21_info[50].mFileTimeHi = 0U;
  c21_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c21_info[51].name = "eml_warning";
  c21_info[51].dominantType = "char";
  c21_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c21_info[51].fileTimeLo = 1286836802U;
  c21_info[51].fileTimeHi = 0U;
  c21_info[51].mFileTimeLo = 0U;
  c21_info[51].mFileTimeHi = 0U;
  c21_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c21_info[52].name = "isnan";
  c21_info[52].dominantType = "double";
  c21_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c21_info[52].fileTimeLo = 1286836760U;
  c21_info[52].fileTimeHi = 0U;
  c21_info[52].mFileTimeLo = 0U;
  c21_info[52].mFileTimeHi = 0U;
  c21_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c21_info[53].name = "eps";
  c21_info[53].dominantType = "char";
  c21_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c21_info[53].fileTimeLo = 1326738796U;
  c21_info[53].fileTimeHi = 0U;
  c21_info[53].mFileTimeLo = 0U;
  c21_info[53].mFileTimeHi = 0U;
  c21_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c21_info[54].name = "eml_flt2str";
  c21_info[54].dominantType = "double";
  c21_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c21_info[54].fileTimeLo = 1309469196U;
  c21_info[54].fileTimeHi = 0U;
  c21_info[54].mFileTimeLo = 0U;
  c21_info[54].mFileTimeHi = 0U;
  c21_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c21_info[55].name = "char";
  c21_info[55].dominantType = "double";
  c21_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m";
  c21_info[55].fileTimeLo = 1319744368U;
  c21_info[55].fileTimeHi = 0U;
  c21_info[55].mFileTimeLo = 0U;
  c21_info[55].mFileTimeHi = 0U;
  c21_info[56].context = "";
  c21_info[56].name = "dot";
  c21_info[56].dominantType = "double";
  c21_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c21_info[56].fileTimeLo = 1313365816U;
  c21_info[56].fileTimeHi = 0U;
  c21_info[56].mFileTimeLo = 0U;
  c21_info[56].mFileTimeHi = 0U;
  c21_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c21_info[57].name = "isequal";
  c21_info[57].dominantType = "double";
  c21_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c21_info[57].fileTimeLo = 1286836758U;
  c21_info[57].fileTimeHi = 0U;
  c21_info[57].mFileTimeLo = 0U;
  c21_info[57].mFileTimeHi = 0U;
  c21_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c21_info[58].name = "eml_isequal_core";
  c21_info[58].dominantType = "double";
  c21_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c21_info[58].fileTimeLo = 1286836786U;
  c21_info[58].fileTimeHi = 0U;
  c21_info[58].mFileTimeLo = 0U;
  c21_info[58].mFileTimeHi = 0U;
  c21_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c21_info[59].name = "isnan";
  c21_info[59].dominantType = "double";
  c21_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c21_info[59].fileTimeLo = 1286836760U;
  c21_info[59].fileTimeHi = 0U;
  c21_info[59].mFileTimeLo = 0U;
  c21_info[59].mFileTimeHi = 0U;
  c21_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c21_info[60].name = "eml_index_class";
  c21_info[60].dominantType = "";
  c21_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[60].fileTimeLo = 1323181378U;
  c21_info[60].fileTimeHi = 0U;
  c21_info[60].mFileTimeLo = 0U;
  c21_info[60].mFileTimeHi = 0U;
  c21_info[61].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c21_info[61].name = "eml_scalar_eg";
  c21_info[61].dominantType = "double";
  c21_info[61].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c21_info[61].fileTimeLo = 1286836796U;
  c21_info[61].fileTimeHi = 0U;
  c21_info[61].mFileTimeLo = 0U;
  c21_info[61].mFileTimeHi = 0U;
  c21_info[62].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m!vdot";
  c21_info[62].name = "eml_xdotc";
  c21_info[62].dominantType = "double";
  c21_info[62].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c21_info[62].fileTimeLo = 1299091172U;
  c21_info[62].fileTimeHi = 0U;
  c21_info[62].mFileTimeLo = 0U;
  c21_info[62].mFileTimeHi = 0U;
  c21_info[63].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c21_info[63].name = "eml_blas_inline";
  c21_info[63].dominantType = "";
  c21_info[63].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c21_info[63].fileTimeLo = 1299091168U;
  c21_info[63].fileTimeHi = 0U;
  c21_info[63].mFileTimeLo = 0U;
  c21_info[63].mFileTimeHi = 0U;
}

static void c21_b_info_helper(c21_ResolvedFunctionInfo c21_info[97])
{
  c21_info[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c21_info[64].name = "eml_xdot";
  c21_info[64].dominantType = "double";
  c21_info[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c21_info[64].fileTimeLo = 1299091172U;
  c21_info[64].fileTimeHi = 0U;
  c21_info[64].mFileTimeLo = 0U;
  c21_info[64].mFileTimeHi = 0U;
  c21_info[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c21_info[65].name = "eml_blas_inline";
  c21_info[65].dominantType = "";
  c21_info[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c21_info[65].fileTimeLo = 1299091168U;
  c21_info[65].fileTimeHi = 0U;
  c21_info[65].mFileTimeLo = 0U;
  c21_info[65].mFileTimeHi = 0U;
  c21_info[66].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m!below_threshold";
  c21_info[66].name = "length";
  c21_info[66].dominantType = "double";
  c21_info[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c21_info[66].fileTimeLo = 1303164206U;
  c21_info[66].fileTimeHi = 0U;
  c21_info[66].mFileTimeLo = 0U;
  c21_info[66].mFileTimeHi = 0U;
  c21_info[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c21_info[67].name = "eml_index_class";
  c21_info[67].dominantType = "";
  c21_info[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[67].fileTimeLo = 1323181378U;
  c21_info[67].fileTimeHi = 0U;
  c21_info[67].mFileTimeLo = 0U;
  c21_info[67].mFileTimeHi = 0U;
  c21_info[68].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c21_info[68].name = "eml_refblas_xdot";
  c21_info[68].dominantType = "double";
  c21_info[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c21_info[68].fileTimeLo = 1299091172U;
  c21_info[68].fileTimeHi = 0U;
  c21_info[68].mFileTimeLo = 0U;
  c21_info[68].mFileTimeHi = 0U;
  c21_info[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c21_info[69].name = "eml_refblas_xdotx";
  c21_info[69].dominantType = "char";
  c21_info[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c21_info[69].fileTimeLo = 1299091174U;
  c21_info[69].fileTimeHi = 0U;
  c21_info[69].mFileTimeLo = 0U;
  c21_info[69].mFileTimeHi = 0U;
  c21_info[70].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c21_info[70].name = "eml_scalar_eg";
  c21_info[70].dominantType = "double";
  c21_info[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c21_info[70].fileTimeLo = 1286836796U;
  c21_info[70].fileTimeHi = 0U;
  c21_info[70].mFileTimeLo = 0U;
  c21_info[70].mFileTimeHi = 0U;
  c21_info[71].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c21_info[71].name = "eml_index_class";
  c21_info[71].dominantType = "";
  c21_info[71].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[71].fileTimeLo = 1323181378U;
  c21_info[71].fileTimeHi = 0U;
  c21_info[71].mFileTimeLo = 0U;
  c21_info[71].mFileTimeHi = 0U;
  c21_info[72].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c21_info[72].name = "eml_int_forloop_overflow_check";
  c21_info[72].dominantType = "";
  c21_info[72].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c21_info[72].fileTimeLo = 1346528340U;
  c21_info[72].fileTimeHi = 0U;
  c21_info[72].mFileTimeLo = 0U;
  c21_info[72].mFileTimeHi = 0U;
  c21_info[73].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c21_info[73].name = "eml_index_minus";
  c21_info[73].dominantType = "double";
  c21_info[73].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c21_info[73].fileTimeLo = 1286836778U;
  c21_info[73].fileTimeHi = 0U;
  c21_info[73].mFileTimeLo = 0U;
  c21_info[73].mFileTimeHi = 0U;
  c21_info[74].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c21_info[74].name = "eml_index_class";
  c21_info[74].dominantType = "";
  c21_info[74].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[74].fileTimeLo = 1323181378U;
  c21_info[74].fileTimeHi = 0U;
  c21_info[74].mFileTimeLo = 0U;
  c21_info[74].mFileTimeHi = 0U;
  c21_info[75].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c21_info[75].name = "eml_index_times";
  c21_info[75].dominantType = "coder.internal.indexInt";
  c21_info[75].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c21_info[75].fileTimeLo = 1286836780U;
  c21_info[75].fileTimeHi = 0U;
  c21_info[75].mFileTimeLo = 0U;
  c21_info[75].mFileTimeHi = 0U;
  c21_info[76].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c21_info[76].name = "eml_index_class";
  c21_info[76].dominantType = "";
  c21_info[76].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[76].fileTimeLo = 1323181378U;
  c21_info[76].fileTimeHi = 0U;
  c21_info[76].mFileTimeLo = 0U;
  c21_info[76].mFileTimeHi = 0U;
  c21_info[77].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c21_info[77].name = "eml_index_plus";
  c21_info[77].dominantType = "coder.internal.indexInt";
  c21_info[77].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c21_info[77].fileTimeLo = 1286836778U;
  c21_info[77].fileTimeHi = 0U;
  c21_info[77].mFileTimeLo = 0U;
  c21_info[77].mFileTimeHi = 0U;
  c21_info[78].context = "";
  c21_info[78].name = "norm";
  c21_info[78].dominantType = "double";
  c21_info[78].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c21_info[78].fileTimeLo = 1336540094U;
  c21_info[78].fileTimeHi = 0U;
  c21_info[78].mFileTimeLo = 0U;
  c21_info[78].mFileTimeHi = 0U;
  c21_info[79].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c21_info[79].name = "eml_index_class";
  c21_info[79].dominantType = "";
  c21_info[79].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[79].fileTimeLo = 1323181378U;
  c21_info[79].fileTimeHi = 0U;
  c21_info[79].mFileTimeLo = 0U;
  c21_info[79].mFileTimeHi = 0U;
  c21_info[80].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c21_info[80].name = "eml_xnrm2";
  c21_info[80].dominantType = "double";
  c21_info[80].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c21_info[80].fileTimeLo = 1299091176U;
  c21_info[80].fileTimeHi = 0U;
  c21_info[80].mFileTimeLo = 0U;
  c21_info[80].mFileTimeHi = 0U;
  c21_info[81].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c21_info[81].name = "eml_blas_inline";
  c21_info[81].dominantType = "";
  c21_info[81].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c21_info[81].fileTimeLo = 1299091168U;
  c21_info[81].fileTimeHi = 0U;
  c21_info[81].mFileTimeLo = 0U;
  c21_info[81].mFileTimeHi = 0U;
  c21_info[82].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c21_info[82].name = "eml_index_class";
  c21_info[82].dominantType = "";
  c21_info[82].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[82].fileTimeLo = 1323181378U;
  c21_info[82].fileTimeHi = 0U;
  c21_info[82].mFileTimeLo = 0U;
  c21_info[82].mFileTimeHi = 0U;
  c21_info[83].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c21_info[83].name = "eml_refblas_xnrm2";
  c21_info[83].dominantType = "double";
  c21_info[83].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c21_info[83].fileTimeLo = 1299091184U;
  c21_info[83].fileTimeHi = 0U;
  c21_info[83].mFileTimeLo = 0U;
  c21_info[83].mFileTimeHi = 0U;
  c21_info[84].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c21_info[84].name = "realmin";
  c21_info[84].dominantType = "char";
  c21_info[84].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c21_info[84].fileTimeLo = 1307669242U;
  c21_info[84].fileTimeHi = 0U;
  c21_info[84].mFileTimeLo = 0U;
  c21_info[84].mFileTimeHi = 0U;
  c21_info[85].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c21_info[85].name = "eml_realmin";
  c21_info[85].dominantType = "char";
  c21_info[85].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c21_info[85].fileTimeLo = 1307669244U;
  c21_info[85].fileTimeHi = 0U;
  c21_info[85].mFileTimeLo = 0U;
  c21_info[85].mFileTimeHi = 0U;
  c21_info[86].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c21_info[86].name = "eml_float_model";
  c21_info[86].dominantType = "char";
  c21_info[86].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c21_info[86].fileTimeLo = 1326738796U;
  c21_info[86].fileTimeHi = 0U;
  c21_info[86].mFileTimeLo = 0U;
  c21_info[86].mFileTimeHi = 0U;
  c21_info[87].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c21_info[87].name = "eml_index_class";
  c21_info[87].dominantType = "";
  c21_info[87].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c21_info[87].fileTimeLo = 1323181378U;
  c21_info[87].fileTimeHi = 0U;
  c21_info[87].mFileTimeLo = 0U;
  c21_info[87].mFileTimeHi = 0U;
  c21_info[88].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c21_info[88].name = "eml_index_minus";
  c21_info[88].dominantType = "double";
  c21_info[88].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c21_info[88].fileTimeLo = 1286836778U;
  c21_info[88].fileTimeHi = 0U;
  c21_info[88].mFileTimeLo = 0U;
  c21_info[88].mFileTimeHi = 0U;
  c21_info[89].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c21_info[89].name = "eml_index_times";
  c21_info[89].dominantType = "coder.internal.indexInt";
  c21_info[89].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c21_info[89].fileTimeLo = 1286836780U;
  c21_info[89].fileTimeHi = 0U;
  c21_info[89].mFileTimeLo = 0U;
  c21_info[89].mFileTimeHi = 0U;
  c21_info[90].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c21_info[90].name = "eml_index_plus";
  c21_info[90].dominantType = "coder.internal.indexInt";
  c21_info[90].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c21_info[90].fileTimeLo = 1286836778U;
  c21_info[90].fileTimeHi = 0U;
  c21_info[90].mFileTimeLo = 0U;
  c21_info[90].mFileTimeHi = 0U;
  c21_info[91].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c21_info[91].name = "eml_int_forloop_overflow_check";
  c21_info[91].dominantType = "";
  c21_info[91].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c21_info[91].fileTimeLo = 1346528340U;
  c21_info[91].fileTimeHi = 0U;
  c21_info[91].mFileTimeLo = 0U;
  c21_info[91].mFileTimeHi = 0U;
  c21_info[92].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c21_info[92].name = "abs";
  c21_info[92].dominantType = "double";
  c21_info[92].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c21_info[92].fileTimeLo = 1343848366U;
  c21_info[92].fileTimeHi = 0U;
  c21_info[92].mFileTimeLo = 0U;
  c21_info[92].mFileTimeHi = 0U;
  c21_info[93].context = "";
  c21_info[93].name = "mrdivide";
  c21_info[93].dominantType = "double";
  c21_info[93].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c21_info[93].fileTimeLo = 1357962348U;
  c21_info[93].fileTimeHi = 0U;
  c21_info[93].mFileTimeLo = 1319744366U;
  c21_info[93].mFileTimeHi = 0U;
  c21_info[94].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c21_info[94].name = "rdivide";
  c21_info[94].dominantType = "double";
  c21_info[94].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c21_info[94].fileTimeLo = 1346528388U;
  c21_info[94].fileTimeHi = 0U;
  c21_info[94].mFileTimeLo = 0U;
  c21_info[94].mFileTimeHi = 0U;
  c21_info[95].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c21_info[95].name = "eml_scalexp_compatible";
  c21_info[95].dominantType = "double";
  c21_info[95].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c21_info[95].fileTimeLo = 1286836796U;
  c21_info[95].fileTimeHi = 0U;
  c21_info[95].mFileTimeLo = 0U;
  c21_info[95].mFileTimeHi = 0U;
  c21_info[96].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c21_info[96].name = "eml_div";
  c21_info[96].dominantType = "double";
  c21_info[96].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c21_info[96].fileTimeLo = 1313365810U;
  c21_info[96].fileTimeHi = 0U;
  c21_info[96].mFileTimeLo = 0U;
  c21_info[96].mFileTimeHi = 0U;
}

static void c21_eye(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                    *chartInstance, real_T c21_I[9])
{
  int32_T c21_i283;
  int32_T c21_i;
  int32_T c21_b_i;
  for (c21_i283 = 0; c21_i283 < 9; c21_i283++) {
    c21_I[c21_i283] = 0.0;
  }

  for (c21_i = 1; c21_i < 4; c21_i++) {
    c21_b_i = c21_i;
    c21_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c21_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c21_b_i), 1, 3, 2, 0) - 1))
      - 1] = 1.0;
  }
}

static void c21_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static real_T c21_mod(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c21_x, real_T c21_y)
{
  real_T c21_r;
  real_T c21_xk;
  real_T c21_yk;
  real_T c21_b_x;
  real_T c21_b_y;
  real_T c21_c_x;
  real_T c21_d_x;
  real_T c21_e_x;
  real_T c21_f_x;
  real_T c21_g_x;
  real_T c21_h_x;
  real_T c21_i_x;
  real_T c21_c_y;
  real_T c21_j_x;
  real_T c21_d_y;
  real_T c21_b;
  real_T c21_e_y;
  real_T c21_k_x;
  real_T c21_l_x;
  c21_eml_scalar_eg(chartInstance);
  c21_xk = c21_x;
  c21_yk = c21_y;
  c21_b_x = c21_xk;
  c21_b_y = c21_yk;
  c21_eml_scalar_eg(chartInstance);
  if (c21_b_y == 0.0) {
    c21_r = c21_b_x;
  } else {
    c21_c_x = c21_b_y;
    c21_d_x = c21_c_x;
    c21_d_x = muDoubleScalarFloor(c21_d_x);
    if (c21_b_y == c21_d_x) {
      c21_e_x = c21_b_x / c21_b_y;
      c21_f_x = c21_e_x;
      c21_f_x = muDoubleScalarFloor(c21_f_x);
      c21_r = c21_b_x - c21_f_x * c21_b_y;
    } else {
      c21_r = c21_b_x / c21_b_y;
      c21_eps(chartInstance);
      c21_g_x = c21_r;
      c21_h_x = c21_g_x;
      c21_h_x = muDoubleScalarRound(c21_h_x);
      c21_i_x = c21_r - c21_h_x;
      c21_c_y = muDoubleScalarAbs(c21_i_x);
      c21_j_x = c21_r;
      c21_d_y = muDoubleScalarAbs(c21_j_x);
      c21_b = c21_d_y;
      c21_e_y = 2.2204460492503131E-16 * c21_b;
      if (c21_c_y <= c21_e_y) {
        c21_r = 0.0;
      } else {
        c21_k_x = c21_r;
        c21_l_x = c21_k_x;
        c21_l_x = muDoubleScalarFloor(c21_l_x);
        c21_r = (c21_r - c21_l_x) * c21_b_y;
      }
    }
  }

  return c21_r;
}

static void c21_eps(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                    *chartInstance)
{
}

static void c21_b_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c21_c_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c21_b_eye(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c21_I[16])
{
  int32_T c21_i284;
  int32_T c21_i;
  int32_T c21_b_i;
  for (c21_i284 = 0; c21_i284 < 16; c21_i284++) {
    c21_I[c21_i284] = 0.0;
  }

  for (c21_i = 1; c21_i < 5; c21_i++) {
    c21_b_i = c21_i;
    c21_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c21_b_i), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c21_b_i), 1, 4, 2, 0) - 1)
            << 2)) - 1] = 1.0;
  }
}

static void c21_inv(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                    *chartInstance, real_T c21_x[9], real_T c21_y[9])
{
  int32_T c21_i285;
  real_T c21_b_x[9];
  int32_T c21_i286;
  real_T c21_c_x[9];
  real_T c21_n1x;
  int32_T c21_i287;
  real_T c21_b_y[9];
  real_T c21_n1xinv;
  real_T c21_a;
  real_T c21_b;
  real_T c21_c_y;
  real_T c21_rc;
  real_T c21_d_x;
  boolean_T c21_b_b;
  real_T c21_e_x;
  int32_T c21_i288;
  static char_T c21_cv0[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  char_T c21_u[8];
  const mxArray *c21_d_y = NULL;
  real_T c21_b_u;
  const mxArray *c21_e_y = NULL;
  real_T c21_c_u;
  const mxArray *c21_f_y = NULL;
  real_T c21_d_u;
  const mxArray *c21_g_y = NULL;
  char_T c21_str[14];
  int32_T c21_i289;
  char_T c21_b_str[14];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  for (c21_i285 = 0; c21_i285 < 9; c21_i285++) {
    c21_b_x[c21_i285] = c21_x[c21_i285];
  }

  c21_inv3x3(chartInstance, c21_b_x, c21_y);
  for (c21_i286 = 0; c21_i286 < 9; c21_i286++) {
    c21_c_x[c21_i286] = c21_x[c21_i286];
  }

  c21_n1x = c21_norm(chartInstance, c21_c_x);
  for (c21_i287 = 0; c21_i287 < 9; c21_i287++) {
    c21_b_y[c21_i287] = c21_y[c21_i287];
  }

  c21_n1xinv = c21_norm(chartInstance, c21_b_y);
  c21_a = c21_n1x;
  c21_b = c21_n1xinv;
  c21_c_y = c21_a * c21_b;
  c21_rc = 1.0 / c21_c_y;
  guard1 = FALSE;
  guard2 = FALSE;
  if (c21_n1x == 0.0) {
    guard2 = TRUE;
  } else if (c21_n1xinv == 0.0) {
    guard2 = TRUE;
  } else if (c21_rc == 0.0) {
    guard1 = TRUE;
  } else {
    c21_d_x = c21_rc;
    c21_b_b = muDoubleScalarIsNaN(c21_d_x);
    guard3 = FALSE;
    if (c21_b_b) {
      guard3 = TRUE;
    } else {
      c21_eps(chartInstance);
      if (c21_rc < 2.2204460492503131E-16) {
        guard3 = TRUE;
      }
    }

    if (guard3 == TRUE) {
      c21_e_x = c21_rc;
      for (c21_i288 = 0; c21_i288 < 8; c21_i288++) {
        c21_u[c21_i288] = c21_cv0[c21_i288];
      }

      c21_d_y = NULL;
      sf_mex_assign(&c21_d_y, sf_mex_create("y", c21_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    FALSE);
      c21_b_u = 14.0;
      c21_e_y = NULL;
      sf_mex_assign(&c21_e_y, sf_mex_create("y", &c21_b_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c21_c_u = 6.0;
      c21_f_y = NULL;
      sf_mex_assign(&c21_f_y, sf_mex_create("y", &c21_c_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c21_d_u = c21_e_x;
      c21_g_y = NULL;
      sf_mex_assign(&c21_g_y, sf_mex_create("y", &c21_d_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c21_q_emlrt_marshallIn(chartInstance, sf_mex_call_debug("sprintf", 1U, 2U,
        14, sf_mex_call_debug("sprintf", 1U, 3U, 14, c21_d_y, 14, c21_e_y, 14,
        c21_f_y), 14, c21_g_y), "sprintf", c21_str);
      for (c21_i289 = 0; c21_i289 < 14; c21_i289++) {
        c21_b_str[c21_i289] = c21_str[c21_i289];
      }

      c21_b_eml_warning(chartInstance, c21_b_str);
    }
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c21_eml_warning(chartInstance);
  }
}

static void c21_inv3x3(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, real_T c21_x[9], real_T c21_y[9])
{
  int32_T c21_p1;
  int32_T c21_p2;
  int32_T c21_p3;
  real_T c21_b_x;
  real_T c21_c_x;
  real_T c21_absx11;
  real_T c21_d_x;
  real_T c21_e_x;
  real_T c21_absx21;
  real_T c21_f_x;
  real_T c21_g_x;
  real_T c21_absx31;
  real_T c21_t1;
  real_T c21_h_x;
  real_T c21_b_y;
  real_T c21_z;
  real_T c21_i_x;
  real_T c21_c_y;
  real_T c21_b_z;
  real_T c21_a;
  real_T c21_b;
  real_T c21_d_y;
  real_T c21_b_a;
  real_T c21_b_b;
  real_T c21_e_y;
  real_T c21_c_a;
  real_T c21_c_b;
  real_T c21_f_y;
  real_T c21_d_a;
  real_T c21_d_b;
  real_T c21_g_y;
  real_T c21_j_x;
  real_T c21_k_x;
  real_T c21_h_y;
  real_T c21_l_x;
  real_T c21_m_x;
  real_T c21_i_y;
  int32_T c21_itmp;
  real_T c21_n_x;
  real_T c21_j_y;
  real_T c21_c_z;
  real_T c21_e_a;
  real_T c21_e_b;
  real_T c21_k_y;
  real_T c21_f_a;
  real_T c21_f_b;
  real_T c21_l_y;
  real_T c21_o_x;
  real_T c21_m_y;
  real_T c21_t3;
  real_T c21_g_a;
  real_T c21_g_b;
  real_T c21_n_y;
  real_T c21_p_x;
  real_T c21_o_y;
  real_T c21_t2;
  int32_T c21_h_a;
  int32_T c21_c;
  real_T c21_i_a;
  real_T c21_h_b;
  real_T c21_p_y;
  real_T c21_j_a;
  real_T c21_i_b;
  real_T c21_q_y;
  real_T c21_q_x;
  real_T c21_r_y;
  real_T c21_d_z;
  int32_T c21_k_a;
  int32_T c21_b_c;
  int32_T c21_l_a;
  int32_T c21_c_c;
  real_T c21_r_x;
  real_T c21_s_y;
  real_T c21_m_a;
  real_T c21_j_b;
  real_T c21_t_y;
  real_T c21_s_x;
  real_T c21_u_y;
  int32_T c21_n_a;
  int32_T c21_d_c;
  real_T c21_o_a;
  real_T c21_k_b;
  real_T c21_v_y;
  real_T c21_p_a;
  real_T c21_l_b;
  real_T c21_w_y;
  real_T c21_t_x;
  real_T c21_x_y;
  real_T c21_e_z;
  int32_T c21_q_a;
  int32_T c21_e_c;
  int32_T c21_r_a;
  int32_T c21_f_c;
  real_T c21_y_y;
  real_T c21_s_a;
  real_T c21_m_b;
  real_T c21_ab_y;
  real_T c21_u_x;
  real_T c21_bb_y;
  int32_T c21_t_a;
  int32_T c21_g_c;
  real_T c21_u_a;
  real_T c21_n_b;
  real_T c21_cb_y;
  real_T c21_v_a;
  real_T c21_o_b;
  real_T c21_db_y;
  real_T c21_v_x;
  real_T c21_eb_y;
  real_T c21_f_z;
  int32_T c21_w_a;
  int32_T c21_h_c;
  int32_T c21_x_a;
  int32_T c21_i_c;
  boolean_T guard1 = FALSE;
  c21_p1 = 0;
  c21_p2 = 3;
  c21_p3 = 6;
  c21_b_x = c21_x[0];
  c21_c_x = c21_b_x;
  c21_absx11 = muDoubleScalarAbs(c21_c_x);
  c21_d_x = c21_x[1];
  c21_e_x = c21_d_x;
  c21_absx21 = muDoubleScalarAbs(c21_e_x);
  c21_f_x = c21_x[2];
  c21_g_x = c21_f_x;
  c21_absx31 = muDoubleScalarAbs(c21_g_x);
  guard1 = FALSE;
  if (c21_absx21 > c21_absx11) {
    if (c21_absx21 > c21_absx31) {
      c21_p1 = 3;
      c21_p2 = 0;
      c21_t1 = c21_x[0];
      c21_x[0] = c21_x[1];
      c21_x[1] = c21_t1;
      c21_t1 = c21_x[3];
      c21_x[3] = c21_x[4];
      c21_x[4] = c21_t1;
      c21_t1 = c21_x[6];
      c21_x[6] = c21_x[7];
      c21_x[7] = c21_t1;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    if (c21_absx31 > c21_absx11) {
      c21_p1 = 6;
      c21_p3 = 0;
      c21_t1 = c21_x[0];
      c21_x[0] = c21_x[2];
      c21_x[2] = c21_t1;
      c21_t1 = c21_x[3];
      c21_x[3] = c21_x[5];
      c21_x[5] = c21_t1;
      c21_t1 = c21_x[6];
      c21_x[6] = c21_x[8];
      c21_x[8] = c21_t1;
    }
  }

  c21_h_x = c21_x[1];
  c21_b_y = c21_x[0];
  c21_z = c21_h_x / c21_b_y;
  c21_x[1] = c21_z;
  c21_i_x = c21_x[2];
  c21_c_y = c21_x[0];
  c21_b_z = c21_i_x / c21_c_y;
  c21_x[2] = c21_b_z;
  c21_a = c21_x[1];
  c21_b = c21_x[3];
  c21_d_y = c21_a * c21_b;
  c21_x[4] -= c21_d_y;
  c21_b_a = c21_x[2];
  c21_b_b = c21_x[3];
  c21_e_y = c21_b_a * c21_b_b;
  c21_x[5] -= c21_e_y;
  c21_c_a = c21_x[1];
  c21_c_b = c21_x[6];
  c21_f_y = c21_c_a * c21_c_b;
  c21_x[7] -= c21_f_y;
  c21_d_a = c21_x[2];
  c21_d_b = c21_x[6];
  c21_g_y = c21_d_a * c21_d_b;
  c21_x[8] -= c21_g_y;
  c21_j_x = c21_x[5];
  c21_k_x = c21_j_x;
  c21_h_y = muDoubleScalarAbs(c21_k_x);
  c21_l_x = c21_x[4];
  c21_m_x = c21_l_x;
  c21_i_y = muDoubleScalarAbs(c21_m_x);
  if (c21_h_y > c21_i_y) {
    c21_itmp = c21_p2;
    c21_p2 = c21_p3;
    c21_p3 = c21_itmp;
    c21_t1 = c21_x[1];
    c21_x[1] = c21_x[2];
    c21_x[2] = c21_t1;
    c21_t1 = c21_x[4];
    c21_x[4] = c21_x[5];
    c21_x[5] = c21_t1;
    c21_t1 = c21_x[7];
    c21_x[7] = c21_x[8];
    c21_x[8] = c21_t1;
  }

  c21_n_x = c21_x[5];
  c21_j_y = c21_x[4];
  c21_c_z = c21_n_x / c21_j_y;
  c21_x[5] = c21_c_z;
  c21_e_a = c21_x[5];
  c21_e_b = c21_x[7];
  c21_k_y = c21_e_a * c21_e_b;
  c21_x[8] -= c21_k_y;
  c21_f_a = c21_x[5];
  c21_f_b = c21_x[1];
  c21_l_y = c21_f_a * c21_f_b;
  c21_o_x = c21_l_y - c21_x[2];
  c21_m_y = c21_x[8];
  c21_t3 = c21_o_x / c21_m_y;
  c21_g_a = c21_x[7];
  c21_g_b = c21_t3;
  c21_n_y = c21_g_a * c21_g_b;
  c21_p_x = -(c21_x[1] + c21_n_y);
  c21_o_y = c21_x[4];
  c21_t2 = c21_p_x / c21_o_y;
  c21_h_a = c21_p1 + 1;
  c21_c = c21_h_a;
  c21_i_a = c21_x[3];
  c21_h_b = c21_t2;
  c21_p_y = c21_i_a * c21_h_b;
  c21_j_a = c21_x[6];
  c21_i_b = c21_t3;
  c21_q_y = c21_j_a * c21_i_b;
  c21_q_x = (1.0 - c21_p_y) - c21_q_y;
  c21_r_y = c21_x[0];
  c21_d_z = c21_q_x / c21_r_y;
  c21_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c21_c), 1, 9, 1, 0) - 1] = c21_d_z;
  c21_k_a = c21_p1 + 2;
  c21_b_c = c21_k_a;
  c21_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c21_b_c), 1, 9, 1, 0) - 1] = c21_t2;
  c21_l_a = c21_p1 + 3;
  c21_c_c = c21_l_a;
  c21_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c21_c_c), 1, 9, 1, 0) - 1] = c21_t3;
  c21_r_x = -c21_x[5];
  c21_s_y = c21_x[8];
  c21_t3 = c21_r_x / c21_s_y;
  c21_m_a = c21_x[7];
  c21_j_b = c21_t3;
  c21_t_y = c21_m_a * c21_j_b;
  c21_s_x = 1.0 - c21_t_y;
  c21_u_y = c21_x[4];
  c21_t2 = c21_s_x / c21_u_y;
  c21_n_a = c21_p2 + 1;
  c21_d_c = c21_n_a;
  c21_o_a = c21_x[3];
  c21_k_b = c21_t2;
  c21_v_y = c21_o_a * c21_k_b;
  c21_p_a = c21_x[6];
  c21_l_b = c21_t3;
  c21_w_y = c21_p_a * c21_l_b;
  c21_t_x = -(c21_v_y + c21_w_y);
  c21_x_y = c21_x[0];
  c21_e_z = c21_t_x / c21_x_y;
  c21_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c21_d_c), 1, 9, 1, 0) - 1] = c21_e_z;
  c21_q_a = c21_p2 + 2;
  c21_e_c = c21_q_a;
  c21_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c21_e_c), 1, 9, 1, 0) - 1] = c21_t2;
  c21_r_a = c21_p2 + 3;
  c21_f_c = c21_r_a;
  c21_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c21_f_c), 1, 9, 1, 0) - 1] = c21_t3;
  c21_y_y = c21_x[8];
  c21_t3 = 1.0 / c21_y_y;
  c21_s_a = -c21_x[7];
  c21_m_b = c21_t3;
  c21_ab_y = c21_s_a * c21_m_b;
  c21_u_x = c21_ab_y;
  c21_bb_y = c21_x[4];
  c21_t2 = c21_u_x / c21_bb_y;
  c21_t_a = c21_p3 + 1;
  c21_g_c = c21_t_a;
  c21_u_a = c21_x[3];
  c21_n_b = c21_t2;
  c21_cb_y = c21_u_a * c21_n_b;
  c21_v_a = c21_x[6];
  c21_o_b = c21_t3;
  c21_db_y = c21_v_a * c21_o_b;
  c21_v_x = -(c21_cb_y + c21_db_y);
  c21_eb_y = c21_x[0];
  c21_f_z = c21_v_x / c21_eb_y;
  c21_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c21_g_c), 1, 9, 1, 0) - 1] = c21_f_z;
  c21_w_a = c21_p3 + 2;
  c21_h_c = c21_w_a;
  c21_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c21_h_c), 1, 9, 1, 0) - 1] = c21_t2;
  c21_x_a = c21_p3 + 3;
  c21_i_c = c21_x_a;
  c21_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c21_i_c), 1, 9, 1, 0) - 1] = c21_t3;
}

static real_T c21_norm(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, real_T c21_x[9])
{
  real_T c21_y;
  int32_T c21_j;
  real_T c21_b_j;
  real_T c21_s;
  int32_T c21_i;
  real_T c21_b_i;
  real_T c21_b_x;
  real_T c21_c_x;
  real_T c21_b_y;
  real_T c21_d_x;
  boolean_T c21_b;
  boolean_T exitg1;
  c21_y = 0.0;
  c21_j = 0;
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (c21_j < 3)) {
    c21_b_j = 1.0 + (real_T)c21_j;
    c21_s = 0.0;
    for (c21_i = 0; c21_i < 3; c21_i++) {
      c21_b_i = 1.0 + (real_T)c21_i;
      c21_b_x = c21_x[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c21_b_i), 1, 3, 1, 0) + 3 * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c21_b_j),
        1, 3, 2, 0) - 1)) - 1];
      c21_c_x = c21_b_x;
      c21_b_y = muDoubleScalarAbs(c21_c_x);
      c21_s += c21_b_y;
    }

    c21_d_x = c21_s;
    c21_b = muDoubleScalarIsNaN(c21_d_x);
    if (c21_b) {
      c21_y = rtNaN;
      exitg1 = TRUE;
    } else {
      if (c21_s > c21_y) {
        c21_y = c21_s;
      }

      c21_j++;
    }
  }

  return c21_y;
}

static void c21_eml_warning(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
  int32_T c21_i290;
  static char_T c21_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c21_u[27];
  const mxArray *c21_y = NULL;
  for (c21_i290 = 0; c21_i290 < 27; c21_i290++) {
    c21_u[c21_i290] = c21_varargin_1[c21_i290];
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 10, 0U, 1U, 0U, 2, 1, 27),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c21_y));
}

static void c21_b_eml_warning(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, char_T c21_varargin_2[14])
{
  int32_T c21_i291;
  static char_T c21_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c21_u[33];
  const mxArray *c21_y = NULL;
  int32_T c21_i292;
  char_T c21_b_u[14];
  const mxArray *c21_b_y = NULL;
  for (c21_i291 = 0; c21_i291 < 33; c21_i291++) {
    c21_u[c21_i291] = c21_varargin_1[c21_i291];
  }

  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", c21_u, 10, 0U, 1U, 0U, 2, 1, 33),
                FALSE);
  for (c21_i292 = 0; c21_i292 < 14; c21_i292++) {
    c21_b_u[c21_i292] = c21_varargin_2[c21_i292];
  }

  c21_b_y = NULL;
  sf_mex_assign(&c21_b_y, sf_mex_create("y", c21_b_u, 10, 0U, 1U, 0U, 2, 1, 14),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
    14, c21_y, 14, c21_b_y));
}

static void c21_d_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c21_e_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c21_f_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c21_g_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c21_h_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static real_T c21_dot(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c21_a[4], real_T c21_b[4])
{
  real_T c21_c;
  int32_T c21_k;
  int32_T c21_b_k;
  c21_i_eml_scalar_eg(chartInstance);
  c21_i_eml_scalar_eg(chartInstance);
  c21_c = 0.0;
  for (c21_k = 1; c21_k < 5; c21_k++) {
    c21_b_k = c21_k;
    c21_c += c21_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
      "", (real_T)c21_b_k), 1, 4, 1, 0) - 1] * c21_b[_SFD_EML_ARRAY_BOUNDS_CHECK
      ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c21_b_k), 1, 4, 1, 0) - 1];
  }

  return c21_c;
}

static void c21_i_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c21_j_eml_scalar_eg(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c21_q_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_sprintf, const char_T *c21_identifier, char_T c21_y[14])
{
  emlrtMsgIdentifier c21_thisId;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_sprintf), &c21_thisId,
    c21_y);
  sf_mex_destroy(&c21_sprintf);
}

static void c21_r_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId, char_T c21_y[14])
{
  char_T c21_cv1[14];
  int32_T c21_i293;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), c21_cv1, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c21_i293 = 0; c21_i293 < 14; c21_i293++) {
    c21_y[c21_i293] = c21_cv1[c21_i293];
  }

  sf_mex_destroy(&c21_u);
}

static const mxArray *c21_n_sf_marshallOut(void *chartInstanceVoid, void
  *c21_inData)
{
  const mxArray *c21_mxArrayOutData = NULL;
  int32_T c21_u;
  const mxArray *c21_y = NULL;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_mxArrayOutData = NULL;
  c21_u = *(int32_T *)c21_inData;
  c21_y = NULL;
  sf_mex_assign(&c21_y, sf_mex_create("y", &c21_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c21_mxArrayOutData, c21_y, FALSE);
  return c21_mxArrayOutData;
}

static int32_T c21_s_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId)
{
  int32_T c21_y;
  int32_T c21_i294;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), &c21_i294, 1, 6, 0U, 0, 0U, 0);
  c21_y = c21_i294;
  sf_mex_destroy(&c21_u);
  return c21_y;
}

static void c21_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c21_mxArrayInData, const char_T *c21_varName, void *c21_outData)
{
  const mxArray *c21_b_sfEvent;
  const char_T *c21_identifier;
  emlrtMsgIdentifier c21_thisId;
  int32_T c21_y;
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c21_b_sfEvent = sf_mex_dup(c21_mxArrayInData);
  c21_identifier = c21_varName;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_y = c21_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c21_b_sfEvent),
    &c21_thisId);
  sf_mex_destroy(&c21_b_sfEvent);
  *(int32_T *)c21_outData = c21_y;
  sf_mex_destroy(&c21_mxArrayInData);
}

static uint8_T c21_t_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_b_is_active_c21_modelo_FK_simul_coleta_dados, const char_T
   *c21_identifier)
{
  uint8_T c21_y;
  emlrtMsgIdentifier c21_thisId;
  c21_thisId.fIdentifier = c21_identifier;
  c21_thisId.fParent = NULL;
  c21_y = c21_u_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c21_b_is_active_c21_modelo_FK_simul_coleta_dados), &c21_thisId);
  sf_mex_destroy(&c21_b_is_active_c21_modelo_FK_simul_coleta_dados);
  return c21_y;
}

static uint8_T c21_u_emlrt_marshallIn
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c21_u, const emlrtMsgIdentifier *c21_parentId)
{
  uint8_T c21_y;
  uint8_T c21_u0;
  sf_mex_import(c21_parentId, sf_mex_dup(c21_u), &c21_u0, 1, 3, 0U, 0, 0U, 0);
  c21_y = c21_u0;
  sf_mex_destroy(&c21_u);
  return c21_y;
}

static void init_dsm_address_info
  (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
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

void sf_c21_modelo_FK_simul_coleta_dados_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1196827906U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(640534406U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2459932724U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4190799641U);
}

mxArray *sf_c21_modelo_FK_simul_coleta_dados_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("9W03y0qqIyJVraHQsj9DUE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
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
      pr[0] = (double)(6);
      pr[1] = (double)(6);
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
      pr[0] = (double)(4);
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
      pr[1] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
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
      pr[0] = (double)(7);
      pr[1] = (double)(7);
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
      pr[0] = (double)(6);
      pr[1] = (double)(6);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c21_modelo_FK_simul_coleta_dados_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c21_modelo_FK_simul_coleta_dados
  (void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[10],T\"PT_est\",},{M[1],M[9],T\"P_est\",},{M[1],M[5],T\"x_est\",},{M[8],M[0],T\"is_active_c21_modelo_FK_simul_coleta_dados\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c21_modelo_FK_simul_coleta_dados_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
    chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modelo_FK_simul_coleta_dadosMachineNumber_,
           21,
           1,
           1,
           8,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"x_prop");
          _SFD_SET_DATA_PROPS(1,2,0,1,"x_est");
          _SFD_SET_DATA_PROPS(2,1,1,0,"PT_prop");
          _SFD_SET_DATA_PROPS(3,1,1,0,"q_obs");
          _SFD_SET_DATA_PROPS(4,1,1,0,"R");
          _SFD_SET_DATA_PROPS(5,2,0,1,"P_est");
          _SFD_SET_DATA_PROPS(6,2,0,1,"PT_est");
          _SFD_SET_DATA_PROPS(7,1,1,0,"i");
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
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1448);
        _SFD_CV_INIT_EML_IF(0,1,0,474,492,570,1448);
        _SFD_CV_INIT_EML_IF(0,1,1,1174,1199,1219,1247);
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
          dimVector[0]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c21_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c21_c_sf_marshallOut,(MexInFcnForType)
            c21_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c21_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c21_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c21_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 7;
          dimVector[1]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c21_b_sf_marshallOut,(MexInFcnForType)
            c21_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c21_sf_marshallOut,(MexInFcnForType)
            c21_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c21_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c21_i;
          real_T (*c21_x_prop)[7];
          real_T (*c21_x_est)[7];
          real_T (*c21_PT_prop)[36];
          real_T (*c21_q_obs)[4];
          real_T (*c21_R)[9];
          real_T (*c21_P_est)[49];
          real_T (*c21_PT_est)[36];
          c21_i = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c21_PT_est = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
          c21_P_est = (real_T (*)[49])ssGetOutputPortSignal(chartInstance->S, 2);
          c21_R = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 3);
          c21_q_obs = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
          c21_PT_prop = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 1);
          c21_x_est = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
          c21_x_prop = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c21_x_prop);
          _SFD_SET_DATA_VALUE_PTR(1U, *c21_x_est);
          _SFD_SET_DATA_VALUE_PTR(2U, *c21_PT_prop);
          _SFD_SET_DATA_VALUE_PTR(3U, *c21_q_obs);
          _SFD_SET_DATA_VALUE_PTR(4U, *c21_R);
          _SFD_SET_DATA_VALUE_PTR(5U, *c21_P_est);
          _SFD_SET_DATA_VALUE_PTR(6U, *c21_PT_est);
          _SFD_SET_DATA_VALUE_PTR(7U, c21_i);
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
  return "72mB3CZilmQNZ6MEOrAgeB";
}

static void sf_opaque_initialize_c21_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c21_modelo_FK_simul_coleta_dados
    ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
  initialize_c21_modelo_FK_simul_coleta_dados
    ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c21_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  enable_c21_modelo_FK_simul_coleta_dados
    ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c21_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  disable_c21_modelo_FK_simul_coleta_dados
    ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c21_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  sf_c21_modelo_FK_simul_coleta_dados
    ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c21_modelo_FK_simul_coleta_dados
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c21_modelo_FK_simul_coleta_dados
    ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c21_modelo_FK_simul_coleta_dados();/* state var info */
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

extern void sf_internal_set_sim_state_c21_modelo_FK_simul_coleta_dados(SimStruct*
  S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c21_modelo_FK_simul_coleta_dados();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c21_modelo_FK_simul_coleta_dados
    ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c21_modelo_FK_simul_coleta_dados
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c21_modelo_FK_simul_coleta_dados(S);
}

static void sf_opaque_set_sim_state_c21_modelo_FK_simul_coleta_dados(SimStruct*
  S, const mxArray *st)
{
  sf_internal_set_sim_state_c21_modelo_FK_simul_coleta_dados(S, st);
}

static void sf_opaque_terminate_c21_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_FK_simul_coleta_dados_optimization_info();
    }

    finalize_c21_modelo_FK_simul_coleta_dados
      ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc21_modelo_FK_simul_coleta_dados
    ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c21_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c21_modelo_FK_simul_coleta_dados
      ((SFc21_modelo_FK_simul_coleta_dadosInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c21_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_modelo_FK_simul_coleta_dados_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      21);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,21,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,21,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,21);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,21,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,21,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,21);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2394509686U));
  ssSetChecksum1(S,(2504078350U));
  ssSetChecksum2(S,(2908107174U));
  ssSetChecksum3(S,(3576201219U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c21_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c21_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct *)utMalloc
    (sizeof(SFc21_modelo_FK_simul_coleta_dadosInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc21_modelo_FK_simul_coleta_dadosInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c21_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c21_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c21_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c21_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c21_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c21_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c21_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c21_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c21_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.mdlStart = mdlStart_c21_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c21_modelo_FK_simul_coleta_dados;
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

void c21_modelo_FK_simul_coleta_dados_method_dispatcher(SimStruct *S, int_T
  method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c21_modelo_FK_simul_coleta_dados(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c21_modelo_FK_simul_coleta_dados(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c21_modelo_FK_simul_coleta_dados(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c21_modelo_FK_simul_coleta_dados_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
