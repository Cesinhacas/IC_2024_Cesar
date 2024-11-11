import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

dados = pd.read_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Corrompido.csv', header=None) #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompido.csv
mx = dados.iloc[0].values
my = dados.iloc[1].values
mz = dados.iloc[2].values
B = np.vstack([mx, my, mz])
sf = 1

# Parâmetros iniciais
stop = 1e-24
tam = B.shape[1]
passo_max = 200
Sigma_noise = (0.006**2)*np.ones((3, tam))
H = np.ones(tam)*sf

# Iniciando variáveis
z_k = np.zeros(tam)
mu_k = np.zeros(tam)
sigma_k = np.zeros(tam)
L_k = np.zeros((9, tam))
sigma_bar = 0

# Cálculo do erro, variância e média
for i in range(tam):
    i_vec = B[:, i]
    z_k[i] = np.linalg.norm(i_vec)**2 - H[i]**2
    mu_k[i] = -(Sigma_noise[0, i] + Sigma_noise[1, i] + Sigma_noise[2, i])
    sigma_k[i] = 4 * i_vec.T @ np.diag(Sigma_noise[:, i]) @ i_vec + \
                    2 * np.sum(Sigma_noise[:, i]**2)
    sigma_bar += 1 / sigma_k[i]
    L_k[:, i] = np.hstack([2 * i_vec, 
                            -B[0, i]**2, -B[1, i]**2, -B[2, i]**2, 
                            -2 * B[0, i] * B[1, i], -2 * B[0, i] * B[2, i], 
                            -2 * B[1, i] * B[2, i]])    
sigma_bar = 1 / sigma_bar

# Centralizando parâmetros
z_bar = 0
mu_bar = 0
L_bar = np.zeros(9)

for i in range(tam):
    z_bar += sigma_bar * (z_k[i] / sigma_k[i])
    mu_bar += sigma_bar * (mu_k[i] / sigma_k[i])
    L_bar += sigma_bar * L_k[:, i] / sigma_k[i]

# Calculando valores tilde
z_tilde = z_k - z_bar
mu_tilde = mu_k - mu_bar
L_tilde = L_k - L_bar[:, None]

F_tt = np.zeros((9, 9))
for i in range(tam):
    F_tt += np.outer(L_tilde[:, i], L_tilde[:, i]) / sigma_k[i]
P_tt = np.linalg.inv(F_tt)

# Inicializando theta
theta = np.zeros(9)
for i in range(tam):
    theta += ((z_tilde[i] - mu_tilde[i]) / sigma_k[i]) * L_tilde[:, i]
theta = P_tt @ theta

ABC = -((z_tilde - mu_tilde) / sigma_k) @ L_tilde.T
passo = 0
loop = True

# Loop principal
while loop:
    if passo != 0:
        theta = theta_np1

    c = theta[:3]
    E = np.array([  [theta[3], theta[6], theta[7]],
                    [theta[6], theta[4], theta[8]],
                    [theta[7], theta[8], theta[5]]])
    
    E_inv = np.array([  [theta[3] + 1, theta[6], theta[7]],
                        [theta[6], theta[4] + 1, theta[8]],
                        [theta[7], theta[8], theta[5] + 1]])
    E_inv = np.linalg.inv(E_inv)  # Inversa de (I + E)
    tmp = np.outer(E_inv @ c, E_inv @ c)  # Produto externo (resulta em matriz 3x3)


    dJdThetap_tilde = ABC + F_tt @ theta
    dbsqdtheta_p = np.hstack([   2 * E_inv @ c, 
                                -np.diag(tmp), 
                                -2 * tmp[0, 1], -2 * tmp[0, 2], -2 * tmp[1, 2]])

    dJdThetap_bar = (-1/sigma_bar) * (L_bar - dbsqdtheta_p) * (z_bar - mu_bar - (L_bar.T @ theta) + (c.T @ E_inv @ c)) 

    dJdTheta = dJdThetap_tilde + dJdThetap_bar

    F_tt_bar = np.outer(L_bar - dbsqdtheta_p, L_bar - dbsqdtheta_p) / sigma_bar

    theta_np1 = theta - np.linalg.inv(F_tt + F_tt_bar) @ dJdTheta

    TS_erro = (theta_np1 - theta).T @ (F_tt + F_tt_bar) @ (theta_np1 - theta)

    if passo > passo_max or TS_erro < stop:
        loop = False

    passo += 1

# Decomposição em autovalores e autovetores
U, S, Vh= np.linalg.svd(E)
S = np.eye(3) + np.diag(S)
W = -np.eye(3) + S**0.5

D = U @ W @ Vh
h = np.linalg.inv(np.eye(3) + D) @ c
print("\nQuantidade de passos: ", passo)
print("Os offsets são:\n")
print(h.T)

print("Os elementos da matriz com os parâmetros são:\n")
print(D)
print("\nE convergiu em : ", passo, " passos")

dados_rest = (B.copy()).T
for i in range(len(mx)):
    dados_rest[i] = (np.eye(3) + D) @ B[:, i] - h

dados_rest = dados_rest.transpose()
mx_rest = dados_rest[:][0]
my_rest = dados_rest[:][1]
mz_rest = dados_rest[:][2]

phi, theta = np.mgrid[0.0:2.0*np.pi:100j, 0.0:np.pi:50j]
x_sphere = (np.sin(theta) * np.cos(phi))*sf
y_sphere = (np.sin(theta) * np.sin(phi))*sf
z_sphere = np.cos(theta)*sf


# Criar uma figura
fig = plt.figure(figsize=(12,6))


ax1 = fig.add_subplot(121, projection='3d')
ax1.scatter(mx, my, mz, c='r', marker='o')
ax1.plot_wireframe(x_sphere, y_sphere, z_sphere, color='grey', alpha=0.5)
ax1.set_xlabel('Eixo X')
ax1.set_ylabel('Eixo Y')
ax1.set_zlabel('Eixo Z')
ax1.set_title('Plot corrompido')
ax1.set_box_aspect([1.0, 1.0, 1.0])

ax = fig.add_subplot(122, projection='3d')
ax.scatter(mx_rest, my_rest, mz_rest, c='r', marker='o')
ax.plot_wireframe(x_sphere, y_sphere, z_sphere, color='grey', alpha=0.5)
ax.set_xlabel('Eixo X')
ax.set_ylabel('Eixo Y')
ax.set_zlabel('Eixo Z')
ax.set_title('Plot reconstrução')
ax.set_box_aspect([1.0, 1.0, 1.0])

plt.tight_layout()
plt.show()