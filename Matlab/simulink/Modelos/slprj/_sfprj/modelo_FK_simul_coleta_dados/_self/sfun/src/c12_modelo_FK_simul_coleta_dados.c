/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_FK_simul_coleta_dados_sfun.h"
#include "c12_modelo_FK_simul_coleta_dados.h"
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
static const char * c12_debug_family_names[8] = { "S", "nargin", "nargout", "w",
  "vs", "vo", "vn", "wr" };

/* Function Declarations */
static void initialize_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void initialize_params_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void enable_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void disable_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c12_update_debugger_state_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void set_sim_state_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_st);
static void finalize_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void sf_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c12_chartstep_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void initSimStructsc12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void registerMessagesc12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber);
static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_wr, const char_T *c12_identifier, real_T c12_y[3]);
static void c12_b_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, real_T c12_y[3]);
static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static real_T c12_c_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_d_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, real_T c12_y[9]);
static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static void c12_info_helper(c12_ResolvedFunctionInfo c12_info[60]);
static void c12_eml_scalar_eg(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c12_randn(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c12_r[3]);
static void c12_eml_rand_mcg16807
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state, uint32_T *c12_f_state, real_T *c12_r);
static void c12_genrandu(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, uint32_T c12_s, uint32_T *c12_e_state, real_T *c12_r);
static void c12_eml_rand_shr3cong
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state[2], uint32_T c12_f_state[2], real_T *c12_r);
static real_T c12_abs(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c12_x);
static void c12_eml_rand_mt19937ar
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state[625]);
static void c12_twister_state_vector
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_mt[625], real_T c12_seed, uint32_T c12_b_mt[625]);
static void c12_b_eml_rand_mt19937ar
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state[625], uint32_T c12_f_state[625], real_T *c12_r);
static void c12_assert_valid_state
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c12_genrand_uint32_vector
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_mt[625], uint32_T c12_b_mt[625], uint32_T c12_u[2]);
static void c12_b_genrandu(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, uint32_T c12_mt[625], uint32_T c12_b_mt[625], real_T *c12_r);
static void c12_eml_error(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static int32_T c12_e_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static uint32_T c12_f_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_c_method, const char_T *c12_identifier);
static uint32_T c12_g_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static uint32_T c12_h_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_c_method, const char_T *c12_identifier);
static uint32_T c12_i_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static uint32_T c12_j_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_e_state, const char_T *c12_identifier);
static uint32_T c12_k_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_l_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_e_state, const char_T *c12_identifier, uint32_T c12_y[625]);
static void c12_m_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, uint32_T c12_y[625]);
static void c12_n_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_e_state, const char_T *c12_identifier, uint32_T c12_y[2]);
static void c12_o_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, uint32_T c12_y[2]);
static void c12_p_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_e_state, const char_T *c12_identifier, uint32_T c12_y[2]);
static void c12_q_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, uint32_T c12_y[2]);
static uint8_T c12_r_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_b_is_active_c12_modelo_FK_simul_coleta_dados, const char_T
   *c12_identifier);
static uint8_T c12_s_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static real_T c12_b_eml_rand_mcg16807
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   *c12_e_state);
static real_T c12_b_eml_rand_shr3cong
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state[2]);
static void c12_b_twister_state_vector
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_mt[625], real_T c12_seed);
static real_T c12_c_eml_rand_mt19937ar
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state[625]);
static void c12_b_genrand_uint32_vector
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_mt[625], uint32_T c12_u[2]);
static real_T c12_c_genrandu(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, uint32_T c12_mt[625]);
static void init_dsm_address_info
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  chartInstance->c12_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c12_method_not_empty = FALSE;
  chartInstance->c12_state_not_empty = FALSE;
  chartInstance->c12_b_method_not_empty = FALSE;
  chartInstance->c12_b_state_not_empty = FALSE;
  chartInstance->c12_c_state_not_empty = FALSE;
  chartInstance->c12_d_state_not_empty = FALSE;
  chartInstance->c12_is_active_c12_modelo_FK_simul_coleta_dados = 0U;
}

static void initialize_params_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void enable_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c12_update_debugger_state_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  const mxArray *c12_st;
  const mxArray *c12_y = NULL;
  int32_T c12_i0;
  real_T c12_u[3];
  const mxArray *c12_b_y = NULL;
  uint32_T c12_hoistedGlobal;
  uint32_T c12_b_u;
  const mxArray *c12_c_y = NULL;
  uint32_T c12_b_hoistedGlobal;
  uint32_T c12_c_u;
  const mxArray *c12_d_y = NULL;
  uint32_T c12_c_hoistedGlobal;
  uint32_T c12_d_u;
  const mxArray *c12_e_y = NULL;
  int32_T c12_i1;
  uint32_T c12_e_u[625];
  const mxArray *c12_f_y = NULL;
  int32_T c12_i2;
  uint32_T c12_f_u[2];
  const mxArray *c12_g_y = NULL;
  int32_T c12_i3;
  uint32_T c12_g_u[2];
  const mxArray *c12_h_y = NULL;
  uint8_T c12_d_hoistedGlobal;
  uint8_T c12_h_u;
  const mxArray *c12_i_y = NULL;
  real_T (*c12_wr)[3];
  c12_wr = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_st = NULL;
  c12_st = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_createcellarray(8), FALSE);
  for (c12_i0 = 0; c12_i0 < 3; c12_i0++) {
    c12_u[c12_i0] = (*c12_wr)[c12_i0];
  }

  c12_b_y = NULL;
  sf_mex_assign(&c12_b_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c12_y, 0, c12_b_y);
  c12_hoistedGlobal = chartInstance->c12_b_method;
  c12_b_u = c12_hoistedGlobal;
  c12_c_y = NULL;
  if (!chartInstance->c12_b_method_not_empty) {
    sf_mex_assign(&c12_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c12_c_y, sf_mex_create("y", &c12_b_u, 7, 0U, 0U, 0U, 0),
                  FALSE);
  }

  sf_mex_setcell(c12_y, 1, c12_c_y);
  c12_b_hoistedGlobal = chartInstance->c12_method;
  c12_c_u = c12_b_hoistedGlobal;
  c12_d_y = NULL;
  if (!chartInstance->c12_method_not_empty) {
    sf_mex_assign(&c12_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c12_d_y, sf_mex_create("y", &c12_c_u, 7, 0U, 0U, 0U, 0),
                  FALSE);
  }

  sf_mex_setcell(c12_y, 2, c12_d_y);
  c12_c_hoistedGlobal = chartInstance->c12_b_state;
  c12_d_u = c12_c_hoistedGlobal;
  c12_e_y = NULL;
  if (!chartInstance->c12_b_state_not_empty) {
    sf_mex_assign(&c12_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c12_e_y, sf_mex_create("y", &c12_d_u, 7, 0U, 0U, 0U, 0),
                  FALSE);
  }

  sf_mex_setcell(c12_y, 3, c12_e_y);
  for (c12_i1 = 0; c12_i1 < 625; c12_i1++) {
    c12_e_u[c12_i1] = chartInstance->c12_d_state[c12_i1];
  }

  c12_f_y = NULL;
  if (!chartInstance->c12_d_state_not_empty) {
    sf_mex_assign(&c12_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c12_f_y, sf_mex_create("y", c12_e_u, 7, 0U, 1U, 0U, 1, 625),
                  FALSE);
  }

  sf_mex_setcell(c12_y, 4, c12_f_y);
  for (c12_i2 = 0; c12_i2 < 2; c12_i2++) {
    c12_f_u[c12_i2] = chartInstance->c12_c_state[c12_i2];
  }

  c12_g_y = NULL;
  if (!chartInstance->c12_c_state_not_empty) {
    sf_mex_assign(&c12_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c12_g_y, sf_mex_create("y", c12_f_u, 7, 0U, 1U, 0U, 1, 2),
                  FALSE);
  }

  sf_mex_setcell(c12_y, 5, c12_g_y);
  for (c12_i3 = 0; c12_i3 < 2; c12_i3++) {
    c12_g_u[c12_i3] = chartInstance->c12_state[c12_i3];
  }

  c12_h_y = NULL;
  if (!chartInstance->c12_state_not_empty) {
    sf_mex_assign(&c12_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c12_h_y, sf_mex_create("y", c12_g_u, 7, 0U, 1U, 0U, 1, 2),
                  FALSE);
  }

  sf_mex_setcell(c12_y, 6, c12_h_y);
  c12_d_hoistedGlobal =
    chartInstance->c12_is_active_c12_modelo_FK_simul_coleta_dados;
  c12_h_u = c12_d_hoistedGlobal;
  c12_i_y = NULL;
  sf_mex_assign(&c12_i_y, sf_mex_create("y", &c12_h_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c12_y, 7, c12_i_y);
  sf_mex_assign(&c12_st, c12_y, FALSE);
  return c12_st;
}

static void set_sim_state_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_st)
{
  const mxArray *c12_u;
  real_T c12_dv0[3];
  int32_T c12_i4;
  uint32_T c12_uv0[625];
  int32_T c12_i5;
  uint32_T c12_uv1[2];
  int32_T c12_i6;
  uint32_T c12_uv2[2];
  int32_T c12_i7;
  real_T (*c12_wr)[3];
  c12_wr = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c12_doneDoubleBufferReInit = TRUE;
  c12_u = sf_mex_dup(c12_st);
  c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 0)), "wr",
                       c12_dv0);
  for (c12_i4 = 0; c12_i4 < 3; c12_i4++) {
    (*c12_wr)[c12_i4] = c12_dv0[c12_i4];
  }

  chartInstance->c12_b_method = c12_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c12_u, 1)), "method");
  chartInstance->c12_method = c12_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c12_u, 2)), "method");
  chartInstance->c12_b_state = c12_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c12_u, 3)), "state");
  c12_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 4)),
    "state", c12_uv0);
  for (c12_i5 = 0; c12_i5 < 625; c12_i5++) {
    chartInstance->c12_d_state[c12_i5] = c12_uv0[c12_i5];
  }

  c12_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 5)),
    "state", c12_uv1);
  for (c12_i6 = 0; c12_i6 < 2; c12_i6++) {
    chartInstance->c12_c_state[c12_i6] = c12_uv1[c12_i6];
  }

  c12_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 6)),
    "state", c12_uv2);
  for (c12_i7 = 0; c12_i7 < 2; c12_i7++) {
    chartInstance->c12_state[c12_i7] = c12_uv2[c12_i7];
  }

  chartInstance->c12_is_active_c12_modelo_FK_simul_coleta_dados =
    c12_r_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 7)),
    "is_active_c12_modelo_FK_simul_coleta_dados");
  sf_mex_destroy(&c12_u);
  c12_update_debugger_state_c12_modelo_FK_simul_coleta_dados(chartInstance);
  sf_mex_destroy(&c12_st);
}

