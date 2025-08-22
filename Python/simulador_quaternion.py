import serial
import time
import math
import threading
import numpy as np

class QuaternionSimulator:
    """
    Simulador de dados de quatérnion para teste da interface
    Envia dados via COM virtual ou arquivo
    """
    
    def __init__(self, com_port='COM1', baudrate=115200):
        self.com_port = com_port
        self.baudrate = baudrate
        self.running = False
        self.time_start = time.time()
        
    def euler_to_quaternion(self, roll, pitch, yaw):
        """
        Converte ângulos de Euler para quatérnion
        
        Args:
            roll, pitch, yaw: ângulos em radianos
            
        Returns:
            quatérnion [w, x, y, z]
        """
        cr = math.cos(roll * 0.5)
        sr = math.sin(roll * 0.5)
        cp = math.cos(pitch * 0.5)
        sp = math.sin(pitch * 0.5)
        cy = math.cos(yaw * 0.5)
        sy = math.sin(yaw * 0.5)

        w = cr * cp * cy + sr * sp * sy
        x = sr * cp * cy - cr * sp * sy
        y = cr * sp * cy + sr * cp * sy
        z = cr * cp * sy - sr * sp * cy

        return [w, x, y, z]
    
    def generate_flight_pattern(self, t):
        """
        Gera um padrão de voo simulado
        
        Args:
            t: tempo em segundos
            
        Returns:
            roll, pitch, yaw em radianos
        """
        # Simulação de manobras de voo
        roll = math.sin(t * 0.3) * 0.5    # Roll suave (-30° a +30°)
        pitch = math.sin(t * 0.2) * 0.3   # Pitch (-17° a +17°)
        yaw = t * 0.1                     # Yaw contínuo
        
        return roll, pitch, yaw
    
    def generate_manual_maneuvers(self, t):
        """
        Gera manobras específicas para demonstração
        
        Args:
            t: tempo em segundos
            
        Returns:
            roll, pitch, yaw em radianos
        """
        # Manobras sequenciais para demonstração
        if t < 10:
            # Início estável
            return 0, 0, 0
        elif t < 20:
            # Roll para direita
            return math.sin((t-10) * 0.5) * 0.8, 0, 0
        elif t < 30:
            # Pitch para cima
            return 0, math.sin((t-20) * 0.5) * 0.6, 0
        elif t < 40:
            # Yaw girando
            return 0, 0, (t-30) * 0.2
        elif t < 50:
            # Manobra combinada
            roll = math.sin((t-40) * 0.8) * 0.5
            pitch = math.cos((t-40) * 0.6) * 0.4
            yaw = (t-40) * 0.15
            return roll, pitch, yaw
        else:
            # Retorna ao voo normal
            return 0, 0, t * 0.05
    
    def start_simulation_to_file(self, filename="quaternion_data.txt"):
        """
        Inicia simulação salvando em arquivo
        """
        print(f"📁 Iniciando simulação em arquivo: {filename}")
        print("Pressione Ctrl+C para parar")
        
        self.running = True
        
        try:
            with open(filename, 'w') as f:
                while self.running:
                    current_time = time.time() - self.time_start
                    
                    # Gera ângulos de Euler
                    roll, pitch, yaw = self.generate_manual_maneuvers(current_time)
                    
                    # Converte para quatérnion
                    quat = self.euler_to_quaternion(roll, pitch, yaw)
                    
                    # Formato: w,x,y,z
                    line = f"{quat[0]:.6f},{quat[1]:.6f},{quat[2]:.6f},{quat[3]:.6f}\n"
                    f.write(line)
                    f.flush()
                    
                    # Mostra progresso
                    roll_deg = math.degrees(roll)
                    pitch_deg = math.degrees(pitch)
                    yaw_deg = math.degrees(yaw)
                    print(f"\r🛩️ t={current_time:.1f}s | Roll:{roll_deg:+6.1f}° | Pitch:{pitch_deg:+6.1f}° | Yaw:{yaw_deg:+6.1f}°", end="")
                    
                    time.sleep(0.1)  # 10 Hz
                    
        except KeyboardInterrupt:
            print(f"\n✓ Simulação parada. Dados salvos em {filename}")
        
        self.running = False
    
    def start_simulation_to_serial(self):
        """
        Inicia simulação enviando dados para porta serial
        """
        try:
            ser = serial.Serial(port=self.com_port, baudrate=self.baudrate, timeout=1)
            print(f"✓ Conectado em {self.com_port} para simulação")
        except serial.SerialException as e:
            print(f"❌ Erro ao conectar em {self.com_port}: {e}")
            print("💡 Dica: Use start_simulation_to_file() para testar sem porta serial")
            return
        
        print("📡 Iniciando simulação via serial")
        print("Pressione Ctrl+C para parar")
        
        self.running = True
        
        try:
            while self.running:
                current_time = time.time() - self.time_start
                
                # Gera ângulos de Euler
                roll, pitch, yaw = self.generate_manual_maneuvers(current_time)
                
                # Converte para quatérnion
                quat = self.euler_to_quaternion(roll, pitch, yaw)
                
                # Formato: w,x,y,z
                line = f"{quat[0]:.6f},{quat[1]:.6f},{quat[2]:.6f},{quat[3]:.6f}\n"
                ser.write(line.encode('utf-8'))
                
                # Mostra progresso
                roll_deg = math.degrees(roll)
                pitch_deg = math.degrees(pitch)
                yaw_deg = math.degrees(yaw)
                print(f"\r🛩️ t={current_time:.1f}s | Roll:{roll_deg:+6.1f}° | Pitch:{pitch_deg:+6.1f}° | Yaw:{yaw_deg:+6.1f}°", end="")
                
                time.sleep(0.1)  # 10 Hz
                
        except KeyboardInterrupt:
            print(f"\n✓ Simulação parada")
        except serial.SerialException as e:
            print(f"\n❌ Erro na comunicação serial: {e}")
        
        self.running = False
        ser.close()
    
    def stop(self):
        """Para a simulação"""
        self.running = False

