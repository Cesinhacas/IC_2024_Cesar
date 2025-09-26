/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_FK_trial_1_sfun.h"
#include "c14_modelo_FK_trial_1.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "modelo_FK_trial_1_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c14_debug_family_names[4] = { "nargin", "nargout", "x", "xe"
};

/* Function Declarations */
static void initialize_c14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance);
static void initialize_params_c14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance);
static void enable_c14_modelo_FK_trial_1(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance);
static void disable_c14_modelo_FK_trial_1(SFc14_modelo_FK_trial_1InstanceStruct *
  chartInstance);
static void c14_update_debugger_state_c14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance);
static void set_sim_state_c14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance, const mxArray *c14_st);
static void finalize_c14_modelo_FK_trial_1(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance);
static void sf_c14_modelo_FK_trial_1(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance);
static void initSimStructsc14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance);
static void registerMessagesc14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c14_machineNumber, uint32_T
  c14_chartNumber);
static const mxArray *c14_sf_marshallOut(void *chartInstanceVoid, void
  *c14_inData);
static void c14_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_xe, const char_T *c14_identifier, real_T
  c14_y[7]);
static void c14_b_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_u, const emlrtMsgIdentifier *c14_parentId,
  real_T c14_y[7]);
static void c14_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c14_mxArrayInData, const char_T *c14_varName, void *c14_outData);
static const mxArray *c14_b_sf_marshallOut(void *chartInstanceVoid, void
  *c14_inData);
static real_T c14_c_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_u, const emlrtMsgIdentifier *c14_parentId);
static void c14_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c14_mxArrayInData, const char_T *c14_varName, void *c14_outData);
static const mxArray *c14_c_sf_marshallOut(void *chartInstanceVoid, void
  *c14_inData);
static int32_T c14_d_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_u, const emlrtMsgIdentifier *c14_parentId);
static void c14_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c14_mxArrayInData, const char_T *c14_varName, void *c14_outData);
static uint8_T c14_e_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_b_is_active_c14_modelo_FK_trial_1, const
  char_T *c14_identifier);
static uint8_T c14_f_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_u, const emlrtMsgIdentifier *c14_parentId);
static void init_dsm_address_info(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance)
{
  chartInstance->c14_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c14_is_active_c14_modelo_FK_trial_1 = 0U;
}

static void initialize_params_c14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance)
{
}

static void enable_c14_modelo_FK_trial_1(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c14_modelo_FK_trial_1(SFc14_modelo_FK_trial_1InstanceStruct *
  chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c14_update_debugger_state_c14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance)
{
  const mxArray *c14_st;
  const mxArray *c14_y = NULL;
  int32_T c14_i0;
  real_T c14_u[7];
  const mxArray *c14_b_y = NULL;
  uint8_T c14_hoistedGlobal;
  uint8_T c14_b_u;
  const mxArray *c14_c_y = NULL;
  real_T (*c14_xe)[7];
  c14_xe = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  c14_st = NULL;
  c14_st = NULL;
  c14_y = NULL;
  sf_mex_assign(&c14_y, sf_mex_createcellarray(2), FALSE);
  for (c14_i0 = 0; c14_i0 < 7; c14_i0++) {
    c14_u[c14_i0] = (*c14_xe)[c14_i0];
  }

  c14_b_y = NULL;
  sf_mex_assign(&c14_b_y, sf_mex_create("y", c14_u, 0, 0U, 1U, 0U, 1, 7), FALSE);
  sf_mex_setcell(c14_y, 0, c14_b_y);
  c14_hoistedGlobal = chartInstance->c14_is_active_c14_modelo_FK_trial_1;
  c14_b_u = c14_hoistedGlobal;
  c14_c_y = NULL;
  sf_mex_assign(&c14_c_y, sf_mex_create("y", &c14_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c14_y, 1, c14_c_y);
  sf_mex_assign(&c14_st, c14_y, FALSE);
  return c14_st;
}

static void set_sim_state_c14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance, const mxArray *c14_st)
{
  const mxArray *c14_u;
  real_T c14_dv0[7];
  int32_T c14_i1;
  real_T (*c14_xe)[7];
  c14_xe = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c14_doneDoubleBufferReInit = TRUE;
  c14_u = sf_mex_dup(c14_st);
  c14_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c14_u, 0)), "xe",
                       c14_dv0);
  for (c14_i1 = 0; c14_i1 < 7; c14_i1++) {
    (*c14_xe)[c14_i1] = c14_dv0[c14_i1];
  }

  chartInstance->c14_is_active_c14_modelo_FK_trial_1 = c14_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c14_u, 1)),
     "is_active_c14_modelo_FK_trial_1");
  sf_mex_destroy(&c14_u);
  c14_update_debugger_state_c14_modelo_FK_trial_1(chartInstance);
  sf_mex_destroy(&c14_st);
}

