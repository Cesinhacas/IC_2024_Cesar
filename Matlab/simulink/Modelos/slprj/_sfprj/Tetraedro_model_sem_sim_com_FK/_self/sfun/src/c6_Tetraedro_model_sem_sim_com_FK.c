/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Tetraedro_model_sem_sim_com_FK_sfun.h"
#include "c6_Tetraedro_model_sem_sim_com_FK.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Tetraedro_model_sem_sim_com_FK_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c6_debug_family_names[24] = { "V1", "V2", "W1", "W2",
  "SigTot1", "SigTot2", "r1", "r2", "r3", "Mref", "s1", "s2", "s3", "Mobs",
  "nargin", "nargout", "sig_ace", "mag_rec", "mag_ref", "acc_ref", "acc_rec",
  "sig_gir", "A", "R" };

/* Function Declarations */
static void initialize_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static void initialize_params_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static void enable_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static void disable_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static void c6_update_debugger_state_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static void set_sim_state_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_st);
static void finalize_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static void sf_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static void c6_chartstep_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static void initSimStructsc6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static void registerMessagesc6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static void c6_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_R, const char_T *c6_identifier, real_T c6_y[9]);
static void c6_b_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[9]);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static real_T c6_c_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static void c6_d_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3]);
static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static void c6_info_helper(c6_ResolvedFunctionInfo c6_info[71]);
static real_T c6_norm(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
                      *chartInstance, real_T c6_x[3]);
static void c6_cross(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
                     *chartInstance, real_T c6_a[3], real_T c6_b[3], real_T
                     c6_c[3]);
static void c6_eml_scalar_eg(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
  *chartInstance);
static real_T c6_mpower(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
  *chartInstance, real_T c6_a);
static void c6_b_eml_scalar_eg(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
  *chartInstance);
static void c6_c_eml_scalar_eg(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
  *chartInstance);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static int32_T c6_e_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static uint8_T c6_f_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_b_is_active_c6_Tetraedro_model_sem_sim_com_FK, const char_T
   *c6_identifier);
static uint8_T c6_g_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void init_dsm_address_info
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c6_is_active_c6_Tetraedro_model_sem_sim_com_FK = 0U;
}

static void initialize_params_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
}

static void enable_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c6_update_debugger_state_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  int32_T c6_i0;
  real_T c6_u[9];
  const mxArray *c6_b_y = NULL;
  int32_T c6_i1;
  real_T c6_b_u[9];
  const mxArray *c6_c_y = NULL;
  uint8_T c6_hoistedGlobal;
  uint8_T c6_c_u;
  const mxArray *c6_d_y = NULL;
  real_T (*c6_R)[9];
  real_T (*c6_A)[9];
  c6_R = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c6_A = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellarray(3), FALSE);
  for (c6_i0 = 0; c6_i0 < 9; c6_i0++) {
    c6_u[c6_i0] = (*c6_A)[c6_i0];
  }

  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  for (c6_i1 = 0; c6_i1 < 9; c6_i1++) {
    c6_b_u[c6_i1] = (*c6_R)[c6_i1];
  }

  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", c6_b_u, 0, 0U, 1U, 0U, 2, 3, 3),
                FALSE);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  c6_hoistedGlobal =
    chartInstance->c6_is_active_c6_Tetraedro_model_sem_sim_com_FK;
  c6_c_u = c6_hoistedGlobal;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 2, c6_d_y);
  sf_mex_assign(&c6_st, c6_y, FALSE);
  return c6_st;
}

static void set_sim_state_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_st)
{
  const mxArray *c6_u;
  real_T c6_dv0[9];
  int32_T c6_i2;
  real_T c6_dv1[9];
  int32_T c6_i3;
  real_T (*c6_A)[9];
  real_T (*c6_R)[9];
  c6_R = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c6_A = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c6_doneDoubleBufferReInit = TRUE;
  c6_u = sf_mex_dup(c6_st);
  c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 0)), "A",
                      c6_dv0);
  for (c6_i2 = 0; c6_i2 < 9; c6_i2++) {
    (*c6_A)[c6_i2] = c6_dv0[c6_i2];
  }

  c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 1)), "R",
                      c6_dv1);
  for (c6_i3 = 0; c6_i3 < 9; c6_i3++) {
    (*c6_R)[c6_i3] = c6_dv1[c6_i3];
  }

  chartInstance->c6_is_active_c6_Tetraedro_model_sem_sim_com_FK =
    c6_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 2)),
    "is_active_c6_Tetraedro_model_sem_sim_com_FK");
  sf_mex_destroy(&c6_u);
  c6_update_debugger_state_c6_Tetraedro_model_sem_sim_com_FK(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void finalize_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
}

