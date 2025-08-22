import serial
import time
import math
import threading
import numpy as np

class DualMagnetometerSimulator:
    """
    Simulador de dados de dois magnetômetros para teste da interface
    """
    
    def __init__(self, com_port='COM1', baudrate=115200):
        self.com_port = com_port
        self.baudrate = baudrate
        self.running = False
        self.time_start = time.time()
        
    def euler_to_rotation_matrix(self, roll, pitch, yaw):
        """
        Converte ângulos de Euler para matriz de rotação
        """
        cr = math.cos(roll)
        sr = math.sin(roll)
        cp = math.cos(pitch)
        sp = math.sin(pitch)
        cy = math.cos(yaw)
        sy = math.sin(yaw)
        
        R = np.array([
            [cy*cp, cy*sp*sr - sy*cr, cy*sp*cr + sy*sr],
            [sy*cp, sy*sp*sr + cy*cr, sy*sp*cr - cy*sr],
            [-sp,   cp*sr,            cp*cr          ]
        ])
        
        return R
    
    def generate_dual_flight_pattern(self, t):
        """
        Gera padrões de voo diferentes para os dois magnetômetros
        Simula duas orientações ligeiramente diferentes
        """
        # Magnetômetro 1 - movimento principal
        roll1 = math.sin(t * 0.3) * 0.6
        pitch1 = math.sin(t * 0.2) * 0.4  
        yaw1 = t * 0.1
        
        # Magnetômetro 2 - com offset e movimento ligeiramente diferente
        roll2 = math.sin(t * 0.35) * 0.5 + 0.1  # Offset de 0.1 rad
        pitch2 = math.sin(t * 0.25) * 0.3 - 0.05  # Offset de -0.05 rad
        yaw2 = t * 0.12 + 0.2  # Offset de 0.2 rad
        
        return (roll1, pitch1, yaw1), (roll2, pitch2, yaw2)
    
    def generate_test_maneuvers(self, t):
        """
        Gera manobras específicas para demonstração
        """
        if t < 10:
            # Início - posições ligeiramente diferentes
            angles1 = (0, 0, 0)
            angles2 = (0.1, -0.05, 0.2)
        elif t < 20:
            # Roll diferencial
            angles1 = (math.sin((t-10) * 0.5) * 0.8, 0, 0)
            angles2 = (math.sin((t-10) * 0.5) * 0.6 + 0.1, 0, 0.2)
        elif t < 30:
            # Pitch diferencial
            angles1 = (0, math.sin((t-20) * 0.5) * 0.6, 0)
            angles2 = (0.1, math.sin((t-20) * 0.5) * 0.4 - 0.05, 0.2)
        elif t < 40:
            # Yaw coordenado mas com offset
            yaw_base = (t-30) * 0.2
            angles1 = (0, 0, yaw_base)
            angles2 = (0.1, -0.05, yaw_base + 0.2)
        else:
            # Movimento combinado
            angles1 = (
                math.sin((t-40) * 0.8) * 0.5,
                math.cos((t-40) * 0.6) * 0.4,
                (t-40) * 0.15
            )
            angles2 = (
                math.sin((t-40) * 0.8) * 0.4 + 0.1,
                math.cos((t-40) * 0.6) * 0.3 - 0.05,
                (t-40) * 0.15 + 0.2
            )
        
        return angles1, angles2
    
    def start_simulation_to_file(self, filename="dual_magnetometer_data.txt", format_type=1):
        """
        Inicia simulação salvando em arquivo
        
        Args:
            format_type: 1 = com identificadores MAG1/MAG2, 2 = sequência alternada
        """
        print(f"📁 Iniciando simulação dual em arquivo: {filename}")
        print(f"📡 Formato: {'Com identificadores' if format_type == 1 else 'Sequência alternada'}")
        print("Pressione Ctrl+C para parar")
        
        self.running = True
        
        try:
            with open(filename, 'w') as f:
                while self.running:
                    current_time = time.time() - self.time_start
                    
                    # Gera ângulos para ambos magnetômetros
                    angles1, angles2 = self.generate_test_maneuvers(current_time)
                    
                    # Converte para matrizes de rotação
                    R1 = self.euler_to_rotation_matrix(*angles1)
                    R2 = self.euler_to_rotation_matrix(*angles2)
                    
                    if format_type == 1:
                        # Formato com identificadores
                        f.write("MAG1\n")
                        f.write(f"{R1[0,0]:.6f}, {R1[0,1]:.6f}, {R1[0,2]:.6f}\n")
                        f.write(f"{R1[1,0]:.6f}, {R1[1,1]:.6f}, {R1[1,2]:.6f}\n")
                        f.write(f"{R1[2,0]:.6f}, {R1[2,1]:.6f}, {R1[2,2]:.6f}\n")
                        f.write("MAG2\n")
                        f.write(f"{R2[0,0]:.6f}, {R2[0,1]:.6f}, {R2[0,2]:.6f}\n")
                        f.write(f"{R2[1,0]:.6f}, {R2[1,1]:.6f}, {R2[1,2]:.6f}\n")
                        f.write(f"{R2[2,0]:.6f}, {R2[2,1]:.6f}, {R2[2,2]:.6f}\n")
                    else:
                        # Formato sequência alternada (3+3)
                        f.write(f"{R1[0,0]:.6f}, {R1[0,1]:.6f}, {R1[0,2]:.6f}\n")
                        f.write(f"{R1[1,0]:.6f}, {R1[1,1]:.6f}, {R1[1,2]:.6f}\n")
                        f.write(f"{R1[2,0]:.6f}, {R1[2,1]:.6f}, {R1[2,2]:.6f}\n")
                        f.write(f"{R2[0,0]:.6f}, {R2[0,1]:.6f}, {R2[0,2]:.6f}\n")
                        f.write(f"{R2[1,0]:.6f}, {R2[1,1]:.6f}, {R2[1,2]:.6f}\n")
                        f.write(f"{R2[2,0]:.6f}, {R2[2,1]:.6f}, {R2[2,2]:.6f}\n")
                    
                    f.flush()
                    
                    # Mostra progresso
                    roll1_deg, pitch1_deg, yaw1_deg = [math.degrees(x) for x in angles1]
                    roll2_deg, pitch2_deg, yaw2_deg = [math.degrees(x) for x in angles2]
                    
                    print(f"\r🛩️ t={current_time:.1f}s | Mag1: R{roll1_deg:+5.1f}° P{pitch1_deg:+5.1f}° Y{yaw1_deg:+5.1f}° | Mag2: R{roll2_deg:+5.1f}° P{pitch2_deg:+5.1f}° Y{yaw2_deg:+5.1f}°", end="")
                    
                    time.sleep(0.1)  # 10 Hz
                    
        except KeyboardInterrupt:
            print(f"\n✓ Simulação parada. Dados salvos em {filename}")
        
        self.running = False
    
    def start_simulation_to_serial(self, format_type=1):
        """
        Inicia simulação enviando dados para porta serial
        """
        try:
            ser = serial.Serial(port=self.com_port, baudrate=self.baudrate, timeout=1)
            print(f"✓ Conectado em {self.com_port} para simulação dual")
        except serial.SerialException as e:
            print(f"❌ Erro ao conectar em {self.com_port}: {e}")
            return
        
        print(f"📡 Simulação dual via serial - Formato: {'Identificadores' if format_type == 1 else 'Sequência'}")
        print("Pressione Ctrl+C para parar")
        
        self.running = True
        
        try:
            while self.running:
                current_time = time.time() - self.time_start
                
                # Gera ângulos para ambos magnetômetros
                angles1, angles2 = self.generate_test_maneuvers(current_time)
                
                # Converte para matrizes
                R1 = self.euler_to_rotation_matrix(*angles1)
                R2 = self.euler_to_rotation_matrix(*angles2)
                
                if format_type == 1:
                    # Com identificadores
                    ser.write("MAG1\n".encode('utf-8'))
                    ser.write(f"{R1[0,0]:.6f}, {R1[0,1]:.6f}, {R1[0,2]:.6f}\n".encode('utf-8'))
                    ser.write(f"{R1[1,0]:.6f}, {R1[1,1]:.6f}, {R1[1,2]:.6f}\n".encode('utf-8'))
                    ser.write(f"{R1[2,0]:.6f}, {R1[2,1]:.6f}, {R1[2,2]:.6f}\n".encode('utf-8'))
                    ser.write("MAG2\n".encode('utf-8'))
                    ser.write(f"{R2[0,0]:.6f}, {R2[0,1]:.6f}, {R2[0,2]:.6f}\n".encode('utf-8'))
                    ser.write(f"{R2[1,0]:.6f}, {R2[1,1]:.6f}, {R2[1,2]:.6f}\n".encode('utf-8'))
                    ser.write(f"{R2[2,0]:.6f}, {R2[2,1]:.6f}, {R2[2,2]:.6f}\n".encode('utf-8'))
                else:
                    # Sequência alternada
                    ser.write(f"{R1[0,0]:.6f}, {R1[0,1]:.6f}, {R1[0,2]:.6f}\n".encode('utf-8'))
                    ser.write(f"{R1[1,0]:.6f}, {R1[1,1]:.6f}, {R1[1,2]:.6f}\n".encode('utf-8'))
                    ser.write(f"{R1[2,0]:.6f}, {R1[2,1]:.6f}, {R1[2,2]:.6f}\n".encode('utf-8'))
                    ser.write(f"{R2[0,0]:.6f}, {R2[0,1]:.6f}, {R2[0,2]:.6f}\n".encode('utf-8'))
                    ser.write(f"{R2[1,0]:.6f}, {R2[1,1]:.6f}, {R2[1,2]:.6f}\n".encode('utf-8'))
                    ser.write(f"{R2[2,0]:.6f}, {R2[2,1]:.6f}, {R2[2,2]:.6f}\n".encode('utf-8'))
                
                # Mostra progresso
                roll1_deg, pitch1_deg, yaw1_deg = [math.degrees(x) for x in angles1]
                roll2_deg, pitch2_deg, yaw2_deg = [math.degrees(x) for x in angles2]
                
                print(f"\r🛩️ t={current_time:.1f}s | Mag1: R{roll1_deg:+5.1f}° P{pitch1_deg:+5.1f}° Y{yaw1_deg:+5.1f}° | Mag2: R{roll2_deg:+5.1f}° P{pitch2_deg:+5.1f}° Y{yaw2_deg:+5.1f}°", end="")
                
                time.sleep(0.1)  # 10 Hz
                
        except KeyboardInterrupt:
            print(f"\n✓ Simulação parada")
        except serial.SerialException as e:
            print(f"\n❌ Erro na comunicação serial: {e}")
        
        self.running = False
        ser.close()

