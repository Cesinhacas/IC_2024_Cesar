import numpy as np
import pandas as pd
import attitude

dados_accel = pd.read_csv('C:/Users/Cesin/Desktop/IC - 2024/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte2_Teste2b/accel.csv', header=None) #/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte2_Teste2b/accel.csv
dados_mag = pd.read_csv('C:/Users/Cesin/Desktop/IC - 2024/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte2_Teste2b/mag.csv', header=None) #/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte2_Teste2b/mag.csv
dados_gyro = pd.read_csv('C:/Users/Cesin/Desktop/IC - 2024/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte2_Teste2b/gyro_out.csv', header=None) #/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte2_Teste2b/gyro_out.csv

dados_accel = dados_accel.to_numpy().transpose()
dados_mag = dados_mag.to_numpy().transpose()
dados_gyro = dados_gyro.to_numpy().transpose()


num_exe = len(dados_accel[0])
print(num_exe)
error_vet_TRIAD = np.zeros((num_exe, 4))

v1 = np.array([0, 1.0, 0])
v2 = np.array([1/np.sqrt(2), 0, 1/np.sqrt(2)])

#  VETORES DE SAÍDA E ARMAZENAMENTO DOS DADOS DA SIMULAÇÃO
quaternion = np.zeros((num_exe, 4))
matrizes_c = np.zeros((num_exe, 3, 3))  # Matrizes calculadas pelo código C
estados_propagados = np.zeros((num_exe, 7))  # Estados propagados pelo filtro de Kalman
matrizes_cov_prop = np.zeros((num_exe, 6, 6))  # Matrizes de covariância propagadas pelo filtro de Kalman
estados_estimados = np.zeros((num_exe, 7))  # Estados estimados pelo filtro de Kalman
covariancias_estimadas = np.zeros((num_exe, 7, 7))  # Matrizes de covariância estimadas pelo filtro de Kalman
covarianciasT_estimadas = np.zeros((num_exe, 6, 6))  # Matrizes de covariância estimadas pelo filtro de Kalman


# INICIALIZAÇÃO DOS ESTADOS PARA SIMULAÇÃO
x_prop = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0], dtype=np.float64)
PT_prop = np.zeros((6, 6), dtype=np.float64)
PT_est = 1e6*np.eye(6, dtype=np.float64)
P_est = np.zeros((7, 7), dtype=np.float64)
x_est = np.array([0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0], dtype=np.float64)

Q = np.diag([0.005**2, 0.005**2, 0.005**2, 0.1**2, 0.1**2, 0.1**2])

for i in range(0, num_exe):
    ax = dados_accel[0][i]
    ay = dados_accel[1][i]
    az = dados_accel[2][i]
    
    mx = dados_mag[0][i]
    my = dados_mag[1][i]
    mz = dados_mag[2][i]

    gx = dados_gyro[0][i]
    gy = dados_gyro[1][i]
    gz = dados_gyro[2][i]

    w1 = np.array([ax, ay, az])
    w2 = np.array([mx, my, mz])
    q = np.array([0.0, 0.0, 0.0, 0.0])
    R = np.zeros((3, 3), dtype=np.float64)
    g = np.array([gx, gy, gz])

    cont = 1 + i
    print(cont)

    q, R = attitude.TRIAD(v1, v2, w1, w2, 0.01, 0.01)
    x_prop, PT_prop, i_out = attitude.propagador(g, 0.05, PT_est, x_est, Q, cont)
    x_est, P_est, PT_est = attitude.estimador(x_prop, PT_prop, q, R, cont)

    quaternion[i] = q.copy()

    matrizes_c[i] = R.copy()

    estados_propagados[i] = x_prop.copy()
    matrizes_cov_prop[i] = PT_prop.copy()

    estados_estimados[i] = x_est.copy()
    covariancias_estimadas[i] = P_est.copy()
    covarianciasT_estimadas[i] = PT_est.copy()
    #if i == 5:
    #    break

quaternion = pd.DataFrame(quaternion)
quaternion.to_csv('C:/Users/Cesin/Desktop/IC - 2024/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte2_Teste2b/quaternion_py.csv', header=False, index=False)

estados_propagados = pd.DataFrame(estados_propagados)
estados_propagados.to_csv('C:/Users/Cesin/Desktop/IC - 2024/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte2_Teste2b/estados_propagados_py.csv', header=False, index=False)

estados_estimados = pd.DataFrame(estados_estimados)
estados_estimados.to_csv('C:/Users/Cesin/Desktop/IC - 2024/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte2_Teste2b/estados_estimados_py.csv', header=False, index=False)