static void sf_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
  int32_T c6_i4;
  int32_T c6_i5;
  int32_T c6_i6;
  int32_T c6_i7;
  int32_T c6_i8;
  int32_T c6_i9;
  real_T *c6_sig_ace;
  real_T *c6_sig_gir;
  real_T (*c6_R)[9];
  real_T (*c6_acc_rec)[3];
  real_T (*c6_acc_ref)[3];
  real_T (*c6_mag_ref)[3];
  real_T (*c6_mag_rec)[3];
  real_T (*c6_A)[9];
  c6_R = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c6_sig_gir = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c6_acc_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c6_acc_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c6_mag_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c6_mag_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c6_A = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_sig_ace = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c6_sig_ace, 0U);
  for (c6_i4 = 0; c6_i4 < 9; c6_i4++) {
    _SFD_DATA_RANGE_CHECK((*c6_A)[c6_i4], 1U);
  }

  for (c6_i5 = 0; c6_i5 < 3; c6_i5++) {
    _SFD_DATA_RANGE_CHECK((*c6_mag_rec)[c6_i5], 2U);
  }

  for (c6_i6 = 0; c6_i6 < 3; c6_i6++) {
    _SFD_DATA_RANGE_CHECK((*c6_mag_ref)[c6_i6], 3U);
  }

  for (c6_i7 = 0; c6_i7 < 3; c6_i7++) {
    _SFD_DATA_RANGE_CHECK((*c6_acc_ref)[c6_i7], 4U);
  }

  for (c6_i8 = 0; c6_i8 < 3; c6_i8++) {
    _SFD_DATA_RANGE_CHECK((*c6_acc_rec)[c6_i8], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c6_sig_gir, 6U);
  for (c6_i9 = 0; c6_i9 < 9; c6_i9++) {
    _SFD_DATA_RANGE_CHECK((*c6_R)[c6_i9], 7U);
  }

  chartInstance->c6_sfEvent = CALL_EVENT;
  c6_chartstep_c6_Tetraedro_model_sem_sim_com_FK(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY
    (_Tetraedro_model_sem_sim_com_FKMachineNumber_, chartInstance->chartNumber,
     chartInstance->instanceNumber);
}

static void c6_chartstep_c6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
  real_T c6_hoistedGlobal;
  real_T c6_b_hoistedGlobal;
  real_T c6_sig_ace;
  int32_T c6_i10;
  real_T c6_mag_rec[3];
  int32_T c6_i11;
  real_T c6_mag_ref[3];
  int32_T c6_i12;
  real_T c6_acc_ref[3];
  int32_T c6_i13;
  real_T c6_acc_rec[3];
  real_T c6_sig_gir;
  uint32_T c6_debug_family_var_map[24];
  real_T c6_V1[3];
  real_T c6_V2[3];
  real_T c6_W1[3];
  real_T c6_W2[3];
  real_T c6_SigTot1;
  real_T c6_SigTot2;
  real_T c6_r1[3];
  real_T c6_r2[3];
  real_T c6_r3[3];
  real_T c6_Mref[9];
  real_T c6_s1[3];
  real_T c6_s2[3];
  real_T c6_s3[3];
  real_T c6_Mobs[9];
  real_T c6_nargin = 6.0;
  real_T c6_nargout = 2.0;
  real_T c6_A[9];
  real_T c6_R[9];
  int32_T c6_i14;
  int32_T c6_i15;
  int32_T c6_i16;
  int32_T c6_i17;
  int32_T c6_i18;
  real_T c6_b_A[3];
  int32_T c6_i19;
  real_T c6_b_V1[3];
  real_T c6_B;
  real_T c6_y;
  real_T c6_b_y;
  int32_T c6_i20;
  int32_T c6_i21;
  real_T c6_c_V1[3];
  int32_T c6_i22;
  real_T c6_b_V2[3];
  real_T c6_dv2[3];
  int32_T c6_i23;
  int32_T c6_i24;
  int32_T c6_i25;
  real_T c6_b_r2[3];
  real_T c6_b_B;
  real_T c6_c_y;
  real_T c6_d_y;
  int32_T c6_i26;
  int32_T c6_i27;
  real_T c6_b_r1[3];
  int32_T c6_i28;
  real_T c6_c_r2[3];
  real_T c6_dv3[3];
  int32_T c6_i29;
  int32_T c6_i30;
  int32_T c6_i31;
  int32_T c6_i32;
  int32_T c6_i33;
  int32_T c6_i34;
  real_T c6_b_W1[3];
  real_T c6_c_B;
  real_T c6_e_y;
  real_T c6_f_y;
  int32_T c6_i35;
  int32_T c6_i36;
  real_T c6_c_W1[3];
  int32_T c6_i37;
  real_T c6_b_W2[3];
  real_T c6_dv4[3];
  int32_T c6_i38;
  int32_T c6_i39;
  int32_T c6_i40;
  real_T c6_b_s2[3];
  real_T c6_d_B;
  real_T c6_g_y;
  real_T c6_h_y;
  int32_T c6_i41;
  int32_T c6_i42;
  real_T c6_b_s1[3];
  int32_T c6_i43;
  real_T c6_c_s2[3];
  real_T c6_dv5[3];
  int32_T c6_i44;
  int32_T c6_i45;
  int32_T c6_i46;
  int32_T c6_i47;
  int32_T c6_i48;
  real_T c6_a[9];
  int32_T c6_i49;
  int32_T c6_i50;
  int32_T c6_i51;
  int32_T c6_i52;
  real_T c6_b[9];
  int32_T c6_i53;
  int32_T c6_i54;
  int32_T c6_i55;
  real_T c6_C[9];
  int32_T c6_i56;
  int32_T c6_i57;
  int32_T c6_i58;
  int32_T c6_i59;
  int32_T c6_i60;
  int32_T c6_i61;
  int32_T c6_i62;
  int32_T c6_i63;
  real_T c6_b_a;
  int32_T c6_i64;
  static real_T c6_b_b[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c6_i65;
  real_T c6_d_W1[3];
  int32_T c6_i66;
  real_T c6_c_W2[3];
  int32_T c6_i67;
  real_T c6_c_A[3];
  real_T c6_e_B;
  real_T c6_i_y;
  real_T c6_j_y;
  real_T c6_k_y;
  int32_T c6_i68;
  real_T c6_c_a[3];
  int32_T c6_i69;
  real_T c6_l_y;
  int32_T c6_k;
  int32_T c6_b_k;
  real_T c6_d_a;
  real_T c6_c_b;
  real_T c6_m_y;
  int32_T c6_i70;
  int32_T c6_i71;
  int32_T c6_i72;
  int32_T c6_i73;
  int32_T c6_i74;
  int32_T c6_i75;
  int32_T c6_i76;
  int32_T c6_i77;
  int32_T c6_i78;
  int32_T c6_i79;
  real_T c6_e_a;
  int32_T c6_i80;
  int32_T c6_i81;
  real_T c6_f_a;
  int32_T c6_i82;
  int32_T c6_i83;
  int32_T c6_i84;
  int32_T c6_i85;
  int32_T c6_i86;
  int32_T c6_i87;
  real_T c6_g_a;
  int32_T c6_i88;
  int32_T c6_i89;
  int32_T c6_i90;
  int32_T c6_i91;
  int32_T c6_i92;
  real_T *c6_b_sig_ace;
  real_T *c6_b_sig_gir;
  real_T (*c6_d_A)[9];
  real_T (*c6_b_R)[9];
  real_T (*c6_b_acc_rec)[3];
  real_T (*c6_b_acc_ref)[3];
  real_T (*c6_b_mag_ref)[3];
  real_T (*c6_b_mag_rec)[3];
  c6_b_R = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c6_b_sig_gir = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c6_b_acc_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c6_b_acc_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c6_b_mag_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c6_b_mag_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c6_d_A = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_b_sig_ace = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  c6_hoistedGlobal = *c6_b_sig_ace;
  c6_b_hoistedGlobal = *c6_b_sig_gir;
  c6_sig_ace = c6_hoistedGlobal;
  for (c6_i10 = 0; c6_i10 < 3; c6_i10++) {
    c6_mag_rec[c6_i10] = (*c6_b_mag_rec)[c6_i10];
  }

  for (c6_i11 = 0; c6_i11 < 3; c6_i11++) {
    c6_mag_ref[c6_i11] = (*c6_b_mag_ref)[c6_i11];
  }

  for (c6_i12 = 0; c6_i12 < 3; c6_i12++) {
    c6_acc_ref[c6_i12] = (*c6_b_acc_ref)[c6_i12];
  }

  for (c6_i13 = 0; c6_i13 < 3; c6_i13++) {
    c6_acc_rec[c6_i13] = (*c6_b_acc_rec)[c6_i13];
  }

  c6_sig_gir = c6_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 24U, 24U, c6_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_V1, 0U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_V2, 1U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_W1, 2U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_W2, 3U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_SigTot1, 4U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_SigTot2, 5U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_r1, 6U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_r2, 7U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_r3, 8U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_Mref, 9U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_s1, 10U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_s2, 11U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_s3, 12U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_Mobs, 13U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 14U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 15U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_sig_ace, 16U, c6_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_mag_rec, 17U, c6_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_mag_ref, 18U, c6_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_acc_ref, 19U, c6_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_acc_rec, 20U, c6_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_sig_gir, 21U, c6_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_A, 22U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_R, 23U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 7);
  for (c6_i14 = 0; c6_i14 < 3; c6_i14++) {
    c6_V1[c6_i14] = c6_acc_ref[c6_i14];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 9);
  for (c6_i15 = 0; c6_i15 < 3; c6_i15++) {
    c6_V2[c6_i15] = c6_mag_ref[c6_i15];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 11);
  for (c6_i16 = 0; c6_i16 < 3; c6_i16++) {
    c6_W1[c6_i16] = c6_acc_rec[c6_i16];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 13);
  for (c6_i17 = 0; c6_i17 < 3; c6_i17++) {
    c6_W2[c6_i17] = c6_mag_rec[c6_i17];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 15);
  c6_SigTot1 = c6_sig_ace;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 17);
  c6_SigTot2 = c6_sig_gir;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 25);
  for (c6_i18 = 0; c6_i18 < 3; c6_i18++) {
    c6_b_A[c6_i18] = c6_V1[c6_i18];
  }

  for (c6_i19 = 0; c6_i19 < 3; c6_i19++) {
    c6_b_V1[c6_i19] = c6_V1[c6_i19];
  }

  c6_B = c6_norm(chartInstance, c6_b_V1);
  c6_y = c6_B;
  c6_b_y = c6_y;
  for (c6_i20 = 0; c6_i20 < 3; c6_i20++) {
    c6_r1[c6_i20] = c6_b_A[c6_i20] / c6_b_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 26);
  for (c6_i21 = 0; c6_i21 < 3; c6_i21++) {
    c6_c_V1[c6_i21] = c6_V1[c6_i21];
  }

  for (c6_i22 = 0; c6_i22 < 3; c6_i22++) {
    c6_b_V2[c6_i22] = c6_V2[c6_i22];
  }

  c6_cross(chartInstance, c6_c_V1, c6_b_V2, c6_dv2);
  for (c6_i23 = 0; c6_i23 < 3; c6_i23++) {
    c6_r2[c6_i23] = c6_dv2[c6_i23];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 27);
  for (c6_i24 = 0; c6_i24 < 3; c6_i24++) {
    c6_b_A[c6_i24] = c6_r2[c6_i24];
  }

  for (c6_i25 = 0; c6_i25 < 3; c6_i25++) {
    c6_b_r2[c6_i25] = c6_r2[c6_i25];
  }

  c6_b_B = c6_norm(chartInstance, c6_b_r2);
  c6_c_y = c6_b_B;
  c6_d_y = c6_c_y;
  for (c6_i26 = 0; c6_i26 < 3; c6_i26++) {
    c6_r2[c6_i26] = c6_b_A[c6_i26] / c6_d_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 28);
  for (c6_i27 = 0; c6_i27 < 3; c6_i27++) {
    c6_b_r1[c6_i27] = c6_r1[c6_i27];
  }

  for (c6_i28 = 0; c6_i28 < 3; c6_i28++) {
    c6_c_r2[c6_i28] = c6_r2[c6_i28];
  }

  c6_cross(chartInstance, c6_b_r1, c6_c_r2, c6_dv3);
  for (c6_i29 = 0; c6_i29 < 3; c6_i29++) {
    c6_r3[c6_i29] = c6_dv3[c6_i29];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 30);
  for (c6_i30 = 0; c6_i30 < 3; c6_i30++) {
    c6_Mref[c6_i30] = c6_r1[c6_i30];
  }

  for (c6_i31 = 0; c6_i31 < 3; c6_i31++) {
    c6_Mref[c6_i31 + 3] = c6_r2[c6_i31];
  }

  for (c6_i32 = 0; c6_i32 < 3; c6_i32++) {
    c6_Mref[c6_i32 + 6] = c6_r3[c6_i32];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 33);
  for (c6_i33 = 0; c6_i33 < 3; c6_i33++) {
    c6_b_A[c6_i33] = c6_W1[c6_i33];
  }

  for (c6_i34 = 0; c6_i34 < 3; c6_i34++) {
    c6_b_W1[c6_i34] = c6_W1[c6_i34];
  }

  c6_c_B = c6_norm(chartInstance, c6_b_W1);
  c6_e_y = c6_c_B;
  c6_f_y = c6_e_y;
  for (c6_i35 = 0; c6_i35 < 3; c6_i35++) {
    c6_s1[c6_i35] = c6_b_A[c6_i35] / c6_f_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 34);
  for (c6_i36 = 0; c6_i36 < 3; c6_i36++) {
    c6_c_W1[c6_i36] = c6_W1[c6_i36];
  }

  for (c6_i37 = 0; c6_i37 < 3; c6_i37++) {
    c6_b_W2[c6_i37] = c6_W2[c6_i37];
  }

  c6_cross(chartInstance, c6_c_W1, c6_b_W2, c6_dv4);
  for (c6_i38 = 0; c6_i38 < 3; c6_i38++) {
    c6_s2[c6_i38] = c6_dv4[c6_i38];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 35);
  for (c6_i39 = 0; c6_i39 < 3; c6_i39++) {
    c6_b_A[c6_i39] = c6_s2[c6_i39];
  }

  for (c6_i40 = 0; c6_i40 < 3; c6_i40++) {
    c6_b_s2[c6_i40] = c6_s2[c6_i40];
  }

  c6_d_B = c6_norm(chartInstance, c6_b_s2);
  c6_g_y = c6_d_B;
  c6_h_y = c6_g_y;
  for (c6_i41 = 0; c6_i41 < 3; c6_i41++) {
    c6_s2[c6_i41] = c6_b_A[c6_i41] / c6_h_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 36);
  for (c6_i42 = 0; c6_i42 < 3; c6_i42++) {
    c6_b_s1[c6_i42] = c6_s1[c6_i42];
  }

  for (c6_i43 = 0; c6_i43 < 3; c6_i43++) {
    c6_c_s2[c6_i43] = c6_s2[c6_i43];
  }

  c6_cross(chartInstance, c6_b_s1, c6_c_s2, c6_dv5);
  for (c6_i44 = 0; c6_i44 < 3; c6_i44++) {
    c6_s3[c6_i44] = c6_dv5[c6_i44];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 38);
  for (c6_i45 = 0; c6_i45 < 3; c6_i45++) {
    c6_Mobs[c6_i45] = c6_s1[c6_i45];
  }

  for (c6_i46 = 0; c6_i46 < 3; c6_i46++) {
    c6_Mobs[c6_i46 + 3] = c6_s2[c6_i46];
  }

  for (c6_i47 = 0; c6_i47 < 3; c6_i47++) {
    c6_Mobs[c6_i47 + 6] = c6_s3[c6_i47];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 40);
  for (c6_i48 = 0; c6_i48 < 9; c6_i48++) {
    c6_a[c6_i48] = c6_Mobs[c6_i48];
  }

  c6_i49 = 0;
  for (c6_i50 = 0; c6_i50 < 3; c6_i50++) {
    c6_i51 = 0;
    for (c6_i52 = 0; c6_i52 < 3; c6_i52++) {
      c6_b[c6_i52 + c6_i49] = c6_Mref[c6_i51 + c6_i50];
      c6_i51 += 3;
    }

    c6_i49 += 3;
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i53 = 0; c6_i53 < 9; c6_i53++) {
    c6_A[c6_i53] = 0.0;
  }

  for (c6_i54 = 0; c6_i54 < 9; c6_i54++) {
    c6_A[c6_i54] = 0.0;
  }

  for (c6_i55 = 0; c6_i55 < 9; c6_i55++) {
    c6_C[c6_i55] = c6_A[c6_i55];
  }

  for (c6_i56 = 0; c6_i56 < 9; c6_i56++) {
    c6_A[c6_i56] = c6_C[c6_i56];
  }

  for (c6_i57 = 0; c6_i57 < 9; c6_i57++) {
    c6_C[c6_i57] = c6_A[c6_i57];
  }

  for (c6_i58 = 0; c6_i58 < 9; c6_i58++) {
    c6_A[c6_i58] = c6_C[c6_i58];
  }

  for (c6_i59 = 0; c6_i59 < 3; c6_i59++) {
    c6_i60 = 0;
    for (c6_i61 = 0; c6_i61 < 3; c6_i61++) {
      c6_A[c6_i60 + c6_i59] = 0.0;
      c6_i62 = 0;
      for (c6_i63 = 0; c6_i63 < 3; c6_i63++) {
        c6_A[c6_i60 + c6_i59] += c6_a[c6_i62 + c6_i59] * c6_b[c6_i63 + c6_i60];
        c6_i62 += 3;
      }

      c6_i60 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 43);
  c6_b_a = c6_mpower(chartInstance, c6_SigTot1);
  for (c6_i64 = 0; c6_i64 < 9; c6_i64++) {
    c6_a[c6_i64] = c6_b_a * c6_b_b[c6_i64];
  }

  for (c6_i65 = 0; c6_i65 < 3; c6_i65++) {
    c6_d_W1[c6_i65] = c6_W1[c6_i65];
  }

  for (c6_i66 = 0; c6_i66 < 3; c6_i66++) {
    c6_c_W2[c6_i66] = c6_W2[c6_i66];
  }

  c6_cross(chartInstance, c6_d_W1, c6_c_W2, c6_b_A);
  for (c6_i67 = 0; c6_i67 < 3; c6_i67++) {
    c6_c_A[c6_i67] = c6_b_A[c6_i67];
  }

  c6_e_B = c6_norm(chartInstance, c6_c_A);
  c6_i_y = c6_e_B;
  c6_j_y = c6_i_y;
  c6_k_y = 1.0 / c6_j_y;
  for (c6_i68 = 0; c6_i68 < 3; c6_i68++) {
    c6_c_a[c6_i68] = c6_W1[c6_i68];
  }

  for (c6_i69 = 0; c6_i69 < 3; c6_i69++) {
    c6_b_A[c6_i69] = c6_W2[c6_i69];
  }

  c6_c_eml_scalar_eg(chartInstance);
  c6_c_eml_scalar_eg(chartInstance);
  c6_l_y = 0.0;
  for (c6_k = 1; c6_k < 4; c6_k++) {
    c6_b_k = c6_k;
    c6_l_y += c6_c_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
      ("", (real_T)c6_b_k), 1, 3, 1, 0) - 1] *
      c6_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c6_b_k), 1, 3, 1, 0) - 1];
  }

  c6_d_a = c6_mpower(chartInstance, c6_SigTot1);
  c6_c_b = c6_l_y;
  c6_m_y = c6_d_a * c6_c_b;
  for (c6_i70 = 0; c6_i70 < 3; c6_i70++) {
    c6_b_A[c6_i70] = c6_W1[c6_i70];
  }

  for (c6_i71 = 0; c6_i71 < 3; c6_i71++) {
    c6_c_a[c6_i71] = c6_W2[c6_i71];
  }

  for (c6_i72 = 0; c6_i72 < 3; c6_i72++) {
    c6_i73 = 0;
    for (c6_i74 = 0; c6_i74 < 3; c6_i74++) {
      c6_b[c6_i73 + c6_i72] = c6_b_A[c6_i72] * c6_c_a[c6_i74];
      c6_i73 += 3;
    }
  }

  for (c6_i75 = 0; c6_i75 < 3; c6_i75++) {
    c6_b_A[c6_i75] = c6_W2[c6_i75];
  }

  for (c6_i76 = 0; c6_i76 < 3; c6_i76++) {
    c6_c_a[c6_i76] = c6_W1[c6_i76];
  }

  for (c6_i77 = 0; c6_i77 < 3; c6_i77++) {
    c6_i78 = 0;
    for (c6_i79 = 0; c6_i79 < 3; c6_i79++) {
      c6_C[c6_i78 + c6_i77] = c6_b_A[c6_i77] * c6_c_a[c6_i79];
      c6_i78 += 3;
    }
  }

  c6_e_a = c6_m_y;
  for (c6_i80 = 0; c6_i80 < 9; c6_i80++) {
    c6_b[c6_i80] += c6_C[c6_i80];
  }

  for (c6_i81 = 0; c6_i81 < 9; c6_i81++) {
    c6_b[c6_i81] *= c6_e_a;
  }

  c6_f_a = c6_mpower(chartInstance, c6_SigTot2) - c6_mpower(chartInstance,
    c6_SigTot1);
  for (c6_i82 = 0; c6_i82 < 3; c6_i82++) {
    c6_b_A[c6_i82] = c6_W1[c6_i82];
  }

  for (c6_i83 = 0; c6_i83 < 3; c6_i83++) {
    c6_b_A[c6_i83] *= c6_f_a;
  }

  for (c6_i84 = 0; c6_i84 < 3; c6_i84++) {
    c6_c_a[c6_i84] = c6_W1[c6_i84];
  }

  for (c6_i85 = 0; c6_i85 < 3; c6_i85++) {
    c6_i86 = 0;
    for (c6_i87 = 0; c6_i87 < 3; c6_i87++) {
      c6_C[c6_i86 + c6_i85] = c6_b_A[c6_i85] * c6_c_a[c6_i87];
      c6_i86 += 3;
    }
  }

  c6_g_a = c6_mpower(chartInstance, c6_k_y);
  for (c6_i88 = 0; c6_i88 < 9; c6_i88++) {
    c6_b[c6_i88] += c6_C[c6_i88];
  }

  for (c6_i89 = 0; c6_i89 < 9; c6_i89++) {
    c6_b[c6_i89] *= c6_g_a;
  }

  for (c6_i90 = 0; c6_i90 < 9; c6_i90++) {
    c6_R[c6_i90] = c6_a[c6_i90] + c6_b[c6_i90];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, -43);
  _SFD_SYMBOL_SCOPE_POP();
  for (c6_i91 = 0; c6_i91 < 9; c6_i91++) {
    (*c6_d_A)[c6_i91] = c6_A[c6_i91];
  }

  for (c6_i92 = 0; c6_i92 < 9; c6_i92++) {
    (*c6_b_R)[c6_i92] = c6_R[c6_i92];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
}

