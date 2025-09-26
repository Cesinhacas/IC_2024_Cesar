#ifndef __Tetraedro_model_sem_sim_com_FK_sfun_h__
#define __Tetraedro_model_sem_sim_com_FK_sfun_h__

/* Include files */
#define S_FUNCTION_NAME                sf_sfun
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"
#include "sfcdebug.h"
#define rtInf                          (mxGetInf())
#define rtMinusInf                     (-(mxGetInf()))
#define rtNaN                          (mxGetNaN())
#define rtIsNaN(X)                     ((int)mxIsNaN(X))
#define rtIsInf(X)                     ((int)mxIsInf(X))

struct SfDebugInstanceStruct;
extern struct SfDebugInstanceStruct* sfGlobalDebugInstanceStruct;

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */
extern uint32_T _Tetraedro_model_sem_sim_com_FKMachineNumber_;
extern real_T _sfTime_;

/* Variable Definitions */

/* Function Declarations */
extern void Tetraedro_model_sem_sim_com_FK_initializer(void);
extern void Tetraedro_model_sem_sim_com_FK_terminator(void);

/* Function Definitions */

/* We load infoStruct for rtw_optimation_info on demand in mdlSetWorkWidths and
   free it immediately in mdlStart. Given that this is machine-wide as
   opposed to chart specific, we use NULL check to make sure it gets loaded
   and unloaded once per machine even though the  methods mdlSetWorkWidths/mdlStart
   are chart/instance specific. The following methods abstract this out. */
extern mxArray* load_Tetraedro_model_sem_sim_com_FK_optimization_info(void);
extern void unload_Tetraedro_model_sem_sim_com_FK_optimization_info(void);

#endif
