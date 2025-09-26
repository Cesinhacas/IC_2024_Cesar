/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Tetraedro_model_sem_sim_com_FK_heur_sfun.h"
#include "c19_Tetraedro_model_sem_sim_com_FK_heur.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Tetraedro_model_sem_sim_com_FK_heur_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c19_debug_family_names[28] = { "q_est", "b_est", "Th",
  "Omega4", "M", "q_prop", "b_prop", "GT", "QT", "Omega3_prop", "A_prop",
  "Omega3_est", "A_est", "L", "KK", "PhiT", "SiG", "nargin", "nargout", "w_gyro",
  "Dt", "PT_est", "x_est", "Q", "i_in", "x_prop", "PT_prop", "i_out" };

/* Function Declarations */
static void initialize_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void initialize_params_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void enable_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void disable_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void c19_update_debugger_state_c19_Tetraedro_model_sem_sim_com_FK_heu
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void set_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_st);
static void finalize_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void sf_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void c19_chartstep_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void initSimStructsc19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void registerMessagesc19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c19_machineNumber, uint32_T
  c19_chartNumber);
static const mxArray *c19_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData);
static real_T c19_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_i_out, const char_T *c19_identifier);
static real_T c19_b_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId);
static void c19_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData);
static const mxArray *c19_b_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData);
static void c19_c_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_PT_prop, const char_T *c19_identifier, real_T c19_y[36]);
static void c19_d_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[36]);
static void c19_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData);
static const mxArray *c19_c_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData);
static void c19_e_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_x_prop, const char_T *c19_identifier, real_T c19_y[7]);
static void c19_f_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[7]);
static void c19_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData);
static const mxArray *c19_d_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData);
static const mxArray *c19_e_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData);
static void c19_g_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[9]);
static void c19_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData);
static void c19_h_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[3]);
static void c19_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData);
static const mxArray *c19_f_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData);
static void c19_i_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[4]);
static void c19_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData);
static const mxArray *c19_g_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData);
static void c19_j_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[16]);
static void c19_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData);
static void c19_info_helper(c19_ResolvedFunctionInfo c19_info[60]);
static void c19_eml_scalar_eg
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static real_T c19_norm(SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct
  *chartInstance, real_T c19_x[3]);
static void c19_b_eml_scalar_eg
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void c19_eye(SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct
                    *chartInstance, real_T c19_I[9]);
static void c19_c_eml_scalar_eg
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static real_T c19_mpower(SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct
  *chartInstance, real_T c19_a);
static void c19_d_eml_scalar_eg
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static const mxArray *c19_h_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData);
static int32_T c19_k_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId);
static void c19_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData);
static uint8_T c19_l_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_b_is_active_c19_Tetraedro_model_sem_sim_com_FK_heur, const
   char_T *c19_identifier);
static uint8_T c19_m_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId);
static void init_dsm_address_info
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  chartInstance->c19_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c19_is_active_c19_Tetraedro_model_sem_sim_com_FK_heur = 0U;
}

static void initialize_params_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void enable_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c19_update_debugger_state_c19_Tetraedro_model_sem_sim_com_FK_heu
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  const mxArray *c19_st;
  const mxArray *c19_y = NULL;
  int32_T c19_i0;
  real_T c19_u[36];
  const mxArray *c19_b_y = NULL;
  real_T c19_hoistedGlobal;
  real_T c19_b_u;
  const mxArray *c19_c_y = NULL;
  int32_T c19_i1;
  real_T c19_c_u[7];
  const mxArray *c19_d_y = NULL;
  uint8_T c19_b_hoistedGlobal;
  uint8_T c19_d_u;
  const mxArray *c19_e_y = NULL;
  real_T *c19_i_out;
  real_T (*c19_x_prop)[7];
  real_T (*c19_PT_prop)[36];
  c19_i_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c19_PT_prop = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 2);
  c19_x_prop = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  c19_st = NULL;
  c19_st = NULL;
  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_createcellarray(4), FALSE);
  for (c19_i0 = 0; c19_i0 < 36; c19_i0++) {
    c19_u[c19_i0] = (*c19_PT_prop)[c19_i0];
  }

  c19_b_y = NULL;
  sf_mex_assign(&c19_b_y, sf_mex_create("y", c19_u, 0, 0U, 1U, 0U, 2, 6, 6),
                FALSE);
  sf_mex_setcell(c19_y, 0, c19_b_y);
  c19_hoistedGlobal = *c19_i_out;
  c19_b_u = c19_hoistedGlobal;
  c19_c_y = NULL;
  sf_mex_assign(&c19_c_y, sf_mex_create("y", &c19_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c19_y, 1, c19_c_y);
  for (c19_i1 = 0; c19_i1 < 7; c19_i1++) {
    c19_c_u[c19_i1] = (*c19_x_prop)[c19_i1];
  }

  c19_d_y = NULL;
  sf_mex_assign(&c19_d_y, sf_mex_create("y", c19_c_u, 0, 0U, 1U, 0U, 1, 7),
                FALSE);
  sf_mex_setcell(c19_y, 2, c19_d_y);
  c19_b_hoistedGlobal =
    chartInstance->c19_is_active_c19_Tetraedro_model_sem_sim_com_FK_heur;
  c19_d_u = c19_b_hoistedGlobal;
  c19_e_y = NULL;
  sf_mex_assign(&c19_e_y, sf_mex_create("y", &c19_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c19_y, 3, c19_e_y);
  sf_mex_assign(&c19_st, c19_y, FALSE);
  return c19_st;
}

static void set_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_st)
{
  const mxArray *c19_u;
  real_T c19_dv0[36];
  int32_T c19_i2;
  real_T c19_dv1[7];
  int32_T c19_i3;
  real_T *c19_i_out;
  real_T (*c19_PT_prop)[36];
  real_T (*c19_x_prop)[7];
  c19_i_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c19_PT_prop = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 2);
  c19_x_prop = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c19_doneDoubleBufferReInit = TRUE;
  c19_u = sf_mex_dup(c19_st);
  c19_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c19_u, 0)),
    "PT_prop", c19_dv0);
  for (c19_i2 = 0; c19_i2 < 36; c19_i2++) {
    (*c19_PT_prop)[c19_i2] = c19_dv0[c19_i2];
  }

  *c19_i_out = c19_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c19_u, 1)), "i_out");
  c19_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c19_u, 2)),
    "x_prop", c19_dv1);
  for (c19_i3 = 0; c19_i3 < 7; c19_i3++) {
    (*c19_x_prop)[c19_i3] = c19_dv1[c19_i3];
  }

  chartInstance->c19_is_active_c19_Tetraedro_model_sem_sim_com_FK_heur =
    c19_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c19_u, 3)),
    "is_active_c19_Tetraedro_model_sem_sim_com_FK_heur");
  sf_mex_destroy(&c19_u);
  c19_update_debugger_state_c19_Tetraedro_model_sem_sim_com_FK_heu(chartInstance);
  sf_mex_destroy(&c19_st);
}

