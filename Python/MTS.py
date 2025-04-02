import numpy as np
import pandas as pd
import functions

param = pd.read_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/commum_param.csv', header=None) #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/commum_param.csv
param = param.to_numpy()

exe = 3000
tempo_exe_ETS = 0
tempo_exe_NLLS = 0
error_vet_ETS = np.zeros((exe, 9))
error_vet_NLLS = np.zeros((exe, 9))


for i in range(0,exe):
    str_save = 'c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_com_ruido/conjunto_dados_corrompidos_' + str(i+1) + '.csv'

    dados_corrompidos = pd.read_csv(str_save, header=None)
    dados_corrompidos = dados_corrompidos.to_numpy()

    str_save = 'c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_com_ruido/param_' + str(i+1) + '.csv'

    e = pd.read_csv(str_save, header=None)
    e = e.to_numpy()
    e = e.transpose()
    

    mx = dados_corrompidos[0]
    my = dados_corrompidos[1]
    mz = dados_corrompidos[2]

    p, Time_ETS = functions.ETS_func(mx, my, mz)
    p0, Time_NLLS = functions.NLLS_func(mx, my, mz)

    tempo_exe_ETS += Time_ETS
    tempo_exe_NLLS += Time_NLLS

    error_vet_ETS[i] = e-p
    error_vet_NLLS[i] = e-p0

tempo_exe_ETS = (tempo_exe_ETS/exe)/1e6
tempo_exe_NLLS = (tempo_exe_NLLS/exe)/1e6
ratio = tempo_exe_NLLS/tempo_exe_ETS

print('Tempo de execução ETS: ', tempo_exe_ETS)
print('Tempo de execução NLLS: ', tempo_exe_NLLS)
print('Razão de tempo (NLLS/ETS): ', ratio)

error_vet_NLLS = np.array(error_vet_NLLS).transpose()
error_vet_ETS = np.array(error_vet_ETS).transpose()

error_vet_NLLS = pd.DataFrame(error_vet_NLLS)
error_vet_ETS = pd.DataFrame(error_vet_ETS)

error_vet_ETS.to_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/MCS_ETS.csv', header=False, index=False)
error_vet_NLLS.to_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/MCS_NLLS.csv', header=False, index=False)