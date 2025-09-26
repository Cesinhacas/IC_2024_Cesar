#ifndef __c6_modelo_FK_simul_coleta_dados_h__
#define __c6_modelo_FK_simul_coleta_dados_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_c6_ResolvedFunctionInfo
#define typedef_c6_ResolvedFunctionInfo

typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c6_ResolvedFunctionInfo;

#endif                                 /*typedef_c6_ResolvedFunctionInfo*/

#ifndef typedef_SFc6_modelo_FK_simul_coleta_dadosInstanceStruct
#define typedef_SFc6_modelo_FK_simul_coleta_dadosInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c6_sfEvent;
  boolean_T c6_isStable;
  boolean_T c6_doneDoubleBufferReInit;
  uint8_T c6_is_active_c6_modelo_FK_simul_coleta_dados;
  uint32_T c6_method;
  boolean_T c6_method_not_empty;
  uint32_T c6_state[2];
  boolean_T c6_state_not_empty;
  uint32_T c6_b_method;
  boolean_T c6_b_method_not_empty;
  uint32_T c6_b_state;
  boolean_T c6_b_state_not_empty;
  uint32_T c6_c_state[2];
  boolean_T c6_c_state_not_empty;
  uint32_T c6_d_state[625];
  boolean_T c6_d_state_not_empty;
} SFc6_modelo_FK_simul_coleta_dadosInstanceStruct;

#endif                                 /*typedef_SFc6_modelo_FK_simul_coleta_dadosInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c6_modelo_FK_simul_coleta_dados_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c6_modelo_FK_simul_coleta_dados_get_check_sum(mxArray *plhs[]);
extern void c6_modelo_FK_simul_coleta_dados_method_dispatcher(SimStruct *S,
  int_T method, void *data);

#endif