static void finalize_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void sf_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  int32_T c12_i8;
  int32_T c12_i9;
  int32_T c12_i10;
  int32_T c12_i11;
  int32_T c12_i12;
  real_T (*c12_vn)[3];
  real_T (*c12_vo)[3];
  real_T (*c12_vs)[3];
  real_T (*c12_wr)[3];
  real_T (*c12_w)[3];
  c12_vn = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c12_vo = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c12_vs = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c12_wr = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_w = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  for (c12_i8 = 0; c12_i8 < 3; c12_i8++) {
    _SFD_DATA_RANGE_CHECK((*c12_w)[c12_i8], 0U);
  }

  for (c12_i9 = 0; c12_i9 < 3; c12_i9++) {
    _SFD_DATA_RANGE_CHECK((*c12_wr)[c12_i9], 1U);
  }

  for (c12_i10 = 0; c12_i10 < 3; c12_i10++) {
    _SFD_DATA_RANGE_CHECK((*c12_vs)[c12_i10], 2U);
  }

  for (c12_i11 = 0; c12_i11 < 3; c12_i11++) {
    _SFD_DATA_RANGE_CHECK((*c12_vo)[c12_i11], 3U);
  }

  for (c12_i12 = 0; c12_i12 < 3; c12_i12++) {
    _SFD_DATA_RANGE_CHECK((*c12_vn)[c12_i12], 4U);
  }

  chartInstance->c12_sfEvent = CALL_EVENT;
  c12_chartstep_c12_modelo_FK_simul_coleta_dados(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_modelo_FK_simul_coleta_dadosMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c12_chartstep_c12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  int32_T c12_i13;
  real_T c12_w[3];
  int32_T c12_i14;
  real_T c12_vs[3];
  int32_T c12_i15;
  real_T c12_vo[3];
  int32_T c12_i16;
  real_T c12_vn[3];
  uint32_T c12_debug_family_var_map[8];
  real_T c12_S[9];
  real_T c12_nargin = 4.0;
  real_T c12_nargout = 1.0;
  real_T c12_wr[3];
  int32_T c12_i17;
  real_T c12_v[3];
  int32_T c12_i18;
  int32_T c12_j;
  int32_T c12_b_j;
  int32_T c12_a;
  int32_T c12_c;
  int32_T c12_i19;
  real_T c12_b_a[9];
  int32_T c12_i20;
  int32_T c12_i21;
  real_T c12_y[3];
  int32_T c12_i22;
  int32_T c12_i23;
  int32_T c12_i24;
  int32_T c12_i25;
  real_T (*c12_b_wr)[3];
  real_T (*c12_b_vn)[3];
  real_T (*c12_b_vo)[3];
  real_T (*c12_b_vs)[3];
  real_T (*c12_b_w)[3];
  c12_b_vn = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c12_b_vo = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c12_b_vs = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c12_b_wr = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_b_w = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  for (c12_i13 = 0; c12_i13 < 3; c12_i13++) {
    c12_w[c12_i13] = (*c12_b_w)[c12_i13];
  }

  for (c12_i14 = 0; c12_i14 < 3; c12_i14++) {
    c12_vs[c12_i14] = (*c12_b_vs)[c12_i14];
  }

  for (c12_i15 = 0; c12_i15 < 3; c12_i15++) {
    c12_vo[c12_i15] = (*c12_b_vo)[c12_i15];
  }

  for (c12_i16 = 0; c12_i16 < 3; c12_i16++) {
    c12_vn[c12_i16] = (*c12_b_vn)[c12_i16];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c12_debug_family_names,
    c12_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_S, 0U, c12_c_sf_marshallOut,
    c12_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargin, 1U, c12_b_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargout, 2U, c12_b_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_w, 3U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_vs, 4U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_vo, 5U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_vn, 6U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_wr, 7U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 4);
  for (c12_i17 = 0; c12_i17 < 3; c12_i17++) {
    c12_v[c12_i17] = c12_vs[c12_i17];
  }

  for (c12_i18 = 0; c12_i18 < 9; c12_i18++) {
    c12_S[c12_i18] = 0.0;
  }

  for (c12_j = 1; c12_j < 4; c12_j++) {
    c12_b_j = c12_j;
    c12_a = c12_b_j;
    c12_c = c12_a;
    c12_S[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c12_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c12_c), 1, 3, 2, 0) - 1)) -
      1] = c12_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c12_b_j), 1, 3, 1, 0) - 1];
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 6);
  for (c12_i19 = 0; c12_i19 < 9; c12_i19++) {
    c12_b_a[c12_i19] = c12_S[c12_i19];
  }

  for (c12_i20 = 0; c12_i20 < 3; c12_i20++) {
    c12_v[c12_i20] = c12_w[c12_i20];
  }

  c12_eml_scalar_eg(chartInstance);
  c12_eml_scalar_eg(chartInstance);
  for (c12_i21 = 0; c12_i21 < 3; c12_i21++) {
    c12_y[c12_i21] = 0.0;
    c12_i22 = 0;
    for (c12_i23 = 0; c12_i23 < 3; c12_i23++) {
      c12_y[c12_i21] += c12_b_a[c12_i22 + c12_i21] * c12_v[c12_i23];
      c12_i22 += 3;
    }
  }

  c12_randn(chartInstance, c12_v);
  for (c12_i24 = 0; c12_i24 < 3; c12_i24++) {
    c12_wr[c12_i24] = (c12_y[c12_i24] + c12_vo[c12_i24]) + c12_vn[c12_i24] *
      c12_v[c12_i24];
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, -6);
  _SFD_SYMBOL_SCOPE_POP();
  for (c12_i25 = 0; c12_i25 < 3; c12_i25++) {
    (*c12_b_wr)[c12_i25] = c12_wr[c12_i25];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
}

static void initSimStructsc12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void registerMessagesc12_modelo_FK_simul_coleta_dados
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
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
  int32_T c12_i26;
  real_T c12_b_inData[3];
  int32_T c12_i27;
  real_T c12_u[3];
  const mxArray *c12_y = NULL;
  SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i26 = 0; c12_i26 < 3; c12_i26++) {
    c12_b_inData[c12_i26] = (*(real_T (*)[3])c12_inData)[c12_i26];
  }

  for (c12_i27 = 0; c12_i27 < 3; c12_i27++) {
    c12_u[c12_i27] = c12_b_inData[c12_i27];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static void c12_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_wr, const char_T *c12_identifier, real_T c12_y[3])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_wr), &c12_thisId, c12_y);
  sf_mex_destroy(&c12_wr);
}

static void c12_b_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, real_T c12_y[3])
{
  real_T c12_dv1[3];
  int32_T c12_i28;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv1, 1, 0, 0U, 1, 0U, 1, 3);
  for (c12_i28 = 0; c12_i28 < 3; c12_i28++) {
    c12_y[c12_i28] = c12_dv1[c12_i28];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_wr;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y[3];
  int32_T c12_i29;
  SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c12_wr = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_wr), &c12_thisId, c12_y);
  sf_mex_destroy(&c12_wr);
  for (c12_i29 = 0; c12_i29 < 3; c12_i29++) {
    (*(real_T (*)[3])c12_outData)[c12_i29] = c12_y[c12_i29];
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  real_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(real_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static real_T c12_c_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
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
  SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *)
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

static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i30;
  int32_T c12_i31;
  int32_T c12_i32;
  real_T c12_b_inData[9];
  int32_T c12_i33;
  int32_T c12_i34;
  int32_T c12_i35;
  real_T c12_u[9];
  const mxArray *c12_y = NULL;
  SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_i30 = 0;
  for (c12_i31 = 0; c12_i31 < 3; c12_i31++) {
    for (c12_i32 = 0; c12_i32 < 3; c12_i32++) {
      c12_b_inData[c12_i32 + c12_i30] = (*(real_T (*)[9])c12_inData)[c12_i32 +
        c12_i30];
    }

    c12_i30 += 3;
  }

  c12_i33 = 0;
  for (c12_i34 = 0; c12_i34 < 3; c12_i34++) {
    for (c12_i35 = 0; c12_i35 < 3; c12_i35++) {
      c12_u[c12_i35 + c12_i33] = c12_b_inData[c12_i35 + c12_i33];
    }

    c12_i33 += 3;
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static void c12_d_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, real_T c12_y[9])
{
  real_T c12_dv2[9];
  int32_T c12_i36;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv2, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c12_i36 = 0; c12_i36 < 9; c12_i36++) {
    c12_y[c12_i36] = c12_dv2[c12_i36];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_S;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y[9];
  int32_T c12_i37;
  int32_T c12_i38;
  int32_T c12_i39;
  SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c12_S = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_S), &c12_thisId, c12_y);
  sf_mex_destroy(&c12_S);
  c12_i37 = 0;
  for (c12_i38 = 0; c12_i38 < 3; c12_i38++) {
    for (c12_i39 = 0; c12_i39 < 3; c12_i39++) {
      (*(real_T (*)[9])c12_outData)[c12_i39 + c12_i37] = c12_y[c12_i39 + c12_i37];
    }

    c12_i37 += 3;
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

const mxArray
  *sf_c12_modelo_FK_simul_coleta_dados_get_eml_resolved_functions_info(void)
{
  const mxArray *c12_nameCaptureInfo;
  c12_ResolvedFunctionInfo c12_info[60];
  const mxArray *c12_m0 = NULL;
  int32_T c12_i40;
  c12_ResolvedFunctionInfo *c12_r0;
  c12_nameCaptureInfo = NULL;
  c12_nameCaptureInfo = NULL;
  c12_info_helper(c12_info);
  sf_mex_assign(&c12_m0, sf_mex_createstruct("nameCaptureInfo", 1, 60), FALSE);
  for (c12_i40 = 0; c12_i40 < 60; c12_i40++) {
    c12_r0 = &c12_info[c12_i40];
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c12_r0->context)), "context", "nameCaptureInfo",
                    c12_i40);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c12_r0->name)), "name", "nameCaptureInfo",
                    c12_i40);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      c12_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c12_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c12_i40);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c12_r0->resolved)), "resolved",
                    "nameCaptureInfo", c12_i40);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", &c12_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c12_i40);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", &c12_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c12_i40);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      &c12_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c12_i40);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      &c12_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c12_i40);
  }

  sf_mex_assign(&c12_nameCaptureInfo, c12_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c12_nameCaptureInfo);
  return c12_nameCaptureInfo;
}

