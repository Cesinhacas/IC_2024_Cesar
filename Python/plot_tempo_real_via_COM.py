import serial
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import time
from collections import deque
import threading
import csv

from datetime import datetime

# Configuração da porta serial
ser = serial.Serial(port='COM1', baudrate=115200, timeout=1)
print(f"Conectado na porta COM1")

# Configuração dos gráficos (dois subplots lado a lado)
fig = plt.figure(figsize=(20, 8))
ax_accel = fig.add_subplot(121, projection='3d')  # Acelerômetro à esquerda
ax_mag = fig.add_subplot(122, projection='3d')    # Magnetômetro à direita

# Buffers para armazenar os dados do acelerômetro (últimos N pontos)
MAX_POINTS = 1112
x_accel = deque(maxlen=MAX_POINTS)
y_accel = deque(maxlen=MAX_POINTS)
z_accel = deque(maxlen=MAX_POINTS)

# Buffers para armazenar os dados do magnetômetro (últimos N pontos)
x_mag = deque(maxlen=MAX_POINTS)
y_mag = deque(maxlen=MAX_POINTS)
z_mag = deque(maxlen=MAX_POINTS)

# Variáveis de controle
running = True
data_lock = threading.Lock()
save_data = False
save_plots = False

def create_unit_sphere():
    """Cria uma esfera unitária para referência"""
    u = np.linspace(0, 2 * np.pi, 20)
    v = np.linspace(0, np.pi, 20)
    x_sphere = np.outer(np.cos(u), np.sin(v))
    y_sphere = np.outer(np.sin(u), np.sin(v))
    z_sphere = np.outer(np.ones(np.size(u)), np.cos(v))
    return x_sphere, y_sphere, z_sphere

def save_buffer_to_file():
    """Salva os buffers em arquivos CSV separados"""
    global save_data
    
    with data_lock:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        
        # Salva dados do acelerômetro
        if len(x_accel) > 0:
            filename_accel = f"acelerometro_data_{timestamp}.csv"
            try:
                with open(filename_accel, 'w', newline='', encoding='utf-8') as csvfile:
                    writer = csv.writer(csvfile)
                    writer.writerow(['Timestamp', 'X_Accel_g', 'Y_Accel_g', 'Z_Accel_g'])
                    
                    for i in range(len(x_accel)):
                        writer.writerow([i, x_accel[i], y_accel[i], z_accel[i]])
                
                print(f"\n✓ Dados do acelerômetro salvos em: {filename_accel}")
                print(f"  Total de pontos: {len(x_accel)}")
                
            except Exception as e:
                print(f"❌ Erro ao salvar arquivo do acelerômetro: {e}")
        
        # Salva dados do magnetômetro
        if len(x_mag) > 0:
            filename_mag = f"magnetometro_data_{timestamp}.csv"
            try:
                with open(filename_mag, 'w', newline='', encoding='utf-8') as csvfile:
                    writer = csv.writer(csvfile)
                    writer.writerow(['Timestamp', 'X_Mag_Ga', 'Y_Mag_Ga', 'Z_Mag_Ga'])
                    
                    for i in range(len(x_mag)):
                        writer.writerow([i, x_mag[i], y_mag[i], z_mag[i]])
                
                print(f"✓ Dados do magnetômetro salvos em: {filename_mag}")
                print(f"  Total de pontos: {len(x_mag)}")
                
            except Exception as e:
                print(f"❌ Erro ao salvar arquivo do magnetômetro: {e}")
        
        if len(x_accel) == 0 and len(x_mag) == 0:
            print("\n⚠️ Nenhum dado para salvar!")
    
    save_data = False

def save_plots_to_file():
    """Salva os gráficos como imagens"""
    global save_plots
    
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    filename = f"plots_sensores_{timestamp}.png"
    
    try:
        plt.savefig(filename, dpi=300, bbox_inches='tight', 
                   facecolor='white', edgecolor='none')
        print(f"\n📊 Plots salvos em: {filename}")
        
    except Exception as e:
        print(f"❌ Erro ao salvar plots: {e}")
    
    save_plots = False

def keyboard_listener():
    """Thread para escutar comandos do teclado"""
    global running, save_data, save_plots
    
    print("\nComandos disponíveis:")
    print("- Digite 's' + Enter para salvar os dados atuais")
    print("- Digite 'p' + Enter para salvar os plots")
    print("- Digite 'q' + Enter para sair")
    print("- Digite 'c' + Enter para limpar dados")
    
    while running:
        try:
            command = input().strip().lower()
            
            if command == 's':
                save_data = True
                print("📁 Salvando dados...")
            elif command == 'p':
                save_plots = True
                print("📊 Salvando plots...")
            elif command == 'q':
                running = False
                print("⏹️ Parando programa...")
                break
            elif command == 'c':
                # Comando para limpar os dados
                with data_lock:
                    x_accel.clear()
                    y_accel.clear()
                    z_accel.clear()
                    x_mag.clear()
                    y_mag.clear()
                    z_mag.clear()
                print("🧹 Dados limpos!")
                
        except EOFError:
            break
        except Exception as e:
            print(f"Erro no comando: {e}")

