#include <math.h>

double GT[6][6], QT[6][6];

void FK_prop(float *u_gyro, double Dt, double PT_est[6][6], double *x_est, double Q[6][6], int i_in, double *x_prop, double PT_prop[6][6], int *i_out)
{
    double q_est[4], b_est[3], Th[3], Omega4[4][4], M[4][4], q_prop[4], Omega3_prop[3][3], A_prop[3][3], q_q_2t[3][3], q_sqrd_norm;
    double Omega3_est[3][3], A_est[3][3], L[3][3], KK[3][3], PhiT[6][6], SiG[6][6];
    double cosTh, sinTh, normTh;

    // contagem de iteração
    i_out = i_in + 1;

    // Propagação de estado
    for (int i = 0; i < 4; i++)
    {
        q_est[i] = x_est[i];
    }

    for (int i = 0; i < 3; i++)
    {
        b_est[i] = x_est[i + 4];
    }

    for (int i = 0; i < 3; i++)
    {
        Th[i] = u_gyro[i] * Dt;
    }

    // Omega4
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

    // Preparação para a matriz M
    normTh = sqrt(Th[0] * Th[0] + Th[1] * Th[1] + Th[2] * Th[2]);
    cosTh = cos(normTh / 2);
    sinTh = sin(normTh / 2) / normTh;

   
    for (int i = 0; i < 4; i++)
    {
        q_prop[i] = q_est[i];
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = 0;
        }
    }
    for (int i = 0; i < 4; i++)
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


    // calculo do estado propagado
    for (int i = 0; i < 4; i++)
    {
        q_prop[i] = M[i][0] * q_est[0] + M[i][1] * q_est[1] + M[i][2] * q_est[2] + M[i][3] * q_est[3];
    }

    for (int i = 0; i < 4; i++)
    {
        x_prop[i] = q_prop[i];
    }
    for (int i = 0; i < 3; i++)
    {
        x_prop[i + 4] = b_est[i];
    }    

    // Propagação da covariância de erro
    Omega3_prop[0][0] = 0;
    Omega3_prop[0][1] = q_prop[2];
    Omega3_prop[0][2] = -q_prop[1];
    Omega3_prop[1][0] = -q_prop[2];
    Omega3_prop[1][1] = 0;
    Omega3_prop[1][2] = q_prop[0];
    Omega3_prop[2][0] = q_prop[1];
    Omega3_prop[2][1] = -q_prop[0];
    Omega3_prop[2][2] = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            q_q_2t[i][j] = 2*q_prop[i] * q_prop[j];
        }
    }

    for (int i = 0; i < 3; i++)
    {
        q_sqrd_norm -= q_prop[i] * q_prop[i];
    }
    q_sqrd_norm += q_prop[3] * q_prop[3];

    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
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

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            q_q_2t[i][j] = 2*q_est[i] * q_est[j];
        }
    }

    for (int i = 0; i < 3; i++)
    {
        q_sqrd_norm -= q_est[i] * q_est[i];
    }
    q_sqrd_norm += q_est[3] * q_est[3];

    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
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

    // L = A_prop * A_est^T
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            L[i][j] = 0;
            for (int k = 0; k < count; k++)
            {
                L[i][j] += A_prop[i][k] * A_est[j][k];
            }
        }
    }
    for(int i = 0; i < 3; i++)
    {
        L[i][i] = L[i][i] + 1;
    }
    

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            KK[i][j] = -0.25 * L[i][j] * Dt;
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if(i < 3 && j < 3)
            {
                PhiT[i][j] = L[i][j];
            }
            else if(i < 3 && j > 2)
            {
                PhiT[i][j] = KK[i][j - 3];
            }
            else if(i > 2 && j < 3)
            {
                PhiT[i][j] = 0;
            }
            else if(i > 2 && j > 2)
            {
                if((i - 3) == j)
                {
                    PhiT[i][j] = 1;
                }
                else
                {
                    PhiT[i][j] = 0;
                }
            }
        }
    }

    // Cálculo ed SiG = (PhiT*QT*PhiT^T + QT)*Dt/2

    // Multiplicação PhiT*QT

    double temp[6][6] = {0};
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 0; k < 6; k++)
            {
                temp[i][j] += PhiT[i][k] * QT[k][j];
            }
        }
    }
    // Multiplicação (PhiT*QT)*PhiT^T
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            SiG[i][j] = 0;
            for (int k = 0; k < 6; k++)
            {
                SiG[i][j] += temp[i][k] * PhiT[j][k];
            }
        }
    }

    // Adicionar QT
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            SiG[i][j] += QT[i][j];
            SiG[i][j] *= Dt/2; // Multiplicar por Dt/2
        }
    }

    // Cálculo da covariância propagada PT_prop = PhiT*PT_est*PhiT^T + SiG
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            temp[i][j] = 0;
            for (int k = 0; k < 6; k++)
            {
                temp[i][j] += PhiT[i][k] * PT_est[k][j];
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            PT_prop[i][j] = 0;
            for (int k = 0; k < 6; k++)
            {
                PT_prop[i][j] += temp[i][k] * PhiT[j][k];
            }
        }
    }

    // Adicionar SiG
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            PT_prop[i][j] += SiG[i][j];
        }
    } 
}

