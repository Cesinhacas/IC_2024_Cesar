import numpy as np
import random
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def ETS_func(mx, my , mz):
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
    lambida = -np.arctan((vet_X[3] / vet_X[4]) * (-(vet_X[4]**2 * (vet_X[4] * vet_X[1]**2 - vet_X[1] * vet_X[2] * vet_X[3] + vet_X[2]**2 - 4 * vet_X[0] * vet_X[4]) / (2 * vet_X[1]**2 * vet_X[3]**2 * vet_X[4] - 4 * vet_X[1]**2 * vet_X[4]**2 - 4 * vet_X[1]**2 * vet_X[4]**2 - vet_X[1] * vet_X[2] * vet_X[3]**3 + vet_X[0] * vet_X[3]**4 - 8 * vet_X[0] * vet_X[3]**2 * vet_X[4] + 16 * vet_X[0] * vet_X[4]**2)))**0.5)

    n1 = -vet_X[1]**2 * vet_X[7]**2 + 4 * vet_X[1]**2 * vet_X[4] * vet_X[8] - 4 * vet_X[1] * vet_X[2] * vet_X[3] * vet_X[8] + 2 * vet_X[1] * vet_X[2] * vet_X[6] * vet_X[7] + 2 * vet_X[1] * vet_X[3] * vet_X[5] * vet_X[7] - 4 * vet_X[1] * vet_X[4] * vet_X[5] * vet_X[6] - vet_X[2]**2 * vet_X[6]**2 + 2 * vet_X[2] * vet_X[3] * vet_X[5] * vet_X[6] + 4 * vet_X[2]**2 * vet_X[8] - 4 * vet_X[2] * vet_X[5] * vet_X[7] - vet_X[3]**2 * vet_X[5]**2 + 4 * vet_X[1] * vet_X[3]**2 * vet_X[8] - 4 * vet_X[0] * vet_X[3] * vet_X[6] * vet_X[7] + 4 * vet_X[4] * vet_X[5]**2 + 4 * vet_X[0] * vet_X[4] * vet_X[6]**2 + 4 * vet_X[0] * vet_X[7]**2 - 16 * vet_X[0] * vet_X[4] * vet_X[8]
    n2 = vet_X[1]**2 * vet_X[4] - vet_X[1] * vet_X[2] * vet_X[3] + vet_X[2]**2 + vet_X[0] * vet_X[3]**2 - 4 * vet_X[0] * vet_X[4]
    n3 = 2 * vet_X[1]**2 * vet_X[3]**2 * vet_X[4] - 4 * vet_X[1]**2 * vet_X[4]**2 - vet_X[1] * vet_X[2] * vet_X[3]**3 + vet_X[2]**2 * vet_X[3]**2 + vet_X[0] * vet_X[3]**2 - 8 * vet_X[0] * vet_X[3]**2 * vet_X[4] + 16 * vet_X[0] * vet_X[4]**2
    n4 = 4 * vet_X[4] - vet_X[3]**2
    n5 = 4 * vet_X[0] * vet_X[4] - vet_X[2]**2
    n6 = 4 * vet_X[0] - vet_X[1]**2

    phi = -np.arctan((abs(vet_X[4]) * (n1 * n5)**0.5 * (2 * vet_X[2] - vet_X[1] * vet_X[3]) * ((vet_X[4] * n4 * n6) / n3)**0.5) / (vet_X[4]**2 * (-n2 / vet_X[4])**0.5 * (n1 * n6)**0.5 * (-(n2 * n4) / n3)**0.5 * (-(n4 * n5) / (vet_X[4] * n2))**0.5))

    p = np.array([sx, sy, sz, bx, by, bz, rho, phi, lambida]).transpose()

    return p

def NLLS_func(mx, my, mz):
    import numpy as np

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


    #P = e_std*np.linalg.inv(H.transpose()@H)
    return p0


random.seed()
phi_sphere = [0]
theta_sphere = [0]

for i in range(0, 180, 5):
    for j in range(6,354,12):
        phi_sphere.append(j)
        theta_sphere.append(i)


