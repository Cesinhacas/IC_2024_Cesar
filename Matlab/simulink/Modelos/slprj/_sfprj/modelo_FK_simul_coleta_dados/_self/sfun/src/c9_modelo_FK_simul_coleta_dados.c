/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_FK_simul_coleta_dados_sfun.h"
#include "c9_modelo_FK_simul_coleta_dados.h"
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
static const char * c9_debug_family_names[24] = { "V1", "V2", "W1", "W2",
  "SigTot1", "SigTot2", "r1", "r2", "r3", "Mref", "s1", "s2", "s3", "Mobs",
  "nargin", "nargout", "sig_mag", "mag_rec", "mag_ref", "acc_ref", "acc_rec",
  "sig_acc", "A", "R" };

/* Function Declarations */
static void initialize_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void initialize_params_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void enable_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void disable_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c9_update_debugger_state_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void set_sim_state_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_st);
static void finalize_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void sf_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void c9_chartstep_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void initSimStructsc9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void registerMessagesc9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber);
static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData);
static void c9_emlrt_marshallIn(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *
  chartInstance, const mxArray *c9_R, const char_T *c9_identifier, real_T c9_y[9]);
static void c9_b_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_u, const emlrtMsgIdentifier *c9_parentId, real_T c9_y[9]);
static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static real_T c9_c_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static void c9_d_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_u, const emlrtMsgIdentifier *c9_parentId, real_T c9_y[3]);
static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static void c9_info_helper(c9_ResolvedFunctionInfo c9_info[71]);
static real_T c9_norm(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c9_x[3]);
static void c9_cross(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
                     *chartInstance, real_T c9_a[3], real_T c9_b[3], real_T
                     c9_c[3]);
static void c9_eml_scalar_eg(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static real_T c9_mpower(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, real_T c9_a);
static void c9_b_eml_scalar_eg(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static void c9_c_eml_scalar_eg(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance);
static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static int32_T c9_e_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static uint8_T c9_f_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_b_is_active_c9_modelo_FK_simul_coleta_dados, const char_T *c9_identifier);
static uint8_T c9_g_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void init_dsm_address_info
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  chartInstance->c9_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c9_is_active_c9_modelo_FK_simul_coleta_dados = 0U;
}

static void initialize_params_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void enable_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c9_update_debugger_state_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  const mxArray *c9_st;
  const mxArray *c9_y = NULL;
  int32_T c9_i0;
  real_T c9_u[9];
  const mxArray *c9_b_y = NULL;
  int32_T c9_i1;
  real_T c9_b_u[9];
  const mxArray *c9_c_y = NULL;
  uint8_T c9_hoistedGlobal;
  uint8_T c9_c_u;
  const mxArray *c9_d_y = NULL;
  real_T (*c9_R)[9];
  real_T (*c9_A)[9];
  c9_R = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c9_A = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_st = NULL;
  c9_st = NULL;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_createcellarray(3), FALSE);
  for (c9_i0 = 0; c9_i0 < 9; c9_i0++) {
    c9_u[c9_i0] = (*c9_A)[c9_i0];
  }

  c9_b_y = NULL;
  sf_mex_assign(&c9_b_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_setcell(c9_y, 0, c9_b_y);
  for (c9_i1 = 0; c9_i1 < 9; c9_i1++) {
    c9_b_u[c9_i1] = (*c9_R)[c9_i1];
  }

  c9_c_y = NULL;
  sf_mex_assign(&c9_c_y, sf_mex_create("y", c9_b_u, 0, 0U, 1U, 0U, 2, 3, 3),
                FALSE);
  sf_mex_setcell(c9_y, 1, c9_c_y);
  c9_hoistedGlobal = chartInstance->c9_is_active_c9_modelo_FK_simul_coleta_dados;
  c9_c_u = c9_hoistedGlobal;
  c9_d_y = NULL;
  sf_mex_assign(&c9_d_y, sf_mex_create("y", &c9_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 2, c9_d_y);
  sf_mex_assign(&c9_st, c9_y, FALSE);
  return c9_st;
}

static void set_sim_state_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_st)
{
  const mxArray *c9_u;
  real_T c9_dv0[9];
  int32_T c9_i2;
  real_T c9_dv1[9];
  int32_T c9_i3;
  real_T (*c9_A)[9];
  real_T (*c9_R)[9];
  c9_R = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c9_A = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c9_doneDoubleBufferReInit = TRUE;
  c9_u = sf_mex_dup(c9_st);
  c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 0)), "A",
                      c9_dv0);
  for (c9_i2 = 0; c9_i2 < 9; c9_i2++) {
    (*c9_A)[c9_i2] = c9_dv0[c9_i2];
  }

  c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 1)), "R",
                      c9_dv1);
  for (c9_i3 = 0; c9_i3 < 9; c9_i3++) {
    (*c9_R)[c9_i3] = c9_dv1[c9_i3];
  }

  chartInstance->c9_is_active_c9_modelo_FK_simul_coleta_dados =
    c9_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 2)),
    "is_active_c9_modelo_FK_simul_coleta_dados");
  sf_mex_destroy(&c9_u);
  c9_update_debugger_state_c9_modelo_FK_simul_coleta_dados(chartInstance);
  sf_mex_destroy(&c9_st);
}

