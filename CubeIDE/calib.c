#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calib.h"


void inverter_matriz(float matriz[N][N], float inversa[N][N])
{
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
        float pivot = matriz[i][i];
        for (int j = 0; j < N; j++)
        {
            matriz[i][j] /= pivot;
            inversa[i][j] /= pivot;
        }

        for (int k = 0; k < N; k++)
        {
            if (k != i)
            {
                float fator = matriz[k][i];
                for (int j = 0; j < N; j++)
                {
                    matriz[k][j] -= fator * matriz[i][j];
                    inversa[k][j] -= fator * inversa[i][j];
                }
            }
        }
    }
}


int NLLS(float *mx, float *my, float *mz, float *p)
{
    int passo = 0, loop = 1;
    float p0[9] = {2^14, 2^14, 2^14, 0, 0, 0, 0, 0, 0}, Be[tam], e[tam], f[tam], sx, sy, sz, bx, by, bz, rho, phi, lambida, error_ant, J, delta_J, mat_H[N][tam];
    float sin_phi, sin_rho, sin_lambda, cos_phi, cos_rho, cos_lambda;
    float Ht_H[N][N], Ht_e[N], inv[N][N], mul_mat[N][tam];

    for (int i=0; i < tam; i++)
    {
        Be[i] = 2^14;
    }

    while(loop == 1)
    {
        sx = p0[0];
        sy = p0[1];
        sz = p0[2];
        bx = p0[3];
        by = p0[4];
        bz = p0[5];
        rho = p0[6];
        phi = p0[7];
        lambida = p0[8];

        sin_phi = sinf(phi);
        sin_rho = sinf(rho);
        sin_lambda = sinf(lambida);
        cos_phi = cosf(phi);
        cos_rho = cosf(rho);
        cos_lambda = cosf(lambida);

        for(int i=0; i < tam; i++)
        {
            f[i] = ((mx[i]-bx)*(mx[i]-bx))/(sx*sx) + ((sx*(my[i]-by) - sy*sin_rho*(mx[i]-bx))*((sx*(my[i]-by) - sy*sin_rho*(mx[i]-bx))))/((sx*sy*cos_rho)*(sx*sy*cos_rho)) + ((sx*sy*cos_rho*(mz[i]-bz) - sx*sz*sin_lambda*(my[i]-by) + sy*sz*(sin_lambda*sin_rho - cos_rho*sin_phi*cos_lambda)*(mx[i]-bx))*(sx*sy*cos_rho*(mz[i]-bz) - sx*sz*sin_lambda*(my[i]-by) + sy*sz*(sin_lambda*sin_rho - cos_rho*sin_phi*cos_lambda)*(mx[i]-bx)))/((sx*sy*sz*cos_rho*cos_phi*cos_lambda)*(sx*sy*sz*cos_rho*cos_phi*cos_lambda));

            e[i] = (Be[i] * Be[i]) - f[i];

            mat_H[0][i] = (2*(sx*(by - my[i]) - sy*sin_rho*(bx - mx[i]))*(by - my[i]))/(sx*sx*sy*sy*cos_rho*cos_rho) - (2*((sx*(by - my[i]) - sy*sin_rho*(bx - mx[i]))*(sx*(by - my[i]) - sy*sin_rho*(bx - mx[i]))))/((sx*sx*sx)*sy*sy*cos_rho*cos_rho) - (2*((bx - mx[i])*(bx - mx[i])))/(sx*sx*sx) - (2*((sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i])) * (sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i]))))/((sx*sx*sx)*sy*sy*sz*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*cos_rho*cos_rho) + (2*(sy*cos_rho*(bz - mz[i]) - sz*sin_lambda*(by - my[i]))*(sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i])))/(sx*sx*sy*sy*sz*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*cos_rho*cos_rho);

            mat_H[1][i] = -(2*(by - my[i])*(by*sx*sz*sin_lambda*sin_lambda - my[i]*sx*sz*sin_lambda*sin_lambda + by*sx*sz*cos_lambda*cos_lambda*cos_phi*cos_phi - my[i]*sx*sz*cos_lambda*cos_lambda*cos_phi*cos_phi - bz*sx*sy*cos_rho*sin_lambda + mz[i]*sx*sy*cos_rho*sin_lambda - bx*sy*sz*sin_lambda*sin_lambda*sin_rho + mx[i]*sy*sz*sin_lambda*sin_lambda*sin_rho - bx*sy*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*sin_rho + mx[i]*sy*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*sin_rho + bx*sy*sz*cos_lambda*cos_rho*sin_lambda*sin_phi - mx[i]*sy*sz*cos_lambda*cos_rho*sin_lambda*sin_phi))/(sx*(sy*sy*sy)*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*cos_rho*cos_rho);

            mat_H[2][i] = -(2*(bz - mz[i])*(bz*sx*sy*cos_rho - by*sx*sz*sin_lambda - mz[i]*sx*sy*cos_rho + my[i]*sx*sz*sin_lambda + bx*sy*sz*sin_lambda*sin_rho - mx[i]*sy*sz*sin_lambda*sin_rho - bx*sy*sz*cos_lambda*cos_rho*sin_phi + mx[i]*sy*sz*cos_lambda*cos_rho*sin_phi))/(sx*sy*(sz*sz*sz)*cos_lambda*cos_lambda*cos_phi*cos_phi*cos_rho);

            mat_H[3][i] = (2*bx - 2*mx[i])/sx*sx - (2*sin_rho*(sx*(by - my[i]) - sy*sin_rho*(bx - mx[i])))/(sx*sx*sy*cos_rho*cos_rho) + (2*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i])))/(sx*sx*sy*sz*cos_lambda*cos_lambda*2*cos_phi*cos_phi*cos_rho*cos_rho);

            mat_H[4][i] = (2*(sx*(by - my[i]) - sy*sin_rho*(bx - mx[i])))/(sx*sy*sy*cos_rho*cos_rho) - (2*sin_lambda*(sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i])))/(sx*sy*sy*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*cos_rho*cos_rho);

            mat_H[5][i] = (2*(sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i])))/(sx*sy*sz*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*cos_rho);

            mat_H[6][i] = -(2*(bx*sy - mx[i]*sy - by*sx*sin_rho + my[i]*sx*sin_rho)*(by*sx*sz*sin_lambda*sin_lambda - my[i]*sx*sz*sin_lambda*sin_lambda + by*sx*sz*cos_lambda*cos_lambda*cos_phi*cos_phi - my[i]*sx*sz*cos_lambda*cos_lambda*cos_phi*cos_phi - bz*sx*sy*cos_rho*sin_lambda + mz[i]*sx*sy*cos_rho*sin_lambda - bx*sy*sz*sin_lambda*sin_lambda*sin_rho + mx[i]*sy*sz*sin_lambda*sin_lambda*sin_rho - bx*sy*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*sin_rho + mx[i]*sy*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*sin_rho + bx*sy*sz*cos_lambda*cos_rho*sin_lambda*sin_phi - mx[i]*sy*sz*cos_lambda*cos_rho*sin_lambda*sin_phi))/(sx*sx*sy*sy*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*(cos_rho*cos_rho*cos_rho));

            mat_H[7][i] = (2*sin_phi*((sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i]))*(sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i]))))/(sx*sx*sy*sy*sz*sz*cos_lambda*cos_lambda*(cos_phi*cos_phi*cos_phi)*cos_rho*cos_rho) - (2*(bx - mx[i])*(sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i])))/(sx*sx*sy*sz*cos_lambda*cos_phi*cos_rho);

            mat_H[8][i] = (2*sin_lambda*((sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i]))*(sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i]))))/(sx*sx*sy*sy*sz*sz*(cos_lambda*cos_lambda*cos_lambda)*cos_phi*cos_phi*(cos_rho*cos_rho)) + (2*(sy*sz*(cos_lambda*sin_rho + cos_rho*sin_lambda*sin_phi)*(bx - mx[i]) - sx*sz*cos_lambda*(by - my[i]))*(sy*sz*(sin_lambda*sin_rho - cos_lambda*cos_rho*sin_phi)*(bx - mx[i]) + sx*sy*cos_rho*(bz - mz[i]) - sx*sz*sin_lambda*(by - my[i])))/(sx*sx*sy*sy*sz*sz*cos_lambda*cos_lambda*cos_phi*cos_phi*cos_rho*cos_rho);
        }

        J = 0;

        for(int i=0; i < tam; i++)
        {
            J += (e[i] * e[i])/2;
        }

        if(passo < 2)
        {
            error_ant = J;
        }
        else
        {
            delta_J = 100*fabs(J-error_ant)/J;
            if(delta_J < 0.05)
            {
                loop = 0;
            }
            error_ant = J;
        }

        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                Ht_H[i][j] = 0;
                for(int k = 0; k < tam; k++)
                {
                    Ht_H[i][j] += mat_H[i][k]*mat_H[j][k];
                }
            }
        }

        inverter_matriz(Ht_H, inv);

        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < tam; j++)
            {
                mul_mat[i][j] = 0;
                for(int k = 0; k < N; k++)
                {
                    mul_mat[i][j] += inv[i][k]*mat_H[k][j];
                }
            }
        }

        for(int i = 0; i < N; i++)
        {
            Ht_e[i] = 0;
            for(int j = 0; j < tam; j++)
            {
                Ht_e[i] += mul_mat[i][j]*e[j];
            }
        }

        for(int i = 0; i < N; i++)
        {
            p0[i] += Ht_e[i];
        }

        passo++;
    }
    p[0] = sx;
    p[1] = sy;
    p[2] = sz;
    p[3] = bx;
    p[4] = by;
    p[5] = bz;
    p[6] = rho;
    p[7] = phi;
    p[8] = lambida;

    return passo;
}

