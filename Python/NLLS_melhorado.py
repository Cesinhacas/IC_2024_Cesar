import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


dados = pd.read_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Corrompido.csv', header=None) #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/dados/Dados_Corrompido.csv
mx = dados.iloc[0].values
my = dados.iloc[1].values
mz = dados.iloc[2].values
sf = 1


passo = 0
loop = 1
p0 = [1, 1, 1, 0, 0, 0, 0, 0, 0]

Be = np.ones_like(mx)*sf
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

    sin_rho = np.sin(rho)
    cos_rho = np.cos(rho)
    sin_phi = np.sin(phi)
    cos_phi = np.cos(phi)
    sin_lambida = np.sin(lambida)
    cos_lambida = np.cos(lambida)
    
    f = (((mx-bx)**2)/(sx)**2) + (((sx*(my-by) - sy*sin_rho*(mx-bx))**2)/((sx*sy*cos_rho)**2)) + (((sx*sy*cos_rho*(mz-bz) - sx*sz*sin_lambida*(my-by) + sy*sz*(sin_lambida*sin_rho - cos_rho*sin_phi*cos_lambida)*(mx-bx))**2)/((sx*sy*sz*cos_rho*cos_phi*cos_lambida)**2))
    
    
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


    h1 = (2*(sx*(by - my) - sy*sin_rho*(bx - mx))*(by - my))/(sx**2*sy**2*cos_rho**2) - (2*(sx*(by - my) - sy*sin_rho*(bx - mx))**2)/(sx**3*sy**2*cos_rho**2) - (2*(bx - mx)**2)/sx**3 - (2*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my))**2)/(sx**3*sy**2*sz**2*cos_lambida**2*cos_phi**2*cos_rho**2) + (2*(sy*cos_rho*(bz - mz) - sz*sin_lambida*(by - my))*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx**2*sy**2*sz**2*cos_lambida**2*cos_phi**2*cos_rho**2)

    h2 = -(2*(by - my)*(by*sx*sz*sin_lambida**2 - my*sx*sz*sin_lambida**2 + by*sx*sz*cos_lambida**2*cos_phi**2 - my*sx*sz*cos_lambida**2*cos_phi**2 - bz*sx*sy*cos_rho*sin_lambida + mz*sx*sy*cos_rho*sin_lambida - bx*sy*sz*sin_lambida**2*sin_rho + mx*sy*sz*sin_lambida**2*sin_rho - bx*sy*sz*cos_lambida**2*cos_phi**2*sin_rho + mx*sy*sz*cos_lambida**2*cos_phi**2*sin_rho + bx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi - mx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi))/(sx*sy**3*sz*cos_lambida**2*cos_phi**2*cos_rho**2)

    h3 = -(2*(bz - mz)*(bz*sx*sy*cos_rho - by*sx*sz*sin_lambida - mz*sx*sy*cos_rho + my*sx*sz*sin_lambida + bx*sy*sz*sin_lambida*sin_rho - mx*sy*sz*sin_lambida*sin_rho - bx*sy*sz*cos_lambida*cos_rho*sin_phi + mx*sy*sz*cos_lambida*cos_rho*sin_phi))/(sx*sy*sz**3*cos_lambida**2*cos_phi**2*cos_rho)

    h4 = (2*bx - 2*mx)/sx**2 - (2*sin_rho*(sx*(by - my) - sy*sin_rho*(bx - mx)))/(sx**2*sy*cos_rho**2) + (2*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx**2*sy*sz*cos_lambida**2*cos_phi**2*cos_rho**2)

    h5 = (2*(sx*(by - my) - sy*sin_rho*(bx - mx)))/(sx*sy**2*cos_rho**2) - (2*sin_lambida*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx*sy**2*sz*cos_lambida**2*cos_phi**2*cos_rho**2)

    h6 = (2*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx*sy*sz**2*cos_lambida**2*cos_phi**2*cos_rho)

    h7 = -(2*(bx*sy - mx*sy - by*sx*sin_rho + my*sx*sin_rho)*(by*sx*sz*sin_lambida**2 - my*sx*sz*sin_lambida**2 + by*sx*sz*cos_lambida**2*cos_phi**2 - my*sx*sz*cos_lambida**2*cos_phi**2 - bz*sx*sy*cos_rho*sin_lambida + mz*sx*sy*cos_rho*sin_lambida - bx*sy*sz*sin_lambida**2*sin_rho + mx*sy*sz*sin_lambida**2*sin_rho - bx*sy*sz*cos_lambida**2*cos_phi**2*sin_rho + mx*sy*sz*cos_lambida**2*cos_phi**2*sin_rho + bx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi - mx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi))/(sx**2*sy**2*sz*cos_lambida**2*cos_phi**2*cos_rho**3)

    h8 = (2*sin_phi*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my))**2)/(sx**2*sy**2*sz**2*cos_lambida**2*cos_phi**3*cos_rho**2) - (2*(bx - mx)*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx**2*sy*sz*cos_lambida*cos_phi*cos_rho)

    h9 = (2*sin_lambida*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my))**2)/(sx**2*sy**2*sz**2*cos_lambida**3*cos_phi**2*cos_rho**2) + (2*(sy*sz*(cos_lambida*sin_rho + cos_rho*sin_lambida*sin_phi)*(bx - mx) - sx*sz*cos_lambida*(by - my))*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx**2*sy**2*sz**2*cos_lambida**2*cos_phi**2*cos_rho**2)

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
print("Os offsets são:\n")
print(p0[3], "Para bx")
print(p0[4], "Para by")
print(p0[5], "Para bz\n")
print("Os ângulos são:\n")
print(p0[6], "Para rho")
print(p0[7], "Para phi")
print(p0[8], "Para lambida")

mx_rest = np.zeros_like(mx)
my_rest = np.zeros_like(mx)
mz_rest = np.zeros_like(mx)

for i in range(len(mx)):
    mx_rest[i] = (mx[i] - p0[3])/p0[0]
    my_rest[i] = ((my[i] - p0[4])/p0[1] - mx[i]*np.sin(p0[6]))/np.cos(p0[6])
    mz_rest[i] = ((mz[i] - p0[5])/p0[2] - mx[i]*np.cos(p0[7])*np.sin(p0[7]) - my[i]*np.sin(p0[8]))/(np.cos(p0[7]*np.cos(p0[8])))

calib_param = pd.DataFrame(p0)
calib_param.to_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Calib_param_NLLS.csv', header=False, index=False)

dados_rest = np.array([mx_rest, my_rest, mz_rest])
dados_rest = pd.DataFrame(dados_rest)
dados_rest.to_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_rest_NLLS.csv', header=False)


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