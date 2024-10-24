import numpy as np
import pandas as pd

# Critérios de parada
passo_max = 200
stop = 1e-24

####### Dados de entrada #######
dados = pd.read_excel('C:/Users/LabT5/Onedrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Corrompidos.xlsx') #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompidos.xlsx 
mx = dados.iloc[0].values # Eixo x campo lido pelo sensor
my = dados.iloc[1].values # Eixo y campo lido pelo sensor
mz = dados.iloc[2].values # Eixo z campo lido pelo sensor
tam = len(mx) # Tamanho dos vetores

noise = 0.006**2*np.ones((3,tam)) # Covariância do erro de medição
H = np.ones_like(mx) # Módulo do campo magnético

# Inicialização dos parâmetros estatísticos
z_k = np.zeros(tam)
mu_k = np.zeros(tam)
sigma_k = np.zeros(tam)
L_k = np.zeros((tam, 9))
sigma_bar = 0

# Atribuindo valores para os parametros estatísticos e sigma_bar
for i in range(tam):
    i_vec = np.array([mx[i], my[i], mz[i]])
    z_k[i] = np.linalg.norm(i_vec)**2 - H[i]**2
    mu_k[i] = -(noise[0][i] + noise[1][i] + noise[2][i])
    sigma_k[i] = 4*i_vec@np.array([[noise[0][i], 0, 0], [0, noise[1][i], 0], [0, 0, noise[2][i]]])@i_vec.T + 2*(noise[0][i]**2 + noise[1][i]**2 + noise[2][i]**2)
    L_k[i] = np.array([2*i_vec[0], 2*i_vec[1], 2*i_vec[2], -mx[i]**2, -my[i]**2, -mz[i]**2, -2*mx[i]*my[i], -2*mx[i]*mz[i], -2*my[i]*mz[i]])
    sigma_bar += 1/sigma_k[i]

sigma_bar = 1/sigma_bar

# Inicializando parâmetros que centralizam os parâmetros estatísticos
z_bar = 0
mu_bar = 0
L_bar = np.zeros(9)

# Atribuindo valores para os parâmetros centralizadores
for i in range(tam):
    z_bar += sigma_bar*(z_k[i]/sigma_k[i])
    mu_bar += sigma_bar*(mu_k[i]/sigma_k[i])
    L_bar += sigma_bar*(L_k[i]/sigma_k[i])

# Inicializando os parâmetros estatísticos centralizados
z_tilde = np.zeros_like(z_k)
mu_tilde = np.zeros_like(mu_k)
L_tilde = np.zeros_like(L_k)

# Centralizando os parâmetros estatísticos
for i in range(tam):
    z_tilde[i] = z_k[i] - z_bar
    mu_tilde[i] = mu_k[i] - mu_bar
    L_tilde[i] = L_k[i] - L_bar

# Inicializando as matrizes fisher
F_tt = np.zeros((9,9))
P_tt = np.zeros((9,9))

for i in range(tam):
    F_tt[0][0] += L_tilde[i][0]**2/sigma_k[i]
    F_tt[1][1] += L_tilde[i][1]**2/sigma_k[i]
    F_tt[2][2] += L_tilde[i][2]**2/sigma_k[i]
    F_tt[3][3] += L_tilde[i][3]**2/sigma_k[i]
    F_tt[4][4] += L_tilde[i][4]**2/sigma_k[i]
    F_tt[5][5] += L_tilde[i][5]**2/sigma_k[i]
    F_tt[6][6] += L_tilde[i][6]**2/sigma_k[i]
    F_tt[7][7] += L_tilde[i][7]**2/sigma_k[i]
    F_tt[8][8] += L_tilde[i][8]**2/sigma_k[i]

P_tt = np.linalg.inv(F_tt)

theta = np.zeros(1,9)