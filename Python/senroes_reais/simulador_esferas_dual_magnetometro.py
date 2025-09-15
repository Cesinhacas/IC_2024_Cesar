import serial
import time
import math
import threading
import numpy as np

class DualMagnetometerRawSimulator:
    """
    Simulador de dados brutos de dois magnetômetros (x, y, z em μT)
    """
    
    def __init__(self, com_port='COM1', baudrate=115200):
        self.com_port = com_port
        self.baudrate = baudrate
        self.running = False
        self.time_start = time.time()
        
    def generate_magnetometer_data(self, t, mag_id=1):
        """
        Gera dados de magnetômetro simulados baseados no campo magnético terrestre
        
        Args:
            t: tempo em segundos
            mag_id: 1 ou 2 para diferentes padrões
            
        Returns:
            (x, y, z) em μT
        """
        # Campo magnético terrestre típico: ~50μT total
        # Componentes aproximadas para uma localização média
        base_field = {
            'declination': 0.2,  # Declinação magnética (radianos)
            'inclination': 1.0,  # Inclinação magnética (radianos)  
            'intensity': 50.0    # Intensidade total (μT)
        }
        
        if mag_id == 1:
            # Magnetômetro 1 - movimento principal
            roll = math.sin(t * 0.3) * 0.5
            pitch = math.sin(t * 0.2) * 0.4
            yaw = t * 0.1
            
            # Offset e ruído específicos
            offset = np.array([2.0, -1.5, 3.0])
            noise_level = 0.8
            
        else:
            # Magnetômetro 2 - movimento ligeiramente diferente
            roll = math.sin(t * 0.35) * 0.6 + 0.1
            pitch = math.sin(t * 0.25) * 0.3 - 0.05
            yaw = t * 0.12 + 0.2
            
            # Offset e ruído diferentes
            offset = np.array([-1.0, 2.5, -2.0])
            noise_level = 0.9
        
        # Matriz de rotação baseada nos ângulos
        cr, sr = math.cos(roll), math.sin(roll)
        cp, sp = math.cos(pitch), math.sin(pitch)
        cy, sy = math.cos(yaw), math.sin(yaw)
        
        R = np.array([
            [cy*cp, cy*sp*sr - sy*cr, cy*sp*cr + sy*sr],
            [sy*cp, sy*sp*sr + cy*cr, sy*sp*cr - cy*sr],
            [-sp,   cp*sr,            cp*cr          ]
        ])
        
        # Campo magnético de referência (NED - North East Down)
        # Componentes típicas do campo magnético terrestre
        mag_ref = np.array([
            base_field['intensity'] * math.cos(base_field['inclination']) * math.cos(base_field['declination']),  # Norte
            base_field['intensity'] * math.cos(base_field['inclination']) * math.sin(base_field['declination']),  # Leste  
            base_field['intensity'] * math.sin(base_field['inclination'])  # Down
        ])
        
        # Rotaciona o campo de referência
        mag_body = R @ mag_ref
        
        # Adiciona offset de hard iron
        mag_body += offset
        
        # Adiciona ruído
        noise = np.random.normal(0, noise_level, 3)
        mag_body += noise
        
        return mag_body[0], mag_body[1], mag_body[2]
    
    def generate_test_pattern(self, t):
        """
        Gera padrão de teste específico
        """
        # Diferentes fases de movimento
        if t < 15:
            # Rotação lenta em yaw para formar círculo
            yaw_angle = t * 0.2
            mag1_data = self.simulate_yaw_rotation(yaw_angle, mag_id=1)
            mag2_data = self.simulate_yaw_rotation(yaw_angle + 0.1, mag_id=2)
            
        elif t < 30:
            # Rotação em roll
            roll_angle = (t - 15) * 0.3
            mag1_data = self.simulate_roll_rotation(roll_angle, mag_id=1)
            mag2_data = self.simulate_roll_rotation(roll_angle + 0.05, mag_id=2)
            
        elif t < 45:
            # Rotação em pitch
            pitch_angle = (t - 30) * 0.25
            mag1_data = self.simulate_pitch_rotation(pitch_angle, mag_id=1)
            mag2_data = self.simulate_pitch_rotation(pitch_angle - 0.05, mag_id=2)
            
        else:
            # Movimento combinado complexo
            mag1_data = self.generate_magnetometer_data(t, mag_id=1)
            mag2_data = self.generate_magnetometer_data(t, mag_id=2)
        
        return mag1_data, mag2_data
    
    def simulate_yaw_rotation(self, yaw, mag_id=1):
        """Simula rotação pura em yaw"""
        base_field = 50.0
        offset = np.array([2.0, -1.5, 3.0]) if mag_id == 1 else np.array([-1.0, 2.5, -2.0])
        
        # Campo magnético rotacionado apenas em yaw
        x = base_field * 0.6 * math.cos(yaw) + offset[0] + np.random.normal(0, 0.5)
        y = base_field * 0.6 * math.sin(yaw) + offset[1] + np.random.normal(0, 0.5)
        z = base_field * 0.8 + offset[2] + np.random.normal(0, 0.3)  # Componente vertical constante
        
        return x, y, z
    
    def simulate_roll_rotation(self, roll, mag_id=1):
        """Simula rotação pura em roll"""
        base_field = 50.0
        offset = np.array([2.0, -1.5, 3.0]) if mag_id == 1 else np.array([-1.0, 2.5, -2.0])
        
        x = base_field * 0.7 + offset[0] + np.random.normal(0, 0.5)  # Componente X constante
        y = base_field * 0.5 * math.cos(roll) + offset[1] + np.random.normal(0, 0.5)
        z = base_field * 0.5 * math.sin(roll) + offset[2] + np.random.normal(0, 0.5)
        
        return x, y, z
    
    def simulate_pitch_rotation(self, pitch, mag_id=1):
        """Simula rotação pura em pitch"""
        base_field = 50.0
        offset = np.array([2.0, -1.5, 3.0]) if mag_id == 1 else np.array([-1.0, 2.5, -2.0])
        
        x = base_field * 0.6 * math.cos(pitch) + offset[0] + np.random.normal(0, 0.5)
        y = base_field * 0.4 + offset[1] + np.random.normal(0, 0.5)  # Componente Y constante
        z = base_field * 0.6 * math.sin(pitch) + offset[2] + np.random.normal(0, 0.5)
        
        return x, y, z
    
    def start_simulation_to_file(self, filename="dual_magnetometer_raw.txt", format_type=1):
        """
        Inicia simulação salvando em arquivo
        """
        print(f"📁 Iniciando simulação dual RAW em arquivo: {filename}")
        print(f"📡 Formato: {'Com identificadores' if format_type == 1 else 'Dados alternados'}")
        print("Pressione Ctrl+C para parar")
        
        self.running = True
        
        try:
            with open(filename, 'w') as f:
                while self.running:
                    current_time = time.time() - self.time_start
                    
                    # Gera dados brutos para ambos magnetômetros
                    mag1_data, mag2_data = self.generate_test_pattern(current_time)
                    
                    if format_type == 1:
                        # Formato com identificadores
                        f.write("MAG1\n")
                        f.write(f"{mag1_data[0]:.3f}, {mag1_data[1]:.3f}, {mag1_data[2]:.3f}\n")
                        f.write("MAG2\n")
                        f.write(f"{mag2_data[0]:.3f}, {mag2_data[1]:.3f}, {mag2_data[2]:.3f}\n")
                    else:
                        # Formato dados alternados
                        f.write(f"{mag1_data[0]:.3f}, {mag1_data[1]:.3f}, {mag1_data[2]:.3f}\n")
                        f.write(f"{mag2_data[0]:.3f}, {mag2_data[1]:.3f}, {mag2_data[2]:.3f}\n")
                    
                    f.flush()
                    
                    # Mostra progresso
                    mag1_magnitude = math.sqrt(sum(x**2 for x in mag1_data))
                    mag2_magnitude = math.sqrt(sum(x**2 for x in mag2_data))
                    
                    print(f"\r🧭 t={current_time:.1f}s | Mag1: [{mag1_data[0]:+6.1f}, {mag1_data[1]:+6.1f}, {mag1_data[2]:+6.1f}] |B|={mag1_magnitude:.1f}μT | Mag2: [{mag2_data[0]:+6.1f}, {mag2_data[1]:+6.1f}, {mag2_data[2]:+6.1f}] |B|={mag2_magnitude:.1f}μT", end="")
                    
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
            print(f"✓ Conectado em {self.com_port} para simulação dual RAW")
        except serial.SerialException as e:
            print(f"❌ Erro ao conectar em {self.com_port}: {e}")
            return
        
        print(f"📡 Simulação dual RAW via serial - Formato: {'Identificadores' if format_type == 1 else 'Alternado'}")
        print("Pressione Ctrl+C para parar")
        
        self.running = True
        
        try:
            while self.running:
                current_time = time.time() - self.time_start
                
                # Gera dados brutos
                mag1_data, mag2_data = self.generate_test_pattern(current_time)
                
                if format_type == 1:
                    # Com identificadores
                    ser.write("MAG1\n".encode('utf-8'))
                    ser.write(f"{mag1_data[0]:.3f}, {mag1_data[1]:.3f}, {mag1_data[2]:.3f}\n".encode('utf-8'))
                    ser.write("MAG2\n".encode('utf-8'))
                    ser.write(f"{mag2_data[0]:.3f}, {mag2_data[1]:.3f}, {mag2_data[2]:.3f}\n".encode('utf-8'))
                else:
                    # Dados alternados
                    ser.write(f"{mag1_data[0]:.3f}, {mag1_data[1]:.3f}, {mag1_data[2]:.3f}\n".encode('utf-8'))
                    ser.write(f"{mag2_data[0]:.3f}, {mag2_data[1]:.3f}, {mag2_data[2]:.3f}\n".encode('utf-8'))
                
                # Mostra progresso
                mag1_magnitude = math.sqrt(sum(x**2 for x in mag1_data))
                mag2_magnitude = math.sqrt(sum(x**2 for x in mag2_data))
                
                print(f"\r🧭 t={current_time:.1f}s | Mag1: [{mag1_data[0]:+6.1f}, {mag1_data[1]:+6.1f}, {mag1_data[2]:+6.1f}] |B|={mag1_magnitude:.1f}μT | Mag2: [{mag2_data[0]:+6.1f}, {mag2_data[1]:+6.1f}, {mag2_data[2]:+6.1f}] |B|={mag2_magnitude:.1f}μT", end="")
                
                time.sleep(0.1)  # 10 Hz
                
        except KeyboardInterrupt:
            print(f"\n✓ Simulação parada")
        except serial.SerialException as e:
            print(f"\n❌ Erro na comunicação serial: {e}")
        
        self.running = False
        ser.close()

