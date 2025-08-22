import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import time
import threading
from collections import deque
import matplotlib.animation as animation

class QuaternionFileVisualizr:
    def __init__(self, filename="quaternion_data.txt"):
        """
        Inicializa o visualizador de atitude lendo de arquivo
        
        Args:
            filename: Arquivo com dados de quatérnion
        """
        self.filename = filename
        
        # Buffer para quatérnions
        self.quat_buffer = deque(maxlen=100)
        self.current_quat = np.array([1.0, 0.0, 0.0, 0.0])  # w, x, y, z
        self.file_position = 0
        
        # Configuração da figura
        self.fig = plt.figure(figsize=(15, 10))
        self.ax_3d = self.fig.add_subplot(121, projection='3d')
        self.ax_info = self.fig.add_subplot(122)
        
        # Configuração do eixo 3D
        self.ax_3d.set_xlim([-2, 2])
        self.ax_3d.set_ylim([-2, 2])
        self.ax_3d.set_zlim([-2, 2])
        self.ax_3d.set_xlabel('X')
        self.ax_3d.set_ylabel('Y')
        self.ax_3d.set_zlabel('Z')
        self.ax_3d.set_title('Atitude do Avião - Reprodução de Arquivo')
        
        # Configuração do painel de informações
        self.ax_info.axis('off')
        self.ax_info.set_title('Informações de Atitude')
        
        # Variáveis de controle
        self.running = True
        self.data_lock = threading.Lock()
        
        # História de ângulos de Euler
        self.euler_history = {'roll': deque(maxlen=100), 
                             'pitch': deque(maxlen=100), 
                             'yaw': deque(maxlen=100)}
        
        # Carrega todos os dados do arquivo
        self.all_quaternions = self.load_quaternions_from_file()
        
    def load_quaternions_from_file(self):
        """
        Carrega todos os quatérnions do arquivo
        
        Returns:
            Lista de quatérnions
        """
        quaternions = []
        try:
            with open(self.filename, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line:
                        try:
                            quat_data = [float(x.strip()) for x in line.split(',')]
                            if len(quat_data) >= 4:
                                quaternions.append(np.array(quat_data[:4]))
                        except ValueError:
                            continue
            print(f"✓ Carregados {len(quaternions)} quatérnions do arquivo {self.filename}")
        except FileNotFoundError:
            print(f"❌ Arquivo {self.filename} não encontrado")
        except Exception as e:
            print(f"❌ Erro ao ler arquivo: {e}")
        
        return quaternions
    
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
    
    def quaternion_to_euler(self, q):
        """
        Converte quatérnion para ângulos de Euler (roll, pitch, yaw)
        
        Args:
            q: quatérnion [w, x, y, z]
            
        Returns:
            Tupla (roll, pitch, yaw) em graus
        """
        w, x, y, z = q
        
        # Normalizar
        norm = np.sqrt(w*w + x*x + y*y + z*z)
        if norm == 0:
            return 0, 0, 0
        w, x, y, z = w/norm, x/norm, y/norm, z/norm
        
        # Roll (x-axis rotation)
        sinr_cosp = 2 * (w * x + y * z)
        cosr_cosp = 1 - 2 * (x * x + y * y)
        roll = np.arctan2(sinr_cosp, cosr_cosp)
        
        # Pitch (y-axis rotation)
        sinp = 2 * (w * y - z * x)
        if abs(sinp) >= 1:
            pitch = np.copysign(np.pi / 2, sinp)  # use 90 degrees if out of range
        else:
            pitch = np.arcsin(sinp)
        
        # Yaw (z-axis rotation)
        siny_cosp = 2 * (w * z + x * y)
        cosy_cosp = 1 - 2 * (y * y + z * z)
        yaw = np.arctan2(siny_cosp, cosy_cosp)
        
        return np.degrees(roll), np.degrees(pitch), np.degrees(yaw)
    
    def create_airplane_geometry(self):
        """
        Cria a geometria básica de um avião
        
        Returns:
            Dicionário com vértices do avião
        """
        # Fuselagem (corpo principal)
        fuselage = np.array([
            [2, 0, 0],     # Nariz
            [-2, 0, 0],    # Cauda
            [0, 0, 0]      # Centro
        ])
        
        # Asas principais
        wings = np.array([
            [-0.5, -1.5, 0],  # Ponta da asa esquerda
            [-0.5, 1.5, 0],   # Ponta da asa direita
            [0, 0, 0]         # Centro
        ])
        
        # Cauda vertical
        vertical_tail = np.array([
            [-2, 0, 0],    # Base
            [-2, 0, 0.8],  # Topo
        ])
        
        # Cauda horizontal
        horizontal_tail = np.array([
            [-1.8, -0.5, 0],  # Esquerda
            [-1.8, 0.5, 0],   # Direita
            [-2, 0, 0]        # Centro
        ])
        
        return {
            'fuselage': fuselage,
            'wings': wings, 
            'vertical_tail': vertical_tail,
            'horizontal_tail': horizontal_tail
        }
    
    def rotate_airplane(self, airplane_parts, rotation_matrix):
        """
        Aplica rotação às partes do avião
        
        Args:
            airplane_parts: Dicionário com partes do avião
            rotation_matrix: Matriz de rotação 3x3
            
        Returns:
            Partes do avião rotacionadas
        """
        rotated_parts = {}
        for part_name, vertices in airplane_parts.items():
            rotated_parts[part_name] = np.dot(vertices, rotation_matrix.T)
        return rotated_parts
    
    def read_next_quaternion(self):
        """
        Lê o próximo quatérnion do arquivo
        """
        if self.all_quaternions and self.file_position < len(self.all_quaternions):
            with self.data_lock:
                self.current_quat = self.all_quaternions[self.file_position].copy()
                self.quat_buffer.append(self.current_quat.copy())
            self.file_position += 1
        elif self.all_quaternions:
            # Reinicia do começo quando chega ao fim
            self.file_position = 0
    
    def update_plot(self, frame):
        """
        Atualiza o plot a cada frame da animação
        """
        # Lê próximo quatérnion
        self.read_next_quaternion()
        
        with self.data_lock:
            current_quat = self.current_quat.copy()
        
        # Limpa o eixo 3D
        self.ax_3d.clear()
        self.ax_3d.set_xlim([-2, 2])
        self.ax_3d.set_ylim([-2, 2])
        self.ax_3d.set_zlim([-2, 2])
        self.ax_3d.set_xlabel('X')
        self.ax_3d.set_ylabel('Y')
        self.ax_3d.set_zlabel('Z')
        self.ax_3d.set_title('Atitude do Avião - Reprodução de Arquivo')
        
        # Converte quatérnion para matriz de rotação
        rotation_matrix = self.quaternion_to_rotation_matrix(current_quat)
        
        # Cria e rotaciona o avião
        airplane_parts = self.create_airplane_geometry()
        rotated_parts = self.rotate_airplane(airplane_parts, rotation_matrix)
        
        # Desenha o avião
        # Fuselagem
        fuselage = rotated_parts['fuselage']
        self.ax_3d.plot([fuselage[0,0], fuselage[1,0]], 
                       [fuselage[0,1], fuselage[1,1]], 
                       [fuselage[0,2], fuselage[1,2]], 
                       'b-', linewidth=3, label='Fuselagem')
        
        # Asas
        wings = rotated_parts['wings']
        self.ax_3d.plot([wings[0,0], wings[1,0]], 
                       [wings[0,1], wings[1,1]], 
                       [wings[0,2], wings[1,2]], 
                       'g-', linewidth=2, label='Asas')
        
        # Cauda vertical
        v_tail = rotated_parts['vertical_tail']
        self.ax_3d.plot([v_tail[0,0], v_tail[1,0]], 
                       [v_tail[0,1], v_tail[1,1]], 
                       [v_tail[0,2], v_tail[1,2]], 
                       'r-', linewidth=2, label='Cauda Vertical')
        
        # Cauda horizontal
        h_tail = rotated_parts['horizontal_tail']
        self.ax_3d.plot([h_tail[0,0], h_tail[1,0]], 
                       [h_tail[0,1], h_tail[1,1]], 
                       [h_tail[0,2], h_tail[1,2]], 
                       'r-', linewidth=2)
        self.ax_3d.plot([h_tail[1,0], h_tail[2,0]], 
                       [h_tail[1,1], h_tail[2,1]], 
                       [h_tail[1,2], h_tail[2,2]], 
                       'r-', linewidth=2)
        
        # Adiciona eixos de referência
        self.ax_3d.plot([0, 1], [0, 0], [0, 0], 'r-', alpha=0.3, linewidth=1)  # X
        self.ax_3d.plot([0, 0], [0, 1], [0, 0], 'g-', alpha=0.3, linewidth=1)  # Y
        self.ax_3d.plot([0, 0], [0, 0], [0, 1], 'b-', alpha=0.3, linewidth=1)  # Z
        
        # Atualiza informações de atitude
        roll, pitch, yaw = self.quaternion_to_euler(current_quat)
        
        # Adiciona à história
        self.euler_history['roll'].append(roll)
        self.euler_history['pitch'].append(pitch)
        self.euler_history['yaw'].append(yaw)
        
        # Limpa e atualiza painel de informações
        self.ax_info.clear()
        self.ax_info.axis('off')
        self.ax_info.set_title('Informações de Atitude', fontsize=16, fontweight='bold')
        
        # Progresso da reprodução
        progress = (self.file_position / len(self.all_quaternions)) * 100 if self.all_quaternions else 0
        
        # Mostra informações atuais
        info_text = f"""
QUATÉRNION:
w: {current_quat[0]:.3f}
x: {current_quat[1]:.3f}
y: {current_quat[2]:.3f}
z: {current_quat[3]:.3f}

ÂNGULOS DE EULER:
Roll:  {roll:.1f}°
Pitch: {pitch:.1f}°
Yaw:   {yaw:.1f}°

REPRODUÇÃO:
Posição: {self.file_position}/{len(self.all_quaternions)}
Progresso: {progress:.1f}%
        """
        
        self.ax_info.text(0.1, 0.7, info_text, fontsize=12, fontfamily='monospace',
                         verticalalignment='top')
        
        # Gráfico dos ângulos de Euler ao longo do tempo
        if len(self.euler_history['roll']) > 1:
            time_points = range(len(self.euler_history['roll']))
            
            # Cria subgráfico para histórico
            ax_hist = self.fig.add_subplot(224)
            ax_hist.clear()
            ax_hist.plot(time_points, list(self.euler_history['roll']), 'r-', label='Roll', linewidth=1)
            ax_hist.plot(time_points, list(self.euler_history['pitch']), 'g-', label='Pitch', linewidth=1)
            ax_hist.plot(time_points, list(self.euler_history['yaw']), 'b-', label='Yaw', linewidth=1)
            ax_hist.set_xlabel('Tempo (amostras)')
            ax_hist.set_ylabel('Ângulo (°)')
            ax_hist.set_title('Histórico de Ângulos')
            ax_hist.legend(fontsize=8)
            ax_hist.grid(True, alpha=0.3)
            ax_hist.set_ylim([-180, 180])
    
    def start_visualization(self):
        """
        Inicia a visualização
        """
        if not self.all_quaternions:
            print("❌ Nenhum dado de quatérnion disponível")
            return
        
        # Configura animação
        ani = animation.FuncAnimation(self.fig, self.update_plot, interval=100, blit=False)
        
        print(f"✓ Reprodução iniciada com {len(self.all_quaternions)} quatérnions")
        print("Pressione Ctrl+C para parar.")
        plt.tight_layout()
        plt.show()

def main():
    """
    Função principal
    """
    print("🛩️ Visualizador de Atitude - Reprodução de Arquivo")
    print("=" * 50)
    
    filename = input("Nome do arquivo (Enter para 'quaternion_data.txt'): ").strip()
    if not filename:
        filename = "quaternion_data.txt"
    
    try:
        visualizer = QuaternionFileVisualizr(filename=filename)
        visualizer.start_visualization()
    except KeyboardInterrupt:
        print("\n❌ Visualização interrompida pelo usuário")
    except Exception as e:
        print(f"❌ Erro: {e}")

if __name__ == "__main__":
    main()
