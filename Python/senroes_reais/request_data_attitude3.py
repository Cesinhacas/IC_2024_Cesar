import serial
import numpy as np
from scipy.spatial.transform import Rotation as R
import vpython as vp
import trimesh # Certifique-se de ter instalado: pip install trimesh

# --- Configurações da Comunicação Serial ---
SERIAL_PORT = 'COM1'
BAUD_RATE = 115200
REQUEST_CHAR = '@'

# --- Configuração do Modelo 3D ---
# ### CORRIGIDO ###: Use r"..." para o caminho no Windows.
# Atualize com o caminho correto no seu computador.
STL_FILE_PATH = r"C:\Users\labt5\Downloads\Shrek_coolgate_stls\obj_1_FabulousWluff.stl"
MODEL_SCALE_FACTOR = 1 # Ajuste este valor conforme o tamanho do seu STL

# --- Variável de Controle Global ---
running = True

# --- Funções de Controle da Interface ---
def stop_program():
    global running
    running = False

# --- Configuração da Cena Gráfica com VPython ---
def setup_scene():
    vp.scene.title = "Visualização de Atitude 3D com Modelo STL"
    vp.scene.caption = f"Orientação do dispositivo (Modelo: {STL_FILE_PATH.split('\\')[-1]})\n"
    vp.scene.width = 800
    vp.scene.height = 600
    
    vp.button(bind=stop_program, text="Fechar Aplicação")

    # Eixos de referência do mundo
    vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(1,0,0), color=vp.color.red, length=1)
    vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(0,1,0), color=vp.color.green, length=1)
    vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(0,0,1), color=vp.color.blue, length=1)

    try:
        mesh = trimesh.load_mesh(STL_FILE_PATH)
        
        # ### CORRIGIDO ###: A escala é aplicada AQUI, na criação de cada vértice.
        # Multiplicamos o vetor de posição de cada vértice pelo fator de escala.
        vertices = [vp.vertex(pos=vp.vector(v[0], v[1], v[2]) * MODEL_SCALE_FACTOR, color=vp.color.white) for v in mesh.vertices]

        # O restante da lógica permanece o mesmo
        triangles = [vp.triangle(vs=[vertices[i] for i in face]) for face in mesh.faces]
        print(f"Modelo '{STL_FILE_PATH.split('\\')[-1]}' carregado com sucesso: {len(vertices)} vértices, {len(triangles)} triângulos.")

        device_mesh = vp.compound(triangles)
        
        # ### CORRIGIDO ###: A linha "device_mesh.scale(...)" foi REMOVIDA.

        # Eixos locais que girarão com o modelo
        axis_x = vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(1,0,0), color=vp.color.red, length=0.8, shaftwidth=0.02)
        axis_y = vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(0,1,0), color=vp.color.green, length=0.8, shaftwidth=0.02)
        axis_z = vp.arrow(pos=vp.vector(0,0,0), axis=vp.vector(0,0,1), color=vp.color.blue, length=0.8, shaftwidth=0.02)
        
        device = vp.compound([device_mesh, axis_x, axis_y, axis_z])

    except Exception as e:
        print(f"ERRO: Não foi possível carregar o modelo STL '{STL_FILE_PATH}'. Detalhe: {e}")
        print("Usando uma caixa como substituto.")
        device_body = vp.box(pos=vp.vector(0,0,0), size=vp.vector(1, 0.5, 0.1), color=vp.color.white, opacity=0.8)
        device = device_body

    return device

# O resto do código (função main) permanece exatamente o mesmo
def main():
    global running
    device = setup_scene()
    if not device: return # Sai se o setup falhar

    ser = None
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Sucesso! Conectado a {SERIAL_PORT}.")
        print("Clique no botão 'Fechar Aplicação' ou pressione Ctrl+C para encerrar.")
    except serial.SerialException as e:
        print(f"ERRO: Não foi possível abrir a porta serial {SERIAL_PORT}. Detalhe: {e}")
        return

    try:
        while running:
            vp.rate(100)
            if not vp.scene.visible: running = False; continue
            
            ser.write(REQUEST_CHAR.encode('utf-8'))
            line_bytes = ser.readline()
            if not line_bytes: continue

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
            except vp.VPythonStopIteration:
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