import numpy as np
import pandas as pd

dados = pd.read_excel('C:/Users/LabT5/Onedrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Corrompidos.xlsx') #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompidos.xlsx
mx = dados.iloc[0].values
my = dados.iloc[1].values
mz = dados.iloc[2].values

stop = 1e-24
tam = len(mx)
passo_max = 200

H = np.ones(tam)
Sigma_noise = (0.006**2)*np.ones((tam, 3))

z_k = np.zeros(tam)
mu_k = np.zeros(tam)
sigma_k = np.zeros(tam)
L_k = np.zeros((tam, 9))
sigma_bar = 0

for i in range(tam):
    i_vec = np.array([mx[i], my[i], mz[i]]).transpose()
    z_k[i] = np.linalg.norm(i_vec)**2 - H[i]**2
    mu_k[i] = -(Sigma_noise[i, 0] + Sigma_noise[i, 1] + Sigma_noise[i, 2])
    sigma_k[i] = 4*i_vec.transpose()@np.array([[Sigma_noise[i, 0], 0, 0], [0, Sigma_noise[i, 1], 0], [0, 0, Sigma_noise[i, 2]]])@i_vec + 2*(Sigma_noise[i, 0]**2 + Sigma_noise[i, 1]**2 + Sigma_noise[i, 2]**2)
    sigma_bar += 1/sigma_k[i]
    L_k[i] = np.array([2*i_vec[0], 2*i_vec[1], 2*i_vec[2], -mx[i]**2, -my[i]**2, -mz[i]**2, -2*mx[i]*my[i], -2*mx[i]*mz[i], -2*my[i]*mz[i]])

sigma_bar = 1/sigma_bar

z_bar = 0
mu_bar = 0
L_bar = np.zeros(9)

for i in range(tam):
    z_bar += sigma_bar*(z_k[i]/sigma_k[i])
    mu_bar += sigma_bar*(mu_k[i]/sigma_k[i])
    L_bar += (sigma_bar/sigma_k[i])*L_k[i]

z_tilde = np.zeros(tam)
mu_tilde = np.zeros(tam)
L_tilde = np.zeros((tam, 9))

for i in range(tam):
    z_tilde[i] = z_k[i] - z_bar
    mu_tilde[i] = mu_k[i] - mu_bar
    L_tilde[i] = L_k[i] - L_bar

F_tt = np.zeros((9, 9))
for i in range(tam):
    F_tt += L_tilde[i].reshape(-1,1) @ L_tilde[i].reshape(1,-1) / sigma_k[i]

P_tt = np.linalg.inv(F_tt)

theta = np.zeros(9)
######## PROBLEMA COM O mu_tilde ########
for i in range(tam):
    theta += ((z_tilde[i] - mu_tilde[i])/sigma_k[i])*L_tilde[i]

theta = P_tt@theta

ABC = -(((z_tilde-mu_tilde)/sigma_k)@L_tilde).transpose()
passo = 0
loop = 1

while loop == 1:
    if passo != 0:
        theta = theta_np1
    
    c = np.array([theta[0], theta[1], theta[2]]).reshape(-1,1)
    E = np.array([[theta[3], theta[6], theta[7]], [theta[6], theta[4], theta[8]], [theta[7], theta[8], theta[5]]])

    E_inv = np.eye(3) + E
    E_inv = np.linalg.inv(E_inv)
    tmp = (E_inv@c) @ ((E_inv@c).transpose())
    dJdthetap_tilde = ABC + F_tt@theta
    vet = (E_inv@c).transpose()
    vet = np.array([vet[0][0], vet[0][1], vet[0][2]])
    dbsqdtheta_p = np.array([vet[0], vet[1], vet[2], -tmp[0][0], -tmp[1][1], -tmp[2][2], -2*tmp[0][1], -2*tmp[0][2], -2*tmp[1][2]]).transpose()
    dJdThetap_bar = (-(1/sigma_bar) * (L_bar - dbsqdtheta_p)*(z_bar - L_bar.transpose()@theta + c.transpose()@vet - mu_bar)).transpose()
    dJdTheta = dJdthetap_tilde + dJdThetap_bar

    F_tt_bar = ((L_bar.transpose()-dbsqdtheta_p).transpose()@(L_bar.transpose()-dbsqdtheta_p))/sigma_bar

    theta_np1 = theta - (np.linalg.inv(F_tt + F_tt_bar)@dJdTheta)
    TS_erro = (theta_np1 - theta).transpose()@(F_tt + F_tt_bar)@(theta_np1 - theta)

    if passo > passo_max:
        loop = 0
    if TS_erro < stop:
        loop = 0
    passo = passo + 1

U, S, Vh = np.linalg.svd(E)
S = np.eye(3) + S
W = -np.eye(3) + S**0.5

D = U@W@Vh
h = np.linalg.inv(D + np.eye(3))@c

print("Os offsets são:\n")
print("%.4f" % h[0], "Para x")
print("%.4f" % h[1], "Para y")
print("%.4f" % h[2], "Para z\n")

print("A matriz interia populada é:\n")
print(D)