static void c12_info_helper(c12_ResolvedFunctionInfo c12_info[60])
{
  c12_info[0].context = "";
  c12_info[0].name = "diag";
  c12_info[0].dominantType = "double";
  c12_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c12_info[0].fileTimeLo = 1286836686U;
  c12_info[0].fileTimeHi = 0U;
  c12_info[0].mFileTimeLo = 0U;
  c12_info[0].mFileTimeHi = 0U;
  c12_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c12_info[1].name = "eml_index_class";
  c12_info[1].dominantType = "";
  c12_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c12_info[1].fileTimeLo = 1323181378U;
  c12_info[1].fileTimeHi = 0U;
  c12_info[1].mFileTimeLo = 0U;
  c12_info[1].mFileTimeHi = 0U;
  c12_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c12_info[2].name = "eml_index_plus";
  c12_info[2].dominantType = "coder.internal.indexInt";
  c12_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c12_info[2].fileTimeLo = 1286836778U;
  c12_info[2].fileTimeHi = 0U;
  c12_info[2].mFileTimeLo = 0U;
  c12_info[2].mFileTimeHi = 0U;
  c12_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c12_info[3].name = "eml_index_class";
  c12_info[3].dominantType = "";
  c12_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c12_info[3].fileTimeLo = 1323181378U;
  c12_info[3].fileTimeHi = 0U;
  c12_info[3].mFileTimeLo = 0U;
  c12_info[3].mFileTimeHi = 0U;
  c12_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c12_info[4].name = "eml_scalar_eg";
  c12_info[4].dominantType = "double";
  c12_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c12_info[4].fileTimeLo = 1286836796U;
  c12_info[4].fileTimeHi = 0U;
  c12_info[4].mFileTimeLo = 0U;
  c12_info[4].mFileTimeHi = 0U;
  c12_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c12_info[5].name = "eml_int_forloop_overflow_check";
  c12_info[5].dominantType = "";
  c12_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c12_info[5].fileTimeLo = 1346528340U;
  c12_info[5].fileTimeHi = 0U;
  c12_info[5].mFileTimeLo = 0U;
  c12_info[5].mFileTimeHi = 0U;
  c12_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c12_info[6].name = "intmax";
  c12_info[6].dominantType = "char";
  c12_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c12_info[6].fileTimeLo = 1311273316U;
  c12_info[6].fileTimeHi = 0U;
  c12_info[6].mFileTimeLo = 0U;
  c12_info[6].mFileTimeHi = 0U;
  c12_info[7].context = "";
  c12_info[7].name = "mtimes";
  c12_info[7].dominantType = "double";
  c12_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[7].fileTimeLo = 1289530492U;
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
  c12_info[16].name = "randn";
  c12_info[16].dominantType = "double";
  c12_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/randn.m";
  c12_info[16].fileTimeLo = 1313365824U;
  c12_info[16].fileTimeHi = 0U;
  c12_info[16].mFileTimeLo = 0U;
  c12_info[16].mFileTimeHi = 0U;
  c12_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/randn.m";
  c12_info[17].name = "eml_is_rand_extrinsic";
  c12_info[17].dominantType = "";
  c12_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_is_rand_extrinsic.m";
  c12_info[17].fileTimeLo = 1334089490U;
  c12_info[17].fileTimeHi = 0U;
  c12_info[17].mFileTimeLo = 0U;
  c12_info[17].mFileTimeHi = 0U;
  c12_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/randn.m";
  c12_info[18].name = "eml_randn";
  c12_info[18].dominantType = "char";
  c12_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_randn.m";
  c12_info[18].fileTimeLo = 1313365822U;
  c12_info[18].fileTimeHi = 0U;
  c12_info[18].mFileTimeLo = 0U;
  c12_info[18].mFileTimeHi = 0U;
  c12_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_randn.m";
  c12_info[19].name = "eml_rand_str2id";
  c12_info[19].dominantType = "char";
  c12_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_str2id.m";
  c12_info[19].fileTimeLo = 1313365822U;
  c12_info[19].fileTimeHi = 0U;
  c12_info[19].mFileTimeLo = 0U;
  c12_info[19].mFileTimeHi = 0U;
  c12_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_randn.m";
  c12_info[20].name = "eml_rand_shr3cong";
  c12_info[20].dominantType = "char";
  c12_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m";
  c12_info[20].fileTimeLo = 1313365820U;
  c12_info[20].fileTimeHi = 0U;
  c12_info[20].mFileTimeLo = 0U;
  c12_info[20].mFileTimeHi = 0U;
  c12_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_randn.m";
  c12_info[21].name = "eml_tolower";
  c12_info[21].dominantType = "char";
  c12_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_tolower.m";
  c12_info[21].fileTimeLo = 1286836800U;
  c12_info[21].fileTimeHi = 0U;
  c12_info[21].mFileTimeLo = 0U;
  c12_info[21].mFileTimeHi = 0U;
  c12_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_randn.m";
  c12_info[22].name = "eml_rand";
  c12_info[22].dominantType = "char";
  c12_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c12_info[22].fileTimeLo = 1313365820U;
  c12_info[22].fileTimeHi = 0U;
  c12_info[22].mFileTimeLo = 0U;
  c12_info[22].mFileTimeHi = 0U;
  c12_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c12_info[23].name = "eml_rand_str2id";
  c12_info[23].dominantType = "char";
  c12_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_str2id.m";
  c12_info[23].fileTimeLo = 1313365822U;
  c12_info[23].fileTimeHi = 0U;
  c12_info[23].mFileTimeLo = 0U;
  c12_info[23].mFileTimeHi = 0U;
  c12_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c12_info[24].name = "eml_rand_mcg16807_stateful";
  c12_info[24].dominantType = "char";
  c12_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m";
  c12_info[24].fileTimeLo = 1313365820U;
  c12_info[24].fileTimeHi = 0U;
  c12_info[24].mFileTimeLo = 0U;
  c12_info[24].mFileTimeHi = 0U;
  c12_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m";
  c12_info[25].name = "eml_rand_mcg16807";
  c12_info[25].dominantType = "char";
  c12_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m";
  c12_info[25].fileTimeLo = 1313365820U;
  c12_info[25].fileTimeHi = 0U;
  c12_info[25].mFileTimeLo = 0U;
  c12_info[25].mFileTimeHi = 0U;
  c12_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m";
  c12_info[26].name = "eml_rand_mcg16807";
  c12_info[26].dominantType = "uint32";
  c12_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m";
  c12_info[26].fileTimeLo = 1313365820U;
  c12_info[26].fileTimeHi = 0U;
  c12_info[26].mFileTimeLo = 0U;
  c12_info[26].mFileTimeHi = 0U;
  c12_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m!genrandu";
  c12_info[27].name = "mtimes";
  c12_info[27].dominantType = "double";
  c12_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[27].fileTimeLo = 1289530492U;
  c12_info[27].fileTimeHi = 0U;
  c12_info[27].mFileTimeLo = 0U;
  c12_info[27].mFileTimeHi = 0U;
  c12_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m!genrandn";
  c12_info[28].name = "mtimes";
  c12_info[28].dominantType = "double";
  c12_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[28].fileTimeLo = 1289530492U;
  c12_info[28].fileTimeHi = 0U;
  c12_info[28].mFileTimeLo = 0U;
  c12_info[28].mFileTimeHi = 0U;
  c12_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c12_info[29].name = "eml_rand_shr3cong_stateful";
  c12_info[29].dominantType = "char";
  c12_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m";
  c12_info[29].fileTimeLo = 1313365822U;
  c12_info[29].fileTimeHi = 0U;
  c12_info[29].mFileTimeLo = 0U;
  c12_info[29].mFileTimeHi = 0U;
  c12_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m";
  c12_info[30].name = "eml_rand_shr3cong";
  c12_info[30].dominantType = "char";
  c12_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m";
  c12_info[30].fileTimeLo = 1313365820U;
  c12_info[30].fileTimeHi = 0U;
  c12_info[30].mFileTimeLo = 0U;
  c12_info[30].mFileTimeHi = 0U;
  c12_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m";
  c12_info[31].name = "eml_rand_shr3cong";
  c12_info[31].dominantType = "uint32";
  c12_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m";
  c12_info[31].fileTimeLo = 1313365820U;
  c12_info[31].fileTimeHi = 0U;
  c12_info[31].mFileTimeLo = 0U;
  c12_info[31].mFileTimeHi = 0U;
  c12_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m!genrandn";
  c12_info[32].name = "mtimes";
  c12_info[32].dominantType = "double";
  c12_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[32].fileTimeLo = 1289530492U;
  c12_info[32].fileTimeHi = 0U;
  c12_info[32].mFileTimeLo = 0U;
  c12_info[32].mFileTimeHi = 0U;
  c12_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m!genrandn";
  c12_info[33].name = "abs";
  c12_info[33].dominantType = "double";
  c12_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c12_info[33].fileTimeLo = 1343848366U;
  c12_info[33].fileTimeHi = 0U;
  c12_info[33].mFileTimeLo = 0U;
  c12_info[33].mFileTimeHi = 0U;
  c12_info[34].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c12_info[34].name = "eml_scalar_abs";
  c12_info[34].dominantType = "double";
  c12_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c12_info[34].fileTimeLo = 1286836712U;
  c12_info[34].fileTimeHi = 0U;
  c12_info[34].mFileTimeLo = 0U;
  c12_info[34].mFileTimeHi = 0U;
  c12_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m!genrandn";
  c12_info[35].name = "mrdivide";
  c12_info[35].dominantType = "double";
  c12_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c12_info[35].fileTimeLo = 1357962348U;
  c12_info[35].fileTimeHi = 0U;
  c12_info[35].mFileTimeLo = 1319744366U;
  c12_info[35].mFileTimeHi = 0U;
  c12_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c12_info[36].name = "rdivide";
  c12_info[36].dominantType = "double";
  c12_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c12_info[36].fileTimeLo = 1346528388U;
  c12_info[36].fileTimeHi = 0U;
  c12_info[36].mFileTimeLo = 0U;
  c12_info[36].mFileTimeHi = 0U;
  c12_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c12_info[37].name = "eml_scalexp_compatible";
  c12_info[37].dominantType = "double";
  c12_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c12_info[37].fileTimeLo = 1286836796U;
  c12_info[37].fileTimeHi = 0U;
  c12_info[37].mFileTimeLo = 0U;
  c12_info[37].mFileTimeHi = 0U;
  c12_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c12_info[38].name = "eml_div";
  c12_info[38].dominantType = "double";
  c12_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c12_info[38].fileTimeLo = 1313365810U;
  c12_info[38].fileTimeHi = 0U;
  c12_info[38].mFileTimeLo = 0U;
  c12_info[38].mFileTimeHi = 0U;
  c12_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m!genrandn";
  c12_info[39].name = "exp";
  c12_info[39].dominantType = "double";
  c12_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/exp.m";
  c12_info[39].fileTimeLo = 1343848380U;
  c12_info[39].fileTimeHi = 0U;
  c12_info[39].mFileTimeLo = 0U;
  c12_info[39].mFileTimeHi = 0U;
  c12_info[40].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/exp.m";
  c12_info[40].name = "eml_scalar_exp";
  c12_info[40].dominantType = "double";
  c12_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_exp.m";
  c12_info[40].fileTimeLo = 1301346464U;
  c12_info[40].fileTimeHi = 0U;
  c12_info[40].mFileTimeLo = 0U;
  c12_info[40].mFileTimeHi = 0U;
  c12_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c12_info[41].name = "eml_rand_mt19937ar_stateful";
  c12_info[41].dominantType = "char";
  c12_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m";
  c12_info[41].fileTimeLo = 1313365820U;
  c12_info[41].fileTimeHi = 0U;
  c12_info[41].mFileTimeLo = 0U;
  c12_info[41].mFileTimeHi = 0U;
  c12_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m";
  c12_info[42].name = "eml_rand_mt19937ar";
  c12_info[42].dominantType = "char";
  c12_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m";
  c12_info[42].fileTimeLo = 1313365820U;
  c12_info[42].fileTimeHi = 0U;
  c12_info[42].mFileTimeLo = 0U;
  c12_info[42].mFileTimeHi = 0U;
  c12_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m";
  c12_info[43].name = "eml_rand_mt19937ar";
  c12_info[43].dominantType = "uint32";
  c12_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m";
  c12_info[43].fileTimeLo = 1313365820U;
  c12_info[43].fileTimeHi = 0U;
  c12_info[43].mFileTimeLo = 0U;
  c12_info[43].mFileTimeHi = 0U;
  c12_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!is_valid_state";
  c12_info[44].name = "isequal";
  c12_info[44].dominantType = "double";
  c12_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c12_info[44].fileTimeLo = 1286836758U;
  c12_info[44].fileTimeHi = 0U;
  c12_info[44].mFileTimeLo = 0U;
  c12_info[44].mFileTimeHi = 0U;
  c12_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c12_info[45].name = "eml_isequal_core";
  c12_info[45].dominantType = "double";
  c12_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c12_info[45].fileTimeLo = 1286836786U;
  c12_info[45].fileTimeHi = 0U;
  c12_info[45].mFileTimeLo = 0U;
  c12_info[45].mFileTimeHi = 0U;
  c12_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c12_info[46].name = "isnan";
  c12_info[46].dominantType = "double";
  c12_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c12_info[46].fileTimeLo = 1286836760U;
  c12_info[46].fileTimeHi = 0U;
  c12_info[46].mFileTimeLo = 0U;
  c12_info[46].mFileTimeHi = 0U;
  c12_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!mtziggurat";
  c12_info[47].name = "mtimes";
  c12_info[47].dominantType = "double";
  c12_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[47].fileTimeLo = 1289530492U;
  c12_info[47].fileTimeHi = 0U;
  c12_info[47].mFileTimeLo = 0U;
  c12_info[47].mFileTimeHi = 0U;
  c12_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!mtziggurat";
  c12_info[48].name = "mrdivide";
  c12_info[48].dominantType = "double";
  c12_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c12_info[48].fileTimeLo = 1357962348U;
  c12_info[48].fileTimeHi = 0U;
  c12_info[48].mFileTimeLo = 1319744366U;
  c12_info[48].mFileTimeHi = 0U;
  c12_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!mtziggurat";
  c12_info[49].name = "abs";
  c12_info[49].dominantType = "double";
  c12_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c12_info[49].fileTimeLo = 1343848366U;
  c12_info[49].fileTimeHi = 0U;
  c12_info[49].mFileTimeLo = 0U;
  c12_info[49].mFileTimeHi = 0U;
  c12_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!genrandu";
  c12_info[50].name = "eps";
  c12_info[50].dominantType = "";
  c12_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c12_info[50].fileTimeLo = 1326738796U;
  c12_info[50].fileTimeHi = 0U;
  c12_info[50].mFileTimeLo = 0U;
  c12_info[50].mFileTimeHi = 0U;
  c12_info[51].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c12_info[51].name = "eml_eps";
  c12_info[51].dominantType = "char";
  c12_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c12_info[51].fileTimeLo = 1326738796U;
  c12_info[51].fileTimeHi = 0U;
  c12_info[51].mFileTimeLo = 0U;
  c12_info[51].mFileTimeHi = 0U;
  c12_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c12_info[52].name = "eml_float_model";
  c12_info[52].dominantType = "char";
  c12_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c12_info[52].fileTimeLo = 1326738796U;
  c12_info[52].fileTimeHi = 0U;
  c12_info[52].mFileTimeLo = 0U;
  c12_info[52].mFileTimeHi = 0U;
  c12_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!genrandu";
  c12_info[53].name = "mtimes";
  c12_info[53].dominantType = "double";
  c12_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[53].fileTimeLo = 1289530492U;
  c12_info[53].fileTimeHi = 0U;
  c12_info[53].mFileTimeLo = 0U;
  c12_info[53].mFileTimeHi = 0U;
  c12_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!is_valid_state";
  c12_info[54].name = "eml_index_class";
  c12_info[54].dominantType = "";
  c12_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c12_info[54].fileTimeLo = 1323181378U;
  c12_info[54].fileTimeHi = 0U;
  c12_info[54].mFileTimeLo = 0U;
  c12_info[54].mFileTimeHi = 0U;
  c12_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!is_valid_state";
  c12_info[55].name = "eml_index_plus";
  c12_info[55].dominantType = "double";
  c12_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c12_info[55].fileTimeLo = 1286836778U;
  c12_info[55].fileTimeHi = 0U;
  c12_info[55].mFileTimeLo = 0U;
  c12_info[55].mFileTimeHi = 0U;
  c12_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!genrandu";
  c12_info[56].name = "eml_error";
  c12_info[56].dominantType = "char";
  c12_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c12_info[56].fileTimeLo = 1343848358U;
  c12_info[56].fileTimeHi = 0U;
  c12_info[56].mFileTimeLo = 0U;
  c12_info[56].mFileTimeHi = 0U;
  c12_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!mtziggurat";
  c12_info[57].name = "exp";
  c12_info[57].dominantType = "double";
  c12_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/exp.m";
  c12_info[57].fileTimeLo = 1343848380U;
  c12_info[57].fileTimeHi = 0U;
  c12_info[57].mFileTimeLo = 0U;
  c12_info[57].mFileTimeHi = 0U;
  c12_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_randn.m";
  c12_info[58].name = "eml_rand_mcg16807";
  c12_info[58].dominantType = "uint32";
  c12_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m";
  c12_info[58].fileTimeLo = 1313365820U;
  c12_info[58].fileTimeHi = 0U;
  c12_info[58].mFileTimeLo = 0U;
  c12_info[58].mFileTimeHi = 0U;
  c12_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_randn.m";
  c12_info[59].name = "eml_rand_shr3cong";
  c12_info[59].dominantType = "uint32";
  c12_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m";
  c12_info[59].fileTimeLo = 1313365820U;
  c12_info[59].fileTimeHi = 0U;
  c12_info[59].mFileTimeLo = 0U;
  c12_info[59].mFileTimeHi = 0U;
}