static void finalize_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void sf_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  int32_T c19_i4;
  int32_T c19_i5;
  int32_T c19_i6;
  int32_T c19_i7;
  int32_T c19_i8;
  int32_T c19_i9;
  real_T *c19_Dt;
  real_T *c19_i_in;
  real_T *c19_i_out;
  real_T (*c19_PT_prop)[36];
  real_T (*c19_Q)[36];
  real_T (*c19_x_est)[7];
  real_T (*c19_PT_est)[36];
  real_T (*c19_x_prop)[7];
  real_T (*c19_w_gyro)[3];
  c19_i_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c19_i_in = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c19_PT_prop = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 2);
  c19_Q = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 4);
  c19_x_est = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 3);
  c19_PT_est = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 2);
  c19_Dt = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c19_x_prop = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  c19_w_gyro = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 14U, chartInstance->c19_sfEvent);
  for (c19_i4 = 0; c19_i4 < 3; c19_i4++) {
    _SFD_DATA_RANGE_CHECK((*c19_w_gyro)[c19_i4], 0U);
  }

  for (c19_i5 = 0; c19_i5 < 7; c19_i5++) {
    _SFD_DATA_RANGE_CHECK((*c19_x_prop)[c19_i5], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c19_Dt, 2U);
  for (c19_i6 = 0; c19_i6 < 36; c19_i6++) {
    _SFD_DATA_RANGE_CHECK((*c19_PT_est)[c19_i6], 3U);
  }

  for (c19_i7 = 0; c19_i7 < 7; c19_i7++) {
    _SFD_DATA_RANGE_CHECK((*c19_x_est)[c19_i7], 4U);
  }

  for (c19_i8 = 0; c19_i8 < 36; c19_i8++) {
    _SFD_DATA_RANGE_CHECK((*c19_Q)[c19_i8], 5U);
  }

  for (c19_i9 = 0; c19_i9 < 36; c19_i9++) {
    _SFD_DATA_RANGE_CHECK((*c19_PT_prop)[c19_i9], 6U);
  }

  _SFD_DATA_RANGE_CHECK(*c19_i_in, 7U);
  _SFD_DATA_RANGE_CHECK(*c19_i_out, 8U);
  chartInstance->c19_sfEvent = CALL_EVENT;
  c19_chartstep_c19_Tetraedro_model_sem_sim_com_FK_heur(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY
    (_Tetraedro_model_sem_sim_com_FK_heurMachineNumber_,
     chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c19_chartstep_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  real_T c19_hoistedGlobal;
  real_T c19_b_hoistedGlobal;
  int32_T c19_i10;
  real_T c19_w_gyro[3];
  real_T c19_Dt;
  int32_T c19_i11;
  real_T c19_PT_est[36];
  int32_T c19_i12;
  real_T c19_x_est[7];
  int32_T c19_i13;
  real_T c19_Q[36];
  real_T c19_i_in;
  uint32_T c19_debug_family_var_map[28];
  real_T c19_q_est[4];
  real_T c19_b_est[3];
  real_T c19_Th[3];
  real_T c19_Omega4[16];
  real_T c19_M[16];
  real_T c19_q_prop[4];
  real_T c19_b_prop[3];
  real_T c19_GT[36];
  real_T c19_QT[36];
  real_T c19_Omega3_prop[9];
  real_T c19_A_prop[9];
  real_T c19_Omega3_est[9];
  real_T c19_A_est[9];
  real_T c19_L[9];
  real_T c19_KK[9];
  real_T c19_PhiT[36];
  real_T c19_SiG[36];
  real_T c19_nargin = 6.0;
  real_T c19_nargout = 3.0;
  real_T c19_x_prop[7];
  real_T c19_PT_prop[36];
  real_T c19_i_out;
  int32_T c19_i14;
  int32_T c19_i15;
  int32_T c19_i16;
  real_T c19_a[3];
  real_T c19_b;
  int32_T c19_i17;
  int32_T c19_i18;
  real_T c19_b_Th[3];
  real_T c19_A;
  real_T c19_x;
  real_T c19_b_x;
  real_T c19_y;
  real_T c19_c_x;
  real_T c19_d_x;
  real_T c19_b_b;
  int32_T c19_i19;
  static real_T c19_b_a[16] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c19_b_y[16];
  int32_T c19_i20;
  real_T c19_c_Th[3];
  real_T c19_b_A;
  real_T c19_e_x;
  real_T c19_f_x;
  real_T c19_c_y;
  real_T c19_g_x;
  real_T c19_h_x;
  int32_T c19_i21;
  real_T c19_c_a[16];
  real_T c19_c_b;
  int32_T c19_i22;
  int32_T c19_i23;
  real_T c19_d_Th[3];
  real_T c19_B;
  real_T c19_d_y;
  real_T c19_e_y;
  int32_T c19_i24;
  int32_T c19_i25;
  int32_T c19_i26;
  int32_T c19_i27;
  real_T c19_d_b[4];
  int32_T c19_i28;
  int32_T c19_i29;
  int32_T c19_i30;
  real_T c19_C[4];
  int32_T c19_i31;
  int32_T c19_i32;
  int32_T c19_i33;
  int32_T c19_i34;
  int32_T c19_i35;
  int32_T c19_i36;
  int32_T c19_i37;
  int32_T c19_i38;
  int32_T c19_i39;
  int32_T c19_i40;
  static real_T c19_d_a[36] = { -0.5, -0.0, -0.0, 0.0, 0.0, 0.0, -0.0, -0.5,
    -0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c19_i41;
  real_T c19_e_b[36];
  int32_T c19_i42;
  int32_T c19_i43;
  int32_T c19_i44;
  real_T c19_f_y[36];
  int32_T c19_i45;
  int32_T c19_i46;
  int32_T c19_i47;
  int32_T c19_i48;
  int32_T c19_i49;
  real_T c19_b_C[36];
  int32_T c19_i50;
  int32_T c19_i51;
  int32_T c19_i52;
  int32_T c19_i53;
  int32_T c19_i54;
  int32_T c19_i55;
  int32_T c19_i56;
  int32_T c19_i57;
  int32_T c19_i58;
  real_T c19_b_q_prop[3];
  real_T c19_e_a;
  int32_T c19_i59;
  static real_T c19_f_b[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c19_g_y[9];
  int32_T c19_i60;
  int32_T c19_i61;
  int32_T c19_i62;
  real_T c19_g_b[3];
  int32_T c19_i63;
  int32_T c19_i64;
  int32_T c19_i65;
  real_T c19_h_y[9];
  real_T c19_h_b;
  real_T c19_i_y;
  real_T c19_f_a;
  int32_T c19_i66;
  real_T c19_i_b[9];
  int32_T c19_i67;
  int32_T c19_i68;
  int32_T c19_i69;
  real_T c19_b_q_est[3];
  real_T c19_g_a;
  int32_T c19_i70;
  int32_T c19_i71;
  int32_T c19_i72;
  int32_T c19_i73;
  int32_T c19_i74;
  int32_T c19_i75;
  int32_T c19_i76;
  real_T c19_j_b;
  real_T c19_j_y;
  real_T c19_h_a;
  int32_T c19_i77;
  int32_T c19_i78;
  int32_T c19_i79;
  int32_T c19_i80;
  int32_T c19_i81;
  int32_T c19_i82;
  int32_T c19_i83;
  int32_T c19_i84;
  int32_T c19_i85;
  int32_T c19_i86;
  int32_T c19_i87;
  int32_T c19_i88;
  int32_T c19_i89;
  int32_T c19_i90;
  int32_T c19_i91;
  int32_T c19_i92;
  int32_T c19_i93;
  int32_T c19_i94;
  int32_T c19_i95;
  int32_T c19_i96;
  int32_T c19_i97;
  real_T c19_k_b;
  int32_T c19_i98;
  int32_T c19_i99;
  int32_T c19_i100;
  int32_T c19_i101;
  int32_T c19_i102;
  int32_T c19_i103;
  int32_T c19_i104;
  int32_T c19_i105;
  int32_T c19_i106;
  int32_T c19_i107;
  int32_T c19_i108;
  int32_T c19_i109;
  int32_T c19_i110;
  int32_T c19_i111;
  int32_T c19_i112;
  int32_T c19_i113;
  int32_T c19_i114;
  int32_T c19_i115;
  int32_T c19_i116;
  int32_T c19_i117;
  int32_T c19_i118;
  int32_T c19_i119;
  int32_T c19_i120;
  int32_T c19_i121;
  int32_T c19_i122;
  int32_T c19_i123;
  int32_T c19_i124;
  int32_T c19_i125;
  int32_T c19_i126;
  int32_T c19_i127;
  int32_T c19_i128;
  int32_T c19_i129;
  int32_T c19_i130;
  int32_T c19_i131;
  real_T c19_l_b;
  int32_T c19_i132;
  int32_T c19_i133;
  int32_T c19_i134;
  int32_T c19_i135;
  int32_T c19_i136;
  int32_T c19_i137;
  int32_T c19_i138;
  int32_T c19_i139;
  int32_T c19_i140;
  int32_T c19_i141;
  int32_T c19_i142;
  int32_T c19_i143;
  int32_T c19_i144;
  int32_T c19_i145;
  int32_T c19_i146;
  int32_T c19_i147;
  int32_T c19_i148;
  int32_T c19_i149;
  int32_T c19_i150;
  int32_T c19_i151;
  int32_T c19_i152;
  real_T *c19_b_Dt;
  real_T *c19_b_i_in;
  real_T *c19_b_i_out;
  real_T (*c19_b_x_prop)[7];
  real_T (*c19_b_PT_prop)[36];
  real_T (*c19_b_Q)[36];
  real_T (*c19_b_x_est)[7];
  real_T (*c19_b_PT_est)[36];
  real_T (*c19_b_w_gyro)[3];
  c19_b_i_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c19_b_i_in = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c19_b_PT_prop = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 2);
  c19_b_Q = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 4);
  c19_b_x_est = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 3);
  c19_b_PT_est = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 2);
  c19_b_Dt = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c19_b_x_prop = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  c19_b_w_gyro = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 14U, chartInstance->c19_sfEvent);
  c19_hoistedGlobal = *c19_b_Dt;
  c19_b_hoistedGlobal = *c19_b_i_in;
  for (c19_i10 = 0; c19_i10 < 3; c19_i10++) {
    c19_w_gyro[c19_i10] = (*c19_b_w_gyro)[c19_i10];
  }

  c19_Dt = c19_hoistedGlobal;
  for (c19_i11 = 0; c19_i11 < 36; c19_i11++) {
    c19_PT_est[c19_i11] = (*c19_b_PT_est)[c19_i11];
  }

  for (c19_i12 = 0; c19_i12 < 7; c19_i12++) {
    c19_x_est[c19_i12] = (*c19_b_x_est)[c19_i12];
  }

  for (c19_i13 = 0; c19_i13 < 36; c19_i13++) {
    c19_Q[c19_i13] = (*c19_b_Q)[c19_i13];
  }

  c19_i_in = c19_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 28U, 28U, c19_debug_family_names,
    c19_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_q_est, 0U, c19_f_sf_marshallOut,
    c19_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_b_est, 1U, c19_d_sf_marshallOut,
    c19_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_Th, 2U, c19_d_sf_marshallOut,
    c19_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_Omega4, 3U, c19_g_sf_marshallOut,
    c19_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_M, 4U, c19_g_sf_marshallOut,
    c19_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_q_prop, 5U, c19_f_sf_marshallOut,
    c19_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_b_prop, 6U, c19_d_sf_marshallOut,
    c19_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c19_GT, 7U, c19_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_QT, 8U, c19_b_sf_marshallOut,
    c19_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_Omega3_prop, 9U, c19_e_sf_marshallOut,
    c19_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_A_prop, 10U, c19_e_sf_marshallOut,
    c19_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_Omega3_est, 11U, c19_e_sf_marshallOut,
    c19_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_A_est, 12U, c19_e_sf_marshallOut,
    c19_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_L, 13U, c19_e_sf_marshallOut,
    c19_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_KK, 14U, c19_e_sf_marshallOut,
    c19_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_PhiT, 15U, c19_b_sf_marshallOut,
    c19_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_SiG, 16U, c19_b_sf_marshallOut,
    c19_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_nargin, 17U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_nargout, 18U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c19_w_gyro, 19U, c19_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_Dt, 20U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c19_PT_est, 21U, c19_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c19_x_est, 22U, c19_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c19_Q, 23U, c19_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_i_in, 24U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_x_prop, 25U, c19_c_sf_marshallOut,
    c19_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c19_PT_prop, 26U, c19_b_sf_marshallOut,
    c19_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_i_out, 27U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 4);
  c19_i_out = c19_i_in + 1.0;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 11);
  for (c19_i14 = 0; c19_i14 < 4; c19_i14++) {
    c19_q_est[c19_i14] = c19_x_est[c19_i14];
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 12);
  for (c19_i15 = 0; c19_i15 < 3; c19_i15++) {
    c19_b_est[c19_i15] = c19_x_est[c19_i15 + 4];
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 16);
  for (c19_i16 = 0; c19_i16 < 3; c19_i16++) {
    c19_a[c19_i16] = c19_w_gyro[c19_i16];
  }

  c19_b = c19_Dt;
  for (c19_i17 = 0; c19_i17 < 3; c19_i17++) {
    c19_Th[c19_i17] = c19_a[c19_i17] * c19_b;
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 18);
  c19_Omega4[0] = 0.0;
  c19_Omega4[4] = c19_Th[2];
  c19_Omega4[8] = -c19_Th[1];
  c19_Omega4[12] = c19_Th[0];
  c19_Omega4[1] = -c19_Th[2];
  c19_Omega4[5] = 0.0;
  c19_Omega4[9] = c19_Th[0];
  c19_Omega4[13] = c19_Th[1];
  c19_Omega4[2] = c19_Th[1];
  c19_Omega4[6] = -c19_Th[0];
  c19_Omega4[10] = 0.0;
  c19_Omega4[14] = c19_Th[2];
  c19_Omega4[3] = -c19_Th[0];
  c19_Omega4[7] = -c19_Th[1];
  c19_Omega4[11] = -c19_Th[2];
  c19_Omega4[15] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 23);
  for (c19_i18 = 0; c19_i18 < 3; c19_i18++) {
    c19_b_Th[c19_i18] = c19_Th[c19_i18];
  }

  c19_A = c19_norm(chartInstance, c19_b_Th);
  c19_x = c19_A;
  c19_b_x = c19_x;
  c19_y = c19_b_x / 2.0;
  c19_c_x = c19_y;
  c19_d_x = c19_c_x;
  c19_d_x = muDoubleScalarCos(c19_d_x);
  c19_b_b = c19_d_x;
  for (c19_i19 = 0; c19_i19 < 16; c19_i19++) {
    c19_b_y[c19_i19] = c19_b_a[c19_i19] * c19_b_b;
  }

  for (c19_i20 = 0; c19_i20 < 3; c19_i20++) {
    c19_c_Th[c19_i20] = c19_Th[c19_i20];
  }

  c19_b_A = c19_norm(chartInstance, c19_c_Th);
  c19_e_x = c19_b_A;
  c19_f_x = c19_e_x;
  c19_c_y = c19_f_x / 2.0;
  c19_g_x = c19_c_y;
  c19_h_x = c19_g_x;
  c19_h_x = muDoubleScalarSin(c19_h_x);
  for (c19_i21 = 0; c19_i21 < 16; c19_i21++) {
    c19_c_a[c19_i21] = c19_Omega4[c19_i21];
  }

  c19_c_b = c19_h_x;
  for (c19_i22 = 0; c19_i22 < 16; c19_i22++) {
    c19_c_a[c19_i22] *= c19_c_b;
  }

  for (c19_i23 = 0; c19_i23 < 3; c19_i23++) {
    c19_d_Th[c19_i23] = c19_Th[c19_i23];
  }

  c19_B = c19_norm(chartInstance, c19_d_Th);
  c19_d_y = c19_B;
  c19_e_y = c19_d_y;
  for (c19_i24 = 0; c19_i24 < 16; c19_i24++) {
    c19_c_a[c19_i24] /= c19_e_y;
  }

  for (c19_i25 = 0; c19_i25 < 16; c19_i25++) {
    c19_M[c19_i25] = c19_b_y[c19_i25] + c19_c_a[c19_i25];
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 24);
  for (c19_i26 = 0; c19_i26 < 16; c19_i26++) {
    c19_c_a[c19_i26] = c19_M[c19_i26];
  }

  for (c19_i27 = 0; c19_i27 < 4; c19_i27++) {
    c19_d_b[c19_i27] = c19_q_est[c19_i27];
  }

  c19_b_eml_scalar_eg(chartInstance);
  c19_b_eml_scalar_eg(chartInstance);
  for (c19_i28 = 0; c19_i28 < 4; c19_i28++) {
    c19_q_prop[c19_i28] = 0.0;
  }

  for (c19_i29 = 0; c19_i29 < 4; c19_i29++) {
    c19_q_prop[c19_i29] = 0.0;
  }

  for (c19_i30 = 0; c19_i30 < 4; c19_i30++) {
    c19_C[c19_i30] = c19_q_prop[c19_i30];
  }

  for (c19_i31 = 0; c19_i31 < 4; c19_i31++) {
    c19_q_prop[c19_i31] = c19_C[c19_i31];
  }

  for (c19_i32 = 0; c19_i32 < 4; c19_i32++) {
    c19_C[c19_i32] = c19_q_prop[c19_i32];
  }

  for (c19_i33 = 0; c19_i33 < 4; c19_i33++) {
    c19_q_prop[c19_i33] = c19_C[c19_i33];
  }

  for (c19_i34 = 0; c19_i34 < 4; c19_i34++) {
    c19_q_prop[c19_i34] = 0.0;
    c19_i35 = 0;
    for (c19_i36 = 0; c19_i36 < 4; c19_i36++) {
      c19_q_prop[c19_i34] += c19_c_a[c19_i35 + c19_i34] * c19_d_b[c19_i36];
      c19_i35 += 4;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 26);
  for (c19_i37 = 0; c19_i37 < 3; c19_i37++) {
    c19_b_prop[c19_i37] = c19_b_est[c19_i37];
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 28);
  for (c19_i38 = 0; c19_i38 < 4; c19_i38++) {
    c19_x_prop[c19_i38] = c19_q_prop[c19_i38];
  }

  for (c19_i39 = 0; c19_i39 < 3; c19_i39++) {
    c19_x_prop[c19_i39 + 4] = c19_b_prop[c19_i39];
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 31);
  for (c19_i40 = 0; c19_i40 < 36; c19_i40++) {
    c19_GT[c19_i40] = c19_d_a[c19_i40];
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 32);
  for (c19_i41 = 0; c19_i41 < 36; c19_i41++) {
    c19_e_b[c19_i41] = c19_Q[c19_i41];
  }

  c19_c_eml_scalar_eg(chartInstance);
  c19_c_eml_scalar_eg(chartInstance);
  for (c19_i42 = 0; c19_i42 < 6; c19_i42++) {
    c19_i43 = 0;
    for (c19_i44 = 0; c19_i44 < 6; c19_i44++) {
      c19_f_y[c19_i43 + c19_i42] = 0.0;
      c19_i45 = 0;
      for (c19_i46 = 0; c19_i46 < 6; c19_i46++) {
        c19_f_y[c19_i43 + c19_i42] += c19_d_a[c19_i45 + c19_i42] *
          c19_e_b[c19_i46 + c19_i43];
        c19_i45 += 6;
      }

      c19_i43 += 6;
    }
  }

  c19_c_eml_scalar_eg(chartInstance);
  c19_c_eml_scalar_eg(chartInstance);
  for (c19_i47 = 0; c19_i47 < 36; c19_i47++) {
    c19_QT[c19_i47] = 0.0;
  }

  for (c19_i48 = 0; c19_i48 < 36; c19_i48++) {
    c19_QT[c19_i48] = 0.0;
  }

  for (c19_i49 = 0; c19_i49 < 36; c19_i49++) {
    c19_b_C[c19_i49] = c19_QT[c19_i49];
  }

  for (c19_i50 = 0; c19_i50 < 36; c19_i50++) {
    c19_QT[c19_i50] = c19_b_C[c19_i50];
  }

  for (c19_i51 = 0; c19_i51 < 36; c19_i51++) {
    c19_b_C[c19_i51] = c19_QT[c19_i51];
  }

  for (c19_i52 = 0; c19_i52 < 36; c19_i52++) {
    c19_QT[c19_i52] = c19_b_C[c19_i52];
  }

  for (c19_i53 = 0; c19_i53 < 6; c19_i53++) {
    c19_i54 = 0;
    for (c19_i55 = 0; c19_i55 < 6; c19_i55++) {
      c19_QT[c19_i54 + c19_i53] = 0.0;
      c19_i56 = 0;
      for (c19_i57 = 0; c19_i57 < 6; c19_i57++) {
        c19_QT[c19_i54 + c19_i53] += c19_f_y[c19_i56 + c19_i53] *
          c19_d_a[c19_i57 + c19_i54];
        c19_i56 += 6;
      }

      c19_i54 += 6;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 36);
  c19_Omega3_prop[0] = 0.0;
  c19_Omega3_prop[3] = c19_q_prop[2];
  c19_Omega3_prop[6] = -c19_q_prop[1];
  c19_Omega3_prop[1] = -c19_q_prop[2];
  c19_Omega3_prop[4] = 0.0;
  c19_Omega3_prop[7] = c19_q_prop[0];
  c19_Omega3_prop[2] = c19_q_prop[1];
  c19_Omega3_prop[5] = -c19_q_prop[0];
  c19_Omega3_prop[8] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 40);
  for (c19_i58 = 0; c19_i58 < 3; c19_i58++) {
    c19_b_q_prop[c19_i58] = c19_q_prop[c19_i58];
  }

  c19_e_a = c19_mpower(chartInstance, c19_q_prop[3]) - c19_mpower(chartInstance,
    c19_norm(chartInstance, c19_b_q_prop));
  for (c19_i59 = 0; c19_i59 < 9; c19_i59++) {
    c19_g_y[c19_i59] = c19_e_a * c19_f_b[c19_i59];
  }

  for (c19_i60 = 0; c19_i60 < 3; c19_i60++) {
    c19_a[c19_i60] = c19_q_prop[c19_i60];
  }

  for (c19_i61 = 0; c19_i61 < 3; c19_i61++) {
    c19_a[c19_i61] *= 2.0;
  }

  for (c19_i62 = 0; c19_i62 < 3; c19_i62++) {
    c19_g_b[c19_i62] = c19_q_prop[c19_i62];
  }

  for (c19_i63 = 0; c19_i63 < 3; c19_i63++) {
    c19_i64 = 0;
    for (c19_i65 = 0; c19_i65 < 3; c19_i65++) {
      c19_h_y[c19_i64 + c19_i63] = c19_a[c19_i63] * c19_g_b[c19_i65];
      c19_i64 += 3;
    }
  }

  c19_h_b = c19_q_prop[3];
  c19_i_y = 2.0 * c19_h_b;
  c19_f_a = c19_i_y;
  for (c19_i66 = 0; c19_i66 < 9; c19_i66++) {
    c19_i_b[c19_i66] = c19_Omega3_prop[c19_i66];
  }

  for (c19_i67 = 0; c19_i67 < 9; c19_i67++) {
    c19_i_b[c19_i67] *= c19_f_a;
  }

  for (c19_i68 = 0; c19_i68 < 9; c19_i68++) {
    c19_A_prop[c19_i68] = (c19_g_y[c19_i68] + c19_h_y[c19_i68]) +
      c19_i_b[c19_i68];
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 43);
  c19_Omega3_est[0] = 0.0;
  c19_Omega3_est[3] = c19_q_est[2];
  c19_Omega3_est[6] = -c19_q_est[1];
  c19_Omega3_est[1] = -c19_q_est[2];
  c19_Omega3_est[4] = 0.0;
  c19_Omega3_est[7] = c19_q_est[0];
  c19_Omega3_est[2] = c19_q_est[1];
  c19_Omega3_est[5] = -c19_q_est[0];
  c19_Omega3_est[8] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 47);
  for (c19_i69 = 0; c19_i69 < 3; c19_i69++) {
    c19_b_q_est[c19_i69] = c19_q_est[c19_i69];
  }

  c19_g_a = c19_mpower(chartInstance, c19_q_est[3]) - c19_mpower(chartInstance,
    c19_norm(chartInstance, c19_b_q_est));
  for (c19_i70 = 0; c19_i70 < 9; c19_i70++) {
    c19_g_y[c19_i70] = c19_g_a * c19_f_b[c19_i70];
  }

  for (c19_i71 = 0; c19_i71 < 3; c19_i71++) {
    c19_a[c19_i71] = c19_q_est[c19_i71];
  }

  for (c19_i72 = 0; c19_i72 < 3; c19_i72++) {
    c19_a[c19_i72] *= 2.0;
  }

  for (c19_i73 = 0; c19_i73 < 3; c19_i73++) {
    c19_g_b[c19_i73] = c19_q_est[c19_i73];
  }

  for (c19_i74 = 0; c19_i74 < 3; c19_i74++) {
    c19_i75 = 0;
    for (c19_i76 = 0; c19_i76 < 3; c19_i76++) {
      c19_h_y[c19_i75 + c19_i74] = c19_a[c19_i74] * c19_g_b[c19_i76];
      c19_i75 += 3;
    }
  }

  c19_j_b = c19_q_est[3];
  c19_j_y = 2.0 * c19_j_b;
  c19_h_a = c19_j_y;
  for (c19_i77 = 0; c19_i77 < 9; c19_i77++) {
    c19_i_b[c19_i77] = c19_Omega3_est[c19_i77];
  }

  for (c19_i78 = 0; c19_i78 < 9; c19_i78++) {
    c19_i_b[c19_i78] *= c19_h_a;
  }

  for (c19_i79 = 0; c19_i79 < 9; c19_i79++) {
    c19_A_est[c19_i79] = (c19_g_y[c19_i79] + c19_h_y[c19_i79]) + c19_i_b[c19_i79];
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 51);
  for (c19_i80 = 0; c19_i80 < 9; c19_i80++) {
    c19_g_y[c19_i80] = c19_A_prop[c19_i80];
  }

  c19_i81 = 0;
  for (c19_i82 = 0; c19_i82 < 3; c19_i82++) {
    c19_i83 = 0;
    for (c19_i84 = 0; c19_i84 < 3; c19_i84++) {
      c19_i_b[c19_i84 + c19_i81] = c19_A_est[c19_i83 + c19_i82];
      c19_i83 += 3;
    }

    c19_i81 += 3;
  }

  c19_d_eml_scalar_eg(chartInstance);
  c19_d_eml_scalar_eg(chartInstance);
  for (c19_i85 = 0; c19_i85 < 9; c19_i85++) {
    c19_L[c19_i85] = 0.0;
  }

  for (c19_i86 = 0; c19_i86 < 9; c19_i86++) {
    c19_L[c19_i86] = 0.0;
  }

  for (c19_i87 = 0; c19_i87 < 9; c19_i87++) {
    c19_h_y[c19_i87] = c19_L[c19_i87];
  }

  for (c19_i88 = 0; c19_i88 < 9; c19_i88++) {
    c19_L[c19_i88] = c19_h_y[c19_i88];
  }

  for (c19_i89 = 0; c19_i89 < 9; c19_i89++) {
    c19_h_y[c19_i89] = c19_L[c19_i89];
  }

  for (c19_i90 = 0; c19_i90 < 9; c19_i90++) {
    c19_L[c19_i90] = c19_h_y[c19_i90];
  }

  for (c19_i91 = 0; c19_i91 < 3; c19_i91++) {
    c19_i92 = 0;
    for (c19_i93 = 0; c19_i93 < 3; c19_i93++) {
      c19_L[c19_i92 + c19_i91] = 0.0;
      c19_i94 = 0;
      for (c19_i95 = 0; c19_i95 < 3; c19_i95++) {
        c19_L[c19_i92 + c19_i91] += c19_g_y[c19_i94 + c19_i91] * c19_i_b[c19_i95
          + c19_i92];
        c19_i94 += 3;
      }

      c19_i92 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 52);
  c19_eye(chartInstance, c19_i_b);
  for (c19_i96 = 0; c19_i96 < 9; c19_i96++) {
    c19_i_b[c19_i96] += c19_L[c19_i96];
  }

  for (c19_i97 = 0; c19_i97 < 9; c19_i97++) {
    c19_i_b[c19_i97] *= -0.5;
  }

  c19_k_b = c19_Dt;
  for (c19_i98 = 0; c19_i98 < 9; c19_i98++) {
    c19_i_b[c19_i98] *= c19_k_b;
  }

  for (c19_i99 = 0; c19_i99 < 9; c19_i99++) {
    c19_KK[c19_i99] = c19_i_b[c19_i99] / 2.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 53);
  c19_eye(chartInstance, c19_g_y);
  c19_i100 = 0;
  c19_i101 = 0;
  for (c19_i102 = 0; c19_i102 < 3; c19_i102++) {
    for (c19_i103 = 0; c19_i103 < 3; c19_i103++) {
      c19_PhiT[c19_i103 + c19_i100] = c19_L[c19_i103 + c19_i101];
    }

    c19_i100 += 6;
    c19_i101 += 3;
  }

  c19_i104 = 0;
  c19_i105 = 0;
  for (c19_i106 = 0; c19_i106 < 3; c19_i106++) {
    for (c19_i107 = 0; c19_i107 < 3; c19_i107++) {
      c19_PhiT[(c19_i107 + c19_i104) + 18] = c19_KK[c19_i107 + c19_i105];
    }

    c19_i104 += 6;
    c19_i105 += 3;
  }

  c19_i108 = 0;
  for (c19_i109 = 0; c19_i109 < 3; c19_i109++) {
    for (c19_i110 = 0; c19_i110 < 3; c19_i110++) {
      c19_PhiT[(c19_i110 + c19_i108) + 3] = 0.0;
    }

    c19_i108 += 6;
  }

  c19_i111 = 0;
  c19_i112 = 0;
  for (c19_i113 = 0; c19_i113 < 3; c19_i113++) {
    for (c19_i114 = 0; c19_i114 < 3; c19_i114++) {
      c19_PhiT[(c19_i114 + c19_i111) + 21] = c19_g_y[c19_i114 + c19_i112];
    }

    c19_i111 += 6;
    c19_i112 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 54);
  for (c19_i115 = 0; c19_i115 < 36; c19_i115++) {
    c19_b_C[c19_i115] = c19_PhiT[c19_i115];
  }

  for (c19_i116 = 0; c19_i116 < 36; c19_i116++) {
    c19_e_b[c19_i116] = c19_QT[c19_i116];
  }

  c19_c_eml_scalar_eg(chartInstance);
  c19_c_eml_scalar_eg(chartInstance);
  for (c19_i117 = 0; c19_i117 < 6; c19_i117++) {
    c19_i118 = 0;
    for (c19_i119 = 0; c19_i119 < 6; c19_i119++) {
      c19_f_y[c19_i118 + c19_i117] = 0.0;
      c19_i120 = 0;
      for (c19_i121 = 0; c19_i121 < 6; c19_i121++) {
        c19_f_y[c19_i118 + c19_i117] += c19_b_C[c19_i120 + c19_i117] *
          c19_e_b[c19_i121 + c19_i118];
        c19_i120 += 6;
      }

      c19_i118 += 6;
    }
  }

  c19_i122 = 0;
  for (c19_i123 = 0; c19_i123 < 6; c19_i123++) {
    c19_i124 = 0;
    for (c19_i125 = 0; c19_i125 < 6; c19_i125++) {
      c19_e_b[c19_i125 + c19_i122] = c19_PhiT[c19_i124 + c19_i123];
      c19_i124 += 6;
    }

    c19_i122 += 6;
  }

  c19_c_eml_scalar_eg(chartInstance);
  c19_c_eml_scalar_eg(chartInstance);
  for (c19_i126 = 0; c19_i126 < 6; c19_i126++) {
    c19_i127 = 0;
    for (c19_i128 = 0; c19_i128 < 6; c19_i128++) {
      c19_b_C[c19_i127 + c19_i126] = 0.0;
      c19_i129 = 0;
      for (c19_i130 = 0; c19_i130 < 6; c19_i130++) {
        c19_b_C[c19_i127 + c19_i126] += c19_f_y[c19_i129 + c19_i126] *
          c19_e_b[c19_i130 + c19_i127];
        c19_i129 += 6;
      }

      c19_i127 += 6;
    }
  }

  for (c19_i131 = 0; c19_i131 < 36; c19_i131++) {
    c19_b_C[c19_i131] += c19_QT[c19_i131];
  }

  c19_l_b = c19_Dt;
  for (c19_i132 = 0; c19_i132 < 36; c19_i132++) {
    c19_b_C[c19_i132] *= c19_l_b;
  }

  for (c19_i133 = 0; c19_i133 < 36; c19_i133++) {
    c19_SiG[c19_i133] = c19_b_C[c19_i133] / 2.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 55);
  for (c19_i134 = 0; c19_i134 < 36; c19_i134++) {
    c19_b_C[c19_i134] = c19_PhiT[c19_i134];
  }

  for (c19_i135 = 0; c19_i135 < 36; c19_i135++) {
    c19_e_b[c19_i135] = c19_PT_est[c19_i135];
  }

  c19_c_eml_scalar_eg(chartInstance);
  c19_c_eml_scalar_eg(chartInstance);
  for (c19_i136 = 0; c19_i136 < 6; c19_i136++) {
    c19_i137 = 0;
    for (c19_i138 = 0; c19_i138 < 6; c19_i138++) {
      c19_f_y[c19_i137 + c19_i136] = 0.0;
      c19_i139 = 0;
      for (c19_i140 = 0; c19_i140 < 6; c19_i140++) {
        c19_f_y[c19_i137 + c19_i136] += c19_b_C[c19_i139 + c19_i136] *
          c19_e_b[c19_i140 + c19_i137];
        c19_i139 += 6;
      }

      c19_i137 += 6;
    }
  }

  c19_i141 = 0;
  for (c19_i142 = 0; c19_i142 < 6; c19_i142++) {
    c19_i143 = 0;
    for (c19_i144 = 0; c19_i144 < 6; c19_i144++) {
      c19_e_b[c19_i144 + c19_i141] = c19_PhiT[c19_i143 + c19_i142];
      c19_i143 += 6;
    }

    c19_i141 += 6;
  }

  c19_c_eml_scalar_eg(chartInstance);
  c19_c_eml_scalar_eg(chartInstance);
  for (c19_i145 = 0; c19_i145 < 6; c19_i145++) {
    c19_i146 = 0;
    for (c19_i147 = 0; c19_i147 < 6; c19_i147++) {
      c19_b_C[c19_i146 + c19_i145] = 0.0;
      c19_i148 = 0;
      for (c19_i149 = 0; c19_i149 < 6; c19_i149++) {
        c19_b_C[c19_i146 + c19_i145] += c19_f_y[c19_i148 + c19_i145] *
          c19_e_b[c19_i149 + c19_i146];
        c19_i148 += 6;
      }

      c19_i146 += 6;
    }
  }

  for (c19_i150 = 0; c19_i150 < 36; c19_i150++) {
    c19_PT_prop[c19_i150] = c19_b_C[c19_i150] + c19_SiG[c19_i150];
  }

  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, -55);
  _SFD_SYMBOL_SCOPE_POP();
  for (c19_i151 = 0; c19_i151 < 7; c19_i151++) {
    (*c19_b_x_prop)[c19_i151] = c19_x_prop[c19_i151];
  }

  for (c19_i152 = 0; c19_i152 < 36; c19_i152++) {
    (*c19_b_PT_prop)[c19_i152] = c19_PT_prop[c19_i152];
  }

  *c19_b_i_out = c19_i_out;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c19_sfEvent);
}

