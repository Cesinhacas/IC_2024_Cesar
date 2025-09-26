/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Tetraedro_model_sem_sim_com_FK_heur_sfun.h"
#include "c8_Tetraedro_model_sem_sim_com_FK_heur.h"
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
static const char * c8_debug_family_names[4] = { "nargin", "nargout", "acc_rec",
  "enable" };

/* Function Declarations */
static void initialize_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void initialize_params_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void enable_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void disable_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void c8_update_debugger_state_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void set_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_st);
static void finalize_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void sf_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void initSimStructsc8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void registerMessagesc8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static real_T c8_emlrt_marshallIn
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_enable, const char_T *c8_identifier);
static real_T c8_b_emlrt_marshallIn
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[20]);
static real_T c8_norm(SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct
                      *chartInstance, real_T c8_x[3]);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_c_emlrt_marshallIn
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static uint8_T c8_d_emlrt_marshallIn
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_b_is_active_c8_Tetraedro_model_sem_sim_com_FK_heur, const char_T *
   c8_identifier);
static uint8_T c8_e_emlrt_marshallIn
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void init_dsm_address_info
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  chartInstance->c8_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c8_is_active_c8_Tetraedro_model_sem_sim_com_FK_heur = 0U;
}

static void initialize_params_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void enable_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c8_update_debugger_state_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  const mxArray *c8_st;
  const mxArray *c8_y = NULL;
  real_T c8_hoistedGlobal;
  real_T c8_u;
  const mxArray *c8_b_y = NULL;
  uint8_T c8_b_hoistedGlobal;
  uint8_T c8_b_u;
  const mxArray *c8_c_y = NULL;
  real_T *c8_enable;
  c8_enable = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellarray(2), FALSE);
  c8_hoistedGlobal = *c8_enable;
  c8_u = c8_hoistedGlobal;
  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 0, c8_b_y);
  c8_b_hoistedGlobal =
    chartInstance->c8_is_active_c8_Tetraedro_model_sem_sim_com_FK_heur;
  c8_b_u = c8_b_hoistedGlobal;
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 1, c8_c_y);
  sf_mex_assign(&c8_st, c8_y, FALSE);
  return c8_st;
}

static void set_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_st)
{
  const mxArray *c8_u;
  real_T *c8_enable;
  c8_enable = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c8_doneDoubleBufferReInit = TRUE;
  c8_u = sf_mex_dup(c8_st);
  *c8_enable = c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u,
    0)), "enable");
  chartInstance->c8_is_active_c8_Tetraedro_model_sem_sim_com_FK_heur =
    c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 1)),
    "is_active_c8_Tetraedro_model_sem_sim_com_FK_heur");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_Tetraedro_model_sem_sim_com_FK_heur(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void sf_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
  int32_T c8_i0;
  int32_T c8_i1;
  real_T c8_acc_rec[3];
  uint32_T c8_debug_family_var_map[4];
  real_T c8_nargin = 1.0;
  real_T c8_nargout = 1.0;
  real_T c8_enable;
  int32_T c8_i2;
  real_T c8_b_acc_rec[3];
  int32_T c8_i3;
  real_T c8_c_acc_rec[3];
  real_T *c8_b_enable;
  real_T (*c8_d_acc_rec)[3];
  boolean_T guard1 = FALSE;
  c8_b_enable = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_d_acc_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  for (c8_i0 = 0; c8_i0 < 3; c8_i0++) {
    _SFD_DATA_RANGE_CHECK((*c8_d_acc_rec)[c8_i0], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c8_b_enable, 1U);
  chartInstance->c8_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  for (c8_i1 = 0; c8_i1 < 3; c8_i1++) {
    c8_acc_rec[c8_i1] = (*c8_d_acc_rec)[c8_i1];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c8_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 0U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 1U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_acc_rec, 2U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_enable, 3U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 4);
  for (c8_i2 = 0; c8_i2 < 3; c8_i2++) {
    c8_b_acc_rec[c8_i2] = c8_acc_rec[c8_i2];
  }

  guard1 = FALSE;
  if (CV_EML_COND(0, 1, 0, c8_norm(chartInstance, c8_b_acc_rec) > 1125.0)) {
    guard1 = TRUE;
  } else {
    for (c8_i3 = 0; c8_i3 < 3; c8_i3++) {
      c8_c_acc_rec[c8_i3] = c8_acc_rec[c8_i3];
    }

    if (CV_EML_COND(0, 1, 1, c8_norm(chartInstance, c8_c_acc_rec) < 925.0)) {
      guard1 = TRUE;
    } else {
      CV_EML_MCDC(0, 1, 0, FALSE);
      CV_EML_IF(0, 1, 0, FALSE);
      _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 7);
      c8_enable = 0.0;
    }
  }

  if (guard1 == TRUE) {
    CV_EML_MCDC(0, 1, 0, TRUE);
    CV_EML_IF(0, 1, 0, TRUE);
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 5);
    c8_enable = 1.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, -7);
  _SFD_SYMBOL_SCOPE_POP();
  *c8_b_enable = c8_enable;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY
    (_Tetraedro_model_sem_sim_com_FK_heurMachineNumber_,
     chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void registerMessagesc8_Tetraedro_model_sem_sim_com_FK_heur
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber)
{
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static real_T c8_emlrt_marshallIn
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_enable, const char_T *c8_identifier)
{
  real_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_enable), &c8_thisId);
  sf_mex_destroy(&c8_enable);
  return c8_y;
}

