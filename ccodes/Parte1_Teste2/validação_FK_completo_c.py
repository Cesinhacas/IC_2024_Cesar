import numpy as np
import pandas as pd
import ctypes

my_atitude = ctypes.CDLL('./atitude.so')
my_FK = ctypes.CDLL('./filtro.so')

my_atitude.TRIAD.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.c_double, ctypes.c_double, ctypes.POINTER(ctypes.c_double)]
my_atitude.TRIAD.restype = ctypes.c_void_p

my_FK.FK_prop.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_double, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_FK.FK_prop.restype = ctypes.c_void_p
my_FK.main.argtypes = []
my_FK.main.restype = ctypes.c_int
my_FK.FK_estimador.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.c_int, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_FK.FK_estimador.restype = ctypes.c_void_p

dados_accel = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/accel.csv', header=None)
dados_mag = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/mag.csv', header=None)
dados_gyro = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/gyro_out.csv', header=None)

dados_accel = dados_accel.to_numpy().transpose()
dados_mag = dados_mag.to_numpy().transpose()
dados_gyro = dados_gyro.to_numpy().transpose()


num_exe = len(dados_accel[0])
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

    w1_ptr = w1.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    w2_ptr = w2.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    
    q_ptr = q.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    R_ptr = R.ctypes.data_as(ctypes.POINTER(ctypes.c_double))    

    g_ptr = g.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    cont = 1 + i
    cont = np.array([cont]).ctypes.data_as(ctypes.POINTER(ctypes.c_int))

    my_atitude.TRIAD(v1_ptr, v2_ptr, w1_ptr, w2_ptr, q_ptr, 0.01, 0.01, R_ptr)
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
    matrizes_cov_prop[i] = np.ctypeslib.as_array(PT_prop_ptr, shape=(6, 6)).copy()

    estados_estimados[i] = np.ctypeslib.as_array(x_est_ptr, shape=(7,)).copy()
    covariancias_estimadas[i] = np.ctypeslib.as_array(P_est_ptr, shape=(7, 7)).copy()
    covarianciasT_estimadas[i] = np.ctypeslib.as_array(PT_est_ptr, shape=(6, 6)).copy()
    #if i == 5:
    #    break

quaternion = pd.DataFrame(quaternion)
quaternion.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/quaternion_c.csv', header=False, index=False)

estados_propagados = pd.DataFrame(estados_propagados)
estados_propagados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/estados_propagados_c.csv', header=False, index=False)

estados_estimados = pd.DataFrame(estados_estimados)
estados_estimados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/estados_estimados_c.csv', header=False, index=False)

'''matrizes_c = pd.DataFrame(matrizes_c.reshape(num_exe, 9))
matrizes_c.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/cov_triad_c_completo.csv', header=False, index=False)

matrizes_cov_prop = pd.DataFrame(matrizes_cov_prop.reshape(num_exe, 36))
matrizes_cov_prop.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/cov_triad_prop_c_completo.csv', header=False, index=False)

covariancias_estimadas = pd.DataFrame(covariancias_estimadas.reshape(num_exe, 49))
covariancias_estimadas.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/cov_triad_est_c_completo.csv', header=False, index=False)

covarianciasT_estimadas = pd.DataFrame(covarianciasT_estimadas.reshape(num_exe, 36))
covarianciasT_estimadas.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Parte1_Teste2/covT_triad_est_c_completo.csv', header=False, index=False)'''