static void initSimStructsc19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void registerMessagesc19_Tetraedro_model_sem_sim_com_FK_heur
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c19_machineNumber, uint32_T
  c19_chartNumber)
{
}

static const mxArray *c19_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData)
{
  const mxArray *c19_mxArrayOutData = NULL;
  real_T c19_u;
  const mxArray *c19_y = NULL;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_mxArrayOutData = NULL;
  c19_u = *(real_T *)c19_inData;
  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", &c19_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c19_mxArrayOutData, c19_y, FALSE);
  return c19_mxArrayOutData;
}

static real_T c19_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_i_out, const char_T *c19_identifier)
{
  real_T c19_y;
  emlrtMsgIdentifier c19_thisId;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_y = c19_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_i_out),
    &c19_thisId);
  sf_mex_destroy(&c19_i_out);
  return c19_y;
}

static real_T c19_b_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId)
{
  real_T c19_y;
  real_T c19_d0;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), &c19_d0, 1, 0, 0U, 0, 0U, 0);
  c19_y = c19_d0;
  sf_mex_destroy(&c19_u);
  return c19_y;
}

static void c19_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData)
{
  const mxArray *c19_i_out;
  const char_T *c19_identifier;
  emlrtMsgIdentifier c19_thisId;
  real_T c19_y;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_i_out = sf_mex_dup(c19_mxArrayInData);
  c19_identifier = c19_varName;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_y = c19_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_i_out),
    &c19_thisId);
  sf_mex_destroy(&c19_i_out);
  *(real_T *)c19_outData = c19_y;
  sf_mex_destroy(&c19_mxArrayInData);
}

