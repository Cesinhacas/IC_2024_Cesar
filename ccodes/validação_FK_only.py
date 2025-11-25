import numpy as np
import pandas as pd
import ctypes

my_FK = ctypes.CDLL('./FK.so')

my_FK.FK_prop.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_double, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_FK.FK_prop.restype = ctypes.c_void_p
my_FK.main.argtypes = []
my_FK.main.restype = ctypes.c_int
my_FK.FK_estimador.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.c_int, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_FK.FK_estimador.restype = ctypes.c_void_p

dados_gyro = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/gyro_out.csv', header=None)

dados_gyro = dados_gyro.to_numpy().transpose()

q_obs = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/q_Triad.csv', header=None)
q_obs = q_obs.to_numpy()

R_mat = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/R_Triad.csv', header=None)
R_mat = R_mat.to_numpy().reshape(3, 3, 1201, order='F')

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
estados_estimados = np.zeros((num_exe, 7))  # Estados estimados pelo filtro de Kalman
covariancias_estimadas = np.zeros((num_exe, 7, 7))  # Matrizes de covariância estimadas pelo filtro de Kalman
covarianciasT_estimadas = np.zeros((num_exe, 6, 6))  # Matrizes de covariância estimadas pelo filtro de Kalman


# INICIALIZAÇÃO DOS ESTADOS PARA SIMULAÇÃO
x_prop = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0], dtype=np.float64)
PT_prop = np.zeros((6, 6), dtype=np.float64)
PT_est = 1e6*np.eye(6, dtype=np.float64)
P_est = np.zeros((7, 7), dtype=np.float64)
x_est = np.array([0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0], dtype=np.float64)

my_FK.main()
x_prop_ptr = x_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

PT_prop_ptr = PT_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

PT_est_ptr = PT_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

P_est_ptr = P_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

x_est_ptr = x_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

for i in range(0, num_exe):
    gx = dados_gyro[0][i]
    gy = dados_gyro[1][i]
    gz = dados_gyro[2][i]

    g = np.array([gx, gy, gz])

    g_ptr = g.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    q = np.array([q_obs[i, 0], q_obs[i, 1], q_obs[i, 2], q_obs[i, 3]], dtype=np.float64)
    R = R_mat[:, :, i]

    q_ptr = q.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    R_ptr = R.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    cont = 1 + i
    cont = np.array([cont]).ctypes.data_as(ctypes.POINTER(ctypes.c_int))

    #(double *u_gyro, double Dt, double PT_est[6][6], double *x_est, double *x_prop, double PT_prop[6][6], int *i)
    my_FK.FK_prop(g_ptr, 0.05, PT_est_ptr, x_est_ptr, x_prop_ptr, PT_prop_ptr)
    #(double *x_prop, double PT_prop[6][6], double *q_obs, double R[3][3], int iteracao, double *x_est, double PT_est[6][6], double P_est[7][7])
    my_FK.FK_estimador(x_prop_ptr, PT_prop_ptr, q_ptr, R_ptr, cont.contents.value, x_est_ptr, PT_est_ptr, P_est_ptr)

    print(cont.contents.value)

    q = np.ctypeslib.as_array(q_ptr, shape=(4,))

    quaternion[i] = q.copy()

    R = np.ctypeslib.as_array(R_ptr, shape=(3, 3))

    matrizes_c[i] = R.copy()

    estados_propagados[i] = np.ctypeslib.as_array(x_prop_ptr, shape=(7,)).copy()

    estados_estimados[i] = np.ctypeslib.as_array(x_est_ptr, shape=(7,)).copy()
    #if i == 5:
    #    break

estados_propagados = pd.DataFrame(estados_propagados)
estados_propagados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/estados_prop_only_FK.csv', header=False, index=False)

estados_estimados = pd.DataFrame(estados_estimados)
estados_estimados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/estados_est_only_FK.csv', header=False, index=False)