/*
 * File: test1.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Oct-2024 09:49:55
 */

/* Include Files */
#include "test1.h"
#include "rt_nonfinite.h"
#include "test1_data.h"
#include "test1_initialize.h"
#include "tic.h"
#include "toc.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double d;
  double d1;
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }
  return y;
}

/*
 * Arguments    : const double Dados_Corrompido[3336]
 *                double *Time
 *                double p1[9]
 * Return Type  : void
 */
void test1(const double Dados_Corrompido[3336], double *Time, double p1[9])
{
  double B[10008];
  double H[10008];
  double y[1112];
  double A[81];
  double X[9];
  double b_psi7_tmp;
  double b_psi7_tmp_tmp;
  double b_psi8_tmp;
  double c_psi7_tmp;
  double c_psi8_tmp;
  double d_psi7_tmp;
  double d_psi8_tmp;
  double divs;
  double divs_tmp;
  double e_psi7_tmp;
  double e_psi8_tmp;
  double n1;
  double n1_tmp;
  double n3;
  double n3_tmp;
  double n4;
  double n5;
  double n6;
  double psi7;
  double psi7_tmp;
  double psi7_tmp_tmp;
  double psi8;
  double psi8_tmp;
  double s;
  double smax;
  int b_tmp;
  int i;
  int i1;
  int j;
  int jA;
  int jBcol;
  int jp1j;
  int k;
  int mmj_tmp;
  int temp_tmp;
  signed char ipiv[9];
  signed char i2;
  if (!isInitialized_test1) {
    test1_initialize();
  }
  /*  Dados_Corrompido é a variável que simula as medidas dos sensores. */
  /*   */
  /*  Retona-se o parâmetro p, um vetor semelhante a p0, onde os três parâmetros
   * são as estimativas dos fatores de escala, do 4 ao 6 são as estimativas para
   * os offsets (bias) e os três últimos valores são os ângulos Rho, Phi e
   * Lambda. */
  tic();
  for (k = 0; k < 1112; k++) {
    smax = Dados_Corrompido[3 * k + 1];
    y[k] = smax * smax;
    s = Dados_Corrompido[3 * k];
    psi8_tmp = Dados_Corrompido[3 * k + 2];
    H[k] = s * s;
    H[k + 1112] = s * smax;
    H[k + 2224] = s * psi8_tmp;
    H[k + 3336] = smax * psi8_tmp;
    H[k + 4448] = psi8_tmp * psi8_tmp;
    H[k + 5560] = s;
    H[k + 6672] = smax;
    H[k + 7784] = psi8_tmp;
    H[k + 8896] = 1.0;
  }
  for (i = 0; i < 9; i++) {
    for (i1 = 0; i1 < 9; i1++) {
      smax = 0.0;
      for (jA = 0; jA < 1112; jA++) {
        smax += H[jA + 1112 * i] * H[jA + 1112 * i1];
      }
      A[i + 9 * i1] = smax;
    }
  }
  for (i = 0; i < 1112; i++) {
    for (i1 = 0; i1 < 9; i1++) {
      B[i1 + 9 * i] = H[i + 1112 * i1];
    }
  }
  for (i = 0; i < 9; i++) {
    ipiv[i] = (signed char)(i + 1);
  }
  for (j = 0; j < 8; j++) {
    mmj_tmp = 7 - j;
    b_tmp = j * 10;
    jp1j = b_tmp + 2;
    jA = 9 - j;
    jBcol = 0;
    smax = fabs(A[b_tmp]);
    for (k = 2; k <= jA; k++) {
      s = fabs(A[(b_tmp + k) - 1]);
      if (s > smax) {
        jBcol = k - 1;
        smax = s;
      }
    }
    if (A[b_tmp + jBcol] != 0.0) {
      if (jBcol != 0) {
        jA = j + jBcol;
        ipiv[j] = (signed char)(jA + 1);
        for (k = 0; k < 9; k++) {
          temp_tmp = j + k * 9;
          smax = A[temp_tmp];
          jBcol = jA + k * 9;
          A[temp_tmp] = A[jBcol];
          A[jBcol] = smax;
        }
      }
      i = (b_tmp - j) + 9;
      for (temp_tmp = jp1j; temp_tmp <= i; temp_tmp++) {
        A[temp_tmp - 1] /= A[b_tmp];
      }
    }
    jA = b_tmp;
    for (jp1j = 0; jp1j <= mmj_tmp; jp1j++) {
      smax = A[(b_tmp + jp1j * 9) + 9];
      if (smax != 0.0) {
        i = jA + 11;
        i1 = (jA - j) + 18;
        for (jBcol = i; jBcol <= i1; jBcol++) {
          A[jBcol - 1] += A[((b_tmp + jBcol) - jA) - 10] * -smax;
        }
      }
      jA += 9;
    }
    i2 = ipiv[j];
    if (i2 != j + 1) {
      for (jp1j = 0; jp1j < 1112; jp1j++) {
        temp_tmp = j + 9 * jp1j;
        smax = B[temp_tmp];
        mmj_tmp = (i2 + 9 * jp1j) - 1;
        B[temp_tmp] = B[mmj_tmp];
        B[mmj_tmp] = smax;
      }
    }
  }
  for (j = 0; j < 1112; j++) {
    jBcol = 9 * j;
    for (k = 0; k < 9; k++) {
      jA = 9 * k;
      i = k + jBcol;
      if (B[i] != 0.0) {
        i1 = k + 2;
        for (temp_tmp = i1; temp_tmp < 10; temp_tmp++) {
          mmj_tmp = (temp_tmp + jBcol) - 1;
          B[mmj_tmp] -= B[i] * A[(temp_tmp + jA) - 1];
        }
      }
    }
  }
  for (j = 0; j < 1112; j++) {
    jBcol = 9 * j;
    for (k = 8; k >= 0; k--) {
      jA = 9 * k;
      i = k + jBcol;
      smax = B[i];
      if (smax != 0.0) {
        B[i] = smax / A[k + jA];
        for (temp_tmp = 0; temp_tmp < k; temp_tmp++) {
          mmj_tmp = temp_tmp + jBcol;
          B[mmj_tmp] -= B[i] * A[temp_tmp + jA];
        }
      }
    }
    y[j] = -y[j];
  }
  for (i = 0; i < 9; i++) {
    smax = 0.0;
    for (i1 = 0; i1 < 1112; i1++) {
      smax += B[i + 9 * i1] * y[i1];
    }
    X[i] = smax;
  }
  psi7_tmp = X[1] * X[1];
  b_psi7_tmp = X[2] * X[2];
  c_psi7_tmp = X[3] * X[3];
  d_psi7_tmp = 4.0 * X[0] * X[4];
  psi7_tmp_tmp = X[1] * X[2];
  b_psi7_tmp_tmp = X[0] * c_psi7_tmp;
  e_psi7_tmp = (((X[4] * psi7_tmp - psi7_tmp_tmp * X[3]) + b_psi7_tmp) +
                b_psi7_tmp_tmp) -
               d_psi7_tmp;
  psi7 = 2.0 * e_psi7_tmp;
  /* m = 1; % magnitude local do campo magnético da terra */
  smax = X[5] * X[5];
  s = X[6] * X[6];
  psi8_tmp = X[7] * X[7];
  b_psi8_tmp = -psi7_tmp * psi8_tmp;
  n3 = 2.0 * X[1] * X[2] * X[6] * X[7];
  n4 = 2.0 * X[1] * X[3] * X[5] * X[7];
  n5 = b_psi7_tmp * s;
  n6 = 2.0 * X[2] * X[3] * X[5] * X[6];
  c_psi8_tmp = 4.0 * X[2] * X[5] * X[7];
  d_psi8_tmp = c_psi7_tmp * smax;
  e_psi8_tmp = 4.0 * X[0] * X[3] * X[6] * X[7];
  smax *= 4.0 * X[4];
  s *= d_psi7_tmp;
  psi8_tmp *= 4.0 * X[0];
  n1 = 16.0 * X[0] * X[4] * X[8];
  psi8 = (((((((((((((((b_psi8_tmp + 4.0 * X[4] * X[8] * psi7_tmp) -
                       4.0 * X[8] * X[1] * X[2] * X[3]) +
                      n3) +
                     n4) -
                    4.0 * X[4] * X[1] * X[5] * X[6]) -
                   n5) +
                  4.0 * X[8] * b_psi7_tmp) +
                 n6) -
                c_psi8_tmp) -
               d_psi8_tmp) +
              4.0 * X[0] * X[8] * c_psi7_tmp) +
             smax) +
            s) +
           psi8_tmp) -
          n1) -
         e_psi8_tmp;
  divs_tmp = rt_powd_snf(X[4], 3.0);
  divs = 2.0 * fabs(divs_tmp) * e_psi7_tmp;
  n1_tmp = 4.0 * psi7_tmp;
  n1 = (((((((((((((((b_psi8_tmp + n1_tmp * X[4] * X[8]) -
                     4.0 * X[1] * X[2] * X[3] * X[8]) +
                    n3) +
                   n4) -
                  4.0 * X[1] * X[4] * X[5] * X[6]) -
                 n5) +
                n6) +
               4.0 * b_psi7_tmp * X[8]) -
              c_psi8_tmp) -
             d_psi8_tmp) +
            4.0 * X[1] * c_psi7_tmp * X[8]) -
           e_psi8_tmp) +
          smax) +
         s) +
        psi8_tmp) -
       n1;
  n3_tmp = X[4] * X[4];
  c_psi8_tmp = ((2.0 * psi7_tmp * c_psi7_tmp * X[4] - n1_tmp * n3_tmp) -
                psi7_tmp_tmp * rt_powd_snf(X[3], 3.0)) +
               b_psi7_tmp * c_psi7_tmp;
  d_psi8_tmp = 8.0 * X[0] * c_psi7_tmp * X[4];
  e_psi8_tmp = 16.0 * X[0] * n3_tmp;
  n3 = ((c_psi8_tmp + b_psi7_tmp_tmp) - d_psi8_tmp) + e_psi8_tmp;
  n4 = 4.0 * X[4] - c_psi7_tmp;
  n5 = d_psi7_tmp - b_psi7_tmp;
  n6 = 4.0 * X[0] - psi7_tmp;
  p1[0] = -(divs_tmp * sqrt(psi8 * (-c_psi7_tmp + 4.0 * X[4]))) / divs;
  p1[1] = -(divs_tmp * sqrt(psi8 * (-b_psi7_tmp + d_psi7_tmp))) / divs;
  p1[2] = -(divs_tmp * sqrt(psi8 * (-psi7_tmp + 4.0 * X[0]))) / divs;
  s = 2.0 * X[1] * X[4];
  psi8_tmp = X[2] * X[3];
  b_psi8_tmp = X[1] * X[3];
  p1[3] = -(((((c_psi7_tmp * X[5] + 2.0 * X[2] * X[7]) - 4.0 * X[4] * X[5]) -
              b_psi8_tmp * X[7]) +
             s * X[6]) -
            psi8_tmp * X[6]) /
          psi7;
  smax = 2.0 * X[0] * X[3];
  p1[4] = -(((((b_psi7_tmp * X[6] + smax * X[7]) - d_psi7_tmp * X[6]) -
              psi7_tmp_tmp * X[7]) +
             s * X[5]) -
            psi8_tmp * X[5]) /
          psi7;
  p1[5] = -(((((psi7_tmp * X[7] - 4.0 * X[0] * X[7]) + 2.0 * X[2] * X[5]) +
              smax * X[6]) -
             psi7_tmp_tmp * X[6]) -
            b_psi8_tmp * X[5]) /
          psi7;
  p1[6] = -atan((s - psi8_tmp) / (2.0 * n3_tmp * sqrt(-e_psi7_tmp / divs_tmp)));
  p1[7] = -atan(fabs(X[4]) * sqrt(n1 * n5) * (2.0 * X[2] - b_psi8_tmp) *
                sqrt(X[4] * n4 * n6 / n3) /
                (n3_tmp * sqrt(-e_psi7_tmp / X[4]) * sqrt(n1 * n6) *
                 sqrt(-(e_psi7_tmp * n4) / n3) *
                 sqrt(-(n4 * n5) / (X[4] * e_psi7_tmp))));
  p1[8] = -atan(
      X[3] / X[4] *
      sqrt(-(n3_tmp * e_psi7_tmp /
             (((c_psi8_tmp + X[0] * rt_powd_snf(X[3], 4.0)) - d_psi8_tmp) +
              e_psi8_tmp))));
  *Time = toc();
}

/*
 * File trailer for test1.c
 *
 * [EOF]
 */
