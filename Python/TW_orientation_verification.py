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
    dif_norm_TW[i] = dados[:, i] - rest_TW[:, i]
    dif_norm_NLLS[i] = dados[:, i] - rest_NLLS[:, i]

dif_norm_TW = pd.DataFrame(dif_norm_TW)
dif_norm_TW.to_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dif_norm.csv', header=False)

dif_norm_NLLS = pd.DataFrame(dif_norm_NLLS)
dif_norm_NLLS.to_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dif_norm_NLLS.csv', header=False)