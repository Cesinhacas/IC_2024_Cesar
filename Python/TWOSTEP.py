import numpy as np
import pandas as pd

def center_data(X_bar, X_tilde, X, sigma_k, sigma_bar):
    X_bar = np.sum(X/sigma_k) * sigma_bar
    for i in range(len(X)):
        X_tilde[i] = X[i] - X_bar

    

def theta_to_b_D(D, b, c, E):
    U,S = np.linalg.eig(E)

    S = np.sqrt(np.identity(3) + S)

    W = -np.identity(3) + S
    D = U @ W @ U.transpose()
    b = np.linalg.inv(np.identity(3) + D) @ c

def theta_to_c_E(c, E, theta):
    c = np.array([theta[0], theta[1], theta[2]])
    E = np.array([[theta[3], theta[6], theta[7]],
                  [theta[6], theta[5], theta[8]],
                  [theta[7], theta[8], theta[5]]])
    
def total_field(B_in):
    B_total = np.sum(B_in**2, axis=0)**0.5
    return B_total

def TS_fisher_center(sigma_bar, L_bar, dbsqdtheta_p):
    i_fisher_bar = ((L_bar.transponse() - dbsqdtheta_p).transponse() @ (L_bar.transponse() - dbsqdtheta_p)) / sigma_bar
    return i_fisher_bar

def TS_fisher_centered(sigma, L_tilde, i_fisher_tilde, i_fisherinv_tilde):
    i_fisher_tilde = ((L_tilde / sigma) @ L_tilde.transponse())
    i_fisherinv_tilde = np.linalg.inv(i_fisher_tilde)


dados = pd.read_excel('C:/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Corrompidos.xlsx') #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompidos.xlsx
mx = dados.iloc[0].values
my = dados.iloc[1].values
mz = dados.iloc[2].values

B = np.array([mx, my, mz])

H = np.ones(1112)
Sigma_noise = (0.006**2)*np.ones((1112,3))

stop_tol = 1e-24
max_n = 200
k_samples = len(mx)

b0 = np.zeros((1,3))
D0 = np.zeros(3)

L = np.array([2*mx, 2*my, 2*mz, mx**2, my**2, mz**2, mx*my, mx*mz, my*mz])

z = total_field(B)**2 - total_field(H)**2
mu = -np.sum(Sigma_noise, axis=1)

sigma = np.zeros((1112,1))
for i in range(k_samples):
    i_vec = np.array([mx[i], my[i], mz[i]]).transpose()
    cov_mat = np.array([[Sigma_noise[i][0], 0, 0], [0, Sigma_noise[i][1], 0], [0, 0, Sigma_noise[i][2]]])
    sigma[i] = 4*i_vec.transpose() @ cov_mat @ i_vec + 2*(Sigma_noise[i][0]+Sigma_noise[i][1]+Sigma_noise[i][2])**2


sigma_bar = 1/np.sum(1/sigma)

mu_bar = 0
mu_tilde = np.zeros((k_samples, 1))
z_bar = 0
z_tilde = np.zeros((k_samples, 1))
L_bar = np.zeros((1, 9))
L_tilde = np.zeros((k_samples, 9))

center_data(mu_bar, mu_tilde, mu, sigma, sigma_bar)
center_data(z_bar, z_tilde, z, sigma, sigma_bar)
center_data(L_bar, L_tilde, L, sigma, sigma_bar)

i_fisher_tilde = np.zeros(9,9)
i_fisherinv_tilde = np.zeros(9,9)
TS_fisher_centered(sigma, L_tilde, i_fisher_tilde, i_fisherinv_tilde)

theta = i_fisherinv_tilde @ (L_tilde @ ((z_tilde - mu_tilde).transpose() / sigma.transpose()).transpose())

passo = 0
loop = True
c = np.zeros(1,3)
E = np.zeros(3)

ABC = -(((z_tilde - mu_tilde)/sigma) @ L_tilde.transpose()).transpose()

while loop:
    if passo != 0:
        theta = theta_np1
    
    theta_to_c_E(c, E, theta)

    tmp = (np.linalg.inv(np.identity(3) + E)@c) @ (np.linalg.inv(np.identity(3) + E)@c)
    dbsqdtheta_p = np.array([2*(np.linalg.inv(np.identity(3)+E)@c), -np.diag(tmp), -2*tmp[0][1], -2*tmp[0][2], -2*tmp[1][2]])
    dJdThetap_tilde = ABC + i_fisher_tilde @ theta
    dJdThetap_bar = (-(1/sigma_bar) @ (L_bar.transpose() - dbsqdtheta_p) @ (z_bar - L_bar.transpose()@theta + c.transpose()@np.linalg.inv(np.identity(3) + E)@c - mu_bar)).transpose()
    dJdTheta = dJdThetap_tilde + dJdThetap_bar

    i_fisher_bar = TS_fisher_center(sigma_bar, L_bar, dbsqdtheta_p)

    theta_np1 = theta - np.linalg.inv(i_fisher_bar + i_fisher_tilde) @ dJdTheta

    TS_err = (theta_np1 - theta).transpose() @ (i_fisher_bar + i_fisher_tilde) @ (theta_np1 - theta)
    if TS_err < stop_tol:
        loop = False
    
    if passo > max_n:
        loop = False

    passo += 1

theta_to_c_E(c, E, theta)

theta_to_b_D(D0, b0, c, E)

print("A matriz D é:\n")
print(D0)
print("\nO vetor b é:\n")
print(b0)