static real_T c8_b_emlrt_marshallIn
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_d0, 1, 0, 0U, 0, 0U, 0);
  c8_y = c8_d0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_enable;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y;
  SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c8_enable = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_enable), &c8_thisId);
  sf_mex_destroy(&c8_enable);
  *(real_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i4;
  real_T c8_b_inData[3];
  int32_T c8_i5;
  real_T c8_u[3];
  const mxArray *c8_y = NULL;
  SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i4 = 0; c8_i4 < 3; c8_i4++) {
    c8_b_inData[c8_i4] = (*(real_T (*)[3])c8_inData)[c8_i4];
  }

  for (c8_i5 = 0; c8_i5 < 3; c8_i5++) {
    c8_u[c8_i5] = c8_b_inData[c8_i5];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

const mxArray
  *sf_c8_Tetraedro_model_sem_sim_com_FK_heur_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c8_nameCaptureInfo;
  c8_ResolvedFunctionInfo c8_info[20];
  const mxArray *c8_m0 = NULL;
  int32_T c8_i6;
  c8_ResolvedFunctionInfo *c8_r0;
  c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  c8_info_helper(c8_info);
  sf_mex_assign(&c8_m0, sf_mex_createstruct("nameCaptureInfo", 1, 20), FALSE);
  for (c8_i6 = 0; c8_i6 < 20; c8_i6++) {
    c8_r0 = &c8_info[c8_i6];
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->context)), "context", "nameCaptureInfo",
                    c8_i6);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c8_r0->name)), "name", "nameCaptureInfo", c8_i6);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c8_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c8_i6);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->resolved)), "resolved", "nameCaptureInfo",
                    c8_i6);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c8_i6);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c8_i6);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c8_i6);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c8_i6);
  }

  sf_mex_assign(&c8_nameCaptureInfo, c8_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c8_nameCaptureInfo);
  return c8_nameCaptureInfo;
}

