import serial
import serial.tools.list_ports
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import time
from collections import deque
import threading
import csv
from datetime import datetime

def find_working_port(baudrate=115200):
    """Encontra automaticamente uma porta COM que funciona"""
    ports = serial.tools.list_ports.comports()
    
    print("Procurando portas COM disponíveis...")
    
    # Prioriza portas STLink (provavelmente o seu dispositivo)
    stm_ports = []
    other_ports = []
    
    for port in ports:
        if 'STM' in port.description or 'STLink' in port.description:
            stm_ports.append(port.device)
            print(f"🔍 Encontrou dispositivo STM: {port.device} - {port.description}")
        else:
            other_ports.append(port.device)
            print(f"📍 Porta disponível: {port.device} - {port.description}")
    
    # Testa primeiro as portas STM, depois as outras
    all_ports = stm_ports + other_ports
    
    for port_name in all_ports:
        try:
            ser = serial.Serial(port=port_name, baudrate=baudrate, timeout=1)
            print(f"✓ Porta {port_name} conectada com sucesso!")
            ser.close()
            return port_name
        except serial.SerialException as e:
            print(f"✗ Erro ao conectar em {port_name}: {e}")
            continue
    
    print("❌ Nenhuma porta COM funcional encontrada!")
    return None

# Configuração da porta serial
ser = serial.Serial(port='COM1', baudrate=115200, timeout=1)
print(f"Conectado na porta COM1")

# Configuração dos gráficos (dois subplots lado a lado)
fig = plt.figure(figsize=(20, 8))
ax_accel = fig.add_subplot(121, projection='3d')  # Acelerômetro à esquerda
ax_mag = fig.add_subplot(122, projection='3d')    # Magnetômetro à direita

# Buffers para armazenar os dados do acelerômetro (últimos N pontos)
MAX_POINTS = 1500
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
recording_data = True  # Controla se os dados estão sendo gravados nos buffers

# Parâmetros de filtragem inteligente
ACCEL_MAX_MAGNITUDE = 1.2  # Máximo módulo para acelerômetro (em g)
MIN_DISTANCE_THRESHOLD = 0.05  # Distância mínima para considerar ponto único (ajustável)
SHOW_REJECTION_LOGS = False  # Controla se mostra logs de pontos rejeitados

def calculate_magnitude(x, y, z):
    """Calcula o módulo de um vetor 3D"""
    return np.sqrt(x**2 + y**2 + z**2)

def calculate_distance(x1, y1, z1, x2, y2, z2):
    """Calcula a distância euclidiana entre dois pontos 3D"""
    return np.sqrt((x2-x1)**2 + (y2-y1)**2 + (z2-z1)**2)

def is_point_redundant(new_x, new_y, new_z, buffer_x, buffer_y, buffer_z, threshold=MIN_DISTANCE_THRESHOLD):
    """
    Verifica se um novo ponto é redundante comparado aos pontos existentes no buffer
    Retorna True se o ponto for muito próximo a algum existente (redundante)
    """
    if len(buffer_x) == 0:
        return False  # Buffer vazio, ponto não é redundante
    
    # Converte buffers para arrays numpy para cálculo eficiente
    existing_x = np.array(buffer_x)
    existing_y = np.array(buffer_y) 
    existing_z = np.array(buffer_z)
    
    # Calcula distâncias para todos os pontos existentes de uma vez
    distances = np.sqrt((existing_x - new_x)**2 + (existing_y - new_y)**2 + (existing_z - new_z)**2)
    
    # Se alguma distância for menor que o threshold, ponto é redundante
    return np.any(distances < threshold)

def should_accept_accel_point(x, y, z):
    """
    Verifica se um ponto do acelerômetro deve ser aceito
    - Rejeita se módulo > ACCEL_MAX_MAGNITUDE
    - Rejeita se redundante espacialmente
    """
    # Verifica módulo
    magnitude = calculate_magnitude(x, y, z)
    if magnitude > ACCEL_MAX_MAGNITUDE:
        return False, f"Módulo muito alto: {magnitude:.3f}g"
    
    # Verifica redundância espacial
    if is_point_redundant(x, y, z, x_accel, y_accel, z_accel):
        return False, f"Ponto redundante"
    
    return True, "Aceito"

