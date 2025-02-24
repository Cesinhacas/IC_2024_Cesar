import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

dados = pd.read_excel('C:/Users/LabT5/Onedrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Corrompidos.xlsx') #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompidos.xlsx
mx = dados.iloc[0].values
my = dados.iloc[1].values
mz = dados.iloc[2].values
sf = 0.5
tam = range(len(mx))

passo = 0
loop = 1
p0 = [1, 1, 1, 0, 0, 0, 0, 0, 0]
f = mx.copy()
h1 = mx.copy()
h2 = mx.copy()
h3 = mx.copy()
h4 = mx.copy()
h5 = mx.copy()
h6 = mx.copy()
h7 = mx.copy()
h8 = mx.copy()
h9 = mx.copy()
Be = np.ones(len(mx))*sf
Be = list(map(lambda x: x**2, Be))
e = Be
error_vet = mx.copy()


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
    for i in tam:
        f[i] = (((mx[i]-bx)**2)/(sx)**2) + (((sx*(my[i]-by) - sy*np.sin(rho)*(mx[i]-bx))**2)/((sx*sy*np.cos(rho))**2)) + (((sx*sy*np.cos(rho)*(mz[i]-bz) - sx*sz*np.sin(lambida)*(my[i]-by) + sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(rho)*np.sin(phi)*np.cos(lambida))*(mx[i]-bx))**2)/((sx*sy*sz*np.cos(rho)*np.cos(phi)*np.cos(lambida))**2))
    
    
    e = Be - f
    
    J = (e.transpose()@e)
    J = J*0.5
    
   
    e_std = (2*J*(1/len(e)))**0.5
    
    if passo < 3:
        error_vet[passo] = J
    else:
        error_vet[passo] = J
        delta_J = 100*np.abs(error_vet[passo]-error_vet[passo-1])/error_vet[passo]
        if delta_J < 0.1:
            loop = 0

    for i in tam:
        h1[i] = (2*(sx*(by - my[i]) - sy*np.sin(rho)*(bx - mx[i]))*(by - my[i]))/(sx**2*sy**2*np.cos(rho)**2) - (2*(sx*(by - my[i]) - sy*np.sin(rho)*(bx - mx[i]))**2)/(sx**3*sy**2*np.cos(rho)**2) - (2*(bx - mx[i])**2)/sx**3 - (2*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx[i]) + sx*sy*np.cos(rho)*(bz - mz[i]) - sx*sz*np.sin(lambida)*(by - my[i]))**2)/(sx**3*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2) + (2*(sy*np.cos(rho)*(bz - mz[i]) - sz*np.sin(lambida)*(by - my[i]))*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx[i]) + sx*sy*np.cos(rho)*(bz - mz[i]) - sx*sz*np.sin(lambida)*(by - my[i])))/(sx**2*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)
    
        h2[i] = -(2*(by - my[i])*(by*sx*sz*np.sin(lambida)**2 - my[i]*sx*sz*np.sin(lambida)**2 + by*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - my[i]*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - bz*sx*sy*np.cos(rho)*np.sin(lambida) + mz[i]*sx*sy*np.cos(rho)*np.sin(lambida) - bx*sy*sz*np.sin(lambida)**2*np.sin(rho) + mx[i]*sy*sz*np.sin(lambida)**2*np.sin(rho) - bx*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + mx[i]*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + bx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi) - mx[i]*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi)))/(sx*sy**3*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)
    
        h3[i] = -(2*(bz - mz[i])*(bz*sx*sy*np.cos(rho) - by*sx*sz*np.sin(lambida) - mz[i]*sx*sy*np.cos(rho) + my[i]*sx*sz*np.sin(lambida) + bx*sy*sz*np.sin(lambida)*np.sin(rho) - mx[i]*sy*sz*np.sin(lambida)*np.sin(rho) - bx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(phi) + mx[i]*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(phi)))/(sx*sy*sz**3*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho))
    
        h4[i] = (2*bx - 2*mx[i])/sx**2 - (2*np.sin(rho)*(sx*(by - my[i]) - sy*np.sin(rho)*(bx - mx[i])))/(sx**2*sy*np.cos(rho)**2) + (2*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx[i]) + sx*sy*np.cos(rho)*(bz - mz[i]) - sx*sz*np.sin(lambida)*(by - my[i])))/(sx**2*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)
    
        h5[i] = (2*(sx*(by - my[i]) - sy*np.sin(rho)*(bx - mx[i])))/(sx*sy**2*np.cos(rho)**2) - (2*np.sin(lambida)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx[i]) + sx*sy*np.cos(rho)*(bz - mz[i]) - sx*sz*np.sin(lambida)*(by - my[i])))/(sx*sy**2*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

        h6[i] = (2*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx[i]) + sx*sy*np.cos(rho)*(bz - mz[i]) - sx*sz*np.sin(lambida)*(by - my[i])))/(sx*sy*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho))

        h7[i] = -(2*(bx*sy - mx[i]*sy - by*sx*np.sin(rho) + my[i]*sx*np.sin(rho))*(by*sx*sz*np.sin(lambida)**2 - my[i]*sx*sz*np.sin(lambida)**2 + by*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - my[i]*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - bz*sx*sy*np.cos(rho)*np.sin(lambida) + mz[i]*sx*sy*np.cos(rho)*np.sin(lambida) - bx*sy*sz*np.sin(lambida)**2*np.sin(rho) + mx[i]*sy*sz*np.sin(lambida)**2*np.sin(rho) - bx*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + mx[i]*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + bx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi) - mx[i]*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi)))/(sx**2*sy**2*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**3)

        h8[i] = (2*np.sin(phi)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx[i]) + sx*sy*np.cos(rho)*(bz - mz[i]) - sx*sz*np.sin(lambida)*(by - my[i]))**2)/(sx**2*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**3*np.cos(rho)**2) - (2*(bx - mx[i])*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx[i]) + sx*sy*np.cos(rho)*(bz - mz[i]) - sx*sz*np.sin(lambida)*(by - my[i])))/(sx**2*sy*sz*np.cos(lambida)*np.cos(phi)*np.cos(rho))

        h9[i] = (2*np.sin(lambida)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx[i]) + sx*sy*np.cos(rho)*(bz - mz[i]) - sx*sz*np.sin(lambida)*(by - my[i]))**2)/(sx**2*sy**2*sz**2*np.cos(lambida)**3*np.cos(phi)**2*np.cos(rho)**2) + (2*(sy*sz*(np.cos(lambida)*np.sin(rho) + np.cos(rho)*np.sin(lambida)*np.sin(phi))*(bx - mx[i]) - sx*sz*np.cos(lambida)*(by - my[i]))*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx[i]) + sx*sy*np.cos(rho)*(bz - mz[i]) - sx*sz*np.sin(lambida)*(by - my[i])))/(sx**2*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

    H_t = np.array([h1, h2, h3, h4, h5, h6, h7, h8, h9])
    H = H_t.transpose()

    deltap = np.linalg.pinv(H)
    deltap = deltap @ e

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

print("\n")
print("Os fatores de escala são:\n")
print(p0[0], "Para sx")
print(p0[1], "Para sy")
print(p0[2], "Para sz\n")
print("Os offsets são:\n")
print(p0[3], "Para x")
print(p0[4], "Para y")
print(p0[5], "Para z\n")
print("Os ângulos são:\n")
print(p0[6], "Para rho")
print(p0[7], "Para phi")
print(p0[8], "Para lambda")

mx_rest = np.zeros_like(mx)
my_rest = np.zeros_like(mx)
mz_rest = np.zeros_like(mx)

for i in range(len(mx)):
    mx_rest[i] = (mx[i] - p0[3])/p0[0]
    my_rest[i] = ((my[i] - p0[4])/p0[1] - mx[i]*np.sin(p0[6]))/np.cos(p0[6])
    mz_rest[i] = ((mz[i] - p0[5])/p0[2] - mx[i]*np.cos(p0[7])*np.sin(p0[7]) - my[i]*np.sin(p0[8]))/(np.cos(p0[7]*np.cos(p0[8])))


phi, theta = np.mgrid[0.0:2.0*np.pi:100j, 0.0:np.pi:50j]
x_sphere = (np.sin(theta) * np.cos(phi))*sf
y_sphere = (np.sin(theta) * np.sin(phi))*sf
z_sphere = (np.cos(theta))*sf


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