static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[20])
{
  c8_info[0].context = "";
  c8_info[0].name = "norm";
  c8_info[0].dominantType = "double";
  c8_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c8_info[0].fileTimeLo = 1336540094U;
  c8_info[0].fileTimeHi = 0U;
  c8_info[0].mFileTimeLo = 0U;
  c8_info[0].mFileTimeHi = 0U;
  c8_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c8_info[1].name = "eml_index_class";
  c8_info[1].dominantType = "";
  c8_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[1].fileTimeLo = 1323181378U;
  c8_info[1].fileTimeHi = 0U;
  c8_info[1].mFileTimeLo = 0U;
  c8_info[1].mFileTimeHi = 0U;
  c8_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c8_info[2].name = "eml_xnrm2";
  c8_info[2].dominantType = "double";
  c8_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c8_info[2].fileTimeLo = 1299091176U;
  c8_info[2].fileTimeHi = 0U;
  c8_info[2].mFileTimeLo = 0U;
  c8_info[2].mFileTimeHi = 0U;
  c8_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c8_info[3].name = "eml_blas_inline";
  c8_info[3].dominantType = "";
  c8_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c8_info[3].fileTimeLo = 1299091168U;
  c8_info[3].fileTimeHi = 0U;
  c8_info[3].mFileTimeLo = 0U;
  c8_info[3].mFileTimeHi = 0U;
  c8_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c8_info[4].name = "eml_index_class";
  c8_info[4].dominantType = "";
  c8_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[4].fileTimeLo = 1323181378U;
  c8_info[4].fileTimeHi = 0U;
  c8_info[4].mFileTimeLo = 0U;
  c8_info[4].mFileTimeHi = 0U;
  c8_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c8_info[5].name = "eml_refblas_xnrm2";
  c8_info[5].dominantType = "double";
  c8_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c8_info[5].fileTimeLo = 1299091184U;
  c8_info[5].fileTimeHi = 0U;
  c8_info[5].mFileTimeLo = 0U;
  c8_info[5].mFileTimeHi = 0U;
  c8_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c8_info[6].name = "realmin";
  c8_info[6].dominantType = "char";
  c8_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c8_info[6].fileTimeLo = 1307669242U;
  c8_info[6].fileTimeHi = 0U;
  c8_info[6].mFileTimeLo = 0U;
  c8_info[6].mFileTimeHi = 0U;
  c8_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c8_info[7].name = "eml_realmin";
  c8_info[7].dominantType = "char";
  c8_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c8_info[7].fileTimeLo = 1307669244U;
  c8_info[7].fileTimeHi = 0U;
  c8_info[7].mFileTimeLo = 0U;
  c8_info[7].mFileTimeHi = 0U;
  c8_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c8_info[8].name = "eml_float_model";
  c8_info[8].dominantType = "char";
  c8_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c8_info[8].fileTimeLo = 1326738796U;
  c8_info[8].fileTimeHi = 0U;
  c8_info[8].mFileTimeLo = 0U;
  c8_info[8].mFileTimeHi = 0U;
  c8_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c8_info[9].name = "eml_index_class";
  c8_info[9].dominantType = "";
  c8_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[9].fileTimeLo = 1323181378U;
  c8_info[9].fileTimeHi = 0U;
  c8_info[9].mFileTimeLo = 0U;
  c8_info[9].mFileTimeHi = 0U;
  c8_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c8_info[10].name = "eml_index_minus";
  c8_info[10].dominantType = "double";
  c8_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c8_info[10].fileTimeLo = 1286836778U;
  c8_info[10].fileTimeHi = 0U;
  c8_info[10].mFileTimeLo = 0U;
  c8_info[10].mFileTimeHi = 0U;
  c8_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c8_info[11].name = "eml_index_class";
  c8_info[11].dominantType = "";
  c8_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[11].fileTimeLo = 1323181378U;
  c8_info[11].fileTimeHi = 0U;
  c8_info[11].mFileTimeLo = 0U;
  c8_info[11].mFileTimeHi = 0U;
  c8_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c8_info[12].name = "eml_index_times";
  c8_info[12].dominantType = "coder.internal.indexInt";
  c8_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c8_info[12].fileTimeLo = 1286836780U;
  c8_info[12].fileTimeHi = 0U;
  c8_info[12].mFileTimeLo = 0U;
  c8_info[12].mFileTimeHi = 0U;
  c8_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c8_info[13].name = "eml_index_class";
  c8_info[13].dominantType = "";
  c8_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[13].fileTimeLo = 1323181378U;
  c8_info[13].fileTimeHi = 0U;
  c8_info[13].mFileTimeLo = 0U;
  c8_info[13].mFileTimeHi = 0U;
  c8_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c8_info[14].name = "eml_index_plus";
  c8_info[14].dominantType = "coder.internal.indexInt";
  c8_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c8_info[14].fileTimeLo = 1286836778U;
  c8_info[14].fileTimeHi = 0U;
  c8_info[14].mFileTimeLo = 0U;
  c8_info[14].mFileTimeHi = 0U;
  c8_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c8_info[15].name = "eml_index_class";
  c8_info[15].dominantType = "";
  c8_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[15].fileTimeLo = 1323181378U;
  c8_info[15].fileTimeHi = 0U;
  c8_info[15].mFileTimeLo = 0U;
  c8_info[15].mFileTimeHi = 0U;
  c8_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c8_info[16].name = "eml_int_forloop_overflow_check";
  c8_info[16].dominantType = "";
  c8_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c8_info[16].fileTimeLo = 1346528340U;
  c8_info[16].fileTimeHi = 0U;
  c8_info[16].mFileTimeLo = 0U;
  c8_info[16].mFileTimeHi = 0U;
  c8_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c8_info[17].name = "intmax";
  c8_info[17].dominantType = "char";
  c8_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c8_info[17].fileTimeLo = 1311273316U;
  c8_info[17].fileTimeHi = 0U;
  c8_info[17].mFileTimeLo = 0U;
  c8_info[17].mFileTimeHi = 0U;
  c8_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
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
}