static void c12_eml_scalar_eg(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c12_randn(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c12_r[3])
{
  int32_T c12_i41;
  static uint32_T c12_uv3[2] = { 362436069U, 0U };

  int32_T c12_k;
  real_T c12_b_k;
  uint32_T c12_e_state;
  real_T c12_d1;
  int32_T c12_i42;
  int32_T c12_c_k;
  real_T c12_d_k;
  real_T c12_d2;
  uint32_T c12_uv4[625];
  int32_T c12_i43;
  int32_T c12_e_k;
  real_T c12_f_k;
  real_T c12_d3;
  uint32_T c12_hoistedGlobal;
  int32_T c12_g_k;
  real_T c12_h_k;
  uint32_T c12_u0;
  real_T c12_d4;
  int32_T c12_i_k;
  real_T c12_d5;
  if (!chartInstance->c12_method_not_empty) {
    chartInstance->c12_method = 0U;
    chartInstance->c12_method_not_empty = TRUE;
    for (c12_i41 = 0; c12_i41 < 2; c12_i41++) {
      chartInstance->c12_state[c12_i41] = c12_uv3[c12_i41];
    }

    if ((real_T)chartInstance->c12_state[1] == 0.0) {
      chartInstance->c12_state[1] = 521288629U;
    }

    chartInstance->c12_state_not_empty = TRUE;
  }

  if (chartInstance->c12_method == 0U) {
    if (!chartInstance->c12_b_method_not_empty) {
      chartInstance->c12_b_method = 7U;
      chartInstance->c12_b_method_not_empty = TRUE;
    }

    if (chartInstance->c12_b_method == 4U) {
      if (!chartInstance->c12_b_state_not_empty) {
        chartInstance->c12_b_state = 1144108930U;
        chartInstance->c12_b_state_not_empty = TRUE;
      }

      for (c12_k = 0; c12_k < 3; c12_k++) {
        c12_b_k = 1.0 + (real_T)c12_k;
        c12_e_state = chartInstance->c12_b_state;
        c12_d1 = c12_b_eml_rand_mcg16807(chartInstance, &c12_e_state);
        chartInstance->c12_b_state = c12_e_state;
        c12_r[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c12_b_k), 1, 3, 1, 0) - 1] = c12_d1;
      }
    } else if (chartInstance->c12_b_method == 5U) {
      if (!chartInstance->c12_c_state_not_empty) {
        for (c12_i42 = 0; c12_i42 < 2; c12_i42++) {
          chartInstance->c12_c_state[c12_i42] = 362436069U + 158852560U *
            (uint32_T)c12_i42;
        }

        chartInstance->c12_c_state_not_empty = TRUE;
      }

      for (c12_c_k = 0; c12_c_k < 3; c12_c_k++) {
        c12_d_k = 1.0 + (real_T)c12_c_k;
        c12_d2 = c12_b_eml_rand_shr3cong(chartInstance,
          chartInstance->c12_c_state);
        c12_r[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c12_d_k), 1, 3, 1, 0) - 1] = c12_d2;
      }
    } else {
      if (!chartInstance->c12_d_state_not_empty) {
        c12_eml_rand_mt19937ar(chartInstance, c12_uv4);
        for (c12_i43 = 0; c12_i43 < 625; c12_i43++) {
          chartInstance->c12_d_state[c12_i43] = c12_uv4[c12_i43];
        }

        chartInstance->c12_d_state_not_empty = TRUE;
      }

      for (c12_e_k = 0; c12_e_k < 3; c12_e_k++) {
        c12_f_k = 1.0 + (real_T)c12_e_k;
        c12_d3 = c12_c_eml_rand_mt19937ar(chartInstance,
          chartInstance->c12_d_state);
        c12_r[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c12_f_k), 1, 3, 1, 0) - 1] = c12_d3;
      }
    }
  } else {
    c12_hoistedGlobal = chartInstance->c12_method;
    if (c12_hoistedGlobal == 4U) {
      for (c12_g_k = 0; c12_g_k < 3; c12_g_k++) {
        c12_h_k = 1.0 + (real_T)c12_g_k;
        c12_u0 = chartInstance->c12_state[0];
        c12_d4 = c12_b_eml_rand_mcg16807(chartInstance, &c12_u0);
        chartInstance->c12_state[0] = c12_u0;
        c12_r[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c12_h_k), 1, 3, 1, 0) - 1] = c12_d4;
      }
    } else {
      for (c12_i_k = 0; c12_i_k < 3; c12_i_k++) {
        c12_h_k = 1.0 + (real_T)c12_i_k;
        c12_d5 = c12_b_eml_rand_shr3cong(chartInstance, chartInstance->c12_state);
        c12_r[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c12_h_k), 1, 3, 1, 0) - 1] = c12_d5;
      }
    }
  }
}

static void c12_eml_rand_mcg16807
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state, uint32_T *c12_f_state, real_T *c12_r)
{
  *c12_f_state = c12_e_state;
  *c12_r = c12_b_eml_rand_mcg16807(chartInstance, c12_f_state);
}

static void c12_genrandu(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, uint32_T c12_s, uint32_T *c12_e_state, real_T *c12_r)
{
  uint32_T c12_u1;
  uint32_T c12_hi;
  uint32_T c12_lo;
  uint32_T c12_test1;
  uint32_T c12_test2;
  real_T c12_a;
  c12_u1 = 127773U;
  if (c12_u1 == 0) {
    c12_hi = MAX_uint32_T;
  } else {
    c12_hi = c12_s / c12_u1;
  }

  c12_lo = c12_s - c12_hi * 127773U;
  c12_test1 = 16807U * c12_lo;
  c12_test2 = 2836U * c12_hi;
  if (c12_test1 < c12_test2) {
    *c12_e_state = (c12_test1 - c12_test2) + 2147483647U;
  } else {
    *c12_e_state = c12_test1 - c12_test2;
  }

  c12_a = (real_T)*c12_e_state;
  *c12_r = c12_a * 4.6566128752457969E-10;
}

static void c12_eml_rand_shr3cong
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state[2], uint32_T c12_f_state[2], real_T *c12_r)
{
  int32_T c12_i44;
  for (c12_i44 = 0; c12_i44 < 2; c12_i44++) {
    c12_f_state[c12_i44] = c12_e_state[c12_i44];
  }

  *c12_r = c12_b_eml_rand_shr3cong(chartInstance, c12_f_state);
}

static real_T c12_abs(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c12_x)
{
  real_T c12_b_x;
  c12_b_x = c12_x;
  return muDoubleScalarAbs(c12_b_x);
}

static void c12_eml_rand_mt19937ar
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state[625])
{
  real_T c12_d6;
  int32_T c12_i45;
  c12_d6 = 5489.0;
  for (c12_i45 = 0; c12_i45 < 625; c12_i45++) {
    c12_e_state[c12_i45] = 0U;
  }

  c12_b_twister_state_vector(chartInstance, c12_e_state, c12_d6);
}

static void c12_twister_state_vector
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_mt[625], real_T c12_seed, uint32_T c12_b_mt[625])
{
  int32_T c12_i46;
  for (c12_i46 = 0; c12_i46 < 625; c12_i46++) {
    c12_b_mt[c12_i46] = c12_mt[c12_i46];
  }

  c12_b_twister_state_vector(chartInstance, c12_b_mt, c12_seed);
}

static void c12_b_eml_rand_mt19937ar
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state[625], uint32_T c12_f_state[625], real_T *c12_r)
{
  int32_T c12_i47;
  for (c12_i47 = 0; c12_i47 < 625; c12_i47++) {
    c12_f_state[c12_i47] = c12_e_state[c12_i47];
  }

  *c12_r = c12_c_eml_rand_mt19937ar(chartInstance, c12_f_state);
}

static void c12_assert_valid_state
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void c12_genrand_uint32_vector
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_mt[625], uint32_T c12_b_mt[625], uint32_T c12_u[2])
{
  int32_T c12_i48;
  for (c12_i48 = 0; c12_i48 < 625; c12_i48++) {
    c12_b_mt[c12_i48] = c12_mt[c12_i48];
  }

  c12_b_genrand_uint32_vector(chartInstance, c12_b_mt, c12_u);
}

static void c12_b_genrandu(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, uint32_T c12_mt[625], uint32_T c12_b_mt[625], real_T *c12_r)
{
  int32_T c12_i49;
  for (c12_i49 = 0; c12_i49 < 625; c12_i49++) {
    c12_b_mt[c12_i49] = c12_mt[c12_i49];
  }

  *c12_r = c12_c_genrandu(chartInstance, c12_b_mt);
}

static void c12_eml_error(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
  int32_T c12_i50;
  static char_T c12_cv0[37] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T', 'L',
    'A', 'B', ':', 'r', 'a', 'n', 'd', '_', 'i', 'n', 'v', 'a', 'l', 'i', 'd',
    'T', 'w', 'i', 's', 't', 'e', 'r', 'S', 't', 'a', 't', 'e' };

  char_T c12_u[37];
  const mxArray *c12_y = NULL;
  for (c12_i50 = 0; c12_i50 < 37; c12_i50++) {
    c12_u[c12_i50] = c12_cv0[c12_i50];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 10, 0U, 1U, 0U, 2, 1, 37),
                FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c12_y));
}

static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(int32_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static int32_T c12_e_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  int32_T c12_y;
  int32_T c12_i51;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_i51, 1, 6, 0U, 0, 0U, 0);
  c12_y = c12_i51;
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
  SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c12_b_sfEvent = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_b_sfEvent),
    &c12_thisId);
  sf_mex_destroy(&c12_b_sfEvent);
  *(int32_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

static uint32_T c12_f_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_c_method, const char_T *c12_identifier)
{
  uint32_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_c_method),
    &c12_thisId);
  sf_mex_destroy(&c12_c_method);
  return c12_y;
}

