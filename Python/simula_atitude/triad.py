import numpy as np

def TRIAD(v1, v2, w1, w2, sig1, sig2):
    v1_triad = v1 / np.linalg.norm(v1)
    w1_triad = w1 / np.linalg.norm(w1)

    mat_ref = np.array([v1_triad,
                        np.cross(v1_triad, v2) / np.linalg.norm(np.cross(v1_triad, v2)),
                        np.cross(v1_triad, np.cross(v1_triad, v2)) / np.linalg.norm(np.cross(v1_triad, v2))])
    mat_obs = np.array([w1_triad,
                        np.cross(w1_triad, w2) / np.linalg.norm(np.cross(w1_triad, w2)),
                        np.cross(w1_triad, np.cross(w1_triad, w2)) / np.linalg.norm(np.cross(w1_triad, w2))])
    dcm = mat_obs.T @ mat_ref

    q0 = 0.5 * np.sqrt(1 + np.trace(dcm))
    q1 = (dcm[1, 2] - dcm[2, 1]) / (4 * q0)
    q2 = (dcm[2, 0] - dcm[0, 2]) / (4 * q0)
    q3 = (dcm[0, 1] - dcm[1, 0]) / (4 * q0)

    quaternion = np.array([q0, q1, q2, q3])

    R = sig1**2 * np.eye(3) + (1/np.cross(w1, w2)**2) * (sig2**2 * (np.dot(w1, w2) @ (w1 @ w2.transpose() + w2 @ w1.transpose()) + (sig2 ** 2 - sig1 **2) * (w1 @ w2.transpose())))

    return quaternion, R