static void finalize_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void sf_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  int32_T c9_i4;
  int32_T c9_i5;
  int32_T c9_i6;
  int32_T c9_i7;
  int32_T c9_i8;
  int32_T c9_i9;
  int32_T c9_i10;
  int32_T c9_i11;
  real_T (*c9_R)[9];
  real_T (*c9_sig_acc)[3];
  real_T (*c9_acc_rec)[3];
  real_T (*c9_acc_ref)[3];
  real_T (*c9_mag_ref)[3];
  real_T (*c9_mag_rec)[3];
  real_T (*c9_A)[9];
  real_T (*c9_sig_mag)[3];
  c9_R = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c9_sig_acc = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
  c9_acc_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c9_acc_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c9_mag_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c9_mag_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c9_A = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_sig_mag = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  for (c9_i4 = 0; c9_i4 < 3; c9_i4++) {
    _SFD_DATA_RANGE_CHECK((*c9_sig_mag)[c9_i4], 0U);
  }

  for (c9_i5 = 0; c9_i5 < 9; c9_i5++) {
    _SFD_DATA_RANGE_CHECK((*c9_A)[c9_i5], 1U);
  }

  for (c9_i6 = 0; c9_i6 < 3; c9_i6++) {
    _SFD_DATA_RANGE_CHECK((*c9_mag_rec)[c9_i6], 2U);
  }

  for (c9_i7 = 0; c9_i7 < 3; c9_i7++) {
    _SFD_DATA_RANGE_CHECK((*c9_mag_ref)[c9_i7], 3U);
  }

  for (c9_i8 = 0; c9_i8 < 3; c9_i8++) {
    _SFD_DATA_RANGE_CHECK((*c9_acc_ref)[c9_i8], 4U);
  }

  for (c9_i9 = 0; c9_i9 < 3; c9_i9++) {
    _SFD_DATA_RANGE_CHECK((*c9_acc_rec)[c9_i9], 5U);
  }

  for (c9_i10 = 0; c9_i10 < 3; c9_i10++) {
    _SFD_DATA_RANGE_CHECK((*c9_sig_acc)[c9_i10], 6U);
  }

  for (c9_i11 = 0; c9_i11 < 9; c9_i11++) {
    _SFD_DATA_RANGE_CHECK((*c9_R)[c9_i11], 7U);
  }

  chartInstance->c9_sfEvent = CALL_EVENT;
  c9_chartstep_c9_modelo_FK_simul_coleta_dados(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_modelo_FK_simul_coleta_dadosMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c9_chartstep_c9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
  int32_T c9_i12;
  real_T c9_sig_mag[3];
  int32_T c9_i13;
  real_T c9_mag_rec[3];
  int32_T c9_i14;
  real_T c9_mag_ref[3];
  int32_T c9_i15;
  real_T c9_acc_ref[3];
  int32_T c9_i16;
  real_T c9_acc_rec[3];
  int32_T c9_i17;
  real_T c9_sig_acc[3];
  uint32_T c9_debug_family_var_map[24];
  real_T c9_V1[3];
  real_T c9_V2[3];
  real_T c9_W1[3];
  real_T c9_W2[3];
  real_T c9_SigTot1;
  real_T c9_SigTot2;
  real_T c9_r1[3];
  real_T c9_r2[3];
  real_T c9_r3[3];
  real_T c9_Mref[9];
  real_T c9_s1[3];
  real_T c9_s2[3];
  real_T c9_s3[3];
  real_T c9_Mobs[9];
  real_T c9_nargin = 6.0;
  real_T c9_nargout = 2.0;
  real_T c9_A[9];
  real_T c9_R[9];
  int32_T c9_i18;
  int32_T c9_i19;
  int32_T c9_i20;
  int32_T c9_i21;
  int32_T c9_i22;
  real_T c9_b_A[3];
  int32_T c9_i23;
  real_T c9_b_V1[3];
  real_T c9_B;
  real_T c9_y;
  real_T c9_b_y;
  int32_T c9_i24;
  int32_T c9_i25;
  real_T c9_c_V1[3];
  int32_T c9_i26;
  real_T c9_b_V2[3];
  real_T c9_dv2[3];
  int32_T c9_i27;
  int32_T c9_i28;
  int32_T c9_i29;
  real_T c9_b_r2[3];
  real_T c9_b_B;
  real_T c9_c_y;
  real_T c9_d_y;
  int32_T c9_i30;
  int32_T c9_i31;
  real_T c9_b_r1[3];
  int32_T c9_i32;
  real_T c9_c_r2[3];
  real_T c9_dv3[3];
  int32_T c9_i33;
  int32_T c9_i34;
  int32_T c9_i35;
  int32_T c9_i36;
  int32_T c9_i37;
  int32_T c9_i38;
  real_T c9_b_W1[3];
  real_T c9_c_B;
  real_T c9_e_y;
  real_T c9_f_y;
  int32_T c9_i39;
  int32_T c9_i40;
  real_T c9_c_W1[3];
  int32_T c9_i41;
  real_T c9_b_W2[3];
  real_T c9_dv4[3];
  int32_T c9_i42;
  int32_T c9_i43;
  int32_T c9_i44;
  real_T c9_b_s2[3];
  real_T c9_d_B;
  real_T c9_g_y;
  real_T c9_h_y;
  int32_T c9_i45;
  int32_T c9_i46;
  real_T c9_b_s1[3];
  int32_T c9_i47;
  real_T c9_c_s2[3];
  real_T c9_dv5[3];
  int32_T c9_i48;
  int32_T c9_i49;
  int32_T c9_i50;
  int32_T c9_i51;
  int32_T c9_i52;
  real_T c9_a[9];
  int32_T c9_i53;
  int32_T c9_i54;
  int32_T c9_i55;
  int32_T c9_i56;
  real_T c9_b[9];
  int32_T c9_i57;
  int32_T c9_i58;
  int32_T c9_i59;
  real_T c9_C[9];
  int32_T c9_i60;
  int32_T c9_i61;
  int32_T c9_i62;
  int32_T c9_i63;
  int32_T c9_i64;
  int32_T c9_i65;
  int32_T c9_i66;
  int32_T c9_i67;
  real_T c9_b_a;
  int32_T c9_i68;
  static real_T c9_b_b[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c9_i69;
  real_T c9_d_W1[3];
  int32_T c9_i70;
  real_T c9_c_W2[3];
  int32_T c9_i71;
  real_T c9_c_A[3];
  real_T c9_e_B;
  real_T c9_i_y;
  real_T c9_j_y;
  real_T c9_k_y;
  int32_T c9_i72;
  real_T c9_c_a[3];
  int32_T c9_i73;
  real_T c9_l_y;
  int32_T c9_k;
  int32_T c9_b_k;
  real_T c9_d_a;
  real_T c9_c_b;
  real_T c9_m_y;
  int32_T c9_i74;
  int32_T c9_i75;
  int32_T c9_i76;
  int32_T c9_i77;
  int32_T c9_i78;
  int32_T c9_i79;
  int32_T c9_i80;
  int32_T c9_i81;
  int32_T c9_i82;
  int32_T c9_i83;
  real_T c9_e_a;
  int32_T c9_i84;
  int32_T c9_i85;
  real_T c9_f_a;
  int32_T c9_i86;
  int32_T c9_i87;
  int32_T c9_i88;
  int32_T c9_i89;
  int32_T c9_i90;
  int32_T c9_i91;
  real_T c9_g_a;
  int32_T c9_i92;
  int32_T c9_i93;
  int32_T c9_i94;
  int32_T c9_i95;
  int32_T c9_i96;
  real_T (*c9_d_A)[9];
  real_T (*c9_b_R)[9];
  real_T (*c9_b_sig_acc)[3];
  real_T (*c9_b_acc_rec)[3];
  real_T (*c9_b_acc_ref)[3];
  real_T (*c9_b_mag_ref)[3];
  real_T (*c9_b_mag_rec)[3];
  real_T (*c9_b_sig_mag)[3];
  c9_b_R = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c9_b_sig_acc = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
  c9_b_acc_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c9_b_acc_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c9_b_mag_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c9_b_mag_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c9_d_A = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_b_sig_mag = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  for (c9_i12 = 0; c9_i12 < 3; c9_i12++) {
    c9_sig_mag[c9_i12] = (*c9_b_sig_mag)[c9_i12];
  }

  for (c9_i13 = 0; c9_i13 < 3; c9_i13++) {
    c9_mag_rec[c9_i13] = (*c9_b_mag_rec)[c9_i13];
  }

  for (c9_i14 = 0; c9_i14 < 3; c9_i14++) {
    c9_mag_ref[c9_i14] = (*c9_b_mag_ref)[c9_i14];
  }

  for (c9_i15 = 0; c9_i15 < 3; c9_i15++) {
    c9_acc_ref[c9_i15] = (*c9_b_acc_ref)[c9_i15];
  }

  for (c9_i16 = 0; c9_i16 < 3; c9_i16++) {
    c9_acc_rec[c9_i16] = (*c9_b_acc_rec)[c9_i16];
  }

  for (c9_i17 = 0; c9_i17 < 3; c9_i17++) {
    c9_sig_acc[c9_i17] = (*c9_b_sig_acc)[c9_i17];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 24U, 24U, c9_debug_family_names,
    c9_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_V1, 0U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_V2, 1U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_W1, 2U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_W2, 3U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_SigTot1, 4U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_SigTot2, 5U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r1, 6U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r2, 7U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r3, 8U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_Mref, 9U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_s1, 10U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_s2, 11U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_s3, 12U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_Mobs, 13U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargin, 14U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargout, 15U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_sig_mag, 16U, c9_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_mag_rec, 17U, c9_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_mag_ref, 18U, c9_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_acc_ref, 19U, c9_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_acc_rec, 20U, c9_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_sig_acc, 21U, c9_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_A, 22U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_R, 23U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 7);
  for (c9_i18 = 0; c9_i18 < 3; c9_i18++) {
    c9_V1[c9_i18] = c9_acc_ref[c9_i18];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 9);
  for (c9_i19 = 0; c9_i19 < 3; c9_i19++) {
    c9_V2[c9_i19] = c9_mag_ref[c9_i19];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 11);
  for (c9_i20 = 0; c9_i20 < 3; c9_i20++) {
    c9_W1[c9_i20] = c9_acc_rec[c9_i20];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 13);
  for (c9_i21 = 0; c9_i21 < 3; c9_i21++) {
    c9_W2[c9_i21] = c9_mag_rec[c9_i21];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 15);
  c9_SigTot1 = c9_sig_acc[0];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 17);
  c9_SigTot2 = c9_sig_mag[0];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 25);
  for (c9_i22 = 0; c9_i22 < 3; c9_i22++) {
    c9_b_A[c9_i22] = c9_V1[c9_i22];
  }

  for (c9_i23 = 0; c9_i23 < 3; c9_i23++) {
    c9_b_V1[c9_i23] = c9_V1[c9_i23];
  }

  c9_B = c9_norm(chartInstance, c9_b_V1);
  c9_y = c9_B;
  c9_b_y = c9_y;
  for (c9_i24 = 0; c9_i24 < 3; c9_i24++) {
    c9_r1[c9_i24] = c9_b_A[c9_i24] / c9_b_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 26);
  for (c9_i25 = 0; c9_i25 < 3; c9_i25++) {
    c9_c_V1[c9_i25] = c9_V1[c9_i25];
  }

  for (c9_i26 = 0; c9_i26 < 3; c9_i26++) {
    c9_b_V2[c9_i26] = c9_V2[c9_i26];
  }

  c9_cross(chartInstance, c9_c_V1, c9_b_V2, c9_dv2);
  for (c9_i27 = 0; c9_i27 < 3; c9_i27++) {
    c9_r2[c9_i27] = c9_dv2[c9_i27];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 27);
  for (c9_i28 = 0; c9_i28 < 3; c9_i28++) {
    c9_b_A[c9_i28] = c9_r2[c9_i28];
  }

  for (c9_i29 = 0; c9_i29 < 3; c9_i29++) {
    c9_b_r2[c9_i29] = c9_r2[c9_i29];
  }

  c9_b_B = c9_norm(chartInstance, c9_b_r2);
  c9_c_y = c9_b_B;
  c9_d_y = c9_c_y;
  for (c9_i30 = 0; c9_i30 < 3; c9_i30++) {
    c9_r2[c9_i30] = c9_b_A[c9_i30] / c9_d_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 28);
  for (c9_i31 = 0; c9_i31 < 3; c9_i31++) {
    c9_b_r1[c9_i31] = c9_r1[c9_i31];
  }

  for (c9_i32 = 0; c9_i32 < 3; c9_i32++) {
    c9_c_r2[c9_i32] = c9_r2[c9_i32];
  }

  c9_cross(chartInstance, c9_b_r1, c9_c_r2, c9_dv3);
  for (c9_i33 = 0; c9_i33 < 3; c9_i33++) {
    c9_r3[c9_i33] = c9_dv3[c9_i33];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 30);
  for (c9_i34 = 0; c9_i34 < 3; c9_i34++) {
    c9_Mref[c9_i34] = c9_r1[c9_i34];
  }

  for (c9_i35 = 0; c9_i35 < 3; c9_i35++) {
    c9_Mref[c9_i35 + 3] = c9_r2[c9_i35];
  }

  for (c9_i36 = 0; c9_i36 < 3; c9_i36++) {
    c9_Mref[c9_i36 + 6] = c9_r3[c9_i36];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 32);
  for (c9_i37 = 0; c9_i37 < 3; c9_i37++) {
    c9_b_A[c9_i37] = c9_W1[c9_i37];
  }

  for (c9_i38 = 0; c9_i38 < 3; c9_i38++) {
    c9_b_W1[c9_i38] = c9_W1[c9_i38];
  }

  c9_c_B = c9_norm(chartInstance, c9_b_W1);
  c9_e_y = c9_c_B;
  c9_f_y = c9_e_y;
  for (c9_i39 = 0; c9_i39 < 3; c9_i39++) {
    c9_s1[c9_i39] = c9_b_A[c9_i39] / c9_f_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 33);
  for (c9_i40 = 0; c9_i40 < 3; c9_i40++) {
    c9_c_W1[c9_i40] = c9_W1[c9_i40];
  }

  for (c9_i41 = 0; c9_i41 < 3; c9_i41++) {
    c9_b_W2[c9_i41] = c9_W2[c9_i41];
  }

  c9_cross(chartInstance, c9_c_W1, c9_b_W2, c9_dv4);
  for (c9_i42 = 0; c9_i42 < 3; c9_i42++) {
    c9_s2[c9_i42] = c9_dv4[c9_i42];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 34);
  for (c9_i43 = 0; c9_i43 < 3; c9_i43++) {
    c9_b_A[c9_i43] = c9_s2[c9_i43];
  }

  for (c9_i44 = 0; c9_i44 < 3; c9_i44++) {
    c9_b_s2[c9_i44] = c9_s2[c9_i44];
  }

  c9_d_B = c9_norm(chartInstance, c9_b_s2);
  c9_g_y = c9_d_B;
  c9_h_y = c9_g_y;
  for (c9_i45 = 0; c9_i45 < 3; c9_i45++) {
    c9_s2[c9_i45] = c9_b_A[c9_i45] / c9_h_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 35);
  for (c9_i46 = 0; c9_i46 < 3; c9_i46++) {
    c9_b_s1[c9_i46] = c9_s1[c9_i46];
  }

  for (c9_i47 = 0; c9_i47 < 3; c9_i47++) {
    c9_c_s2[c9_i47] = c9_s2[c9_i47];
  }

  c9_cross(chartInstance, c9_b_s1, c9_c_s2, c9_dv5);
  for (c9_i48 = 0; c9_i48 < 3; c9_i48++) {
    c9_s3[c9_i48] = c9_dv5[c9_i48];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 37);
  for (c9_i49 = 0; c9_i49 < 3; c9_i49++) {
    c9_Mobs[c9_i49] = c9_s1[c9_i49];
  }

  for (c9_i50 = 0; c9_i50 < 3; c9_i50++) {
    c9_Mobs[c9_i50 + 3] = c9_s2[c9_i50];
  }

  for (c9_i51 = 0; c9_i51 < 3; c9_i51++) {
    c9_Mobs[c9_i51 + 6] = c9_s3[c9_i51];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 39);
  for (c9_i52 = 0; c9_i52 < 9; c9_i52++) {
    c9_a[c9_i52] = c9_Mobs[c9_i52];
  }

  c9_i53 = 0;
  for (c9_i54 = 0; c9_i54 < 3; c9_i54++) {
    c9_i55 = 0;
    for (c9_i56 = 0; c9_i56 < 3; c9_i56++) {
      c9_b[c9_i56 + c9_i53] = c9_Mref[c9_i55 + c9_i54];
      c9_i55 += 3;
    }

    c9_i53 += 3;
  }

  c9_eml_scalar_eg(chartInstance);
  c9_eml_scalar_eg(chartInstance);
  for (c9_i57 = 0; c9_i57 < 9; c9_i57++) {
    c9_A[c9_i57] = 0.0;
  }

  for (c9_i58 = 0; c9_i58 < 9; c9_i58++) {
    c9_A[c9_i58] = 0.0;
  }

  for (c9_i59 = 0; c9_i59 < 9; c9_i59++) {
    c9_C[c9_i59] = c9_A[c9_i59];
  }

  for (c9_i60 = 0; c9_i60 < 9; c9_i60++) {
    c9_A[c9_i60] = c9_C[c9_i60];
  }

  for (c9_i61 = 0; c9_i61 < 9; c9_i61++) {
    c9_C[c9_i61] = c9_A[c9_i61];
  }

  for (c9_i62 = 0; c9_i62 < 9; c9_i62++) {
    c9_A[c9_i62] = c9_C[c9_i62];
  }

  for (c9_i63 = 0; c9_i63 < 3; c9_i63++) {
    c9_i64 = 0;
    for (c9_i65 = 0; c9_i65 < 3; c9_i65++) {
      c9_A[c9_i64 + c9_i63] = 0.0;
      c9_i66 = 0;
      for (c9_i67 = 0; c9_i67 < 3; c9_i67++) {
        c9_A[c9_i64 + c9_i63] += c9_a[c9_i66 + c9_i63] * c9_b[c9_i67 + c9_i64];
        c9_i66 += 3;
      }

      c9_i64 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 42);
  c9_b_a = c9_mpower(chartInstance, c9_SigTot1);
  for (c9_i68 = 0; c9_i68 < 9; c9_i68++) {
    c9_a[c9_i68] = c9_b_a * c9_b_b[c9_i68];
  }

  for (c9_i69 = 0; c9_i69 < 3; c9_i69++) {
    c9_d_W1[c9_i69] = c9_W1[c9_i69];
  }

  for (c9_i70 = 0; c9_i70 < 3; c9_i70++) {
    c9_c_W2[c9_i70] = c9_W2[c9_i70];
  }

  c9_cross(chartInstance, c9_d_W1, c9_c_W2, c9_b_A);
  for (c9_i71 = 0; c9_i71 < 3; c9_i71++) {
    c9_c_A[c9_i71] = c9_b_A[c9_i71];
  }

  c9_e_B = c9_norm(chartInstance, c9_c_A);
  c9_i_y = c9_e_B;
  c9_j_y = c9_i_y;
  c9_k_y = 1.0 / c9_j_y;
  for (c9_i72 = 0; c9_i72 < 3; c9_i72++) {
    c9_c_a[c9_i72] = c9_W1[c9_i72];
  }

  for (c9_i73 = 0; c9_i73 < 3; c9_i73++) {
    c9_b_A[c9_i73] = c9_W2[c9_i73];
  }

  c9_c_eml_scalar_eg(chartInstance);
  c9_c_eml_scalar_eg(chartInstance);
  c9_l_y = 0.0;
  for (c9_k = 1; c9_k < 4; c9_k++) {
    c9_b_k = c9_k;
    c9_l_y += c9_c_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
      ("", (real_T)c9_b_k), 1, 3, 1, 0) - 1] *
      c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c9_b_k), 1, 3, 1, 0) - 1];
  }

  c9_d_a = c9_mpower(chartInstance, c9_SigTot1);
  c9_c_b = c9_l_y;
  c9_m_y = c9_d_a * c9_c_b;
  for (c9_i74 = 0; c9_i74 < 3; c9_i74++) {
    c9_b_A[c9_i74] = c9_W1[c9_i74];
  }

  for (c9_i75 = 0; c9_i75 < 3; c9_i75++) {
    c9_c_a[c9_i75] = c9_W2[c9_i75];
  }

  for (c9_i76 = 0; c9_i76 < 3; c9_i76++) {
    c9_i77 = 0;
    for (c9_i78 = 0; c9_i78 < 3; c9_i78++) {
      c9_b[c9_i77 + c9_i76] = c9_b_A[c9_i76] * c9_c_a[c9_i78];
      c9_i77 += 3;
    }
  }

  for (c9_i79 = 0; c9_i79 < 3; c9_i79++) {
    c9_b_A[c9_i79] = c9_W2[c9_i79];
  }

  for (c9_i80 = 0; c9_i80 < 3; c9_i80++) {
    c9_c_a[c9_i80] = c9_W1[c9_i80];
  }

  for (c9_i81 = 0; c9_i81 < 3; c9_i81++) {
    c9_i82 = 0;
    for (c9_i83 = 0; c9_i83 < 3; c9_i83++) {
      c9_C[c9_i82 + c9_i81] = c9_b_A[c9_i81] * c9_c_a[c9_i83];
      c9_i82 += 3;
    }
  }

  c9_e_a = c9_m_y;
  for (c9_i84 = 0; c9_i84 < 9; c9_i84++) {
    c9_b[c9_i84] += c9_C[c9_i84];
  }

  for (c9_i85 = 0; c9_i85 < 9; c9_i85++) {
    c9_b[c9_i85] *= c9_e_a;
  }

  c9_f_a = c9_mpower(chartInstance, c9_SigTot2) - c9_mpower(chartInstance,
    c9_SigTot1);
  for (c9_i86 = 0; c9_i86 < 3; c9_i86++) {
    c9_b_A[c9_i86] = c9_W1[c9_i86];
  }

  for (c9_i87 = 0; c9_i87 < 3; c9_i87++) {
    c9_b_A[c9_i87] *= c9_f_a;
  }

  for (c9_i88 = 0; c9_i88 < 3; c9_i88++) {
    c9_c_a[c9_i88] = c9_W1[c9_i88];
  }

  for (c9_i89 = 0; c9_i89 < 3; c9_i89++) {
    c9_i90 = 0;
    for (c9_i91 = 0; c9_i91 < 3; c9_i91++) {
      c9_C[c9_i90 + c9_i89] = c9_b_A[c9_i89] * c9_c_a[c9_i91];
      c9_i90 += 3;
    }
  }

  c9_g_a = c9_mpower(chartInstance, c9_k_y);
  for (c9_i92 = 0; c9_i92 < 9; c9_i92++) {
    c9_b[c9_i92] += c9_C[c9_i92];
  }

  for (c9_i93 = 0; c9_i93 < 9; c9_i93++) {
    c9_b[c9_i93] *= c9_g_a;
  }

  for (c9_i94 = 0; c9_i94 < 9; c9_i94++) {
    c9_R[c9_i94] = c9_a[c9_i94] + c9_b[c9_i94];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, -42);
  _SFD_SYMBOL_SCOPE_POP();
  for (c9_i95 = 0; c9_i95 < 9; c9_i95++) {
    (*c9_d_A)[c9_i95] = c9_A[c9_i95];
  }

  for (c9_i96 = 0; c9_i96 < 9; c9_i96++) {
    (*c9_b_R)[c9_i96] = c9_R[c9_i96];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
}