static uint32_T c12_g_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint32_T c12_y;
  uint32_T c12_u2;
  if (mxIsEmpty(c12_u)) {
    chartInstance->c12_b_method_not_empty = FALSE;
  } else {
    chartInstance->c12_b_method_not_empty = TRUE;
    sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u2, 1, 7, 0U, 0, 0U, 0);
    c12_y = c12_u2;
  }

  sf_mex_destroy(&c12_u);
  return c12_y;
}

static uint32_T c12_h_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_c_method, const char_T *c12_identifier)
{
  uint32_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_c_method),
    &c12_thisId);
  sf_mex_destroy(&c12_c_method);
  return c12_y;
}

static uint32_T c12_i_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint32_T c12_y;
  uint32_T c12_u3;
  if (mxIsEmpty(c12_u)) {
    chartInstance->c12_method_not_empty = FALSE;
  } else {
    chartInstance->c12_method_not_empty = TRUE;
    sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u3, 1, 7, 0U, 0, 0U, 0);
    c12_y = c12_u3;
  }

  sf_mex_destroy(&c12_u);
  return c12_y;
}

static uint32_T c12_j_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_e_state, const char_T *c12_identifier)
{
  uint32_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_e_state),
    &c12_thisId);
  sf_mex_destroy(&c12_e_state);
  return c12_y;
}

static uint32_T c12_k_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint32_T c12_y;
  uint32_T c12_u4;
  if (mxIsEmpty(c12_u)) {
    chartInstance->c12_b_state_not_empty = FALSE;
  } else {
    chartInstance->c12_b_state_not_empty = TRUE;
    sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u4, 1, 7, 0U, 0, 0U, 0);
    c12_y = c12_u4;
  }

  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_l_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_e_state, const char_T *c12_identifier, uint32_T c12_y[625])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_e_state), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_e_state);
}

static void c12_m_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, uint32_T c12_y[625])
{
  uint32_T c12_uv5[625];
  int32_T c12_i52;
  if (mxIsEmpty(c12_u)) {
    chartInstance->c12_d_state_not_empty = FALSE;
  } else {
    chartInstance->c12_d_state_not_empty = TRUE;
    sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_uv5, 1, 7, 0U, 1, 0U, 1,
                  625);
    for (c12_i52 = 0; c12_i52 < 625; c12_i52++) {
      c12_y[c12_i52] = c12_uv5[c12_i52];
    }
  }

  sf_mex_destroy(&c12_u);
}

static void c12_n_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_e_state, const char_T *c12_identifier, uint32_T c12_y[2])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_e_state), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_e_state);
}

static void c12_o_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, uint32_T c12_y[2])
{
  uint32_T c12_uv6[2];
  int32_T c12_i53;
  if (mxIsEmpty(c12_u)) {
    chartInstance->c12_c_state_not_empty = FALSE;
  } else {
    chartInstance->c12_c_state_not_empty = TRUE;
    sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_uv6, 1, 7, 0U, 1, 0U, 1,
                  2);
    for (c12_i53 = 0; c12_i53 < 2; c12_i53++) {
      c12_y[c12_i53] = c12_uv6[c12_i53];
    }
  }

  sf_mex_destroy(&c12_u);
}

static void c12_p_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_e_state, const char_T *c12_identifier, uint32_T c12_y[2])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_e_state), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_e_state);
}

static void c12_q_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, uint32_T c12_y[2])
{
  uint32_T c12_uv7[2];
  int32_T c12_i54;
  if (mxIsEmpty(c12_u)) {
    chartInstance->c12_state_not_empty = FALSE;
  } else {
    chartInstance->c12_state_not_empty = TRUE;
    sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_uv7, 1, 7, 0U, 1, 0U, 1,
                  2);
    for (c12_i54 = 0; c12_i54 < 2; c12_i54++) {
      c12_y[c12_i54] = c12_uv7[c12_i54];
    }
  }

  sf_mex_destroy(&c12_u);
}

static uint8_T c12_r_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_b_is_active_c12_modelo_FK_simul_coleta_dados, const char_T
   *c12_identifier)
{
  uint8_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_s_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c12_b_is_active_c12_modelo_FK_simul_coleta_dados), &c12_thisId);
  sf_mex_destroy(&c12_b_is_active_c12_modelo_FK_simul_coleta_dados);
  return c12_y;
}

static uint8_T c12_s_emlrt_marshallIn
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const
   mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint8_T c12_y;
  uint8_T c12_u5;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u5, 1, 3, 0U, 0, 0U, 0);
  c12_y = c12_u5;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static real_T c12_b_eml_rand_mcg16807
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   *c12_e_state)
{
  uint32_T c12_f_state;
  uint32_T c12_g_state;
  real_T c12_b_r;
  uint32_T c12_h_state;
  real_T c12_c_r;
  real_T c12_t;
  uint32_T c12_i_state;
  real_T c12_b_t;
  real_T c12_b;
  real_T c12_y;
  real_T c12_b_b;
  real_T c12_b_y;
  real_T c12_a;
  real_T c12_c_b;
  real_T c12_c_y;
  real_T c12_b_a;
  real_T c12_d_b;
  real_T c12_d_y;
  real_T c12_e_b;
  real_T c12_e_y;
  real_T c12_c_a;
  real_T c12_f_b;
  c12_f_state = *c12_e_state;
  c12_g_state = c12_f_state;
  do {
    c12_genrandu(chartInstance, c12_g_state, &c12_h_state, &c12_b_r);
    c12_g_state = c12_h_state;
    c12_c_r = c12_b_r;
    c12_genrandu(chartInstance, c12_g_state, &c12_i_state, &c12_t);
    c12_g_state = c12_i_state;
    c12_b_t = c12_t;
    c12_b = c12_c_r;
    c12_y = 2.0 * c12_b;
    c12_c_r = c12_y - 1.0;
    c12_b_b = c12_b_t;
    c12_b_y = 2.0 * c12_b_b;
    c12_b_t = c12_b_y - 1.0;
    c12_a = c12_b_t;
    c12_c_b = c12_b_t;
    c12_c_y = c12_a * c12_c_b;
    c12_b_a = c12_c_r;
    c12_d_b = c12_c_r;
    c12_d_y = c12_b_a * c12_d_b;
    c12_b_t = c12_c_y + c12_d_y;
  } while (!(c12_b_t <= 1.0));

  c12_e_b = muDoubleScalarLog(c12_b_t);
  c12_e_y = -2.0 * c12_e_b;
  c12_c_a = c12_c_r;
  c12_f_b = muDoubleScalarSqrt(c12_e_y / c12_b_t);
  c12_c_r = c12_c_a * c12_f_b;
  *c12_e_state = c12_g_state;
  return c12_c_r;
}