static const mxArray *c19_b_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData)
{
  const mxArray *c19_mxArrayOutData = NULL;
  int32_T c19_i153;
  int32_T c19_i154;
  int32_T c19_i155;
  real_T c19_b_inData[36];
  int32_T c19_i156;
  int32_T c19_i157;
  int32_T c19_i158;
  real_T c19_u[36];
  const mxArray *c19_y = NULL;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_mxArrayOutData = NULL;
  c19_i153 = 0;
  for (c19_i154 = 0; c19_i154 < 6; c19_i154++) {
    for (c19_i155 = 0; c19_i155 < 6; c19_i155++) {
      c19_b_inData[c19_i155 + c19_i153] = (*(real_T (*)[36])c19_inData)[c19_i155
        + c19_i153];
    }

    c19_i153 += 6;
  }

  c19_i156 = 0;
  for (c19_i157 = 0; c19_i157 < 6; c19_i157++) {
    for (c19_i158 = 0; c19_i158 < 6; c19_i158++) {
      c19_u[c19_i158 + c19_i156] = c19_b_inData[c19_i158 + c19_i156];
    }

    c19_i156 += 6;
  }

  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", c19_u, 0, 0U, 1U, 0U, 2, 6, 6), FALSE);
  sf_mex_assign(&c19_mxArrayOutData, c19_y, FALSE);
  return c19_mxArrayOutData;
}