def read_serial_data():
    """Thread para ler dados da porta serial"""
    global running
    
    accel_data = None
    waiting_for_mag = False
    
    while running:
        try:
            if ser.in_waiting > 0:
                # Lê uma linha da porta serial
                line = ser.readline().decode('utf-8').strip()
                
                if line:
                    # Remove espaços extras e processa a linha
                    if ',' in line:
                        coords = [x.strip() for x in line.split(',')]
                    elif ' ' in line:
                        coords = [x.strip() for x in line.split() if x.strip()]
                    else:
                        continue
                    
                    if len(coords) >= 3:
                        try:
                            x = float(coords[0])
                            y = float(coords[1])
                            z = float(coords[2])
                            
                            if not waiting_for_mag:
                                # Primeira linha - dados do acelerômetro
                                accel_data = (x, y, z)
                                waiting_for_mag = True
                            else:
                                # Segunda linha - dados do magnetômetro
                                mag_data = (x, y, z)
                                
                                # Adiciona ambos os dados aos buffers de forma thread-safe
                                with data_lock:
                                    # Dados do acelerômetro
                                    x_accel.append(accel_data[0])
                                    y_accel.append(accel_data[1])
                                    z_accel.append(accel_data[2])
                                    
                                    # Dados do magnetômetro
                                    x_mag.append(mag_data[0])
                                    y_mag.append(mag_data[1])
                                    z_mag.append(mag_data[2])
                                
                                # Reset para próximo par de dados
                                accel_data = None
                                waiting_for_mag = False
                                
                        except ValueError:
                            print(f"Erro ao converter dados: {line}")
                            # Reset em caso de erro
                            accel_data = None
                            waiting_for_mag = False
                            continue
                            
        except Exception as e:
            print(f"Erro na leitura serial: {e}")
            time.sleep(0.1)
            
        time.sleep(0.01)  # Pequeno delay para não sobrecarregar