static real_T c12_b_eml_rand_shr3cong
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state[2])
{
  uint32_T c12_icng;
  uint32_T c12_jsr;
  uint32_T c12_b_icng;
  uint32_T c12_b_jsr;
  uint32_T c12_c_jsr;
  uint32_T c12_c_icng;
  uint32_T c12_ui;
  uint32_T c12_b_ui;
  uint32_T c12_j;
  uint32_T c12_jp1;
  int32_T c12_i;
  real_T c12_a;
  real_T c12_y;
  real_T c12_b_a;
  static real_T c12_dv3[65] = { 0.340945, 0.4573146, 0.5397793, 0.6062427,
    0.6631691, 0.7136975, 0.7596125, 0.8020356, 0.8417227, 0.8792102, 0.9148948,
    0.9490791, 0.9820005, 1.0138492, 1.044781, 1.0749254, 1.1043917, 1.1332738,
    1.161653, 1.189601, 1.2171815, 1.2444516, 1.2714635, 1.298265, 1.3249008,
    1.3514125, 1.3778399, 1.4042211, 1.4305929, 1.4569915, 1.4834527, 1.5100122,
    1.5367061, 1.5635712, 1.5906454, 1.617968, 1.6455802, 1.6735255, 1.7018503,
    1.7306045, 1.7598422, 1.7896223, 1.8200099, 1.851077, 1.8829044, 1.9155831,
    1.9492166, 1.9839239, 2.0198431, 2.0571356, 2.095993, 2.136645, 2.1793713,
    2.2245175, 2.2725186, 2.3239338, 2.3795008, 2.4402218, 2.5075117, 2.5834658,
    2.6713916, 2.7769942, 2.7769942, 2.7769942, 2.7769942 };

  real_T c12_b;
  real_T c12_b_r;
  real_T c12_x;
  real_T c12_b_x;
  real_T c12_b_y;
  real_T c12_c_r;
  real_T c12_c_x;
  real_T c12_d_x;
  real_T c12_c_y;
  real_T c12_A;
  real_T c12_B;
  real_T c12_e_x;
  real_T c12_d_y;
  real_T c12_f_x;
  real_T c12_e_y;
  real_T c12_g_x;
  uint32_T c12_d_icng;
  uint32_T c12_d_jsr;
  uint32_T c12_e_jsr;
  uint32_T c12_e_icng;
  uint32_T c12_c_ui;
  real_T c12_c_a;
  real_T c12_f_y;
  real_T c12_g_y;
  real_T c12_s;
  real_T c12_b_b;
  real_T c12_h_y;
  real_T c12_c_b;
  real_T c12_i_y;
  real_T c12_d_b;
  real_T c12_j_y;
  real_T c12_e_b;
  real_T c12_k_y;
  real_T c12_d_a;
  real_T c12_f_b;
  real_T c12_l_y;
  real_T c12_g_b;
  real_T c12_m_y;
  real_T c12_h_b;
  real_T c12_n_y;
  real_T c12_e_a;
  real_T c12_i_b;
  real_T c12_o_y;
  real_T c12_h_x;
  real_T c12_i_x;
  real_T c12_f_a;
  real_T c12_p_y;
  real_T c12_b_A;
  real_T c12_b_B;
  real_T c12_j_x;
  real_T c12_q_y;
  real_T c12_k_x;
  real_T c12_r_y;
  real_T c12_s_y;
  real_T c12_j_b;
  real_T c12_t_y;
  real_T c12_g_a;
  real_T c12_k_b;
  real_T c12_u_y;
  uint32_T c12_f_icng;
  uint32_T c12_f_jsr;
  uint32_T c12_g_jsr;
  uint32_T c12_g_icng;
  uint32_T c12_d_ui;
  real_T c12_h_a;
  real_T c12_v_y;
  real_T c12_c_A;
  real_T c12_l_x;
  real_T c12_m_x;
  uint32_T c12_h_icng;
  uint32_T c12_h_jsr;
  uint32_T c12_i_jsr;
  uint32_T c12_i_icng;
  uint32_T c12_e_ui;
  real_T c12_i_a;
  real_T c12_w_y;
  real_T c12_l_b;
  real_T c12_x_y;
  real_T c12_j_a;
  real_T c12_m_b;
  real_T c12_y_y;
  c12_icng = c12_e_state[0];
  c12_jsr = c12_e_state[1];
  c12_b_icng = c12_icng;
  c12_b_jsr = c12_jsr;
  c12_c_jsr = c12_b_jsr;
  c12_c_icng = c12_b_icng;
  c12_c_icng = 69069U * c12_c_icng + 1234567U;
  c12_c_jsr ^= c12_c_jsr << 13U;
  c12_c_jsr ^= c12_c_jsr >> 17U;
  c12_c_jsr ^= c12_c_jsr << 5U;
  c12_ui = c12_c_icng + c12_c_jsr;
  c12_icng = c12_c_icng;
  c12_jsr = c12_c_jsr;
  c12_b_ui = c12_ui;
  c12_j = (c12_b_ui & 63U) + 1U;
  c12_j;
  c12_jp1 = c12_j + 1U;
  c12_i = (int32_T)c12_b_ui;
  c12_a = (real_T)c12_i;
  c12_y = c12_a * 4.6566128730773926E-10;
  c12_b_a = c12_y;
  c12_b = c12_dv3[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    (uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_jp1), 1, 65, 1, 0) - 1];
  c12_b_r = c12_b_a * c12_b;
  c12_x = c12_b_r;
  c12_b_x = c12_x;
  c12_b_y = muDoubleScalarAbs(c12_b_x);
  if (c12_b_y <= c12_dv3[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
       (int32_T)(uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_j), 1, 65, 1, 0) -
      1]) {
    c12_c_r = c12_b_r;
  } else {
    c12_c_x = c12_b_r;
    c12_d_x = c12_c_x;
    c12_c_y = muDoubleScalarAbs(c12_d_x);
    c12_A = c12_c_y - c12_dv3[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)(uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_j), 1, 65, 1, 0) - 1];
    c12_B = c12_dv3[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      (uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_jp1), 1, 65, 1, 0) - 1] -
      c12_dv3[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      (uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_j), 1, 65, 1, 0) - 1];
    c12_e_x = c12_A;
    c12_d_y = c12_B;
    c12_f_x = c12_e_x;
    c12_e_y = c12_d_y;
    c12_g_x = c12_f_x / c12_e_y;
    c12_d_icng = c12_icng;
    c12_d_jsr = c12_jsr;
    c12_e_jsr = c12_d_jsr;
    c12_e_icng = c12_d_icng;
    c12_e_icng = 69069U * c12_e_icng + 1234567U;
    c12_e_jsr ^= c12_e_jsr << 13U;
    c12_e_jsr ^= c12_e_jsr >> 17U;
    c12_e_jsr ^= c12_e_jsr << 5U;
    c12_c_ui = c12_e_icng + c12_e_jsr;
    c12_icng = c12_e_icng;
    c12_jsr = c12_e_jsr;
    c12_b_ui = c12_c_ui;
    c12_i = (int32_T)c12_b_ui;
    c12_c_a = (real_T)c12_i;
    c12_f_y = c12_c_a * 2.328306436538696E-10;
    c12_g_y = 0.5 + c12_f_y;
    c12_s = c12_g_x + c12_g_y;
    if (c12_s > 1.301198) {
      if (c12_b_r < 0.0) {
        c12_b_b = c12_g_x;
        c12_h_y = 0.4878992 * c12_b_b;
        c12_c_r = c12_h_y - 0.4878992;
      } else {
        c12_c_b = c12_g_x;
        c12_i_y = 0.4878992 * c12_c_b;
        c12_c_r = 0.4878992 - c12_i_y;
      }
    } else if (c12_s <= 0.9689279) {
      c12_c_r = c12_b_r;
    } else {
      c12_d_b = c12_g_x;
      c12_j_y = 0.4878992 * c12_d_b;
      c12_g_x = 0.4878992 - c12_j_y;
      c12_e_b = c12_g_x;
      c12_k_y = -0.5 * c12_e_b;
      c12_d_a = c12_k_y;
      c12_f_b = c12_g_x;
      c12_l_y = c12_d_a * c12_f_b;
      c12_g_b = muDoubleScalarExp(c12_l_y);
      c12_m_y = 12.37586 * c12_g_b;
      if (c12_g_y > 12.67706 - c12_m_y) {
        if (c12_b_r < 0.0) {
          c12_c_r = -c12_g_x;
        } else {
          c12_c_r = c12_g_x;
        }
      } else {
        c12_h_b = c12_dv3[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_jp1), 1, 65, 1,
          0) - 1];
        c12_n_y = -0.5 * c12_h_b;
        c12_e_a = c12_n_y;
        c12_i_b = c12_dv3[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_jp1), 1, 65, 1,
          0) - 1];
        c12_o_y = c12_e_a * c12_i_b;
        c12_h_x = c12_o_y;
        c12_i_x = c12_h_x;
        c12_i_x = muDoubleScalarExp(c12_i_x);
        c12_f_a = c12_g_y;
        c12_p_y = c12_f_a * 0.01958303;
        c12_b_A = c12_p_y;
        c12_b_B = c12_dv3[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_jp1), 1, 65, 1,
          0) - 1];
        c12_j_x = c12_b_A;
        c12_q_y = c12_b_B;
        c12_k_x = c12_j_x;
        c12_r_y = c12_q_y;
        c12_s_y = c12_k_x / c12_r_y;
        c12_j_b = c12_b_r;
        c12_t_y = -0.5 * c12_j_b;
        c12_g_a = c12_t_y;
        c12_k_b = c12_b_r;
        c12_u_y = c12_g_a * c12_k_b;
        if (c12_i_x + c12_s_y <= muDoubleScalarExp(c12_u_y)) {
          c12_c_r = c12_b_r;
        } else {
          do {
            c12_f_icng = c12_icng;
            c12_f_jsr = c12_jsr;
            c12_g_jsr = c12_f_jsr;
            c12_g_icng = c12_f_icng;
            c12_g_icng = 69069U * c12_g_icng + 1234567U;
            c12_g_jsr ^= c12_g_jsr << 13U;
            c12_g_jsr ^= c12_g_jsr >> 17U;
            c12_g_jsr ^= c12_g_jsr << 5U;
            c12_d_ui = c12_g_icng + c12_g_jsr;
            c12_icng = c12_g_icng;
            c12_jsr = c12_g_jsr;
            c12_b_ui = c12_d_ui;
            c12_i = (int32_T)c12_b_ui;
            c12_h_a = (real_T)c12_i;
            c12_v_y = c12_h_a * 2.328306436538696E-10;
            c12_c_A = muDoubleScalarLog(0.5 + c12_v_y);
            c12_l_x = c12_c_A;
            c12_m_x = c12_l_x;
            c12_g_x = c12_m_x / 2.776994;
            c12_h_icng = c12_icng;
            c12_h_jsr = c12_jsr;
            c12_i_jsr = c12_h_jsr;
            c12_i_icng = c12_h_icng;
            c12_i_icng = 69069U * c12_i_icng + 1234567U;
            c12_i_jsr ^= c12_i_jsr << 13U;
            c12_i_jsr ^= c12_i_jsr >> 17U;
            c12_i_jsr ^= c12_i_jsr << 5U;
            c12_e_ui = c12_i_icng + c12_i_jsr;
            c12_icng = c12_i_icng;
            c12_jsr = c12_i_jsr;
            c12_b_ui = c12_e_ui;
            c12_i = (int32_T)c12_b_ui;
            c12_i_a = (real_T)c12_i;
            c12_w_y = c12_i_a * 2.328306436538696E-10;
            c12_l_b = muDoubleScalarLog(0.5 + c12_w_y);
            c12_x_y = -2.0 * c12_l_b;
            c12_j_a = c12_g_x;
            c12_m_b = c12_g_x;
            c12_y_y = c12_j_a * c12_m_b;
          } while (!(c12_x_y > c12_y_y));

          if (c12_b_r < 0.0) {
            c12_c_r = c12_g_x - 2.776994;
          } else {
            c12_c_r = 2.776994 - c12_g_x;
          }
        }
      }
    }
  }

  c12_e_state[0] = c12_icng;
  c12_e_state[1] = c12_jsr;
  return c12_c_r;
}