def main():
    """
    Função principal do simulador
    """
    print("🧭 Simulador de Dados Brutos - Dois Magnetômetros")
    print("=" * 60)
    
    while True:
        print("\nOpções:")
        print("1. Simular dados para arquivo (com identificadores)")
        print("2. Simular dados para arquivo (alternado)")
        print("3. Simular dados via serial (com identificadores)")
        print("4. Simular dados via serial (alternado)")
        print("5. Sair")
        
        choice = input("\nEscolha uma opção (1-5): ").strip()
        
        if choice == '1':
            filename = input("Nome do arquivo (Enter para 'dual_mag_raw.txt'): ").strip()
            if not filename:
                filename = "dual_mag_raw.txt"
            
            sim = DualMagnetometerRawSimulator()
            sim.start_simulation_to_file(filename, format_type=1)
            
        elif choice == '2':
            filename = input("Nome do arquivo (Enter para 'dual_mag_alternated.txt'): ").strip()
            if not filename:
                filename = "dual_mag_alternated.txt"
            
            sim = DualMagnetometerRawSimulator()
            sim.start_simulation_to_file(filename, format_type=2)
            
        elif choice == '3':
            port = input("Porta COM (Enter para 'COM1'): ").strip()
            if not port:
                port = 'COM1'
            
            sim = DualMagnetometerRawSimulator(com_port=port)
            sim.start_simulation_to_serial(format_type=1)
            
        elif choice == '4':
            port = input("Porta COM (Enter para 'COM1'): ").strip()
            if not port:
                port = 'COM1'
            
            sim = DualMagnetometerRawSimulator(com_port=port)
            sim.start_simulation_to_serial(format_type=2)
            
        elif choice == '5':
            print("👋 Saindo...")
            break
            
        else:
            print("❌ Opção inválida")

if __name__ == "__main__":
    main()
