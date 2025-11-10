import numpy as np
import pandas as pd
import ctypes

my_FK = ctypes.CDLL('./filtro.so')
my_atitude = ctypes.CDLL('./atitude.so')

my_atitude.TRIAD.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.c_double, ctypes.c_double, ctypes.POINTER(ctypes.c_double)]
my_atitude.TRIAD.restype = ctypes.c_void_p

my_FK.main.argtypes = []
my_FK.main.restype = ctypes.c_int
my_FK.FK_estimador.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.c_int, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_FK.FK_estimador.restype = ctypes.c_void_p

PT_prop_mat = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/PT_prop.csv', header=None)
x_prop_mat = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/x_prop.csv', header=None)

PT_prop_mat = PT_prop_mat.to_numpy().reshape(6, 6, 201, order='F')
x_prop_mat = x_prop_mat.to_numpy()  # shape: (201, 7)

dados_accel = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Accel_cinematica.csv', header=None)
dados_mag = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Mag_cinematica.csv', header=None)
dados_gyro = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/gyro_cinematica.csv', header=None)

dados_accel = dados_accel.to_numpy().transpose()
dados_mag = dados_mag.to_numpy().transpose()
dados_gyro = dados_gyro.to_numpy().transpose()

num_exe = len(dados_accel[0])
print(num_exe)

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

Dt = 0.05
Dt = ctypes.c_double(Dt)

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

    w1 = np.array([ax, ay, az], dtype=np.float64)
    w2 = np.array([mx, my, mz], dtype=np.float64)
    q = np.array([0.0, 0.0, 0.0, 0.0], dtype=np.float64)
    R = np.zeros((3, 3), dtype=np.float64)
    g = np.array([gx, gy, gz], dtype=np.float64)    

    w1_ptr = w1.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    w2_ptr = w2.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    
    q_ptr = q.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    R_ptr = R.ctypes.data_as(ctypes.POINTER(ctypes.c_double))    

    g_ptr = g.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    cont = ctypes.c_int(1 + i)

    my_atitude.TRIAD(v1_ptr, v2_ptr, w1_ptr, w2_ptr, q_ptr, 0.01, 0.01, R_ptr)

    #(double *u_gyro, double Dt, double PT_est[6][6], double *x_est, double *x_prop, double PT_prop[6][6], int *i)
    my_FK.FK_prop(g_ptr, Dt, PT_est_ptr, x_est_ptr, x_prop_ptr, PT_prop_ptr)

    estados_propagados[i] = np.ctypeslib.as_array(x_prop_ptr, shape=(7,)).copy()
    matrizes_cov_prop[i] = np.ctypeslib.as_array(PT_prop_ptr, shape=(6, 6)).copy()

    # Usar x_prop e PT_prop do MATLAB em vez dos calculados pelo propagador
    x_prop = np.ascontiguousarray(x_prop_mat[i], dtype=np.float64)
    x_prop_ptr = x_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    
    PT_prop = np.ascontiguousarray(PT_prop_mat[:, :, i], dtype=np.float64)
    PT_prop_ptr = PT_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    
    #(double *x_prop, double PT_prop[6][6], double *q_obs, double R[3][3], int iteracao, double *x_est, double PT_est[6][6], double P_est[7][7])
    my_FK.FK_estimador(x_prop_ptr, PT_prop_ptr, q_ptr, R_ptr, cont, x_est_ptr, PT_est_ptr, P_est_ptr)

    print(cont.value)

    # Copiar os valores atualizados dos ponteiros para os arrays numpy
    q = np.ctypeslib.as_array(q_ptr, shape=(4,)).copy()
    R = np.ctypeslib.as_array(R_ptr, shape=(3, 3)).copy()
    
    # Armazenar resultados
    quaternion[i] = q
    matrizes_c[i] = R

    estados_estimados[i] = np.ctypeslib.as_array(x_est_ptr, shape=(7,)).copy()
    covariancias_estimadas[i] = np.ctypeslib.as_array(P_est_ptr, shape=(7, 7)).copy()
    covarianciasT_estimadas[i] = np.ctypeslib.as_array(PT_est_ptr, shape=(6, 6)).copy()
    
    # Atualizar os arrays numpy com os valores modificados pelo estimador (para contiguidade)
    x_est = np.ascontiguousarray(estados_estimados[i], dtype=np.float64)
    PT_est = np.ascontiguousarray(covarianciasT_estimadas[i], dtype=np.float64)
    P_est = np.ascontiguousarray(covariancias_estimadas[i], dtype=np.float64)
    
    # Atualizar os ponteiros para a próxima iteração
    x_est_ptr = x_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    PT_est_ptr = PT_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    P_est_ptr = P_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    
    #if i == 10:
        #break

estados_propagados = pd.DataFrame(estados_propagados)
estados_propagados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/estados_propagados_c_tudo_menos_PT_prop.csv', header=False, index=False)

matrizes_cov_prop = pd.DataFrame(matrizes_cov_prop.reshape(num_exe, 36))
matrizes_cov_prop.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/cov_triad_prop_c_tudo_menos_PT_prop.csv', header=False, index=False)

estados_estimados = pd.DataFrame(estados_estimados)
estados_estimados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/estados_estimados_c_tudo_menos_PT_prop.csv', header=False, index=False)

covariancias_estimadas = pd.DataFrame(covariancias_estimadas.reshape(num_exe, 49))
covariancias_estimadas.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/cov_triad_est_c_tudo_menos_PT_prop.csv', header=False, index=False)

covarianciasT_estimadas = pd.DataFrame(covarianciasT_estimadas.reshape(num_exe, 36))
covarianciasT_estimadas.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/cov_triadT_est_c_tudo_menos_PT_prop.csv', header=False, index=False)