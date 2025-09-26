import serial
import struct
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import time
import matplotlib.pyplot as plt

# Configurações da porta serial
SERIAL_PORT = 'COM1'
BAUDRATE = 115200
TIMEOUT = 0.1

def read_quaternion(ser):
    ser.write(b'@')
    try:
        # Lê uma linha completa (até \n)
        line = ser.readline().decode('utf-8').strip()
        if not line:
            return None
        
        # Remove espaços e divide por vírgula
        values = [float(x.strip()) for x in line.split(',')]
        
        if len(values) != 4:
            return None
            
        return np.array(values)
    
    except (ValueError, UnicodeDecodeError) as e:
        print(f"Erro ao ler dados: {e}")
        return None

def quaternion_to_rotation_matrix(q):
    w, x, y, z = q
    R = np.array([
        [1-2*(y**2+z**2), 2*(x*y-z*w),   2*(x*z+y*w)],
        [2*(x*y+z*w),     1-2*(x**2+z**2), 2*(y*z-x*w)],
        [2*(x*z-y*w),     2*(y*z+x*w),   1-2*(x**2+y**2)]
    ])
    return R

def plot_attitude(ax, R, q):
    ax.cla()
    ax.set_xlim([-1, 1])
    ax.set_ylim([-1, 1])
    ax.set_zlim([-1, 1])
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title(f'Quaternion: w={q[0]:.3f}, x={q[1]:.3f}, y={q[2]:.3f}, z={q[3]:.3f}')
    
    # Eixos do corpo
    origin = np.zeros(3)
    x_axis = R @ np.array([1, 0, 0])
    y_axis = R @ np.array([0, 1, 0])
    z_axis = R @ np.array([0, 0, 1])
    
    ax.quiver(*origin, *x_axis, color='r', length=1, normalize=True, label='X-axis')
    ax.quiver(*origin, *y_axis, color='g', length=1, normalize=True, label='Y-axis')
    ax.quiver(*origin, *z_axis, color='b', length=1, normalize=True, label='Z-axis')
    ax.legend()
    
    plt.draw()
    plt.pause(0.001)

def main():
    ser = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=TIMEOUT)
    plt.ion()
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    try:
        while True:
            q = read_quaternion(ser)
            if q is not None:
                # Verifica se o quaternion é válido
                norm = np.linalg.norm(q)
                if norm > 0:
                    q = q / norm  # Normaliza o quatérnion
                    R = quaternion_to_rotation_matrix(q)
                    plot_attitude(ax, R, q)
                else:
                    print("Quaternion inválido (norma zero)")
            else:
                time.sleep(0.01)
                
    except KeyboardInterrupt:
        print("Programa interrompido pelo usuário")
    finally:
        ser.close()
        plt.ioff()
        plt.show()

if __name__ == '__main__':
    main()