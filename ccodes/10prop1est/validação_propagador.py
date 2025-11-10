import numpy as np
import pandas as pd
import ctypes

my_FK = ctypes.CDLL('./filtro.so')

PT_est_mat = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/PT_est.csv', header=None)
x_est_mat = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/x_est.csv', header=None)

# PT_est.csv: 6x1206 (201 matrizes 6x6 concatenadas horizontalmente)
# Reshape mantendo ordem por colunas (Fortran) para agrupar blocos 6x6 corretamente
# (6, 1206) -> (6, 6, 1201)
PT_est_mat = PT_est_mat.to_numpy().reshape(6, 6, 1201, order='F')

# x_est.csv: 201x7 (201 linhas de estados)
x_est_mat = x_est_mat.to_numpy()  # shape: (201, 7)


my_FK.FK_prop.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_double, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_FK.FK_prop.restype = ctypes.c_void_p
my_FK.main.argtypes = []
my_FK.main.restype = ctypes.c_int

dados_gyro = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/10prop1est/gyro_out.csv', header=None)

dados_gyro = dados_gyro.to_numpy().transpose()

num_exe = len(dados_gyro[0])
print(num_exe)

estados_propagados = np.zeros((num_exe, 7))  # Estados propagados pelo filtro de Kalman
matrizes_cov_prop = np.zeros((num_exe, 6, 6))  # Matrizes de covariância propagadas pelo filtro de Kalman

# INICIALIZAÇÃO DOS ESTADOS PARA SIMULAÇÃO
x_prop = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0], dtype=np.float64)
PT_prop = np.zeros((6, 6), dtype=np.float64)

Dt = 0.05
Dt = ctypes.c_double(Dt)

my_FK.main()
x_prop_ptr = x_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

PT_prop_ptr = PT_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

# CONDIÇÕES INICIAIS PARA O ESTIMADOR (primeira iteração)
PT_est = 1e6 * np.eye(6, dtype=np.float64)
x_est = np.array([0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0], dtype=np.float64)

PT_est_ptr = PT_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
x_est_ptr = x_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

for i in range(0, num_exe):
    print("execução: ", i)

    gx = dados_gyro[0][i]
    gy = dados_gyro[1][i]
    gz = dados_gyro[2][i]

    g = np.array([gx, gy, gz])

    g_ptr = g.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    print("Estados estimados antes da propagação:", x_est)
    #(double *u_gyro, double Dt, double PT_est[6][6], double *x_est, double *x_prop, double PT_prop[6][6])
    my_FK.FK_prop(g_ptr, Dt, PT_est_ptr, x_est_ptr, x_prop_ptr, PT_prop_ptr)
    
    print("Estado estimado:")
    print(x_est)
    
    estados_propagados[i] = np.ctypeslib.as_array(x_prop_ptr, shape=(7,)).copy()
    print("Estado propagado:")
    print(estados_propagados[i])
    matrizes_cov_prop[i] = np.ctypeslib.as_array(PT_prop_ptr, shape=(6, 6)).copy()

    # ATUALIZAR estados estimados para a próxima iteração (saída do estimador do MATLAB)
    # Na última iteração não precisa atualizar
    PT_est = np.ascontiguousarray(PT_est_mat[:, :, i], dtype=np.float64)
    x_est = np.ascontiguousarray(x_est_mat[i], dtype=np.float64)
    
    PT_est_ptr = PT_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    x_est_ptr = x_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    
    print("Estados carregados do MATLAB para próxima iteração:", x_est)

    #if i == 2:
        #break

estados_propagados = pd.DataFrame(estados_propagados)
estados_propagados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/estados_propagados_est_c_10prop1est.csv', header=False, index=False)

matrizes_cov_prop = pd.DataFrame(matrizes_cov_prop.reshape(num_exe, 36))
matrizes_cov_prop.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/cov_triad_prop_est_c_10prop1est.csv', header=False, index=False)