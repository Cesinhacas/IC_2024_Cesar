#include <math.h>
#include <stdio.h>

double GT[6][6] = {0}, QT[6][6] = {0};
#define N 3

void inverter_matriz(double matriz[3][3], double inversa[3][3]) {
    // Inicializando a matriz identidade na matriz inversa
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                inversa[i][j] = 1;
            } else {
                inversa[i][j] = 0;
            }
        }
    }

    // Aplicando o método de Gauss-Jordan
    for (int i = 0; i < N; i++)
    {
        double pivot = matriz[i][i];
        for (int j = 0; j < N; j++)
        {
            matriz[i][j] /= pivot;
            inversa[i][j] /= pivot;
        }

        for (int k = 0; k < N; k++)
        {
            if (k != i)
            {
                double fator = matriz[k][i];
                for (int j = 0; j < N; j++)
                {
                    matriz[k][j] -= fator * matriz[i][j];
                    inversa[k][j] -= fator * inversa[i][j];
                }
            }
        }
    }
}

void FK_prop(double *u_gyro, double Dt, double PT_est[6][6], double *x_est, double *x_prop, double PT_prop[6][6], int *i)
{
    double q_est[4], b_est[3], Th[3], Omega4[4][4], M[4][4] = {0}, q_prop[4], Omega3_prop[3][3], A_prop[3][3] = {0}, q_q_2t[3][3], q_sqrd_norm;
    double Omega3_est[3][3], A_est[3][3] = {0}, L[3][3], KK[3][3], PhiT[6][6], SiG[6][6] = {0};
    double cosTh, sinTh, normTh;

    // contagem de iteração
    (*i) += 1;

    // Propagação de estado
    //printf("Estado propagado:\n");
    for (int i = 0; i < 4; i++)
    {
        q_est[i] = x_est[i];
        //printf("%f ", q_est[i]);
    }
    //printf("\n");

    //printf("Th:\n");
    for (int i = 0; i < 3; i++)
    {
        b_est[i] = x_est[i + 4];
        Th[i] = u_gyro[i] * Dt;
        //printf("%f ", Th[i]);
    }
    //printf("\n");

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
    normTh = sqrt((Th[0] * Th[0]) + (Th[1] * Th[1]) + (Th[2] * Th[2]));
    cosTh = cos(normTh / 2);
    sinTh = sin(normTh / 2) / normTh;

    //printf("Matriz M:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
            {
                M[i][j] = cosTh;
            }
            else
            {
                M[i][j] = sinTh * Omega4[i][j];
            }
            /*printf("%f ", M[i][j]);
            if (j == 3)
            {
                printf("\n");
            }*/
        }
    }
    //printf("\n");


    // calculo do estado propagado
    for (int i = 0; i < 4; i++)
    {
        q_prop[i] = M[i][0] * q_est[0] + M[i][1] * q_est[1] + M[i][2] * q_est[2] + M[i][3] * q_est[3];
    }

    //printf("Vetor de estado propagado x_prop:\n");
    for (int i = 0; i < 4; i++)
    {
        x_prop[i] = q_prop[i];
        //printf("%f ", x_prop[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        x_prop[i + 4] = b_est[i];
        //printf("%f ", x_prop[i + 4]);
    }
    //printf("\n");

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

    q_sqrd_norm = q_prop[3] * q_prop[3] - (sqrt((q_prop[0] * q_prop[0]) + (q_prop[1] * q_prop[1]) + (q_prop[2] * q_prop[2]))) * (sqrt((q_prop[0] * q_prop[0]) + (q_prop[1] * q_prop[1]) + (q_prop[2] * q_prop[2])));

    //printf("Matriz A_prop:\n");
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            A_prop[i][j] = q_q_2t[i][j] + 2*q_prop[3]*Omega3_prop[i][j];
            if(i == j)
            {
                A_prop[i][j] += q_sqrd_norm;
            }
            /*printf("%f ", A_prop[i][j]);
            if (j == 2)
            {
                printf("\n");
            }*/
        }
    }
    //printf("\n");

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

    q_sqrd_norm = q_est[3] * q_est[3] - (sqrt((q_est[0] * q_est[0]) + (q_est[1] * q_est[1]) + (q_est[2] * q_est[2]))) * (sqrt((q_est[0] * q_est[0]) + (q_est[1] * q_est[1]) + (q_est[2] * q_est[2])));

    //printf("Matriz A_est:\n");
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            A_est[i][j] = q_q_2t[i][j] + 2*q_est[3]*Omega3_est[i][j];
            if(i == j)
            {
                A_est[i][j] += q_sqrd_norm;
            }
            /*printf("%f ", A_est[i][j]);
            if (j == 2)
            {
                printf("\n");
            }*/
        }
    }
    //printf("\n");

    // L = A_prop * A_est^T
    //printf("Matriz L:\n");  
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            L[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                L[i][j] += A_prop[i][k] * A_est[j][k];
            }
            /*printf("%f ", L[i][j]);
            if (j == 2)
            {
                printf("\n");
            }*/
        }
    }
    

    //printf("Matriz KK:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(i == j)
            {
                KK[i][j] = -0.25 * (L[i][j] + 1) * Dt;
            }
            else
            {
                KK[i][j] = -0.25 * L[i][j] * Dt;
            }
            /*printf("%f ", KK[i][j]);
            if (j == 2)
            {
                printf("\n");
            }*/
        }
    }

    //printf("Matriz PhiT:\n");
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
                if((i - 3) == (j - 3))
                {
                    PhiT[i][j] = 1;
                }
                else
                {
                    PhiT[i][j] = 0;
                }
            }
            /*printf("%f ", PhiT[i][j]);
            if(j == 5)
            {
                printf("\n");
            }*/
        }
    }
    //printf("\n");

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
    //printf("Matriz SiG:\n");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
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
            /*double sig_value = SiG[i][j]*10000;
            printf("%f ", sig_value);
            if (j == 5)
            {
                printf("\n");
            }*/
        }
    }
    //printf("\n");

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
    //printf("Matriz PT_prop:\n");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            PT_prop[i][j] += SiG[i][j];
            /*printf("%f ", PT_prop[i][j]);
            if (j == 5)
            {
                printf("\n");
            }*/
        }
    }
    //printf("\n");
}