static real_T c8_norm(SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct
                      *chartInstance, real_T c8_x[3])
{
  real_T c8_y;
  real_T c8_scale;
  int32_T c8_k;
  int32_T c8_b_k;
  real_T c8_b_x;
  real_T c8_c_x;
  real_T c8_absxk;
  real_T c8_t;
  c8_y = 0.0;
  c8_scale = 2.2250738585072014E-308;
  for (c8_k = 1; c8_k < 4; c8_k++) {
    c8_b_k = c8_k;
    c8_b_x = c8_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c8_b_k), 1, 3, 1, 0) - 1];
    c8_c_x = c8_b_x;
    c8_absxk = muDoubleScalarAbs(c8_c_x);
    if (c8_absxk > c8_scale) {
      c8_t = c8_scale / c8_absxk;
      c8_y = 1.0 + c8_y * c8_t * c8_t;
      c8_scale = c8_absxk;
    } else {
      c8_t = c8_absxk / c8_scale;
      c8_y += c8_t * c8_t;
    }
  }

  return c8_scale * muDoubleScalarSqrt(c8_y);
}

static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static int32_T c8_c_emlrt_marshallIn
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i7;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i7, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i7;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_sfEvent;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int32_T c8_y;
  SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    chartInstanceVoid;
  c8_b_sfEvent = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_sfEvent),
    &c8_thisId);
  sf_mex_destroy(&c8_b_sfEvent);
  *(int32_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static uint8_T c8_d_emlrt_marshallIn
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_b_is_active_c8_Tetraedro_model_sem_sim_com_FK_heur, const char_T *
   c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c8_b_is_active_c8_Tetraedro_model_sem_sim_com_FK_heur), &c8_thisId);
  sf_mex_destroy(&c8_b_is_active_c8_Tetraedro_model_sem_sim_com_FK_heur);
  return c8_y;
}

static uint8_T c8_e_emlrt_marshallIn
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance, const
   mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_u0, 1, 3, 0U, 0, 0U, 0);
  c8_y = c8_u0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void init_dsm_address_info
  (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance)
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

void sf_c8_Tetraedro_model_sem_sim_com_FK_heur_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2613488117U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2537159208U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1107712327U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2077149128U);
}

