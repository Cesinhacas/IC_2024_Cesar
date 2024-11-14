import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Importar os dados
dados = pd.read_csv('C:/Users/LabT5/Onedrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Corrompido.csv', header=None) #mnt/c/users/labt5/OneDrive/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompidos.xlsx
mx = dados.iloc[0].values
my = dados.iloc[1].values
mz = dados.iloc[2].values
B = np.vstack([mx, my, mz])

# Parâmetros
sf = 1/2
param = pd.read_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/ccodes/dados.csv', header=None)
D = np.vstack([param.iloc[0][0:3].values, param.iloc[1][0:3].values, param.iloc[2][0:3].values])
h_t = np.vstack([param.iloc[3].values, param.iloc[4].values, param.iloc[5].values])
h = np.array([h_t[0][0], h_t[1][0], h_t[2][0]])

dados_rest = (B.copy()).T
for i in range(len(mx)):
    dados_rest[i] = (np.eye(3) + D) @ B[:, i] - h

dados_rest = dados_rest.transpose()
mx_rest = dados_rest[:][0]
my_rest = dados_rest[:][1]
mz_rest = dados_rest[:][2]

dados_rest = pd.DataFrame(dados_rest)
dados_rest.to_csv('C:/Users/LabT5/Onedrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_rest_TW.csv', header=False)

phi, theta = np.mgrid[0.0:2.0*np.pi:100j, 0.0:np.pi:50j]
x_sphere = (np.sin(theta) * np.cos(phi))*sf
y_sphere = (np.sin(theta) * np.sin(phi))*sf
z_sphere = np.cos(theta)*sf


# Criar uma figura
fig = plt.figure(figsize=(12,6))


ax1 = fig.add_subplot(121, projection='3d')
ax1.scatter(mx, my, mz, c='r', marker='o')
ax1.plot_wireframe(x_sphere, y_sphere, z_sphere, color='grey', alpha=0.5)
ax1.set_xlabel('Eixo X')
ax1.set_ylabel('Eixo Y')
ax1.set_zlabel('Eixo Z')
ax1.set_title('Plot corrompido')
ax1.set_box_aspect([1.0, 1.0, 1.0])

ax = fig.add_subplot(122, projection='3d')
ax.scatter(mx_rest, my_rest, mz_rest, c='r', marker='o')
ax.plot_wireframe(x_sphere, y_sphere, z_sphere, color='grey', alpha=0.5)
ax.set_xlabel('Eixo X')
ax.set_ylabel('Eixo Y')
ax.set_zlabel('Eixo Z')
ax.set_title('Plot reconstrução')
ax.set_box_aspect([1.0, 1.0, 1.0])

#plt.tight_layout()
plt.show()