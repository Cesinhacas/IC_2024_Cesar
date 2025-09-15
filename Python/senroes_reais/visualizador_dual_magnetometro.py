import serial
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import time
import threading
from collections import deque
import matplotlib.animation as animation

class DualMagnetometerAttitudeVisualizr:
    def __init__(self, com_port='COM1', baudrate=115200):
        """
        Inicializa o visualizador de atitude com dois magnetômetros
        
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
        
        # Buffers para matrizes de rotação
        self.rotation_buffer_mag1 = deque(maxlen=50)
        self.rotation_buffer_mag2 = deque(maxlen=50)
        self.current_rotation_mag1 = np.eye(3)
        self.current_rotation_mag2 = np.eye(3)
        
        # Buffer para reconstruir matrizes linha por linha
        self.matrix_rows_mag1 = []
        self.matrix_rows_mag2 = []
        self.current_magnetometer = 1  # Alternará entre 1 e 2
        
        # Configuração da figura (dois aviões lado a lado)
        self.fig = plt.figure(figsize=(16, 8))
        self.ax_mag1 = self.fig.add_subplot(121, projection='3d')
        self.ax_mag2 = self.fig.add_subplot(122, projection='3d')
        
        # Configuração dos eixos 3D
        for ax, title in [(self.ax_mag1, 'Magnetômetro 1'), (self.ax_mag2, 'Magnetômetro 2')]:
            ax.set_xlim([-2, 2])
            ax.set_ylim([-2, 2])
            ax.set_zlim([-2, 2])
            ax.set_xlabel('X')
            ax.set_ylabel('Y')
            ax.set_zlabel('Z')
            ax.set_title(title)
        
        # Variáveis de controle
        self.running = True
        self.data_lock = threading.Lock()
        
        # Contador de frames para monitoramento
        self.frame_count = 0
        self.start_time = time.time()
        
        # Estatísticas
        self.matrices_received_mag1 = 0
        self.matrices_received_mag2 = 0
        
    def create_airplane_geometry(self):
        """
        Cria a geometria básica de um avião (otimizada)
        
        Returns:
            Array numpy com vértices do avião
        """
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
        Formato esperado:
        - MAG1: seguido de 3 linhas da matriz
        - MAG2: seguido de 3 linhas da matriz
        Ou alternativamente, 6 linhas consecutivas (3 para cada magnetômetro)
        """
        while self.running and self.ser:
            try:
                if self.ser.in_waiting > 0:
                    line = self.ser.readline().decode('utf-8').strip()
                    if line:
                        try:
                            # Verifica se é identificador de magnetômetro
                            if line.upper() == 'MAG1':
                                self.current_magnetometer = 1
                                self.matrix_rows_mag1 = []
                                continue
                            elif line.upper() == 'MAG2':
                                self.current_magnetometer = 2
                                self.matrix_rows_mag2 = []
                                continue
                            
                            # Tenta interpretar como linha de dados
                            row_data = [float(x.strip()) for x in line.split(',')]
                            if len(row_data) >= 3:
                                if self.current_magnetometer == 1:
                                    self.matrix_rows_mag1.append(row_data[:3])
                                    
                                    # Quando tiver 3 linhas, reconstrói a matriz
                                    if len(self.matrix_rows_mag1) >= 3:
                                        rotation_matrix = np.array(self.matrix_rows_mag1[:3])
                                        
                                        with self.data_lock:
                                            self.current_rotation_mag1 = rotation_matrix.copy()
                                            self.rotation_buffer_mag1.append(rotation_matrix.copy())
                                        
                                        self.matrices_received_mag1 += 1
                                        self.matrix_rows_mag1 = []
                                        
                                elif self.current_magnetometer == 2:
                                    self.matrix_rows_mag2.append(row_data[:3])
                                    
                                    # Quando tiver 3 linhas, reconstrói a matriz
                                    if len(self.matrix_rows_mag2) >= 3:
                                        rotation_matrix = np.array(self.matrix_rows_mag2[:3])
                                        
                                        with self.data_lock:
                                            self.current_rotation_mag2 = rotation_matrix.copy()
                                            self.rotation_buffer_mag2.append(rotation_matrix.copy())
                                        
                                        self.matrices_received_mag2 += 1
                                        self.matrix_rows_mag2 = []
                                
                                # Alternativa: assume sequência de 6 linhas (3+3)
                                else:
                                    # Se não há identificador, assume alternância automática
                                    if len(self.matrix_rows_mag1) < 3:
                                        self.matrix_rows_mag1.append(row_data[:3])
                                        if len(self.matrix_rows_mag1) == 3:
                                            rotation_matrix = np.array(self.matrix_rows_mag1)
                                            with self.data_lock:
                                                self.current_rotation_mag1 = rotation_matrix.copy()
                                                self.rotation_buffer_mag1.append(rotation_matrix.copy())
                                            self.matrices_received_mag1 += 1
                                    elif len(self.matrix_rows_mag2) < 3:
                                        self.matrix_rows_mag2.append(row_data[:3])
                                        if len(self.matrix_rows_mag2) == 3:
                                            rotation_matrix = np.array(self.matrix_rows_mag2)
                                            with self.data_lock:
                                                self.current_rotation_mag2 = rotation_matrix.copy()
                                                self.rotation_buffer_mag2.append(rotation_matrix.copy())
                                            self.matrices_received_mag2 += 1
                                            # Reset para próximo ciclo
                                            self.matrix_rows_mag1 = []
                                            self.matrix_rows_mag2 = []
                                            
                        except (ValueError, IndexError):
                            # Se erro, limpa buffers inconsistentes
                            if len(self.matrix_rows_mag1) > 3:
                                self.matrix_rows_mag1 = []
                            if len(self.matrix_rows_mag2) > 3:
                                self.matrix_rows_mag2 = []
                            pass
                            
            except serial.SerialException:
                print("❌ Erro na comunicação serial")
                break
            except Exception as e:
                print(f"❌ Erro inesperado: {e}")
                break
                
            time.sleep(0.001)
    
    def draw_airplane(self, ax, vertices, color_scheme=1):
        """
        Desenha o avião em um eixo específico
        
        Args:
            ax: Eixo matplotlib
            vertices: Vértices rotacionados do avião
            color_scheme: 1 ou 2 para cores diferentes
        """
        colors = {
            1: {'fuselage': 'b', 'wings': 'g', 'tail': 'r'},
            2: {'fuselage': 'c', 'wings': 'm', 'tail': 'orange'}
        }
        
        scheme = colors[color_scheme]
        
        # Fuselagem
        ax.plot([vertices[0,0], vertices[1,0]], 
               [vertices[0,1], vertices[1,1]], 
               [vertices[0,2], vertices[1,2]], 
               color=scheme['fuselage'], linewidth=3)
        
        # Asas
        ax.plot([vertices[2,0], vertices[3,0]], 
               [vertices[2,1], vertices[3,1]], 
               [vertices[2,2], vertices[3,2]], 
               color=scheme['wings'], linewidth=2)
        
        # Cauda vertical
        ax.plot([vertices[4,0], vertices[5,0]], 
               [vertices[4,1], vertices[5,1]], 
               [vertices[4,2], vertices[5,2]], 
               color=scheme['tail'], linewidth=2)
        
        # Cauda horizontal
        ax.plot([vertices[6,0], vertices[7,0]], 
               [vertices[6,1], vertices[7,1]], 
               [vertices[6,2], vertices[7,2]], 
               color=scheme['tail'], linewidth=2)
    
    def draw_reference_axes(self, ax):
        """
        Desenha eixos de referência
        """
        ax.plot([0, 1], [0, 0], [0, 0], 'r-', alpha=0.3, linewidth=1)  # X
        ax.plot([0, 0], [0, 1], [0, 0], 'g-', alpha=0.3, linewidth=1)  # Y
        ax.plot([0, 0], [0, 0], [0, 1], 'b-', alpha=0.3, linewidth=1)  # Z
    
    def update_plot(self, frame):
        """
        Atualiza o plot a cada frame da animação
        """
        with self.data_lock:
            current_rotation_mag1 = self.current_rotation_mag1.copy()
            current_rotation_mag2 = self.current_rotation_mag2.copy()
        
        # Limpa os eixos
        self.ax_mag1.clear()
        self.ax_mag2.clear()
        
        # Reconfigura os eixos
        for ax, title in [(self.ax_mag1, 'Magnetômetro 1'), (self.ax_mag2, 'Magnetômetro 2')]:
            ax.set_xlim([-2, 2])
            ax.set_ylim([-2, 2])
            ax.set_zlim([-2, 2])
            ax.set_xlabel('X')
            ax.set_ylabel('Y')
            ax.set_zlabel('Z')
            ax.set_title(title)
        
        # Cria geometria do avião
        vertices = self.create_airplane_geometry()
        
        # Rotaciona e desenha aviões
        rotated_vertices_mag1 = self.rotate_airplane(vertices, current_rotation_mag1)
        rotated_vertices_mag2 = self.rotate_airplane(vertices, current_rotation_mag2)
        
        self.draw_airplane(self.ax_mag1, rotated_vertices_mag1, color_scheme=1)
        self.draw_airplane(self.ax_mag2, rotated_vertices_mag2, color_scheme=2)
        
        # Desenha eixos de referência
        self.draw_reference_axes(self.ax_mag1)
        self.draw_reference_axes(self.ax_mag2)
        
        # Atualiza contador de frames e títulos
        self.frame_count += 1
        if self.frame_count % 60 == 0:
            elapsed = time.time() - self.start_time
            fps = self.frame_count / elapsed
            
            self.ax_mag1.set_title(f'Magnetômetro 1 | {fps:.1f} FPS | Dados: {self.matrices_received_mag1}')
            self.ax_mag2.set_title(f'Magnetômetro 2 | {fps:.1f} FPS | Dados: {self.matrices_received_mag2}')
    
    def start_visualization(self):
        """
        Inicia a visualização em tempo real
        """
        if not self.ser:
            print("❌ Porta serial não disponível")
            return
        
        # Inicia thread para leitura serial
        serial_thread = threading.Thread(target=self.read_serial_data)
        serial_thread.daemon = True
        serial_thread.start()
        
        # Configura animação
        ani = animation.FuncAnimation(self.fig, self.update_plot, interval=100, blit=False)
        
        print("✓ Visualização dual iniciada. Pressione Ctrl+C para parar.")
        print("📡 Formatos aceitos:")
        print("   Opção 1 - Com identificadores:")
        print("     MAG1")
        print("     r11, r12, r13")
        print("     r21, r22, r23")
        print("     r31, r32, r33")
        print("     MAG2")
        print("     r11, r12, r13")
        print("     r21, r22, r23")
        print("     r31, r32, r33")
        print("   Opção 2 - Sequência alternada (6 linhas):")
        print("     3 linhas Mag1 + 3 linhas Mag2")
        
        plt.tight_layout()
        plt.show()
        
        self.running = False
        if self.ser:
            self.ser.close()

def main():
    """
    Função principal
    """
    print("🛩️ Visualizador de Atitude - Dois Magnetômetros")
    print("=" * 60)
    
    try:
        visualizer = DualMagnetometerAttitudeVisualizr(com_port='COM1', baudrate=115200)
        visualizer.start_visualization()
    except KeyboardInterrupt:
        print("\n❌ Visualização interrompida pelo usuário")
    except Exception as e:
        print(f"❌ Erro: {e}")

if __name__ == "__main__":
    main()
