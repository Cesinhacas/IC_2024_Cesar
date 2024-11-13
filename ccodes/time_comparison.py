import numpy as np
import random
import pandas as pd
import time
import ctypes
import matplotlib.pyplot as plt

my_functions = ctypes.CDLL('./functions.so')
#dll_path = r'C:\\Users\\LabT5\\Desktop\\Cesar\\IC_2024_Cesar\\ccodes\\functions.dll'

#my_functions = ctypes.CDLL(dll_path)

my_functions.ETS.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]
my_functions.ETS.restype = ctypes.c_void_p

my_functions.NLLS.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]
my_functions.NLLS.restype = ctypes.c_int

my_functions.TWOSTEP.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]
my_functions.TWOSTEP.restype = ctypes.c_int

def gera_dados(erros):

    random.seed()
    phi_sphere = [0]
    theta_sphere = [0]

    for i in range(0, 180, 5):
        for j in range(6,354,12):
            phi_sphere.append(j)
            theta_sphere.append(i)


    x_sphere = np.sin(theta_sphere) * np.cos(phi_sphere)
    y_sphere = np.sin(theta_sphere) * np.sin(phi_sphere)
    z_sphere = np.cos(theta_sphere)
    e = [0, 0, 0, 0, 0, 0, 0, 0, 0]
    e[0] = (random.random()*0.4) + 0.8
    e[1] = (random.random()*0.4) + 0.8
    e[2] = (random.random()*0.4) + 0.8

    e[3] = (random.random()*0.4) - 0.2
    e[4] = (random.random()*0.4) - 0.2
    e[5] = (random.random()*0.4) - 0.2
    
    e[6] = ((random.random()*6) - 3) * (np.pi/180)
    e[7] = ((random.random()*6) - 3) * (np.pi/180)
    e[8] = ((random.random()*6) - 3) * (np.pi/180)

    dados_corrompidos = np.array([x_sphere, y_sphere, z_sphere]).transpose()
    offset = (np.array([e[3], e[4], e[5]])).transpose()
    scale =np.array([[e[0], 0, 0], [0, e[1], 0], [0, 0, e[2]]])
    T = np.array([[1, 0, 0], [np.sin(e[6]), np.cos(e[6]), 0], [np.sin(e[7])*np.cos(e[8]), np.sin(e[8]), np.cos(e[7])*np.cos(e[8])]])

    
    for j in range(len(x_sphere)):
        noise = 0.006*(np.random.rand(1,3))
        dados_corrompidos[j] = scale @ T @ np.array([dados_corrompidos[j][0], dados_corrompidos[j][1], dados_corrompidos[j][2]]).transpose() + offset + noise

    dados_corrompidos = dados_corrompidos.transpose()

    erros.extend(e)

    mx = dados_corrompidos[0]
    my = dados_corrompidos[1]
    mz = dados_corrompidos[2]
    dados = pd.array([mx, my, mz])
    dados = dados.transpose()

    return dados

num_exe = 3000
num_exe_TW = 3000
execution_time_ETS = 0
execution_time_NLLS = 0
execution_time_TWOSTEP = 0
error_vet_ETS = []
error_vet_NLLS = []
passos_NLLS = 0
passos_TWOSTEP = 0

for i in range(0, num_exe):
    erros = []
    dados = gera_dados(erros)
    mx = dados[0].astype(np.float32)
    my = dados[1].astype(np.float32)
    mz = dados[2].astype(np.float32)

    mx_ptr = mx.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    my_ptr = my.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    mz_ptr = mz.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

    mx_ptr1 = mx.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    my_ptr1 = my.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    mz_ptr1 = mz.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

    p0 = np.zeros(9, dtype=np.float32)
    p1 = np.zeros(9, dtype=np.float32)
    p2 = np.zeros(9, dtype=np.float32)
    p0_ptr = p0.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    p1_ptr = p1.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    p2_ptr = p2.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

    time_start_ETS = time.perf_counter_ns()
    my_functions.ETS(mx_ptr, my_ptr, mz_ptr, p0_ptr)
    time_end_ETS = time.perf_counter_ns()
    execution_time_ETS += (time_end_ETS - time_start_ETS)

    time_start_NLLS = time.perf_counter_ns()
    passos_NLLS_c = my_functions.NLLS(mx_ptr, my_ptr, mz_ptr, p1_ptr)
    time_end_NLLS = time.perf_counter_ns()
    passos_NLLS += passos_NLLS_c
    execution_time_NLLS += (time_end_NLLS - time_start_NLLS)

    time_start_TWOSTEP = time.perf_counter_ns()
    passos_TWOSTEP_c = my_functions.TWOSTEP(mx_ptr1, my_ptr1, mz_ptr1, p2_ptr)
    time_end_TWOSTEP = time.perf_counter_ns()
    if passos_TWOSTEP_c > 199:
        num_exe_TW -= 1
        passos_TWOSTEP = passos_TWOSTEP
        execution_time_TWOSTEP = execution_time_TWOSTEP
    else:
        passos_TWOSTEP += passos_TWOSTEP_c
        execution_time_TWOSTEP += (time_end_TWOSTEP - time_start_TWOSTEP)



execution_time_ETS = (execution_time_ETS/num_exe)/1000000

execution_time_NLLS = (execution_time_NLLS/num_exe)/1000000

execution_time_TWOSTEP = (execution_time_TWOSTEP/num_exe_TW)/1000000

passos_NLLS = passos_NLLS/num_exe
passos_TWOSTEP = passos_TWOSTEP/num_exe_TW

ratio = execution_time_NLLS/execution_time_ETS
ratio1 = execution_time_TWOSTEP/execution_time_ETS
raatio2 = execution_time_TWOSTEP/execution_time_NLLS

ratio3 = (num_exe_TW/num_exe)*100

print("Número de execuções: ", num_exe)
print("Execution time ETS: ", execution_time_ETS, "ms")
print("Execution time NLLS: ", execution_time_NLLS, "ms")
print("Passos NLLS: ", passos_NLLS)
print("Execution time TWOSTEP: ", execution_time_TWOSTEP, "ms")
print("Passos TWOSTEP: ", passos_TWOSTEP)
print("Número de execuções TWOSTEP: ", num_exe_TW)
print("Taxa de convergência: ", ratio3 , "%")
print("Execution time razão (tempo NLLS / tempo ETS): ", ratio)
print("Execution time razão (tempo TWOSTEP / tempo ETS): ", ratio1)
print("Execution time razão (tempo TWOSTEP / tempo NLLS): ", raatio2)