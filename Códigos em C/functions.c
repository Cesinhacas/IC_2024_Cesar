#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 9
#define tam 1045

void inverter_matriz(float matriz[N][N], float inversa[N][N]) {
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

void NLLS(float *mx, float *my, float *mz)
{
    int passo = 0, loop = 1;
    float p0[9] = {1, 1, 1, 0, 0, 0, 0, 0, 0}, Be[tam], e[tam], f[tam], sx, sy, sz, bx, by, bz, rho, phi, lambida, error_ant, J, delta_J, mat_H[N][tam];

    for (int i=0; i < tam; i++)
    {
        Be[i] = 1;
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
        
        for(int i=0; i < tam; i++)
        {
            f[i] = pow((mx[i]-bx), 2)/pow(sx, 2) + pow((sx*(my[i]-by) - sy*sin(rho)*(mx[i]-bx)), 2)/pow((sx*sy*cos(rho)), 2) + pow((sx*sy*cos(rho)*(mz[i]-bz) - sx*sz*sin(lambida)*(my[i]-by) + sy*sz*(sin(lambida)*sin(rho) - cos(rho)*sin(phi)*cos(lambida))*(mx[i]-bx)), 2)/pow((sx*sy*sz*cos(rho)*cos(phi)*cos(lambida)), 2);

            e[i] = pow(Be[i], 2) - f[i];

            mat_H[0][i] = (2*(sx*(by - my[i]) - sy*sin(rho)*(bx - mx[i]))*(by - my[i]))/(sx*sx*sy*sy*cos(rho)*cos(rho)) - (2*pow((sx*(by - my[i]) - sy*sin(rho)*(bx - mx[i])), 2))/(pow(sx, 3)*sy*sy*cos(rho)*cos(rho)) - (2*pow((bx - mx[i]), 2))/pow(sx, 3) - (2*pow((sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(bx - mx[i]) + sx*sy*cos(rho)*(bz - mz[i]) - sx*sz*sin(lambida)*(by - my[i])), 2))/(pow(sx, 3)*sy*sy*sz*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*cos(rho)*cos(rho)) + (2*(sy*cos(rho)*(bz - mz[i]) - sz*sin(lambida)*(by - my[i]))*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(bx - mx[i]) + sx*sy*cos(rho)*(bz - mz[i]) - sx*sz*sin(lambida)*(by - my[i])))/(sx*sx*sy*sy*sz*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*cos(rho)*cos(rho));

            mat_H[1][i] = -(2*(by - my[i])*(by*sx*sz*sin(lambida)*sin(lambida) - my[i]*sx*sz*sin(lambida)*sin(lambida) + by*sx*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi) - my[i]*sx*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi) - bz*sx*sy*cos(rho)*sin(lambida) + mz[i]*sx*sy*cos(rho)*sin(lambida) - bx*sy*sz*sin(lambida)*sin(lambida)*sin(rho) + mx[i]*sy*sz*sin(lambida)*sin(lambida)*sin(rho) - bx*sy*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*sin(rho) + mx[i]*sy*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*sin(rho) + bx*sy*sz*cos(lambida)*cos(rho)*sin(lambida)*sin(phi) - mx[i]*sy*sz*cos(lambida)*cos(rho)*sin(lambida)*sin(phi)))/(sx*pow(sy, 3)*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*cos(rho)*cos(rho));

            mat_H[2][i] = -(2*(bz - mz[i])*(bz*sx*sy*cos(rho) - by*sx*sz*sin(lambida) - mz[i]*sx*sy*cos(rho) + my[i]*sx*sz*sin(lambida) + bx*sy*sz*sin(lambida)*sin(rho) - mx[i]*sy*sz*sin(lambida)*sin(rho) - bx*sy*sz*cos(lambida)*cos(rho)*sin(phi) + mx[i]*sy*sz*cos(lambida)*cos(rho)*sin(phi)))/(sx*sy*pow(sz, 3)*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*cos(rho));

            mat_H[3][i] = (2*bx - 2*mx[i])/sx*sx - (2*sin(rho)*(sx*(by - my[i]) - sy*sin(rho)*(bx - mx[i])))/(sx*sx*sy*cos(rho)*cos(rho)) + (2*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(bx - mx[i]) + sx*sy*cos(rho)*(bz - mz[i]) - sx*sz*sin(lambida)*(by - my[i])))/(sx*sx*sy*sz*cos(lambida)*cos(lambida)*2*cos(phi)*cos(phi)*cos(rho)*cos(rho));

            mat_H[4][i] = (2*(sx*(by - my[i]) - sy*sin(rho)*(bx - mx[i])))/(sx*sy*sy*cos(rho)*cos(rho)) - (2*sin(lambida)*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(bx - mx[i]) + sx*sy*cos(rho)*(bz - mz[i]) - sx*sz*sin(lambida)*(by - my[i])))/(sx*sy*sy*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*cos(rho)*cos(rho));

            mat_H[5][i] = (2*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(bx - mx[i]) + sx*sy*cos(rho)*(bz - mz[i]) - sx*sz*sin(lambida)*(by - my[i])))/(sx*sy*sz*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*cos(rho));

            mat_H[6][i] = -(2*(bx*sy - mx[i]*sy - by*sx*sin(rho) + my[i]*sx*sin(rho))*(by*sx*sz*sin(lambida)*sin(lambida) - my[i]*sx*sz*sin(lambida)*sin(lambida) + by*sx*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi) - my[i]*sx*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi) - bz*sx*sy*cos(rho)*sin(lambida) + mz[i]*sx*sy*cos(rho)*sin(lambida) - bx*sy*sz*sin(lambida)*sin(lambida)*sin(rho) + mx[i]*sy*sz*sin(lambida)*sin(lambida)*sin(rho) - bx*sy*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*sin(rho) + mx[i]*sy*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*sin(rho) + bx*sy*sz*cos(lambida)*cos(rho)*sin(lambida)*sin(phi) - mx[i]*sy*sz*cos(lambida)*cos(rho)*sin(lambida)*sin(phi)))/(sx*sx*sy*sy*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*pow(cos(rho), 3));

            mat_H[7][i] = (2*sin(phi)*pow((sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(bx - mx[i]) + sx*sy*cos(rho)*(bz - mz[i]) - sx*sz*sin(lambida)*(by - my[i])), 2))/(sx*sx*sy*sy*sz*sz*cos(lambida)*cos(lambida)*pow(cos(phi), 3)*cos(rho)*cos(rho)) - (2*(bx - mx[i])*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(bx - mx[i]) + sx*sy*cos(rho)*(bz - mz[i]) - sx*sz*sin(lambida)*(by - my[i])))/(sx*sx*sy*sz*cos(lambida)*cos(phi)*cos(rho));

            mat_H[8][i] = (2*sin(lambida)*pow((sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(bx - mx[i]) + sx*sy*cos(rho)*(bz - mz[i]) - sx*sz*sin(lambida)*(by - my[i])), 2))/(sx*sx*sy*sy*sz*sz*pow(cos(lambida), 3)*cos(phi)*cos(phi)*pow(cos(rho), 2)) + (2*(sy*sz*(cos(lambida)*sin(rho) + cos(rho)*sin(lambida)*sin(phi))*(bx - mx[i]) - sx*sz*cos(lambida)*(by - my[i]))*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(bx - mx[i]) + sx*sy*cos(rho)*(bz - mz[i]) - sx*sz*sin(lambida)*(by - my[i])))/(sx*sx*sy*sy*sz*sz*cos(lambida)*cos(lambida)*cos(phi)*cos(phi)*cos(rho)*cos(rho));
        }
        
        J = 0;

        for(int i=0; i < tam; i++)
        {
            J += pow(e[i], 2)/2;
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
        
        float Ht_H[N][N], Ht_e[N], inv[N][N], mul_mat[N][tam];

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
}