static void initSimStructsc6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
}

static void registerMessagesc6_Tetraedro_model_sem_sim_com_FK
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber)
{
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i93;
  int32_T c6_i94;
  int32_T c6_i95;
  real_T c6_b_inData[9];
  int32_T c6_i96;
  int32_T c6_i97;
  int32_T c6_i98;
  real_T c6_u[9];
  const mxArray *c6_y = NULL;
  SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance;
  chartInstance = (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *)
    chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_i93 = 0;
  for (c6_i94 = 0; c6_i94 < 3; c6_i94++) {
    for (c6_i95 = 0; c6_i95 < 3; c6_i95++) {
      c6_b_inData[c6_i95 + c6_i93] = (*(real_T (*)[9])c6_inData)[c6_i95 + c6_i93];
    }

    c6_i93 += 3;
  }

  c6_i96 = 0;
  for (c6_i97 = 0; c6_i97 < 3; c6_i97++) {
    for (c6_i98 = 0; c6_i98 < 3; c6_i98++) {
      c6_u[c6_i98 + c6_i96] = c6_b_inData[c6_i98 + c6_i96];
    }

    c6_i96 += 3;
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static void c6_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_R, const char_T *c6_identifier, real_T c6_y[9])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_R), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_R);
}

static void c6_b_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[9])
{
  real_T c6_dv6[9];
  int32_T c6_i99;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv6, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c6_i99 = 0; c6_i99 < 9; c6_i99++) {
    c6_y[c6_i99] = c6_dv6[c6_i99];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_R;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[9];
  int32_T c6_i100;
  int32_T c6_i101;
  int32_T c6_i102;
  SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance;
  chartInstance = (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *)
    chartInstanceVoid;
  c6_R = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_R), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_R);
  c6_i100 = 0;
  for (c6_i101 = 0; c6_i101 < 3; c6_i101++) {
    for (c6_i102 = 0; c6_i102 < 3; c6_i102++) {
      (*(real_T (*)[9])c6_outData)[c6_i102 + c6_i100] = c6_y[c6_i102 + c6_i100];
    }

    c6_i100 += 3;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance;
  chartInstance = (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *)
    chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i103;
  real_T c6_b_inData[3];
  int32_T c6_i104;
  real_T c6_u[3];
  const mxArray *c6_y = NULL;
  SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance;
  chartInstance = (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *)
    chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i103 = 0; c6_i103 < 3; c6_i103++) {
    c6_b_inData[c6_i103] = (*(real_T (*)[3])c6_inData)[c6_i103];
  }

  for (c6_i104 = 0; c6_i104 < 3; c6_i104++) {
    c6_u[c6_i104] = c6_b_inData[c6_i104];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static real_T c6_c_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d0, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_nargout;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance;
  chartInstance = (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *)
    chartInstanceVoid;
  c6_nargout = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_nargout), &c6_thisId);
  sf_mex_destroy(&c6_nargout);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static void c6_d_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3])
{
  real_T c6_dv7[3];
  int32_T c6_i105;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv7, 1, 0, 0U, 1, 0U, 1, 3);
  for (c6_i105 = 0; c6_i105 < 3; c6_i105++) {
    c6_y[c6_i105] = c6_dv7[c6_i105];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_s3;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[3];
  int32_T c6_i106;
  SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance;
  chartInstance = (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *)
    chartInstanceVoid;
  c6_s3 = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_s3), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_s3);
  for (c6_i106 = 0; c6_i106 < 3; c6_i106++) {
    (*(real_T (*)[3])c6_outData)[c6_i106] = c6_y[c6_i106];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

const mxArray
  *sf_c6_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo;
  c6_ResolvedFunctionInfo c6_info[71];
  c6_ResolvedFunctionInfo (*c6_b_info)[71];
  const mxArray *c6_m0 = NULL;
  int32_T c6_i107;
  c6_ResolvedFunctionInfo *c6_r0;
  c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  c6_info_helper(c6_info);
  c6_b_info = (c6_ResolvedFunctionInfo (*)[71])c6_info;
  (*c6_b_info)[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  (*c6_b_info)[64].name = "eml_refblas_xdotx";
  (*c6_b_info)[64].dominantType = "char";
  (*c6_b_info)[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c6_b_info)[64].fileTimeLo = 1299091174U;
  (*c6_b_info)[64].fileTimeHi = 0U;
  (*c6_b_info)[64].mFileTimeLo = 0U;
  (*c6_b_info)[64].mFileTimeHi = 0U;
  (*c6_b_info)[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c6_b_info)[65].name = "eml_scalar_eg";
  (*c6_b_info)[65].dominantType = "double";
  (*c6_b_info)[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c6_b_info)[65].fileTimeLo = 1286836796U;
  (*c6_b_info)[65].fileTimeHi = 0U;
  (*c6_b_info)[65].mFileTimeLo = 0U;
  (*c6_b_info)[65].mFileTimeHi = 0U;
  (*c6_b_info)[66].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c6_b_info)[66].name = "eml_index_class";
  (*c6_b_info)[66].dominantType = "";
  (*c6_b_info)[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*c6_b_info)[66].fileTimeLo = 1323181378U;
  (*c6_b_info)[66].fileTimeHi = 0U;
  (*c6_b_info)[66].mFileTimeLo = 0U;
  (*c6_b_info)[66].mFileTimeHi = 0U;
  (*c6_b_info)[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c6_b_info)[67].name = "eml_index_minus";
  (*c6_b_info)[67].dominantType = "double";
  (*c6_b_info)[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  (*c6_b_info)[67].fileTimeLo = 1286836778U;
  (*c6_b_info)[67].fileTimeHi = 0U;
  (*c6_b_info)[67].mFileTimeLo = 0U;
  (*c6_b_info)[67].mFileTimeHi = 0U;
  (*c6_b_info)[68].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c6_b_info)[68].name = "eml_index_times";
  (*c6_b_info)[68].dominantType = "coder.internal.indexInt";
  (*c6_b_info)[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  (*c6_b_info)[68].fileTimeLo = 1286836780U;
  (*c6_b_info)[68].fileTimeHi = 0U;
  (*c6_b_info)[68].mFileTimeLo = 0U;
  (*c6_b_info)[68].mFileTimeHi = 0U;
  (*c6_b_info)[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c6_b_info)[69].name = "eml_index_plus";
  (*c6_b_info)[69].dominantType = "coder.internal.indexInt";
  (*c6_b_info)[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  (*c6_b_info)[69].fileTimeLo = 1286836778U;
  (*c6_b_info)[69].fileTimeHi = 0U;
  (*c6_b_info)[69].mFileTimeLo = 0U;
  (*c6_b_info)[69].mFileTimeHi = 0U;
  (*c6_b_info)[70].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  (*c6_b_info)[70].name = "eml_int_forloop_overflow_check";
  (*c6_b_info)[70].dominantType = "";
  (*c6_b_info)[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  (*c6_b_info)[70].fileTimeLo = 1346528340U;
  (*c6_b_info)[70].fileTimeHi = 0U;
  (*c6_b_info)[70].mFileTimeLo = 0U;
  (*c6_b_info)[70].mFileTimeHi = 0U;
  sf_mex_assign(&c6_m0, sf_mex_createstruct("nameCaptureInfo", 1, 71), FALSE);
  for (c6_i107 = 0; c6_i107 < 71; c6_i107++) {
    c6_r0 = &c6_info[c6_i107];
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r0->context)), "context", "nameCaptureInfo",
                    c6_i107);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c6_r0->name)), "name", "nameCaptureInfo", c6_i107);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c6_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c6_i107);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r0->resolved)), "resolved", "nameCaptureInfo",
                    c6_i107);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c6_i107);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c6_i107);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c6_i107);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c6_i107);
  }

  sf_mex_assign(&c6_nameCaptureInfo, c6_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c6_nameCaptureInfo);
  return c6_nameCaptureInfo;
}

