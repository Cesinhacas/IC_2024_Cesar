import serial
import time

def monitor_rotation_matrix_com1():
    """
    Monitora a porta COM1 para verificar os dados de matriz de rotação sendo enviados
    Formato esperado: 3 linhas por matriz (r11,r12,r13 / r21,r22,r23 / r31,r32,r33)
    """
    try:
        ser = serial.Serial(port='COM1', baudrate=115200, timeout=1)
        print("✓ Conectado na COM1 - Monitorando dados de matriz de rotação...")
        print("Pressione Ctrl+C para parar")
        print("=" * 70)
        
        line_count = 0
        matrix_count = 0
        current_matrix = []
        
        while True:
            if ser.in_waiting > 0:
                try:
                    line = ser.readline().decode('utf-8').strip()
                    if line:
                        line_count += 1
                        
                        # Tenta fazer parsing dos dados
                        try:
                            if ',' in line:
                                coords = [float(x.strip()) for x in line.split(',')]
                            else:
                                coords = [float(x.strip()) for x in line.split()]
                            
                            if len(coords) >= 3:
                                current_matrix.append(coords[:3])
                                
                                # Determina qual linha da matriz
                                row_num = len(current_matrix)
                                row_names = ["", "R1", "R2", "R3"]
                                
                                print(f"🔢 [{line_count:03d}] {row_names[row_num]}: [{coords[0]:+.6f}, {coords[1]:+.6f}, {coords[2]:+.6f}]")
                                
                                # Quando completar uma matriz (3 linhas)
                                if len(current_matrix) >= 3:
                                    matrix_count += 1
                                    print(f"✅ MATRIZ #{matrix_count} COMPLETA:")
                                    for i, row in enumerate(current_matrix):
                                        print(f"   [{row[0]:+.6f}  {row[1]:+.6f}  {row[2]:+.6f}]")
                                    
                                    # Verifica se é uma matriz de rotação válida
                                    try:
                                        import numpy as np
                                        R = np.array(current_matrix)
                                        det = np.linalg.det(R)
                                        is_orthogonal = np.allclose(R @ R.T, np.eye(3), atol=1e-3)
                                        
                                        if abs(det - 1.0) < 0.1 and is_orthogonal:
                                            print(f"   ✅ Matriz válida (det={det:.3f})")
                                        else:
                                            print(f"   ⚠️ Matriz pode estar incorreta (det={det:.3f})")
                                    except:
                                        print(f"   ❓ Não foi possível verificar a matriz")
                                    
                                    print("-" * 70)
                                    current_matrix = []  # Reset para próxima matriz
                            else:
                                print(f"⚠️ [{line_count:03d}] Dados insuficientes: {line}")
                                
                        except ValueError:
                            print(f"⚠️ [{line_count:03d}] Erro ao interpretar: {line}")
                            # Se erro, reseta a matriz atual
                            if current_matrix:
                                print(f"   🔄 Resetando matriz parcial...")
                                current_matrix = []
                        
                except UnicodeDecodeError:
                    print(f"[{line_count:03d}] ⚠️ Dados binários recebidos")
                    line_count += 1
                    
            time.sleep(0.001)  # Pequeno delay
            
    except serial.SerialException as e:
        print(f"❌ Erro na porta serial: {e}")
    except KeyboardInterrupt:
        print(f"\n✓ Monitoramento parado")
        print(f"📊 Estatísticas:")
        print(f"   Linhas recebidas: {line_count}")
        print(f"   Matrizes completas: {matrix_count}")
    except Exception as e:
        print(f"❌ Erro inesperado: {e}")
    finally:
        if 'ser' in locals():
            ser.close()

def test_format():
    """
    Testa o formato de dados esperado
    """
    print("🧪 Testando formato de dados")
    print("=" * 40)
    
    # Simula dados como enviados pelo STM32
    test_matrix = [
        "1.000000, 0.000000, 0.000000",  # Linha 1
        "0.000000, 0.866025, -0.500000", # Linha 2  
        "0.000000, 0.500000, 0.866025"   # Linha 3
    ]
    
    print("Exemplo de matriz de rotação (30° em Y):")
    current_matrix = []
    
    for i, line in enumerate(test_matrix):
        coords = [float(x.strip()) for x in line.split(',')]
        current_matrix.append(coords)
        print(f"R{i+1}: [{coords[0]:+.6f}, {coords[1]:+.6f}, {coords[2]:+.6f}]")
    
    print("\nMatriz completa:")
    for row in current_matrix:
        print(f"   [{row[0]:+.6f}  {row[1]:+.6f}  {row[2]:+.6f}]")

def main():
    """
    Função principal
    """
    print("🛩️ Monitor de Matriz de Rotação - COM1")
    print("=" * 50)
    
    while True:
        print("\nOpções:")
        print("1. Monitorar COM1")
        print("2. Testar formato")
        print("3. Sair")
        
        choice = input("\nEscolha uma opção (1-3): ").strip()
        
        if choice == '1':
            monitor_rotation_matrix_com1()
        elif choice == '2':
            test_format()
        elif choice == '3':
            print("👋 Saindo...")
            break
        else:
            print("❌ Opção inválida")

if __name__ == "__main__":
    main()