void ETS(float *mx, float *my, float *mz)
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
    lambida = -atan((X[3] / X[4]) * sqrt(-(pow(X[4], 2)*(X[4]*pow(X[1], 2) - X[1]*X[2]*X[3] + pow(X[2], 2) - 4*X[0]*X[4]) / (2*pow(X[1], 2)*pow(X[3], 2)*X[4] - 4*pow(X[1], 2)*pow(X[4], 2) - 4*pow(X[1], 2)*pow(X[4], 2) - X[1]*X[2]*pow(X[3], 3) + X[0]*pow(X[3], 4) - 8*X[0]*pow(X[3], 2)*X[4] + 16*X[0]*pow(X[4], 2)))));

    n1 = -pow(X[1], 2)*pow(X[7], 2) + 4*pow(X[1], 2)*X[4]*X[8] - 4*X[1]*X[2]*X[3]*X[8] + 2*X[1]*X[2]*X[6]*X[7] + 2*X[1]*X[3]*X[5]*X[7] - 4*X[1]*X[4]*X[5]*X[6] - pow(X[2], 2)*pow(X[6], 2) + 2*X[2]*X[3]*X[5]*X[6] + 4*pow(X[2], 2)*X[8] - 4*X[2]*X[5]*X[7] - pow(X[3], 2)*pow(X[5], 2) + 4*X[1]*pow(X[3], 2)*X[8] - 4*X[0]*X[3]*X[6]*X[7] + 4*X[4]*pow(X[5], 2) + 4*X[0]*X[4]*pow(X[6],2) + 4*X[0]*pow(X[7], 2) - 16*X[0]*X[4]*X[8];
    n2 = pow(X[1], 2)*X[4] - X[1]*X[2]*X[3] + pow(X[2], 2) + X[0]*pow(X[3], 2) - 4*X[0]*X[4];
    n3 = 2*pow(X[1], 2)*pow(X[3], 2)*X[4] - 4*pow(X[1], 2)*pow(X[4], 2) - X[1]*X[2]*pow(X[3], 3) + pow(X[2], 2)*pow(X[3], 2) + X[0]*pow(X[3], 2) - 8*X[0]*pow(X[3], 2)*X[4] + 16*X[0]*pow(X[4], 2);
    n4 = 4*X[4] - pow(X[3], 2);
    n5 = 4*X[0]*X[4] - pow(X[2], 2);
    n6 = 4*X[0] - pow(X[1], 2);

    phi = -atan((fabs(X[4])*sqrt(n1*n5) * (2*X[2] - X[1]*X[3]) * sqrt((X[4]*n4*n6) / n3)) / (pow(X[4], 2) * sqrt(-n2 / X[4]) * sqrt(n1*n6) * sqrt(-(n2 * n4) / n3) * sqrt(-(n4*n5) / (X[4]*n2))));
}

int main()
{
    return 0;
}