static void initSimStructsc9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void registerMessagesc9_modelo_FK_simul_coleta_dados
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber)
{
}

static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i97;
  int32_T c9_i98;
  int32_T c9_i99;
  real_T c9_b_inData[9];
  int32_T c9_i100;
  int32_T c9_i101;
  int32_T c9_i102;
  real_T c9_u[9];
  const mxArray *c9_y = NULL;
  SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_i97 = 0;
  for (c9_i98 = 0; c9_i98 < 3; c9_i98++) {
    for (c9_i99 = 0; c9_i99 < 3; c9_i99++) {
      c9_b_inData[c9_i99 + c9_i97] = (*(real_T (*)[9])c9_inData)[c9_i99 + c9_i97];
    }

    c9_i97 += 3;
  }

  c9_i100 = 0;
  for (c9_i101 = 0; c9_i101 < 3; c9_i101++) {
    for (c9_i102 = 0; c9_i102 < 3; c9_i102++) {
      c9_u[c9_i102 + c9_i100] = c9_b_inData[c9_i102 + c9_i100];
    }

    c9_i100 += 3;
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static void c9_emlrt_marshallIn(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *
  chartInstance, const mxArray *c9_R, const char_T *c9_identifier, real_T c9_y[9])
{
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_R), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_R);
}