def should_accept_mag_point(x, y, z):
    """
    Verifica se um ponto do magnetômetro deve ser aceito
    - Rejeita apenas se redundante espacialmente
    """
    # Verifica redundância espacial
    if is_point_redundant(x, y, z, x_mag, y_mag, z_mag):
        return False, "Ponto redundante"
    
    return True, "Aceito"

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
    global running, save_data, save_plots, recording_data, ACCEL_MAX_MAGNITUDE, MIN_DISTANCE_THRESHOLD, SHOW_REJECTION_LOGS
    
    print("\nComandos disponíveis:")
    print("- Digite 's' + Enter para salvar os dados atuais")
    print("- Digite 'p' + Enter para salvar os plots")
    print("- Digite 'b' + Enter para alternar gravação de dados (pausar/retomar)")
    print("- Digite 'f' + Enter para ajustar filtros de qualidade")
    print("- Digite 'i' + Enter para mostrar info dos filtros")
    print("- Digite 'l' + Enter para ativar/desativar logs de rejeição")
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
            elif command == 'b':
                recording_data = not recording_data
                if recording_data:
                    print("▶️ Gravação de dados RETOMADA")
                else:
                    print("⏸️ Gravação de dados PAUSADA")
            elif command == 'f':
                print("\n🔧 Ajustar Filtros:")
                print("1 - Limiar acelerômetro (módulo máximo)")
                print("2 - Threshold anti-redundância")
                try:
                    choice = input("Escolha (1/2): ").strip()
                    if choice == '1':
                        new_val = float(input(f"Atual: {ACCEL_MAX_MAGNITUDE}g. Novo valor: "))
                        ACCEL_MAX_MAGNITUDE = new_val
                        print(f"✓ Limiar acelerômetro alterado para {ACCEL_MAX_MAGNITUDE}g")
                    elif choice == '2':
                        new_val = float(input(f"Atual: {MIN_DISTANCE_THRESHOLD}. Novo valor: "))
                        MIN_DISTANCE_THRESHOLD = new_val
                        print(f"✓ Threshold anti-redundância alterado para {MIN_DISTANCE_THRESHOLD}")
                except ValueError:
                    print("❌ Valor inválido!")
            elif command == 'i':
                accel_usage = (len(x_accel) / MAX_POINTS) * 100
                mag_usage = (len(x_mag) / MAX_POINTS) * 100
                print(f"\n📊 Status dos Filtros e Buffers:")
                print(f"   🎯 Acelerômetro: módulo ≤ {ACCEL_MAX_MAGNITUDE}g")
                print(f"   🔍 Anti-redundância: distância ≥ {MIN_DISTANCE_THRESHOLD}")
                print(f"   💾 Buffer Acelerômetro: {len(x_accel)}/{MAX_POINTS} ({accel_usage:.1f}%)")
                print(f"   💾 Buffer Magnetômetro: {len(x_mag)}/{MAX_POINTS} ({mag_usage:.1f}%)")
                print(f"   📈 Pontos únicos - Accel: {len(x_accel)}, Mag: {len(x_mag)}")
                print(f"   📋 Logs de rejeição: {'ATIVO' if SHOW_REJECTION_LOGS else 'INATIVO'}")
            elif command == 'l':
                SHOW_REJECTION_LOGS = not SHOW_REJECTION_LOGS
                status = "ATIVADOS" if SHOW_REJECTION_LOGS else "DESATIVADOS"
                print(f"📋 Logs de pontos rejeitados: {status}")
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
                # Lê uma linha da porta serial com tratamento de erro de encoding
                try:
                    line = ser.readline().decode('utf-8').strip()
                except UnicodeDecodeError:
                    # Tenta outros encodings ou ignora caracteres problemáticos
                    try:
                        line = ser.readline().decode('latin-1').strip()
                    except:
                        # Se ainda falhar, descarta esta linha
                        continue
                
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
                                # somente se a gravação estiver ativa E se passaram pela filtragem
                                if recording_data:
                                    with data_lock:
                                        # Verifica se deve aceitar o ponto do acelerômetro
                                        accel_accepted, accel_reason = should_accept_accel_point(accel_data[0], accel_data[1], accel_data[2])
                                        
                                        if accel_accepted:
                                            x_accel.append(accel_data[0])
                                            y_accel.append(accel_data[1])
                                            z_accel.append(accel_data[2])
                                        elif SHOW_REJECTION_LOGS:
                                            print(f"🚫 Acelerômetro rejeitado: {accel_reason}")
                                        
                                        # Verifica se deve aceitar o ponto do magnetômetro  
                                        mag_accepted, mag_reason = should_accept_mag_point(mag_data[0], mag_data[1], mag_data[2])
                                        
                                        if mag_accepted:
                                            x_mag.append(mag_data[0])
                                            y_mag.append(mag_data[1])
                                            z_mag.append(mag_data[2])
                                        elif SHOW_REJECTION_LOGS:
                                            print(f"🚫 Magnetômetro rejeitado: {mag_reason}")

                                # Reset para próximo par de dados
                                accel_data = None
                                waiting_for_mag = False
                                
                        except ValueError:
                            # Reset em caso de erro de conversão
                            accel_data = None
                            waiting_for_mag = False
                            continue
                            
        except Exception as e:
            if running:  # Só mostra erro se ainda estiver rodando
                print(f"Erro na leitura serial: {e}")
            time.sleep(0.1)
            
        time.sleep(0.01)  # Pequeno delay para não sobrecarregar