static void c19_c_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_PT_prop, const char_T *c19_identifier, real_T c19_y[36])
{
  emlrtMsgIdentifier c19_thisId;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_PT_prop), &c19_thisId,
    c19_y);
  sf_mex_destroy(&c19_PT_prop);
}

static void c19_d_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[36])
{
  real_T c19_dv2[36];
  int32_T c19_i159;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), c19_dv2, 1, 0, 0U, 1, 0U, 2, 6,
                6);
  for (c19_i159 = 0; c19_i159 < 36; c19_i159++) {
    c19_y[c19_i159] = c19_dv2[c19_i159];
  }

  sf_mex_destroy(&c19_u);
}

static void c19_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData)
{
  const mxArray *c19_PT_prop;
  const char_T *c19_identifier;
  emlrtMsgIdentifier c19_thisId;
  real_T c19_y[36];
  int32_T c19_i160;
  int32_T c19_i161;
  int32_T c19_i162;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_PT_prop = sf_mex_dup(c19_mxArrayInData);
  c19_identifier = c19_varName;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_PT_prop), &c19_thisId,
    c19_y);
  sf_mex_destroy(&c19_PT_prop);
  c19_i160 = 0;
  for (c19_i161 = 0; c19_i161 < 6; c19_i161++) {
    for (c19_i162 = 0; c19_i162 < 6; c19_i162++) {
      (*(real_T (*)[36])c19_outData)[c19_i162 + c19_i160] = c19_y[c19_i162 +
        c19_i160];
    }

    c19_i160 += 6;
  }

  sf_mex_destroy(&c19_mxArrayInData);
}

static const mxArray *c19_c_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData)
{
  const mxArray *c19_mxArrayOutData = NULL;
  int32_T c19_i163;
  real_T c19_b_inData[7];
  int32_T c19_i164;
  real_T c19_u[7];
  const mxArray *c19_y = NULL;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_mxArrayOutData = NULL;
  for (c19_i163 = 0; c19_i163 < 7; c19_i163++) {
    c19_b_inData[c19_i163] = (*(real_T (*)[7])c19_inData)[c19_i163];
  }

  for (c19_i164 = 0; c19_i164 < 7; c19_i164++) {
    c19_u[c19_i164] = c19_b_inData[c19_i164];
  }

  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", c19_u, 0, 0U, 1U, 0U, 1, 7), FALSE);
  sf_mex_assign(&c19_mxArrayOutData, c19_y, FALSE);
  return c19_mxArrayOutData;
}

static void c19_e_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_x_prop, const char_T *c19_identifier, real_T c19_y[7])
{
  emlrtMsgIdentifier c19_thisId;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_x_prop), &c19_thisId,
    c19_y);
  sf_mex_destroy(&c19_x_prop);
}

static void c19_f_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[7])
{
  real_T c19_dv3[7];
  int32_T c19_i165;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), c19_dv3, 1, 0, 0U, 1, 0U, 1, 7);
  for (c19_i165 = 0; c19_i165 < 7; c19_i165++) {
    c19_y[c19_i165] = c19_dv3[c19_i165];
  }

  sf_mex_destroy(&c19_u);
}

static void c19_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData)
{
  const mxArray *c19_x_prop;
  const char_T *c19_identifier;
  emlrtMsgIdentifier c19_thisId;
  real_T c19_y[7];
  int32_T c19_i166;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_x_prop = sf_mex_dup(c19_mxArrayInData);
  c19_identifier = c19_varName;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_x_prop), &c19_thisId,
    c19_y);
  sf_mex_destroy(&c19_x_prop);
  for (c19_i166 = 0; c19_i166 < 7; c19_i166++) {
    (*(real_T (*)[7])c19_outData)[c19_i166] = c19_y[c19_i166];
  }

  sf_mex_destroy(&c19_mxArrayInData);
}

static const mxArray *c19_d_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData)
{
  const mxArray *c19_mxArrayOutData = NULL;
  int32_T c19_i167;
  real_T c19_b_inData[3];
  int32_T c19_i168;
  real_T c19_u[3];
  const mxArray *c19_y = NULL;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_mxArrayOutData = NULL;
  for (c19_i167 = 0; c19_i167 < 3; c19_i167++) {
    c19_b_inData[c19_i167] = (*(real_T (*)[3])c19_inData)[c19_i167];
  }

  for (c19_i168 = 0; c19_i168 < 3; c19_i168++) {
    c19_u[c19_i168] = c19_b_inData[c19_i168];
  }

  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", c19_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c19_mxArrayOutData, c19_y, FALSE);
  return c19_mxArrayOutData;
}

static const mxArray *c19_e_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData)
{
  const mxArray *c19_mxArrayOutData = NULL;
  int32_T c19_i169;
  int32_T c19_i170;
  int32_T c19_i171;
  real_T c19_b_inData[9];
  int32_T c19_i172;
  int32_T c19_i173;
  int32_T c19_i174;
  real_T c19_u[9];
  const mxArray *c19_y = NULL;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_mxArrayOutData = NULL;
  c19_i169 = 0;
  for (c19_i170 = 0; c19_i170 < 3; c19_i170++) {
    for (c19_i171 = 0; c19_i171 < 3; c19_i171++) {
      c19_b_inData[c19_i171 + c19_i169] = (*(real_T (*)[9])c19_inData)[c19_i171
        + c19_i169];
    }

    c19_i169 += 3;
  }

  c19_i172 = 0;
  for (c19_i173 = 0; c19_i173 < 3; c19_i173++) {
    for (c19_i174 = 0; c19_i174 < 3; c19_i174++) {
      c19_u[c19_i174 + c19_i172] = c19_b_inData[c19_i174 + c19_i172];
    }

    c19_i172 += 3;
  }

  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", c19_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c19_mxArrayOutData, c19_y, FALSE);
  return c19_mxArrayOutData;
}

static void c19_g_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[9])
{
  real_T c19_dv4[9];
  int32_T c19_i175;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), c19_dv4, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c19_i175 = 0; c19_i175 < 9; c19_i175++) {
    c19_y[c19_i175] = c19_dv4[c19_i175];
  }

  sf_mex_destroy(&c19_u);
}

static void c19_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData)
{
  const mxArray *c19_KK;
  const char_T *c19_identifier;
  emlrtMsgIdentifier c19_thisId;
  real_T c19_y[9];
  int32_T c19_i176;
  int32_T c19_i177;
  int32_T c19_i178;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_KK = sf_mex_dup(c19_mxArrayInData);
  c19_identifier = c19_varName;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_KK), &c19_thisId, c19_y);
  sf_mex_destroy(&c19_KK);
  c19_i176 = 0;
  for (c19_i177 = 0; c19_i177 < 3; c19_i177++) {
    for (c19_i178 = 0; c19_i178 < 3; c19_i178++) {
      (*(real_T (*)[9])c19_outData)[c19_i178 + c19_i176] = c19_y[c19_i178 +
        c19_i176];
    }

    c19_i176 += 3;
  }

  sf_mex_destroy(&c19_mxArrayInData);
}

static void c19_h_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[3])
{
  real_T c19_dv5[3];
  int32_T c19_i179;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), c19_dv5, 1, 0, 0U, 1, 0U, 1, 3);
  for (c19_i179 = 0; c19_i179 < 3; c19_i179++) {
    c19_y[c19_i179] = c19_dv5[c19_i179];
  }

  sf_mex_destroy(&c19_u);
}

static void c19_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData)
{
  const mxArray *c19_b_prop;
  const char_T *c19_identifier;
  emlrtMsgIdentifier c19_thisId;
  real_T c19_y[3];
  int32_T c19_i180;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_b_prop = sf_mex_dup(c19_mxArrayInData);
  c19_identifier = c19_varName;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_b_prop), &c19_thisId,
    c19_y);
  sf_mex_destroy(&c19_b_prop);
  for (c19_i180 = 0; c19_i180 < 3; c19_i180++) {
    (*(real_T (*)[3])c19_outData)[c19_i180] = c19_y[c19_i180];
  }

  sf_mex_destroy(&c19_mxArrayInData);
}

static const mxArray *c19_f_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData)
{
  const mxArray *c19_mxArrayOutData = NULL;
  int32_T c19_i181;
  real_T c19_b_inData[4];
  int32_T c19_i182;
  real_T c19_u[4];
  const mxArray *c19_y = NULL;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_mxArrayOutData = NULL;
  for (c19_i181 = 0; c19_i181 < 4; c19_i181++) {
    c19_b_inData[c19_i181] = (*(real_T (*)[4])c19_inData)[c19_i181];
  }

  for (c19_i182 = 0; c19_i182 < 4; c19_i182++) {
    c19_u[c19_i182] = c19_b_inData[c19_i182];
  }

  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", c19_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c19_mxArrayOutData, c19_y, FALSE);
  return c19_mxArrayOutData;
}

static void c19_i_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[4])
{
  real_T c19_dv6[4];
  int32_T c19_i183;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), c19_dv6, 1, 0, 0U, 1, 0U, 1, 4);
  for (c19_i183 = 0; c19_i183 < 4; c19_i183++) {
    c19_y[c19_i183] = c19_dv6[c19_i183];
  }

  sf_mex_destroy(&c19_u);
}

static void c19_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData)
{
  const mxArray *c19_q_prop;
  const char_T *c19_identifier;
  emlrtMsgIdentifier c19_thisId;
  real_T c19_y[4];
  int32_T c19_i184;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_q_prop = sf_mex_dup(c19_mxArrayInData);
  c19_identifier = c19_varName;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_q_prop), &c19_thisId,
    c19_y);
  sf_mex_destroy(&c19_q_prop);
  for (c19_i184 = 0; c19_i184 < 4; c19_i184++) {
    (*(real_T (*)[4])c19_outData)[c19_i184] = c19_y[c19_i184];
  }

  sf_mex_destroy(&c19_mxArrayInData);
}

static const mxArray *c19_g_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData)
{
  const mxArray *c19_mxArrayOutData = NULL;
  int32_T c19_i185;
  int32_T c19_i186;
  int32_T c19_i187;
  real_T c19_b_inData[16];
  int32_T c19_i188;
  int32_T c19_i189;
  int32_T c19_i190;
  real_T c19_u[16];
  const mxArray *c19_y = NULL;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_mxArrayOutData = NULL;
  c19_i185 = 0;
  for (c19_i186 = 0; c19_i186 < 4; c19_i186++) {
    for (c19_i187 = 0; c19_i187 < 4; c19_i187++) {
      c19_b_inData[c19_i187 + c19_i185] = (*(real_T (*)[16])c19_inData)[c19_i187
        + c19_i185];
    }

    c19_i185 += 4;
  }

  c19_i188 = 0;
  for (c19_i189 = 0; c19_i189 < 4; c19_i189++) {
    for (c19_i190 = 0; c19_i190 < 4; c19_i190++) {
      c19_u[c19_i190 + c19_i188] = c19_b_inData[c19_i190 + c19_i188];
    }

    c19_i188 += 4;
  }

  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", c19_u, 0, 0U, 1U, 0U, 2, 4, 4), FALSE);
  sf_mex_assign(&c19_mxArrayOutData, c19_y, FALSE);
  return c19_mxArrayOutData;
}