static void c9_b_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_u, const emlrtMsgIdentifier *c9_parentId, real_T c9_y[9])
{
  real_T c9_dv6[9];
  int32_T c9_i103;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv6, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c9_i103 = 0; c9_i103 < 9; c9_i103++) {
    c9_y[c9_i103] = c9_dv6[c9_i103];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_R;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[9];
  int32_T c9_i104;
  int32_T c9_i105;
  int32_T c9_i106;
  SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c9_R = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_R), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_R);
  c9_i104 = 0;
  for (c9_i105 = 0; c9_i105 < 3; c9_i105++) {
    for (c9_i106 = 0; c9_i106 < 3; c9_i106++) {
      (*(real_T (*)[9])c9_outData)[c9_i106 + c9_i104] = c9_y[c9_i106 + c9_i104];
    }

    c9_i104 += 3;
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i107;
  real_T c9_b_inData[3];
  int32_T c9_i108;
  real_T c9_u[3];
  const mxArray *c9_y = NULL;
  SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i107 = 0; c9_i107 < 3; c9_i107++) {
    c9_b_inData[c9_i107] = (*(real_T (*)[3])c9_inData)[c9_i107];
  }

  for (c9_i108 = 0; c9_i108 < 3; c9_i108++) {
    c9_u[c9_i108] = c9_b_inData[c9_i108];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  real_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(real_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static real_T c9_c_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  real_T c9_y;
  real_T c9_d0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_d0, 1, 0, 0U, 0, 0U, 0);
  c9_y = c9_d0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_nargout;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y;
  SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c9_nargout = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_nargout), &c9_thisId);
  sf_mex_destroy(&c9_nargout);
  *(real_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static void c9_d_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_u, const emlrtMsgIdentifier *c9_parentId, real_T c9_y[3])
{
  real_T c9_dv7[3];
  int32_T c9_i109;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv7, 1, 0, 0U, 1, 0U, 1, 3);
  for (c9_i109 = 0; c9_i109 < 3; c9_i109++) {
    c9_y[c9_i109] = c9_dv7[c9_i109];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_s3;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[3];
  int32_T c9_i110;
  SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c9_s3 = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_s3), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_s3);
  for (c9_i110 = 0; c9_i110 < 3; c9_i110++) {
    (*(real_T (*)[3])c9_outData)[c9_i110] = c9_y[c9_i110];
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

const mxArray
  *sf_c9_modelo_FK_simul_coleta_dados_get_eml_resolved_functions_info(void)
{
  const mxArray *c9_nameCaptureInfo;
  c9_ResolvedFunctionInfo c9_info[71];
  c9_ResolvedFunctionInfo (*c9_b_info)[71];
  const mxArray *c9_m0 = NULL;
  int32_T c9_i111;
  c9_ResolvedFunctionInfo *c9_r0;
  c9_nameCaptureInfo = NULL;
  c9_nameCaptureInfo = NULL;
  c9_info_helper(c9_info);
  c9_b_info = (c9_ResolvedFunctionInfo (*)[71])c9_info;
  (*c9_b_info)[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  (*c9_b_info)[64].name = "eml_refblas_xdotx";
  (*c9_b_info)[64].dominantType = "char";
  (*c9_b_info)[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c9_b_info)[64].fileTimeLo = 1299091174U;
  (*c9_b_info)[64].fileTimeHi = 0U;
  (*c9_b_info)[64].mFileTimeLo = 0U;
  (*c9_b_info)[64].mFileTimeHi = 0U;
  (*c9_b_info)[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c9_b_info)[65].name = "eml_scalar_eg";
  (*c9_b_info)[65].dominantType = "double";
  (*c9_b_info)[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c9_b_info)[65].fileTimeLo = 1286836796U;
  (*c9_b_info)[65].fileTimeHi = 0U;
  (*c9_b_info)[65].mFileTimeLo = 0U;
  (*c9_b_info)[65].mFileTimeHi = 0U;
  (*c9_b_info)[66].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c9_b_info)[66].name = "eml_index_class";
  (*c9_b_info)[66].dominantType = "";
  (*c9_b_info)[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*c9_b_info)[66].fileTimeLo = 1323181378U;
  (*c9_b_info)[66].fileTimeHi = 0U;
  (*c9_b_info)[66].mFileTimeLo = 0U;
  (*c9_b_info)[66].mFileTimeHi = 0U;
  (*c9_b_info)[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c9_b_info)[67].name = "eml_index_minus";
  (*c9_b_info)[67].dominantType = "double";
  (*c9_b_info)[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  (*c9_b_info)[67].fileTimeLo = 1286836778U;
  (*c9_b_info)[67].fileTimeHi = 0U;
  (*c9_b_info)[67].mFileTimeLo = 0U;
  (*c9_b_info)[67].mFileTimeHi = 0U;
  (*c9_b_info)[68].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c9_b_info)[68].name = "eml_index_times";
  (*c9_b_info)[68].dominantType = "coder.internal.indexInt";
  (*c9_b_info)[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  (*c9_b_info)[68].fileTimeLo = 1286836780U;
  (*c9_b_info)[68].fileTimeHi = 0U;
  (*c9_b_info)[68].mFileTimeLo = 0U;
  (*c9_b_info)[68].mFileTimeHi = 0U;
  (*c9_b_info)[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c9_b_info)[69].name = "eml_index_plus";
  (*c9_b_info)[69].dominantType = "coder.internal.indexInt";
  (*c9_b_info)[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  (*c9_b_info)[69].fileTimeLo = 1286836778U;
  (*c9_b_info)[69].fileTimeHi = 0U;
  (*c9_b_info)[69].mFileTimeLo = 0U;
  (*c9_b_info)[69].mFileTimeHi = 0U;
  (*c9_b_info)[70].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c9_b_info)[70].name = "eml_int_forloop_overflow_check";
  (*c9_b_info)[70].dominantType = "";
  (*c9_b_info)[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  (*c9_b_info)[70].fileTimeLo = 1346528340U;
  (*c9_b_info)[70].fileTimeHi = 0U;
  (*c9_b_info)[70].mFileTimeLo = 0U;
  (*c9_b_info)[70].mFileTimeHi = 0U;
  sf_mex_assign(&c9_m0, sf_mex_createstruct("nameCaptureInfo", 1, 71), FALSE);
  for (c9_i111 = 0; c9_i111 < 71; c9_i111++) {
    c9_r0 = &c9_info[c9_i111];
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->context)), "context", "nameCaptureInfo",
                    c9_i111);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c9_r0->name)), "name", "nameCaptureInfo", c9_i111);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c9_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c9_i111);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->resolved)), "resolved", "nameCaptureInfo",
                    c9_i111);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c9_i111);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c9_i111);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c9_i111);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c9_i111);
  }

  sf_mex_assign(&c9_nameCaptureInfo, c9_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c9_nameCaptureInfo);
  return c9_nameCaptureInfo;
}

