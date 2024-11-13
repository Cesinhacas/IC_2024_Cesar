#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 9
#define N1 3
#define tam 1045

typedef struct {
    float r1;
    float r2;
    float r3;
    } raizes_t;

void inverter_matriz9x9(float matriz[N][N], float inversa[N][N]) {
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

void inverter_matriz3x3(float matriz[N1][N1], float inversa[N1][N1]) {
    float fator = 0, pivot = 0;
    // Inicializando a matriz identidade na matriz inversa
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N1; j++) {
            if (i == j) {
                inversa[i][j] = 1;
            } else {
                inversa[i][j] = 0;
            }
        }
    }

    // Aplicando o método de Gauss-Jordan
    for (int i = 0; i < N1; i++)
    {
        pivot = matriz[i][i];
        for (int j = 0; j < N1; j++)
        {
            matriz[i][j] /= pivot;
            inversa[i][j] /= pivot;
        }

        for (int k = 0; k < N1; k++)
        {
            if (k != i)
            {
                fator = matriz[k][i];
                for (int j = 0; j < N1; j++)
                {
                    matriz[k][j] -= fator * matriz[i][j];
                    inversa[k][j] -= fator * inversa[i][j];
                }
            }
        }
    }
}

void resolver_cubica(float a, float b, float c, float d, raizes_t *raizes)
{
    // Passo 1: Reduzindo para a forma t^3 + pt + q = 0
    float p = (3 * a * c - b * b) / (3 * a * a);
    float q = (2 * b * b * b - 9 * a * b * c + 27 * a * a * d) / (27 * a * a * a);

    // Passo 2: Calculando o discriminante
    float delta = pow(q / 2, 2) + pow(p / 3, 3);

    // Passo 3: Encontrar as raízes com base no valor de delta
    if (delta == 0) {
        // Três raízes reais (pelo menos duas iguais)
        float u = cbrt(-q / 2);
        raizes->r1 = 2 * u - b / (3 * a);
        raizes->r2 = -u - b / (3 * a);
        raizes->r3 = raizes->r2;
    } else {
        // Três raízes reais diferentes
        float r = sqrt(-p / 3);
        float theta = acos(-q / (2 * pow(r, 3)));
        raizes->r3 = 2 * r * cos(theta / 3) - b / (3 * a);
        raizes->r1 = 2 * r * cos((theta + 2 * 3.14159265358979323846) / 3) - b / (3 * a);
        raizes->r2 = 2 * r * cos((theta + 4 * 3.14159265358979323846) / 3) - b / (3 * a);
    }
}

void autovetor(float A[N1][N1], float lambda, float x[N1])
{
    float A_lambda[3][3], v[3] = {1, 1, 1}, A_lambda_inv[3][3], norma = 0;
    for(int i=0; i < 3; i++)
    {
        for(int j=0; j < 3; j++)
        {
            if(i == j)
            {
                A_lambda[i][j] = A[i][j] - lambda;
            }
            else
            {
                A_lambda[i][j] = A[i][j];
            }
        }
    }
    inverter_matriz3x3(A_lambda, A_lambda_inv);
    for(int i=0; i < 3; i++)
    {
        x[i] = 0;
        for(int j=0; j < 3; j++)
        {
            x[i] += A_lambda_inv[i][j]*v[j];
        }
    }

    for(int i=0; i < 3; i++)
    {
        norma += x[i]*x[i];
    }
    norma = sqrt(norma);
    for(int i=0; i < 3; i++)
    {
        x[i] /= norma;
    }
}