static void c6_info_helper(c6_ResolvedFunctionInfo c6_info[71])
{
  c6_info[0].context = "";
  c6_info[0].name = "norm";
  c6_info[0].dominantType = "double";
  c6_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c6_info[0].fileTimeLo = 1336540094U;
  c6_info[0].fileTimeHi = 0U;
  c6_info[0].mFileTimeLo = 0U;
  c6_info[0].mFileTimeHi = 0U;
  c6_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c6_info[1].name = "eml_index_class";
  c6_info[1].dominantType = "";
  c6_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[1].fileTimeLo = 1323181378U;
  c6_info[1].fileTimeHi = 0U;
  c6_info[1].mFileTimeLo = 0U;
  c6_info[1].mFileTimeHi = 0U;
  c6_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c6_info[2].name = "eml_xnrm2";
  c6_info[2].dominantType = "double";
  c6_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c6_info[2].fileTimeLo = 1299091176U;
  c6_info[2].fileTimeHi = 0U;
  c6_info[2].mFileTimeLo = 0U;
  c6_info[2].mFileTimeHi = 0U;
  c6_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c6_info[3].name = "eml_blas_inline";
  c6_info[3].dominantType = "";
  c6_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c6_info[3].fileTimeLo = 1299091168U;
  c6_info[3].fileTimeHi = 0U;
  c6_info[3].mFileTimeLo = 0U;
  c6_info[3].mFileTimeHi = 0U;
  c6_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c6_info[4].name = "eml_index_class";
  c6_info[4].dominantType = "";
  c6_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[4].fileTimeLo = 1323181378U;
  c6_info[4].fileTimeHi = 0U;
  c6_info[4].mFileTimeLo = 0U;
  c6_info[4].mFileTimeHi = 0U;
  c6_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c6_info[5].name = "eml_refblas_xnrm2";
  c6_info[5].dominantType = "double";
  c6_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[5].fileTimeLo = 1299091184U;
  c6_info[5].fileTimeHi = 0U;
  c6_info[5].mFileTimeLo = 0U;
  c6_info[5].mFileTimeHi = 0U;
  c6_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[6].name = "realmin";
  c6_info[6].dominantType = "char";
  c6_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c6_info[6].fileTimeLo = 1307669242U;
  c6_info[6].fileTimeHi = 0U;
  c6_info[6].mFileTimeLo = 0U;
  c6_info[6].mFileTimeHi = 0U;
  c6_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c6_info[7].name = "eml_realmin";
  c6_info[7].dominantType = "char";
  c6_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c6_info[7].fileTimeLo = 1307669244U;
  c6_info[7].fileTimeHi = 0U;
  c6_info[7].mFileTimeLo = 0U;
  c6_info[7].mFileTimeHi = 0U;
  c6_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c6_info[8].name = "eml_float_model";
  c6_info[8].dominantType = "char";
  c6_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c6_info[8].fileTimeLo = 1326738796U;
  c6_info[8].fileTimeHi = 0U;
  c6_info[8].mFileTimeLo = 0U;
  c6_info[8].mFileTimeHi = 0U;
  c6_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[9].name = "eml_index_class";
  c6_info[9].dominantType = "";
  c6_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[9].fileTimeLo = 1323181378U;
  c6_info[9].fileTimeHi = 0U;
  c6_info[9].mFileTimeLo = 0U;
  c6_info[9].mFileTimeHi = 0U;
  c6_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[10].name = "eml_index_minus";
  c6_info[10].dominantType = "double";
  c6_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c6_info[10].fileTimeLo = 1286836778U;
  c6_info[10].fileTimeHi = 0U;
  c6_info[10].mFileTimeLo = 0U;
  c6_info[10].mFileTimeHi = 0U;
  c6_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c6_info[11].name = "eml_index_class";
  c6_info[11].dominantType = "";
  c6_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[11].fileTimeLo = 1323181378U;
  c6_info[11].fileTimeHi = 0U;
  c6_info[11].mFileTimeLo = 0U;
  c6_info[11].mFileTimeHi = 0U;
  c6_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[12].name = "eml_index_times";
  c6_info[12].dominantType = "coder.internal.indexInt";
  c6_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c6_info[12].fileTimeLo = 1286836780U;
  c6_info[12].fileTimeHi = 0U;
  c6_info[12].mFileTimeLo = 0U;
  c6_info[12].mFileTimeHi = 0U;
  c6_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c6_info[13].name = "eml_index_class";
  c6_info[13].dominantType = "";
  c6_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[13].fileTimeLo = 1323181378U;
  c6_info[13].fileTimeHi = 0U;
  c6_info[13].mFileTimeLo = 0U;
  c6_info[13].mFileTimeHi = 0U;
  c6_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[14].name = "eml_index_plus";
  c6_info[14].dominantType = "coder.internal.indexInt";
  c6_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c6_info[14].fileTimeLo = 1286836778U;
  c6_info[14].fileTimeHi = 0U;
  c6_info[14].mFileTimeLo = 0U;
  c6_info[14].mFileTimeHi = 0U;
  c6_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c6_info[15].name = "eml_index_class";
  c6_info[15].dominantType = "";
  c6_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[15].fileTimeLo = 1323181378U;
  c6_info[15].fileTimeHi = 0U;
  c6_info[15].mFileTimeLo = 0U;
  c6_info[15].mFileTimeHi = 0U;
  c6_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[16].name = "eml_int_forloop_overflow_check";
  c6_info[16].dominantType = "";
  c6_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c6_info[16].fileTimeLo = 1346528340U;
  c6_info[16].fileTimeHi = 0U;
  c6_info[16].mFileTimeLo = 0U;
  c6_info[16].mFileTimeHi = 0U;
  c6_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c6_info[17].name = "intmax";
  c6_info[17].dominantType = "char";
  c6_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c6_info[17].fileTimeLo = 1311273316U;
  c6_info[17].fileTimeHi = 0U;
  c6_info[17].mFileTimeLo = 0U;
  c6_info[17].mFileTimeHi = 0U;
  c6_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[18].name = "abs";
  c6_info[18].dominantType = "double";
  c6_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c6_info[18].fileTimeLo = 1343848366U;
  c6_info[18].fileTimeHi = 0U;
  c6_info[18].mFileTimeLo = 0U;
  c6_info[18].mFileTimeHi = 0U;
  c6_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c6_info[19].name = "eml_scalar_abs";
  c6_info[19].dominantType = "double";
  c6_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c6_info[19].fileTimeLo = 1286836712U;
  c6_info[19].fileTimeHi = 0U;
  c6_info[19].mFileTimeLo = 0U;
  c6_info[19].mFileTimeHi = 0U;
  c6_info[20].context = "";
  c6_info[20].name = "mrdivide";
  c6_info[20].dominantType = "double";
  c6_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c6_info[20].fileTimeLo = 1357962348U;
  c6_info[20].fileTimeHi = 0U;
  c6_info[20].mFileTimeLo = 1319744366U;
  c6_info[20].mFileTimeHi = 0U;
  c6_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c6_info[21].name = "rdivide";
  c6_info[21].dominantType = "double";
  c6_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c6_info[21].fileTimeLo = 1346528388U;
  c6_info[21].fileTimeHi = 0U;
  c6_info[21].mFileTimeLo = 0U;
  c6_info[21].mFileTimeHi = 0U;
  c6_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c6_info[22].name = "eml_scalexp_compatible";
  c6_info[22].dominantType = "double";
  c6_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c6_info[22].fileTimeLo = 1286836796U;
  c6_info[22].fileTimeHi = 0U;
  c6_info[22].mFileTimeLo = 0U;
  c6_info[22].mFileTimeHi = 0U;
  c6_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c6_info[23].name = "eml_div";
  c6_info[23].dominantType = "double";
  c6_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c6_info[23].fileTimeLo = 1313365810U;
  c6_info[23].fileTimeHi = 0U;
  c6_info[23].mFileTimeLo = 0U;
  c6_info[23].mFileTimeHi = 0U;
  c6_info[24].context = "";
  c6_info[24].name = "cross";
  c6_info[24].dominantType = "double";
  c6_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c6_info[24].fileTimeLo = 1286836842U;
  c6_info[24].fileTimeHi = 0U;
  c6_info[24].mFileTimeLo = 0U;
  c6_info[24].mFileTimeHi = 0U;
  c6_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c6_info[25].name = "mtimes";
  c6_info[25].dominantType = "double";
  c6_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[25].fileTimeLo = 1289530492U;
  c6_info[25].fileTimeHi = 0U;
  c6_info[25].mFileTimeLo = 0U;
  c6_info[25].mFileTimeHi = 0U;
  c6_info[26].context = "";
  c6_info[26].name = "mtimes";
  c6_info[26].dominantType = "double";
  c6_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[26].fileTimeLo = 1289530492U;
  c6_info[26].fileTimeHi = 0U;
  c6_info[26].mFileTimeLo = 0U;
  c6_info[26].mFileTimeHi = 0U;
  c6_info[27].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[27].name = "eml_index_class";
  c6_info[27].dominantType = "";
  c6_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[27].fileTimeLo = 1323181378U;
  c6_info[27].fileTimeHi = 0U;
  c6_info[27].mFileTimeLo = 0U;
  c6_info[27].mFileTimeHi = 0U;
  c6_info[28].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[28].name = "eml_scalar_eg";
  c6_info[28].dominantType = "double";
  c6_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[28].fileTimeLo = 1286836796U;
  c6_info[28].fileTimeHi = 0U;
  c6_info[28].mFileTimeLo = 0U;
  c6_info[28].mFileTimeHi = 0U;
  c6_info[29].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[29].name = "eml_xgemm";
  c6_info[29].dominantType = "char";
  c6_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c6_info[29].fileTimeLo = 1299091172U;
  c6_info[29].fileTimeHi = 0U;
  c6_info[29].mFileTimeLo = 0U;
  c6_info[29].mFileTimeHi = 0U;
  c6_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c6_info[30].name = "eml_blas_inline";
  c6_info[30].dominantType = "";
  c6_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c6_info[30].fileTimeLo = 1299091168U;
  c6_info[30].fileTimeHi = 0U;
  c6_info[30].mFileTimeLo = 0U;
  c6_info[30].mFileTimeHi = 0U;
  c6_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c6_info[31].name = "mtimes";
  c6_info[31].dominantType = "double";
  c6_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[31].fileTimeLo = 1289530492U;
  c6_info[31].fileTimeHi = 0U;
  c6_info[31].mFileTimeLo = 0U;
  c6_info[31].mFileTimeHi = 0U;
  c6_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[32].name = "eml_index_class";
  c6_info[32].dominantType = "";
  c6_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[32].fileTimeLo = 1323181378U;
  c6_info[32].fileTimeHi = 0U;
  c6_info[32].mFileTimeLo = 0U;
  c6_info[32].mFileTimeHi = 0U;
  c6_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[33].name = "eml_scalar_eg";
  c6_info[33].dominantType = "double";
  c6_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[33].fileTimeLo = 1286836796U;
  c6_info[33].fileTimeHi = 0U;
  c6_info[33].mFileTimeLo = 0U;
  c6_info[33].mFileTimeHi = 0U;
  c6_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[34].name = "eml_refblas_xgemm";
  c6_info[34].dominantType = "char";
  c6_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c6_info[34].fileTimeLo = 1299091174U;
  c6_info[34].fileTimeHi = 0U;
  c6_info[34].mFileTimeLo = 0U;
  c6_info[34].mFileTimeHi = 0U;
  c6_info[35].context = "";
  c6_info[35].name = "mpower";
  c6_info[35].dominantType = "double";
  c6_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c6_info[35].fileTimeLo = 1286836842U;
  c6_info[35].fileTimeHi = 0U;
  c6_info[35].mFileTimeLo = 0U;
  c6_info[35].mFileTimeHi = 0U;
  c6_info[36].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c6_info[36].name = "power";
  c6_info[36].dominantType = "double";
  c6_info[36].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c6_info[36].fileTimeLo = 1348209930U;
  c6_info[36].fileTimeHi = 0U;
  c6_info[36].mFileTimeLo = 0U;
  c6_info[36].mFileTimeHi = 0U;
  c6_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c6_info[37].name = "eml_scalar_eg";
  c6_info[37].dominantType = "double";
  c6_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[37].fileTimeLo = 1286836796U;
  c6_info[37].fileTimeHi = 0U;
  c6_info[37].mFileTimeLo = 0U;
  c6_info[37].mFileTimeHi = 0U;
  c6_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c6_info[38].name = "eml_scalexp_alloc";
  c6_info[38].dominantType = "double";
  c6_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c6_info[38].fileTimeLo = 1352435660U;
  c6_info[38].fileTimeHi = 0U;
  c6_info[38].mFileTimeLo = 0U;
  c6_info[38].mFileTimeHi = 0U;
  c6_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c6_info[39].name = "floor";
  c6_info[39].dominantType = "double";
  c6_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c6_info[39].fileTimeLo = 1343848380U;
  c6_info[39].fileTimeHi = 0U;
  c6_info[39].mFileTimeLo = 0U;
  c6_info[39].mFileTimeHi = 0U;
  c6_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c6_info[40].name = "eml_scalar_floor";
  c6_info[40].dominantType = "double";
  c6_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c6_info[40].fileTimeLo = 1286836726U;
  c6_info[40].fileTimeHi = 0U;
  c6_info[40].mFileTimeLo = 0U;
  c6_info[40].mFileTimeHi = 0U;
  c6_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c6_info[41].name = "eml_scalar_eg";
  c6_info[41].dominantType = "double";
  c6_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[41].fileTimeLo = 1286836796U;
  c6_info[41].fileTimeHi = 0U;
  c6_info[41].mFileTimeLo = 0U;
  c6_info[41].mFileTimeHi = 0U;
  c6_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c6_info[42].name = "mtimes";
  c6_info[42].dominantType = "double";
  c6_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[42].fileTimeLo = 1289530492U;
  c6_info[42].fileTimeHi = 0U;
  c6_info[42].mFileTimeLo = 0U;
  c6_info[42].mFileTimeHi = 0U;
  c6_info[43].context = "";
  c6_info[43].name = "eye";
  c6_info[43].dominantType = "double";
  c6_info[43].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m";
  c6_info[43].fileTimeLo = 1286836688U;
  c6_info[43].fileTimeHi = 0U;
  c6_info[43].mFileTimeLo = 0U;
  c6_info[43].mFileTimeHi = 0U;
  c6_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c6_info[44].name = "eml_assert_valid_size_arg";
  c6_info[44].dominantType = "double";
  c6_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c6_info[44].fileTimeLo = 1286836694U;
  c6_info[44].fileTimeHi = 0U;
  c6_info[44].mFileTimeLo = 0U;
  c6_info[44].mFileTimeHi = 0U;
  c6_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c6_info[45].name = "isinf";
  c6_info[45].dominantType = "double";
  c6_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c6_info[45].fileTimeLo = 1286836760U;
  c6_info[45].fileTimeHi = 0U;
  c6_info[45].mFileTimeLo = 0U;
  c6_info[45].mFileTimeHi = 0U;
  c6_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c6_info[46].name = "mtimes";
  c6_info[46].dominantType = "double";
  c6_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[46].fileTimeLo = 1289530492U;
  c6_info[46].fileTimeHi = 0U;
  c6_info[46].mFileTimeLo = 0U;
  c6_info[46].mFileTimeHi = 0U;
  c6_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c6_info[47].name = "eml_index_class";
  c6_info[47].dominantType = "";
  c6_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[47].fileTimeLo = 1323181378U;
  c6_info[47].fileTimeHi = 0U;
  c6_info[47].mFileTimeLo = 0U;
  c6_info[47].mFileTimeHi = 0U;
  c6_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c6_info[48].name = "intmax";
  c6_info[48].dominantType = "char";
  c6_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c6_info[48].fileTimeLo = 1311273316U;
  c6_info[48].fileTimeHi = 0U;
  c6_info[48].mFileTimeLo = 0U;
  c6_info[48].mFileTimeHi = 0U;
  c6_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c6_info[49].name = "eml_is_float_class";
  c6_info[49].dominantType = "char";
  c6_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c6_info[49].fileTimeLo = 1286836782U;
  c6_info[49].fileTimeHi = 0U;
  c6_info[49].mFileTimeLo = 0U;
  c6_info[49].mFileTimeHi = 0U;
  c6_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c6_info[50].name = "min";
  c6_info[50].dominantType = "double";
  c6_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c6_info[50].fileTimeLo = 1311273318U;
  c6_info[50].fileTimeHi = 0U;
  c6_info[50].mFileTimeLo = 0U;
  c6_info[50].mFileTimeHi = 0U;
  c6_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c6_info[51].name = "eml_min_or_max";
  c6_info[51].dominantType = "char";
  c6_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c6_info[51].fileTimeLo = 1334089490U;
  c6_info[51].fileTimeHi = 0U;
  c6_info[51].mFileTimeLo = 0U;
  c6_info[51].mFileTimeHi = 0U;
  c6_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c6_info[52].name = "eml_scalar_eg";
  c6_info[52].dominantType = "double";
  c6_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[52].fileTimeLo = 1286836796U;
  c6_info[52].fileTimeHi = 0U;
  c6_info[52].mFileTimeLo = 0U;
  c6_info[52].mFileTimeHi = 0U;
  c6_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c6_info[53].name = "eml_scalexp_alloc";
  c6_info[53].dominantType = "double";
  c6_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c6_info[53].fileTimeLo = 1352435660U;
  c6_info[53].fileTimeHi = 0U;
  c6_info[53].mFileTimeLo = 0U;
  c6_info[53].mFileTimeHi = 0U;
  c6_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c6_info[54].name = "eml_index_class";
  c6_info[54].dominantType = "";
  c6_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[54].fileTimeLo = 1323181378U;
  c6_info[54].fileTimeHi = 0U;
  c6_info[54].mFileTimeLo = 0U;
  c6_info[54].mFileTimeHi = 0U;
  c6_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c6_info[55].name = "eml_scalar_eg";
  c6_info[55].dominantType = "double";
  c6_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[55].fileTimeLo = 1286836796U;
  c6_info[55].fileTimeHi = 0U;
  c6_info[55].mFileTimeLo = 0U;
  c6_info[55].mFileTimeHi = 0U;
  c6_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c6_info[56].name = "eml_index_class";
  c6_info[56].dominantType = "";
  c6_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[56].fileTimeLo = 1323181378U;
  c6_info[56].fileTimeHi = 0U;
  c6_info[56].mFileTimeLo = 0U;
  c6_info[56].mFileTimeHi = 0U;
  c6_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c6_info[57].name = "eml_int_forloop_overflow_check";
  c6_info[57].dominantType = "";
  c6_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c6_info[57].fileTimeLo = 1346528340U;
  c6_info[57].fileTimeHi = 0U;
  c6_info[57].mFileTimeLo = 0U;
  c6_info[57].mFileTimeHi = 0U;
  c6_info[58].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[58].name = "eml_xdotu";
  c6_info[58].dominantType = "double";
  c6_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c6_info[58].fileTimeLo = 1299091172U;
  c6_info[58].fileTimeHi = 0U;
  c6_info[58].mFileTimeLo = 0U;
  c6_info[58].mFileTimeHi = 0U;
  c6_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c6_info[59].name = "eml_blas_inline";
  c6_info[59].dominantType = "";
  c6_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c6_info[59].fileTimeLo = 1299091168U;
  c6_info[59].fileTimeHi = 0U;
  c6_info[59].mFileTimeLo = 0U;
  c6_info[59].mFileTimeHi = 0U;
  c6_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c6_info[60].name = "eml_xdot";
  c6_info[60].dominantType = "double";
  c6_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c6_info[60].fileTimeLo = 1299091172U;
  c6_info[60].fileTimeHi = 0U;
  c6_info[60].mFileTimeLo = 0U;
  c6_info[60].mFileTimeHi = 0U;
  c6_info[61].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c6_info[61].name = "eml_blas_inline";
  c6_info[61].dominantType = "";
  c6_info[61].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c6_info[61].fileTimeLo = 1299091168U;
  c6_info[61].fileTimeHi = 0U;
  c6_info[61].mFileTimeLo = 0U;
  c6_info[61].mFileTimeHi = 0U;
  c6_info[62].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c6_info[62].name = "eml_index_class";
  c6_info[62].dominantType = "";
  c6_info[62].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[62].fileTimeLo = 1323181378U;
  c6_info[62].fileTimeHi = 0U;
  c6_info[62].mFileTimeLo = 0U;
  c6_info[62].mFileTimeHi = 0U;
  c6_info[63].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c6_info[63].name = "eml_refblas_xdot";
  c6_info[63].dominantType = "double";
  c6_info[63].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c6_info[63].fileTimeLo = 1299091172U;
  c6_info[63].fileTimeHi = 0U;
  c6_info[63].mFileTimeLo = 0U;
  c6_info[63].mFileTimeHi = 0U;
}

