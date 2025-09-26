/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Tetraedro_model_sem_sim_com_FK_heur_sfun.h"
#include "c7_Tetraedro_model_sem_sim_com_FK_heur.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Tetraedro_model_sem_sim_com_FK_heur_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c7_debug_family_names[17] = { "mag_x", "mag_y", "mag_z",
  "acc_x", "acc_y", "acc_z", "gyro_placa_1", "gyro_placa_2", "gyro_placa_3",
  "gyro_placa_4", "nargin", "nargout", "entrada_TETRA", "mag_TETRA", "acc_TETRA",
  "gyro_TETRA", "Timer_TETRA" };

/* Function Declarations */
static void initialize_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void initialize_params_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void enable_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void disable_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void c7_update_debugger_state_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void set_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_st);
static void finalize_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void sf_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void initSimStructsc7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void registerMessagesc7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber);
static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData);
static real_T c7_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_Timer_TETRA, const char_T *c7_identifier);
static real_T c7_b_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_c_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_gyro_TETRA, const char_T *c7_identifier, real_T c7_y[4]);
static void c7_d_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[4]);
static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_e_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_acc_TETRA, const char_T *c7_identifier, real_T c7_y[3]);
static void c7_f_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[3]);
static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static const mxArray *c7_e_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static int32_T c7_g_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static uint8_T c7_h_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_b_is_active_c7_Tetraedro_model_sem_sim_com_FK_heur, const char_T *
   c7_identifier);
static uint8_T c7_i_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void init_dsm_address_info
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  chartInstance->c7_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c7_is_active_c7_Tetraedro_model_sem_sim_com_FK_heur = 0U;
}

