import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


dados = pd.read_excel('/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompidos.xlsx') #C:/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Corrompidos.xlsx
mx = dados.iloc[0].values
my = dados.iloc[1].values
mz = dados.iloc[2].values


passo = 0
loop = 1
p0 = [1, 1, 1, 0, 0, 0, 0, 0, 0]
Be = np.ones_like(mx)
Be = list(map(lambda x: x**2, Be))
e = Be
error_vet = []

while loop == 1:
    sx = p0[0]
    sy = p0[1]
    sz = p0[2]
    bx = p0[3]
    by = p0[4]
    bz = p0[5]
    rho = p0[6]
    phi = p0[7]
    lambida = p0[8]
    
    f = (((mx-bx)**2)/(sx)**2) + (((sx*(my-by) - sy*np.sin(rho)*(mx-bx))**2)/((sx*sy*np.cos(rho))**2)) + (((sx*sy*np.cos(rho)*(mz-bz) - sx*sz*np.sin(lambida)*(my-by) + sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(rho)*np.sin(phi)*np.cos(lambida))*(mx-bx))**2)/((sx*sy*sz*np.cos(rho)*np.cos(phi)*np.cos(lambida))**2))
    
    
    e = Be - f
    
    J = (e.transpose()@e)
    J = J*0.5
    
   
    e_std = (2*J*(1/len(e)))**0.5
    
    if passo < 3:
        error_vet.append(J)
    else:
        error_vet.append(J)
        delta_J = 100*np.abs(error_vet[passo]-error_vet[passo-1])/error_vet[passo]
        if delta_J < 0.1:
            loop = 0

    
    h1 = (2*(sx*(by - my) - sy*np.sin(rho)*(bx - mx))*(by - my))/(sx**2*sy**2*np.cos(rho)**2) - (2*(sx*(by - my) - sy*np.sin(rho)*(bx - mx))**2)/(sx**3*sy**2*np.cos(rho)**2) - (2*(bx - mx)**2)/sx**3 - (2*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my))**2)/(sx**3*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2) + (2*(sy*np.cos(rho)*(bz - mz) - sz*np.sin(lambida)*(by - my))*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx**2*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

    h2 = -(2*(by - my)*(by*sx*sz*np.sin(lambida)**2 - my*sx*sz*np.sin(lambida)**2 + by*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - my*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - bz*sx*sy*np.cos(rho)*np.sin(lambida) + mz*sx*sy*np.cos(rho)*np.sin(lambida) - bx*sy*sz*np.sin(lambida)**2*np.sin(rho) + mx*sy*sz*np.sin(lambida)**2*np.sin(rho) - bx*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + mx*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + bx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi) - mx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi)))/(sx*sy**3*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

    h3 = -(2*(bz - mz)*(bz*sx*sy*np.cos(rho) - by*sx*sz*np.sin(lambida) - mz*sx*sy*np.cos(rho) + my*sx*sz*np.sin(lambida) + bx*sy*sz*np.sin(lambida)*np.sin(rho) - mx*sy*sz*np.sin(lambida)*np.sin(rho) - bx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(phi) + mx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(phi)))/(sx*sy*sz**3*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho))

    h4 = (2*bx - 2*mx)/sx**2 - (2*np.sin(rho)*(sx*(by - my) - sy*np.sin(rho)*(bx - mx)))/(sx**2*sy*np.cos(rho)**2) + (2*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx**2*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

    h5 = (2*(sx*(by - my) - sy*np.sin(rho)*(bx - mx)))/(sx*sy**2*np.cos(rho)**2) - (2*np.sin(lambida)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx*sy**2*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

    h6 = (2*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx*sy*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho))

    h7 = -(2*(bx*sy - mx*sy - by*sx*np.sin(rho) + my*sx*np.sin(rho))*(by*sx*sz*np.sin(lambida)**2 - my*sx*sz*np.sin(lambida)**2 + by*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - my*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - bz*sx*sy*np.cos(rho)*np.sin(lambida) + mz*sx*sy*np.cos(rho)*np.sin(lambida) - bx*sy*sz*np.sin(lambida)**2*np.sin(rho) + mx*sy*sz*np.sin(lambida)**2*np.sin(rho) - bx*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + mx*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + bx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi) - mx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi)))/(sx**2*sy**2*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**3)

    h8 = (2*np.sin(phi)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my))**2)/(sx**2*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**3*np.cos(rho)**2) - (2*(bx - mx)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx**2*sy*sz*np.cos(lambida)*np.cos(phi)*np.cos(rho))

    h9 = (2*np.sin(lambida)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my))**2)/(sx**2*sy**2*sz**2*np.cos(lambida)**3*np.cos(phi)**2*np.cos(rho)**2) + (2*(sy*sz*(np.cos(lambida)*np.sin(rho) + np.cos(rho)*np.sin(lambida)*np.sin(phi))*(bx - mx) - sx*sz*np.cos(lambida)*(by - my))*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx**2*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

    H_t = np.array([h1, h2, h3, h4, h5, h6, h7, h8, h9])
    H = H_t.transpose()

    deltap = np.linalg.pinv(H) @ e

    p0 = p0 + deltap

    passo += 1

sx = p0[0]
sy = p0[1]
sz = p0[2]
bx = p0[3]
by = p0[4]
bz = p0[5]
rho = p0[6]
phi = p0[7]
lambida = p0[8]
P = e_std*np.linalg.inv(H.transpose()@H)

print("Os fatores de escala são:\n")
print(p0[0], "Para sx")
print(p0[1], "Para sy")
print(p0[2], "Para sz\n")
print("Os fatores de escala são:\n")
print(p0[0], "Para sx")
print(p0[1], "Para sy")
print(p0[2], "Para sz\n")
print("Os fatores de escala são:\n")
print(p0[0], "Para sx")
print(p0[1], "Para sy")
print(p0[2], "Para sz")

scale_i = np.linalg.inv([[p0[0], 0, 0], [0, p0[1], 0], [0, 0, p0[2]]])
T_inv = np.linalg.inv([[1, 0, 0], [np.sin(p0[6]), np.cos(p0[6]), 0], [np.sin(p0[7])*np.cos(p0[8]), np.sin(p0[8]), np.cos(p0[7])*np.cos(p0[8])]])
offset = [p0[3], p0[4], p0[5]]

dados_corrompidos = np.array([mx, my, mz]).transpose()

dados_rest = dados_corrompidos.copy()

for i in range(len(mx)):
    dados_rest[i] = scale_i @ T_inv @ dados_corrompidos[i] - offset

dados_rest = dados_rest.transpose()
mx_rest = dados_rest[:][0]
my_rest = dados_rest[:][1]
mz_rest = dados_rest[:][2]

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