static void finalize_c14_modelo_FK_trial_1(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance)
{
}

static void sf_c14_modelo_FK_trial_1(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance)
{
  int32_T c14_i2;
  int32_T c14_i3;
  int32_T c14_i4;
  real_T c14_x[7];
  uint32_T c14_debug_family_var_map[4];
  real_T c14_nargin = 1.0;
  real_T c14_nargout = 1.0;
  real_T c14_xe[7];
  int32_T c14_i5;
  int32_T c14_i6;
  int32_T c14_i7;
  int32_T c14_i8;
  int32_T c14_i9;
  real_T (*c14_b_xe)[7];
  real_T (*c14_b_x)[7];
  c14_b_xe = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
  c14_b_x = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 12U, chartInstance->c14_sfEvent);
  for (c14_i2 = 0; c14_i2 < 7; c14_i2++) {
    _SFD_DATA_RANGE_CHECK((*c14_b_x)[c14_i2], 0U);
  }

  for (c14_i3 = 0; c14_i3 < 7; c14_i3++) {
    _SFD_DATA_RANGE_CHECK((*c14_b_xe)[c14_i3], 1U);
  }

  chartInstance->c14_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 12U, chartInstance->c14_sfEvent);
  for (c14_i4 = 0; c14_i4 < 7; c14_i4++) {
    c14_x[c14_i4] = (*c14_b_x)[c14_i4];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c14_debug_family_names,
    c14_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c14_nargin, 0U, c14_b_sf_marshallOut,
    c14_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c14_nargout, 1U, c14_b_sf_marshallOut,
    c14_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c14_x, 2U, c14_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c14_xe, 3U, c14_sf_marshallOut,
    c14_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c14_sfEvent, 2);
  for (c14_i5 = 0; c14_i5 < 7; c14_i5++) {
    c14_xe[c14_i5] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c14_sfEvent, 3);
  if (CV_EML_IF(0, 1, 0, c14_x[3] < 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c14_sfEvent, 4);
    for (c14_i6 = 0; c14_i6 < 4; c14_i6++) {
      c14_xe[c14_i6] = -c14_x[c14_i6];
    }

    _SFD_EML_CALL(0U, chartInstance->c14_sfEvent, 5);
    for (c14_i7 = 0; c14_i7 < 3; c14_i7++) {
      c14_xe[c14_i7 + 4] = c14_x[c14_i7 + 4];
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c14_sfEvent, 7);
    for (c14_i8 = 0; c14_i8 < 7; c14_i8++) {
      c14_xe[c14_i8] = c14_x[c14_i8];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c14_sfEvent, -7);
  _SFD_SYMBOL_SCOPE_POP();
  for (c14_i9 = 0; c14_i9 < 7; c14_i9++) {
    (*c14_b_xe)[c14_i9] = c14_xe[c14_i9];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c14_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_modelo_FK_trial_1MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance)
{
}

static void registerMessagesc14_modelo_FK_trial_1
  (SFc14_modelo_FK_trial_1InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c14_machineNumber, uint32_T
  c14_chartNumber)
{
}

static const mxArray *c14_sf_marshallOut(void *chartInstanceVoid, void
  *c14_inData)
{
  const mxArray *c14_mxArrayOutData = NULL;
  int32_T c14_i10;
  real_T c14_b_inData[7];
  int32_T c14_i11;
  real_T c14_u[7];
  const mxArray *c14_y = NULL;
  SFc14_modelo_FK_trial_1InstanceStruct *chartInstance;
  chartInstance = (SFc14_modelo_FK_trial_1InstanceStruct *)chartInstanceVoid;
  c14_mxArrayOutData = NULL;
  for (c14_i10 = 0; c14_i10 < 7; c14_i10++) {
    c14_b_inData[c14_i10] = (*(real_T (*)[7])c14_inData)[c14_i10];
  }

  for (c14_i11 = 0; c14_i11 < 7; c14_i11++) {
    c14_u[c14_i11] = c14_b_inData[c14_i11];
  }

  c14_y = NULL;
  sf_mex_assign(&c14_y, sf_mex_create("y", c14_u, 0, 0U, 1U, 0U, 1, 7), FALSE);
  sf_mex_assign(&c14_mxArrayOutData, c14_y, FALSE);
  return c14_mxArrayOutData;
}

static void c14_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_xe, const char_T *c14_identifier, real_T
  c14_y[7])
{
  emlrtMsgIdentifier c14_thisId;
  c14_thisId.fIdentifier = c14_identifier;
  c14_thisId.fParent = NULL;
  c14_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c14_xe), &c14_thisId, c14_y);
  sf_mex_destroy(&c14_xe);
}

