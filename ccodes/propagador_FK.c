/*
 * File: propagador_FK.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 04-Nov-2025 17:35:10
 */

/* Include Files */
#include "propagador_FK.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const double u_gyro[3]
 *                double Dt
 *                const double PT_est[36]
 *                const double x_est[7]
 *                const double Q[36]
 *                double i_in
 *                double x_prop[7]
 *                double PT_prop[36]
 *                double *i_out
 * Return Type  : void
 */
void propagador_FK(const double u_gyro[3], double Dt, const double PT_est[36],
                   const double x_est[7], const double Q[36], double i_in,
                   double x_prop[7], double PT_prop[36], double *i_out)
{
  static const double d_a[36] = {
      -0.5, -0.0, -0.0, 0.0, 0.0, 0.0, -0.0, -0.5, -0.0, 0.0, 0.0, 0.0,
      -0.0, -0.0, -0.5, 0.0, 0.0, 0.0, 0.0,  0.0,  0.0,  1.0, 0.0, 0.0,
      0.0,  0.0,  0.0,  0.0, 1.0, 0.0, 0.0,  0.0,  0.0,  0.0, 0.0, 1.0};
  static const double dv[36] = {
      -0.5, -0.0, -0.0, 0.0, 0.0, 0.0, -0.0, -0.5, -0.0, 0.0, 0.0, 0.0,
      -0.0, -0.0, -0.5, 0.0, 0.0, 0.0, 0.0,  0.0,  0.0,  1.0, 0.0, 0.0,
      0.0,  0.0,  0.0,  0.0, 1.0, 0.0, 0.0,  0.0,  0.0,  0.0, 0.0, 1.0};
  static const signed char iv[18] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     1, 0, 0, 0, 1, 0, 0, 0, 1};
  static const signed char b_a[16] = {1, 0, 0, 0, 0, 1, 0, 0,
                                      0, 0, 1, 0, 0, 0, 0, 1};
  static const signed char c_b[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  double PhiT[36];
  double QT[36];
  double b_PhiT[36];
  double c_a[36];
  double y_tmp[36];
  double a[16];
  double L[9];
  double e_a[9];
  double f_a[9];
  double g_a[9];
  double q_prop[4];
  double M_tmp;
  double Th_idx_0;
  double Th_idx_1;
  double a_tmp;
  double absxk;
  double b;
  double b_b;
  double b_scale;
  double d;
  double scale;
  double t;
  double y;
  int PhiT_tmp;
  int b_PhiT_tmp;
  int b_i;
  int c_PhiT_tmp;
  int i;
  signed char b_I[9];
  *i_out = i_in + 1.0;
  /*  ================== Propagação ================== */
  /*  ------ Propagação do Estado */
  /*  São medidos os Girômetros e sua saída subtraida */
  /*  do bias é integrada no período de propagação */
  /*  Matriz de atualização do quaternion */
  scale = 3.3121686421112381E-170;
  b_scale = 3.3121686421112381E-170;
  d = u_gyro[0] * Dt;
  Th_idx_0 = d;
  absxk = fabs(d);
  if (absxk > 3.3121686421112381E-170) {
    M_tmp = 1.0;
    scale = absxk;
    y = 1.0;
    b_scale = absxk;
  } else {
    absxk /= 3.3121686421112381E-170;
    M_tmp = absxk * absxk;
    y = absxk * absxk;
  }
  d = u_gyro[1] * Dt;
  Th_idx_1 = d;
  absxk = fabs(d);
  if (absxk > scale) {
    t = scale / absxk;
    M_tmp = M_tmp * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    M_tmp += t * t;
  }
  if (absxk > b_scale) {
    t = b_scale / absxk;
    y = y * t * t + 1.0;
    b_scale = absxk;
  } else {
    t = absxk / b_scale;
    y += t * t;
  }
  d = u_gyro[2] * Dt;
  absxk = fabs(d);
  if (absxk > scale) {
    t = scale / absxk;
    M_tmp = M_tmp * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    M_tmp += t * t;
  }
  if (absxk > b_scale) {
    t = b_scale / absxk;
    y = y * t * t + 1.0;
    b_scale = absxk;
  } else {
    t = absxk / b_scale;
    y += t * t;
  }
  M_tmp = scale * sqrt(M_tmp);
  b = cos(M_tmp / 2.0);
  y = b_scale * sqrt(y);
  b_b = sin(y / 2.0);
  a_tmp = 0.0 * b_b / M_tmp;
  a[0] = a_tmp;
  y = d * b_b / M_tmp;
  a[4] = y;
  t = -Th_idx_1 * b_b / M_tmp;
  a[8] = t;
  scale = Th_idx_0 * b_b / M_tmp;
  a[12] = scale;
  absxk = -d * b_b / M_tmp;
  a[1] = absxk;
  a[5] = a_tmp;
  a[9] = scale;
  scale = Th_idx_1 * b_b / M_tmp;
  a[13] = scale;
  a[2] = scale;
  scale = -Th_idx_0 * b_b / M_tmp;
  a[6] = scale;
  a[10] = a_tmp;
  a[14] = y;
  a[3] = scale;
  a[7] = t;
  a[11] = absxk;
  a[15] = a_tmp;
  for (i = 0; i < 16; i++) {
    a[i] += (double)b_a[i] * b;
  }
  d = x_est[0];
  absxk = x_est[1];
  y = x_est[2];
  b_b = x_est[3];
  for (b_i = 0; b_i < 4; b_i++) {
    a_tmp = ((a[b_i] * d + a[b_i + 4] * absxk) + a[b_i + 8] * y) +
            a[b_i + 12] * b_b;
    q_prop[b_i] = a_tmp;
    x_prop[b_i] = a_tmp;
  }
  x_prop[4] = x_est[4];
  x_prop[5] = x_est[5];
  x_prop[6] = x_est[6];
  /*  Matriz Constante // A ser executado fora dessa função */
  for (i = 0; i < 6; i++) {
    for (PhiT_tmp = 0; PhiT_tmp < 6; PhiT_tmp++) {
      d = 0.0;
      for (b_i = 0; b_i < 6; b_i++) {
        d += d_a[i + 6 * b_i] * Q[b_i + 6 * PhiT_tmp];
      }
      c_a[i + 6 * PhiT_tmp] = d;
    }
    for (PhiT_tmp = 0; PhiT_tmp < 6; PhiT_tmp++) {
      d = 0.0;
      for (b_i = 0; b_i < 6; b_i++) {
        d += c_a[i + 6 * b_i] * dv[b_i + 6 * PhiT_tmp];
      }
      QT[i + 6 * PhiT_tmp] = d;
    }
  }
  /*  --------------------- */
  scale = 3.3121686421112381E-170;
  y = 2.0 * q_prop[3];
  b_scale = 3.3121686421112381E-170;
  absxk = fabs(q_prop[0]);
  if (absxk > 3.3121686421112381E-170) {
    b_b = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    b_b = t * t;
  }
  absxk = fabs(x_est[0]);
  if (absxk > 3.3121686421112381E-170) {
    a_tmp = 1.0;
    b_scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    a_tmp = t * t;
  }
  absxk = fabs(q_prop[1]);
  if (absxk > scale) {
    t = scale / absxk;
    b_b = b_b * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    b_b += t * t;
  }
  absxk = fabs(x_est[1]);
  if (absxk > b_scale) {
    t = b_scale / absxk;
    a_tmp = a_tmp * t * t + 1.0;
    b_scale = absxk;
  } else {
    t = absxk / b_scale;
    a_tmp += t * t;
  }
  absxk = fabs(q_prop[2]);
  if (absxk > scale) {
    t = scale / absxk;
    b_b = b_b * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    b_b += t * t;
  }
  absxk = fabs(x_est[2]);
  if (absxk > b_scale) {
    t = b_scale / absxk;
    a_tmp = a_tmp * t * t + 1.0;
    b_scale = absxk;
  } else {
    t = absxk / b_scale;
    a_tmp += t * t;
  }
  b_b = scale * sqrt(b_b);
  b_b = q_prop[3] * q_prop[3] - b_b * b_b;
  a_tmp = b_scale * sqrt(a_tmp);
  a_tmp = x_est[3] * x_est[3] - a_tmp * a_tmp;
  absxk = 2.0 * x_est[3];
  /*  ------ Propagação da Matriz de Covariância */
  L[0] = y * 0.0;
  L[3] = y * q_prop[2];
  L[6] = y * -q_prop[1];
  L[1] = y * -q_prop[2];
  L[4] = y * 0.0;
  L[7] = y * q_prop[0];
  L[2] = y * q_prop[1];
  L[5] = y * -q_prop[0];
  L[8] = y * 0.0;
  for (i = 0; i < 3; i++) {
    e_a[3 * i] = b_b * (double)c_b[3 * i] + 2.0 * q_prop[0] * q_prop[i];
    f_a[3 * i] = a_tmp * (double)c_b[i] + 2.0 * x_est[i] * x_est[0];
    b_i = 3 * i + 1;
    e_a[b_i] = b_b * (double)c_b[b_i] + 2.0 * q_prop[1] * q_prop[i];
    f_a[b_i] = a_tmp * (double)c_b[i + 3] + 2.0 * x_est[i] * x_est[1];
    b_i = 3 * i + 2;
    e_a[b_i] = b_b * (double)c_b[b_i] + 2.0 * q_prop[2] * q_prop[i];
    f_a[b_i] = a_tmp * (double)c_b[i + 6] + 2.0 * x_est[i] * x_est[2];
  }
  g_a[0] = absxk * 0.0;
  g_a[1] = absxk * x_est[2];
  g_a[2] = absxk * -x_est[1];
  g_a[3] = absxk * -x_est[2];
  g_a[4] = absxk * 0.0;
  g_a[5] = absxk * x_est[0];
  g_a[6] = absxk * x_est[1];
  g_a[7] = absxk * -x_est[0];
  g_a[8] = absxk * 0.0;
  for (i = 0; i < 9; i++) {
    e_a[i] += L[i];
    f_a[i] += g_a[i];
  }
  for (i = 0; i < 3; i++) {
    d = e_a[i];
    absxk = e_a[i + 3];
    y = e_a[i + 6];
    for (PhiT_tmp = 0; PhiT_tmp < 3; PhiT_tmp++) {
      L[i + 3 * PhiT_tmp] =
          (d * f_a[3 * PhiT_tmp] + absxk * f_a[3 * PhiT_tmp + 1]) +
          y * f_a[3 * PhiT_tmp + 2];
    }
  }
  for (i = 0; i < 9; i++) {
    b_I[i] = 0;
  }
  /*  Integral Trapézio */
  for (b_i = 0; b_i < 3; b_i++) {
    b_I[b_i + 3 * b_i] = 1;
    d = L[3 * b_i];
    PhiT[6 * b_i] = d;
    b_PhiT_tmp = 3 * b_i + 1;
    absxk = L[b_PhiT_tmp];
    PhiT[6 * b_i + 1] = absxk;
    c_PhiT_tmp = 3 * b_i + 2;
    y = L[c_PhiT_tmp];
    PhiT[6 * b_i + 2] = y;
    PhiT_tmp = 6 * (b_i + 3);
    PhiT[PhiT_tmp] = -0.5 * (d + (double)b_I[3 * b_i]) * Dt / 2.0;
    PhiT[PhiT_tmp + 1] = -0.5 * (absxk + (double)b_I[b_PhiT_tmp]) * Dt / 2.0;
    PhiT[PhiT_tmp + 2] = -0.5 * (y + (double)b_I[c_PhiT_tmp]) * Dt / 2.0;
  }
  for (i = 0; i < 6; i++) {
    PhiT[6 * i + 3] = iv[3 * i];
    PhiT[6 * i + 4] = iv[3 * i + 1];
    PhiT[6 * i + 5] = iv[3 * i + 2];
  }
  /*  Integral Trapézio */
  for (i = 0; i < 6; i++) {
    for (PhiT_tmp = 0; PhiT_tmp < 6; PhiT_tmp++) {
      b_PhiT_tmp = i + 6 * PhiT_tmp;
      y_tmp[PhiT_tmp + 6 * i] = PhiT[b_PhiT_tmp];
      d = 0.0;
      absxk = 0.0;
      for (b_i = 0; b_i < 6; b_i++) {
        y = PhiT[i + 6 * b_i];
        c_PhiT_tmp = b_i + 6 * PhiT_tmp;
        d += y * PT_est[c_PhiT_tmp];
        absxk += y * QT[c_PhiT_tmp];
      }
      c_a[b_PhiT_tmp] = absxk;
      b_PhiT[b_PhiT_tmp] = d;
    }
  }
  for (i = 0; i < 6; i++) {
    for (PhiT_tmp = 0; PhiT_tmp < 6; PhiT_tmp++) {
      d = 0.0;
      absxk = 0.0;
      for (b_i = 0; b_i < 6; b_i++) {
        y = y_tmp[b_i + 6 * PhiT_tmp];
        c_PhiT_tmp = i + 6 * b_i;
        d += c_a[c_PhiT_tmp] * y;
        absxk += b_PhiT[c_PhiT_tmp] * y;
      }
      b_i = i + 6 * PhiT_tmp;
      PT_prop[b_i] = absxk + (d + QT[b_i]) * Dt / 2.0;
    }
  }
}

/*
 * File trailer for propagador_FK.c
 *
 * [EOF]
 */
