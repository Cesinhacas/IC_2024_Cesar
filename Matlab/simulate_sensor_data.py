import serial
import time
import math
import random

def simulate_sensor_data():
    """Simula dados de sensores para testar o plot"""
    
    # Tenta conectar na porta COM1 (você pode ajustar se necessário)
    try:
        # Conecta usando uma porta virtual ou loopback se disponível
        # Para teste, você pode usar um cabo loopback ou software como com0com
        print("Para testar, você pode:")
        print("1. Usar um cabo loopback (conectar TX ao RX)")
        print("2. Usar software como com0com para criar portas virtuais")
        print("3. Executar este script enquanto o plot_sensors_dual.py está rodando")
        print()
        
        # Simula dados realísticos
        t = 0
        while True:
            # Dados do acelerômetro (simulando movimento)
            ax = 0.1 * math.sin(t * 0.5) + random.uniform(-0.05, 0.05)
            ay = 0.1 * math.cos(t * 0.3) + random.uniform(-0.05, 0.05)
            az = 1.0 + 0.05 * math.sin(t * 0.2) + random.uniform(-0.02, 0.02)
            
            # Dados do magnetômetro (simulando campo magnético terrestre)
            mx = 25.0 + 5.0 * math.sin(t * 0.1) + random.uniform(-2, 2)
            my = 15.0 + 3.0 * math.cos(t * 0.15) + random.uniform(-2, 2)
            mz = -35.0 + 2.0 * math.sin(t * 0.08) + random.uniform(-1, 1)
            
            print(f"Dados simulados:")
            print(f"Acelerômetro: {ax:.3f}, {ay:.3f}, {az:.3f}")
            print(f"Magnetômetro: {mx:.1f}, {my:.1f}, {mz:.1f}")
            print("-" * 40)
            
            t += 0.1
            time.sleep(0.1)  # 10Hz
            
    except KeyboardInterrupt:
        print("\nSimulação interrompida.")
    except Exception as e:
        print(f"Erro: {e}")

if __name__ == "__main__":
    print("=== SIMULADOR DE DADOS DE SENSORES ===")
    print("Este script simula dados para teste do visualizador")
    print("Pressione Ctrl+C para parar\n")
    simulate_sensor_data()
