import numpy as np
import pandas as pd

dados = pd.read_excel('C:/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/Dados/Dados_Corrompidos.xlsx')
mx = dados.iloc[0].values
my = dados.iloc[1].values
mz = dados.iloc[2].values

mxs = mx.copy()
mys = my.copy()
mzs = mz.copy()

vet = mx.copy()
mxy = mx.copy()
mxz = mx.copy()
myz = my.copy()

tam = range(len(my))


for i, value in enumerate(my):
    mys[i] = -(value**2)
    

for i, value in enumerate(mx):
    mxs[i] = value**2


for i in tam:
    mxy[i] = mx[i]*my[i]

    mxz[i] = mx[i]*mz[i]

    myz[i] = my[i]*mz[i]

    vet[i] = 1

for i, value in enumerate(mz):
    mzs[i] = value**2

mat_H_t = np.array([mxs, mxy, mxz, myz, mzs, mx, my, mz, vet])
mat_H = mat_H_t.transpose()

# Pseudo-inversa
vet_X = np.linalg.pinv(mat_H)
vet_X = vet_X @ mys

# Cálculo dos offsets
psi7 = 2*(vet_X[4]*vet_X[1]**2 - vet_X[1]*vet_X[2]*vet_X[3] + vet_X[2]**2 + vet_X[0]*vet_X[3]**2 - 4*vet_X[0]*vet_X[4])

bx = -(vet_X[3]**2*vet_X[5] + 2*vet_X[2]*vet_X[7] - 4*vet_X[4]*vet_X[5] - vet_X[1]*vet_X[3]*vet_X[7] + 2*vet_X[1]*vet_X[4]*vet_X[6] - vet_X[2]*vet_X[3]*vet_X[6])/psi7
by = -(vet_X[2]**2*vet_X[6] + 2*vet_X[0]*vet_X[3]*vet_X[7] - 4*vet_X[0]*vet_X[4]*vet_X[6] - vet_X[1]*vet_X[2]*vet_X[7] + 2*vet_X[1]*vet_X[4]*vet_X[5] - vet_X[2]*vet_X[3]*vet_X[5])/psi7
bz = -(vet_X[1]**2*vet_X[7] - 4*vet_X[0]*vet_X[7] + 2*vet_X[2]*vet_X[5] + 2*vet_X[0]*vet_X[3]*vet_X[6] - vet_X[1]*vet_X[2]*vet_X[6] - vet_X[1]*vet_X[3]*vet_X[5])/psi7

psi8 = -(vet_X[1]**2)*(vet_X[7]**2) + 4*vet_X[4]*vet_X[8]*(vet_X[1]**2) - 4*vet_X[8]*vet_X[1]*vet_X[2]*vet_X[3] + 2*vet_X[1]*vet_X[2]*vet_X[6]*vet_X[7] + 2*vet_X[1]*vet_X[3]*vet_X[5]*vet_X[7] - 4*vet_X[4]*vet_X[1]*vet_X[5]*vet_X[6] - (vet_X[2]**2)*(vet_X[6]**2) + 4*vet_X[8]*(vet_X[2]**2) + 2*vet_X[2]*vet_X[3]*vet_X[5]*vet_X[6] - 4*vet_X[2]*vet_X[5]*vet_X[7] - (vet_X[3]**2)*(vet_X[5]**2) + 4*vet_X[0]*vet_X[8]*(vet_X[3]**2) + 4*vet_X[4]*(vet_X[5]**2) + 4*vet_X[0]*vet_X[4]*(vet_X[6]**2) + 4*vet_X[0]*(vet_X[7]**2) - 16*vet_X[0]*vet_X[4]*vet_X[8] - 4*vet_X[0]*vet_X[3]*vet_X[6]*vet_X[7]
divs = 2 * abs(vet_X[4])**3 * (vet_X[4]*(vet_X[1]**2) - vet_X[1]*vet_X[2]*vet_X[3] + (vet_X[2]**2) + vet_X[0]*(vet_X[3]**2) - 4*vet_X[0]*vet_X[4])

