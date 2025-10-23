import numpy as np
import pandas as pd
import ctypes

my_atitude = ctypes.CDLL('./atitude_fixed.so')
my_atitude.TRIAD.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_atitude.TRIAD.restype = None

# Teste simples primeiro
v1 = np.array([0, 1, 0], dtype=np.float64)
v2 = np.array([1/np.sqrt(2), 0, 1/np.sqrt(2)], dtype=np.float64)
w1 = np.array([0.00537667, 1.01833885, -0.02258847], dtype=np.float64)
w2 = np.array([0.71248345, 0.01833885, 0.68451831], dtype=np.float64)

v1_ptr = v1.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
v2_ptr = v2.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
w1_ptr = w1.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
w2_ptr = w2.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

q = np.array([0.0, 0.0, 0.0, 0.0], dtype=np.float64)
q_ptr = q.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

print("Teste com versão corrigida:")
print("q antes:", q)
my_atitude.TRIAD(v1_ptr, v2_ptr, w1_ptr, w2_ptr, q_ptr)
print("q depois:", q)
print("Norma do quaternion:", np.linalg.norm(q))