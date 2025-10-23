#include <math.h>
#include <stdio.h>

void normalize(double *v, double *v_norm) {
    double norm = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if (norm > 1e-12) {
        v_norm[0] = v[0] / norm;
        v_norm[1] = v[1] / norm;
        v_norm[2] = v[2] / norm;
    } else {
        v_norm[0] = v_norm[1] = v_norm[2] = 0.0;
    }
}

void cross_product(double *a, double *b, double *c) {
    c[0] = a[1]*b[2] - a[2]*b[1];
    c[1] = a[2]*b[0] - a[0]*b[2];
    c[2] = a[0]*b[1] - a[1]*b[0];
}

void TRIAD(double *v1_ref, double *v2_ref, double *v1_obs, double *v2_obs, double *q)
{
    double r1_ref[3], r2_ref[3], r3_ref[3];
    double r1_obs[3], r2_obs[3], r3_obs[3];
    double temp[3];
    
    // Criar sistema de referência
    normalize(v1_ref, r1_ref);
    cross_product(v1_ref, v2_ref, temp);
    normalize(temp, r2_ref);
    cross_product(r1_ref, r2_ref, r3_ref);
    
    // Criar sistema observado
    normalize(v1_obs, r1_obs);
    cross_product(v1_obs, v2_obs, temp);
    normalize(temp, r2_obs);
    cross_product(r1_obs, r2_obs, r3_obs);
    
    // Matriz de atitude: A = M_obs * M_ref^T
    double A[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = r1_obs[i]*r1_ref[j] + r2_obs[i]*r2_ref[j] + r3_obs[i]*r3_ref[j];
        }
    }
    
    // Converter para quaternion
    double trace = A[0][0] + A[1][1] + A[2][2];
    
    if (trace > 0) {
        double s = sqrt(trace + 1.0) * 2.0; // s = 4 * q0
        q[0] = 0.25 * s;
        q[1] = (A[2][1] - A[1][2]) / s;
        q[2] = (A[0][2] - A[2][0]) / s;
        q[3] = (A[1][0] - A[0][1]) / s;
    } else if (A[0][0] > A[1][1] && A[0][0] > A[2][2]) {
        double s = sqrt(1.0 + A[0][0] - A[1][1] - A[2][2]) * 2.0; // s = 4 * q1
        q[0] = (A[2][1] - A[1][2]) / s;
        q[1] = 0.25 * s;
        q[2] = (A[0][1] + A[1][0]) / s;
        q[3] = (A[0][2] + A[2][0]) / s;
    } else if (A[1][1] > A[2][2]) {
        double s = sqrt(1.0 + A[1][1] - A[0][0] - A[2][2]) * 2.0; // s = 4 * q2
        q[0] = (A[0][2] - A[2][0]) / s;
        q[1] = (A[0][1] + A[1][0]) / s;
        q[2] = 0.25 * s;
        q[3] = (A[1][2] + A[2][1]) / s;
    } else {
        double s = sqrt(1.0 + A[2][2] - A[0][0] - A[1][1]) * 2.0; // s = 4 * q3
        q[0] = (A[1][0] - A[0][1]) / s;
        q[1] = (A[0][2] + A[2][0]) / s;
        q[2] = (A[1][2] + A[2][1]) / s;
        q[3] = 0.25 * s;
    }
}

int main(void)
{
    return 0;
}