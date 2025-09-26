/* Include files */

#include "Tetraedro_model_sem_sim_com_FK_sfun.h"
#include "Tetraedro_model_sem_sim_com_FK_sfun_debug_macros.h"
#include "c1_Tetraedro_model_sem_sim_com_FK.h"
#include "c2_Tetraedro_model_sem_sim_com_FK.h"
#include "c3_Tetraedro_model_sem_sim_com_FK.h"
#include "c4_Tetraedro_model_sem_sim_com_FK.h"
#include "c5_Tetraedro_model_sem_sim_com_FK.h"
#include "c6_Tetraedro_model_sem_sim_com_FK.h"
#include "c7_Tetraedro_model_sem_sim_com_FK.h"
#include "c10_Tetraedro_model_sem_sim_com_FK.h"
#include "c13_Tetraedro_model_sem_sim_com_FK.h"
#include "c14_Tetraedro_model_sem_sim_com_FK.h"
#include "c15_Tetraedro_model_sem_sim_com_FK.h"
#include "c16_Tetraedro_model_sem_sim_com_FK.h"
#include "c19_Tetraedro_model_sem_sim_com_FK.h"
#include "c21_Tetraedro_model_sem_sim_com_FK.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _Tetraedro_model_sem_sim_com_FKMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void Tetraedro_model_sem_sim_com_FK_initializer(void)
{
}