static void initialize_params_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void enable_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c7_update_debugger_state_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  const mxArray *c7_st;
  const mxArray *c7_y = NULL;
  real_T c7_hoistedGlobal;
  real_T c7_u;
  const mxArray *c7_b_y = NULL;
  int32_T c7_i0;
  real_T c7_b_u[3];
  const mxArray *c7_c_y = NULL;
  int32_T c7_i1;
  real_T c7_c_u[4];
  const mxArray *c7_d_y = NULL;
  int32_T c7_i2;
  real_T c7_d_u[3];
  const mxArray *c7_e_y = NULL;
  uint8_T c7_b_hoistedGlobal;
  uint8_T c7_e_u;
  const mxArray *c7_f_y = NULL;
  real_T *c7_Timer_TETRA;
  real_T (*c7_mag_TETRA)[3];
  real_T (*c7_gyro_TETRA)[4];
  real_T (*c7_acc_TETRA)[3];
  c7_Timer_TETRA = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c7_gyro_TETRA = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 3);
  c7_acc_TETRA = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c7_mag_TETRA = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_st = NULL;
  c7_st = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_createcellarray(5), FALSE);
  c7_hoistedGlobal = *c7_Timer_TETRA;
  c7_u = c7_hoistedGlobal;
  c7_b_y = NULL;
  sf_mex_assign(&c7_b_y, sf_mex_create("y", &c7_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c7_y, 0, c7_b_y);
  for (c7_i0 = 0; c7_i0 < 3; c7_i0++) {
    c7_b_u[c7_i0] = (*c7_acc_TETRA)[c7_i0];
  }

  c7_c_y = NULL;
  sf_mex_assign(&c7_c_y, sf_mex_create("y", c7_b_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c7_y, 1, c7_c_y);
  for (c7_i1 = 0; c7_i1 < 4; c7_i1++) {
    c7_c_u[c7_i1] = (*c7_gyro_TETRA)[c7_i1];
  }

  c7_d_y = NULL;
  sf_mex_assign(&c7_d_y, sf_mex_create("y", c7_c_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_setcell(c7_y, 2, c7_d_y);
  for (c7_i2 = 0; c7_i2 < 3; c7_i2++) {
    c7_d_u[c7_i2] = (*c7_mag_TETRA)[c7_i2];
  }

  c7_e_y = NULL;
  sf_mex_assign(&c7_e_y, sf_mex_create("y", c7_d_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c7_y, 3, c7_e_y);
  c7_b_hoistedGlobal =
    chartInstance->c7_is_active_c7_Tetraedro_model_sem_sim_com_FK_heur;
  c7_e_u = c7_b_hoistedGlobal;
  c7_f_y = NULL;
  sf_mex_assign(&c7_f_y, sf_mex_create("y", &c7_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c7_y, 4, c7_f_y);
  sf_mex_assign(&c7_st, c7_y, FALSE);
  return c7_st;
}

static void set_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_st)
{
  const mxArray *c7_u;
  real_T c7_dv0[3];
  int32_T c7_i3;
  real_T c7_dv1[4];
  int32_T c7_i4;
  real_T c7_dv2[3];
  int32_T c7_i5;
  real_T *c7_Timer_TETRA;
  real_T (*c7_acc_TETRA)[3];
  real_T (*c7_gyro_TETRA)[4];
  real_T (*c7_mag_TETRA)[3];
  c7_Timer_TETRA = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c7_gyro_TETRA = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 3);
  c7_acc_TETRA = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c7_mag_TETRA = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c7_doneDoubleBufferReInit = TRUE;
  c7_u = sf_mex_dup(c7_st);
  *c7_Timer_TETRA = c7_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c7_u, 0)), "Timer_TETRA");
  c7_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 1)),
                        "acc_TETRA", c7_dv0);
  for (c7_i3 = 0; c7_i3 < 3; c7_i3++) {
    (*c7_acc_TETRA)[c7_i3] = c7_dv0[c7_i3];
  }

  c7_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 2)),
                        "gyro_TETRA", c7_dv1);
  for (c7_i4 = 0; c7_i4 < 4; c7_i4++) {
    (*c7_gyro_TETRA)[c7_i4] = c7_dv1[c7_i4];
  }

  c7_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 3)),
                        "mag_TETRA", c7_dv2);
  for (c7_i5 = 0; c7_i5 < 3; c7_i5++) {
    (*c7_mag_TETRA)[c7_i5] = c7_dv2[c7_i5];
  }

  chartInstance->c7_is_active_c7_Tetraedro_model_sem_sim_com_FK_heur =
    c7_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 4)),
    "is_active_c7_Tetraedro_model_sem_sim_com_FK_heur");
  sf_mex_destroy(&c7_u);
  c7_update_debugger_state_c7_Tetraedro_model_sem_sim_com_FK_heur(chartInstance);
  sf_mex_destroy(&c7_st);
}