static real_T c6_norm(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
                      *chartInstance, real_T c6_x[3])
{
  real_T c6_y;
  real_T c6_scale;
  int32_T c6_k;
  int32_T c6_b_k;
  real_T c6_b_x;
  real_T c6_c_x;
  real_T c6_absxk;
  real_T c6_t;
  c6_y = 0.0;
  c6_scale = 2.2250738585072014E-308;
  for (c6_k = 1; c6_k < 4; c6_k++) {
    c6_b_k = c6_k;
    c6_b_x = c6_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c6_b_k), 1, 3, 1, 0) - 1];
    c6_c_x = c6_b_x;
    c6_absxk = muDoubleScalarAbs(c6_c_x);
    if (c6_absxk > c6_scale) {
      c6_t = c6_scale / c6_absxk;
      c6_y = 1.0 + c6_y * c6_t * c6_t;
      c6_scale = c6_absxk;
    } else {
      c6_t = c6_absxk / c6_scale;
      c6_y += c6_t * c6_t;
    }
  }

  return c6_scale * muDoubleScalarSqrt(c6_y);
}

static void c6_cross(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
                     *chartInstance, real_T c6_a[3], real_T c6_b[3], real_T
                     c6_c[3])
{
  real_T c6_b_a;
  real_T c6_b_b;
  real_T c6_y;
  real_T c6_c_a;
  real_T c6_c_b;
  real_T c6_b_y;
  real_T c6_c1;
  real_T c6_d_a;
  real_T c6_d_b;
  real_T c6_c_y;
  real_T c6_e_a;
  real_T c6_e_b;
  real_T c6_d_y;
  real_T c6_c2;
  real_T c6_f_a;
  real_T c6_f_b;
  real_T c6_e_y;
  real_T c6_g_a;
  real_T c6_g_b;
  real_T c6_f_y;
  real_T c6_c3;
  c6_b_a = c6_a[1];
  c6_b_b = c6_b[2];
  c6_y = c6_b_a * c6_b_b;
  c6_c_a = c6_a[2];
  c6_c_b = c6_b[1];
  c6_b_y = c6_c_a * c6_c_b;
  c6_c1 = c6_y - c6_b_y;
  c6_d_a = c6_a[2];
  c6_d_b = c6_b[0];
  c6_c_y = c6_d_a * c6_d_b;
  c6_e_a = c6_a[0];
  c6_e_b = c6_b[2];
  c6_d_y = c6_e_a * c6_e_b;
  c6_c2 = c6_c_y - c6_d_y;
  c6_f_a = c6_a[0];
  c6_f_b = c6_b[1];
  c6_e_y = c6_f_a * c6_f_b;
  c6_g_a = c6_a[1];
  c6_g_b = c6_b[0];
  c6_f_y = c6_g_a * c6_g_b;
  c6_c3 = c6_e_y - c6_f_y;
  c6_c[0] = c6_c1;
  c6_c[1] = c6_c2;
  c6_c[2] = c6_c3;
}

