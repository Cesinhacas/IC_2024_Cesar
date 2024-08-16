def ETS_func(mx, my , mz):
    import numpy as np
    import pandas as pd

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

    p = np.array([sx, sy, sz, bx, by, bz, rho, phi, lambida])

    return p