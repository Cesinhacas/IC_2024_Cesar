import numpy as np
import random
import pandas as pd
import time
import ctypes

my_functions = ctypes.CDLL('./functions.so')
#dll_path = r'C:\\Users\\LabT5\\Desktop\\Cesar\\IC_2024_Cesar\\ccodes\\functions.dll'

#my_functions = ctypes.CDLL(dll_path)

my_functions.ETS.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]
my_functions.ETS.restype = ctypes.c_void_p

my_functions.NLLS.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]
my_functions.NLLS.restype = ctypes.c_int

my_functions.TWOSTEP.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]
my_functions.TWOSTEP.restype = ctypes.c_int


phi_sphere = [0]
theta_sphere = [0]

for i in range(0, 180, 5):
    for j in range(6,354,12):
        phi_sphere.append(j)
        theta_sphere.append(i)


x_sphere = np.sin(theta_sphere) * np.cos(phi_sphere)
y_sphere = np.sin(theta_sphere) * np.sin(phi_sphere)
z_sphere = np.cos(theta_sphere)

param = pd.read_csv('/mnt/c/users/labt5/onedrive/desktop/cesar/IC_2024_Cesar/Dados/commum_param.csv', header=None) #c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/commum_param.csv
param = param.to_numpy()

num_exe = 3000
num_exe_TW = num_exe
execution_time_ETS = 0
execution_time_NLLS = 0
execution_time_TWOSTEP = 0
error_vet_ETS = np.zeros((num_exe, 9))
error_vet_NLLS = np.zeros((num_exe, 9))
passos_NLLS = 0
passos_TWOSTEP = 0

for i in range(0, num_exe):
    e = [0, 0, 0, 0, 0, 0, 0, 0, 0]
    e[0] = param[0][i]
    e[1] = param[1][i]
    e[2] = param[2][i]

    e[3] = param[3][i]
    e[4] = param[4][i]
    e[5] = param[5][i]
    
    e[6] = param[6][i]
    e[7] = param[7][i]
    e[8] = param[8][i]

    dados_corrompidos = np.array([x_sphere, y_sphere, z_sphere]).transpose()
    offset = (np.array([e[3], e[4], e[5]])).transpose()
    scale =np.array([[e[0], 0, 0], [0, e[1], 0], [0, 0, e[2]]])
    T = np.array([[1, 0, 0], [np.sin(e[6]), np.cos(e[6]), 0], [np.sin(e[7])*np.cos(e[8]), np.sin(e[8]), np.cos(e[7])*np.cos(e[8])]])

    
    for j in range(len(x_sphere)):
        noise = 0.006*(np.random.rand(1,3))
        dados_corrompidos[j] = scale @ T @ np.array([dados_corrompidos[j][0], dados_corrompidos[j][1], dados_corrompidos[j][2]]).transpose() + offset + noise

    dados_corrompidos = dados_corrompidos.transpose()

    mx = dados_corrompidos[0].astype(np.float32)
    my = dados_corrompidos[1].astype(np.float32)
    mz = dados_corrompidos[2].astype(np.float32)

    mx_ptr = mx.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    my_ptr = my.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    mz_ptr = mz.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

    '''
    mx_ptr1 = mx.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    my_ptr1 = my.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    mz_ptr1 = mz.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    '''

    p0 = np.zeros(9, dtype=np.float32)
    p1 = np.zeros(9, dtype=np.float32)
    #p2 = np.zeros(9, dtype=np.float32)
    p0_ptr = p0.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    p1_ptr = p1.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    #p2_ptr = p2.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

    time_start_ETS = time.perf_counter_ns()
    my_functions.ETS(mx_ptr, my_ptr, mz_ptr, p0_ptr)
    time_end_ETS = time.perf_counter_ns()
    execution_time_ETS += (time_end_ETS - time_start_ETS)
    p0 = np.ctypeslib.as_array(p0_ptr, shape=(9,))


    time_start_NLLS = time.perf_counter_ns()
    passos_NLLS_c = my_functions.NLLS(mx_ptr, my_ptr, mz_ptr, p1_ptr)
    time_end_NLLS = time.perf_counter_ns()
    passos_NLLS += passos_NLLS_c
    execution_time_NLLS += (time_end_NLLS - time_start_NLLS)
    p1 = np.ctypeslib.as_array(p1_ptr, shape=(9,))

    error_vet_ETS[i] = e - p1
    error_vet_NLLS[i] = e - p0


    '''
    time_start_TWOSTEP = time.perf_counter_ns()
    passos_TWOSTEP_c = my_functions.TWOSTEP(mx_ptr1, my_ptr1, mz_ptr1, p2_ptr)
    time_end_TWOSTEP = time.perf_counter_ns()
    passos_TWOSTEP += passos_TWOSTEP_c
    execution_time_TWOSTEP += (time_end_TWOSTEP - time_start_TWOSTEP)
    '''

error_vet_ETS = error_vet_ETS.transpose()
error_vet_NLLS = error_vet_NLLS.transpose()

error_vet_NLLS = pd.DataFrame(error_vet_NLLS)
error_vet_ETS = pd.DataFrame(error_vet_ETS)

error_vet_ETS.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/MCS_ETS_c.csv', header=False, index=False)
error_vet_NLLS.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/MCS_NLLS_c.csv', header=False, index=False)

execution_time_ETS = (execution_time_ETS/num_exe)/1000000

execution_time_NLLS = (execution_time_NLLS/num_exe)/1000000

#execution_time_TWOSTEP = (execution_time_TWOSTEP/num_exe_TW)/1000000

passos_NLLS = passos_NLLS/num_exe
#passos_TWOSTEP = passos_TWOSTEP/num_exe_TW

ratio = execution_time_NLLS/execution_time_ETS
#ratio1 = execution_time_TWOSTEP/execution_time_ETS
#raatio2 = execution_time_TWOSTEP/execution_time_NLLS

#ratio3 = (num_exe_TW/num_exe)*100

print("Número de execuções: ", num_exe)
print("Execution time ETS: ", execution_time_ETS, "ms")
print("Execution time NLLS: ", execution_time_NLLS, "ms")
print("Passos NLLS: ", passos_NLLS)
#print("Execution time TWOSTEP: ", execution_time_TWOSTEP, "ms")
#print("Passos TWOSTEP: ", passos_TWOSTEP)
#print("Número de execuções TWOSTEP: ", num_exe_TW)
#print("Taxa de convergência: ", ratio3 , "%")
print("Execution time razão (tempo NLLS / tempo ETS): ", ratio)
#print("Execution time razão (tempo TWOSTEP / tempo ETS): ", ratio1)
#print("Execution time razão (tempo TWOSTEP / tempo NLLS): ", raatio2)