static void finalize_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void sf_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  int32_T c7_i6;
  int32_T c7_i7;
  int32_T c7_i8;
  int32_T c7_i9;
  int32_T c7_i10;
  real_T c7_entrada_TETRA[15];
  uint32_T c7_debug_family_var_map[17];
  real_T c7_mag_x;
  real_T c7_mag_y;
  real_T c7_mag_z;
  real_T c7_acc_x;
  real_T c7_acc_y;
  real_T c7_acc_z;
  real_T c7_gyro_placa_1;
  real_T c7_gyro_placa_2;
  real_T c7_gyro_placa_3;
  real_T c7_gyro_placa_4;
  real_T c7_nargin = 1.0;
  real_T c7_nargout = 4.0;
  real_T c7_mag_TETRA[3];
  real_T c7_acc_TETRA[3];
  real_T c7_gyro_TETRA[4];
  real_T c7_Timer_TETRA;
  int32_T c7_i11;
  int32_T c7_i12;
  int32_T c7_i13;
  real_T c7_b_mag_x[3];
  int32_T c7_i14;
  real_T c7_b_acc_x[3];
  int32_T c7_i15;
  real_T c7_b_gyro_placa_1[4];
  int32_T c7_i16;
  int32_T c7_i17;
  int32_T c7_i18;
  int32_T c7_i19;
  real_T *c7_b_Timer_TETRA;
  real_T (*c7_b_mag_TETRA)[3];
  real_T (*c7_b_acc_TETRA)[3];
  real_T (*c7_b_gyro_TETRA)[4];
  real_T (*c7_b_entrada_TETRA)[15];
  c7_b_Timer_TETRA = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c7_b_gyro_TETRA = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 3);
  c7_b_acc_TETRA = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c7_b_entrada_TETRA = (real_T (*)[15])ssGetInputPortSignal(chartInstance->S, 0);
  c7_b_mag_TETRA = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 6U, chartInstance->c7_sfEvent);
  for (c7_i6 = 0; c7_i6 < 3; c7_i6++) {
    _SFD_DATA_RANGE_CHECK((*c7_b_mag_TETRA)[c7_i6], 0U);
  }

  for (c7_i7 = 0; c7_i7 < 15; c7_i7++) {
    _SFD_DATA_RANGE_CHECK((*c7_b_entrada_TETRA)[c7_i7], 1U);
  }

  for (c7_i8 = 0; c7_i8 < 3; c7_i8++) {
    _SFD_DATA_RANGE_CHECK((*c7_b_acc_TETRA)[c7_i8], 2U);
  }

  for (c7_i9 = 0; c7_i9 < 4; c7_i9++) {
    _SFD_DATA_RANGE_CHECK((*c7_b_gyro_TETRA)[c7_i9], 3U);
  }

  _SFD_DATA_RANGE_CHECK(*c7_b_Timer_TETRA, 4U);
  chartInstance->c7_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 6U, chartInstance->c7_sfEvent);
  for (c7_i10 = 0; c7_i10 < 15; c7_i10++) {
    c7_entrada_TETRA[c7_i10] = (*c7_b_entrada_TETRA)[c7_i10];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 17U, 17U, c7_debug_family_names,
    c7_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_mag_x, 0U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_mag_y, 1U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_mag_z, 2U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_acc_x, 3U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_acc_y, 4U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_acc_z, 5U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_gyro_placa_1, 6U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_gyro_placa_2, 7U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_gyro_placa_3, 8U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_gyro_placa_4, 9U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargin, 10U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargout, 11U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c7_entrada_TETRA, 12U, c7_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_mag_TETRA, 13U, c7_c_sf_marshallOut,
    c7_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_acc_TETRA, 14U, c7_c_sf_marshallOut,
    c7_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_gyro_TETRA, 15U, c7_b_sf_marshallOut,
    c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_Timer_TETRA, 16U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 4);
  for (c7_i11 = 0; c7_i11 < 3; c7_i11++) {
    c7_mag_TETRA[c7_i11] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 5);
  for (c7_i12 = 0; c7_i12 < 3; c7_i12++) {
    c7_acc_TETRA[c7_i12] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 6);
  for (c7_i13 = 0; c7_i13 < 4; c7_i13++) {
    c7_gyro_TETRA[c7_i13] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 8);
  c7_mag_x = c7_entrada_TETRA[0];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 9);
  c7_mag_y = c7_entrada_TETRA[1];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 10);
  c7_mag_z = c7_entrada_TETRA[2];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 12);
  c7_acc_x = c7_entrada_TETRA[3];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 13);
  c7_acc_y = c7_entrada_TETRA[4];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 14);
  c7_acc_z = c7_entrada_TETRA[5];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 16);
  c7_gyro_placa_1 = c7_entrada_TETRA[6];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 17);
  c7_gyro_placa_2 = c7_entrada_TETRA[8];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 18);
  c7_gyro_placa_3 = c7_entrada_TETRA[10];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 19);
  c7_gyro_placa_4 = c7_entrada_TETRA[12];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 21);
  c7_b_mag_x[0] = c7_mag_x;
  c7_b_mag_x[1] = c7_mag_y;
  c7_b_mag_x[2] = c7_mag_z;
  for (c7_i14 = 0; c7_i14 < 3; c7_i14++) {
    c7_mag_TETRA[c7_i14] = c7_b_mag_x[c7_i14];
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 22);
  c7_b_acc_x[0] = c7_acc_x;
  c7_b_acc_x[1] = c7_acc_y;
  c7_b_acc_x[2] = c7_acc_z;
  for (c7_i15 = 0; c7_i15 < 3; c7_i15++) {
    c7_acc_TETRA[c7_i15] = c7_b_acc_x[c7_i15];
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 23);
  c7_b_gyro_placa_1[0] = c7_gyro_placa_1;
  c7_b_gyro_placa_1[1] = c7_gyro_placa_2;
  c7_b_gyro_placa_1[2] = c7_gyro_placa_3;
  c7_b_gyro_placa_1[3] = c7_gyro_placa_4;
  for (c7_i16 = 0; c7_i16 < 4; c7_i16++) {
    c7_gyro_TETRA[c7_i16] = c7_b_gyro_placa_1[c7_i16];
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 24);
  c7_Timer_TETRA = c7_entrada_TETRA[14];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, -24);
  _SFD_SYMBOL_SCOPE_POP();
  for (c7_i17 = 0; c7_i17 < 3; c7_i17++) {
    (*c7_b_mag_TETRA)[c7_i17] = c7_mag_TETRA[c7_i17];
  }

  for (c7_i18 = 0; c7_i18 < 3; c7_i18++) {
    (*c7_b_acc_TETRA)[c7_i18] = c7_acc_TETRA[c7_i18];
  }

  for (c7_i19 = 0; c7_i19 < 4; c7_i19++) {
    (*c7_b_gyro_TETRA)[c7_i19] = c7_gyro_TETRA[c7_i19];
  }

  *c7_b_Timer_TETRA = c7_Timer_TETRA;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c7_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY
    (_Tetraedro_model_sem_sim_com_FK_heurMachineNumber_,
     chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void registerMessagesc7_Tetraedro_model_sem_sim_com_FK_heur
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber)
{
}