static void c9_info_helper(c9_ResolvedFunctionInfo c9_info[71])
{
  c9_info[0].context = "";
  c9_info[0].name = "norm";
  c9_info[0].dominantType = "double";
  c9_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c9_info[0].fileTimeLo = 1336540094U;
  c9_info[0].fileTimeHi = 0U;
  c9_info[0].mFileTimeLo = 0U;
  c9_info[0].mFileTimeHi = 0U;
  c9_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c9_info[1].name = "eml_index_class";
  c9_info[1].dominantType = "";
  c9_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[1].fileTimeLo = 1323181378U;
  c9_info[1].fileTimeHi = 0U;
  c9_info[1].mFileTimeLo = 0U;
  c9_info[1].mFileTimeHi = 0U;
  c9_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c9_info[2].name = "eml_xnrm2";
  c9_info[2].dominantType = "double";
  c9_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c9_info[2].fileTimeLo = 1299091176U;
  c9_info[2].fileTimeHi = 0U;
  c9_info[2].mFileTimeLo = 0U;
  c9_info[2].mFileTimeHi = 0U;
  c9_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c9_info[3].name = "eml_blas_inline";
  c9_info[3].dominantType = "";
  c9_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c9_info[3].fileTimeLo = 1299091168U;
  c9_info[3].fileTimeHi = 0U;
  c9_info[3].mFileTimeLo = 0U;
  c9_info[3].mFileTimeHi = 0U;
  c9_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c9_info[4].name = "eml_index_class";
  c9_info[4].dominantType = "";
  c9_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[4].fileTimeLo = 1323181378U;
  c9_info[4].fileTimeHi = 0U;
  c9_info[4].mFileTimeLo = 0U;
  c9_info[4].mFileTimeHi = 0U;
  c9_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c9_info[5].name = "eml_refblas_xnrm2";
  c9_info[5].dominantType = "double";
  c9_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[5].fileTimeLo = 1299091184U;
  c9_info[5].fileTimeHi = 0U;
  c9_info[5].mFileTimeLo = 0U;
  c9_info[5].mFileTimeHi = 0U;
  c9_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[6].name = "realmin";
  c9_info[6].dominantType = "char";
  c9_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c9_info[6].fileTimeLo = 1307669242U;
  c9_info[6].fileTimeHi = 0U;
  c9_info[6].mFileTimeLo = 0U;
  c9_info[6].mFileTimeHi = 0U;
  c9_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c9_info[7].name = "eml_realmin";
  c9_info[7].dominantType = "char";
  c9_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c9_info[7].fileTimeLo = 1307669244U;
  c9_info[7].fileTimeHi = 0U;
  c9_info[7].mFileTimeLo = 0U;
  c9_info[7].mFileTimeHi = 0U;
  c9_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c9_info[8].name = "eml_float_model";
  c9_info[8].dominantType = "char";
  c9_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c9_info[8].fileTimeLo = 1326738796U;
  c9_info[8].fileTimeHi = 0U;
  c9_info[8].mFileTimeLo = 0U;
  c9_info[8].mFileTimeHi = 0U;
  c9_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[9].name = "eml_index_class";
  c9_info[9].dominantType = "";
  c9_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[9].fileTimeLo = 1323181378U;
  c9_info[9].fileTimeHi = 0U;
  c9_info[9].mFileTimeLo = 0U;
  c9_info[9].mFileTimeHi = 0U;
  c9_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[10].name = "eml_index_minus";
  c9_info[10].dominantType = "double";
  c9_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c9_info[10].fileTimeLo = 1286836778U;
  c9_info[10].fileTimeHi = 0U;
  c9_info[10].mFileTimeLo = 0U;
  c9_info[10].mFileTimeHi = 0U;
  c9_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c9_info[11].name = "eml_index_class";
  c9_info[11].dominantType = "";
  c9_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[11].fileTimeLo = 1323181378U;
  c9_info[11].fileTimeHi = 0U;
  c9_info[11].mFileTimeLo = 0U;
  c9_info[11].mFileTimeHi = 0U;
  c9_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[12].name = "eml_index_times";
  c9_info[12].dominantType = "coder.internal.indexInt";
  c9_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c9_info[12].fileTimeLo = 1286836780U;
  c9_info[12].fileTimeHi = 0U;
  c9_info[12].mFileTimeLo = 0U;
  c9_info[12].mFileTimeHi = 0U;
  c9_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c9_info[13].name = "eml_index_class";
  c9_info[13].dominantType = "";
  c9_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[13].fileTimeLo = 1323181378U;
  c9_info[13].fileTimeHi = 0U;
  c9_info[13].mFileTimeLo = 0U;
  c9_info[13].mFileTimeHi = 0U;
  c9_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[14].name = "eml_index_plus";
  c9_info[14].dominantType = "coder.internal.indexInt";
  c9_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c9_info[14].fileTimeLo = 1286836778U;
  c9_info[14].fileTimeHi = 0U;
  c9_info[14].mFileTimeLo = 0U;
  c9_info[14].mFileTimeHi = 0U;
  c9_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c9_info[15].name = "eml_index_class";
  c9_info[15].dominantType = "";
  c9_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[15].fileTimeLo = 1323181378U;
  c9_info[15].fileTimeHi = 0U;
  c9_info[15].mFileTimeLo = 0U;
  c9_info[15].mFileTimeHi = 0U;
  c9_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[16].name = "eml_int_forloop_overflow_check";
  c9_info[16].dominantType = "";
  c9_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c9_info[16].fileTimeLo = 1346528340U;
  c9_info[16].fileTimeHi = 0U;
  c9_info[16].mFileTimeLo = 0U;
  c9_info[16].mFileTimeHi = 0U;
  c9_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c9_info[17].name = "intmax";
  c9_info[17].dominantType = "char";
  c9_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c9_info[17].fileTimeLo = 1311273316U;
  c9_info[17].fileTimeHi = 0U;
  c9_info[17].mFileTimeLo = 0U;
  c9_info[17].mFileTimeHi = 0U;
  c9_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[18].name = "abs";
  c9_info[18].dominantType = "double";
  c9_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c9_info[18].fileTimeLo = 1343848366U;
  c9_info[18].fileTimeHi = 0U;
  c9_info[18].mFileTimeLo = 0U;
  c9_info[18].mFileTimeHi = 0U;
  c9_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c9_info[19].name = "eml_scalar_abs";
  c9_info[19].dominantType = "double";
  c9_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c9_info[19].fileTimeLo = 1286836712U;
  c9_info[19].fileTimeHi = 0U;
  c9_info[19].mFileTimeLo = 0U;
  c9_info[19].mFileTimeHi = 0U;
  c9_info[20].context = "";
  c9_info[20].name = "mrdivide";
  c9_info[20].dominantType = "double";
  c9_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c9_info[20].fileTimeLo = 1357962348U;
  c9_info[20].fileTimeHi = 0U;
  c9_info[20].mFileTimeLo = 1319744366U;
  c9_info[20].mFileTimeHi = 0U;
  c9_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c9_info[21].name = "rdivide";
  c9_info[21].dominantType = "double";
  c9_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c9_info[21].fileTimeLo = 1346528388U;
  c9_info[21].fileTimeHi = 0U;
  c9_info[21].mFileTimeLo = 0U;
  c9_info[21].mFileTimeHi = 0U;
  c9_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c9_info[22].name = "eml_scalexp_compatible";
  c9_info[22].dominantType = "double";
  c9_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c9_info[22].fileTimeLo = 1286836796U;
  c9_info[22].fileTimeHi = 0U;
  c9_info[22].mFileTimeLo = 0U;
  c9_info[22].mFileTimeHi = 0U;
  c9_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c9_info[23].name = "eml_div";
  c9_info[23].dominantType = "double";
  c9_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c9_info[23].fileTimeLo = 1313365810U;
  c9_info[23].fileTimeHi = 0U;
  c9_info[23].mFileTimeLo = 0U;
  c9_info[23].mFileTimeHi = 0U;
  c9_info[24].context = "";
  c9_info[24].name = "cross";
  c9_info[24].dominantType = "double";
  c9_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c9_info[24].fileTimeLo = 1286836842U;
  c9_info[24].fileTimeHi = 0U;
  c9_info[24].mFileTimeLo = 0U;
  c9_info[24].mFileTimeHi = 0U;
  c9_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c9_info[25].name = "mtimes";
  c9_info[25].dominantType = "double";
  c9_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[25].fileTimeLo = 1289530492U;
  c9_info[25].fileTimeHi = 0U;
  c9_info[25].mFileTimeLo = 0U;
  c9_info[25].mFileTimeHi = 0U;
  c9_info[26].context = "";
  c9_info[26].name = "mtimes";
  c9_info[26].dominantType = "double";
  c9_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[26].fileTimeLo = 1289530492U;
  c9_info[26].fileTimeHi = 0U;
  c9_info[26].mFileTimeLo = 0U;
  c9_info[26].mFileTimeHi = 0U;
  c9_info[27].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[27].name = "eml_index_class";
  c9_info[27].dominantType = "";
  c9_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[27].fileTimeLo = 1323181378U;
  c9_info[27].fileTimeHi = 0U;
  c9_info[27].mFileTimeLo = 0U;
  c9_info[27].mFileTimeHi = 0U;
  c9_info[28].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[28].name = "eml_scalar_eg";
  c9_info[28].dominantType = "double";
  c9_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[28].fileTimeLo = 1286836796U;
  c9_info[28].fileTimeHi = 0U;
  c9_info[28].mFileTimeLo = 0U;
  c9_info[28].mFileTimeHi = 0U;
  c9_info[29].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[29].name = "eml_xgemm";
  c9_info[29].dominantType = "char";
  c9_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c9_info[29].fileTimeLo = 1299091172U;
  c9_info[29].fileTimeHi = 0U;
  c9_info[29].mFileTimeLo = 0U;
  c9_info[29].mFileTimeHi = 0U;
  c9_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c9_info[30].name = "eml_blas_inline";
  c9_info[30].dominantType = "";
  c9_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c9_info[30].fileTimeLo = 1299091168U;
  c9_info[30].fileTimeHi = 0U;
  c9_info[30].mFileTimeLo = 0U;
  c9_info[30].mFileTimeHi = 0U;
  c9_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c9_info[31].name = "mtimes";
  c9_info[31].dominantType = "double";
  c9_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[31].fileTimeLo = 1289530492U;
  c9_info[31].fileTimeHi = 0U;
  c9_info[31].mFileTimeLo = 0U;
  c9_info[31].mFileTimeHi = 0U;
  c9_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c9_info[32].name = "eml_index_class";
  c9_info[32].dominantType = "";
  c9_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[32].fileTimeLo = 1323181378U;
  c9_info[32].fileTimeHi = 0U;
  c9_info[32].mFileTimeLo = 0U;
  c9_info[32].mFileTimeHi = 0U;
  c9_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c9_info[33].name = "eml_scalar_eg";
  c9_info[33].dominantType = "double";
  c9_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[33].fileTimeLo = 1286836796U;
  c9_info[33].fileTimeHi = 0U;
  c9_info[33].mFileTimeLo = 0U;
  c9_info[33].mFileTimeHi = 0U;
  c9_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c9_info[34].name = "eml_refblas_xgemm";
  c9_info[34].dominantType = "char";
  c9_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c9_info[34].fileTimeLo = 1299091174U;
  c9_info[34].fileTimeHi = 0U;
  c9_info[34].mFileTimeLo = 0U;
  c9_info[34].mFileTimeHi = 0U;
  c9_info[35].context = "";
  c9_info[35].name = "mpower";
  c9_info[35].dominantType = "double";
  c9_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c9_info[35].fileTimeLo = 1286836842U;
  c9_info[35].fileTimeHi = 0U;
  c9_info[35].mFileTimeLo = 0U;
  c9_info[35].mFileTimeHi = 0U;
  c9_info[36].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c9_info[36].name = "power";
  c9_info[36].dominantType = "double";
  c9_info[36].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c9_info[36].fileTimeLo = 1348209930U;
  c9_info[36].fileTimeHi = 0U;
  c9_info[36].mFileTimeLo = 0U;
  c9_info[36].mFileTimeHi = 0U;
  c9_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c9_info[37].name = "eml_scalar_eg";
  c9_info[37].dominantType = "double";
  c9_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[37].fileTimeLo = 1286836796U;
  c9_info[37].fileTimeHi = 0U;
  c9_info[37].mFileTimeLo = 0U;
  c9_info[37].mFileTimeHi = 0U;
  c9_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c9_info[38].name = "eml_scalexp_alloc";
  c9_info[38].dominantType = "double";
  c9_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c9_info[38].fileTimeLo = 1352435660U;
  c9_info[38].fileTimeHi = 0U;
  c9_info[38].mFileTimeLo = 0U;
  c9_info[38].mFileTimeHi = 0U;
  c9_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c9_info[39].name = "floor";
  c9_info[39].dominantType = "double";
  c9_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c9_info[39].fileTimeLo = 1343848380U;
  c9_info[39].fileTimeHi = 0U;
  c9_info[39].mFileTimeLo = 0U;
  c9_info[39].mFileTimeHi = 0U;
  c9_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c9_info[40].name = "eml_scalar_floor";
  c9_info[40].dominantType = "double";
  c9_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c9_info[40].fileTimeLo = 1286836726U;
  c9_info[40].fileTimeHi = 0U;
  c9_info[40].mFileTimeLo = 0U;
  c9_info[40].mFileTimeHi = 0U;
  c9_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c9_info[41].name = "eml_scalar_eg";
  c9_info[41].dominantType = "double";
  c9_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[41].fileTimeLo = 1286836796U;
  c9_info[41].fileTimeHi = 0U;
  c9_info[41].mFileTimeLo = 0U;
  c9_info[41].mFileTimeHi = 0U;
  c9_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c9_info[42].name = "mtimes";
  c9_info[42].dominantType = "double";
  c9_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[42].fileTimeLo = 1289530492U;
  c9_info[42].fileTimeHi = 0U;
  c9_info[42].mFileTimeLo = 0U;
  c9_info[42].mFileTimeHi = 0U;
  c9_info[43].context = "";
  c9_info[43].name = "eye";
  c9_info[43].dominantType = "double";
  c9_info[43].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m";
  c9_info[43].fileTimeLo = 1286836688U;
  c9_info[43].fileTimeHi = 0U;
  c9_info[43].mFileTimeLo = 0U;
  c9_info[43].mFileTimeHi = 0U;
  c9_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c9_info[44].name = "eml_assert_valid_size_arg";
  c9_info[44].dominantType = "double";
  c9_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c9_info[44].fileTimeLo = 1286836694U;
  c9_info[44].fileTimeHi = 0U;
  c9_info[44].mFileTimeLo = 0U;
  c9_info[44].mFileTimeHi = 0U;
  c9_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c9_info[45].name = "isinf";
  c9_info[45].dominantType = "double";
  c9_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c9_info[45].fileTimeLo = 1286836760U;
  c9_info[45].fileTimeHi = 0U;
  c9_info[45].mFileTimeLo = 0U;
  c9_info[45].mFileTimeHi = 0U;
  c9_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c9_info[46].name = "mtimes";
  c9_info[46].dominantType = "double";
  c9_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[46].fileTimeLo = 1289530492U;
  c9_info[46].fileTimeHi = 0U;
  c9_info[46].mFileTimeLo = 0U;
  c9_info[46].mFileTimeHi = 0U;
  c9_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c9_info[47].name = "eml_index_class";
  c9_info[47].dominantType = "";
  c9_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[47].fileTimeLo = 1323181378U;
  c9_info[47].fileTimeHi = 0U;
  c9_info[47].mFileTimeLo = 0U;
  c9_info[47].mFileTimeHi = 0U;
  c9_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c9_info[48].name = "intmax";
  c9_info[48].dominantType = "char";
  c9_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c9_info[48].fileTimeLo = 1311273316U;
  c9_info[48].fileTimeHi = 0U;
  c9_info[48].mFileTimeLo = 0U;
  c9_info[48].mFileTimeHi = 0U;
  c9_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c9_info[49].name = "eml_is_float_class";
  c9_info[49].dominantType = "char";
  c9_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c9_info[49].fileTimeLo = 1286836782U;
  c9_info[49].fileTimeHi = 0U;
  c9_info[49].mFileTimeLo = 0U;
  c9_info[49].mFileTimeHi = 0U;
  c9_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c9_info[50].name = "min";
  c9_info[50].dominantType = "double";
  c9_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c9_info[50].fileTimeLo = 1311273318U;
  c9_info[50].fileTimeHi = 0U;
  c9_info[50].mFileTimeLo = 0U;
  c9_info[50].mFileTimeHi = 0U;
  c9_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c9_info[51].name = "eml_min_or_max";
  c9_info[51].dominantType = "char";
  c9_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c9_info[51].fileTimeLo = 1334089490U;
  c9_info[51].fileTimeHi = 0U;
  c9_info[51].mFileTimeLo = 0U;
  c9_info[51].mFileTimeHi = 0U;
  c9_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c9_info[52].name = "eml_scalar_eg";
  c9_info[52].dominantType = "double";
  c9_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[52].fileTimeLo = 1286836796U;
  c9_info[52].fileTimeHi = 0U;
  c9_info[52].mFileTimeLo = 0U;
  c9_info[52].mFileTimeHi = 0U;
  c9_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c9_info[53].name = "eml_scalexp_alloc";
  c9_info[53].dominantType = "double";
  c9_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c9_info[53].fileTimeLo = 1352435660U;
  c9_info[53].fileTimeHi = 0U;
  c9_info[53].mFileTimeLo = 0U;
  c9_info[53].mFileTimeHi = 0U;
  c9_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c9_info[54].name = "eml_index_class";
  c9_info[54].dominantType = "";
  c9_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[54].fileTimeLo = 1323181378U;
  c9_info[54].fileTimeHi = 0U;
  c9_info[54].mFileTimeLo = 0U;
  c9_info[54].mFileTimeHi = 0U;
  c9_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c9_info[55].name = "eml_scalar_eg";
  c9_info[55].dominantType = "double";
  c9_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[55].fileTimeLo = 1286836796U;
  c9_info[55].fileTimeHi = 0U;
  c9_info[55].mFileTimeLo = 0U;
  c9_info[55].mFileTimeHi = 0U;
  c9_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c9_info[56].name = "eml_index_class";
  c9_info[56].dominantType = "";
  c9_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[56].fileTimeLo = 1323181378U;
  c9_info[56].fileTimeHi = 0U;
  c9_info[56].mFileTimeLo = 0U;
  c9_info[56].mFileTimeHi = 0U;
  c9_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c9_info[57].name = "eml_int_forloop_overflow_check";
  c9_info[57].dominantType = "";
  c9_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c9_info[57].fileTimeLo = 1346528340U;
  c9_info[57].fileTimeHi = 0U;
  c9_info[57].mFileTimeLo = 0U;
  c9_info[57].mFileTimeHi = 0U;
  c9_info[58].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[58].name = "eml_xdotu";
  c9_info[58].dominantType = "double";
  c9_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c9_info[58].fileTimeLo = 1299091172U;
  c9_info[58].fileTimeHi = 0U;
  c9_info[58].mFileTimeLo = 0U;
  c9_info[58].mFileTimeHi = 0U;
  c9_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c9_info[59].name = "eml_blas_inline";
  c9_info[59].dominantType = "";
  c9_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c9_info[59].fileTimeLo = 1299091168U;
  c9_info[59].fileTimeHi = 0U;
  c9_info[59].mFileTimeLo = 0U;
  c9_info[59].mFileTimeHi = 0U;
  c9_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c9_info[60].name = "eml_xdot";
  c9_info[60].dominantType = "double";
  c9_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c9_info[60].fileTimeLo = 1299091172U;
  c9_info[60].fileTimeHi = 0U;
  c9_info[60].mFileTimeLo = 0U;
  c9_info[60].mFileTimeHi = 0U;
  c9_info[61].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c9_info[61].name = "eml_blas_inline";
  c9_info[61].dominantType = "";
  c9_info[61].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c9_info[61].fileTimeLo = 1299091168U;
  c9_info[61].fileTimeHi = 0U;
  c9_info[61].mFileTimeLo = 0U;
  c9_info[61].mFileTimeHi = 0U;
  c9_info[62].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c9_info[62].name = "eml_index_class";
  c9_info[62].dominantType = "";
  c9_info[62].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[62].fileTimeLo = 1323181378U;
  c9_info[62].fileTimeHi = 0U;
  c9_info[62].mFileTimeLo = 0U;
  c9_info[62].mFileTimeHi = 0U;
  c9_info[63].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c9_info[63].name = "eml_refblas_xdot";
  c9_info[63].dominantType = "double";
  c9_info[63].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c9_info[63].fileTimeLo = 1299091172U;
  c9_info[63].fileTimeHi = 0U;
  c9_info[63].mFileTimeLo = 0U;
  c9_info[63].mFileTimeHi = 0U;
}

