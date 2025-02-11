import numpy as np
import random
import pandas as pd
import time

def ETS_func(mx, my , mz):
    time_start = time.perf_counter_ns()
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
    lambida = -np.arctan((vet_X[3] / vet_X[4]) * (-((vet_X[4]**2) * (vet_X[4] * (vet_X[1]**2) - vet_X[1] * vet_X[2] * vet_X[3] + (vet_X[2]**2) - 4 * vet_X[0] * vet_X[4]) / (2 * (vet_X[1]**2) * (vet_X[3]**2) * vet_X[4] - 4 * (vet_X[1]**2) * (vet_X[4]**2) - 4 * (vet_X[1]**2) * (vet_X[4]**2) - vet_X[1] * vet_X[2] * (vet_X[3]**3) + vet_X[0] * (vet_X[3]**4) - 8 * vet_X[0] * (vet_X[3]**2) * vet_X[4] + 16 * vet_X[0] * (vet_X[4]**2))))**0.5)

    n1 = -vet_X[1]**2 * vet_X[7]**2 + 4 * vet_X[1]**2 * vet_X[4] * vet_X[8] - 4 * vet_X[1] * vet_X[2] * vet_X[3] * vet_X[8] + 2 * vet_X[1] * vet_X[2] * vet_X[6] * vet_X[7] + 2 * vet_X[1] * vet_X[3] * vet_X[5] * vet_X[7] - 4 * vet_X[1] * vet_X[4] * vet_X[5] * vet_X[6] - vet_X[2]**2 * vet_X[6]**2 + 2 * vet_X[2] * vet_X[3] * vet_X[5] * vet_X[6] + 4 * vet_X[2]**2 * vet_X[8] - 4 * vet_X[2] * vet_X[5] * vet_X[7] - vet_X[3]**2 * vet_X[5]**2 + 4 * vet_X[1] * vet_X[3]**2 * vet_X[8] - 4 * vet_X[0] * vet_X[3] * vet_X[6] * vet_X[7] + 4 * vet_X[4] * vet_X[5]**2 + 4 * vet_X[0] * vet_X[4] * vet_X[6]**2 + 4 * vet_X[0] * vet_X[7]**2 - 16 * vet_X[0] * vet_X[4] * vet_X[8]
    n2 = vet_X[1]**2 * vet_X[4] - vet_X[1] * vet_X[2] * vet_X[3] + vet_X[2]**2 + vet_X[0] * vet_X[3]**2 - 4 * vet_X[0] * vet_X[4]
    n3 = 2 * vet_X[1]**2 * vet_X[3]**2 * vet_X[4] - 4 * vet_X[1]**2 * vet_X[4]**2 - vet_X[1] * vet_X[2] * vet_X[3]**3 + vet_X[2]**2 * vet_X[3]**2 + vet_X[0] * vet_X[3]**2 - 8 * vet_X[0] * vet_X[3]**2 * vet_X[4] + 16 * vet_X[0] * vet_X[4]**2
    n4 = 4 * vet_X[4] - vet_X[3]**2
    n5 = 4 * vet_X[0] * vet_X[4] - vet_X[2]**2
    n6 = 4 * vet_X[0] - vet_X[1]**2

    phi = -np.arctan((abs(vet_X[4]) * (n1 * n5)**0.5 * (2 * vet_X[2] - vet_X[1] * vet_X[3]) * ((vet_X[4] * n4 * n6) / n3)**0.5) / (vet_X[4]**2 * (-n2 / vet_X[4])**0.5 * (n1 * n6)**0.5 * (-(n2 * n4) / n3)**0.5 * (-(n4 * n5) / (vet_X[4] * n2))**0.5))

    p = np.array([sx, sy, sz, bx, by, bz, rho, phi, lambida]).transpose()

    time_end = time.perf_counter_ns()
    Time = time_end - time_start

    return p, Time

def NLLS_func(mx, my, mz):

    passo = 0
    loop = 1
    p0 = [1, 1, 1, 0, 0, 0, 0, 0, 0]
    Be = np.ones_like(mx)
    Be = list(map(lambda x: x**2, Be))
    e = Be
    error_vet = []

    time_start = time.perf_counter_ns()
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
        
    
        #e_std = (2*J*(1/len(e)))**0.5
        
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

    time_end = time.perf_counter_ns()
    Time = time_end - time_start

    #P = e_std*np.linalg.inv(H.transpose()@H)
    return p0, Time


phi_sphere = [0]
theta_sphere = [0]

for i in range(0, 180, 5):
    for j in range(6,354,12):
        phi_sphere.append(j)
        theta_sphere.append(i)


x_sphere = np.sin(theta_sphere) * np.cos(phi_sphere)
y_sphere = np.sin(theta_sphere) * np.sin(phi_sphere)
z_sphere = np.cos(theta_sphere)

param = pd.read_csv('c:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Dados/commum_param.csv', header=None) #/mnt/c/users/labt5/desktop/cesar/IC_2024_Cesar/commum_param.csv
param = param.to_numpy()

exe = 3000
tempo_exe_ETS = 0
tempo_exe_NLLS = 0
error_vet_ETS = np.zeros((exe, 9))
error_vet_NLLS = np.zeros((exe, 9))


for i in range(0,exe):
    e = [0, 0, 0, 0, 0, 0, 0, 0, 0]
    e[0] = param[0][i]
    e[1] = param[1][i]
    e[2] = param[2][i]

    e[3] = param[3][i]
    e[4] = param[4][i]
    e[5] = param[5][i]
    
    e[6] = param[6][i]
    e[7] = param[7][i]
    e[8] = param[8][i]

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

    p, Time_ETS = ETS_func(mx, my, mz)
    p0, Time_NLLS = NLLS_func(mx, my, mz)

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