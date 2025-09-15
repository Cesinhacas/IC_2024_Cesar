import numpy as np
import pandas as pd
import time
import ctypes

my_functions = ctypes.CDLL('./functions.so')
my_functions_64 = ctypes.CDLL('./functions_64.so')
#dll_path = r'C:\\Users\\LabT5\\Desktop\\Cesar\\IC_2024_Cesar\\ccodes\\functions.dll'

#my_functions = ctypes.CDLL(dll_path)

my_functions.ETS.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]
my_functions.ETS.restype = ctypes.c_void_p

my_functions.NLLS.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]
my_functions.NLLS.restype = ctypes.c_int

my_functions.TWOSTEP.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]
my_functions.TWOSTEP.restype = ctypes.c_int


my_functions_64.ETS_64.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_functions_64.ETS_64.restype = ctypes.c_void_p

my_functions_64.NLLS_64.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_functions_64.NLLS_64.restype = ctypes.c_int

num_exe = 3000
num_exe_TW = num_exe
execution_time_ETS = 0
execution_time_NLLS = 0
execution_time_ETS_64 = 0
execution_time_NLLS_64 = 0
execution_time_TWOSTEP = 0
error_vet_ETS = np.zeros((num_exe, 9))
error_vet_NLLS = np.zeros((num_exe, 9))
error_vet_ETS_64 = np.zeros((num_exe, 9))
error_vet_NLLS_64 = np.zeros((num_exe, 9))
passos_NLLS = 0
passos_NLLS_64 = 0
passos_TWOSTEP = 0

for i in range(0, num_exe):
    str_save = '/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_com_ruido/conjunto_dados_corrompidos_' + str(i+1) + '.csv'
    #str_save = '/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/dados_ATmega/run' + str(i+1) + '.txt'

    dados_corrompidos = pd.read_csv(str_save, header=None)
    dados_corrompidos = dados_corrompidos.to_numpy()

    str_save = '/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_com_ruido/param_' + str(i+1) + '.csv'

    e = pd.read_csv(str_save, header=None)
    e = e.to_numpy()
    e = e.transpose()

    mx = dados_corrompidos[0].astype(np.float32)
    my = dados_corrompidos[1].astype(np.float32)
    mz = dados_corrompidos[2].astype(np.float32)

    mx_ptr = mx.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    my_ptr = my.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    mz_ptr = mz.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

    mx_64 = dados_corrompidos[0].astype(np.double)
    my_64 = dados_corrompidos[1].astype(np.double)
    mz_64 = dados_corrompidos[2].astype(np.double)

    mx_ptr_64 = mx_64.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    my_ptr_64 = my_64.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    mz_ptr_64 = mz_64.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

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

    p0_64 = np.zeros(9, dtype=np.double)
    p1_64 = np.zeros(9, dtype=np.double)

    p0_ptr_64 = p0_64.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    p1_ptr_64 = p1_64.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    time_start_ETS_64 = time.perf_counter_ns()
    my_functions_64.ETS_64(mx_ptr_64, my_ptr_64, mz_ptr_64, p0_ptr_64)
    time_end_ETS_64 = time.perf_counter_ns()
    execution_time_ETS_64 += (time_end_ETS_64 - time_start_ETS_64)
    p0_64 = np.ctypeslib.as_array(p0_ptr_64, shape=(9,))


    time_start_NLLS_64 = time.perf_counter_ns()
    passos_NLLS_c_64 = my_functions_64.NLLS_64(mx_ptr_64, my_ptr_64, mz_ptr_64, p1_ptr_64)
    time_end_NLLS_64 = time.perf_counter_ns()
    passos_NLLS_64 += passos_NLLS_c_64
    execution_time_NLLS_64 += (time_end_NLLS_64 - time_start_NLLS_64)
    p1_64 = np.ctypeslib.as_array(p1_ptr_64, shape=(9,))
    
    error_vet_ETS_64[i] = e - p1_64
    error_vet_NLLS_64[i] = e - p0_64
    '''
    time_start_TWOSTEP = time.perf_counter_ns()
    passos_TWOSTEP_c = my_functions.TWOSTEP(mx_ptr1, my_ptr1, mz_ptr1, p2_ptr)
    time_end_TWOSTEP = time.perf_counter_ns()
    passos_TWOSTEP += passos_TWOSTEP_c
    execution_time_TWOSTEP += (time_end_TWOSTEP - time_start_TWOSTEP)
    '''

