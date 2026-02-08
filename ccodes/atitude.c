#include <math.h>
#include <stdio.h>

void cria_triad(double *v1, double *v2, double *r1, double *r2, double *r3)
{
	double vec_prod[3];
	vec_prod[0] = v1[1]*v2[2] - v1[2]*v2[1];
	vec_prod[1] = v1[2]*v2[0] - v1[0]*v2[2];
	vec_prod[2] = v1[0]*v2[1] - v1[1]*v2[0];

	double norm = sqrt(vec_prod[0]*vec_prod[0] + vec_prod[1]*vec_prod[1] + vec_prod[2]*vec_prod[2]);

	r3[0] = v1[1]*vec_prod[2] - v1[2]*vec_prod[1];
	r3[1] = v1[2]*vec_prod[0] - v1[0]*vec_prod[2];
	r3[2] = v1[0]*vec_prod[1] - v1[1]*vec_prod[0];

	for(int i = 0; i < 3; i++)
	{
		r1[i] = v1[i];
		r2[i] = vec_prod[i]/norm;
		r3[i] /= norm;
	}
}

void vet2mat(double *r1, double *r2, double *r3, double M[3][3])
{
	for(int i = 0; i < 3; i++)
	  {
		  M[i][0] = r1[i];
		  M[i][1] = r2[i];
		  M[i][2] = r3[i];
	  }
}

void atitude_estimation(double Mref[3][3], double Mobs[3][3], double atitude[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			atitude[i][j] = 0;
	        for (int k = 0; k < 3; k++)
	        {
	        	atitude[i][j] += Mobs[i][k] * Mref[j][k];
	        }
	     }
	  }
}

void mat2quaternion(double atitude[3][3], double q[4])
{
	for(int i = 0; i < 3; i++)
	{
		q[0] += atitude[i][i];
	}

	q[0] = sqrt(q[0] + 1)/2;
	q[1] = (atitude[1][2] - atitude[2][1])/(4*q[0]);
	q[2] = (atitude[2][0] - atitude[0][2])/(4*q[0]);
	q[3] = (atitude[0][1] - atitude[1][0])/(4*q[0]);
}

void matcov(double sig1, double sig2, double *w1, double *w2, double R[3][3])
{
	// Pré-cálculo dos escalares para clareza
    double sig1_sq = sig1 * sig1;
    double sig2_sq = sig2 * sig2;

    // 1. Calcular o produto vetorial: V = W1 x W2
    double cross_prod[3];
    cross_prod[0] = w1[1] * w2[2] - w1[2] * w2[1];
    cross_prod[1] = w1[2] * w2[0] - w1[0] * w2[2];
    cross_prod[2] = w1[0] * w2[1] - w1[1] * w2[0];

    // 2. Calcular a norma ao quadrado do produto vetorial: norm_sq = ||V||^2
    double norm_sq = cross_prod[0] * cross_prod[0] + 
                     cross_prod[1] * cross_prod[1] + 
                     cross_prod[2] * cross_prod[2];

    // Evitar divisão por zero se os vetores forem paralelos
    /*if (norm_sq < 1e-12) {
        // Lidar com o caso singular (por exemplo, zerar a matriz ou retornar um erro)
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                R[i][j] = 0.0;
            }
        }
        return;
    }*/

    // 3. Calcular o coeficiente: coeff = 1 / norm_sq
    double coeff = 1.0 / norm_sq;

    // 4. Calcular o produto escalar: dot_w1_w2 = W1' * W2
    double dot_w1_w2 = w1[0] * w2[0] + w1[1] * w2[1] + w1[2] * w2[2];

    // 5. Construir a matriz R em um único laço
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Termo 1: SigTot1^2 * eye(3)
            // Usamos um ternário para criar a matriz identidade escalada
            R[i][j] = (i == j) ? sig1_sq : 0.0;
            
            // Termo 2: SigTot1^2 * (W1'*W2) * (W1*W2' + W2*W1')
            // (W1*W2' + W2*W1') na posição [i][j] é (w1[i]*w2[j] + w2[i]*w1[j])
            double term2 = sig1_sq * dot_w1_w2 * (w1[i] * w2[j] + w2[i] * w1[j]);

            // Termo 3: (SigTot2^2 - SigTot1^2) * W1*W1'
            // W1*W1' na posição [i][j] é w1[i]*w1[j]
            double term3 = (sig2_sq - sig1_sq) * (w1[i] * w1[j]);

            // Soma final, multiplicando os Termos 2 e 3 pelo coeficiente
            R[i][j] += coeff * (term2 + term3);
        }
    }
}

void TRIAD(double *v1_ref, double *v2_ref, double *v1_obs, double *v2_obs, double *q, double sig1, double sig2, double *R)
{
	double r1_ref[3], r2_ref[3], r3_ref[3];
	double r1_obs[3], r2_obs[3], r3_obs[3];
	double Mref[3][3], Mobs[3][3], atitude[3][3], R_[3][3];
	double norm = sqrt(v1_obs[0]*v1_obs[0] + v1_obs[1]*v1_obs[1] + v1_obs[2]*v1_obs[2]), norm2 = sqrt(v2_obs[0]*v2_obs[0] + v2_obs[1]*v2_obs[1] + v2_obs[2]*v2_obs[2]);
	double v1[3], v2[3], w1[3], w2[3];

	for(int i = 0; i < 3; i++)
	{
		v1[i] = v1_ref[i];
		v2[i] = v2_ref[i];
		w1[i] = v1_obs[i];
		w2[i] = v2_obs[i];
	}

	for(int i = 0; i < 3; i++)
	{
		w1[i] /= norm;
		w2[i] /= norm2;
	}

	cria_triad(v1, v2, r1_ref, r2_ref, r3_ref);
	cria_triad(w1, w2, r1_obs, r2_obs, r3_obs);
	vet2mat(r1_ref, r2_ref, r3_ref, Mref);
	vet2mat(r1_obs, r2_obs, r3_obs, Mobs);
	atitude_estimation(Mref, Mobs, atitude);
	mat2quaternion(atitude, q);

	matcov(sig1, sig2, w1, w2, R_);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			R[i*3 + j] = R_[i][j];
		}
	}
}

int main(void)
{
	return 0;
}