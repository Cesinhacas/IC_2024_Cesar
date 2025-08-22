import serial
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import time
import threading
from collections import deque
import matplotlib.animation as animation

class DualMagnetometerSphereVisualizr:
    def __init__(self, com_port='COM1', baudrate=115200):
        """
        Inicializa o visualizador de esferas com dois magnetômetros
        
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
        
        # Buffers para dados dos magnetômetros (últimos N pontos)
        MAX_POINTS = 1000
        self.x_mag1 = deque(maxlen=MAX_POINTS)
        self.y_mag1 = deque(maxlen=MAX_POINTS)
        self.z_mag1 = deque(maxlen=MAX_POINTS)
        
        self.x_mag2 = deque(maxlen=MAX_POINTS)
        self.y_mag2 = deque(maxlen=MAX_POINTS)
        self.z_mag2 = deque(maxlen=MAX_POINTS)
        
        # Estado atual para identificar qual magnetômetro
        self.current_magnetometer = 1
        self.expecting_data_lines = 0
        
        # Configuração da figura (duas esferas lado a lado)
        self.fig = plt.figure(figsize=(16, 8))
        self.ax_mag1 = self.fig.add_subplot(121, projection='3d')
        self.ax_mag2 = self.fig.add_subplot(122, projection='3d')
        
        # Configuração dos eixos 3D para esferas
        for ax, title in [(self.ax_mag1, 'Magnetômetro 1'), (self.ax_mag2, 'Magnetômetro 2')]:
            ax.set_xlim([-80, 80])  # Ajustado para dados de magnetômetro (Ga)
            ax.set_ylim([-80, 80])
            ax.set_zlim([-80, 80])
            ax.set_xlabel('X (Ga)')
            ax.set_ylabel('Y (Ga)')
            ax.set_zlabel('Z (Ga)')
            ax.set_title(title)
        
        # Variáveis de controle
        self.running = True
        self.data_lock = threading.Lock()
        
        # Contador de frames e pontos
        self.frame_count = 0
        self.start_time = time.time()
        self.points_received_mag1 = 0
        self.points_received_mag2 = 0
        
    def create_unit_sphere(self):
        """Cria uma esfera unitária para referência"""
        u = np.linspace(0, 2 * np.pi, 20)
        v = np.linspace(0, np.pi, 20)
        x_sphere = 0.23 * np.outer(np.cos(u), np.sin(v))  # Escala para magnetômetro
        y_sphere = 0.23 * np.outer(np.sin(u), np.sin(v))
        z_sphere = 0.23 * np.outer(np.ones(np.size(u)), np.cos(v))
        return x_sphere, y_sphere, z_sphere
    
    def read_serial_data(self):
        """
        Thread para ler dados da porta serial
        Espera dados no formato:
        MAG1
        x1, y1, z1
        MAG2  
        x2, y2, z2
        Ou dados brutos alternados
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
                                continue
                            elif line.upper() == 'MAG2':
                                self.current_magnetometer = 2
                                continue
                            
                            # Tenta interpretar como dados x,y,z
                            coords = [float(x.strip()) for x in line.split(',')]
                            if len(coords) >= 3:
                                with self.data_lock:
                                    if self.current_magnetometer == 1:
                                        self.x_mag1.append(coords[0])
                                        self.y_mag1.append(coords[1])
                                        self.z_mag1.append(coords[2])
                                        self.points_received_mag1 += 1
                                        self.current_magnetometer = 2  # Alterna para próximo
                                    else:
                                        self.x_mag2.append(coords[0])
                                        self.y_mag2.append(coords[1])
                                        self.z_mag2.append(coords[2])
                                        self.points_received_mag2 += 1
                                        self.current_magnetometer = 1  # Volta para o primeiro
                        except (ValueError, IndexError):
                            # Se não conseguir converter, ignora a linha
                            pass
                            
            except serial.SerialException:
                print("❌ Erro na comunicação serial")
                break
            except Exception as e:
                print(f"❌ Erro inesperado: {e}")
                break
                
            time.sleep(0.001)
    
    def update_plot(self, frame):
        """
        Atualiza o plot a cada frame da animação
        """
        with self.data_lock:
            x_mag1_data = list(self.x_mag1)
            y_mag1_data = list(self.y_mag1)
            z_mag1_data = list(self.z_mag1)
            
            x_mag2_data = list(self.x_mag2)
            y_mag2_data = list(self.y_mag2)
            z_mag2_data = list(self.z_mag2)
        
        # Limpa os eixos
        self.ax_mag1.clear()
        self.ax_mag2.clear()
        
        # Reconfigura os eixos
        for ax, title in [(self.ax_mag1, 'Magnetômetro 1'), (self.ax_mag2, 'Magnetômetro 2')]:
            ax.set_xlim([-0.5, 0.5])
            ax.set_ylim([-0.5, 0.5])
            ax.set_zlim([-0.5, 0.5])
            ax.set_xlabel('X (Ga)')
            ax.set_ylabel('Y (Ga)')
            ax.set_zlabel('Z (Ga)')
            ax.set_title(title)
        
        # Desenha esferas de referência
        x_sphere, y_sphere, z_sphere = self.create_unit_sphere()
        self.ax_mag1.plot_surface(x_sphere, y_sphere, z_sphere, alpha=0.1, color='gray')
        self.ax_mag2.plot_surface(x_sphere, y_sphere, z_sphere, alpha=0.1, color='gray')
        
        # Plota pontos do magnetômetro 1
        if len(x_mag1_data) > 0:
            # Gradient de cores baseado no tempo (pontos mais recentes mais brilhantes)
            colors1 = np.linspace(0.3, 1.0, len(x_mag1_data))
            scatter1 = self.ax_mag1.scatter(x_mag1_data, y_mag1_data, z_mag1_data, 
                                          c=colors1, cmap='Blues', s=20, alpha=0.6)
            
            # Destaca o último ponto
            if len(x_mag1_data) > 0:
                self.ax_mag1.scatter([x_mag1_data[-1]], [y_mag1_data[-1]], [z_mag1_data[-1]], 
                                   c='red', s=100, alpha=1.0, edgecolors='black', linewidth=1)
        
        # Plota pontos do magnetômetro 2
        if len(x_mag2_data) > 0:
            colors2 = np.linspace(0.3, 1.0, len(x_mag2_data))
            scatter2 = self.ax_mag2.scatter(x_mag2_data, y_mag2_data, z_mag2_data, 
                                          c=colors2, cmap='Greens', s=20, alpha=0.6)
            
            # Destaca o último ponto
            if len(x_mag2_data) > 0:
                self.ax_mag2.scatter([x_mag2_data[-1]], [y_mag2_data[-1]], [z_mag2_data[-1]], 
                                   c='orange', s=100, alpha=1.0, edgecolors='black', linewidth=1)
        
        # Desenha eixos de coordenadas
        for ax in [self.ax_mag1, self.ax_mag2]:
            # Eixos
            ax.plot([0, 0.23], [0, 0], [0, 0], 'r-', alpha=0.5, linewidth=2)  # X
            ax.plot([0, 0], [0, 0.23], [0, 0], 'g-', alpha=0.5, linewidth=2)  # Y
            ax.plot([0, 0], [0, 0], [0, 0.23], 'b-', alpha=0.5, linewidth=2)  # Z

        # Atualiza títulos com estatísticas
        self.frame_count += 1
        if self.frame_count % 30 == 0:  # A cada 30 frames
            elapsed = time.time() - self.start_time
            fps = self.frame_count / elapsed
            
            self.ax_mag1.set_title(f'Magnetômetro 1 | {fps:.1f} FPS | Pontos: {self.points_received_mag1}')
            self.ax_mag2.set_title(f'Magnetômetro 2 | {fps:.1f} FPS | Pontos: {self.points_received_mag2}')
        
        # Informações adicionais no gráfico
        if len(x_mag1_data) > 0:
            # Calcula magnitude atual do magnetômetro 1
            mag1_magnitude = np.sqrt(x_mag1_data[-1]**2 + y_mag1_data[-1]**2 + z_mag1_data[-1]**2)
            self.ax_mag1.text2D(0.02, 0.98, f'|B1|: {mag1_magnitude:.1f} Ga', 
                              transform=self.ax_mag1.transAxes, va='top', 
                              bbox=dict(boxstyle='round', facecolor='lightblue', alpha=0.7))
        
        if len(x_mag2_data) > 0:
            # Calcula magnitude atual do magnetômetro 2
            mag2_magnitude = np.sqrt(x_mag2_data[-1]**2 + y_mag2_data[-1]**2 + z_mag2_data[-1]**2)
            self.ax_mag2.text2D(0.02, 0.98, f'|B2|: {mag2_magnitude:.1f} Ga', 
                              transform=self.ax_mag2.transAxes, va='top',
                              bbox=dict(boxstyle='round', facecolor='lightgreen', alpha=0.7))
    
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
        
        print("✓ Visualização de esferas duplas iniciada. Pressione Ctrl+C para parar.")
        print("📡 Formatos aceitos:")
        print("   Opção 1 - Com identificadores:")
        print("     MAG1")
        print("     x1, y1, z1")
        print("     MAG2")  
        print("     x2, y2, z2")
        print("   Opção 2 - Dados alternados:")
        print("     x1, y1, z1  (Mag1)")
        print("     x2, y2, z2  (Mag2)")
        
        plt.tight_layout()
        plt.show()
        
        self.running = False
        if self.ser:
            self.ser.close()

def main():
    """
    Função principal
    """
    print("🧭 Visualizador de Esferas - Dois Magnetômetros")
    print("=" * 60)
    
    try:
        visualizer = DualMagnetometerSphereVisualizr(com_port='COM1', baudrate=115200)
        visualizer.start_visualization()
    except KeyboardInterrupt:
        print("\n❌ Visualização interrompida pelo usuário")
    except Exception as e:
        print(f"❌ Erro: {e}")

if __name__ == "__main__":
    main()