static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  real_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(real_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static real_T c7_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_Timer_TETRA, const char_T *c7_identifier)
{
  real_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_Timer_TETRA),
    &c7_thisId);
  sf_mex_destroy(&c7_Timer_TETRA);
  return c7_y;
}

static real_T c7_b_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  real_T c7_y;
  real_T c7_d0;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_d0, 1, 0, 0U, 0, 0U, 0);
  c7_y = c7_d0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_Timer_TETRA;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y;
  SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c7_Timer_TETRA = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_Timer_TETRA),
    &c7_thisId);
  sf_mex_destroy(&c7_Timer_TETRA);
  *(real_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i20;
  real_T c7_b_inData[4];
  int32_T c7_i21;
  real_T c7_u[4];
  const mxArray *c7_y = NULL;
  SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  for (c7_i20 = 0; c7_i20 < 4; c7_i20++) {
    c7_b_inData[c7_i20] = (*(real_T (*)[4])c7_inData)[c7_i20];
  }

  for (c7_i21 = 0; c7_i21 < 4; c7_i21++) {
    c7_u[c7_i21] = c7_b_inData[c7_i21];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static void c7_c_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_gyro_TETRA, const char_T *c7_identifier, real_T c7_y[4])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_gyro_TETRA), &c7_thisId,
                        c7_y);
  sf_mex_destroy(&c7_gyro_TETRA);
}

static void c7_d_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[4])
{
  real_T c7_dv3[4];
  int32_T c7_i22;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv3, 1, 0, 0U, 1, 0U, 1, 4);
  for (c7_i22 = 0; c7_i22 < 4; c7_i22++) {
    c7_y[c7_i22] = c7_dv3[c7_i22];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_gyro_TETRA;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[4];
  int32_T c7_i23;
  SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c7_gyro_TETRA = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_gyro_TETRA), &c7_thisId,
                        c7_y);
  sf_mex_destroy(&c7_gyro_TETRA);
  for (c7_i23 = 0; c7_i23 < 4; c7_i23++) {
    (*(real_T (*)[4])c7_outData)[c7_i23] = c7_y[c7_i23];
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i24;
  real_T c7_b_inData[3];
  int32_T c7_i25;
  real_T c7_u[3];
  const mxArray *c7_y = NULL;
  SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  for (c7_i24 = 0; c7_i24 < 3; c7_i24++) {
    c7_b_inData[c7_i24] = (*(real_T (*)[3])c7_inData)[c7_i24];
  }

  for (c7_i25 = 0; c7_i25 < 3; c7_i25++) {
    c7_u[c7_i25] = c7_b_inData[c7_i25];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static void c7_e_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_acc_TETRA, const char_T *c7_identifier, real_T c7_y[3])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_acc_TETRA), &c7_thisId,
                        c7_y);
  sf_mex_destroy(&c7_acc_TETRA);
}

