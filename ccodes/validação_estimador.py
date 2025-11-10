import numpy as np
import pandas as pd
import ctypes

my_FK = ctypes.CDLL('./FK.so')

my_FK.main.argtypes = []
my_FK.main.restype = ctypes.c_int
my_FK.FK_estimador.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.c_int, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_FK.FK_estimador.restype = ctypes.c_void_p

PT_prop_mat = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/PT_prop.csv', header=None)
x_prop_mat = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/x_prop.csv', header=None)
q_obs_mat = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/TRIAD_out.csv', header=None)
cov_matlab = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/R_triad_matlab.csv', header=None)

# TRIAD_out.csv: 201x4 (201 linhas de quatérnions)
q_obs = q_obs_mat.to_numpy()  # shape: (201, 4)

# x_prop.csv: 201x7 (201 linhas de estados)
x_prop = x_prop_mat.to_numpy()  # shape: (201, 7)

# PT_prop.csv: 6x1206 (201 matrizes 6x6 concatenadas horizontalmente)
# Reshape mantendo ordem por colunas (Fortran) para agrupar blocos 6x6 corretamente
# (6, 1206) -> (6, 6, 201)
PT_prop_mat = PT_prop_mat.to_numpy().reshape(6, 6, 201, order='F')

# R_triad_matlab.csv: 3x603 (201 matrizes 3x3 concatenadas horizontalmente)
# Reshape mantendo ordem por colunas (Fortran) para agrupar blocos 3x3 corretamente
# (3, 603) -> (3, 3, 201)
R_mat = cov_matlab.to_numpy().reshape(3, 3, 201, order='F')

num_exe = 201

#  VETORES DE SAÍDA E ARMAZENAMENTO DOS DADOS DA SIMULAÇÃO
estados_estimados = np.zeros((num_exe, 7))  # Estados estimados pelo filtro de Kalman
covariancias_estimadas = np.zeros((num_exe, 7, 7))  # Matrizes de covariância estimadas pelo filtro de Kalman
covarianciasT_estimadas = np.zeros((num_exe, 6, 6))  # Matrizes de covariância estimadas pelo filtro de Kalman


# INICIALIZAÇÃO DOS ESTADOS PARA SIMULAÇÃO
PT_est = np.zeros((6, 6), dtype=np.float64)
P_est = np.zeros((7, 7), dtype=np.float64)
x_est = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0], dtype=np.float64)

my_FK.main()

PT_est_ptr = PT_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

P_est_ptr = P_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

x_est_ptr = x_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

for i in range(0, num_exe):
    #print("-----")
    print(i)
    PT_prop = PT_prop_mat[:, :, i]
    x = np.array([x_prop[i, 0], x_prop[i, 1], x_prop[i, 2], x_prop[i, 3], x_prop[i, 4], x_prop[i, 5], x_prop[i, 6]], dtype=np.float64)
    q = np.array([q_obs[i, 0], q_obs[i, 1], q_obs[i, 2], q_obs[i, 3]], dtype=np.float64)
    R = R_mat[:, :, i]

    #print(f"Iteração {i+1}")
    #print("x_prop:", x)
    #print("q_obs:", q)
    #print("R:", R)
    #print("PT_prop:", PT_prop)

    PT_prop_ptr = PT_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    x_prop_ptr = x.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    q_ptr = q.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    R_ptr = R.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    cont = 1+i
    cont = np.array([cont]).ctypes.data_as(ctypes.POINTER(ctypes.c_int))

    
    #(double *x_prop, double PT_prop[6][6], double *q_obs, double R[3][3], int iteracao, double *x_est, double PT_est[6][6], double P_est[7][7])
    my_FK.FK_estimador(x_prop_ptr, PT_prop_ptr, q_ptr, R_ptr, cont.contents.value, x_est_ptr, PT_est_ptr, P_est_ptr)

    print(cont.contents.value)

    R = np.ctypeslib.as_array(R_ptr, shape=(3, 3))

    estados_estimados[i] = np.ctypeslib.as_array(x_est_ptr, shape=(7,)).copy()
    covariancias_estimadas[i] = np.ctypeslib.as_array(P_est_ptr, shape=(7, 7)).copy()
    covarianciasT_estimadas[i] = np.ctypeslib.as_array(PT_est_ptr, shape=(6, 6)).copy()
    #if i == 5:
        #break

estados_estimados = pd.DataFrame(estados_estimados)
estados_estimados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/estados_estimados_mat_c.csv', header=False, index=False)

covariancias_estimadas = pd.DataFrame(covariancias_estimadas.reshape(num_exe, 49))
covariancias_estimadas.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/cov_triad_est_mat_c.csv', header=False, index=False)

covarianciasT_estimadas = pd.DataFrame(covarianciasT_estimadas.reshape(num_exe, 36))
covarianciasT_estimadas.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/covT_triad_est_mat_c.csv', header=False, index=False)