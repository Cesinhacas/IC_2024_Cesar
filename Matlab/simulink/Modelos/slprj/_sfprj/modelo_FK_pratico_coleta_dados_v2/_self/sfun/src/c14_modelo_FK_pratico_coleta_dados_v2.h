#ifndef __c14_modelo_FK_pratico_coleta_dados_v2_h__
#define __c14_modelo_FK_pratico_coleta_dados_v2_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_SFc14_modelo_FK_pratico_coleta_dados_v2InstanceStruct
#define typedef_SFc14_modelo_FK_pratico_coleta_dados_v2InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c14_sfEvent;
  boolean_T c14_isStable;
  boolean_T c14_doneDoubleBufferReInit;
  uint8_T c14_is_active_c14_modelo_FK_pratico_coleta_dados_v2;
} SFc14_modelo_FK_pratico_coleta_dados_v2InstanceStruct;

#endif                                 /*typedef_SFc14_modelo_FK_pratico_coleta_dados_v2InstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c14_modelo_FK_pratico_coleta_dados_v2_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c14_modelo_FK_pratico_coleta_dados_v2_get_check_sum(mxArray *
  plhs[]);
extern void c14_modelo_FK_pratico_coleta_dados_v2_method_dispatcher(SimStruct *S,
  int_T method, void *data);

#endif