def update_plot():
    """Atualiza os gráficos 3D (acelerômetro e magnetômetro)"""
    global running, save_data, save_plots
    
    plt.ion()  # Modo interativo
    
    # Cria as esferas de referência uma vez
    x_sphere, y_sphere, z_sphere = create_unit_sphere()
    
    while running:
        try:
            # Verifica se deve salvar os dados
            if save_data:
                save_buffer_to_file()
            
            # Verifica se deve salvar os plots
            if save_plots:
                save_plots_to_file()
            
            with data_lock:
                # Limpa os gráficos anteriores
                ax_accel.clear()
                ax_mag.clear()
                
                # ---- GRÁFICO DO ACELERÔMETRO ----
                # Desenha a esfera de referência unitária
                ax_accel.plot_surface(x_sphere, y_sphere, z_sphere, 
                                    alpha=0.2, color='gray', linewidth=0.5)
                
                if len(x_accel) > 0:
                    # Converte para arrays numpy
                    x_accel_array = np.array(x_accel)
                    y_accel_array = np.array(y_accel)
                    z_accel_array = np.array(z_accel)
                    
                    # Plota os pontos do acelerômetro
                    scatter_accel = ax_accel.scatter(x_accel_array, y_accel_array, z_accel_array, 
                                                   c=range(len(x_accel_array)), cmap='viridis', 
                                                   s=20, alpha=0.7)
                    
                    # Plota a trajetória (linha conectando os pontos)
                    if len(x_accel_array) > 1:
                        ax_accel.plot(x_accel_array, y_accel_array, z_accel_array, 'b-', alpha=0.3, linewidth=1)
                    
                    # Destaca o ponto mais recente
                    if len(x_accel_array) > 0:
                        ax_accel.scatter([x_accel_array[-1]], [y_accel_array[-1]], [z_accel_array[-1]], 
                                       c='red', s=100, alpha=1.0)
                    
                    # Adiciona informações na tela do acelerômetro
                    info_text_accel = f'Último: X={x_accel_array[-1]:.2f}, Y={y_accel_array[-1]:.2f}, Z={z_accel_array[-1]:.2f}\nPontos: {len(x_accel_array)}'
                    ax_accel.text2D(0.02, 0.98, info_text_accel, transform=ax_accel.transAxes, 
                                  fontsize=9, verticalalignment='top',
                                  bbox=dict(boxstyle='round', facecolor='lightblue', alpha=0.8))
                
                # Configurações do gráfico do acelerômetro
                ax_accel.set_xlabel('X (g)')
                ax_accel.set_ylabel('Y (g)')
                ax_accel.set_zlabel('Z (g)')
                ax_accel.set_title('Acelerômetro - Esfera de Referência (r=1g)')
                ax_accel.set_xlim([-1.5, 1.5])
                ax_accel.set_ylim([-1.5, 1.5])
                ax_accel.set_zlim([-1.5, 1.5])
                ax_accel.set_box_aspect([1,1,1])
                
                # ---- GRÁFICO DO MAGNETÔMETRO ----
                # Define escala apropriada para magnetômetro em Gauss
                # Campo magnético terrestre típico: ~0.5 Ga
                mag_scale = 0.23  # Assumindo dados em Gauss
                x_sphere_mag = x_sphere * mag_scale
                y_sphere_mag = y_sphere * mag_scale
                z_sphere_mag = z_sphere * mag_scale
                
                # Desenha a esfera de referência para magnetômetro
                ax_mag.plot_surface(x_sphere_mag, y_sphere_mag, z_sphere_mag, 
                                  alpha=0.2, color='gray', linewidth=0.5)
                
                if len(x_mag) > 0:
                    # Converte para arrays numpy
                    x_mag_array = np.array(x_mag)
                    y_mag_array = np.array(y_mag)
                    z_mag_array = np.array(z_mag)
                    
                    # Plota os pontos do magnetômetro
                    scatter_mag = ax_mag.scatter(x_mag_array, y_mag_array, z_mag_array, 
                                               c=range(len(x_mag_array)), cmap='plasma', 
                                               s=20, alpha=0.7)
                    
                    # Plota a trajetória (linha conectando os pontos)
                    if len(x_mag_array) > 1:
                        ax_mag.plot(x_mag_array, y_mag_array, z_mag_array, 'r-', alpha=0.3, linewidth=1)
                    
                    # Destaca o ponto mais recente
                    if len(x_mag_array) > 0:
                        ax_mag.scatter([x_mag_array[-1]], [y_mag_array[-1]], [z_mag_array[-1]], 
                                     c='red', s=100, alpha=1.0)
                    
                    # Adiciona informações na tela do magnetômetro
                    info_text_mag = f'Último: X={x_mag_array[-1]:.3f}, Y={y_mag_array[-1]:.3f}, Z={z_mag_array[-1]:.3f}\nPontos: {len(x_mag_array)}'
                    ax_mag.text2D(0.02, 0.98, info_text_mag, transform=ax_mag.transAxes, 
                                fontsize=9, verticalalignment='top',
                                bbox=dict(boxstyle='round', facecolor='lightcoral', alpha=0.8))
                
                # Configurações do gráfico do magnetômetro
                ax_mag.set_xlabel('X (Ga)')
                ax_mag.set_ylabel('Y (Ga)')
                ax_mag.set_zlabel('Z (Ga)')
                ax_mag.set_title('Magnetômetro - Esfera de Referência (r=0.5Ga)')
                ax_mag.set_xlim([-mag_scale*1.5, mag_scale*1.5])
                ax_mag.set_ylim([-mag_scale*1.5, mag_scale*1.5])
                ax_mag.set_zlim([-mag_scale*1.5, mag_scale*1.5])
                ax_mag.set_box_aspect([1,1,1])
            
            plt.tight_layout()
            plt.pause(0.05)  # Pausa pequena para atualizar o gráfico
            
        except Exception as e:
            print(f"Erro na atualização do gráfico: {e}")
            time.sleep(0.1)

def main():
    """Função principal"""
    global running
    
    print("Iniciando leitura dos sensores via COM1...")
    print("Gráfico esquerdo: Acelerômetro (esfera de referência: 1g)")
    print("Gráfico direito: Magnetômetro (esfera de referência: 0.5Ga)")
    print("\nFormato esperado dos dados:")
    print("Linha 1: ax, ay, az")
    print("Linha 2: mx, my, mz (em Gauss)")
    
    # Inicia a thread de leitura serial
    serial_thread = threading.Thread(target=read_serial_data)
    serial_thread.daemon = True
    serial_thread.start()
    
    # Inicia a thread de escuta do teclado
    keyboard_thread = threading.Thread(target=keyboard_listener)
    keyboard_thread.daemon = True
    keyboard_thread.start()
    
    try:
        # Inicia a atualização do gráfico (thread principal)
        update_plot()
        
    except KeyboardInterrupt:
        print("\nParando...")
        running = False
        
    finally:
        # Limpa recursos
        running = False
        if ser.is_open:
            ser.close()
        plt.ioff()
        plt.show()

if __name__ == "__main__":
    main()

