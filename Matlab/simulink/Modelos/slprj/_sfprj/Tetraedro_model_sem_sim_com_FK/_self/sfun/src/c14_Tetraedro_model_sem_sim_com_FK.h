#ifndef __c14_Tetraedro_model_sem_sim_com_FK_h__
#define __c14_Tetraedro_model_sem_sim_com_FK_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_SFc14_Tetraedro_model_sem_sim_com_FKInstanceStruct
#define typedef_SFc14_Tetraedro_model_sem_sim_com_FKInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c14_sfEvent;
  boolean_T c14_isStable;
  boolean_T c14_doneDoubleBufferReInit;
  uint8_T c14_is_active_c14_Tetraedro_model_sem_sim_com_FK;
} SFc14_Tetraedro_model_sem_sim_com_FKInstanceStruct;

#endif                                 /*typedef_SFc14_Tetraedro_model_sem_sim_com_FKInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c14_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c14_Tetraedro_model_sem_sim_com_FK_get_check_sum(mxArray *plhs[]);
extern void c14_Tetraedro_model_sem_sim_com_FK_method_dispatcher(SimStruct *S,
  int_T method, void *data);

#endif