sx = -(vet_X[4]**3) * ( psi8*(-vet_X[3]**2 + 4*vet_X[4]))**0.5/(divs)
sy = -(vet_X[4]**3) * (psi8*(-vet_X[2]**2 + 4*vet_X[0]*vet_X[4]))**0.5/(divs)
sz = -(vet_X[4]**3) * (psi8*(-vet_X[1]**2 + 4*vet_X[0]))**0.5/(divs)

rho = (2*vet_X[1]*vet_X[4] - vet_X[2]*vet_X[3])/(2*vet_X[4]**2*(-(vet_X[4]*vet_X[1]**2 - vet_X[1]*vet_X[2]*vet_X[3] + vet_X[2]**2 + vet_X[0]*vet_X[3]**2 - 4*vet_X[0]*vet_X[4])/(vet_X[4]**3))**0.5)
rho = -np.arctan(rho)
lambida = -np.arctan((vet_X[3]/vet_X[4]) * (-(vet_X[4]**2*(vet_X[4]*vet_X[1]**2 - vet_X[1]*vet_X[2]*vet_X[3] + vet_X[2]**2 - 4*vet_X[0]*vet_X[4])/(2*vet_X[1]**2*vet_X[3]**2*vet_X[4] - 4*vet_X[1]**2*vet_X[4]**2 - 4*vet_X[1]**2*vet_X[4]**2 - vet_X[1]*vet_X[2]*vet_X[3]**3 + vet_X[0]*vet_X[3]**4 - 8*vet_X[0]*vet_X[3]**2*vet_X[4] + 16*vet_X[0]*vet_X[4]**2)))**0.5)

n1 = -vet_X[1]**2*vet_X[7]**2 + 4*vet_X[1]**2*vet_X[4]*vet_X[8] - 4*vet_X[1]*vet_X[2]*vet_X[3]*vet_X[8] + 2*vet_X[1]*vet_X[2]*vet_X[6]*vet_X[7] + 2*vet_X[1]*vet_X[3]*vet_X[5]*vet_X[7] - 4*vet_X[1]*vet_X[4]*vet_X[5]*vet_X[6] - vet_X[2]**2*vet_X[6]**2 + 2*vet_X[2]*vet_X[3]*vet_X[5]*vet_X[6] + 4*vet_X[2]**2*vet_X[8] - 4*vet_X[2]*vet_X[5]*vet_X[7] - vet_X[3]**2*vet_X[5]**2 + 4*vet_X[1]*vet_X[3]**2*vet_X[8] - 4*vet_X[0]*vet_X[3]*vet_X[6]*vet_X[7] + 4*vet_X[4]*vet_X[5]**2 + 4*vet_X[0]*vet_X[4]*vet_X[6]**2 + 4*vet_X[0]*vet_X[7]**2 - 16*vet_X[0]*vet_X[4]*vet_X[8]
n2 = vet_X[1]**2*vet_X[4] - vet_X[1]*vet_X[2]*vet_X[3] + vet_X[2]**2 + vet_X[0]*vet_X[3]**2 - 4*vet_X[0]*vet_X[4]
n3 = 2*vet_X[1]**2*vet_X[3]**2*vet_X[4] - 4*vet_X[1]**2*vet_X[4]**2 - vet_X[1]*vet_X[2]*vet_X[3]**3 + vet_X[2]**2*vet_X[3]**2 + vet_X[0]*vet_X[3]**2 - 8*vet_X[0]*vet_X[3]**2*vet_X[4] + 16*vet_X[0]*vet_X[4]**2
n4 = 4*vet_X[4] - vet_X[3]**2
n5 = 4*vet_X[0]*vet_X[4] - vet_X[2]**2
n6 = 4*vet_X[0] - vet_X[1]**2

phi = -np.arctan((abs(vet_X[4])*(n1*n5)**0.5*(2*vet_X[2] - vet_X[1]*vet_X[3])*((vet_X[4]*n4*n6)/n3)**0.5)/(vet_X[4]**2 * (-n2/vet_X[4])**0.5 * (n1*n6)**0.5 * (-(n2*n4)/n3)**0.5*(-(n4*n5)/(vet_X[4]*n2))**0.5))

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