static void c12_b_twister_state_vector
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_mt[625], real_T c12_seed)
{
  real_T c12_d7;
  uint32_T c12_u6;
  uint32_T c12_r;
  int32_T c12_mti;
  real_T c12_b_mti;
  real_T c12_d8;
  uint32_T c12_u7;
  c12_d7 = c12_seed;
  if (c12_d7 < 4.294967296E+9) {
    if (c12_d7 >= 0.0) {
      c12_u6 = (uint32_T)c12_d7;
    } else {
      c12_u6 = 0U;
    }
  } else if (c12_d7 >= 4.294967296E+9) {
    c12_u6 = MAX_uint32_T;
  } else {
    c12_u6 = 0U;
  }

  c12_r = c12_u6;
  c12_mt[0] = c12_r;
  for (c12_mti = 0; c12_mti < 623; c12_mti++) {
    c12_b_mti = 2.0 + (real_T)c12_mti;
    c12_d8 = muDoubleScalarRound(c12_b_mti - 1.0);
    if (c12_d8 < 4.294967296E+9) {
      if (c12_d8 >= 0.0) {
        c12_u7 = (uint32_T)c12_d8;
      } else {
        c12_u7 = 0U;
      }
    } else if (c12_d8 >= 4.294967296E+9) {
      c12_u7 = MAX_uint32_T;
    } else {
      c12_u7 = 0U;
    }

    c12_r = (c12_r ^ c12_r >> 30U) * 1812433253U + c12_u7;
    c12_mt[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", c12_b_mti), 1, 625, 1, 0) - 1] = c12_r;
  }

  c12_mt[624] = 624U;
}

static real_T c12_c_eml_rand_mt19937ar
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_e_state[625])
{
  uint32_T c12_u32[2];
  uint32_T c12_i;
  uint32_T c12_ip1;
  real_T c12_a;
  real_T c12_y;
  real_T c12_b_a;
  real_T c12_b_y;
  real_T c12_u;
  real_T c12_c_a;
  static real_T c12_dv4[257] = { 0.0, 0.215241895984875, 0.286174591792068,
    0.335737519214422, 0.375121332878378, 0.408389134611989, 0.43751840220787,
    0.46363433679088, 0.487443966139235, 0.50942332960209, 0.529909720661557,
    0.549151702327164, 0.567338257053817, 0.584616766106378, 0.601104617755991,
    0.61689699000775, 0.63207223638606, 0.646695714894993, 0.660822574244419,
    0.674499822837293, 0.687767892795788, 0.700661841106814, 0.713212285190975,
    0.725446140909999, 0.737387211434295, 0.749056662017815, 0.760473406430107,
    0.771654424224568, 0.782615023307232, 0.793369058840623, 0.80392911698997,
    0.814306670135215, 0.824512208752291, 0.834555354086381, 0.844444954909153,
    0.854189171008163, 0.863795545553308, 0.87327106808886, 0.882622229585165,
    0.891855070732941, 0.900975224461221, 0.909987953496718, 0.91889818364959,
    0.927710533401999, 0.936429340286575, 0.945058684468165, 0.953602409881086,
    0.96206414322304, 0.970447311064224, 0.978755155294224, 0.986990747099062,
    0.99515699963509, 1.00325667954467, 1.01129241744, 1.01926671746548,
    1.02718196603564, 1.03504043983344, 1.04284431314415, 1.05059566459093,
    1.05829648333067, 1.06594867476212, 1.07355406579244, 1.0811144097034,
    1.08863139065398, 1.09610662785202, 1.10354167942464, 1.11093804601357,
    1.11829717411934, 1.12562045921553, 1.13290924865253, 1.14016484436815,
    1.14738850542085, 1.15458145035993, 1.16174485944561, 1.16887987673083,
    1.17598761201545, 1.18306914268269, 1.19012551542669, 1.19715774787944,
    1.20416683014438, 1.2111537262437, 1.21811937548548, 1.22506469375653,
    1.23199057474614, 1.23889789110569, 1.24578749554863, 1.2526602218949,
    1.25951688606371, 1.26635828701823, 1.27318520766536, 1.27999841571382,
    1.28679866449324, 1.29358669373695, 1.30036323033084, 1.30712898903073,
    1.31388467315022, 1.32063097522106, 1.32736857762793, 1.33409815321936,
    1.3408203658964, 1.34753587118059, 1.35424531676263, 1.36094934303328,
    1.36764858359748, 1.37434366577317, 1.38103521107586, 1.38772383568998,
    1.39441015092814, 1.40109476367925, 1.4077782768464, 1.41446128977547,
    1.42114439867531, 1.42782819703026, 1.43451327600589, 1.44120022484872,
    1.44788963128058, 1.45458208188841, 1.46127816251028, 1.46797845861808,
    1.47468355569786, 1.48139403962819, 1.48811049705745, 1.49483351578049,
    1.50156368511546, 1.50830159628131, 1.51504784277671, 1.521803020761,
    1.52856772943771, 1.53534257144151, 1.542128153229, 1.54892508547417,
    1.55573398346918, 1.56255546753104, 1.56939016341512, 1.57623870273591,
    1.58310172339603, 1.58997987002419, 1.59687379442279, 1.60378415602609,
    1.61071162236983, 1.61765686957301, 1.62462058283303, 1.63160345693487,
    1.63860619677555, 1.64562951790478, 1.65267414708306, 1.65974082285818,
    1.66683029616166, 1.67394333092612, 1.68108070472517, 1.68824320943719,
    1.69543165193456, 1.70264685479992, 1.7098896570713, 1.71716091501782,
    1.72446150294804, 1.73179231405296, 1.73915426128591, 1.74654827828172,
    1.75397532031767, 1.76143636531891, 1.76893241491127, 1.77646449552452,
    1.78403365954944, 1.79164098655216, 1.79928758454972, 1.80697459135082,
    1.81470317596628, 1.82247454009388, 1.83028991968276, 1.83815058658281,
    1.84605785028518, 1.8540130597602, 1.86201760539967, 1.87007292107127,
    1.878180486293, 1.88634182853678, 1.8945585256707, 1.90283220855043,
    1.91116456377125, 1.91955733659319, 1.92801233405266, 1.93653142827569,
    1.94511656000868, 1.95376974238465, 1.96249306494436, 1.97128869793366,
    1.98015889690048, 1.98910600761744, 1.99813247135842, 2.00724083056053,
    2.0164337349062, 2.02571394786385, 2.03508435372962, 2.04454796521753,
    2.05410793165065, 2.06376754781173, 2.07353026351874, 2.0833996939983,
    2.09337963113879, 2.10347405571488, 2.11368715068665, 2.12402331568952,
    2.13448718284602, 2.14508363404789, 2.15581781987674, 2.16669518035431,
    2.17772146774029, 2.18890277162636, 2.20024554661128, 2.21175664288416,
    2.22344334009251, 2.23531338492992, 2.24737503294739, 2.25963709517379,
    2.27210899022838, 2.28480080272449, 2.29772334890286, 2.31088825060137,
    2.32430801887113, 2.33799614879653, 2.35196722737914, 2.36623705671729,
    2.38082279517208, 2.39574311978193, 2.41101841390112, 2.42667098493715,
    2.44272531820036, 2.4592083743347, 2.47614993967052, 2.49358304127105,
    2.51154444162669, 2.53007523215985, 2.54922155032478, 2.56903545268184,
    2.58957598670829, 2.61091051848882, 2.63311639363158, 2.65628303757674,
    2.68051464328574, 2.70593365612306, 2.73268535904401, 2.76094400527999,
    2.79092117400193, 2.82287739682644, 2.85713873087322, 2.89412105361341,
    2.93436686720889, 2.97860327988184, 3.02783779176959, 3.08352613200214,
    3.147889289518, 3.2245750520478, 3.32024473383983, 3.44927829856143,
    3.65415288536101, 3.91075795952492 };

  real_T c12_b;
  real_T c12_b_r;
  real_T c12_b_u;
  real_T c12_d_a;
  static real_T c12_dv5[257] = { 1.0, 0.977101701267673, 0.959879091800108,
    0.9451989534423, 0.932060075959231, 0.919991505039348, 0.908726440052131,
    0.898095921898344, 0.887984660755834, 0.878309655808918, 0.869008688036857,
    0.860033621196332, 0.851346258458678, 0.842915653112205, 0.834716292986884,
    0.826726833946222, 0.818929191603703, 0.811307874312656, 0.803849483170964,
    0.796542330422959, 0.789376143566025, 0.782341832654803, 0.775431304981187,
    0.768637315798486, 0.761953346836795, 0.755373506507096, 0.748892447219157,
    0.742505296340151, 0.736207598126863, 0.729995264561476, 0.72386453346863,
    0.717811932630722, 0.711834248878248, 0.705928501332754, 0.700091918136512,
    0.694321916126117, 0.688616083004672, 0.682972161644995, 0.677388036218774,
    0.671861719897082, 0.66639134390875, 0.660975147776663, 0.655611470579697,
    0.650298743110817, 0.645035480820822, 0.639820277453057, 0.634651799287624,
    0.629528779924837, 0.624450015547027, 0.619414360605834, 0.614420723888914,
    0.609468064925773, 0.604555390697468, 0.599681752619125, 0.594846243767987,
    0.590047996332826, 0.585286179263371, 0.580559996100791, 0.575868682972354,
    0.571211506735253, 0.566587763256165, 0.561996775814525, 0.557437893618766,
    0.552910490425833, 0.548413963255266, 0.543947731190026, 0.539511234256952,
    0.535103932380458, 0.530725304403662, 0.526374847171684, 0.522052074672322,
    0.517756517229756, 0.513487720747327, 0.509245245995748, 0.505028667943468,
    0.500837575126149, 0.49667156905249, 0.492530263643869, 0.488413284705458,
    0.484320269426683, 0.480250865909047, 0.476204732719506, 0.47218153846773,
    0.468180961405694, 0.464202689048174, 0.460246417812843, 0.456311852678716,
    0.452398706861849, 0.448506701507203, 0.444635565395739, 0.440785034665804,
    0.436954852547985, 0.433144769112652, 0.429354541029442, 0.425583931338022,
    0.421832709229496, 0.418100649837848, 0.414387534040891, 0.410693148270188,
    0.407017284329473, 0.403359739221114, 0.399720314980197, 0.396098818515832,
    0.392495061459315, 0.388908860018789, 0.385340034840077, 0.381788410873393,
    0.378253817245619, 0.374736087137891, 0.371235057668239, 0.367750569779032,
    0.364282468129004, 0.360830600989648, 0.357394820145781, 0.353974980800077,
    0.350570941481406, 0.347182563956794, 0.343809713146851, 0.340452257044522,
    0.337110066637006, 0.333783015830718, 0.330470981379163, 0.327173842813601,
    0.323891482376391, 0.320623784956905, 0.317370638029914, 0.314131931596337,
    0.310907558126286, 0.307697412504292, 0.30450139197665, 0.301319396100803,
    0.298151326696685, 0.294997087799962, 0.291856585617095, 0.288729728482183,
    0.285616426815502, 0.282516593083708, 0.279430141761638, 0.276356989295668,
    0.273297054068577, 0.270250256365875, 0.267216518343561, 0.264195763997261,
    0.261187919132721, 0.258192911337619, 0.255210669954662, 0.252241126055942,
    0.249284212418529, 0.246339863501264, 0.24340801542275, 0.240488605940501,
    0.237581574431238, 0.23468686187233, 0.231804410824339, 0.228934165414681,
    0.226076071322381, 0.223230075763918, 0.220396127480152, 0.217574176724331,
    0.214764175251174, 0.211966076307031, 0.209179834621125, 0.206405406397881,
    0.203642749310335, 0.200891822494657, 0.198152586545776, 0.195425003514135,
    0.192709036903589, 0.190004651670465, 0.187311814223801, 0.1846304924268,
    0.181960655599523, 0.179302274522848, 0.176655321443735, 0.174019770081839,
    0.171395595637506, 0.168782774801212, 0.166181285764482, 0.163591108232366,
    0.161012223437511, 0.158444614155925, 0.15588826472448, 0.153343161060263,
    0.150809290681846, 0.148286642732575, 0.145775208005994, 0.143274978973514,
    0.140785949814445, 0.138308116448551, 0.135841476571254, 0.133386029691669,
    0.130941777173644, 0.12850872228, 0.126086870220186, 0.123676228201597,
    0.12127680548479, 0.11888861344291, 0.116511665625611, 0.114145977827839,
    0.111791568163838, 0.109448457146812, 0.107116667774684, 0.104796225622487,
    0.102487158941935, 0.10018949876881, 0.0979032790388625, 0.095628536713009,
    0.093365311912691, 0.0911136480663738, 0.0888735920682759,
    0.0866451944505581, 0.0844285095703535, 0.082223595813203,
    0.0800305158146631, 0.0778493367020961, 0.0756801303589272,
    0.0735229737139814, 0.0713779490588905, 0.0692451443970068,
    0.0671246538277886, 0.065016577971243, 0.0629210244377582, 0.06083810834954,
    0.0587679529209339, 0.0567106901062031, 0.0546664613248891,
    0.0526354182767924, 0.0506177238609479, 0.0486135532158687,
    0.0466230949019305, 0.0446465522512946, 0.0426841449164746,
    0.0407361106559411, 0.0388027074045262, 0.0368842156885674,
    0.0349809414617162, 0.0330932194585786, 0.0312214171919203,
    0.0293659397581334, 0.0275272356696031, 0.0257058040085489,
    0.0239022033057959, 0.0221170627073089, 0.0203510962300445,
    0.0186051212757247, 0.0168800831525432, 0.0151770883079353,
    0.0134974506017399, 0.0118427578579079, 0.0102149714397015,
    0.00861658276939875, 0.00705087547137324, 0.00552240329925101,
    0.00403797259336304, 0.00260907274610216, 0.0012602859304986,
    0.000477467764609386 };

  real_T c12_b_b;
  real_T c12_c_y;
  real_T c12_c_b;
  real_T c12_d_y;
  real_T c12_e_a;
  real_T c12_d_b;
  real_T c12_e_y;
  real_T c12_x;
  real_T c12_b_x;
  real_T c12_c_u;
  real_T c12_f_a;
  real_T c12_c_x;
  real_T c12_d_u;
  real_T c12_e_b;
  real_T c12_f_y;
  real_T c12_g_a;
  real_T c12_f_b;
  real_T c12_g_y;
  int32_T exitg1;
  c12_assert_valid_state(chartInstance);
  do {
    exitg1 = 0;
    c12_b_genrand_uint32_vector(chartInstance, c12_e_state, c12_u32);
    c12_i = (c12_u32[1] >> 24U) + 1U;
    c12_ip1 = c12_i + 1U;
    c12_a = (real_T)(c12_u32[0] >> 3U);
    c12_y = c12_a * 1.6777216E+7;
    c12_b_a = c12_y + (real_T)(c12_u32[1] & 16777215U);
    c12_b_y = c12_b_a * 2.2204460492503131E-16;
    c12_u = c12_b_y - 1.0;
    c12_c_a = c12_u;
    c12_b = c12_dv4[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      (uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_ip1), 1, 257, 1, 0) - 1];
    c12_b_r = c12_c_a * c12_b;
    if (c12_abs(chartInstance, c12_b_r) <= c12_dv4[(int32_T)(uint32_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)(uint32_T)_SFD_INTEGER_CHECK("",
          (real_T)c12_i), 1, 257, 1, 0) - 1]) {
      exitg1 = 1;
    } else if ((real_T)c12_i < 256.0) {
      c12_b_u = c12_c_genrandu(chartInstance, c12_e_state);
      c12_u = c12_b_u;
      c12_d_a = c12_u;
      c12_b_b = c12_dv5[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)(uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_i), 1, 257, 1, 0)
        - 1] - c12_dv5[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)(uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_ip1), 1, 257, 1, 0)
        - 1];
      c12_c_y = c12_d_a * c12_b_b;
      c12_c_b = c12_b_r;
      c12_d_y = -0.5 * c12_c_b;
      c12_e_a = c12_d_y;
      c12_d_b = c12_b_r;
      c12_e_y = c12_e_a * c12_d_b;
      c12_x = c12_e_y;
      c12_b_x = c12_x;
      c12_b_x = muDoubleScalarExp(c12_b_x);
      if (c12_dv5[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           (uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_ip1), 1, 257, 1, 0) - 1]
          + c12_c_y < c12_b_x) {
        exitg1 = 1;
      }
    } else {
      do {
        c12_c_u = c12_c_genrandu(chartInstance, c12_e_state);
        c12_u = c12_c_u;
        c12_f_a = muDoubleScalarLog(c12_u);
        c12_c_x = c12_f_a * 0.273661237329758;
        c12_d_u = c12_c_genrandu(chartInstance, c12_e_state);
        c12_u = c12_d_u;
        c12_e_b = muDoubleScalarLog(c12_u);
        c12_f_y = -2.0 * c12_e_b;
        c12_g_a = c12_c_x;
        c12_f_b = c12_c_x;
        c12_g_y = c12_g_a * c12_f_b;
      } while (!(c12_f_y > c12_g_y));

      if (c12_b_r < 0.0) {
        c12_b_r = c12_c_x - 3.65415288536101;
      } else {
        c12_b_r = 3.65415288536101 - c12_c_x;
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return c12_b_r;
}

static void c12_b_genrand_uint32_vector
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, uint32_T
   c12_mt[625], uint32_T c12_u[2])
{
  int32_T c12_i55;
  int32_T c12_j;
  real_T c12_b_j;
  uint32_T c12_mti;
  int32_T c12_kk;
  real_T c12_b_kk;
  uint32_T c12_y;
  uint32_T c12_b_y;
  uint32_T c12_c_y;
  int32_T c12_c_kk;
  uint32_T c12_d_y;
  uint32_T c12_e_y;
  uint32_T c12_f_y;
  uint32_T c12_g_y;
  for (c12_i55 = 0; c12_i55 < 2; c12_i55++) {
    c12_u[c12_i55] = 0U;
  }

  for (c12_j = 0; c12_j < 2; c12_j++) {
    c12_b_j = 1.0 + (real_T)c12_j;
    c12_mti = c12_mt[624] + 1U;
    if ((real_T)c12_mti >= 625.0) {
      for (c12_kk = 0; c12_kk < 227; c12_kk++) {
        c12_b_kk = 1.0 + (real_T)c12_kk;
        c12_y = (c12_mt[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
                  (int32_T)_SFD_INTEGER_CHECK("", c12_b_kk), 1, 625, 1, 0) - 1]
                 & 2147483648U) | (c12_mt[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          c12_b_kk + 1.0), 1, 625, 1, 0) - 1] & 2147483647U);
        c12_b_y = c12_y;
        c12_c_y = c12_b_y;
        if ((real_T)(c12_c_y & 1U) == 0.0) {
          c12_c_y >>= 1U;
        } else {
          c12_c_y = c12_c_y >> 1U ^ 2567483615U;
        }

        c12_mt[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c12_b_kk), 1, 625, 1, 0) - 1] = c12_mt[(int32_T)
          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          c12_b_kk + 397.0), 1, 625, 1, 0) - 1] ^ c12_c_y;
      }

      for (c12_c_kk = 0; c12_c_kk < 396; c12_c_kk++) {
        c12_b_kk = 228.0 + (real_T)c12_c_kk;
        c12_y = (c12_mt[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
                  (int32_T)_SFD_INTEGER_CHECK("", c12_b_kk), 1, 625, 1, 0) - 1]
                 & 2147483648U) | (c12_mt[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          c12_b_kk + 1.0), 1, 625, 1, 0) - 1] & 2147483647U);
        c12_d_y = c12_y;
        c12_e_y = c12_d_y;
        if ((real_T)(c12_e_y & 1U) == 0.0) {
          c12_e_y >>= 1U;
        } else {
          c12_e_y = c12_e_y >> 1U ^ 2567483615U;
        }

        c12_mt[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c12_b_kk), 1, 625, 1, 0) - 1] = c12_mt[(int32_T)
          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (c12_b_kk + 1.0) - 228.0), 1, 625, 1, 0) - 1] ^ c12_e_y;
      }

      c12_y = (c12_mt[623] & 2147483648U) | (c12_mt[0] & 2147483647U);
      c12_f_y = c12_y;
      c12_g_y = c12_f_y;
      if ((real_T)(c12_g_y & 1U) == 0.0) {
        c12_g_y >>= 1U;
      } else {
        c12_g_y = c12_g_y >> 1U ^ 2567483615U;
      }

      c12_mt[623] = c12_mt[396] ^ c12_g_y;
      c12_mti = 1U;
    }

    c12_y = c12_mt[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      (uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_mti), 1, 625, 1, 0) - 1];
    c12_mt[624] = c12_mti;
    c12_y ^= c12_y >> 11U;
    c12_y ^= c12_y << 7U & 2636928640U;
    c12_y ^= c12_y << 15U & 4022730752U;
    c12_y ^= c12_y >> 18U;
    c12_u[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", c12_b_j), 1, 2, 1, 0) - 1] = c12_y;
  }
}

