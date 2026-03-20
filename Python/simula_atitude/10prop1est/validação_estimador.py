import numpy as np
import pandas as pd
import attitude

PT_prop_mat = pd.read_csv('C:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/PT_prop.csv', header=None)
x_prop_mat = pd.read_csv('C:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/x_prop.csv', header=None)
q_obs_mat = pd.read_csv('C:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/q_Triad.csv', header=None)
cov_matlab = pd.read_csv('C:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/R_triad.csv', header=None)

# TRIAD_out.csv: 1201x4 (1201 linhas de quatérnions)
q_obs = q_obs_mat.to_numpy()  # shape: (1201, 4)

# x_prop.csv: 1201x7 (1201 linhas de estados)
x_prop = x_prop_mat.to_numpy()  # shape: (1201, 7)

# PT_prop.csv: 6x1201 (1201 matrizes 6x6 concatenadas horizontalmente)
# Reshape mantendo ordem por colunas (Fortran) para agrupar blocos 6x6 corretamente
# (6, 1206) -> (6, 6, 1201)
PT_prop_mat = PT_prop_mat.to_numpy().reshape(6, 6, 1201, order='F')

# R_triad_matlab.csv: 3x603 (1201 matrizes 3x3 concatenadas horizontalmente)
# Reshape mantendo ordem por colunas (Fortran) para agrupar blocos 3x3 corretamente
# (3, 603) -> (3, 3, 1201)
R_mat = cov_matlab.to_numpy().reshape(3, 3, 1201, order='F')

num_exe = 1201

#  VETORES DE SAÍDA E ARMAZENAMENTO DOS DADOS DA SIMULAÇÃO
estados_estimados = np.zeros((num_exe, 7))  # Estados estimados pelo filtro de Kalman
covariancias_estimadas = np.zeros((num_exe, 7, 7))  # Matrizes de covariância estimadas pelo filtro de Kalman
covarianciasT_estimadas = np.zeros((num_exe, 6, 6))  # Matrizes de covariância estimadas pelo filtro de Kalman


# INICIALIZAÇÃO DOS ESTADOS PARA SIMULAÇÃO
PT_est = np.zeros((6, 6), dtype=np.float64)
P_est = np.zeros((7, 7), dtype=np.float64)
x_est = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0], dtype=np.float64)

for i in range(0, num_exe):
    #print("-----")
    print(i)
    PT_prop = PT_prop_mat[:, :, i]
    x = np.array([x_prop[i, 0], x_prop[i, 1], x_prop[i, 2], x_prop[i, 3], x_prop[i, 4], x_prop[i, 5], x_prop[i, 6]], dtype=np.float64)
    q = np.array([q_obs[i, 0], q_obs[i, 1], q_obs[i, 2], q_obs[i, 3]], dtype=np.float64)
    R = R_mat[:, :, i]

    print(f"Iteração {i+1}")
    #print("x_prop:", x)
    #print("q_obs:", q)
    #print("PT_prop:", PT_prop)

    cont = 1+i

    
    #(double *x_prop, double PT_prop[6][6], double *q_obs, double R[3][3], int iteracao, double *x_est, double PT_est[6][6], double P_est[7][7])
    x_est, P_est, PT_est = attitude.estimador(x, PT_prop, q, R, cont)

    print(cont)

    estados_estimados[i] = x_est.copy()
    covariancias_estimadas[i] = P_est.copy()
    covarianciasT_estimadas[i] = PT_est.copy()
    #if i == 5:
        #break

estados_estimados = pd.DataFrame(estados_estimados)
estados_estimados.to_csv('C:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/validacao_estimador_python.csv', header=False, index=False)

covariancias_estimadas = pd.DataFrame(covariancias_estimadas.reshape(num_exe, 49))
covariancias_estimadas.to_csv('C:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/validacao_estimador_cov_python.csv', header=False, index=False)

covarianciasT_estimadas = pd.DataFrame(covarianciasT_estimadas.reshape(num_exe, 36))
covarianciasT_estimadas.to_csv('C:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/validacao_estimador_covT_python.csv', header=False, index=False)