void SVD_dec(float A[N1][N1], float U[N1][N1], float S[N1][N1])
{
    float a, b, c, d;
    raizes_t raizes;
    float AU1[3], AU2[3], AU3[3]; 

    a = -1;
    b = A[0][0] + A[1][1] + A[2][2];
    c = -A[0][0]*A[1][1] - A[0][0]*A[2][2] - A[1][1]*A[2][2] + A[0][1]*A[1][0] + A[0][2]*A[2][0] + A[0][2]*A[2][0];
    d = A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][1]*A[1][0]*A[2][1] - A[0][1]*A[1][0]*A[2][2] - A[1][2]*A[2][1]*A[0][0] - A[0][2]*A[2][0]*A[1][1];

    resolver_cubica(a, b, c, d, &raizes);
    S[0][0] = raizes.r1;
    S[0][1] = 0;
    S[0][2] = 0;
    S[1][1] = raizes.r2;
    S[1][0] = 0;
    S[1][2] = 0;
    S[2][2] = raizes.r3;
    S[2][0] = 0;
    S[2][1] = 0;

    autovetor(A, raizes.r1, AU1);
    autovetor(A, raizes.r2, AU2);
    autovetor(A, raizes.r3, AU3);
    

    U[0][0] = AU1[0];
    U[0][1] = AU1[1];
    U[0][2] = AU1[2];
    U[1][0] = AU2[0];
    U[1][1] = AU2[1];
    U[1][2] = AU2[2];
    U[2][0] = AU3[0];
    U[2][1] = AU3[1];
    U[2][2] = AU3[2];
}

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

