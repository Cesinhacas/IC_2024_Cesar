import serial
import serial.tools.list_ports
import time

def list_available_ports():
    """Lista todas as portas COM disponíveis"""
    ports = serial.tools.list_ports.comports()
    available_ports = []
    
    print("Portas COM encontradas:")
    print("-" * 50)
    
    for port in ports:
        print(f"Porta: {port.device}")
        print(f"Descrição: {port.description}")
        print(f"Hardware ID: {port.hwid}")
        print("-" * 50)
        available_ports.append(port.device)
    
    return available_ports

def test_port(port_name, baudrate=115200):
    """Testa se uma porta pode ser aberta"""
    try:
        ser = serial.Serial(port=port_name, baudrate=baudrate, timeout=1)
        print(f"✓ Porta {port_name} aberta com sucesso!")
        ser.close()
        return True
    except serial.SerialException as e:
        print(f"✗ Erro ao abrir porta {port_name}: {e}")
        return False
    except Exception as e:
        print(f"✗ Erro inesperado ao testar porta {port_name}: {e}")
        return False

def find_working_port(baudrate=115200):
    """Encontra a primeira porta que funciona"""
    available_ports = list_available_ports()
    
    if not available_ports:
        print("Nenhuma porta COM encontrada!")
        return None
    
    print("\nTestando portas...")
    print("-" * 30)
    
    for port in available_ports:
        if test_port(port, baudrate):
            return port
    
    print("Nenhuma porta funcionando encontrada!")
    return None

def monitor_port_data(port_name, baudrate=115200, duration=10):
    """Monitora dados de uma porta por alguns segundos"""
    try:
        ser = serial.Serial(port=port_name, baudrate=baudrate, timeout=1)
        print(f"\nMonitorando porta {port_name} por {duration} segundos...")
        print("Pressione Ctrl+C para parar")
        print("-" * 50)
        
        start_time = time.time()
        line_count = 0
        
        while (time.time() - start_time) < duration:
            if ser.in_waiting > 0:
                try:
                    line = ser.readline().decode('utf-8').strip()
                    if line:
                        line_count += 1
                        print(f"[{line_count:03d}] {line}")
                except UnicodeDecodeError:
                    print(f"[{line_count:03d}] <dados binários>")
            time.sleep(0.1)
        
        ser.close()
        print(f"\nMonitoramento concluído. {line_count} linhas recebidas.")
        
    except KeyboardInterrupt:
        print("\nMonitoramento interrompido pelo usuário.")
        if 'ser' in locals() and ser.is_open:
            ser.close()
    except Exception as e:
        print(f"Erro durante o monitoramento: {e}")

if __name__ == "__main__":
    print("=== DETECTOR DE PORTAS COM ===")
    print()
    
    # Encontra uma porta que funciona
    working_port = find_working_port()
    
    if working_port:
        print(f"\n🎉 Porta recomendada: {working_port}")
        
        # Pergunta se quer monitorar os dados
        response = input(f"\nDeseja monitorar os dados da porta {working_port}? (s/n): ").lower()
        if response in ['s', 'sim', 'y', 'yes']:
            monitor_port_data(working_port)
    else:
        print("\n❌ Nenhuma porta COM funcional encontrada.")
        print("\nPossíveis soluções:")
        print("1. Verifique se o dispositivo está conectado")
        print("2. Instale os drivers necessários")
        print("3. Execute como administrador")
        print("4. Verifique se outro programa está usando a porta")