static real_T c12_c_genrandu(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, uint32_T c12_mt[625])
{
  real_T c12_r;
  uint32_T c12_u[2];
  real_T c12_a;
  real_T c12_y;
  real_T c12_b;
  boolean_T c12_b0;
  boolean_T c12_isvalid;
  int32_T c12_k;
  int32_T c12_b_a;
  real_T c12_d9;
  boolean_T guard1 = FALSE;
  int32_T exitg1;
  boolean_T exitg2;

  /* <LEGAL>   This is a uniform (0,1) pseudorandom number generator based on: */
  /* <LEGAL> */
  /* <LEGAL>    A C-program for MT19937, with initialization improved 2002/1/26. */
  /* <LEGAL>    Coded by Takuji Nishimura and Makoto Matsumoto. */
  /* <LEGAL> */
  /* <LEGAL>    Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura, */
  /* <LEGAL>    All rights reserved. */
  /* <LEGAL> */
  /* <LEGAL>    Redistribution and use in source and binary forms, with or without */
  /* <LEGAL>    modification, are permitted provided that the following conditions */
  /* <LEGAL>    are met: */
  /* <LEGAL> */
  /* <LEGAL>      1. Redistributions of source code must retain the above copyright */
  /* <LEGAL>         notice, this list of conditions and the following disclaimer. */
  /* <LEGAL> */
  /* <LEGAL>      2. Redistributions in binary form must reproduce the above copyright */
  /* <LEGAL>         notice, this list of conditions and the following disclaimer in the */
  /* <LEGAL>         documentation and/or other materials provided with the distribution. */
  /* <LEGAL> */
  /* <LEGAL>      3. The names of its contributors may not be used to endorse or promote */
  /* <LEGAL>         products derived from this software without specific prior written */
  /* <LEGAL>         permission. */
  /* <LEGAL> */
  /* <LEGAL>    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS */
  /* <LEGAL>    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT */
  /* <LEGAL>    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR */
  /* <LEGAL>    A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR */
  /* <LEGAL>    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, */
  /* <LEGAL>    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, */
  /* <LEGAL>    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR */
  /* <LEGAL>    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF */
  /* <LEGAL>    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING */
  /* <LEGAL>    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS */
  /* <LEGAL>    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
  do {
    exitg1 = 0;
    c12_b_genrand_uint32_vector(chartInstance, c12_mt, c12_u);
    c12_u[0] >>= 5U;
    c12_u[1] >>= 6U;
    c12_a = (real_T)c12_u[0];
    c12_y = c12_a * 6.7108864E+7;
    c12_b = c12_y + (real_T)c12_u[1];
    c12_r = 1.1102230246251565E-16 * c12_b;
    if (c12_r == 0.0) {
      guard1 = FALSE;
      if ((real_T)c12_mt[624] >= 1.0) {
        if ((real_T)c12_mt[624] < 625.0) {
          c12_b0 = TRUE;
        } else {
          guard1 = TRUE;
        }
      } else {
        guard1 = TRUE;
      }

      if (guard1 == TRUE) {
        c12_b0 = FALSE;
      }

      c12_isvalid = c12_b0;
      if (c12_isvalid) {
        c12_isvalid = FALSE;
        c12_k = 1;
        exitg2 = FALSE;
        while ((exitg2 == FALSE) && (c12_k < 625)) {
          if ((real_T)c12_mt[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
               _SFD_INTEGER_CHECK("", (real_T)c12_k), 1, 625, 1, 0) - 1] == 0.0)
          {
            c12_b_a = c12_k + 1;
            c12_k = c12_b_a;
          } else {
            c12_isvalid = TRUE;
            exitg2 = TRUE;
          }
        }
      }

      if (!c12_isvalid) {
        c12_eml_error(chartInstance);
        c12_d9 = 5489.0;
        c12_b_twister_state_vector(chartInstance, c12_mt, c12_d9);
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return c12_r;
}

static void init_dsm_address_info
  (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
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

void sf_c12_modelo_FK_simul_coleta_dados_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3507567924U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3661141093U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3159065500U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1573228020U);
}

mxArray *sf_c12_modelo_FK_simul_coleta_dados_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("6nG4JuqWYqurm78QOW277G");
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

mxArray *sf_c12_modelo_FK_simul_coleta_dados_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c12_modelo_FK_simul_coleta_dados
  (void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x8'type','srcId','name','auxInfo'{{M[1],M[5],T\"wr\",},{M[4],M[0],T\"method\",S'l','i','p'{{M1x2[512 518],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand.m\"}}},{M[4],M[0],T\"method\",S'l','i','p'{{M1x2[638 644],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_randn.m\"}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[165 170],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m\"}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[166 171],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m\"}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[165 170],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m\"}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[645 650],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_randn.m\"}}},{M[8],M[0],T\"is_active_c12_modelo_FK_simul_coleta_dados\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 8, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c12_modelo_FK_simul_coleta_dados_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
    chartInstance = (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modelo_FK_simul_coleta_dadosMachineNumber_,
           12,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"w");
          _SFD_SET_DATA_PROPS(1,2,0,1,"wr");
          _SFD_SET_DATA_PROPS(2,1,1,0,"vs");
          _SFD_SET_DATA_PROPS(3,1,1,0,"vo");
          _SFD_SET_DATA_PROPS(4,1,1,0,"vn");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,92);
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
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)
            c12_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c12_w)[3];
          real_T (*c12_wr)[3];
          real_T (*c12_vs)[3];
          real_T (*c12_vo)[3];
          real_T (*c12_vn)[3];
          c12_vn = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c12_vo = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c12_vs = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c12_wr = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c12_w = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c12_w);
          _SFD_SET_DATA_VALUE_PTR(1U, *c12_wr);
          _SFD_SET_DATA_VALUE_PTR(2U, *c12_vs);
          _SFD_SET_DATA_VALUE_PTR(3U, *c12_vo);
          _SFD_SET_DATA_VALUE_PTR(4U, *c12_vn);
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
  return "ZjRXr2c4RjuVprmIDqSzDH";
}

static void sf_opaque_initialize_c12_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c12_modelo_FK_simul_coleta_dados
    ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
  initialize_c12_modelo_FK_simul_coleta_dados
    ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c12_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  enable_c12_modelo_FK_simul_coleta_dados
    ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c12_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  disable_c12_modelo_FK_simul_coleta_dados
    ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c12_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  sf_c12_modelo_FK_simul_coleta_dados
    ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c12_modelo_FK_simul_coleta_dados
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c12_modelo_FK_simul_coleta_dados
    ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c12_modelo_FK_simul_coleta_dados();/* state var info */
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

extern void sf_internal_set_sim_state_c12_modelo_FK_simul_coleta_dados(SimStruct*
  S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c12_modelo_FK_simul_coleta_dados();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c12_modelo_FK_simul_coleta_dados
    ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c12_modelo_FK_simul_coleta_dados
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c12_modelo_FK_simul_coleta_dados(S);
}

static void sf_opaque_set_sim_state_c12_modelo_FK_simul_coleta_dados(SimStruct*
  S, const mxArray *st)
{
  sf_internal_set_sim_state_c12_modelo_FK_simul_coleta_dados(S, st);
}

static void sf_opaque_terminate_c12_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_FK_simul_coleta_dados_optimization_info();
    }

    finalize_c12_modelo_FK_simul_coleta_dados
      ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc12_modelo_FK_simul_coleta_dados
    ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c12_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c12_modelo_FK_simul_coleta_dados
      ((SFc12_modelo_FK_simul_coleta_dadosInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c12_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_modelo_FK_simul_coleta_dados_optimization_info();
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
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,12,4);
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
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,12);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2501948247U));
  ssSetChecksum1(S,(3796081315U));
  ssSetChecksum2(S,(158560397U));
  ssSetChecksum3(S,(3545373243U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c12_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c12_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct *)utMalloc
    (sizeof(SFc12_modelo_FK_simul_coleta_dadosInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc12_modelo_FK_simul_coleta_dadosInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c12_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c12_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c12_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c12_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c12_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c12_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c12_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c12_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c12_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.mdlStart = mdlStart_c12_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c12_modelo_FK_simul_coleta_dados;
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

void c12_modelo_FK_simul_coleta_dados_method_dispatcher(SimStruct *S, int_T
  method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c12_modelo_FK_simul_coleta_dados(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c12_modelo_FK_simul_coleta_dados(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c12_modelo_FK_simul_coleta_dados(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c12_modelo_FK_simul_coleta_dados_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
