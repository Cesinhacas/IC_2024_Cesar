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

# Configuração do gráfico
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

# Buffers para armazenar os dados (últimos N pontos)
MAX_POINTS = 1112
x_data = deque(maxlen=MAX_POINTS)
y_data = deque(maxlen=MAX_POINTS)
z_data = deque(maxlen=MAX_POINTS)

# Variáveis de controle
running = True
data_lock = threading.Lock()
save_data = False

def create_unit_sphere():
    """Cria uma esfera unitária para referência"""
    u = np.linspace(0, 2 * np.pi, 20)
    v = np.linspace(0, np.pi, 20)
    x_sphere = np.outer(np.cos(u), np.sin(v))
    y_sphere = np.outer(np.sin(u), np.sin(v))
    z_sphere = np.outer(np.ones(np.size(u)), np.cos(v))
    return x_sphere, y_sphere, z_sphere

def save_buffer_to_file():
    """Salva o buffer atual em um arquivo CSV"""
    global save_data
    
    with data_lock:
        if len(x_data) > 0:
            # Cria nome do arquivo com timestamp
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            filename = f"acelerometro_data_{timestamp}.csv"
            
            try:
                with open(filename, 'w', newline='', encoding='utf-8') as csvfile:
                    writer = csv.writer(csvfile)
                    # Escreve cabeçalho
                    writer.writerow(['X', 'Y', 'Z'])
                    
                    # Escreve os dados
                    for i in range(len(x_data)):
                        writer.writerow([x_data[i], y_data[i], z_data[i]])
                
                print(f"\nDados salvos em: {filename}")
                print(f"Total de pontos salvos: {len(x_data)}")
                
            except Exception as e:
                print(f"Erro ao salvar arquivo: {e}")
        else:
            print("\nNenhum dado para salvar!")
    
    save_data = False

def keyboard_listener():
    """Thread para escutar comandos do teclado"""
    global running, save_data
    
    print("\nComandos disponíveis:")
    print("- Digite 's' + Enter para salvar os dados atuais")
    print("- Digite 'q' + Enter para sair")
    
    while running:
        try:
            command = input().strip().lower()
            
            if command == 's':
                save_data = True
                print("Salvando dados...")
            elif command == 'q':
                running = False
                print("Parando programa...")
                break
            elif command == 'c':
                # Comando para limpar os dados
                with data_lock:
                    x_data.clear()
                    y_data.clear()
                    z_data.clear()
                print("Dados limpos!")
                
        except EOFError:
            break
        except Exception as e:
            print(f"Erro no comando: {e}")

def read_serial_data():
    """Thread para ler dados da porta serial"""
    global running
    
    while running:
        try:
            if ser.in_waiting > 0:
                # Lê uma linha da porta serial
                line = ser.readline().decode('utf-8').strip()
                
                # Processa a linha (assumindo formato: "x,y,z" ou "x y z")
                if line:
                    # Tenta diferentes formatos de separação
                    if ',' in line:
                        coords = line.split(',')
                    elif ' ' in line:
                        coords = line.split()
                    else:
                        continue
                    
                    if len(coords) >= 3:
                        try:
                            x = float(coords[0])
                            y = float(coords[1])
                            z = float(coords[2])
                            
                            # Adiciona os dados aos buffers de forma thread-safe
                            with data_lock:
                                x_data.append(x)
                                y_data.append(y)
                                z_data.append(z)
                                
                        except ValueError:
                            print(f"Erro ao converter dados: {line}")
                            continue
                            
        except Exception as e:
            print(f"Erro na leitura serial: {e}")
            time.sleep(0.1)
            
        time.sleep(0.01)  # Pequeno delay para não sobrecarregar

def update_plot():
    """Atualiza o gráfico 3D"""
    global running, save_data
    
    plt.ion()  # Modo interativo
    
    # Cria a esfera de referência uma vez
    x_sphere, y_sphere, z_sphere = create_unit_sphere()
    
    while running:
        try:
            # Verifica se deve salvar os dados
            if save_data:
                save_buffer_to_file()
            
            with data_lock:
                # Limpa o gráfico anterior
                ax.clear()
                
                # Desenha a esfera de referência unitária
                ax.plot_surface(x_sphere, y_sphere, z_sphere, 
                              alpha=0.2, color='gray', linewidth=0.5)
                
                if len(x_data) > 0:
                    # Converte para arrays numpy
                    x_array = np.array(x_data)
                    y_array = np.array(y_data)
                    z_array = np.array(z_data)
                    
                    # Plota os pontos
                    scatter = ax.scatter(x_array, y_array, z_array, 
                                       c=range(len(x_array)), cmap='viridis', 
                                       s=20, alpha=0.7)
                    
                    # Plota a trajetória (linha conectando os pontos)
                    if len(x_array) > 1:
                        ax.plot(x_array, y_array, z_array, 'b-', alpha=0.3, linewidth=1)
                    
                    # Destaca o ponto mais recente
                    if len(x_array) > 0:
                        ax.scatter([x_array[-1]], [y_array[-1]], [z_array[-1]], 
                                 c='red', s=100, alpha=1.0)
                    
                    # Adiciona informações na tela
                    info_text = f'Último ponto: X={x_array[-1]:.2f}, Y={y_array[-1]:.2f}, Z={z_array[-1]:.2f}\nTotal de pontos: {len(x_array)}\n\nComandos: "s" = salvar, "q" = sair'
                    ax.text2D(0.02, 0.98, info_text, transform=ax.transAxes, 
                            fontsize=10, verticalalignment='top',
                            bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.8))
                
                # Configurações do gráfico
                ax.set_xlabel('X (g)')
                ax.set_ylabel('Y (g)')
                ax.set_zlabel('Z (g)')
                ax.set_title('Dados do Acelerômetro em Tempo Real - Esfera de Referência (r=1)')
                
                # Define limites fixos para mostrar a esfera unitária
                ax.set_xlim([-1.5, 1.5])
                ax.set_ylim([-1.5, 1.5])
                ax.set_zlim([-1.5, 1.5])
                
                # Garante que os eixos tenham a mesma escala
                ax.set_box_aspect([1,1,1])
            
            plt.pause(0.05)  # Pausa pequena para atualizar o gráfico
            
        except Exception as e:
            print(f"Erro na atualização do gráfico: {e}")
            time.sleep(0.1)

def main():
    """Função principal"""
    global running
    
    print("Iniciando leitura do acelerômetro...")
    print("Esfera de referência: raio unitário (1g)")
    
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