static void c6_eml_scalar_eg(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
  *chartInstance)
{
}

static real_T c6_mpower(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
  *chartInstance, real_T c6_a)
{
  real_T c6_b_a;
  real_T c6_c_a;
  real_T c6_ak;
  real_T c6_d_a;
  real_T c6_e_a;
  real_T c6_b;
  c6_b_a = c6_a;
  c6_c_a = c6_b_a;
  c6_b_eml_scalar_eg(chartInstance);
  c6_ak = c6_c_a;
  c6_d_a = c6_ak;
  c6_b_eml_scalar_eg(chartInstance);
  c6_e_a = c6_d_a;
  c6_b = c6_d_a;
  return c6_e_a * c6_b;
}

static void c6_b_eml_scalar_eg(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
  *chartInstance)
{
}

static void c6_c_eml_scalar_eg(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct
  *chartInstance)
{
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance;
  chartInstance = (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *)
    chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static int32_T c6_e_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i108;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i108, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i108;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance;
  chartInstance = (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *)
    chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent),
    &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static uint8_T c6_f_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_b_is_active_c6_Tetraedro_model_sem_sim_com_FK, const char_T
   *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_is_active_c6_Tetraedro_model_sem_sim_com_FK), &c6_thisId);
  sf_mex_destroy(&c6_b_is_active_c6_Tetraedro_model_sem_sim_com_FK);
  return c6_y;
}