static void c7_f_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[3])
{
  real_T c7_dv4[3];
  int32_T c7_i26;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv4, 1, 0, 0U, 1, 0U, 1, 3);
  for (c7_i26 = 0; c7_i26 < 3; c7_i26++) {
    c7_y[c7_i26] = c7_dv4[c7_i26];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_acc_TETRA;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[3];
  int32_T c7_i27;
  SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c7_acc_TETRA = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_acc_TETRA), &c7_thisId,
                        c7_y);
  sf_mex_destroy(&c7_acc_TETRA);
  for (c7_i27 = 0; c7_i27 < 3; c7_i27++) {
    (*(real_T (*)[3])c7_outData)[c7_i27] = c7_y[c7_i27];
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i28;
  real_T c7_b_inData[15];
  int32_T c7_i29;
  real_T c7_u[15];
  const mxArray *c7_y = NULL;
  SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  for (c7_i28 = 0; c7_i28 < 15; c7_i28++) {
    c7_b_inData[c7_i28] = (*(real_T (*)[15])c7_inData)[c7_i28];
  }

  for (c7_i29 = 0; c7_i29 < 15; c7_i29++) {
    c7_u[c7_i29] = c7_b_inData[c7_i29];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 15, 1), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

const mxArray
  *sf_c7_Tetraedro_model_sem_sim_com_FK_heur_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c7_nameCaptureInfo = NULL;
  c7_nameCaptureInfo = NULL;
  sf_mex_assign(&c7_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c7_nameCaptureInfo;
}

static const mxArray *c7_e_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(int32_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static int32_T c7_g_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  int32_T c7_y;
  int32_T c7_i30;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_i30, 1, 6, 0U, 0, 0U, 0);
  c7_y = c7_i30;
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
  SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
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
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_b_is_active_c7_Tetraedro_model_sem_sim_com_FK_heur, const char_T *
   c7_identifier)
{
  uint8_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c7_b_is_active_c7_Tetraedro_model_sem_sim_com_FK_heur), &c7_thisId);
  sf_mex_destroy(&c7_b_is_active_c7_Tetraedro_model_sem_sim_com_FK_heur);
  return c7_y;
}

static uint8_T c7_i_emlrt_marshallIn
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint8_T c7_y;
  uint8_T c7_u0;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_u0, 1, 3, 0U, 0, 0U, 0);
  c7_y = c7_u0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void init_dsm_address_info
  (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
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

void sf_c7_Tetraedro_model_sem_sim_com_FK_heur_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3557718247U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1710218268U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(354146220U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3413173743U);
}

