import numpy as np
import pandas as pd
import ctypes

my_atitude = ctypes.CDLL('./atitude.so')
my_atitude.TRIAD.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
my_atitude.TRIAD.restype = None

# Teste com apenas 3 pontos
num_exe = 3
quaternion = np.zeros((num_exe, 4))

print("Array quaternion inicial:")
print(quaternion)

# Dados de teste
dados_accel = np.array([[0.00537667, 0.00945506, -0.00100314],
                        [1.01833885, 1.00318731, 1.00342069], 
                        [-0.02258847, -0.01307312, 0.03584415]])

dados_mag = np.array([[0.71248345, 0.71129507, 0.68487016],
                      [0.01833885, 0.00259942, 0.00108565],
                      [0.68451831, 0.69843547, 0.76034556]])

v1 = np.array([0, 1, 0], dtype=np.float64)
v2 = np.array([1/np.sqrt(2), 0, 1/np.sqrt(2)], dtype=np.float64)

v1_ptr = v1.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
v2_ptr = v2.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

for i in range(num_exe):
    print(f"\n--- Iteração {i} ---")
    
    ax = dados_accel[0][i]
    ay = dados_accel[1][i]
    az = dados_accel[2][i]
    w1 = np.array([ax, ay, az], dtype=np.float64)

    mx = dados_mag[0][i]
    my = dados_mag[1][i]
    mz = dados_mag[2][i]
    w2 = np.array([mx, my, mz], dtype=np.float64)

    w1_ptr = w1.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    w2_ptr = w2.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    q = np.array([0.0, 0.0, 0.0, 0.0], dtype=np.float64)
    q_ptr = q.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    print(f"q antes: {q}")
    
    my_atitude.TRIAD(v1_ptr, v2_ptr, w1_ptr, w2_ptr, q_ptr)
    
    print(f"q depois: {q}")
    
    quaternion[i] = q.copy()
    
    print(f"quaternion[{i}] = {quaternion[i]}")

print("\nArray quaternion final:")
print(quaternion)

# Salvando
df = pd.DataFrame(quaternion)
print("\nDataFrame:")
print(df)

df.to_csv('./test_quaternion.csv', header=False, index=False)
print("Arquivo salvo como test_quaternion.csv")