void FK_estimador(double *x_prop, double PT_prop[6][6], double *q_obs, double R[3][3], int iteracao, double *x_est, double PT_est[6][6], double P_est[6][6])
{
    // Declaração de variáveis
    double q[4] = {q_obs[1], q_obs[2], q_obs[3], q_obs[0]};
    double q_prop[4] = {x_prop[0], x_prop[1], x_prop[2], x_prop[3]};
    double E[4][3] = {0}, S[7][6] = {0};

    // Cálculo da matriz E
    E[0][0] = q_prop[3];
    E[0][1] = -q_prop[2];
    E[0][2] = q_prop[1];
    E[1][0] = q_prop[2];
    E[1][1] = q_prop[3];
    E[1][2] = -q_prop[0];
    E[2][0] = -q_prop[1];
    E[2][1] = q_prop[0];
    E[2][2] = q_prop[3];
    E[3][0] = -q_prop[0];
    E[3][1] = -q_prop[1];
    E[3][2] = -q_prop[2];
    
    // Cálculo da matriz S (S = [E 0; 0 I])
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            S[i][j] = E[i][j];
        }
    }

    for (int i = 4; i < 7; i++)
    {
        for (int j = 3; j < 6; j++)
        {
            if ((i - 4) == (j - 3))
            {
                S[i][j] = 1;
            }
            else
            {
                S[i][j] = 0;
            }
        }
    }

    if((iteracao % 2) != 0)
    {
        for(int i = 0; i < 6; i++)
        {
            x_est[i] = x_prop[i];
            for(int j = 0; j < 6; j++)
            {
                PT_est[i][j] = PT_prop[i][j];
            }
        }

        // P_est = S*PT_prop*S^T
        double temp[7][6] = {0};
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                for (int k = 0; k < 6; k++)
                {
                    temp[i][j] += S[i][k] * PT_prop[k][j];
                }
            }
        }
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                P_est[i][j] = 0;
                for (int k = 0; k < 6; k++)
                {
                    P_est[i][j] += temp[i][k] * S[j][k];
                }
            }
        }
    }
    else
    {
        double HT[4][7], Ptt_prop[3][3], Pbt_prop[3][3], KT[6][6], K[6][6];
        // Cálculo da matriz HT = [E 0]
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (j < 3)
                {
                    HT[i][j] = E[i][j];
                }
                else
                {
                    HT[i][j] = 0;
                }
            }
        }

        // Cálculo da matriz Ptt_prop = PT_prop(1:3,1:3)
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                Ptt_prop[i][j] = PT_prop[i][j];
            }
        }

        // Cálculo da matriz Pbt_prop = PT_prop(4:6,1:3)
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                Pbt_prop[i][j] = PT_prop[i + 3][j];
            }
        }

        // Cálculo KT = [Ptt_prop; Pbt_prop] * (Ptt_prop + R)^-1 * E^T
        double Ptt_R[3][3], Ptt_R_inv[3][3], temp1[6][3] = {0}, temp2[6][6] = {0};
        // Ptt_prop + R
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                Ptt_R[i][j] = Ptt_prop[i][j] + R[i][j];
            }
        }
        // (Ptt_prop + R)^-1
        double det = Ptt_R[0][0] * (Ptt_R[1][1] * Ptt_R[2][2] - Ptt_R[1][2] * Ptt_R[2][1]) - Ptt_R[0][1] * (Ptt_R[1][0] * Ptt_R[2][2] - Ptt_R[1][2] * Ptt_R[2][0]) + Ptt_R[0][2] * (Ptt_R[1][0] * Ptt_R[2][1] - Ptt_R[1][1] * Ptt_R[2][0]);
        
        Ptt_R_inv[0][0] = (Ptt_R[1][1] * Ptt_R[2][2] - Ptt_R[1][2] * Ptt_R[2][1]) / det;
        Ptt_R_inv[0][1] = (Ptt_R[0][2] * Ptt_R[2][1] - Ptt_R[0][1] * Ptt_R[2][2]) / det;
        Ptt_R_inv[0][2] = (Ptt_R[0][1] * Ptt_R[1][2] - Ptt_R[0][2] * Ptt_R[1][1]) / det;
        Ptt_R_inv[1][0] = (Ptt_R[1][2] * Ptt_R[2][0] - Ptt_R[1][0] * Ptt_R[2][2]) / det;
        Ptt_R_inv[1][1] = (Ptt_R[0][0] * Ptt_R[2][2] - Ptt_R[0][2] * Ptt_R[2][0]) / det;
        Ptt_R_inv[1][2] = (Ptt_R[0][2] * Ptt_R[1][0] - Ptt_R[0][0] * Ptt_R[1][2]) / det;
        Ptt_R_inv[2][0] = (Ptt_R[1][0] * Ptt_R[2][1] - Ptt_R[1][1] * Ptt_R[2][0]) / det;
        Ptt_R_inv[2][1] = (Ptt_R[0][1] * Ptt_R[2][0] - Ptt_R[0][0] * Ptt_R[2][1]) / det;
        Ptt_R_inv[2][2] = (Ptt_R[0][0] * Ptt_R[1][1] - Ptt_R[0][1] * Ptt_R[1][0]) / det;

        // [Ptt_prop; Pbt_prop] * (Ptt_prop + R)^-1
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (i < 3)
                    {
                        temp1[i][j] += Ptt_prop[i][k] * Ptt_R_inv[k][j];
                    }
                    else
                    {
                        temp1[i][j] += Pbt_prop[i - 3][k] * Ptt_R_inv[k][j];
                    }
                }
            }
        }
       // Multiplicação por E^T
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    temp2[i][j] += temp1[i][k] * E[j][k];
                }
            }
        }

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                KT[i][j] = temp2[i][j];
            }
        }

        // PT_est = PT_prop - KT*HT*PT_prop
        double temp3[6][6] = {0}, temp4[6][6] = {0};
        // KT*HT
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                for (int k = 0; k < 7; k++)
                {
                    temp3[i][j] += KT[i][k] * HT[j][k];
                }
            }
        }
        // (KT*HT)*PT_prop
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                for (int k = 0; k < 6; k++)
                {
                    temp4[i][j] += temp3[i][k] * PT_prop[k][j];
                }
            }
        }
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                PT_est[i][j] = PT_prop[i][j] - temp4[i][j];
            }
        }

        // P_est = S*PT_est*S^T

        // S*PT_est
        double temp5[7][6] = {0};
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                for (int k = 0; k < 6; k++)
                {
                    temp5[i][j] += S[i][k] * PT_est[k][j];
                }
            }
        }

        // (S*PT_est)*S^T
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                P_est[i][j] = 0;
                for (int k = 0; k < 6; k++)
                {
                    P_est[i][j] += temp5[i][k] * S[j][k];
                }
            }
        }

        // Cálculo do ganho estendido K = S*KT
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                K[i][j] = 0;
                for (int k = 0; k < 6; k++)
                {
                    K[i][j] += S[i][k] * KT[k][j];
                }
            }
        }

        // Atualização do estado x_est = x_prop + K*(q_obs - q_prop)
        double norm = 0;
        for(int i = 0; i < 7; i++)
        {
            norm += q_prop[i] * q_obs[i];
        }
        if(norm < 0)
        {
            for(int i = 0; i < 4; i++)
            {
                q_obs[i] = -q_obs[i];
            }
        }

        // Estimação do estado x_est = x_prop + K*(q_obs - q_prop)

        // K*(q_obs - q_prop)
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                x_est[i] = x_prop[i];
                if (j < 4)
                {
                    x_est[i] += K[i][j] * (q_obs[j] - q_prop[j]);
                }
            }
        }

        // Normalização do quaternion
        norm = 0;
        for (int i = 0; i < 4; i++)
        {
            norm += x_est[i] * x_est[i];
        }
        norm = sqrt(norm);
        for (int i = 0; i < 4; i++)
        {
            x_est[i] /= norm;
        }        
    }
}

int main(void)
{
    return 0;
}