static void c14_b_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_u, const emlrtMsgIdentifier *c14_parentId,
  real_T c14_y[7])
{
  real_T c14_dv1[7];
  int32_T c14_i12;
  sf_mex_import(c14_parentId, sf_mex_dup(c14_u), c14_dv1, 1, 0, 0U, 1, 0U, 1, 7);
  for (c14_i12 = 0; c14_i12 < 7; c14_i12++) {
    c14_y[c14_i12] = c14_dv1[c14_i12];
  }

  sf_mex_destroy(&c14_u);
}

static void c14_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c14_mxArrayInData, const char_T *c14_varName, void *c14_outData)
{
  const mxArray *c14_xe;
  const char_T *c14_identifier;
  emlrtMsgIdentifier c14_thisId;
  real_T c14_y[7];
  int32_T c14_i13;
  SFc14_modelo_FK_trial_1InstanceStruct *chartInstance;
  chartInstance = (SFc14_modelo_FK_trial_1InstanceStruct *)chartInstanceVoid;
  c14_xe = sf_mex_dup(c14_mxArrayInData);
  c14_identifier = c14_varName;
  c14_thisId.fIdentifier = c14_identifier;
  c14_thisId.fParent = NULL;
  c14_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c14_xe), &c14_thisId, c14_y);
  sf_mex_destroy(&c14_xe);
  for (c14_i13 = 0; c14_i13 < 7; c14_i13++) {
    (*(real_T (*)[7])c14_outData)[c14_i13] = c14_y[c14_i13];
  }

  sf_mex_destroy(&c14_mxArrayInData);
}

static const mxArray *c14_b_sf_marshallOut(void *chartInstanceVoid, void
  *c14_inData)
{
  const mxArray *c14_mxArrayOutData = NULL;
  real_T c14_u;
  const mxArray *c14_y = NULL;
  SFc14_modelo_FK_trial_1InstanceStruct *chartInstance;
  chartInstance = (SFc14_modelo_FK_trial_1InstanceStruct *)chartInstanceVoid;
  c14_mxArrayOutData = NULL;
  c14_u = *(real_T *)c14_inData;
  c14_y = NULL;
  sf_mex_assign(&c14_y, sf_mex_create("y", &c14_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c14_mxArrayOutData, c14_y, FALSE);
  return c14_mxArrayOutData;
}

static real_T c14_c_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_u, const emlrtMsgIdentifier *c14_parentId)
{
  real_T c14_y;
  real_T c14_d0;
  sf_mex_import(c14_parentId, sf_mex_dup(c14_u), &c14_d0, 1, 0, 0U, 0, 0U, 0);
  c14_y = c14_d0;
  sf_mex_destroy(&c14_u);
  return c14_y;
}

static void c14_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c14_mxArrayInData, const char_T *c14_varName, void *c14_outData)
{
  const mxArray *c14_nargout;
  const char_T *c14_identifier;
  emlrtMsgIdentifier c14_thisId;
  real_T c14_y;
  SFc14_modelo_FK_trial_1InstanceStruct *chartInstance;
  chartInstance = (SFc14_modelo_FK_trial_1InstanceStruct *)chartInstanceVoid;
  c14_nargout = sf_mex_dup(c14_mxArrayInData);
  c14_identifier = c14_varName;
  c14_thisId.fIdentifier = c14_identifier;
  c14_thisId.fParent = NULL;
  c14_y = c14_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c14_nargout),
    &c14_thisId);
  sf_mex_destroy(&c14_nargout);
  *(real_T *)c14_outData = c14_y;
  sf_mex_destroy(&c14_mxArrayInData);
}

