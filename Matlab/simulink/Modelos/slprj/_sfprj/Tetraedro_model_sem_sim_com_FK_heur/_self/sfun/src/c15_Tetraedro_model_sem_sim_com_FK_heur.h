#ifndef __c15_Tetraedro_model_sem_sim_com_FK_heur_h__
#define __c15_Tetraedro_model_sem_sim_com_FK_heur_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_SFc15_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct
#define typedef_SFc15_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c15_sfEvent;
  boolean_T c15_isStable;
  boolean_T c15_doneDoubleBufferReInit;
  uint8_T c15_is_active_c15_Tetraedro_model_sem_sim_com_FK_heur;
} SFc15_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct;

#endif                                 /*typedef_SFc15_Tetraedro_model_sem_sim_com_FK_heurInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c15_Tetraedro_model_sem_sim_com_FK_heur_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c15_Tetraedro_model_sem_sim_com_FK_heur_get_check_sum(mxArray
  *plhs[]);
extern void c15_Tetraedro_model_sem_sim_com_FK_heur_method_dispatcher(SimStruct *
  S, int_T method, void *data);

#endif