error_vet_ETS = error_vet_ETS.transpose()
error_vet_NLLS = error_vet_NLLS.transpose()

error_vet_ETS_64 = error_vet_ETS_64.transpose()
error_vet_NLLS_64 = error_vet_NLLS_64.transpose()

error_vet_NLLS = pd.DataFrame(error_vet_NLLS)
error_vet_ETS = pd.DataFrame(error_vet_ETS)

error_vet_NLLS_64 = pd.DataFrame(error_vet_NLLS_64)
error_vet_ETS_64 = pd.DataFrame(error_vet_ETS_64)

error_vet_ETS.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/MCS_ETS_c.csv', header=False, index=False)
error_vet_NLLS.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/MCS_NLLS_c.csv', header=False, index=False)

error_vet_ETS_64.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/MCS_ETS_c_64.csv', header=False, index=False)
error_vet_NLLS_64.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/MCS_NLLS_c_64.csv', header=False, index=False)

execution_time_ETS = (execution_time_ETS/num_exe)/1000000

execution_time_NLLS = (execution_time_NLLS/num_exe)/1000000

execution_time_ETS_64 = (execution_time_ETS_64/num_exe)/1000000

execution_time_NLLS_64 = (execution_time_NLLS_64/num_exe)/1000000

#execution_time_TWOSTEP = (execution_time_TWOSTEP/num_exe_TW)/1000000

passos_NLLS = passos_NLLS/num_exe
passos_NLLS_64 = passos_NLLS_64/num_exe
#passos_TWOSTEP = passos_TWOSTEP/num_exe_TW

ratio = execution_time_NLLS/execution_time_ETS
ratio_64 = execution_time_NLLS_64/execution_time_ETS_64
#ratio1 = execution_time_TWOSTEP/execution_time_ETS
#raatio2 = execution_time_TWOSTEP/execution_time_NLLS

#ratio3 = (num_exe_TW/num_exe)*100

print("Número de execuções: ", num_exe)
print("Execution time ETS: ", execution_time_ETS, "ms")
print("execution time ETS 64: ", execution_time_ETS_64, "ms")
print("Execution time NLLS: ", execution_time_NLLS, "ms")
print("Passos NLLS: ", passos_NLLS)
print("Execution time NLLS 64: ", execution_time_NLLS_64, "ms")
print("Passos NLLS 64: ", passos_NLLS_64)
#print("Execution time TWOSTEP: ", execution_time_TWOSTEP, "ms")
#print("Passos TWOSTEP: ", passos_TWOSTEP)
#print("Número de execuções TWOSTEP: ", num_exe_TW)
#print("Taxa de convergência: ", ratio3 , "%")
print("Execution time razão (tempo NLLS / tempo ETS): ", ratio)
print("Execution time razão (tempo NLLS / tempo ETS 64): ", ratio_64)
#print("Execution time razão (tempo TWOSTEP / tempo ETS): ", ratio1)
#print("Execution time razão (tempo TWOSTEP / tempo NLLS): ", raatio2)
passos_NLLS = pd.DataFrame([passos_NLLS])
passos_NLLS.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/passos_NLLS_c.csv', header=False, index=False)
passos_NLLS_64 = pd.DataFrame([passos_NLLS_64])
passos_NLLS_64.to_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/passos_NLLS_c_64.csv', header=False, index=False)