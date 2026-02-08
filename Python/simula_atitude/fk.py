import numpy as np

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