def main():
    """
    Função principal do simulador dual
    """
    print("🛩️ Simulador de Dois Magnetômetros")
    print("=" * 60)
    
    while True:
        print("\nOpções:")
        print("1. Simular dados para arquivo (com identificadores)")
        print("2. Simular dados para arquivo (sequência alternada)")
        print("3. Simular dados via serial (com identificadores)")
        print("4. Simular dados via serial (sequência alternada)")
        print("5. Sair")
        
        choice = input("\nEscolha uma opção (1-5): ").strip()
        
        if choice == '1':
            filename = input("Nome do arquivo (Enter para 'dual_mag_data.txt'): ").strip()
            if not filename:
                filename = "dual_mag_data.txt"
            
            sim = DualMagnetometerSimulator()
            sim.start_simulation_to_file(filename, format_type=1)
            
        elif choice == '2':
            filename = input("Nome do arquivo (Enter para 'dual_mag_sequence.txt'): ").strip()
            if not filename:
                filename = "dual_mag_sequence.txt"
            
            sim = DualMagnetometerSimulator()
            sim.start_simulation_to_file(filename, format_type=2)
            
        elif choice == '3':
            port = input("Porta COM (Enter para 'COM1'): ").strip()
            if not port:
                port = 'COM1'
            
            sim = DualMagnetometerSimulator(com_port=port)
            sim.start_simulation_to_serial(format_type=1)
            
        elif choice == '4':
            port = input("Porta COM (Enter para 'COM1'): ").strip()
            if not port:
                port = 'COM1'
            
            sim = DualMagnetometerSimulator(com_port=port)
            sim.start_simulation_to_serial(format_type=2)
            
        elif choice == '5':
            print("👋 Saindo...")
            break
            
        else:
            print("❌ Opção inválida")

if __name__ == "__main__":
    main()