mxArray *sf_c7_Tetraedro_model_sem_sim_com_FK_heur_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("hjZFNdcUd5Id4pvjnrogiE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(15);
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
      pr[0] = (double)(1);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c7_Tetraedro_model_sem_sim_com_FK_heur_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray
  *sf_get_sim_state_info_c7_Tetraedro_model_sem_sim_com_FK_heur(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[18],T\"Timer_TETRA\",},{M[1],M[16],T\"acc_TETRA\",},{M[1],M[17],T\"gyro_TETRA\",},{M[1],M[14],T\"mag_TETRA\",},{M[8],M[0],T\"is_active_c7_Tetraedro_model_sem_sim_com_FK_heur\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c7_Tetraedro_model_sem_sim_com_FK_heur_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
    chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Tetraedro_model_sem_sim_com_FK_heurMachineNumber_,
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
          _SFD_SET_DATA_PROPS(0,2,0,1,"mag_TETRA");
          _SFD_SET_DATA_PROPS(1,1,1,0,"entrada_TETRA");
          _SFD_SET_DATA_PROPS(2,2,0,1,"acc_TETRA");
          _SFD_SET_DATA_PROPS(3,2,0,1,"gyro_TETRA");
          _SFD_SET_DATA_PROPS(4,2,0,1,"Timer_TETRA");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,636);
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
            1.0,0,0,(MexFcnForType)c7_c_sf_marshallOut,(MexInFcnForType)
            c7_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 15;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_c_sf_marshallOut,(MexInFcnForType)
            c7_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_b_sf_marshallOut,(MexInFcnForType)
            c7_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)c7_sf_marshallIn);

        {
          real_T *c7_Timer_TETRA;
          real_T (*c7_mag_TETRA)[3];
          real_T (*c7_entrada_TETRA)[15];
          real_T (*c7_acc_TETRA)[3];
          real_T (*c7_gyro_TETRA)[4];
          c7_Timer_TETRA = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c7_gyro_TETRA = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S,
            3);
          c7_acc_TETRA = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            2);
          c7_entrada_TETRA = (real_T (*)[15])ssGetInputPortSignal
            (chartInstance->S, 0);
          c7_mag_TETRA = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            1);
          _SFD_SET_DATA_VALUE_PTR(0U, *c7_mag_TETRA);
          _SFD_SET_DATA_VALUE_PTR(1U, *c7_entrada_TETRA);
          _SFD_SET_DATA_VALUE_PTR(2U, *c7_acc_TETRA);
          _SFD_SET_DATA_VALUE_PTR(3U, *c7_gyro_TETRA);
          _SFD_SET_DATA_VALUE_PTR(4U, c7_Timer_TETRA);
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
  return "GzskDYDU6bzJNYEkjyBi9B";
}

static void sf_opaque_initialize_c7_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  chart_debug_initialization
    (((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar)
     ->S,0);
  initialize_params_c7_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
  initialize_c7_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c7_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  enable_c7_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c7_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  disable_c7_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c7_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  sf_c7_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

extern const mxArray*
  sf_internal_get_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
     chartInfo->chartInstance);        /* raw sim ctx */
  prhs[3] = (mxArray*)
    sf_get_sim_state_info_c7_Tetraedro_model_sem_sim_com_FK_heur();/* state var info */
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

extern void sf_internal_set_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur
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
    sf_get_sim_state_info_c7_Tetraedro_model_sem_sim_com_FK_heur();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
     chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray*
  sf_opaque_get_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur(SimStruct* S)
{
  return sf_internal_get_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur(S);
}

static void sf_opaque_set_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur(S, st);
}

static void sf_opaque_terminate_c7_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Tetraedro_model_sem_sim_com_FK_heur_optimization_info();
    }

    finalize_c7_Tetraedro_model_sem_sim_com_FK_heur
      ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
       chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc7_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c7_Tetraedro_model_sem_sim_com_FK_heur
  (SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c7_Tetraedro_model_sem_sim_com_FK_heur
      ((SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
       (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c7_Tetraedro_model_sem_sim_com_FK_heur(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct =
      load_Tetraedro_model_sem_sim_com_FK_heur_optimization_info();
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
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,7,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,7,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,7);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1957187294U));
  ssSetChecksum1(S,(3060653497U));
  ssSetChecksum2(S,(2807623153U));
  ssSetChecksum3(S,(2070467944U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c7_Tetraedro_model_sem_sim_com_FK_heur(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c7_Tetraedro_model_sem_sim_com_FK_heur(SimStruct *S)
{
  SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    utMalloc(sizeof(SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc7_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c7_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c7_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c7_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c7_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c7_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c7_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c7_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW =
    mdlRTW_c7_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.mdlStart =
    mdlStart_c7_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c7_Tetraedro_model_sem_sim_com_FK_heur;
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

void c7_Tetraedro_model_sem_sim_com_FK_heur_method_dispatcher(SimStruct *S,
  int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c7_Tetraedro_model_sem_sim_com_FK_heur(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c7_Tetraedro_model_sem_sim_com_FK_heur(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c7_Tetraedro_model_sem_sim_com_FK_heur(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c7_Tetraedro_model_sem_sim_com_FK_heur_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