static uint8_T c6_g_emlrt_marshallIn
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance, const
   mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u0, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void init_dsm_address_info
  (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance)
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

void sf_c6_Tetraedro_model_sem_sim_com_FK_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3699584743U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1125978218U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3923887933U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1504849711U);
}

mxArray *sf_c6_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("1NxDvSQpsHZkTPZYlcwpoE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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

mxArray *sf_c6_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c6_Tetraedro_model_sem_sim_com_FK
  (void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"A\",},{M[1],M[11],T\"R\",},{M[8],M[0],T\"is_active_c6_Tetraedro_model_sem_sim_com_FK\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_Tetraedro_model_sem_sim_com_FK_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance;
    chartInstance = (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Tetraedro_model_sem_sim_com_FKMachineNumber_,
           6,
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
            (_Tetraedro_model_sem_sim_com_FKMachineNumber_,
             chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,
             _Tetraedro_model_sem_sim_com_FKMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _Tetraedro_model_sem_sim_com_FKMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"sig_ace");
          _SFD_SET_DATA_PROPS(1,2,0,1,"A");
          _SFD_SET_DATA_PROPS(2,1,1,0,"mag_rec");
          _SFD_SET_DATA_PROPS(3,1,1,0,"mag_ref");
          _SFD_SET_DATA_PROPS(4,1,1,0,"acc_ref");
          _SFD_SET_DATA_PROPS(5,1,1,0,"acc_rec");
          _SFD_SET_DATA_PROPS(6,1,1,0,"sig_gir");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1496);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)
            c6_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)
            c6_sf_marshallIn);
        }

        {
          real_T *c6_sig_ace;
          real_T *c6_sig_gir;
          real_T (*c6_A)[9];
          real_T (*c6_mag_rec)[3];
          real_T (*c6_mag_ref)[3];
          real_T (*c6_acc_ref)[3];
          real_T (*c6_acc_rec)[3];
          real_T (*c6_R)[9];
          c6_R = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
          c6_sig_gir = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c6_acc_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
          c6_acc_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c6_mag_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c6_mag_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c6_A = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
          c6_sig_ace = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c6_sig_ace);
          _SFD_SET_DATA_VALUE_PTR(1U, *c6_A);
          _SFD_SET_DATA_VALUE_PTR(2U, *c6_mag_rec);
          _SFD_SET_DATA_VALUE_PTR(3U, *c6_mag_ref);
          _SFD_SET_DATA_VALUE_PTR(4U, *c6_acc_ref);
          _SFD_SET_DATA_VALUE_PTR(5U, *c6_acc_rec);
          _SFD_SET_DATA_VALUE_PTR(6U, c6_sig_gir);
          _SFD_SET_DATA_VALUE_PTR(7U, *c6_R);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _Tetraedro_model_sem_sim_com_FKMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "kOFWelOWEMGZP3kdf0kxjE";
}