x_sphere = np.sin(theta_sphere) * np.cos(phi_sphere)
y_sphere = np.sin(theta_sphere) * np.sin(phi_sphere)
z_sphere = np.cos(theta_sphere)
error_vet_ETS = []
error_vet_NLLS = []

for i in range(0,1000):
    e = [0, 0, 0, 0, 0, 0, 0, 0, 0]
    e[0] = (random.random()*0.4) + 0.8
    e[1] = (random.random()*0.4) + 0.8
    e[2] = (random.random()*0.4) + 0.8

    e[3] = (random.random()*0.4) - 0.2
    e[4] = (random.random()*0.4) - 0.2
    e[5] = (random.random()*0.4) - 0.2
    
    e[6] = ((random.random()*6) - 3) * (np.pi/180)
    e[7] = ((random.random()*6) - 3) * (np.pi/180)
    e[8] = ((random.random()*6) - 3) * (np.pi/180)

    dados_corrompidos = np.array([x_sphere, y_sphere, z_sphere]).transpose()
    offset = (np.array([e[3], e[4], e[5]])).transpose()
    scale =np.array([[e[0], 0, 0], [0, e[1], 0], [0, 0, e[2]]])
    T = np.array([[1, 0, 0], [np.sin(e[6]), np.cos(e[6]), 0], [np.sin(e[7])*np.cos(e[8]), np.sin(e[8]), np.cos(e[7])*np.cos(e[8])]])

    
    for j in range(len(x_sphere)):
        noise = 0.006*(np.random.rand(1,3))
        dados_corrompidos[j] = scale @ T @ np.array([dados_corrompidos[j][0], dados_corrompidos[j][1], dados_corrompidos[j][2]]).transpose() + offset + noise

    dados_corrompidos = dados_corrompidos.transpose()

    mx = dados_corrompidos[0]
    my = dados_corrompidos[1]
    mz = dados_corrompidos[2]

    p = ETS_func(mx, my, mz)
    p0 = NLLS_func(mx, my, mz)

    error_vet_ETS.append(e-p)
    error_vet_NLLS.append(e-p0)

error_vet_NLLS = np.array(error_vet_NLLS).transpose()
error_vet_ETS = np.array(error_vet_ETS).transpose()


plt.plot(error_vet_NLLS[0])
plt.ylabel('Erro escala x')
plt.show()
plt.plot(error_vet_NLLS[1])
plt.ylabel('Erro escala y')
plt.show() 
plt.plot(error_vet_NLLS[2])
plt.ylabel('Erro escala z')
plt.show() 
plt.plot(error_vet_NLLS[3])
plt.ylabel('Erro offset em x')
plt.show() 
plt.plot(error_vet_NLLS[4])
plt.ylabel('Erro offset em y')
plt.show() 
plt.plot(error_vet_NLLS[5])
plt.ylabel('Erro offset em z')
plt.show() 
plt.plot(error_vet_NLLS[6])
plt.ylabel('Erro ângulo rho')
plt.show() 
plt.plot(error_vet_NLLS[7])
plt.ylabel('Erro ângulo phi')
plt.show() 
plt.plot(error_vet_NLLS[8])
plt.ylabel('Erro ângulo lambda')
plt.show()

plt.plot(error_vet_ETS[0])
plt.ylabel('Erro escala x')
plt.show()
plt.plot(error_vet_ETS[1])
plt.ylabel('Erro escala y')
plt.show() 
plt.plot(error_vet_ETS[2])
plt.ylabel('Erro escala z')
plt.show() 
plt.plot(error_vet_ETS[3])
plt.ylabel('Erro offset em x')
plt.show() 
plt.plot(error_vet_ETS[4])
plt.ylabel('Erro offset em y')
plt.show() 
plt.plot(error_vet_ETS[5])
plt.ylabel('Erro offset em z')
plt.show() 
plt.plot(error_vet_ETS[6])
plt.ylabel('Erro ângulo rho')
plt.show() 
plt.plot(error_vet_ETS[7])
plt.ylabel('Erro ângulo phi')
plt.show() 
plt.plot(error_vet_ETS[8])
plt.ylabel('Erro ângulo lambda')
plt.show()