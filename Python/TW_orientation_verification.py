import numpy as np
import pandas as pd

dados = pd.read_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Teoricos.csv', header=None) #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompido.csv
dados_TW = pd.read_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_rest_TW.csv', header=None) #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompido.csv
dados_NLLS = pd.read_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_rest_NLLS.csv', header=None) #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompido.csv

dados = dados.values
rest_TW = dados_TW.values
rest_NLLS = dados_NLLS.values

tam = len(dados[0])
dif_norm_TW = np.zeros((tam,3))
dif_norm_NLLS = np.zeros((tam,3))

for i in range(tam):
    dif_norm_TW[i] = rest_TW[:, i]
    dif_norm_NLLS[i] = rest_NLLS[:, i]

dif_norm_TW_data = pd.DataFrame(dif_norm_TW)
dif_norm_TW_data.to_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dif_norm.csv', header=False)

dif_norm_NLLS_data = pd.DataFrame(dif_norm_NLLS)
dif_norm_NLLS_data.to_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dif_norm_NLLS.csv', header=False)

dif_rms_TW_x =  np.sqrt(np.mean(dif_norm_TW[0,:]**2))
dif_rms_TW_y =  np.sqrt(np.mean(dif_norm_TW[1,:]**2))
dif_rms_TW_z =  np.sqrt(np.mean(dif_norm_TW[2,:]**2))

print(dif_rms_TW_x)
print(dif_rms_TW_y) 
print(dif_rms_TW_z)

dif_rms_NLLS_x =  np.sqrt(np.mean(dif_norm_NLLS[0,:]**2))
dif_rms_NLLS_y =  np.sqrt(np.mean(dif_norm_NLLS[1,:]**2))
dif_rms_NLLS_z =  np.sqrt(np.mean(dif_norm_NLLS[2,:]**2))

print(dif_rms_NLLS_x)
print(dif_rms_NLLS_y)
print(dif_rms_NLLS_z)