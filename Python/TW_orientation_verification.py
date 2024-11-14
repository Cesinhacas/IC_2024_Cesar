import numpy as np
import pandas as pd

dados_NLLS = pd.read_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_rest_NLLS.csv', header=None) #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompido.csv
dados_TW = pd.read_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_rest_TW.csv', header=None) #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompido.csv

rest_NLLS = dados_NLLS.values
rest_TW = dados_TW.values

tam = len(rest_NLLS[0])
dif_norm = np.zeros(tam)

for i in range(tam):
    dif_norm[i] = np.linalg.norm(rest_NLLS[:, i] - rest_TW[:, i])

dif_norm = pd.DataFrame(dif_norm)
dif_norm.to_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dif_norm.csv', header=False)