const mxArray *sf_c14_modelo_FK_trial_1_get_eml_resolved_functions_info(void)
{
  const mxArray *c14_nameCaptureInfo = NULL;
  c14_nameCaptureInfo = NULL;
  sf_mex_assign(&c14_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c14_nameCaptureInfo;
}

static const mxArray *c14_c_sf_marshallOut(void *chartInstanceVoid, void
  *c14_inData)
{
  const mxArray *c14_mxArrayOutData = NULL;
  int32_T c14_u;
  const mxArray *c14_y = NULL;
  SFc14_modelo_FK_trial_1InstanceStruct *chartInstance;
  chartInstance = (SFc14_modelo_FK_trial_1InstanceStruct *)chartInstanceVoid;
  c14_mxArrayOutData = NULL;
  c14_u = *(int32_T *)c14_inData;
  c14_y = NULL;
  sf_mex_assign(&c14_y, sf_mex_create("y", &c14_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c14_mxArrayOutData, c14_y, FALSE);
  return c14_mxArrayOutData;
}

static int32_T c14_d_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_u, const emlrtMsgIdentifier *c14_parentId)
{
  int32_T c14_y;
  int32_T c14_i14;
  sf_mex_import(c14_parentId, sf_mex_dup(c14_u), &c14_i14, 1, 6, 0U, 0, 0U, 0);
  c14_y = c14_i14;
  sf_mex_destroy(&c14_u);
  return c14_y;
}

static void c14_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c14_mxArrayInData, const char_T *c14_varName, void *c14_outData)
{
  const mxArray *c14_b_sfEvent;
  const char_T *c14_identifier;
  emlrtMsgIdentifier c14_thisId;
  int32_T c14_y;
  SFc14_modelo_FK_trial_1InstanceStruct *chartInstance;
  chartInstance = (SFc14_modelo_FK_trial_1InstanceStruct *)chartInstanceVoid;
  c14_b_sfEvent = sf_mex_dup(c14_mxArrayInData);
  c14_identifier = c14_varName;
  c14_thisId.fIdentifier = c14_identifier;
  c14_thisId.fParent = NULL;
  c14_y = c14_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c14_b_sfEvent),
    &c14_thisId);
  sf_mex_destroy(&c14_b_sfEvent);
  *(int32_T *)c14_outData = c14_y;
  sf_mex_destroy(&c14_mxArrayInData);
}

static uint8_T c14_e_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_b_is_active_c14_modelo_FK_trial_1, const
  char_T *c14_identifier)
{
  uint8_T c14_y;
  emlrtMsgIdentifier c14_thisId;
  c14_thisId.fIdentifier = c14_identifier;
  c14_thisId.fParent = NULL;
  c14_y = c14_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c14_b_is_active_c14_modelo_FK_trial_1), &c14_thisId);
  sf_mex_destroy(&c14_b_is_active_c14_modelo_FK_trial_1);
  return c14_y;
}

static uint8_T c14_f_emlrt_marshallIn(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance, const mxArray *c14_u, const emlrtMsgIdentifier *c14_parentId)
{
  uint8_T c14_y;
  uint8_T c14_u0;
  sf_mex_import(c14_parentId, sf_mex_dup(c14_u), &c14_u0, 1, 3, 0U, 0, 0U, 0);
  c14_y = c14_u0;
  sf_mex_destroy(&c14_u);
  return c14_y;
}

static void init_dsm_address_info(SFc14_modelo_FK_trial_1InstanceStruct
  *chartInstance)
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

void sf_c14_modelo_FK_trial_1_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1827729401U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3244519531U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2677620643U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3439306018U);
}

