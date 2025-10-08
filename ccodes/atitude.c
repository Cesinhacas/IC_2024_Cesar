#include <math.h>

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
		  M[0][i] = r1[i];
		  M[1][i] = r2[i];
		  M[2][i] = r3[i];
	  }
}

void atitude_determination(double Mref[3][3], double Mobs[3][3], double atitude[3][3])
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
	// R = SigTot1^2 * eye(3) + (1/norm(cross(W1,W2)))^2 * (SigTot1^2* (W1'*W2) * (W1*W2' + W2*W1') + (SigTot2^2 - SigTot1^2)*W1*W1')
	double vec_prod[3], w1t_w2[3][3], w1_w2t[3][3], w2_w1t[3][3], w1_w1t[3][3];
	double norm;
	vec_prod[0] = w1[1]*w2[2] - w1[2]*w2[1];
	vec_prod[1] = w1[2]*w2[0] - w1[0]*w2[2];
	vec_prod[2] = w1[0]*w2[1] - w1[1]*w2[0];

	norm = sqrt(vec_prod[0]*vec_prod[0] + vec_prod[1]*vec_prod[1] + vec_prod[2]*vec_prod[2]);

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(i == j)
			{
				R[i][j] = sig1*sig1;
			}
			else
			{
				R[i][j] = 0;
			}
			// w1'*w2
			w1t_w2[i][j] = w1[i]*w2[j];
			// w1*w2'
			w1_w2t[i][j] = w1[j]*w2[i];
			// w2*w1'
			w2_w1t[i][j] = w2[j]*w1[i];
			// w1*w1'
			w1_w1t[i][j] = w1[i]*w1[j];
			R[i][j] += (1/(norm*norm))*(sig1*sig1*(w1t_w2[i][j] + w1_w2t[i][j]) + (sig2*sig2 - sig1*sig1)*w1_w1t[i][j]);
		}
	}
}

int main(void)
{
	return 0;
}