static real_T c9_norm(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
                      *chartInstance, real_T c9_x[3])
{
  real_T c9_y;
  real_T c9_scale;
  int32_T c9_k;
  int32_T c9_b_k;
  real_T c9_b_x;
  real_T c9_c_x;
  real_T c9_absxk;
  real_T c9_t;
  c9_y = 0.0;
  c9_scale = 2.2250738585072014E-308;
  for (c9_k = 1; c9_k < 4; c9_k++) {
    c9_b_k = c9_k;
    c9_b_x = c9_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c9_b_k), 1, 3, 1, 0) - 1];
    c9_c_x = c9_b_x;
    c9_absxk = muDoubleScalarAbs(c9_c_x);
    if (c9_absxk > c9_scale) {
      c9_t = c9_scale / c9_absxk;
      c9_y = 1.0 + c9_y * c9_t * c9_t;
      c9_scale = c9_absxk;
    } else {
      c9_t = c9_absxk / c9_scale;
      c9_y += c9_t * c9_t;
    }
  }

  return c9_scale * muDoubleScalarSqrt(c9_y);
}

static void c9_cross(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
                     *chartInstance, real_T c9_a[3], real_T c9_b[3], real_T
                     c9_c[3])
{
  real_T c9_b_a;
  real_T c9_b_b;
  real_T c9_y;
  real_T c9_c_a;
  real_T c9_c_b;
  real_T c9_b_y;
  real_T c9_c1;
  real_T c9_d_a;
  real_T c9_d_b;
  real_T c9_c_y;
  real_T c9_e_a;
  real_T c9_e_b;
  real_T c9_d_y;
  real_T c9_c2;
  real_T c9_f_a;
  real_T c9_f_b;
  real_T c9_e_y;
  real_T c9_g_a;
  real_T c9_g_b;
  real_T c9_f_y;
  real_T c9_c3;
  c9_b_a = c9_a[1];
  c9_b_b = c9_b[2];
  c9_y = c9_b_a * c9_b_b;
  c9_c_a = c9_a[2];
  c9_c_b = c9_b[1];
  c9_b_y = c9_c_a * c9_c_b;
  c9_c1 = c9_y - c9_b_y;
  c9_d_a = c9_a[2];
  c9_d_b = c9_b[0];
  c9_c_y = c9_d_a * c9_d_b;
  c9_e_a = c9_a[0];
  c9_e_b = c9_b[2];
  c9_d_y = c9_e_a * c9_e_b;
  c9_c2 = c9_c_y - c9_d_y;
  c9_f_a = c9_a[0];
  c9_f_b = c9_b[1];
  c9_e_y = c9_f_a * c9_f_b;
  c9_g_a = c9_a[1];
  c9_g_b = c9_b[0];
  c9_f_y = c9_g_a * c9_g_b;
  c9_c3 = c9_e_y - c9_f_y;
  c9_c[0] = c9_c1;
  c9_c[1] = c9_c2;
  c9_c[2] = c9_c3;
}