mxArray *sf_c14_modelo_FK_trial_1_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("7aLrJi0jJ0S3LP2dWyv9k");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c14_modelo_FK_trial_1_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c14_modelo_FK_trial_1(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"xe\",},{M[8],M[0],T\"is_active_c14_modelo_FK_trial_1\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c14_modelo_FK_trial_1_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc14_modelo_FK_trial_1InstanceStruct *chartInstance;
    chartInstance = (SFc14_modelo_FK_trial_1InstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modelo_FK_trial_1MachineNumber_,
           14,
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
          init_script_number_translation(_modelo_FK_trial_1MachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_modelo_FK_trial_1MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _modelo_FK_trial_1MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"x");
          _SFD_SET_DATA_PROPS(1,2,0,1,"xe");
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
        _SFD_CV_INIT_EML(0,1,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,144);
        _SFD_CV_INIT_EML_IF(0,1,0,52,65,122,143);
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
            1.0,0,0,(MexFcnForType)c14_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c14_sf_marshallOut,(MexInFcnForType)
            c14_sf_marshallIn);
        }

        {
          real_T (*c14_x)[7];
          real_T (*c14_xe)[7];
          c14_xe = (real_T (*)[7])ssGetOutputPortSignal(chartInstance->S, 1);
          c14_x = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c14_x);
          _SFD_SET_DATA_VALUE_PTR(1U, *c14_xe);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _modelo_FK_trial_1MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "aKGdEMDDdTa5lWYu8iUHSC";
}

static void sf_opaque_initialize_c14_modelo_FK_trial_1(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc14_modelo_FK_trial_1InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c14_modelo_FK_trial_1((SFc14_modelo_FK_trial_1InstanceStruct*)
    chartInstanceVar);
  initialize_c14_modelo_FK_trial_1((SFc14_modelo_FK_trial_1InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c14_modelo_FK_trial_1(void *chartInstanceVar)
{
  enable_c14_modelo_FK_trial_1((SFc14_modelo_FK_trial_1InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c14_modelo_FK_trial_1(void *chartInstanceVar)
{
  disable_c14_modelo_FK_trial_1((SFc14_modelo_FK_trial_1InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c14_modelo_FK_trial_1(void *chartInstanceVar)
{
  sf_c14_modelo_FK_trial_1((SFc14_modelo_FK_trial_1InstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c14_modelo_FK_trial_1(SimStruct*
  S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c14_modelo_FK_trial_1
    ((SFc14_modelo_FK_trial_1InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c14_modelo_FK_trial_1();/* state var info */
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

extern void sf_internal_set_sim_state_c14_modelo_FK_trial_1(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c14_modelo_FK_trial_1();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c14_modelo_FK_trial_1((SFc14_modelo_FK_trial_1InstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c14_modelo_FK_trial_1(SimStruct* S)
{
  return sf_internal_get_sim_state_c14_modelo_FK_trial_1(S);
}

static void sf_opaque_set_sim_state_c14_modelo_FK_trial_1(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c14_modelo_FK_trial_1(S, st);
}

static void sf_opaque_terminate_c14_modelo_FK_trial_1(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc14_modelo_FK_trial_1InstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_FK_trial_1_optimization_info();
    }

    finalize_c14_modelo_FK_trial_1((SFc14_modelo_FK_trial_1InstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc14_modelo_FK_trial_1((SFc14_modelo_FK_trial_1InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c14_modelo_FK_trial_1(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c14_modelo_FK_trial_1
      ((SFc14_modelo_FK_trial_1InstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c14_modelo_FK_trial_1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_modelo_FK_trial_1_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      14);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,14,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,14,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,14);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,14,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,14,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,14);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2893144628U));
  ssSetChecksum1(S,(2263286069U));
  ssSetChecksum2(S,(767091306U));
  ssSetChecksum3(S,(3821184635U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c14_modelo_FK_trial_1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c14_modelo_FK_trial_1(SimStruct *S)
{
  SFc14_modelo_FK_trial_1InstanceStruct *chartInstance;
  chartInstance = (SFc14_modelo_FK_trial_1InstanceStruct *)utMalloc(sizeof
    (SFc14_modelo_FK_trial_1InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc14_modelo_FK_trial_1InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c14_modelo_FK_trial_1;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c14_modelo_FK_trial_1;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c14_modelo_FK_trial_1;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c14_modelo_FK_trial_1;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c14_modelo_FK_trial_1;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c14_modelo_FK_trial_1;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c14_modelo_FK_trial_1;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c14_modelo_FK_trial_1;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c14_modelo_FK_trial_1;
  chartInstance->chartInfo.mdlStart = mdlStart_c14_modelo_FK_trial_1;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c14_modelo_FK_trial_1;
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

void c14_modelo_FK_trial_1_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c14_modelo_FK_trial_1(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c14_modelo_FK_trial_1(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c14_modelo_FK_trial_1(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c14_modelo_FK_trial_1_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
