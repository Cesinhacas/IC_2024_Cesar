#ifndef __c14_modelo_FK_trial_2_testes_h__
#define __c14_modelo_FK_trial_2_testes_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_SFc14_modelo_FK_trial_2_testesInstanceStruct
#define typedef_SFc14_modelo_FK_trial_2_testesInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c14_sfEvent;
  boolean_T c14_isStable;
  boolean_T c14_doneDoubleBufferReInit;
  uint8_T c14_is_active_c14_modelo_FK_trial_2_testes;
} SFc14_modelo_FK_trial_2_testesInstanceStruct;

#endif                                 /*typedef_SFc14_modelo_FK_trial_2_testesInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c14_modelo_FK_trial_2_testes_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c14_modelo_FK_trial_2_testes_get_check_sum(mxArray *plhs[]);
extern void c14_modelo_FK_trial_2_testes_method_dispatcher(SimStruct *S, int_T
  method, void *data);

#endif
