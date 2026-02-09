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