static void c19_j_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId, real_T c19_y[16])
{
  real_T c19_dv7[16];
  int32_T c19_i191;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), c19_dv7, 1, 0, 0U, 1, 0U, 2, 4,
                4);
  for (c19_i191 = 0; c19_i191 < 16; c19_i191++) {
    c19_y[c19_i191] = c19_dv7[c19_i191];
  }

  sf_mex_destroy(&c19_u);
}

static void c19_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData)
{
  const mxArray *c19_M;
  const char_T *c19_identifier;
  emlrtMsgIdentifier c19_thisId;
  real_T c19_y[16];
  int32_T c19_i192;
  int32_T c19_i193;
  int32_T c19_i194;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_M = sf_mex_dup(c19_mxArrayInData);
  c19_identifier = c19_varName;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_M), &c19_thisId, c19_y);
  sf_mex_destroy(&c19_M);
  c19_i192 = 0;
  for (c19_i193 = 0; c19_i193 < 4; c19_i193++) {
    for (c19_i194 = 0; c19_i194 < 4; c19_i194++) {
      (*(real_T (*)[16])c19_outData)[c19_i194 + c19_i192] = c19_y[c19_i194 +
        c19_i192];
    }

    c19_i192 += 4;
  }

  sf_mex_destroy(&c19_mxArrayInData);
}