int NLLS(float *mx, float *my, float *mz, float *p)
{
    int passo = 0, loop = 1;
    float p0[9] = {1, 1, 1, 0, 0, 0, 0, 0, 0}, Be[tam], e[tam], f[tam], sx, sy, sz, bx, by, bz, rho, phi, lambida, error_ant, J, delta_J, mat_H[N][tam];
    float sin_phi, sin_rho, sin_lambda, cos_phi, cos_rho, cos_lambda;
    float Ht_H[N][N], Ht_e[N], inv[N][N], mul_mat[N][tam];

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

int TWOSTEP(float *mx, float *my, float *mz, float *p)
{
    int passo_max = 200;
    float stop = pow(10, -24);
    float H[tam], Sigma_noise[3][tam];

    int passo = 0, loop = 1;
    float z_k[tam], mu_k[tam], sigma_k[tam], L_k[9][tam], sigma_bar = 0;
    float z_bar = 0, mu_bar = 0, L_bar[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    float z_tilde[tam], mu_tilde[tam], L_tilde[9][tam];
    float F_tt[9][9], F_tt_copy[9][9], P_tt[9][9];
    float theta[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}, theta1[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    float ABC[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    float TS_erro = 0, c[3], E[3][3], E_inv[3][3], tmp[3][3], dJdThetap_tilde[9], dbsqdtheta_p[9], dJdThetap_bar[9], dJdThetap_bar_scalar = 0, dJdTheta[9], F_tt_bar[9][9], F_tt_bar_copy[9][9], F_tt_bar_vet[9], F_tt_bar_inv[9][9], theta_np1[9], E_inv_c[3] = {0, 0, 0};
    float U[3][3], S[3][3], W[3][3], D[3][3], D_copy[3][3], h[3], D_inv[3][3];

    for(int i=0; i < tam; i++)
    {
        H[i] = 1;
        Sigma_noise[0][i] = 0.006*0.006;
        Sigma_noise[1][i] = 0.006*0.006;
        Sigma_noise[2][i] = 0.006*0.006;
        z_k[i] = pow(sqrt(mx[i]*mx[i] + my[i]*my[i] + mz[i]*mz[i]), 2) - H[i]*H[i];
        mu_k[i] = -(Sigma_noise[0][i] + Sigma_noise[1][i] + Sigma_noise[2][i]);
        sigma_k[i] = 4*(mx[i]*mx[i]*Sigma_noise[0][i] + my[i]*my[i]*Sigma_noise[1][i] + mz[i]*mz[i]*Sigma_noise[2][i]) + 2*(Sigma_noise[0][i]*Sigma_noise[0][i] + Sigma_noise[1][i]*Sigma_noise[1][0] + Sigma_noise[2][i]*Sigma_noise[2][i]);
        sigma_bar += 1/sigma_k[i];
        L_k[0][i] = 2*mx[i];
        L_k[1][i] = 2*my[i];
        L_k[2][i] = 2*mz[i];
        L_k[3][i] = -(mx[i]*mx[i]);
        L_k[4][i] = -(my[i]*my[i]);
        L_k[5][i] = -(mz[i]*mz[i]);
        L_k[6][i] = -2*mx[i]*my[i];
        L_k[7][i] = -2*mx[i]*mz[i];
        L_k[8][i] = -2*my[i]*mz[i];
    }
    sigma_bar = 1/sigma_bar;
    
    
    for(int i=0; i < tam; i++)
    {
        z_bar += z_k[i]*sigma_bar/sigma_k[i];
        mu_bar += mu_k[i]*sigma_bar/sigma_k[i];
        for(int j=0; j < 9; j++)
        {
            L_bar[j] += L_k[j][i]*sigma_bar/sigma_k[i];
        }
    }

    
    for(int i=0; i < tam; i++)
    {
        z_tilde[i] = z_k[i] - z_bar;
        mu_tilde[i] = mu_k[i] - mu_bar;
        for(int j=0; j < 9; j++)
        {
            L_tilde[j][i] = L_k[j][i] - L_bar[j];
        }
    }

    
    for(int i=0; i < 9; i++)
    {
        for(int j=0; j < 9; j++)
        {
            F_tt[i][j] = 0;
            F_tt_copy[i][j] = 0;
            P_tt[i][j] = 0;
        }
    }

    for(int i=0; i < tam; i++)
    {
        for(int j=0; j < 9; j++)
        {
            for(int k=0; k < 9; k++)
            {
                F_tt[j][k] += (L_tilde[j][i]*L_tilde[k][i])/sigma_k[i];
                F_tt_copy[j][k] = F_tt[j][k];
            }
        }
    }

    inverter_matriz9x9(F_tt_copy, P_tt);

    
    for(int i=0; i < 9; i++)
    {
        for(int j=0; j < tam; j++)
        {
            theta1[i] += ((z_tilde[j]-mu_tilde[j])*L_tilde[i][j])/sigma_k[j];
        }
    }
    for(int i=0; i < 9; i++)
    {
        for(int j=0; j < 9; j++)
        {
            theta[j] += P_tt[i][j]*theta1[i];
        }
    }

    
    for(int i=0; i < 9; i++)
    {
        for(int j=0; j < tam; j++)
        {
            ABC[i] -= ((z_tilde[j]-mu_tilde[j])*L_tilde[i][j])/sigma_k[j];
        }
    }
    
    while(loop == 1)
    {
        if(passo != 0)
        {
            for(int i=0; i < 9; i++)
            {
                theta[i] = theta_np1[i];
            }
        }
        
        c[0] = theta[0];
        c[1] = theta[1];
        c[2] = theta[2];

        E[0][0] = theta[3] + 1;
        E[0][1] = theta[6];
        E[0][2] = theta[7];
        E[1][0] = theta[6];
        E[1][1] = theta[4] + 1;
        E[1][2] = theta[8];
        E[2][0] = theta[7];
        E[2][1] = theta[8];
        E[2][2] = theta[5] + 1;

        inverter_matriz3x3(E, E_inv);

        //Cálculo do vetor E_inv * c
        for(int i=0; i < 3; i++)
        {
            E_inv_c[i] = (E_inv[0][i] + E_inv[1][i] + E_inv[2][i])*c[i];
        }

        //Cálculo da matriz tmp = E_inv * c * E_inv * c
        for(int i=0; i < 3; i++)
        {
            for(int j=0; j < 3; j++)
            {
                tmp[i][j] = E_inv_c[i]*E_inv_c[j];
            }
        }

        //Cálculo do vetor dJdThetap_tilde
        for(int i=0; i < 9; i++)
        {
            dJdThetap_tilde[i] = ABC[i];
            for(int j=0; j < 9; j++)
            {
                dJdThetap_tilde[i] += F_tt[i][j]*theta[j];
            }
        }

        //Cálculo do vetor dbsqdtheta_p
        dbsqdtheta_p[0] = 2*E_inv_c[0];
        dbsqdtheta_p[1] = 2*E_inv_c[1];
        dbsqdtheta_p[2] = 2*E_inv_c[2];
        dbsqdtheta_p[3] = -tmp[0][0];
        dbsqdtheta_p[4] = -tmp[1][1];
        dbsqdtheta_p[5] = -tmp[2][2];
        dbsqdtheta_p[6] = -2*tmp[0][1];
        dbsqdtheta_p[7] = -2*tmp[0][2];
        dbsqdtheta_p[8] = -2*tmp[1][2];

        //Cálculo do vetor dJdThetap_bar
        dJdThetap_bar_scalar = 0;
        for(int i=0; i < 9; i++)
        {
            dJdThetap_bar_scalar -= L_bar[i]*theta[i];
        }
        for(int i=0; i < 3; i++)
        {
            dJdThetap_bar_scalar += c[i]*E_inv_c[i];
        }
        dJdThetap_bar_scalar = dJdThetap_bar_scalar - mu_bar + z_bar;
        dJdThetap_bar_scalar = -dJdThetap_bar_scalar/sigma_bar;
        for(int i=0; i < 9; i++)
        {
            dJdThetap_bar[i] = dJdThetap_bar_scalar*(L_bar[i] - dbsqdtheta_p[i]);
        }

        //Cálculo do vetor dJdTheta
        for(int i=0; i < 9; i++)
        {
            dJdTheta[i] = dJdThetap_tilde[i] + dJdThetap_bar[i];
        }

        //Cálculo da matriz F_tt_bar
        for(int i=0; i < 9; i++)
        {
            F_tt_bar_vet[i] = (L_bar[i] - dbsqdtheta_p[i]);
        }
        for(int i=0; i < 9; i++)
        {
            for(int j=0; j < 9; j++)
            {
                F_tt_bar[i][j] = (F_tt_bar_vet[i]*F_tt_bar_vet[j])/sigma_bar + F_tt[i][j];
                F_tt_bar_copy[i][j] = F_tt_bar[i][j];
            }
        }

        //Cálculo do vetor theta_np1
        inverter_matriz9x9(F_tt_bar_copy, F_tt_bar_inv);
        for(int i=0; i < 9; i++)
        {
            theta_np1[i] = theta[i];
            for(int j=0; j < 9; j++)
            {
                theta_np1[i] -= F_tt_bar_inv[i][j]*dJdTheta[j];
            }
        }

        //Cálculo do erro
        TS_erro = 0;
        for(int i=0; i < 9; i++)
        {
            for(int j=0; j < 9; j++)
            {
                TS_erro += (theta_np1[i] - theta[i])*F_tt_bar[i][j]*(theta_np1[j] - theta[j]);
            }
        }


        if(passo > passo_max || TS_erro < stop)
        {
            loop = 0;
        }
        passo += 1;
    }
    c[0] = theta[0];
    c[1] = theta[1];
    c[2] = theta[2];

    E[0][0] = theta[3];
    E[0][1] = theta[6];
    E[0][2] = theta[7];
    E[1][0] = theta[6];
    E[1][1] = theta[4];
    E[1][2] = theta[8];
    E[2][0] = theta[7];
    E[2][1] = theta[8];
    E[2][2] = theta[5];

    // Segundo passo, encontrando os parâmetros
    SVD_dec(E, U, S);
    W[0][0] = -1 + sqrt(S[0][0] + 1);
    W[0][1] = 0;
    W[0][2] = 0;
    W[1][0] = 0;
    W[1][1] = -1 + sqrt(S[1][1] + 1);
    W[1][2] = 0;
    W[2][0] = 0;
    W[2][1] = 0;
    W[2][2] = -1 + sqrt(S[2][2] + 1);

    for(int i=0; i < 3; i++)
    {
        for(int j=0; j < 3; j++)
        {
            D[i][j] = 0;
            for(int k=0; k < 3; k++)
            {
                D[i][j] += U[i][k]*W[k][k]*U[j][k];
            }
            if(i == j)
            {
                D_copy[i][j] = D[i][j] + 1;
            }
            else
            {
                D_copy[i][j] = D[i][j];
            }
        }
    }

    inverter_matriz3x3(D_copy, D_inv);

    for(int i=0; i < 3; i++)
    {
        h[i] = 0;
        for(int j=0; j < 3; j++)
        {
            h[i] += D_inv[i][j]*c[j];
        }
    }
    p[0] = h[0];
    p[1] = h[1];
    p[2] = h[2];
    p[3] = D[0][0];
    p[4] = D[1][1];
    p[5] = D[2][2];
    p[6] = D[0][1];
    p[7] = D[0][2];
    p[8] = D[1][2];

    return passo;
}

int main()
{
    return 0;
}