def test_quaternion_conversion():
    """
    Testa as conversões de quatérnion
    """
    print("🧪 Testando conversões de quatérnion")
    print("=" * 40)
    
    sim = QuaternionSimulator()
    
    # Testa casos conhecidos
    test_cases = [
        (0, 0, 0, "Posição neutra"),
        (math.pi/4, 0, 0, "Roll 45°"),
        (0, math.pi/6, 0, "Pitch 30°"),
        (0, 0, math.pi/2, "Yaw 90°"),
        (math.pi/6, math.pi/4, math.pi/3, "Combinado")
    ]
    
    for roll, pitch, yaw, desc in test_cases:
        quat = sim.euler_to_quaternion(roll, pitch, yaw)
        print(f"{desc}:")
        print(f"  Euler: Roll={math.degrees(roll):.1f}° Pitch={math.degrees(pitch):.1f}° Yaw={math.degrees(yaw):.1f}°")
        print(f"  Quat:  w={quat[0]:.3f} x={quat[1]:.3f} y={quat[2]:.3f} z={quat[3]:.3f}")
        print()

def main():
    """
    Função principal do simulador
    """
    print("🛩️ Simulador de Dados de Quatérnion")
    print("=" * 50)
    
    while True:
        print("\nOpções:")
        print("1. Simular dados para arquivo")
        print("2. Simular dados via serial (COM1)")
        print("3. Testar conversões")
        print("4. Sair")
        
        choice = input("\nEscolha uma opção (1-4): ").strip()
        
        if choice == '1':
            filename = input("Nome do arquivo (Enter para 'quaternion_data.txt'): ").strip()
            if not filename:
                filename = "quaternion_data.txt"
            
            sim = QuaternionSimulator()
            sim.start_simulation_to_file(filename)
            
        elif choice == '2':
            port = input("Porta COM (Enter para 'COM1'): ").strip()
            if not port:
                port = 'COM1'
            
            sim = QuaternionSimulator(com_port=port)
            sim.start_simulation_to_serial()
            
        elif choice == '3':
            test_quaternion_conversion()
            
        elif choice == '4':
            print("👋 Saindo...")
            break
            
        else:
            print("❌ Opção inválida")

if __name__ == "__main__":
    main()
