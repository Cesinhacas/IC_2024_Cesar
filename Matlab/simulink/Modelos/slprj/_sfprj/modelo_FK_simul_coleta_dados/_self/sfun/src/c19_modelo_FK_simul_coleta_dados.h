#ifndef __c19_modelo_FK_simul_coleta_dados_h__
#define __c19_modelo_FK_simul_coleta_dados_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_c19_ResolvedFunctionInfo
#define typedef_c19_ResolvedFunctionInfo

typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c19_ResolvedFunctionInfo;

#endif                                 /*typedef_c19_ResolvedFunctionInfo*/

#ifndef typedef_SFc19_modelo_FK_simul_coleta_dadosInstanceStruct
#define typedef_SFc19_modelo_FK_simul_coleta_dadosInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c19_sfEvent;
  boolean_T c19_isStable;
  boolean_T c19_doneDoubleBufferReInit;
  uint8_T c19_is_active_c19_modelo_FK_simul_coleta_dados;
} SFc19_modelo_FK_simul_coleta_dadosInstanceStruct;

#endif                                 /*typedef_SFc19_modelo_FK_simul_coleta_dadosInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c19_modelo_FK_simul_coleta_dados_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c19_modelo_FK_simul_coleta_dados_get_check_sum(mxArray *plhs[]);
extern void c19_modelo_FK_simul_coleta_dados_method_dispatcher(SimStruct *S,
  int_T method, void *data);

#endif