const mxArray
  *sf_c19_Tetraedro_model_sem_sim_com_FK_heur_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c19_nameCaptureInfo;
  c19_ResolvedFunctionInfo c19_info[60];
  const mxArray *c19_m0 = NULL;
  int32_T c19_i195;
  c19_ResolvedFunctionInfo *c19_r0;
  c19_nameCaptureInfo = NULL;
  c19_nameCaptureInfo = NULL;
  c19_info_helper(c19_info);
  sf_mex_assign(&c19_m0, sf_mex_createstruct("nameCaptureInfo", 1, 60), FALSE);
  for (c19_i195 = 0; c19_i195 < 60; c19_i195++) {
    c19_r0 = &c19_info[c19_i195];
    sf_mex_addfield(c19_m0, sf_mex_create("nameCaptureInfo", c19_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c19_r0->context)), "context", "nameCaptureInfo",
                    c19_i195);
    sf_mex_addfield(c19_m0, sf_mex_create("nameCaptureInfo", c19_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c19_r0->name)), "name", "nameCaptureInfo",
                    c19_i195);
    sf_mex_addfield(c19_m0, sf_mex_create("nameCaptureInfo",
      c19_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c19_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c19_i195);
    sf_mex_addfield(c19_m0, sf_mex_create("nameCaptureInfo", c19_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c19_r0->resolved)), "resolved",
                    "nameCaptureInfo", c19_i195);
    sf_mex_addfield(c19_m0, sf_mex_create("nameCaptureInfo", &c19_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c19_i195);
    sf_mex_addfield(c19_m0, sf_mex_create("nameCaptureInfo", &c19_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c19_i195);
    sf_mex_addfield(c19_m0, sf_mex_create("nameCaptureInfo",
      &c19_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c19_i195);
    sf_mex_addfield(c19_m0, sf_mex_create("nameCaptureInfo",
      &c19_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c19_i195);
  }

  sf_mex_assign(&c19_nameCaptureInfo, c19_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c19_nameCaptureInfo);
  return c19_nameCaptureInfo;
}

static void c19_info_helper(c19_ResolvedFunctionInfo c19_info[60])
{
  c19_info[0].context = "";
  c19_info[0].name = "mtimes";
  c19_info[0].dominantType = "double";
  c19_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c19_info[0].fileTimeLo = 1289530492U;
  c19_info[0].fileTimeHi = 0U;
  c19_info[0].mFileTimeLo = 0U;
  c19_info[0].mFileTimeHi = 0U;
  c19_info[1].context = "";
  c19_info[1].name = "eye";
  c19_info[1].dominantType = "double";
  c19_info[1].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m";
  c19_info[1].fileTimeLo = 1286836688U;
  c19_info[1].fileTimeHi = 0U;
  c19_info[1].mFileTimeLo = 0U;
  c19_info[1].mFileTimeHi = 0U;
  c19_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c19_info[2].name = "eml_assert_valid_size_arg";
  c19_info[2].dominantType = "double";
  c19_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c19_info[2].fileTimeLo = 1286836694U;
  c19_info[2].fileTimeHi = 0U;
  c19_info[2].mFileTimeLo = 0U;
  c19_info[2].mFileTimeHi = 0U;
  c19_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c19_info[3].name = "isinf";
  c19_info[3].dominantType = "double";
  c19_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c19_info[3].fileTimeLo = 1286836760U;
  c19_info[3].fileTimeHi = 0U;
  c19_info[3].mFileTimeLo = 0U;
  c19_info[3].mFileTimeHi = 0U;
  c19_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c19_info[4].name = "mtimes";
  c19_info[4].dominantType = "double";
  c19_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c19_info[4].fileTimeLo = 1289530492U;
  c19_info[4].fileTimeHi = 0U;
  c19_info[4].mFileTimeLo = 0U;
  c19_info[4].mFileTimeHi = 0U;
  c19_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c19_info[5].name = "eml_index_class";
  c19_info[5].dominantType = "";
  c19_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[5].fileTimeLo = 1323181378U;
  c19_info[5].fileTimeHi = 0U;
  c19_info[5].mFileTimeLo = 0U;
  c19_info[5].mFileTimeHi = 0U;
  c19_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c19_info[6].name = "intmax";
  c19_info[6].dominantType = "char";
  c19_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c19_info[6].fileTimeLo = 1311273316U;
  c19_info[6].fileTimeHi = 0U;
  c19_info[6].mFileTimeLo = 0U;
  c19_info[6].mFileTimeHi = 0U;
  c19_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c19_info[7].name = "eml_is_float_class";
  c19_info[7].dominantType = "char";
  c19_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c19_info[7].fileTimeLo = 1286836782U;
  c19_info[7].fileTimeHi = 0U;
  c19_info[7].mFileTimeLo = 0U;
  c19_info[7].mFileTimeHi = 0U;
  c19_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c19_info[8].name = "min";
  c19_info[8].dominantType = "double";
  c19_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c19_info[8].fileTimeLo = 1311273318U;
  c19_info[8].fileTimeHi = 0U;
  c19_info[8].mFileTimeLo = 0U;
  c19_info[8].mFileTimeHi = 0U;
  c19_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c19_info[9].name = "eml_min_or_max";
  c19_info[9].dominantType = "char";
  c19_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c19_info[9].fileTimeLo = 1334089490U;
  c19_info[9].fileTimeHi = 0U;
  c19_info[9].mFileTimeLo = 0U;
  c19_info[9].mFileTimeHi = 0U;
  c19_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c19_info[10].name = "eml_scalar_eg";
  c19_info[10].dominantType = "double";
  c19_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c19_info[10].fileTimeLo = 1286836796U;
  c19_info[10].fileTimeHi = 0U;
  c19_info[10].mFileTimeLo = 0U;
  c19_info[10].mFileTimeHi = 0U;
  c19_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c19_info[11].name = "eml_scalexp_alloc";
  c19_info[11].dominantType = "double";
  c19_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c19_info[11].fileTimeLo = 1352435660U;
  c19_info[11].fileTimeHi = 0U;
  c19_info[11].mFileTimeLo = 0U;
  c19_info[11].mFileTimeHi = 0U;
  c19_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c19_info[12].name = "eml_index_class";
  c19_info[12].dominantType = "";
  c19_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[12].fileTimeLo = 1323181378U;
  c19_info[12].fileTimeHi = 0U;
  c19_info[12].mFileTimeLo = 0U;
  c19_info[12].mFileTimeHi = 0U;
  c19_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c19_info[13].name = "eml_scalar_eg";
  c19_info[13].dominantType = "double";
  c19_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c19_info[13].fileTimeLo = 1286836796U;
  c19_info[13].fileTimeHi = 0U;
  c19_info[13].mFileTimeLo = 0U;
  c19_info[13].mFileTimeHi = 0U;
  c19_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c19_info[14].name = "eml_index_class";
  c19_info[14].dominantType = "";
  c19_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[14].fileTimeLo = 1323181378U;
  c19_info[14].fileTimeHi = 0U;
  c19_info[14].mFileTimeLo = 0U;
  c19_info[14].mFileTimeHi = 0U;
  c19_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c19_info[15].name = "eml_int_forloop_overflow_check";
  c19_info[15].dominantType = "";
  c19_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c19_info[15].fileTimeLo = 1346528340U;
  c19_info[15].fileTimeHi = 0U;
  c19_info[15].mFileTimeLo = 0U;
  c19_info[15].mFileTimeHi = 0U;
  c19_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c19_info[16].name = "intmax";
  c19_info[16].dominantType = "char";
  c19_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c19_info[16].fileTimeLo = 1311273316U;
  c19_info[16].fileTimeHi = 0U;
  c19_info[16].mFileTimeLo = 0U;
  c19_info[16].mFileTimeHi = 0U;
  c19_info[17].context = "";
  c19_info[17].name = "norm";
  c19_info[17].dominantType = "double";
  c19_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c19_info[17].fileTimeLo = 1336540094U;
  c19_info[17].fileTimeHi = 0U;
  c19_info[17].mFileTimeLo = 0U;
  c19_info[17].mFileTimeHi = 0U;
  c19_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c19_info[18].name = "eml_index_class";
  c19_info[18].dominantType = "";
  c19_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[18].fileTimeLo = 1323181378U;
  c19_info[18].fileTimeHi = 0U;
  c19_info[18].mFileTimeLo = 0U;
  c19_info[18].mFileTimeHi = 0U;
  c19_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c19_info[19].name = "eml_xnrm2";
  c19_info[19].dominantType = "double";
  c19_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c19_info[19].fileTimeLo = 1299091176U;
  c19_info[19].fileTimeHi = 0U;
  c19_info[19].mFileTimeLo = 0U;
  c19_info[19].mFileTimeHi = 0U;
  c19_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c19_info[20].name = "eml_blas_inline";
  c19_info[20].dominantType = "";
  c19_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c19_info[20].fileTimeLo = 1299091168U;
  c19_info[20].fileTimeHi = 0U;
  c19_info[20].mFileTimeLo = 0U;
  c19_info[20].mFileTimeHi = 0U;
  c19_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c19_info[21].name = "eml_index_class";
  c19_info[21].dominantType = "";
  c19_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[21].fileTimeLo = 1323181378U;
  c19_info[21].fileTimeHi = 0U;
  c19_info[21].mFileTimeLo = 0U;
  c19_info[21].mFileTimeHi = 0U;
  c19_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c19_info[22].name = "eml_refblas_xnrm2";
  c19_info[22].dominantType = "double";
  c19_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c19_info[22].fileTimeLo = 1299091184U;
  c19_info[22].fileTimeHi = 0U;
  c19_info[22].mFileTimeLo = 0U;
  c19_info[22].mFileTimeHi = 0U;
  c19_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c19_info[23].name = "realmin";
  c19_info[23].dominantType = "char";
  c19_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c19_info[23].fileTimeLo = 1307669242U;
  c19_info[23].fileTimeHi = 0U;
  c19_info[23].mFileTimeLo = 0U;
  c19_info[23].mFileTimeHi = 0U;
  c19_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c19_info[24].name = "eml_realmin";
  c19_info[24].dominantType = "char";
  c19_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c19_info[24].fileTimeLo = 1307669244U;
  c19_info[24].fileTimeHi = 0U;
  c19_info[24].mFileTimeLo = 0U;
  c19_info[24].mFileTimeHi = 0U;
  c19_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c19_info[25].name = "eml_float_model";
  c19_info[25].dominantType = "char";
  c19_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c19_info[25].fileTimeLo = 1326738796U;
  c19_info[25].fileTimeHi = 0U;
  c19_info[25].mFileTimeLo = 0U;
  c19_info[25].mFileTimeHi = 0U;
  c19_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c19_info[26].name = "eml_index_class";
  c19_info[26].dominantType = "";
  c19_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[26].fileTimeLo = 1323181378U;
  c19_info[26].fileTimeHi = 0U;
  c19_info[26].mFileTimeLo = 0U;
  c19_info[26].mFileTimeHi = 0U;
  c19_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c19_info[27].name = "eml_index_minus";
  c19_info[27].dominantType = "double";
  c19_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c19_info[27].fileTimeLo = 1286836778U;
  c19_info[27].fileTimeHi = 0U;
  c19_info[27].mFileTimeLo = 0U;
  c19_info[27].mFileTimeHi = 0U;
  c19_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c19_info[28].name = "eml_index_class";
  c19_info[28].dominantType = "";
  c19_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[28].fileTimeLo = 1323181378U;
  c19_info[28].fileTimeHi = 0U;
  c19_info[28].mFileTimeLo = 0U;
  c19_info[28].mFileTimeHi = 0U;
  c19_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c19_info[29].name = "eml_index_times";
  c19_info[29].dominantType = "coder.internal.indexInt";
  c19_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c19_info[29].fileTimeLo = 1286836780U;
  c19_info[29].fileTimeHi = 0U;
  c19_info[29].mFileTimeLo = 0U;
  c19_info[29].mFileTimeHi = 0U;
  c19_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c19_info[30].name = "eml_index_class";
  c19_info[30].dominantType = "";
  c19_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[30].fileTimeLo = 1323181378U;
  c19_info[30].fileTimeHi = 0U;
  c19_info[30].mFileTimeLo = 0U;
  c19_info[30].mFileTimeHi = 0U;
  c19_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c19_info[31].name = "eml_index_plus";
  c19_info[31].dominantType = "coder.internal.indexInt";
  c19_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c19_info[31].fileTimeLo = 1286836778U;
  c19_info[31].fileTimeHi = 0U;
  c19_info[31].mFileTimeLo = 0U;
  c19_info[31].mFileTimeHi = 0U;
  c19_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c19_info[32].name = "eml_index_class";
  c19_info[32].dominantType = "";
  c19_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[32].fileTimeLo = 1323181378U;
  c19_info[32].fileTimeHi = 0U;
  c19_info[32].mFileTimeLo = 0U;
  c19_info[32].mFileTimeHi = 0U;
  c19_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c19_info[33].name = "eml_int_forloop_overflow_check";
  c19_info[33].dominantType = "";
  c19_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c19_info[33].fileTimeLo = 1346528340U;
  c19_info[33].fileTimeHi = 0U;
  c19_info[33].mFileTimeLo = 0U;
  c19_info[33].mFileTimeHi = 0U;
  c19_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c19_info[34].name = "abs";
  c19_info[34].dominantType = "double";
  c19_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c19_info[34].fileTimeLo = 1343848366U;
  c19_info[34].fileTimeHi = 0U;
  c19_info[34].mFileTimeLo = 0U;
  c19_info[34].mFileTimeHi = 0U;
  c19_info[35].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c19_info[35].name = "eml_scalar_abs";
  c19_info[35].dominantType = "double";
  c19_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c19_info[35].fileTimeLo = 1286836712U;
  c19_info[35].fileTimeHi = 0U;
  c19_info[35].mFileTimeLo = 0U;
  c19_info[35].mFileTimeHi = 0U;
  c19_info[36].context = "";
  c19_info[36].name = "mrdivide";
  c19_info[36].dominantType = "double";
  c19_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c19_info[36].fileTimeLo = 1357962348U;
  c19_info[36].fileTimeHi = 0U;
  c19_info[36].mFileTimeLo = 1319744366U;
  c19_info[36].mFileTimeHi = 0U;
  c19_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c19_info[37].name = "rdivide";
  c19_info[37].dominantType = "double";
  c19_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c19_info[37].fileTimeLo = 1346528388U;
  c19_info[37].fileTimeHi = 0U;
  c19_info[37].mFileTimeLo = 0U;
  c19_info[37].mFileTimeHi = 0U;
  c19_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c19_info[38].name = "eml_scalexp_compatible";
  c19_info[38].dominantType = "double";
  c19_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c19_info[38].fileTimeLo = 1286836796U;
  c19_info[38].fileTimeHi = 0U;
  c19_info[38].mFileTimeLo = 0U;
  c19_info[38].mFileTimeHi = 0U;
  c19_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c19_info[39].name = "eml_div";
  c19_info[39].dominantType = "double";
  c19_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c19_info[39].fileTimeLo = 1313365810U;
  c19_info[39].fileTimeHi = 0U;
  c19_info[39].mFileTimeLo = 0U;
  c19_info[39].mFileTimeHi = 0U;
  c19_info[40].context = "";
  c19_info[40].name = "cos";
  c19_info[40].dominantType = "double";
  c19_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c19_info[40].fileTimeLo = 1343848372U;
  c19_info[40].fileTimeHi = 0U;
  c19_info[40].mFileTimeLo = 0U;
  c19_info[40].mFileTimeHi = 0U;
  c19_info[41].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c19_info[41].name = "eml_scalar_cos";
  c19_info[41].dominantType = "double";
  c19_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c19_info[41].fileTimeLo = 1286836722U;
  c19_info[41].fileTimeHi = 0U;
  c19_info[41].mFileTimeLo = 0U;
  c19_info[41].mFileTimeHi = 0U;
  c19_info[42].context = "";
  c19_info[42].name = "sin";
  c19_info[42].dominantType = "double";
  c19_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c19_info[42].fileTimeLo = 1343848386U;
  c19_info[42].fileTimeHi = 0U;
  c19_info[42].mFileTimeLo = 0U;
  c19_info[42].mFileTimeHi = 0U;
  c19_info[43].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c19_info[43].name = "eml_scalar_sin";
  c19_info[43].dominantType = "double";
  c19_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c19_info[43].fileTimeLo = 1286836736U;
  c19_info[43].fileTimeHi = 0U;
  c19_info[43].mFileTimeLo = 0U;
  c19_info[43].mFileTimeHi = 0U;
  c19_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c19_info[44].name = "eml_index_class";
  c19_info[44].dominantType = "";
  c19_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[44].fileTimeLo = 1323181378U;
  c19_info[44].fileTimeHi = 0U;
  c19_info[44].mFileTimeLo = 0U;
  c19_info[44].mFileTimeHi = 0U;
  c19_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c19_info[45].name = "eml_scalar_eg";
  c19_info[45].dominantType = "double";
  c19_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c19_info[45].fileTimeLo = 1286836796U;
  c19_info[45].fileTimeHi = 0U;
  c19_info[45].mFileTimeLo = 0U;
  c19_info[45].mFileTimeHi = 0U;
  c19_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c19_info[46].name = "eml_xgemm";
  c19_info[46].dominantType = "char";
  c19_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c19_info[46].fileTimeLo = 1299091172U;
  c19_info[46].fileTimeHi = 0U;
  c19_info[46].mFileTimeLo = 0U;
  c19_info[46].mFileTimeHi = 0U;
  c19_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c19_info[47].name = "eml_blas_inline";
  c19_info[47].dominantType = "";
  c19_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c19_info[47].fileTimeLo = 1299091168U;
  c19_info[47].fileTimeHi = 0U;
  c19_info[47].mFileTimeLo = 0U;
  c19_info[47].mFileTimeHi = 0U;
  c19_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c19_info[48].name = "mtimes";
  c19_info[48].dominantType = "double";
  c19_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c19_info[48].fileTimeLo = 1289530492U;
  c19_info[48].fileTimeHi = 0U;
  c19_info[48].mFileTimeLo = 0U;
  c19_info[48].mFileTimeHi = 0U;
  c19_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c19_info[49].name = "eml_index_class";
  c19_info[49].dominantType = "";
  c19_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c19_info[49].fileTimeLo = 1323181378U;
  c19_info[49].fileTimeHi = 0U;
  c19_info[49].mFileTimeLo = 0U;
  c19_info[49].mFileTimeHi = 0U;
  c19_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c19_info[50].name = "eml_scalar_eg";
  c19_info[50].dominantType = "double";
  c19_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c19_info[50].fileTimeLo = 1286836796U;
  c19_info[50].fileTimeHi = 0U;
  c19_info[50].mFileTimeLo = 0U;
  c19_info[50].mFileTimeHi = 0U;
  c19_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c19_info[51].name = "eml_refblas_xgemm";
  c19_info[51].dominantType = "char";
  c19_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c19_info[51].fileTimeLo = 1299091174U;
  c19_info[51].fileTimeHi = 0U;
  c19_info[51].mFileTimeLo = 0U;
  c19_info[51].mFileTimeHi = 0U;
  c19_info[52].context = "";
  c19_info[52].name = "mpower";
  c19_info[52].dominantType = "double";
  c19_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c19_info[52].fileTimeLo = 1286836842U;
  c19_info[52].fileTimeHi = 0U;
  c19_info[52].mFileTimeLo = 0U;
  c19_info[52].mFileTimeHi = 0U;
  c19_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c19_info[53].name = "power";
  c19_info[53].dominantType = "double";
  c19_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c19_info[53].fileTimeLo = 1348209930U;
  c19_info[53].fileTimeHi = 0U;
  c19_info[53].mFileTimeLo = 0U;
  c19_info[53].mFileTimeHi = 0U;
  c19_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c19_info[54].name = "eml_scalar_eg";
  c19_info[54].dominantType = "double";
  c19_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c19_info[54].fileTimeLo = 1286836796U;
  c19_info[54].fileTimeHi = 0U;
  c19_info[54].mFileTimeLo = 0U;
  c19_info[54].mFileTimeHi = 0U;
  c19_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c19_info[55].name = "eml_scalexp_alloc";
  c19_info[55].dominantType = "double";
  c19_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c19_info[55].fileTimeLo = 1352435660U;
  c19_info[55].fileTimeHi = 0U;
  c19_info[55].mFileTimeLo = 0U;
  c19_info[55].mFileTimeHi = 0U;
  c19_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c19_info[56].name = "floor";
  c19_info[56].dominantType = "double";
  c19_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c19_info[56].fileTimeLo = 1343848380U;
  c19_info[56].fileTimeHi = 0U;
  c19_info[56].mFileTimeLo = 0U;
  c19_info[56].mFileTimeHi = 0U;
  c19_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c19_info[57].name = "eml_scalar_floor";
  c19_info[57].dominantType = "double";
  c19_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c19_info[57].fileTimeLo = 1286836726U;
  c19_info[57].fileTimeHi = 0U;
  c19_info[57].mFileTimeLo = 0U;
  c19_info[57].mFileTimeHi = 0U;
  c19_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c19_info[58].name = "eml_scalar_eg";
  c19_info[58].dominantType = "double";
  c19_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c19_info[58].fileTimeLo = 1286836796U;
  c19_info[58].fileTimeHi = 0U;
  c19_info[58].mFileTimeLo = 0U;
  c19_info[58].mFileTimeHi = 0U;
  c19_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c19_info[59].name = "mtimes";
  c19_info[59].dominantType = "double";
  c19_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c19_info[59].fileTimeLo = 1289530492U;
  c19_info[59].fileTimeHi = 0U;
  c19_info[59].mFileTimeLo = 0U;
  c19_info[59].mFileTimeHi = 0U;
}

static void c19_eml_scalar_eg
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static real_T c19_norm(SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct
  *chartInstance, real_T c19_x[3])
{
  real_T c19_y;
  real_T c19_scale;
  int32_T c19_k;
  int32_T c19_b_k;
  real_T c19_b_x;
  real_T c19_c_x;
  real_T c19_absxk;
  real_T c19_t;
  c19_y = 0.0;
  c19_scale = 2.2250738585072014E-308;
  for (c19_k = 1; c19_k < 4; c19_k++) {
    c19_b_k = c19_k;
    c19_b_x = c19_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
      "", (real_T)c19_b_k), 1, 3, 1, 0) - 1];
    c19_c_x = c19_b_x;
    c19_absxk = muDoubleScalarAbs(c19_c_x);
    if (c19_absxk > c19_scale) {
      c19_t = c19_scale / c19_absxk;
      c19_y = 1.0 + c19_y * c19_t * c19_t;
      c19_scale = c19_absxk;
    } else {
      c19_t = c19_absxk / c19_scale;
      c19_y += c19_t * c19_t;
    }
  }

  return c19_scale * muDoubleScalarSqrt(c19_y);
}