static void c9_eml_scalar_eg(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static real_T c9_mpower(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance, real_T c9_a)
{
  real_T c9_b_a;
  real_T c9_c_a;
  real_T c9_ak;
  real_T c9_d_a;
  real_T c9_e_a;
  real_T c9_b;
  c9_b_a = c9_a;
  c9_c_a = c9_b_a;
  c9_b_eml_scalar_eg(chartInstance);
  c9_ak = c9_c_a;
  c9_d_a = c9_ak;
  c9_b_eml_scalar_eg(chartInstance);
  c9_e_a = c9_d_a;
  c9_b = c9_d_a;
  return c9_e_a * c9_b;
}

static void c9_b_eml_scalar_eg(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static void c9_c_eml_scalar_eg(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct
  *chartInstance)
{
}

static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(int32_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static int32_T c9_e_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  int32_T c9_y;
  int32_T c9_i112;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_i112, 1, 6, 0U, 0, 0U, 0);
  c9_y = c9_i112;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_b_sfEvent;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  int32_T c9_y;
  SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *)
    chartInstanceVoid;
  c9_b_sfEvent = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_sfEvent),
    &c9_thisId);
  sf_mex_destroy(&c9_b_sfEvent);
  *(int32_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static uint8_T c9_f_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_b_is_active_c9_modelo_FK_simul_coleta_dados, const char_T *c9_identifier)
{
  uint8_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c9_b_is_active_c9_modelo_FK_simul_coleta_dados), &c9_thisId);
  sf_mex_destroy(&c9_b_is_active_c9_modelo_FK_simul_coleta_dados);
  return c9_y;
}

