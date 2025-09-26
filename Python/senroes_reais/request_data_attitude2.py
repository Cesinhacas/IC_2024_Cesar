import serial
import numpy as np
from scipy.spatial.transform import Rotation as R
import vpython as vp

# --- Configurações da Comunicação Serial ---
SERIAL_PORT = 'COM1'
BAUD_RATE = 115200
REQUEST_CHAR = '@'

# --- Variável de Controle Global ---
# ### NOVO ###: Esta variável será usada para sinalizar quando o programa deve parar.
running = True

# --- Funções de Controle da Interface ---
# ### NOVO ###: Esta função será chamada quando o botão for clicado.
def stop_program():
    """Altera a variável global 'running' para False para parar o loop principal."""
    global running
    running = False

# --- Configuração da Cena Gráfica com VPython ---
def setup_scene():
    """Cria a cena 3D, os objetos e os controles (botão de fechar)."""
    vp.scene.title = "Visualização de Atitude 3D"
    vp.scene.caption = "Orientação do dispositivo em tempo real. Eixos do Mundo: Vermelho(X), Verde(Y), Azul(Z)\n"
    vp.scene.width = 800
    vp.scene.height = 600
    
    # ### NOVO ###: Adiciona o botão para fechar a aplicação na legenda da cena.
    # A função 'stop_program' é 'ligada' (bind) ao evento de clique do botão.
    vp.button(bind=stop_program, text="Fechar Aplicação")

    # Desenha os eixos de referência do mundo (fixos)
    vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(1,0,0), color=vp.color.red, length=1)
    vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(0,1,0), color=vp.color.green, length=1)
    vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(0,0,1), color=vp.color.blue, length=1)

    # Cria o objeto que representará o dispositivo
    device_body = vp.box(pos=vp.vector(0,0,0), size=vp.vector(1, 0.5, 0.1), color=vp.color.white, opacity=0.8)
    
    # Anexa eixos ao corpo do dispositivo
    axis_x = vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(1,0,0), color=vp.color.red, length=0.8, shaftwidth=0.02)
    axis_y = vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(0,1,0), color=vp.color.green, length=0.8, shaftwidth=0.02)
    axis_z = vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(0,0,1), color=vp.color.blue, length=0.8, shaftwidth=0.02)
    
    # Agrupa todos os objetos do dispositivo
    device = vp.compound([device_body, axis_x, axis_y, axis_z])
    
    return device

def main():
    """Função principal: lê dados seriais e atualiza a visualização 3D."""
    global running # ### NOVO ###: Informa que usaremos a variável global

    device = setup_scene()

    ser = None
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Sucesso! Conectado a {SERIAL_PORT}. Uma janela do navegador deve abrir com a visualização.")
        print("Clique no botão 'Fechar Aplicação' na janela 3D ou pressione Ctrl+C no terminal para encerrar.")
    except serial.SerialException as e:
        print(f"ERRO: Não foi possível abrir a porta serial {SERIAL_PORT}. Detalhe: {e}")
        return

    try:
        # ### NOVO ###: O loop agora depende da variável 'running'.
        while running:
            vp.rate(100)
            
            # Se a janela do navegador for fechada manualmente, a conexão se perde.
            # Isso causa uma exceção que podemos usar para parar o programa.
            if not vp.scene.visible:
                running = False
                continue
            
            ser.write(REQUEST_CHAR.encode('utf-8'))
            line_bytes = ser.readline()

            if not line_bytes:
                continue

            try:
                line_str = line_bytes.decode('utf-8').strip()
                parts = line_str.split(',')
                if len(parts) != 4: continue
                
                q_received = np.array([float(p) for p in parts])
                q_scipy_format = np.array([q_received[1], q_received[2], q_received[3], q_received[0]])
                rotation = R.from_quat(q_scipy_format)
                
                rot_matrix = rotation.as_matrix()
                new_y_axis = vp.vector(rot_matrix[0,1], rot_matrix[1,1], rot_matrix[2,1])
                new_z_axis = vp.vector(rot_matrix[0,2], rot_matrix[1,2], rot_matrix[2,2])
                
                device.axis = new_z_axis
                device.up = new_y_axis
                
            except (ValueError, UnicodeDecodeError):
                continue
            # ### NOVO ###: Verifica se a cena ainda está ativa. Se o usuário fechar a aba/janela do navegador,
            # o VPython lança uma exceção na próxima chamada a `rate()`. Isso nos permite sair do loop.
            except vp. หยุดการทำงาน: # Exceção específica do VPython
                print("Janela de visualização fechada pelo usuário.")
                running = False


    except KeyboardInterrupt:
        print("\nPrograma interrompido pelo terminal.")
    finally:
        if ser and ser.is_open:
            ser.close()
            print(f"Porta serial {SERIAL_PORT} fechada.")
        print("Aplicação encerrada.")

if __name__ == "__main__":
    main()