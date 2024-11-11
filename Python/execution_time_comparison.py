import numpy as np
import random
import pandas as pd
import time

def ETS_func(mx, my , mz):
    time_start_ETS = time.perf_counter_ns()
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
    lambida = -np.arctan((vet_X[3]/vet_X[4]) * (-(vet_X[4]**2*(vet_X[4]*vet_X[1]**2 - vet_X[1]*vet_X[2]*vet_X[3] + vet_X[2]**2 + vet_X[0]*vet_X[3]**2 - 4*vet_X[0]*vet_X[4])/(2 * vet_X[1]**2 * vet_X[3]**2 * vet_X[4] - 4 * vet_X[1]**2 * vet_X[4]**2 - vet_X[1] * vet_X[2] * vet_X[3]**3 + vet_X[2]**2 * vet_X[3]**2 + vet_X[0] * vet_X[3]**4 - 8*vet_X[0]*vet_X[3]**2 * vet_X[4] + 16*vet_X[0] * vet_X[5]**2)))**0.5)

    n1 = -vet_X[1]**2 * vet_X[7]**2 + 4 * vet_X[1]**2 * vet_X[4] * vet_X[8] - 4 * vet_X[1] * vet_X[2] * vet_X[3] * vet_X[8] + 2 * vet_X[1] * vet_X[2] * vet_X[6] * vet_X[7] + 2 * vet_X[1] * vet_X[3] * vet_X[5] * vet_X[7] - 4 * vet_X[1] * vet_X[4] * vet_X[5] * vet_X[6] - vet_X[2]**2 * vet_X[6]**2 + 2 * vet_X[2] * vet_X[3] * vet_X[5] * vet_X[6] + 4 * vet_X[2]**2 * vet_X[8] - 4 * vet_X[2] * vet_X[5] * vet_X[7] - vet_X[3]**2 * vet_X[5]**2 + 4 * vet_X[1] * vet_X[3]**2 * vet_X[8] - 4 * vet_X[0] * vet_X[3] * vet_X[6] * vet_X[7] + 4 * vet_X[4] * vet_X[5]**2 + 4 * vet_X[0] * vet_X[4] * vet_X[6]**2 + 4 * vet_X[0] * vet_X[7]**2 - 16 * vet_X[0] * vet_X[4] * vet_X[8]
    n2 = vet_X[1]**2 * vet_X[4] - vet_X[1] * vet_X[2] * vet_X[3] + vet_X[2]**2 + vet_X[0] * vet_X[3]**2 - 4 * vet_X[0] * vet_X[4]
    n3 = 2 * vet_X[1]**2 * vet_X[3]**2 * vet_X[4] - 4 * vet_X[1]**2 * vet_X[4]**2 - vet_X[1] * vet_X[2] * vet_X[3]**3 + vet_X[2]**2 * vet_X[3]**2 + vet_X[0] * vet_X[3]**2 - 8 * vet_X[0] * vet_X[3]**2 * vet_X[4] + 16 * vet_X[0] * vet_X[4]**2
    n4 = 4 * vet_X[4] - vet_X[3]**2
    n5 = 4 * vet_X[0] * vet_X[4] - vet_X[2]**2
    n6 = 4 * vet_X[0] - vet_X[1]**2

    phi = -np.arctan((abs(vet_X[4]) * (n1 * n5)**0.5 * (2 * vet_X[2] - vet_X[1] * vet_X[3]) * ((vet_X[4] * n4 * n6) / n3)**0.5) / (vet_X[4]**2 * (-n2 / vet_X[4])**0.5 * (n1 * n6)**0.5 * (-(n2 * n4) / n3)**0.5 * (-(n4 * n5) / (vet_X[4] * n2))**0.5))

    p = np.array([sx, sy, sz, bx, by, bz, rho, phi, lambida]).transpose()
    time_end_ETS = time.perf_counter_ns()
    Time = time_end_ETS - time_start_ETS

    return p, Time

def NLLS_func(mx, my, mz):
    passo = 0
    loop = 1
    p0 = [1, 1, 1, 0, 0, 0, 0, 0, 0]
    Be = np.ones_like(mx)
    Be = list(map(lambda x: x**2, Be))
    e = Be
    error_vet = []

    time_start_NLLS = time.perf_counter_ns()
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
        
    
        #e_std = (2*J*(1/len(e)))**0.5
        
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

    time_end_NLLS = time.perf_counter_ns()
    Time = time_end_NLLS - time_start_NLLS
    #P = e_std*np.linalg.inv(H.transpose()@H)
    return p0, Time, passo