void FK_estimador(double *x_prop, double PT_prop[6][6], double *q_obs, double R[3][3], int iteracao, double *x_est, double PT_est[6][6], double P_est[7][7])
{
    // Declaração de variáveis
    double q_prop[4] = {x_prop[0], x_prop[1], x_prop[2], x_prop[3]}, q[4] = {q_obs[1], q_obs[2], q_obs[3], q_obs[0]};
    double E[4][3] = {0}, S[7][6] = {0};

    printf("q_prop:\n");
    for(int i = 0; i < 4; i++)
    {
        printf("%f ", q_prop[i]);
    }
    printf("\n");

    printf("q_obs:\n");
    for(int i = 0; i < 4; i++)
    {
        printf("%f ", q_obs[i]);
    }
    printf("\n");

    printf("R:\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("%f ", R[i][j]);
            if(j == 2)
            {
                printf("\n");
            }
        }
    }
    printf("\n");

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

    printf("Matriz S:\n");
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("%f ", S[i][j]);
            if (j == 5)
            {
                printf("\n");
            }
        }
    }
    printf("\n");

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
            for (int j = 0; j < 7; j++)
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
        double HT[4][6], Ptt_prop[3][3], Pbt_prop[3][3], KT[6][4], K[6][4];
        // Cálculo da matriz HT = [E 0]
        //printf("Matriz HT:\n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (j < 3)
                {
                    HT[i][j] = E[i][j];
                }
                else
                {
                    HT[i][j] = 0;
                }
                /*printf("%f ", HT[i][j]);
                if (j == 5)
                {
                    printf("\n");
                }*/
            }
        }

        // Cálculo da matriz Ptt_prop = PT_prop(1:3,1:3)
        // Cálculo da matriz Pbt_prop = PT_prop(4:6,1:3)
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                Ptt_prop[i][j] = PT_prop[i][j];
                Pbt_prop[i][j] = PT_prop[i + 3][j];
            }
        }

        // Cálculo KT = [Ptt_prop; Pbt_prop] * (Ptt_prop + R)^-1 * E^T
        double Ptt_R[3][3], Ptt_R_inv[3][3], temp1[6][3] = {0}, temp2[6][4] = {0};
        // Ptt_prop + R
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                Ptt_R[i][j] = Ptt_prop[i][j] + R[i][j];
            }
        }
        // (Ptt_prop + R)^-1
        inverter_matriz(Ptt_R, Ptt_R_inv);

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
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    temp2[i][j] += temp1[i][k] * E[j][k];
                }
                KT[i][j] = temp2[i][j];
            }
        }

        // PT_est = PT_prop - KT*HT*PT_prop
        double temp3[6][6] = {0}, temp_KH[6][6] = {0};
        // KT*HT
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    temp_KH[i][j] += KT[i][k] * HT[k][j];
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
                    temp3[i][j] += temp_KH[i][k] * PT_prop[k][j];
                }
            }
        }
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                PT_est[i][j] = PT_prop[i][j] - temp3[i][j];
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
            for (int j = 0; j < 7; j++)
            {
                P_est[i][j] = 0;
                for (int k = 0; k < 6; k++)
                {
                    P_est[i][j] += temp5[i][k] * S[j][k];
                }
            }
        }

        // Cálculo do ganho estendido K = S*KT
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 4; j++)
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
        for(int i = 0; i < 4; i++)
        {
            norm += q_prop[i] * q[i];
        }
        if(norm < 0)
        {
            for(int i = 0; i < 4; i++)
            {
                q[i] = -q[i];
            }
        }

        // Estimação do estado x_est = x_prop + K*(q_obs - q_prop)

        // K*(q_obs - q_prop)
        for (int i = 0; i < 6; i++)
        {
            x_est[i] = x_prop[i];
            for (int j = 0; j < 4; j++)
            {
                x_est[i] += K[i][j] * (q[j] - q_prop[j]);
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

int main()
{
    double Q[6][6] = {0}, GT_T[6][6] = {0}, temp[6][6] = {0};
    double val1 = 0.005 * 0.005; // 0.000025
    double val2 = 0.1 * 0.1;     // 0.01

    Q[0][0] = val1;
    Q[1][1] = val1;
    Q[2][2] = val1;
    Q[3][3] = val2;
    Q[4][4] = val2;
    Q[5][5] = val2;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            // Bloco superior esquerdo: -0.5 * eye(3)
            if (i < 3 && j < 3) {
                GT[i][j] = (i == j) ? -0.5 : 0.0;
            }
            // Bloco inferior direito: eye(3)
            else if (i >= 3 && j >= 3) {
                GT[i][j] = (i == j) ? 1.0 : 0.0;
            }
            // Blocos de zeros
            else {
                GT[i][j] = 0.0;
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            GT_T[i][j] = GT[j][i];
        }
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            temp[i][j] = 0.0;
            for (int k = 0; k < 6; k++) {
                temp[i][j] += GT[i][k] * Q[k][j];
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            QT[i][j] = 0.0;
            for (int k = 0; k < 6; k++) {
                QT[i][j] += temp[i][k] * GT_T[k][j];
            }
        }
    }
    return 0;
}