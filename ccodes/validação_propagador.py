import numpy as np
import pandas as pd
import ctypes

my_FK = ctypes.CDLL('./FK.so')

my_FK.FK_prop.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_double, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_FK.FK_prop.restype = ctypes.c_void_p
my_FK.main.argtypes = []
my_FK.main.restype = ctypes.c_int

dados_gyro = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/gyro_out.csv', header=None)

dados_gyro = dados_gyro.to_numpy().transpose()

#x_est e PT_est inicializados como no validação_FK_completo_c.py
estados_estimados = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/x_est.csv', header=None)
cov_est = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/PT_est.csv', header=None)

estados_estimados = estados_estimados.to_numpy().transpose()
print(estados_estimados.shape)
cov_est = cov_est.to_numpy().reshape(6, 6, 1201, order='F')

num_exe = len(dados_gyro[0])
print(num_exe)
error_vet_TRIAD = np.zeros((num_exe, 4))

v1 = np.array([0, 1.0, 0])
v2 = np.array([1/np.sqrt(2), 0, 1/np.sqrt(2)])

v1_ptr = v1.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
v2_ptr = v2.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

#  VETORES DE SAÍDA E ARMAZENAMENTO DOS DADOS DA SIMULAÇÃO
quaternion = np.zeros((num_exe, 4))
matrizes_c = np.zeros((num_exe, 3, 3))  # Matrizes calculadas pelo código C
estados_propagados = np.zeros((num_exe, 7))  # Estados propagados pelo filtro de Kalman
matrizes_cov_prop = np.zeros((num_exe, 6, 6))  # Matrizes de covariância propagadas pelo filtro de Kalman


# INICIALIZAÇÃO DOS ESTADOS PARA SIMULAÇÃO
x_prop = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0], dtype=np.float64)
PT_prop = np.zeros((6, 6), dtype=np.float64)
PT_est = 1e6*np.eye(6, dtype=np.float64)
x_est = np.array([0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0], dtype=np.float64)

my_FK.main()
x_prop_ptr = x_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

PT_prop_ptr = PT_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

PT_est_ptr = PT_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

x_est_ptr = x_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

for i in range(0, num_exe):
    gx = dados_gyro[0][i]
    gy = dados_gyro[1][i]
    gz = dados_gyro[2][i]
    g = np.array([gx, gy, gz])       

    g_ptr = g.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    

    cont = 1 + i
    cont = np.array([cont]).ctypes.data_as(ctypes.POINTER(ctypes.c_int))

    #(double *u_gyro, double Dt, double PT_est[6][6], double *x_est, double *x_prop, double PT_prop[6][6], int *i)
    my_FK.FK_prop(g_ptr, 0.05, PT_est_ptr, x_est_ptr, x_prop_ptr, PT_prop_ptr)

    PT_est = cov_est[:, :, i]
    PT_est_ptr = PT_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    x_est = np.array([estados_estimados[0][i], estados_estimados[1][i], estados_estimados[2][i], estados_estimados[3][i], estados_estimados[4][i], estados_estimados[5][i], estados_estimados[6][i]], dtype=np.float64)
    x_est_ptr = x_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    print(cont.contents.value)

    estados_propagados[i] = np.ctypeslib.as_array(x_prop_ptr, shape=(7,)).copy()
    matrizes_cov_prop[i] = np.ctypeslib.as_array(PT_prop_ptr, shape=(6, 6)).copy()

'''quaternion = pd.DataFrame(quaternion)
quaternion.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/quaternion_c.csv', header=False, index=False)'''

estados_propagados = pd.DataFrame(estados_propagados)
estados_propagados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/validacao_propagador_only.csv', header=False, index=False)

'''estados_estimados = pd.DataFrame(estados_estimados)
estados_estimados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/estados_estimados_c.csv', header=False, index=False)

matrizes_c = pd.DataFrame(matrizes_c.reshape(num_exe, 9))
matrizes_c.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/cov_triad_c_completo.csv', header=False, index=False)

matrizes_cov_prop = pd.DataFrame(matrizes_cov_prop.reshape(num_exe, 36))
matrizes_cov_prop.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/cov_triad_prop_c_completo.csv', header=False, index=False)

covariancias_estimadas = pd.DataFrame(covariancias_estimadas.reshape(num_exe, 49))
covariancias_estimadas.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/cov_triad_est_c_completo.csv', header=False, index=False)

covarianciasT_estimadas = pd.DataFrame(covarianciasT_estimadas.reshape(num_exe, 36))
covarianciasT_estimadas.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/covT_triad_est_c_completo.csv', header=False, index=False)'''