static void sf_opaque_initialize_c6_Tetraedro_model_sem_sim_com_FK(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c6_Tetraedro_model_sem_sim_com_FK
    ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*) chartInstanceVar);
  initialize_c6_Tetraedro_model_sem_sim_com_FK
    ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c6_Tetraedro_model_sem_sim_com_FK(void
  *chartInstanceVar)
{
  enable_c6_Tetraedro_model_sem_sim_com_FK
    ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c6_Tetraedro_model_sem_sim_com_FK(void
  *chartInstanceVar)
{
  disable_c6_Tetraedro_model_sem_sim_com_FK
    ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c6_Tetraedro_model_sem_sim_com_FK(void
  *chartInstanceVar)
{
  sf_c6_Tetraedro_model_sem_sim_com_FK
    ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*) chartInstanceVar);
}

extern const mxArray*
  sf_internal_get_sim_state_c6_Tetraedro_model_sem_sim_com_FK(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c6_Tetraedro_model_sem_sim_com_FK
    ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*)
     chartInfo->chartInstance);        /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_Tetraedro_model_sem_sim_com_FK();/* state var info */
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

extern void sf_internal_set_sim_state_c6_Tetraedro_model_sem_sim_com_FK
  (SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_Tetraedro_model_sem_sim_com_FK();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c6_Tetraedro_model_sem_sim_com_FK
    ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*)
     chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c6_Tetraedro_model_sem_sim_com_FK
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c6_Tetraedro_model_sem_sim_com_FK(S);
}

static void sf_opaque_set_sim_state_c6_Tetraedro_model_sem_sim_com_FK(SimStruct*
  S, const mxArray *st)
{
  sf_internal_set_sim_state_c6_Tetraedro_model_sem_sim_com_FK(S, st);
}

static void sf_opaque_terminate_c6_Tetraedro_model_sem_sim_com_FK(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Tetraedro_model_sem_sim_com_FK_optimization_info();
    }

    finalize_c6_Tetraedro_model_sem_sim_com_FK
      ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_Tetraedro_model_sem_sim_com_FK
    ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_Tetraedro_model_sem_sim_com_FK(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c6_Tetraedro_model_sem_sim_com_FK
      ((SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c6_Tetraedro_model_sem_sim_com_FK(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Tetraedro_model_sem_sim_com_FK_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,6,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,6,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,6);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,2);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1527590581U));
  ssSetChecksum1(S,(3660722491U));
  ssSetChecksum2(S,(2559948480U));
  ssSetChecksum3(S,(149599832U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c6_Tetraedro_model_sem_sim_com_FK(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c6_Tetraedro_model_sem_sim_com_FK(SimStruct *S)
{
  SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *chartInstance;
  chartInstance = (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct *)utMalloc
    (sizeof(SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc6_Tetraedro_model_sem_sim_com_FKInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c6_Tetraedro_model_sem_sim_com_FK;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c6_Tetraedro_model_sem_sim_com_FK;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c6_Tetraedro_model_sem_sim_com_FK;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c6_Tetraedro_model_sem_sim_com_FK;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c6_Tetraedro_model_sem_sim_com_FK;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c6_Tetraedro_model_sem_sim_com_FK;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c6_Tetraedro_model_sem_sim_com_FK;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c6_Tetraedro_model_sem_sim_com_FK;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_Tetraedro_model_sem_sim_com_FK;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_Tetraedro_model_sem_sim_com_FK;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c6_Tetraedro_model_sem_sim_com_FK;
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

void c6_Tetraedro_model_sem_sim_com_FK_method_dispatcher(SimStruct *S, int_T
  method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_Tetraedro_model_sem_sim_com_FK(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_Tetraedro_model_sem_sim_com_FK(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_Tetraedro_model_sem_sim_com_FK(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_Tetraedro_model_sem_sim_com_FK_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