void ETS(float *mx, float *my, float *mz, float *p)
{
    //Cria a matriz H
    float mat_H[N][tam], my_2[tam];
    for(int i=0; i < tam; i++)
    {
        mat_H[0][i] = mx[i]*mx[i];
        mat_H[1][i] = mx[i]*my[i];
        mat_H[2][i] = mx[i]*mz[i];
        mat_H[3][i] = my[i]*mz[i];
        mat_H[4][i] = mz[i]*mz[i];
        mat_H[5][i] = mx[i];
        mat_H[6][i] = my[i];
        mat_H[7][i] = mz[i];
        mat_H[8][i] = 1;
        my_2[i] = -(my[i]*my[i]);
    }

    //Multiplicação da matriz H por sua transposta
    float H_Ht[N][N], inv[N][N];
    for(int i=0; i < N; i++)
    {
        for(int j=0; j < N; j++)
        {
            H_Ht[i][j] = 0;
            for(int k = 0; k < tam; k++)
            {
                H_Ht[i][j] += mat_H[i][k]*mat_H[j][k];
            }
        }
    }

    inverter_matriz(H_Ht, inv);

    //Multiplica a inversa por H transposta
    float mul_mat[N][tam];
    for(int i=0; i < N; i++)
    {
        for(int j=0; j < tam; j++)
        {
            mul_mat[i][j] = 0;
            for(int k=0; k < N; k++)
            {
                mul_mat[i][j] += inv[i][k]*mat_H[k][j];
            }
        }
    }

    //Resultado da psedo-inversa
    float X[N];
    for(int i=0; i < N; i++)
    {
        X[i] = 0;
        for(int j=0; j < tam; j++)
        {
            X[i] += mul_mat[i][j]*my_2[j];
        }
    }


    // Segundo passo, encontrando os parâmetros
    float psi7, psi8, divs, n1, n2, n3, n4, n5, n6, bx, by, bz, sx, sy, sz, rho, phi, lambida;

    psi7 = 2*(X[4]*pow(X[1], 2) - X[1]*X[2]*X[3] + pow(X[2], 2) + X[0]*pow(X[3], 2) - 4*X[0]*X[4]);
    bx = -(pow(X[3], 2) * X[5] + 2*X[2]*X[7] - 4*X[4]*X[5] - X[1]*X[3]*X[7] + 2*X[1]*X[4]*X[6] - X[2]*X[3]*X[6]) / psi7;
    by = -(pow(X[2], 2) * X[6] + 2*X[0]*X[3]*X[7] - 4*X[0]*X[4]*X[6] - X[1]*X[2]*X[7] + 2*X[1]*X[4]*X[5] - X[2]*X[3]*X[5]) / psi7;
    bz = -(pow(X[1], 2)*X[7] - 4*X[0]*X[7] + 2*X[2]*X[5] + 2*X[0]*X[3]*X[6] - X[1]*X[2]*X[6] - X[1]*X[3]*X[5]) / psi7;

    psi8 = -pow(X[1],2)*pow(X[7],2) + 4*X[4]*X[8]*pow(X[1],2) - 4*X[8]*X[1]*X[2]*X[3] + 2*X[1]*X[2]*X[6]*X[7] + 2*X[1]*X[3]*X[5]*X[7] - 4*X[4]*X[1]*X[5]*X[6] - pow(X[2], 2)*pow(X[6], 2) + 4*X[8]*pow(X[2], 2) + 2*X[2]*X[3]*X[5]*X[6] - 4*X[2]*X[5]*X[7] - pow(X[3], 2)*pow(X[5], 2) + 4*X[0]*X[8]*pow(X[3], 2) + 4*X[4]*pow(X[5], 2) + 4*X[0]*X[4]*pow(X[6], 2) + 4*X[0]*pow(X[7], 2) - 16*X[0]*X[4]*X[8] - 4*X[0]*X[3]*X[6]*X[7];

    divs =  2 * pow(fabs(X[4]), 3) * (X[4] * pow(X[1], 2) - X[1] * X[2] * X[3] + pow(X[2], 2) + X[0] * pow(X[3], 2) - 4 * X[0] * X[4]);

    sx = -pow(X[4], 3) * sqrt(psi8 * (-pow(X[3], 2) + 4*X[4])) / (divs);
    sy = -pow(X[4], 3) * sqrt(psi8 * (-pow(X[2], 2) + 4*X[0]*X[4])) / (divs);
    sz = -pow(X[4], 3) * sqrt(psi8 * (-pow(X[1], 2) + 4*X[0])) / (divs);

    rho = (2 * X[1]*X[4] - X[2]*X[3]) / (2*pow(X[4], 2) * sqrt(-(X[4]*pow(X[1], 2) - X[1]*X[2]*X[3] + pow(X[2], 2) + X[0]*pow(X[3], 2) - 4*X[0]*X[4]) / (pow(X[4], 3))));
    rho = -atan(rho);
    lambida = -atan((X[3] / X[4]) * sqrt(-(pow(X[4], 2)*(X[4]*pow(X[1], 2) - X[1]*X[2]*X[3] + pow(X[2], 2) - 4*X[0]*X[4]) / (2*pow(X[1], 2)*pow(X[3], 2)*X[4] - 4*pow(X[1], 2)*pow(X[4], 2) - 4*pow(X[1], 2)*pow(X[4], 2) - X[1]*X[2]*pow(X[3], 3) + pow(X[2],2)*pow(X[3],2) + X[0]*pow(X[3], 4) - 8*X[0]*pow(X[3], 2)*X[4] + 16*X[0]*pow(X[4], 2)))));

    n1 = -pow(X[1], 2)*pow(X[7], 2) + 4*pow(X[1], 2)*X[4]*X[8] - 4*X[1]*X[2]*X[3]*X[8] + 2*X[1]*X[2]*X[6]*X[7] + 2*X[1]*X[3]*X[5]*X[7] - 4*X[1]*X[4]*X[5]*X[6] - pow(X[2], 2)*pow(X[6], 2) + 2*X[2]*X[3]*X[5]*X[6] + 4*pow(X[2], 2)*X[8] - 4*X[2]*X[5]*X[7] - pow(X[3], 2)*pow(X[5], 2) + 4*X[1]*pow(X[3], 2)*X[8] - 4*X[0]*X[3]*X[6]*X[7] + 4*X[4]*pow(X[5], 2) + 4*X[0]*X[4]*pow(X[6],2) + 4*X[0]*pow(X[7], 2) - 16*X[0]*X[4]*X[8];
    n2 = pow(X[1], 2)*X[4] - X[1]*X[2]*X[3] + pow(X[2], 2) + X[0]*pow(X[3], 2) - 4*X[0]*X[4];
    n3 = 2*pow(X[1], 2)*pow(X[3], 2)*X[4] - 4*pow(X[1], 2)*pow(X[4], 2) - X[1]*X[2]*pow(X[3], 3) + pow(X[2], 2)*pow(X[3], 2) + X[0]*pow(X[3], 2) - 8*X[0]*pow(X[3], 2)*X[4] + 16*X[0]*pow(X[4], 2);
    n4 = 4*X[4] - pow(X[3], 2);
    n5 = 4*X[0]*X[4] - pow(X[2], 2);
    n6 = 4*X[0] - pow(X[1], 2);

    phi = -atan((fabs(X[4])*sqrt(n1*n5) * (2*X[2] - X[1]*X[3]) * sqrt((X[4]*n4*n6) / n3)) / (pow(X[4], 2) * sqrt(-n2 / X[4]) * sqrt(n1*n6) * sqrt(-(n2 * n4) / n3) * sqrt(-(n4*n5) / (X[4]*n2))));

    p[0] = sx;
    p[1] = sy;
    p[2] = sz;
    p[3] = bx;
    p[4] = by;
    p[5] = bz;
    p[6] = rho;
    p[7] = phi;
    p[8] = lambida;
}
