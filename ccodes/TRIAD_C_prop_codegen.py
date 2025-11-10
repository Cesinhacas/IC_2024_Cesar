import numpy as np
import pandas as pd
import ctypes

my_FK = ctypes.CDLL('./propagador_FK.so')

# void propagador_FK(const double u_gyro[3], double Dt, const double PT_est[36],
#                    const double x_est[7], const double Q[36], double i_in,
#                    double x_prop[7], double PT_prop[36], double *i_out)
my_FK.propagador_FK.argtypes = [
    ctypes.POINTER(ctypes.c_double),  # u_gyro[3]
    ctypes.c_double,                  # Dt
    ctypes.POINTER(ctypes.c_double),  # PT_est[36]
    ctypes.POINTER(ctypes.c_double),  # x_est[7]
    ctypes.POINTER(ctypes.c_double),  # Q[36]
    ctypes.c_double,                  # i_in
    ctypes.POINTER(ctypes.c_double),  # x_prop[7]
    ctypes.POINTER(ctypes.c_double),  # PT_prop[36]
    ctypes.POINTER(ctypes.c_double),  # i_out
]
my_FK.propagador_FK.restype = None

dados_gyro = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/gyro_cinematica.csv', header=None)

dados_gyro = dados_gyro.to_numpy().transpose()

num_exe = len(dados_gyro[0])
print(num_exe)

estados_propagados = np.zeros((num_exe, 7))  # Estados propagados pelo filtro de Kalman
matrizes_cov_prop = np.zeros((num_exe, 6, 6))  # Matrizes de covariância propagadas pelo filtro de Kalman

# INICIALIZAÇÃO DOS ESTADOS PARA SIMULAÇÃO
x_prop = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0], dtype=np.float64)
PT_prop = np.zeros((6, 6), dtype=np.float64)
PT_est = 1e6*np.eye(6, dtype=np.float64)
# Matriz de ruído de processo (Q). Assumindo identidade escalada
# Ajuste conforme necessário para sua aplicação
Q = (1e-6) * np.eye(6, dtype=np.float64)
x_est = np.array([0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0], dtype=np.float64)

Dt = 0.05
Dt = ctypes.c_double(Dt)

x_prop_ptr = x_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

PT_prop_ptr = PT_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

PT_est_ptr = PT_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

x_est_ptr = x_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

Q_ptr = Q.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

for i in range(0, num_exe):
    gx = dados_gyro[0][i]
    gy = dados_gyro[1][i]
    gz = dados_gyro[2][i]

    g = np.array([gx, gy, gz])

    g_ptr = g.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    # i_in (double) e i_out (double*)
    i_out = ctypes.c_double(0.0)

    # Chamada: propagador_FK(u_gyro, Dt, PT_est, x_est, Q, i_in, x_prop, PT_prop, i_out)
    my_FK.propagador_FK(
        g_ptr,
        Dt,
        PT_est_ptr,
        x_est_ptr,
        Q_ptr,
        ctypes.c_double(float(i)),
        x_prop_ptr,
        PT_prop_ptr,
        ctypes.byref(i_out),
    )

    # Atualiza IN-PLACE os estados para a próxima iteração (não recrie arrays)
    PT_est[:, :] = np.ctypeslib.as_array(PT_prop_ptr, shape=(6, 6))
    x_est[:] = np.ctypeslib.as_array(x_prop_ptr, shape=(7,))

    print(i_out.value)

    estados_propagados[i] = np.ctypeslib.as_array(x_prop_ptr, shape=(7,)).copy()
    matrizes_cov_prop[i] = np.ctypeslib.as_array(PT_prop_ptr, shape=(6, 6)).copy()

    #if i == 3:
        #break

estados_propagados = pd.DataFrame(estados_propagados)
estados_propagados.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/estados_propagados_noest_c.csv', header=False, index=False)

matrizes_cov_prop = pd.DataFrame(matrizes_cov_prop.reshape(num_exe, 36))
matrizes_cov_prop.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/cov_triad_prop_noest_c.csv', header=False, index=False)