def TWOSTEP_func(mx, my, mz):
  
    B = np.vstack([mx, my, mz])

    # Parâmetros iniciais
    stop = 1e-24
    tam = B.shape[1]
    passo_max = 200
    Sigma_noise = (0.006**2)*np.ones((3, tam))
    H = np.ones(tam)

    time_start_TWOSTEP = time.perf_counter_ns()

    # Iniciando variáveis
    z_k = np.zeros(tam)
    mu_k = np.zeros(tam)
    sigma_k = np.zeros(tam)
    L_k = np.zeros((9, tam))
    sigma_bar = 0

    # Cálculo do erro, variância e média
    for i in range(tam):
        i_vec = B[:, i]
        z_k[i] = np.linalg.norm(i_vec)**2 - H[i]**2
        mu_k[i] = -(Sigma_noise[0, i] + Sigma_noise[1, i] + Sigma_noise[2, i])
        sigma_k[i] = 4 * i_vec.T @ np.diag(Sigma_noise[:, i]) @ i_vec + \
                        2 * np.sum(Sigma_noise[:, i]**2)
        sigma_bar += 1 / sigma_k[i]
        L_k[:, i] = np.hstack([
            2 * i_vec, 
            -B[0, i]**2, -B[1, i]**2, -B[2, i]**2, 
            -2 * B[0, i] * B[1, i], -2 * B[0, i] * B[2, i], 
            -2 * B[1, i] * B[2, i]
        ])
    sigma_bar = 1 / sigma_bar

    # Centralizando parâmetros
    z_bar = 0
    mu_bar = 0
    L_bar = np.zeros(9)

    for i in range(tam):
        z_bar += sigma_bar * (z_k[i] / sigma_k[i])
        mu_bar += sigma_bar * (mu_k[i] / sigma_k[i])
        L_bar += sigma_bar * L_k[:, i] / sigma_k[i]

    # Calculando valores tilde
    z_tilde = z_k - z_bar
    mu_tilde = mu_k - mu_bar
    L_tilde = L_k - L_bar[:, None]

    F_tt = np.zeros((9, 9))
    for i in range(tam):
        F_tt += np.outer(L_tilde[:, i], L_tilde[:, i]) / sigma_k[i]
    P_tt = np.linalg.inv(F_tt)

    # Inicializando theta
    theta = np.zeros(9)
    for i in range(tam):
        theta += ((z_tilde[i] - mu_tilde[i]) / sigma_k[i]) * L_tilde[:, i]
    theta = P_tt @ theta

    ABC = -((z_tilde - mu_tilde) / sigma_k) @ L_tilde.T
    passo = 0
    loop = True

    # Loop principal
    while loop:
        if passo != 0:
            theta = theta_np1

        c = theta[:3]
        E = np.array([
            [theta[3], theta[6], theta[7]],
            [theta[6], theta[4], theta[8]],
            [theta[7], theta[8], theta[5]]
        ])
        E_inv = np.linalg.inv(np.eye(3) + E)  # Inversa de (I + E)
        tmp = np.outer(E_inv @ c, E_inv @ c)  # Produto externo (resulta em matriz 3x3)


        dJdThetap_tilde = ABC + F_tt @ theta
        dbsqdtheta_p = np.hstack([
            2 * E_inv @ c, 
            -np.diag(tmp), 
            -2 * tmp[0, 1], -2 * tmp[0, 2], -2 * tmp[1, 2]
        ])

        dJdThetap_bar = (-1/sigma_bar) * (L_bar - dbsqdtheta_p) * (z_bar - mu_bar - (L_bar.T @ theta) + (c.T @ E_inv @ c)) 

        dJdTheta = dJdThetap_tilde + dJdThetap_bar

        F_tt_bar = np.outer(L_bar - dbsqdtheta_p, L_bar - dbsqdtheta_p) / sigma_bar

        theta_np1 = theta - np.linalg.inv(F_tt + F_tt_bar) @ dJdTheta

        TS_erro = (theta_np1 - theta).T @ (F_tt + F_tt_bar) @ (theta_np1 - theta)

        if passo > passo_max or TS_erro < stop:
            loop = False

        passo += 1

    # Decomposição em autovalores e autovetores
    U, S, Vh= np.linalg.svd(E)
    S = np.eye(3) + np.diag(S)
    W = -np.eye(3) + S**0.5

    D = U @ W @ Vh
    h = np.linalg.inv(np.eye(3) + D) @ c

    time_end_TWOSTEP = time.perf_counter_ns()
    Time = time_end_TWOSTEP - time_start_TWOSTEP

    return Time, h, D, passo 


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
num_exe = 5000
execution_time_ETS = 0
execution_time_NLLS = 0
execution_time_TWOSTEP  = 0
passos_TWOSTEP = 0
passos_NLLS = 0


for i in range(0,num_exe):
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

    p, tempo= ETS_func(mx, my, mz)
    execution_time_ETS += tempo
    
    p0, Time, passitos = NLLS_func(mx, my, mz)
    passos_NLLS += passitos
    execution_time_NLLS += Time

    tiempo, h, D, passo = TWOSTEP_func(mx, my, mz)
    passos_TWOSTEP += passo
    execution_time_TWOSTEP += tiempo


execution_time_ETS = (execution_time_ETS/num_exe)/1e6

execution_time_NLLS = (execution_time_NLLS/num_exe)/1e6
passos_NLLS = passos_NLLS/num_exe

execution_time_TWOSTEP = (execution_time_TWOSTEP/num_exe)/1e6
passos_TWOSTEP = passos_TWOSTEP/num_exe

ratio = execution_time_NLLS/execution_time_ETS
ratio2 = execution_time_TWOSTEP/execution_time_ETS

print("\n")
print("O tempo médio de execução do TWOSTEP foi:", execution_time_TWOSTEP, "ms")
print("O número médio de passos foi:\n", passos_TWOSTEP)
print("O tempo médio de execução do ETS foi:", execution_time_ETS, "ms\n")
print("O tempo médio de execução do NLLS foi:", execution_time_NLLS, "ms")
print("O número médio de passos foi:\n", passos_NLLS)
print("A relação entre a execução foi de:","%.2f" % ratio, "(tempo de execução do NLLS/tempo de execução do ETS)")
print("A relação entre a execução foi de:","%.2f" % ratio2, "(tempo de execução do TWOSTEP/tempo de execução do ETS)")