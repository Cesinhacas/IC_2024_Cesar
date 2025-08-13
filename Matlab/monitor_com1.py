import serial
import time

def monitor_com1():
    """Monitora a porta COM1 para verificar os dados sendo enviados"""
    try:
        ser = serial.Serial(port='COM1', baudrate=115200, timeout=1)
        print("✓ Conectado na COM1 - Monitorando dados...")
        print("Pressione Ctrl+C para parar")
        print("=" * 60)
        
        line_count = 0
        accel_line = True  # Alterna entre linha do acelerômetro e magnetômetro
        
        while True:
            if ser.in_waiting > 0:
                try:
                    line = ser.readline().decode('utf-8').strip()
                    if line:
                        line_count += 1
                        
                        # Identifica o tipo de dado baseado na alternância
                        if accel_line:
                            sensor_type = "ACELERÔMETRO"
                            prefix = "🟢"
                        else:
                            sensor_type = "MAGNETÔMETRO"
                            prefix = "🔵"
                        
                        print(f"{prefix} [{line_count:03d}] {sensor_type}: {line}")
                        accel_line = not accel_line  # Alterna para próxima linha
                        
                        # Tenta fazer parsing dos dados
                        try:
                            if ',' in line:
                                coords = [float(x.strip()) for x in line.split(',')]
                            else:
                                coords = [float(x.strip()) for x in line.split()]
                            
                            if len(coords) >= 3:
                                print(f"   Valores: X={coords[0]:.3f}, Y={coords[1]:.3f}, Z={coords[2]:.3f}")
                        except ValueError:
                            print(f"   ⚠️ Erro ao interpretar dados numéricos")
                        
                        print()
                        
                except UnicodeDecodeError:
                    print(f"[{line_count:03d}] ⚠️ Dados binários recebidos")
                    line_count += 1
                    
            time.sleep(0.01)
            
    except serial.SerialException as e:
        print(f"❌ Erro ao conectar na COM1: {e}")
        print("\nPossíveis soluções:")
        print("1. Verifique se o dispositivo está conectado")
        print("2. Feche outros programas que podem estar usando a porta")
        print("3. Execute como administrador")
        
    except KeyboardInterrupt:
        print("\n\n📊 Monitoramento interrompido.")
        print(f"Total de linhas recebidas: {line_count}")
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Porta COM1 fechada.")
            
    except Exception as e:
        print(f"❌ Erro inesperado: {e}")

if __name__ == "__main__":
    print("=== MONITOR COM1 ===")
    print("Este script monitora os dados sendo enviados via COM1")
    print("Formato esperado:")
    print("Linha 1: ax, ay, az")
    print("Linha 2: mx, my, mz")
    print()
    monitor_com1()
