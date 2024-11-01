import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Carregar dados
dados = pd.read_excel('C:/Users/LabT5/Onedrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Corrompidos.xlsx') #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompidos.xlsx
mx = dados.iloc[0].values
my = dados.iloc[1].values
mz = dados.iloc[2].values

# Cálculo dos termos
mxs = mx**2
mys = -my**2
mzs = mz**2

mxy = mx * my
mxz = mx * mz
myz = my * mz
vet = np.ones_like(mx)

# Construção da matriz H e sua transposta
mat_H_t = np.array([mxs, mxy, mxz, myz, mzs, mx, my, mz, vet])
mat_H = mat_H_t.transpose()

# Pseudo-inversa e cálculo de vet_X
vet_X = np.linalg.pinv(mat_H) @ mys

# Cálculo dos offsets
psi7 = 2 * (vet_X[4] * vet_X[1]**2 - vet_X[1] * vet_X[2] * vet_X[3] + vet_X[2]**2 + vet_X[0] * vet_X[3]**2 - 4 * vet_X[0] * vet_X[4])

bx = -(vet_X[3]**2 * vet_X[5] + 2 * vet_X[2] * vet_X[7] - 4 * vet_X[4] * vet_X[5] - vet_X[1] * vet_X[3] * vet_X[7] + 2 * vet_X[1] * vet_X[4] * vet_X[6] - vet_X[2] * vet_X[3] * vet_X[6]) / psi7
by = -(vet_X[2]**2 * vet_X[6] + 2 * vet_X[0] * vet_X[3] * vet_X[7] - 4 * vet_X[0] * vet_X[4] * vet_X[6] - vet_X[1] * vet_X[2] * vet_X[7] + 2 * vet_X[1] * vet_X[4] * vet_X[5] - vet_X[2] * vet_X[3] * vet_X[5]) / psi7
bz = -(vet_X[1]**2 * vet_X[7] - 4 * vet_X[0] * vet_X[7] + 2 * vet_X[2] * vet_X[5] + 2 * vet_X[0] * vet_X[3] * vet_X[6] - vet_X[1] * vet_X[2] * vet_X[6] - vet_X[1] * vet_X[3] * vet_X[5]) / psi7

# Continuação dos cálculos
psi8 = -(vet_X[1]**2) * (vet_X[7]**2) + 4 * vet_X[4] * vet_X[8] * (vet_X[1]**2) - 4 * vet_X[8] * vet_X[1] * vet_X[2] * vet_X[3] + 2 * vet_X[1] * vet_X[2] * vet_X[6] * vet_X[7] + 2 * vet_X[1] * vet_X[3] * vet_X[5] * vet_X[7] - 4 * vet_X[4] * vet_X[1] * vet_X[5] * vet_X[6] - (vet_X[2]**2) * (vet_X[6]**2) + 4 * vet_X[8] * (vet_X[2]**2) + 2 * vet_X[2] * vet_X[3] * vet_X[5] * vet_X[6] - 4 * vet_X[2] * vet_X[5] * vet_X[7] - (vet_X[3]**2) * (vet_X[5]**2) + 4 * vet_X[0] * vet_X[8] * (vet_X[3]**2) + 4 * vet_X[4] * (vet_X[5]**2) + 4 * vet_X[0] * vet_X[4] * (vet_X[6]**2) + 4 * vet_X[0] * (vet_X[7]**2) - 16 * vet_X[0] * vet_X[4] * vet_X[8] - 4 * vet_X[0] * vet_X[3] * vet_X[6] * vet_X[7]
divs = 2 * abs(vet_X[4])**3 * (vet_X[4] * (vet_X[1]**2) - vet_X[1] * vet_X[2] * vet_X[3] + (vet_X[2]**2) + vet_X[0] * (vet_X[3]**2) - 4 * vet_X[0] * vet_X[4])

sx = -(vet_X[4]**3) * (psi8 * (-vet_X[3]**2 + 4 * vet_X[4]))**0.5 / (divs)
sy = -(vet_X[4]**3) * (psi8 * (-vet_X[2]**2 + 4 * vet_X[0] * vet_X[4]))**0.5 / (divs)
sz = -(vet_X[4]**3) * (psi8 * (-vet_X[1]**2 + 4 * vet_X[0]))**0.5 / (divs)

