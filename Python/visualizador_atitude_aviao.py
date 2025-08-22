import serial
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import time
import threading
from collections import deque
import matplotlib.animation as animation

class QuaternionAttitudeVisualizr:
    def __init__(self, com_port='COM1', baudrate=115200):
        """
        Inicializa o visualizador de atitude com quatérnions
        
        Args:
            com_port: Porta COM para receber dados
            baudrate: Taxa de transmissão
        """
        # Configuração da porta serial
        try:
            self.ser = serial.Serial(port=com_port, baudrate=baudrate, timeout=1)
            print(f"✓ Conectado na porta {com_port}")
        except serial.SerialException as e:
            print(f"❌ Erro ao conectar na porta {com_port}: {e}")
            self.ser = None
            return
        
        # Buffer para quatérnions (reduzido)
        self.quat_buffer = deque(maxlen=50)
        self.current_quat = np.array([1.0, 0.0, 0.0, 0.0])  # w, x, y, z
        
        # Configuração da figura (simplificada)
        self.fig = plt.figure(figsize=(12, 8))
        self.ax_3d = self.fig.add_subplot(111, projection='3d')
        
        # Configuração do eixo 3D
        self.ax_3d.set_xlim([-2, 2])
        self.ax_3d.set_ylim([-2, 2])
        self.ax_3d.set_zlim([-2, 2])
        self.ax_3d.set_xlabel('X')
        self.ax_3d.set_ylabel('Y')
        self.ax_3d.set_zlabel('Z')
        self.ax_3d.set_title('Atitude do Avião em Tempo Real')
        
        # Variáveis de controle
        self.running = True
        self.data_lock = threading.Lock()
        
        # Contador de frames para monitoramento
        self.frame_count = 0
        self.start_time = time.time()
        
    def quaternion_to_rotation_matrix(self, q):
        """
        Converte um quatérnion para matriz de rotação
        
        Args:
            q: quatérnion [w, x, y, z]
            
        Returns:
            Matriz de rotação 3x3
        """
        w, x, y, z = q
        
        # Normalizar o quatérnion
        norm = np.sqrt(w*w + x*x + y*y + z*z)
        if norm == 0:
            return np.eye(3)
        w, x, y, z = w/norm, x/norm, y/norm, z/norm
        
        # Matriz de rotação
        R = np.array([
            [1 - 2*(y*y + z*z), 2*(x*y - w*z), 2*(x*z + w*y)],
            [2*(x*y + w*z), 1 - 2*(x*x + z*z), 2*(y*z - w*x)],
            [2*(x*z - w*y), 2*(y*z + w*x), 1 - 2*(x*x + y*y)]
        ])
        
        return R
    
    def create_airplane_geometry(self):
        """
        Cria a geometria básica de um avião (otimizada)
        
        Returns:
            Array numpy com vértices do avião
        """
        # Geometria simplificada para melhor performance
        vertices = np.array([
            # Fuselagem (nariz → cauda)
            [2, 0, 0], [-2, 0, 0],
            # Asas (esquerda ↔ direita)
            [-0.5, -1.5, 0], [-0.5, 1.5, 0],
            # Cauda vertical
            [-2, 0, 0], [-2, 0, 0.8],
            # Cauda horizontal
            [-1.8, -0.5, 0], [-1.8, 0.5, 0]
        ])
        
        return vertices
    
    def rotate_airplane(self, vertices, rotation_matrix):
        """
        Aplica rotação aos vértices do avião
        
        Args:
            vertices: Array de vértices
            rotation_matrix: Matriz de rotação 3x3
            
        Returns:
            Vértices rotacionados
        """
        return np.dot(vertices, rotation_matrix.T)
    
    def read_serial_data(self):
        """
        Thread para ler dados da porta serial
        """
        while self.running and self.ser:
            try:
                if self.ser.in_waiting > 0:
                    line = self.ser.readline().decode('utf-8').strip()
                    if line:
                        # Assume formato: "w,x,y,z" para quatérnion
                        try:
                            quat_data = [float(x.strip()) for x in line.split(',')]
                            if len(quat_data) >= 4:
                                with self.data_lock:
                                    self.current_quat = np.array(quat_data[:4])
                                    self.quat_buffer.append(self.current_quat.copy())
                        except ValueError:
                            # Se não conseguir converter, ignora a linha
                            pass
                            
            except serial.SerialException:
                print("❌ Erro na comunicação serial")
                break
            except Exception as e:
                print(f"❌ Erro inesperado: {e}")
                break
                
            time.sleep(0.001)  # Pequeno delay para não sobrecarregar
    
    def update_plot(self, frame):
        """
        Atualiza o plot a cada frame da animação (otimizado)
        """
        with self.data_lock:
            current_quat = self.current_quat.copy()
        
        # Limpa apenas o necessário
        self.ax_3d.clear()
        self.ax_3d.set_xlim([-2, 2])
        self.ax_3d.set_ylim([-2, 2])
        self.ax_3d.set_zlim([-2, 2])
        self.ax_3d.set_xlabel('X')
        self.ax_3d.set_ylabel('Y')
        self.ax_3d.set_zlabel('Z')
        
        # Converte quatérnion para matriz de rotação
        rotation_matrix = self.quaternion_to_rotation_matrix(current_quat)
        
        # Cria e rotaciona o avião
        vertices = self.create_airplane_geometry()
        rotated_vertices = self.rotate_airplane(vertices, rotation_matrix)
        
        # Desenha o avião de forma otimizada
        # Fuselagem
        self.ax_3d.plot([rotated_vertices[0,0], rotated_vertices[1,0]], 
                       [rotated_vertices[0,1], rotated_vertices[1,1]], 
                       [rotated_vertices[0,2], rotated_vertices[1,2]], 
                       'b-', linewidth=3)
        
        # Asas
        self.ax_3d.plot([rotated_vertices[2,0], rotated_vertices[3,0]], 
                       [rotated_vertices[2,1], rotated_vertices[3,1]], 
                       [rotated_vertices[2,2], rotated_vertices[3,2]], 
                       'g-', linewidth=2)
        
        # Cauda vertical
        self.ax_3d.plot([rotated_vertices[4,0], rotated_vertices[5,0]], 
                       [rotated_vertices[4,1], rotated_vertices[5,1]], 
                       [rotated_vertices[4,2], rotated_vertices[5,2]], 
                       'r-', linewidth=2)
        
        # Cauda horizontal
        self.ax_3d.plot([rotated_vertices[6,0], rotated_vertices[7,0]], 
                       [rotated_vertices[6,1], rotated_vertices[7,1]], 
                       [rotated_vertices[6,2], rotated_vertices[7,2]], 
                       'r-', linewidth=2)
        
        # Eixos de referência (simplificados)
        self.ax_3d.plot([0, 1], [0, 0], [0, 0], 'r-', alpha=0.3, linewidth=1)  # X
        self.ax_3d.plot([0, 0], [0, 1], [0, 0], 'g-', alpha=0.3, linewidth=1)  # Y
        self.ax_3d.plot([0, 0], [0, 0], [0, 1], 'b-', alpha=0.3, linewidth=1)  # Z
        
        # Atualiza contador de frames
        self.frame_count += 1
        if self.frame_count % 60 == 0:  # A cada 60 frames
            elapsed = time.time() - self.start_time
            fps = self.frame_count / elapsed
            self.ax_3d.set_title(f'Atitude do Avião - {fps:.1f} FPS | Dados: {len(self.quat_buffer)}')
    
    def start_visualization(self):
        """
        Inicia a visualização em tempo real (otimizada)
        """
        if not self.ser:
            print("❌ Porta serial não disponível")
            return
        
        # Inicia thread para leitura serial
        serial_thread = threading.Thread(target=self.read_serial_data)
        serial_thread.daemon = True
        serial_thread.start()
        
        # Configura animação com intervalo maior para melhor performance
        ani = animation.FuncAnimation(self.fig, self.update_plot, interval=100, blit=False)
        
        print("✓ Visualização iniciada (modo otimizado). Pressione Ctrl+C para parar.")
        plt.tight_layout()
        plt.show()
        
        self.running = False
        if self.ser:
            self.ser.close()

def main():
    """
    Função principal
    """
    print("🛩️ Visualizador de Atitude com Quatérnions")
    print("=" * 50)
    
    try:
        visualizer = QuaternionAttitudeVisualizr(com_port='COM1', baudrate=115200)
        visualizer.start_visualization()
    except KeyboardInterrupt:
        print("\n❌ Visualização interrompida pelo usuário")
    except Exception as e:
        print(f"❌ Erro: {e}")

if __name__ == "__main__":
    main()
