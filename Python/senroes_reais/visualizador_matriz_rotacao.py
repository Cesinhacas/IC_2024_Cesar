import serial
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import time
import threading
from collections import deque
import matplotlib.animation as animation

class RotationMatrixAttitudeVisualizr:
    def __init__(self, com_port='COM1', baudrate=115200):
        """
        Inicializa o visualizador de atitude com matriz de rotação
        
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
        
        # Buffer para matrizes de rotação
        self.rotation_buffer = deque(maxlen=50)  # Reduzido para economizar memória
        self.current_rotation = np.eye(3)  # Matriz identidade
        
        # Buffer para reconstruir matriz linha por linha
        self.matrix_rows = []
        self.waiting_for_rows = 0
        
        # Configuração da figura - simplificada
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
        
        # Linhas que conectam os vértices
        lines = [
            [0, 1],  # Fuselagem
            [2, 3],  # Asas
            [4, 5],  # Cauda vertical
            [6, 7]   # Cauda horizontal
        ]
        
        return vertices, lines
    
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
        Espera matriz de rotação no formato linha por linha:
        Linha 1: r11, r12, r13
        Linha 2: r21, r22, r23  
        Linha 3: r31, r32, r33
        """
        while self.running and self.ser:
            try:
                if self.ser.in_waiting > 0:
                    line = self.ser.readline().decode('utf-8').strip()
                    if line:
                        try:
                            # Espera 3 valores por linha (r1, r2, r3)
                            row_data = [float(x.strip()) for x in line.split(',')]
                            if len(row_data) >= 3:
                                # Adiciona a linha à matriz em construção
                                self.matrix_rows.append(row_data[:3])
                                
                                # Quando tiver 3 linhas, reconstrói a matriz
                                if len(self.matrix_rows) >= 3:
                                    rotation_matrix = np.array(self.matrix_rows[:3])
                                    
                                    with self.data_lock:
                                        self.current_rotation = rotation_matrix.copy()
                                        self.rotation_buffer.append(rotation_matrix.copy())
                                    
                                    # Limpa o buffer para próxima matriz
                                    self.matrix_rows = []
                        except (ValueError, IndexError):
                            # Se não conseguir converter, ignora a linha
                            # Mas limpa o buffer se estiver inconsistente
                            if len(self.matrix_rows) > 3:
                                self.matrix_rows = []
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
            current_rotation = self.current_rotation.copy()
        
        # Limpa apenas o necessário
        self.ax_3d.clear()
        self.ax_3d.set_xlim([-2, 2])
        self.ax_3d.set_ylim([-2, 2])
        self.ax_3d.set_zlim([-2, 2])
        self.ax_3d.set_xlabel('X')
        self.ax_3d.set_ylabel('Y')
        self.ax_3d.set_zlabel('Z')
        
        # Cria e rotaciona o avião
        vertices, lines = self.create_airplane_geometry()
        rotated_vertices = self.rotate_airplane(vertices, current_rotation)
        
        # Desenha o avião com menos elementos para melhor performance
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
            self.ax_3d.set_title(f'Atitude do Avião - {fps:.1f} FPS | Dados: {len(self.rotation_buffer)}')
    
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
        print("📡 Formato esperado:")
        print("   Linha 1: r11, r12, r13")
        print("   Linha 2: r21, r22, r23") 
        print("   Linha 3: r31, r32, r33")
        plt.tight_layout()
        plt.show()
        
        self.running = False
        if self.ser:
            self.ser.close()

def main():
    """
    Função principal
    """
    print("🛩️ Visualizador de Atitude com Matriz de Rotação (Otimizado)")
    print("=" * 60)
    
    try:
        visualizer = RotationMatrixAttitudeVisualizr(com_port='COM1', baudrate=115200)
        visualizer.start_visualization()
    except KeyboardInterrupt:
        print("\n❌ Visualização interrompida pelo usuário")
    except Exception as e:
        print(f"❌ Erro: {e}")

if __name__ == "__main__":
    main()