rho = (2 * vet_X[1] * vet_X[4] - vet_X[2] * vet_X[3]) / (2 * vet_X[4]**2 * (-(vet_X[4] * vet_X[1]**2 - vet_X[1] * vet_X[2] * vet_X[3] + vet_X[2]**2 + vet_X[0] * vet_X[3]**2 - 4 * vet_X[0] * vet_X[4]) / (vet_X[4]**3))**0.5)
rho = -np.arctan(rho)
lambida = -np.arctan((vet_X[3] / vet_X[4]) * (-(vet_X[4]**2 * (vet_X[4] * vet_X[1]**2 - vet_X[1] * vet_X[2] * vet_X[3] + vet_X[2]**2 + vet_X[0]*vet_X[3]**2 - 4 * vet_X[0] * vet_X[4]) / (2 * vet_X[1]**2 * vet_X[3]**2 * vet_X[4] - 4 * vet_X[1]**2 * vet_X[4]**2 - vet_X[1] * vet_X[2] * vet_X[3]**3 + vet_X[2]**2 * vet_X[3]**2 + vet_X[0] * vet_X[3]**4 - 8*vet_X[0]*vet_X[3]**2 * vet_X[4] + 16*vet_X[0] * vet_X[5]**2)))**0.5)

n1 = -vet_X[1]**2 * vet_X[7]**2 + 4 * vet_X[1]**2 * vet_X[4] * vet_X[8] - 4 * vet_X[1] * vet_X[2] * vet_X[3] * vet_X[8] + 2 * vet_X[1] * vet_X[2] * vet_X[6] * vet_X[7] + 2 * vet_X[1] * vet_X[3] * vet_X[5] * vet_X[7] - 4 * vet_X[1] * vet_X[4] * vet_X[5] * vet_X[6] - vet_X[2]**2 * vet_X[6]**2 + 2 * vet_X[2] * vet_X[3] * vet_X[5] * vet_X[6] + 4 * vet_X[2]**2 * vet_X[8] - 4 * vet_X[2] * vet_X[5] * vet_X[7] - vet_X[3]**2 * vet_X[5]**2 + 4 * vet_X[1] * vet_X[3]**2 * vet_X[8] - 4 * vet_X[0] * vet_X[3] * vet_X[6] * vet_X[7] + 4 * vet_X[4] * vet_X[5]**2 + 4 * vet_X[0] * vet_X[4] * vet_X[6]**2 + 4 * vet_X[0] * vet_X[7]**2 - 16 * vet_X[0] * vet_X[4] * vet_X[8]
n2 = vet_X[1]**2 * vet_X[4] - vet_X[1] * vet_X[2] * vet_X[3] + vet_X[2]**2 + vet_X[0] * vet_X[3]**2 - 4 * vet_X[0] * vet_X[4]
n3 = 2 * vet_X[1]**2 * vet_X[3]**2 * vet_X[4] - 4 * vet_X[1]**2 * vet_X[4]**2 - vet_X[1] * vet_X[2] * vet_X[3]**3 + vet_X[2]**2 * vet_X[3]**2 + vet_X[0] * vet_X[3]**2 - 8 * vet_X[0] * vet_X[3]**2 * vet_X[4] + 16 * vet_X[0] * vet_X[4]**2
n4 = 4 * vet_X[4] - vet_X[3]**2
n5 = 4 * vet_X[0] * vet_X[4] - vet_X[2]**2
n6 = 4 * vet_X[0] - vet_X[1]**2

phi = -np.arctan((abs(vet_X[4]) * (n1 * n5)**0.5 * (2 * vet_X[2] - vet_X[1] * vet_X[3]) * ((vet_X[4] * n4 * n6) / n3)**0.5) / (vet_X[4]**2 * (-n2 / vet_X[4])**0.5 * (n1 * n6)**0.5 * (-(n2 * n4) / n3)**0.5 * (-(n4 * n5) / (vet_X[4] * n2))**0.5))

p = np.array([sx, sy, sz, bx, by, bz, rho, phi, lambida])

print("Os fatores de escala são:\n")
print("%.4f" % p[0], "Para sx")
print("%.4f" % p[1], "Para sy")
print("%.4f" % p[2], "Para sz\n")

print("Os offsets são:\n")
print("%.4f" % p[3], "Para x")
print("%.4f" % p[4], "Para y")
print("%.4f" % p[5], "Para z\n")

print("Os ângulos são:\n")
print("%.4f" % p[6], "Para rho")
print("%.4f" % p[7], "Para phi")
print("%.4f" % p[8], "Para lambda")

mx_rest = np.zeros_like(mx)
my_rest = np.zeros_like(mx)
mz_rest = np.zeros_like(mx)

for i in range(len(mx)):
    mx_rest[i] = (mx[i] - p[3])/p[0]
    my_rest[i] = ((my[i] - p[4])/p[1] - mx[i]*np.sin(p[6]))/np.cos(p[6])
    mz_rest[i] = ((mz[i] - p[5])/p[2] - mx[i]*np.cos(p[7])*np.sin(p[7]) - my[i]*np.sin(p[8]))/(np.cos(p[7]*np.cos(p[8])))


phi, theta = np.mgrid[0.0:2.0*np.pi:100j, 0.0:np.pi:50j]
x_sphere = np.sin(theta) * np.cos(phi)
y_sphere = np.sin(theta) * np.sin(phi)
z_sphere = np.cos(theta)


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