void Tetraedro_model_sem_sim_com_FK_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_Tetraedro_model_sem_sim_com_FK_method_dispatcher(SimStruct
  *simstructPtr, unsigned int chartFileNumber, const char* specsCksum, int_T
  method, void *data)
{
  if (chartFileNumber==1) {
    c1_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==7) {
    c7_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==10) {
    c10_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==13) {
    c13_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==14) {
    c14_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==15) {
    c15_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==16) {
    c16_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==19) {
    c19_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  if (chartFileNumber==21) {
    c21_Tetraedro_model_sem_sim_com_FK_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  return 0;
}

unsigned int sf_Tetraedro_model_sem_sim_com_FK_process_check_sum_call( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1987531821U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3029799096U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2503700043U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3400973991U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2382031844U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3217239307U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2436449340U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(133798213U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_Tetraedro_model_sem_sim_com_FK_get_check_sum(mxArray
            *plhs[]);
          sf_c1_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_Tetraedro_model_sem_sim_com_FK_get_check_sum(mxArray
            *plhs[]);
          sf_c2_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_Tetraedro_model_sem_sim_com_FK_get_check_sum(mxArray
            *plhs[]);
          sf_c3_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_Tetraedro_model_sem_sim_com_FK_get_check_sum(mxArray
            *plhs[]);
          sf_c4_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_Tetraedro_model_sem_sim_com_FK_get_check_sum(mxArray
            *plhs[]);
          sf_c5_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_Tetraedro_model_sem_sim_com_FK_get_check_sum(mxArray
            *plhs[]);
          sf_c6_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 7:
        {
          extern void sf_c7_Tetraedro_model_sem_sim_com_FK_get_check_sum(mxArray
            *plhs[]);
          sf_c7_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 10:
        {
          extern void sf_c10_Tetraedro_model_sem_sim_com_FK_get_check_sum
            (mxArray *plhs[]);
          sf_c10_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 13:
        {
          extern void sf_c13_Tetraedro_model_sem_sim_com_FK_get_check_sum
            (mxArray *plhs[]);
          sf_c13_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 14:
        {
          extern void sf_c14_Tetraedro_model_sem_sim_com_FK_get_check_sum
            (mxArray *plhs[]);
          sf_c14_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 15:
        {
          extern void sf_c15_Tetraedro_model_sem_sim_com_FK_get_check_sum
            (mxArray *plhs[]);
          sf_c15_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 16:
        {
          extern void sf_c16_Tetraedro_model_sem_sim_com_FK_get_check_sum
            (mxArray *plhs[]);
          sf_c16_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 19:
        {
          extern void sf_c19_Tetraedro_model_sem_sim_com_FK_get_check_sum
            (mxArray *plhs[]);
          sf_c19_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       case 21:
        {
          extern void sf_c21_Tetraedro_model_sem_sim_com_FK_get_check_sum
            (mxArray *plhs[]);
          sf_c21_Tetraedro_model_sem_sim_com_FK_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3564696471U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(678668628U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1090454852U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3896867807U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(348655025U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3315343035U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1829144047U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3455202562U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_Tetraedro_model_sem_sim_com_FK_autoinheritance_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "MsEQmWqqQd8xJ4XfbdzCkG") == 0) {
          extern mxArray
            *sf_c1_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c1_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "lwKef8n1QUQaqypxIl9cnC") == 0) {
          extern mxArray
            *sf_c2_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c2_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "p6peyDa4LZBW4ujGt4Y1AF") == 0) {
          extern mxArray
            *sf_c3_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c3_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "DQCql0qF0M5bHB0tiPvB1") == 0) {
          extern mxArray
            *sf_c4_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c4_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "MsEQmWqqQd8xJ4XfbdzCkG") == 0) {
          extern mxArray
            *sf_c5_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c5_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "1NxDvSQpsHZkTPZYlcwpoE") == 0) {
          extern mxArray
            *sf_c6_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c6_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 7:
      {
        if (strcmp(aiChksum, "VeK1W32wc9ThgoBiMm7tcD") == 0) {
          extern mxArray
            *sf_c7_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c7_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 10:
      {
        if (strcmp(aiChksum, "h8uWlnEYAMX1P1ewEH7KuB") == 0) {
          extern mxArray
            *sf_c10_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c10_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 13:
      {
        if (strcmp(aiChksum, "7zXTKVNRxdGbKgBpW1HOjE") == 0) {
          extern mxArray
            *sf_c13_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c13_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 14:
      {
        if (strcmp(aiChksum, "7aLrJi0jJ0S3LP2dWyv9k") == 0) {
          extern mxArray
            *sf_c14_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c14_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 15:
      {
        if (strcmp(aiChksum, "H2dlIkbEksujVsUIC0xE7G") == 0) {
          extern mxArray
            *sf_c15_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c15_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 16:
      {
        if (strcmp(aiChksum, "p6peyDa4LZBW4ujGt4Y1AF") == 0) {
          extern mxArray
            *sf_c16_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c16_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 19:
      {
        if (strcmp(aiChksum, "BqcDgCUqwSuA4vNJRRmBMC") == 0) {
          extern mxArray
            *sf_c19_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c19_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 21:
      {
        if (strcmp(aiChksum, "6F1m6QJe7g8Hca7hZbbefE") == 0) {
          extern mxArray
            *sf_c21_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info(void);
          plhs[0] =
            sf_c21_Tetraedro_model_sem_sim_com_FK_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
  ( int nlhs, mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray
          *sf_c1_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray
          *sf_c2_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray
          *sf_c3_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray
          *sf_c4_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray
          *sf_c5_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray
          *sf_c6_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 7:
      {
        extern const mxArray
          *sf_c7_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c7_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 10:
      {
        extern const mxArray
          *sf_c10_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c10_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 13:
      {
        extern const mxArray
          *sf_c13_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c13_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 14:
      {
        extern const mxArray
          *sf_c14_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c14_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 15:
      {
        extern const mxArray
          *sf_c15_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c15_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 16:
      {
        extern const mxArray
          *sf_c16_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c16_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 19:
      {
        extern const mxArray
          *sf_c19_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c19_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 21:
      {
        extern const mxArray
          *sf_c21_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c21_Tetraedro_model_sem_sim_com_FK_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_Tetraedro_model_sem_sim_com_FK_third_party_uses_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "I2djRvfs42haF39lbGcrKE") == 0) {
          extern mxArray
            *sf_c1_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c1_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "AlsxNYUMAtTuHJA3AQzfKD") == 0) {
          extern mxArray
            *sf_c2_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c2_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "6RILy90kegE0msbIE8qFsD") == 0) {
          extern mxArray
            *sf_c3_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c3_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "egPaVPKBGXhfpT3qLeqLzF") == 0) {
          extern mxArray
            *sf_c4_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c4_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "I2djRvfs42haF39lbGcrKE") == 0) {
          extern mxArray
            *sf_c5_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c5_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "kOFWelOWEMGZP3kdf0kxjE") == 0) {
          extern mxArray
            *sf_c6_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c6_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "6TGkMoJTZnZgtaJuDcw0MG") == 0) {
          extern mxArray
            *sf_c7_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c7_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 10:
      {
        if (strcmp(tpChksum, "CHJBkXyPg026xMRFLWjoxE") == 0) {
          extern mxArray
            *sf_c10_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c10_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 13:
      {
        if (strcmp(tpChksum, "VceH2kJ8HBePdSSQDUYUwE") == 0) {
          extern mxArray
            *sf_c13_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c13_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 14:
      {
        if (strcmp(tpChksum, "aKGdEMDDdTa5lWYu8iUHSC") == 0) {
          extern mxArray
            *sf_c14_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c14_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 15:
      {
        if (strcmp(tpChksum, "dnbUP8rIOAO3EAs0nVotNC") == 0) {
          extern mxArray
            *sf_c15_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c15_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 16:
      {
        if (strcmp(tpChksum, "6RILy90kegE0msbIE8qFsD") == 0) {
          extern mxArray
            *sf_c16_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c16_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 19:
      {
        if (strcmp(tpChksum, "4GUIKMHRIGruagEiBj8ImB") == 0) {
          extern mxArray
            *sf_c19_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c19_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     case 21:
      {
        if (strcmp(tpChksum, "YSYMs5dHgujPbOm9wCGuRG") == 0) {
          extern mxArray
            *sf_c21_Tetraedro_model_sem_sim_com_FK_third_party_uses_info(void);
          plhs[0] = sf_c21_Tetraedro_model_sem_sim_com_FK_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void Tetraedro_model_sem_sim_com_FK_debug_initialize(struct
  SfDebugInstanceStruct* debugInstance)
{
  _Tetraedro_model_sem_sim_com_FKMachineNumber_ = sf_debug_initialize_machine
    (debugInstance,"Tetraedro_model_sem_sim_com_FK","sfun",0,14,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _Tetraedro_model_sem_sim_com_FKMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _Tetraedro_model_sem_sim_com_FKMachineNumber_,0);
}

void Tetraedro_model_sem_sim_com_FK_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_Tetraedro_model_sem_sim_com_FK_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info(
      "Tetraedro_model_sem_sim_com_FK", "Tetraedro_model_sem_sim_com_FK");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_Tetraedro_model_sem_sim_com_FK_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