static uint8_T c9_g_emlrt_marshallIn
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance, const mxArray
   *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  uint8_T c9_y;
  uint8_T c9_u0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_u0, 1, 3, 0U, 0, 0U, 0);
  c9_y = c9_u0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void init_dsm_address_info
  (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance)
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

void sf_c9_modelo_FK_simul_coleta_dados_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3351463977U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(703004669U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1935869677U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(332743258U);
}

mxArray *sf_c9_modelo_FK_simul_coleta_dados_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("tKqlja5jpgcWgFNvrxxo0D");
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
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
      pr[1] = (double)(3);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c9_modelo_FK_simul_coleta_dados_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c9_modelo_FK_simul_coleta_dados(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"A\",},{M[1],M[11],T\"R\",},{M[8],M[0],T\"is_active_c9_modelo_FK_simul_coleta_dados\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c9_modelo_FK_simul_coleta_dados_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
    chartInstance = (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modelo_FK_simul_coleta_dadosMachineNumber_,
           9,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"sig_mag");
          _SFD_SET_DATA_PROPS(1,2,0,1,"A");
          _SFD_SET_DATA_PROPS(2,1,1,0,"mag_rec");
          _SFD_SET_DATA_PROPS(3,1,1,0,"mag_ref");
          _SFD_SET_DATA_PROPS(4,1,1,0,"acc_ref");
          _SFD_SET_DATA_PROPS(5,1,1,0,"acc_rec");
          _SFD_SET_DATA_PROPS(6,1,1,0,"sig_acc");
          _SFD_SET_DATA_PROPS(7,2,0,1,"R");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1501);
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
            1.0,0,0,(MexFcnForType)c9_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)
            c9_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)
            c9_sf_marshallIn);
        }

        {
          real_T (*c9_sig_mag)[3];
          real_T (*c9_A)[9];
          real_T (*c9_mag_rec)[3];
          real_T (*c9_mag_ref)[3];
          real_T (*c9_acc_ref)[3];
          real_T (*c9_acc_rec)[3];
          real_T (*c9_sig_acc)[3];
          real_T (*c9_R)[9];
          c9_R = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
          c9_sig_acc = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
          c9_acc_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
          c9_acc_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c9_mag_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c9_mag_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c9_A = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
          c9_sig_mag = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c9_sig_mag);
          _SFD_SET_DATA_VALUE_PTR(1U, *c9_A);
          _SFD_SET_DATA_VALUE_PTR(2U, *c9_mag_rec);
          _SFD_SET_DATA_VALUE_PTR(3U, *c9_mag_ref);
          _SFD_SET_DATA_VALUE_PTR(4U, *c9_acc_ref);
          _SFD_SET_DATA_VALUE_PTR(5U, *c9_acc_rec);
          _SFD_SET_DATA_VALUE_PTR(6U, *c9_sig_acc);
          _SFD_SET_DATA_VALUE_PTR(7U, *c9_R);
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
  return "HMiwoKvFZGvMTvStzmzMeE";
}

static void sf_opaque_initialize_c9_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c9_modelo_FK_simul_coleta_dados
    ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
  initialize_c9_modelo_FK_simul_coleta_dados
    ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c9_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  enable_c9_modelo_FK_simul_coleta_dados
    ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c9_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  disable_c9_modelo_FK_simul_coleta_dados
    ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c9_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  sf_c9_modelo_FK_simul_coleta_dados
    ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c9_modelo_FK_simul_coleta_dados
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c9_modelo_FK_simul_coleta_dados
    ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_modelo_FK_simul_coleta_dados();/* state var info */
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

extern void sf_internal_set_sim_state_c9_modelo_FK_simul_coleta_dados(SimStruct*
  S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_modelo_FK_simul_coleta_dados();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c9_modelo_FK_simul_coleta_dados
    ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c9_modelo_FK_simul_coleta_dados
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c9_modelo_FK_simul_coleta_dados(S);
}

static void sf_opaque_set_sim_state_c9_modelo_FK_simul_coleta_dados(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c9_modelo_FK_simul_coleta_dados(S, st);
}

static void sf_opaque_terminate_c9_modelo_FK_simul_coleta_dados(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_FK_simul_coleta_dados_optimization_info();
    }

    finalize_c9_modelo_FK_simul_coleta_dados
      ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc9_modelo_FK_simul_coleta_dados
    ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c9_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c9_modelo_FK_simul_coleta_dados
      ((SFc9_modelo_FK_simul_coleta_dadosInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c9_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_modelo_FK_simul_coleta_dados_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      9);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,9,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,9,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,9);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,9,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,9,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 6; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,9);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(122134168U));
  ssSetChecksum1(S,(1355071747U));
  ssSetChecksum2(S,(2041418877U));
  ssSetChecksum3(S,(2917076295U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c9_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c9_modelo_FK_simul_coleta_dados(SimStruct *S)
{
  SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *chartInstance;
  chartInstance = (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct *)utMalloc
    (sizeof(SFc9_modelo_FK_simul_coleta_dadosInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc9_modelo_FK_simul_coleta_dadosInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c9_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c9_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c9_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c9_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c9_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c9_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c9_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c9_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c9_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.mdlStart = mdlStart_c9_modelo_FK_simul_coleta_dados;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c9_modelo_FK_simul_coleta_dados;
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

void c9_modelo_FK_simul_coleta_dados_method_dispatcher(SimStruct *S, int_T
  method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c9_modelo_FK_simul_coleta_dados(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c9_modelo_FK_simul_coleta_dados(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c9_modelo_FK_simul_coleta_dados(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c9_modelo_FK_simul_coleta_dados_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