static void c19_b_eml_scalar_eg
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void c19_eye(SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct
                    *chartInstance, real_T c19_I[9])
{
  int32_T c19_i196;
  int32_T c19_i;
  int32_T c19_b_i;
  for (c19_i196 = 0; c19_i196 < 9; c19_i196++) {
    c19_I[c19_i196] = 0.0;
  }

  for (c19_i = 1; c19_i < 4; c19_i++) {
    c19_b_i = c19_i;
    c19_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c19_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c19_b_i), 1, 3, 2, 0) - 1))
      - 1] = 1.0;
  }
}

static void c19_c_eml_scalar_eg
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static real_T c19_mpower(SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct
  *chartInstance, real_T c19_a)
{
  real_T c19_b_a;
  real_T c19_c_a;
  real_T c19_ak;
  real_T c19_d_a;
  real_T c19_e_a;
  real_T c19_b;
  c19_b_a = c19_a;
  c19_c_a = c19_b_a;
  c19_eml_scalar_eg(chartInstance);
  c19_ak = c19_c_a;
  c19_d_a = c19_ak;
  c19_eml_scalar_eg(chartInstance);
  c19_e_a = c19_d_a;
  c19_b = c19_d_a;
  return c19_e_a * c19_b;
}

static void c19_d_eml_scalar_eg
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static const mxArray *c19_h_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData)
{
  const mxArray *c19_mxArrayOutData = NULL;
  int32_T c19_u;
  const mxArray *c19_y = NULL;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_mxArrayOutData = NULL;
  c19_u = *(int32_T *)c19_inData;
  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", &c19_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c19_mxArrayOutData, c19_y, FALSE);
  return c19_mxArrayOutData;
}

static int32_T c19_k_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId)
{
  int32_T c19_y;
  int32_T c19_i197;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), &c19_i197, 1, 6, 0U, 0, 0U, 0);
  c19_y = c19_i197;
  sf_mex_destroy(&c19_u);
  return c19_y;
}

static void c19_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData)
{
  const mxArray *c19_b_sfEvent;
  const char_T *c19_identifier;
  emlrtMsgIdentifier c19_thisId;
  int32_T c19_y;
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c19_b_sfEvent = sf_mex_dup(c19_mxArrayInData);
  c19_identifier = c19_varName;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_y = c19_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_b_sfEvent),
    &c19_thisId);
  sf_mex_destroy(&c19_b_sfEvent);
  *(int32_T *)c19_outData = c19_y;
  sf_mex_destroy(&c19_mxArrayInData);
}

static uint8_T c19_l_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_b_is_active_c19_Tetraedro_model_sem_sim_com_FK_heur, const
   char_T *c19_identifier)
{
  uint8_T c19_y;
  emlrtMsgIdentifier c19_thisId;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_y = c19_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c19_b_is_active_c19_Tetraedro_model_sem_sim_com_FK_heur), &c19_thisId);
  sf_mex_destroy(&c19_b_is_active_c19_Tetraedro_model_sem_sim_com_FK_heur);
  return c19_y;
}

static uint8_T c19_m_emlrt_marshallIn
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId)
{
  uint8_T c19_y;
  uint8_T c19_u0;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), &c19_u0, 1, 3, 0U, 0, 0U, 0);
  c19_y = c19_u0;
  sf_mex_destroy(&c19_u);
  return c19_y;
}

static void init_dsm_address_info
  (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
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

void sf_c19_Tetraedro_model_sem_sim_com_FK_heur_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(117555088U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(665622924U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2887445302U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2160608143U);
}

mxArray *sf_c19_Tetraedro_model_sem_sim_com_FK_heur_get_autoinheritance_info
  (void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("BqcDgCUqwSuA4vNJRRmBMC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

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
      pr[0] = (double)(1);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(6);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
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
      pr[0] = (double)(1);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c19_Tetraedro_model_sem_sim_com_FK_heur_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray
  *sf_get_sim_state_info_c19_Tetraedro_model_sem_sim_com_FK_heur(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[10],T\"PT_prop\",},{M[1],M[12],T\"i_out\",},{M[1],M[5],T\"x_prop\",},{M[8],M[0],T\"is_active_c19_Tetraedro_model_sem_sim_com_FK_heur\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c19_Tetraedro_model_sem_sim_com_FK_heur_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
    chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Tetraedro_model_sem_sim_com_FK_heurMachineNumber_,
           19,
           1,
           1,
           9,
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
            (_Tetraedro_model_sem_sim_com_FK_heurMachineNumber_,
             chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,
             _Tetraedro_model_sem_sim_com_FK_heurMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _Tetraedro_model_sem_sim_com_FK_heurMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"w_gyro");
          _SFD_SET_DATA_PROPS(1,2,0,1,"x_prop");
          _SFD_SET_DATA_PROPS(2,1,1,0,"Dt");
          _SFD_SET_DATA_PROPS(3,1,1,0,"PT_est");
          _SFD_SET_DATA_PROPS(4,1,1,0,"x_est");
          _SFD_SET_DATA_PROPS(5,1,1,0,"Q");
          _SFD_SET_DATA_PROPS(6,2,0,1,"PT_prop");
          _SFD_SET_DATA_PROPS(7,1,1,0,"i_in");
          _SFD_SET_DATA_PROPS(8,2,0,1,"i_out");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1547);
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
            1.0,0,0,(MexFcnForType)c19_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c19_c_sf_marshallOut,(MexInFcnForType)
            c19_c_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c19_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c19_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c19_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c19_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c19_b_sf_marshallOut,(MexInFcnForType)
            c19_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c19_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c19_sf_marshallOut,(MexInFcnForType)c19_sf_marshallIn);

        {
          real_T *c19_Dt;
          real_T *c19_i_in;
          real_T *c19_i_out;
          real_T (*c19_w_gyro)[3];
          real_T (*c19_x_prop)[7];
          real_T (*c19_PT_est)[36];
          real_T (*c19_x_est)[7];
          real_T (*c19_Q)[36];
          real_T (*c19_PT_prop)[36];
          c19_i_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c19_i_in = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c19_PT_prop = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S,
            2);
          c19_Q = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 4);
          c19_x_est = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 3);
          c19_PT_est = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 2);
          c19_Dt = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c19_x_prop = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
          c19_w_gyro = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c19_w_gyro);
          _SFD_SET_DATA_VALUE_PTR(1U, *c19_x_prop);
          _SFD_SET_DATA_VALUE_PTR(2U, c19_Dt);
          _SFD_SET_DATA_VALUE_PTR(3U, *c19_PT_est);
          _SFD_SET_DATA_VALUE_PTR(4U, *c19_x_est);
          _SFD_SET_DATA_VALUE_PTR(5U, *c19_Q);
          _SFD_SET_DATA_VALUE_PTR(6U, *c19_PT_prop);
          _SFD_SET_DATA_VALUE_PTR(7U, c19_i_in);
          _SFD_SET_DATA_VALUE_PTR(8U, c19_i_out);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _Tetraedro_model_sem_sim_com_FK_heurMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "4GUIKMHRIGruagEiBj8ImB";
}

static void sf_opaque_initialize_c19_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  chart_debug_initialization
    (((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
      chartInstanceVar)->S,0);
  initialize_params_c19_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
  initialize_c19_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c19_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  enable_c19_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c19_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  disable_c19_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c19_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  sf_c19_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

extern const mxArray*
  sf_internal_get_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
     chartInfo->chartInstance);        /* raw sim ctx */
  prhs[3] = (mxArray*)
    sf_get_sim_state_info_c19_Tetraedro_model_sem_sim_com_FK_heur();/* state var info */
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

extern void sf_internal_set_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur
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
    sf_get_sim_state_info_c19_Tetraedro_model_sem_sim_com_FK_heur();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
     chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray*
  sf_opaque_get_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur(SimStruct* S)
{
  return sf_internal_get_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur(S);
}

static void sf_opaque_set_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur(S, st);
}

static void sf_opaque_terminate_c19_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Tetraedro_model_sem_sim_com_FK_heur_optimization_info();
    }

    finalize_c19_Tetraedro_model_sem_sim_com_FK_heur
      ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
       chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc19_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c19_Tetraedro_model_sem_sim_com_FK_heur
  (SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c19_Tetraedro_model_sem_sim_com_FK_heur
      ((SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
       (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c19_Tetraedro_model_sem_sim_com_FK_heur(SimStruct
  *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct =
      load_Tetraedro_model_sem_sim_com_FK_heur_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      19);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,19,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,19,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,19);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,19,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,19,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 6; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,19);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2642667796U));
  ssSetChecksum1(S,(1843760551U));
  ssSetChecksum2(S,(3734956083U));
  ssSetChecksum3(S,(2953787574U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c19_Tetraedro_model_sem_sim_com_FK_heur(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c19_Tetraedro_model_sem_sim_com_FK_heur(SimStruct *S)
{
  SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    utMalloc(sizeof(SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc19_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c19_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c19_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c19_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c19_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c19_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c19_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c19_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW =
    mdlRTW_c19_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.mdlStart =
    mdlStart_c19_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c19_Tetraedro_model_sem_sim_com_FK_heur;
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

void c19_Tetraedro_model_sem_sim_com_FK_heur_method_dispatcher(SimStruct *S,
  int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c19_Tetraedro_model_sem_sim_com_FK_heur(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c19_Tetraedro_model_sem_sim_com_FK_heur(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c19_Tetraedro_model_sem_sim_com_FK_heur(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c19_Tetraedro_model_sem_sim_com_FK_heur_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