def update_plot():
    """Atualiza os gráficos 3D (acelerômetro e magnetômetro)"""
    global running, save_data, save_plots, recording_data
    
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
                    record_status = "🔴 GRAVANDO" if recording_data else "⏸️ PAUSADO"
                    magnitude = calculate_magnitude(x_accel_array[-1], y_accel_array[-1], z_accel_array[-1]) if len(x_accel_array) > 0 else 0
                    buffer_size_accel = len(x_accel)  # Tamanho atual do buffer
                    info_text_accel = f'Último: X={x_accel_array[-1]:.2f}, Y={y_accel_array[-1]:.2f}, Z={z_accel_array[-1]:.2f}\nMódulo: {magnitude:.3f}g\nBuffer: {buffer_size_accel}/{MAX_POINTS} pontos\nPontos únicos: {len(x_accel_array)}\n{record_status}\n🔍 Filtro: |v|≤{ACCEL_MAX_MAGNITUDE}g'
                    ax_accel.text2D(0.02, 0.98, info_text_accel, transform=ax_accel.transAxes, 
                                  fontsize=7, verticalalignment='top',
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
                    record_status = "🔴 GRAVANDO" if recording_data else "⏸️ PAUSADO"
                    mag_magnitude = calculate_magnitude(x_mag_array[-1], y_mag_array[-1], z_mag_array[-1]) if len(x_mag_array) > 0 else 0
                    buffer_size_mag = len(x_mag)  # Tamanho atual do buffer
                    info_text_mag = f'Último: X={x_mag_array[-1]:.3f}, Y={y_mag_array[-1]:.3f}, Z={z_mag_array[-1]:.3f}\nMódulo: {mag_magnitude:.3f}Ga\nBuffer: {buffer_size_mag}/{MAX_POINTS} pontos\nPontos únicos: {len(x_mag_array)}\n{record_status}\n🔍 Filtro: Anti-redundância'
                    ax_mag.text2D(0.02, 0.98, info_text_mag, transform=ax_mag.transAxes, 
                                fontsize=7, verticalalignment='top',
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
    print("\n📋 SISTEMA DE FILTRAGEM INTELIGENTE ATIVO:")
    print(f"   🎯 Acelerômetro: aceita apenas |v| ≤ {ACCEL_MAX_MAGNITUDE}g")
    print(f"   🔍 Anti-redundância: distância mín. = {MIN_DISTANCE_THRESHOLD}")
    print("   📊 Buffer armazena apenas pontos únicos espacialmente")
    print("   ⚙️ Use comando 'f' para ajustar filtros, 'i' para status")
    
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
