#include <math.h>
#include "FK.h"

void FK_prop(float *u_gyro, double Dt, double PT_est[6][6], double *x_est, double Q[6][6], uint8_t i_in, double *x_prop, double PT_prop[6][6], uint8_t *i_out)
{
    double q_est[4], b_est[3], Th[3], Omega4[4][4], M[4][4], q_prop[4], Omega3_prop[3][3], A_prop[3][3], q_q_2t[3][3], q_sqrd_norm, Omega3_est[3][3], A_est[3][3], L[3][3], KK[3][3], PhiT[6][6];
    double cosTh, sinTh, normTh;

    // contagem de iteração
    i_out = i_in + 1;

    // Propagação de estado
    for (uint8_t i = 0; i < 4; i++)
    {
        q_est[i] = x_est[i];
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        b_est[i] = x_est[i + 4];
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        Th[i] = u_gyro[i] * Dt;
    }

    Omega4[0][0] = 0;
    Omega4[0][1] = Th[2];
    Omega4[0][2] = -Th[1];
    Omega4[0][3] = Th[0];
    Omega4[1][0] = -Th[2];
    Omega4[1][1] = 0;
    Omega4[1][2] = Th[0];
    Omega4[1][3] = Th[1];
    Omega4[2][0] = Th[1];
    Omega4[2][1] = -Th[0];
    Omega4[2][2] = 0;
    Omega4[2][3] = Th[2];
    Omega4[3][0] = -Th[0];
    Omega4[3][1] = -Th[1];
    Omega4[3][2] = -Th[2];
    Omega4[3][3] = 0;

    normTh = sqrt(Th[0] * Th[0] + Th[1] * Th[1] + Th[2] * Th[2]);
    cosTh = cos(normTh / 2) / normTh;
    sinTh = sin(normTh / 2) / normTh;

   
    for (uint8_t i = 0; i < 4; i++)
    {
        q_prop[i] = q_est[i];
        for (uint8_t j = 0; j < 4; j++)
        {
            M[i][j] = 0;
        }
    }
    for (uint8_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if (i == j)
            {
                M[i][j] = cosTh;
            }
            else
            {
                M[i][j] += sinTh * Omega4[i][j];
            }
        }        
    }


    for (uint8_t i = 0; i < 4; i++)
    {
        q_prop[i] = M[i][0] * q_est[0] + M[i][1] * q_est[1] + M[i][2] * q_est[2] + M[i][3] * q_est[3];
    }

    for (uint8_t i = 0; i < 4; i++)
    {
        x_prop[i] = q_prop[i];
    }
    for (uint8_t i = 0; i < 3; i++)
    {
        x_prop[i + 4] = b_est[i];
    }    

    // Propagate covariance
    Omega3_prop[0][0] = 0;
    Omega3_prop[0][1] = q_prop[2];
    Omega3_prop[0][2] = -q_prop[1];
    Omega3_prop[1][0] = -q_prop[2];
    Omega3_prop[1][1] = 0;
    Omega3_prop[1][2] = q_prop[0];
    Omega3_prop[2][0] = q_prop[1];
    Omega3_prop[2][1] = -q_prop[0];
    Omega3_prop[2][2] = 0;

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            q_q_2t[i][j] = 2*q_prop[i + 1] * q_prop[j + 1];
        }
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        q_sqrd_norm -= q_prop[i] * q_prop[i];
    }
    q_sqrd_norm += q_prop[0] * q_prop[0];

    for(uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            if(i == j)
            {
                A_prop[i][j] += q_sqrd_norm + q_q_2t[i][j];
            }
            else
            {
                A_prop[i][j] += q_q_2t[i][j] + 2*q_prop[4]*Omega3_prop[i][j];
            }
        }
    }

    Omega3_est[0][0] = 0;
    Omega3_est[0][1] = q_est[2];
    Omega3_est[0][2] = -q_est[1];
    Omega3_est[1][0] = -q_est[2];
    Omega3_est[1][1] = 0;
    Omega3_est[1][2] = q_est[0];
    Omega3_est[2][0] = q_est[1];
    Omega3_est[2][1] = -q_est[0];
    Omega3_est[2][2] = 0;

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            q_q_2t[i][j] = 2*q_est[i + 1] * q_est[j + 1];
        }
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        q_sqrd_norm -= q_est[i] * q_est[i];
    }
    q_sqrd_norm += q_est[0] * q_est[0];

    for(uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            if(i == j)
            {
                A_est[i][j] += q_sqrd_norm + q_q_2t[i][j];
            }
            else
            {
                A_est[i][j] += q_q_2t[i][j] + 2*q_est[4]*Omega3_est[i][j];
            }
        }
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            L[i][j] = A_prop[i][j] - A_est[j][i];
        }
        L[i][i] += 1;
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            KK[i][j] = -0.5 * (L[i][j] + 1) * Dt/2;
        }
    }

    for (uint8_t i = 0; i < 6; i++)
    {
        for (uint8_t j = 0; j < 6; j++)
        {
            if(i < 3 && j < 3)
            {
                // Quadrante superior esquerdo: L[3x3]
                PhiT[i][j] = L[i][j];
            }
            else if(i < 3 && j > 2)
            {
                // Quadrante superior direito: KK[3x3]
                PhiT[i][j] = KK[i][j - 3];
            }
            else if(i > 2 && j < 3)
            {
                // Quadrante inferior esquerdo: I[3x3] (matriz identidade)
                if((i - 3) == j)
                {
                    PhiT[i][j] = 1;
                }
                else
                {
                    PhiT[i][j] = 0;
                }
            }
            else if(i > 2 && j > 2)
            {
                // Quadrante inferior direito: 0[3x3] (matriz zero)
                PhiT[i][j] = 0;
            }
        }
    }
}