mxArray *sf_c8_Tetraedro_model_sem_sim_com_FK_heur_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("KZ4e3U4f1z33dladvKY2nE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c8_Tetraedro_model_sem_sim_com_FK_heur_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray
  *sf_get_sim_state_info_c8_Tetraedro_model_sem_sim_com_FK_heur(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"enable\",},{M[8],M[0],T\"is_active_c8_Tetraedro_model_sem_sim_com_FK_heur\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_Tetraedro_model_sem_sim_com_FK_heur_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
    chartInstance = (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Tetraedro_model_sem_sim_com_FK_heurMachineNumber_,
           8,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"acc_rec");
          _SFD_SET_DATA_PROPS(1,2,0,1,"enable");
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
        _SFD_CV_INIT_EML(0,1,1,1,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,126);
        _SFD_CV_INIT_EML_IF(0,1,0,45,88,103,125);

        {
          static int condStart[] = { 48, 70 };

          static int condEnd[] = { 66, 87 };

          static int pfixExpr[] = { 0, 1, -2 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,48,87,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

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
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)c8_sf_marshallIn);

        {
          real_T *c8_enable;
          real_T (*c8_acc_rec)[3];
          c8_enable = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c8_acc_rec = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c8_acc_rec);
          _SFD_SET_DATA_VALUE_PTR(1U, c8_enable);
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
  return "D4HJxT9xckHAkMJaVCnpFG";
}

static void sf_opaque_initialize_c8_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  chart_debug_initialization
    (((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar)
     ->S,0);
  initialize_params_c8_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
  initialize_c8_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c8_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  enable_c8_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c8_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  disable_c8_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c8_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  sf_c8_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

extern const mxArray*
  sf_internal_get_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
     chartInfo->chartInstance);        /* raw sim ctx */
  prhs[3] = (mxArray*)
    sf_get_sim_state_info_c8_Tetraedro_model_sem_sim_com_FK_heur();/* state var info */
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

extern void sf_internal_set_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur
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
    sf_get_sim_state_info_c8_Tetraedro_model_sem_sim_com_FK_heur();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
     chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray*
  sf_opaque_get_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur(SimStruct* S)
{
  return sf_internal_get_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur(S);
}

static void sf_opaque_set_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur(S, st);
}

static void sf_opaque_terminate_c8_Tetraedro_model_sem_sim_com_FK_heur(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Tetraedro_model_sem_sim_com_FK_heur_optimization_info();
    }

    finalize_c8_Tetraedro_model_sem_sim_com_FK_heur
      ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
       chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc8_Tetraedro_model_sem_sim_com_FK_heur
    ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_Tetraedro_model_sem_sim_com_FK_heur
  (SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c8_Tetraedro_model_sem_sim_com_FK_heur
      ((SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*)
       (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c8_Tetraedro_model_sem_sim_com_FK_heur(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct =
      load_Tetraedro_model_sem_sim_com_FK_heur_optimization_info();
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
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,8,1);
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
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,8);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2463744524U));
  ssSetChecksum1(S,(2098541632U));
  ssSetChecksum2(S,(3169798403U));
  ssSetChecksum3(S,(680586241U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c8_Tetraedro_model_sem_sim_com_FK_heur(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_Tetraedro_model_sem_sim_com_FK_heur(SimStruct *S)
{
  SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *chartInstance;
  chartInstance = (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct *)
    utMalloc(sizeof(SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc8_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c8_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c8_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c8_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c8_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c8_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c8_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c8_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW =
    mdlRTW_c8_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.mdlStart =
    mdlStart_c8_Tetraedro_model_sem_sim_com_FK_heur;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c8_Tetraedro_model_sem_sim_com_FK_heur;
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

void c8_Tetraedro_model_sem_sim_com_FK_heur_method_dispatcher(SimStruct *S,
  int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_Tetraedro_model_sem_sim_com_FK_heur(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_Tetraedro_model_sem_sim_com_FK_heur(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_Tetraedro_model_sem_sim_com_FK_heur(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_Tetraedro_model_sem_sim_com_FK_heur_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
