import numpy as np

def TRIAD(v1, v2, w1, w2, sig1, sig2):
    v1 = np.array(v1, dtype=float)
    v2 = np.array(v2, dtype=float)
    w1 = np.array(w1, dtype=float)
    w2 = np.array(w2, dtype=float)

    v1_triad = v1 / np.linalg.norm(v1)
    w1_norm = np.linalg.norm(w1) 
    w1_triad = w1 / w1_norm

    r1 = v1_triad
    r2 = np.cross(v1_triad, v2)
    r2 = r2 / np.linalg.norm(r2)
    r3 = np.cross(r1, r2)
    
    mat_ref = np.array([r1, r2, r3]) 

    s1 = w1_triad
    s2 = np.cross(w1_triad, w2)
    s2 = s2 / np.linalg.norm(s2)
    s3 = np.cross(s1, s2)
    
    mat_obs = np.array([s1, s2, s3])

    dcm = mat_obs.T @ mat_ref

    trace = np.trace(dcm)
    q0 = 0.5 * np.sqrt(1 + trace)
    q1 = (dcm[1, 2] - dcm[2, 1]) / (4 * q0)
    q2 = (dcm[2, 0] - dcm[0, 2]) / (4 * q0)
    q3 = (dcm[0, 1] - dcm[1, 0]) / (4 * q0)

    quaternion = np.array([q0, q1, q2, q3])

    cross_w1_w2 = np.cross(w1, w2)
    norm_sq_cross = np.linalg.norm(cross_w1_w2)**2
    
    outer_sum = np.outer(w1, w2) + np.outer(w2, w1)
    
    outer_w1 = np.outer(w1, w1)
    
    dot_w1_w2 = np.dot(w1, w2)

    term1 = (sig1**2) * np.eye(3)
    
    coeff = 1.0 / norm_sq_cross
    
    term2 = (sig1**2) * dot_w1_w2 * outer_sum
    
    term3 = (sig2**2 - sig1**2) * outer_w1

    R = term1 + coeff * (term2 + term3)

    return quaternion, R

def propagador(gyro, Dt, PT_est, x_est, Q, i_in):
    i_out = i_in + 1

    q_est = x_est[0:4] 
    b_gyro = x_est[4:7]
    
    w_gyro = gyro - b_gyro
    Th = w_gyro * Dt 
    th_norm = np.linalg.norm(Th)
    
    # Matriz Omega 4x4
    omega4 = np.array([ [0, Th[2], -Th[1], Th[0]],
                        [-Th[2], 0, Th[0], Th[1]],
                        [Th[1], -Th[0], 0, Th[2]],
                        [-Th[0], -Th[1], -Th[2], 0] ])

    sin_term = np.sin(th_norm / 2) / th_norm

    M = np.eye(4) * np.cos(th_norm / 2) + omega4 * sin_term

    # Propagação do estado
    q_prop = M @ q_est
    b_gyro_prop = b_gyro
    x_prop = np.concatenate([q_prop, b_gyro_prop]) # Flatten automático

    # Matrizes Jacobianas
    GT = np.block([[ -0.5 * np.eye(3), np.zeros((3, 3)) ], 
                   [ np.zeros((3, 3)), np.eye(3) ]])
    QT = GT @ Q @ GT.T

    omega3_prop = np.array([ [0, q_prop[2], -q_prop[1]],
                             [-q_prop[2], 0, q_prop[0]],
                             [q_prop[1], -q_prop[0], 0] ])

    omega3_est = np.array([  [0, q_est[2], -q_est[1]],
                             [-q_est[2], 0, q_est[0]],
                             [q_est[1], -q_est[0], 0] ])
    
    # Cálculo de A_prop e A_est
    A_prop = (q_prop[3]**2 - np.linalg.norm(q_prop[0:3])**2) * np.eye(3) + \
             2 * np.outer(q_prop[0:3], q_prop[0:3]) + \
             2 * q_prop[3] * omega3_prop
             
    A_est = (q_est[3]**2 - np.linalg.norm(q_est[0:3])**2) * np.eye(3) + \
            2 * np.outer(q_est[0:3], q_est[0:3]) + \
            2 * q_est[3] * omega3_est

    L = A_prop @ A_est.T
    KK = -0.5 * (L + np.eye(3)) * (Dt / 2)
    
    PhiT = np.block([
        [L, KK], 
        [np.zeros((3, 3)), np.eye(3)]
    ])
    
    SiG = (PhiT @ QT @ PhiT.T + QT) * (Dt / 2)
    PT_prop = PhiT @ PT_est @ PhiT.T + SiG

    return x_prop, PT_prop, i_out

def estimador(x_prop, PT_prop, q_obs, R, i):
    q = q_obs
    q_obs_vec = np.array([q[1], q[2], q[3], q[0]])

    q_prop = x_prop[0:4]
    # b_prop = x_prop[4:7]

    E = np.array([ [ q_prop[3], -q_prop[2], q_prop[1] ],
                   [ q_prop[2], q_prop[3], -q_prop[0] ],
                   [ -q_prop[1], q_prop[0], q_prop[3] ],
                   [ -q_prop[0], -q_prop[1], -q_prop[2]] ])
    
    S = np.block([[E, np.zeros((4, 3))], 
                  [np.zeros((3, 3)), np.eye(3)]])

    if i % 10 != 0:
        x_est = x_prop
        PT_est = PT_prop
        P_est = S @ PT_est @ S.T
    else:
        HT = np.block([[E, np.zeros((4, 3))]])

        Ptt_prop = PT_prop[0:3, 0:3]
        Pbt_prop = PT_prop[3:6, 0:3]

        KT = np.concatenate([Ptt_prop, Pbt_prop], axis=0) @ np.linalg.inv(Ptt_prop + R) @ E.T

        PT_est = PT_prop - KT @ HT @ PT_prop
        P_est = S @ PT_est @ S.T
        K = S @ KT

        if (np.dot(q_prop, q_obs_vec)) > 0:
            q_obs_final = q_obs_vec
        else:
            q_obs_final = -q_obs_vec
        
        x_est = x_prop + K @ (q_obs_final - q_prop)

        n = np.linalg.norm(x_est[0:4])
        x_est[0:4] = x_est[0:4] / n

    return x_est, P_est, PT_est