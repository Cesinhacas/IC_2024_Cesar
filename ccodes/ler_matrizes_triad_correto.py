#!/usr/bin/env python3
"""
Script para ler as 201 matrizes 3x3 do arquivo R_triad_matlab.csv
Formato: 3 linhas, cada uma contendo 603 valores (201 matrizes * 3 elementos por linha)
Cesar - IC 2024
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def ler_matrizes_triad_correto(caminho_arquivo):
    """
    Lê as matrizes 3x3 do arquivo R_triad_matlab.csv no formato correto
    
    O arquivo tem 3 linhas:
    - Linha 1: todos os elementos R[i,0,0], R[i,0,1], R[i,0,2] para i=0..200
    - Linha 2: todos os elementos R[i,1,0], R[i,1,1], R[i,1,2] para i=0..200  
    - Linha 3: todos os elementos R[i,2,0], R[i,2,1], R[i,2,2] para i=0..200
    
    Args:
        caminho_arquivo: caminho para o arquivo CSV
        
    Returns:
        numpy array com shape (201, 3, 3)
    """
    print(f"Lendo arquivo: {caminho_arquivo}")
    
    try:
        # Lê o arquivo CSV
        dados = pd.read_csv(caminho_arquivo, header=None)
        print(f"Dados carregados: {dados.shape[0]} linhas x {dados.shape[1]} colunas")
        
        # Converte para numpy array
        dados_array = dados.to_numpy()
        
        # Verifica o formato
        if dados_array.shape[0] != 3:
            raise ValueError(f"Esperado 3 linhas, encontrado {dados_array.shape[0]}")
            
        num_elementos_por_linha = dados_array.shape[1]
        num_matrizes = num_elementos_por_linha // 3
        
        print(f"Elementos por linha: {num_elementos_por_linha}")
        print(f"Número de matrizes calculado: {num_matrizes}")
        
        if num_elementos_por_linha % 3 != 0:
            print(f"Aviso: número de elementos por linha ({num_elementos_por_linha}) não é divisível por 3")
        
        # Reorganiza os dados
        matrizes = np.zeros((num_matrizes, 3, 3))
        
        for i in range(num_matrizes):
            # Para cada matriz i:
            # Linha 0 da matriz: dados_array[0, i*3:(i+1)*3]
            # Linha 1 da matriz: dados_array[1, i*3:(i+1)*3]  
            # Linha 2 da matriz: dados_array[2, i*3:(i+1)*3]
            
            matrizes[i, 0, :] = dados_array[0, i*3:(i+1)*3]  # Primeira linha da matriz i
            matrizes[i, 1, :] = dados_array[1, i*3:(i+1)*3]  # Segunda linha da matriz i
            matrizes[i, 2, :] = dados_array[2, i*3:(i+1)*3]  # Terceira linha da matriz i
        
        print(f"Formato final das matrizes: {matrizes.shape}")
        return matrizes
        
    except Exception as e:
        print(f"Erro ao ler arquivo: {e}")
        return None

def analisar_matrizes(matrizes):
    """
    Faz análise básica das matrizes carregadas
    """
    if matrizes is None:
        return
    
    print(f"\n{'='*50}")
    print(f"ANÁLISE DAS MATRIZES")
    print(f"{'='*50}")
    
    print(f"Número total de matrizes: {matrizes.shape[0]}")
    print(f"Dimensão de cada matriz: {matrizes.shape[1]}x{matrizes.shape[2]}")
    print(f"Valor mínimo em todas as matrizes: {np.min(matrizes):.8f}")
    print(f"Valor máximo em todas as matrizes: {np.max(matrizes):.8f}")
    print(f"Valor médio: {np.mean(matrizes):.8f}")
    print(f"Desvio padrão: {np.std(matrizes):.8f}")
    
    # Análise específica para matrizes de rotação
    print(f"\n{'='*30}")
    print(f"ANÁLISE DE MATRIZES DE ROTAÇÃO")
    print(f"{'='*30}")
    
    # Calcula determinantes (devem ser ~1 para matrizes de rotação)
    determinantes = np.linalg.det(matrizes)
    print(f"Determinantes - Min: {np.min(determinantes):.8f}, Max: {np.max(determinantes):.8f}")
    print(f"Determinantes - Média: {np.mean(determinantes):.8f}, Std: {np.std(determinantes):.8f}")
    
    # Verifica ortogonalidade: R @ R.T deve ser aproximadamente identidade
    identidades = np.matmul(matrizes, np.transpose(matrizes, (0, 2, 1)))
    identidade_ideal = np.eye(3)
    
    # Calcula o erro em relação à identidade
    erros_ortogonalidade = np.linalg.norm(identidades - identidade_ideal, axis=(1, 2))
    print(f"Erro de ortogonalidade - Min: {np.min(erros_ortogonalidade):.8f}, Max: {np.max(erros_ortogonalidade):.8f}")
    print(f"Erro de ortogonalidade - Média: {np.mean(erros_ortogonalidade):.8f}")
    
    # Mostra algumas matrizes como exemplo
    print(f"\n{'='*20}")
    print(f"EXEMPLOS DE MATRIZES")
    print(f"{'='*20}")
    
    print(f"\nPrimeira matriz (índice 0):")
    print(matrizes[0])
    print(f"Determinante: {determinantes[0]:.8f}")
    print(f"Erro de ortogonalidade: {erros_ortogonalidade[0]:.8f}")
    
    print(f"\nMatriz do meio (índice {len(matrizes)//2}):")
    meio = len(matrizes)//2
    print(matrizes[meio])
    print(f"Determinante: {determinantes[meio]:.8f}")
    print(f"Erro de ortogonalidade: {erros_ortogonalidade[meio]:.8f}")
    
    print(f"\nÚltima matriz (índice {len(matrizes)-1}):")
    print(matrizes[-1])
    print(f"Determinante: {determinantes[-1]:.8f}")
    print(f"Erro de ortogonalidade: {erros_ortogonalidade[-1]:.8f}")
    
    return determinantes, erros_ortogonalidade

def extrair_angulos_euler(matrizes):
    """
    Extrai ângulos de Euler (roll, pitch, yaw) das matrizes de rotação
    Assume convenção ZYX (yaw-pitch-roll)
    """
    num_matrizes = matrizes.shape[0]
    angulos = np.zeros((num_matrizes, 3))  # [roll, pitch, yaw]
    
    for i in range(num_matrizes):
        R = matrizes[i]
        
        # Extração de ângulos de Euler (ZYX)
        # pitch = arcsin(-R[2,0])
        # roll = atan2(R[2,1], R[2,2])
        # yaw = atan2(R[1,0], R[0,0])
        
        # Garante que o valor esteja no domínio do arcsin
        sin_pitch = np.clip(-R[2, 0], -1.0, 1.0)
        pitch = np.arcsin(sin_pitch)
        roll = np.arctan2(R[2, 1], R[2, 2])
        yaw = np.arctan2(R[1, 0], R[0, 0])
        
        angulos[i] = [roll, pitch, yaw]
    
    # Converte de radianos para graus
    angulos_graus = np.degrees(angulos)
    
    print(f"\n{'='*30}")
    print(f"ÂNGULOS DE EULER (GRAUS)")
    print(f"{'='*30}")
    print(f"Roll - Min: {np.min(angulos_graus[:, 0]):.3f}°, Max: {np.max(angulos_graus[:, 0]):.3f}°")
    print(f"Pitch - Min: {np.min(angulos_graus[:, 1]):.3f}°, Max: {np.max(angulos_graus[:, 1]):.3f}°")
    print(f"Yaw - Min: {np.min(angulos_graus[:, 2]):.3f}°, Max: {np.max(angulos_graus[:, 2]):.3f}°")
    
    return angulos, angulos_graus

def plotar_resultados(determinantes, erros_ortogonalidade, angulos_graus):
    """
    Cria gráficos dos resultados
    """
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(12, 10))
    
    # Gráfico 1: Determinantes
    ax1.plot(determinantes, 'b-', linewidth=1)
    ax1.set_title('Determinantes das Matrizes')
    ax1.set_xlabel('Índice da Matriz')
    ax1.set_ylabel('Determinante')
    ax1.grid(True, alpha=0.3)
    ax1.axhline(y=1.0, color='r', linestyle='--', alpha=0.7, label='Ideal = 1.0')
    ax1.legend()
    
    # Gráfico 2: Erros de ortogonalidade
    ax2.plot(erros_ortogonalidade, 'r-', linewidth=1)
    ax2.set_title('Erros de Ortogonalidade')
    ax2.set_xlabel('Índice da Matriz')
    ax2.set_ylabel('Erro (norma)')
    ax2.grid(True, alpha=0.3)
    ax2.set_yscale('log')
    
    # Gráfico 3: Ângulos de Euler
    ax3.plot(angulos_graus[:, 0], 'g-', label='Roll', linewidth=1)
    ax3.plot(angulos_graus[:, 1], 'b-', label='Pitch', linewidth=1)
    ax3.plot(angulos_graus[:, 2], 'm-', label='Yaw', linewidth=1)
    ax3.set_title('Ângulos de Euler')
    ax3.set_xlabel('Índice da Matriz')
    ax3.set_ylabel('Ângulo (graus)')
    ax3.grid(True, alpha=0.3)
    ax3.legend()
    
    # Gráfico 4: Histograma dos determinantes
    ax4.hist(determinantes, bins=30, alpha=0.7, color='blue', edgecolor='black')
    ax4.set_title('Distribuição dos Determinantes')
    ax4.set_xlabel('Determinante')
    ax4.set_ylabel('Frequência')
    ax4.axvline(x=1.0, color='r', linestyle='--', alpha=0.7, label='Ideal = 1.0')
    ax4.grid(True, alpha=0.3)
    ax4.legend()
    
    plt.tight_layout()
    plt.savefig('analise_matrizes_triad.png', dpi=300, bbox_inches='tight')
    print("Gráficos salvos em: analise_matrizes_triad.png")
    
    return fig

def main():
    """
    Função principal
    """
    # Caminho do seu arquivo
    caminho_arquivo = '/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/R_triad_matlab.csv'
    
    # Lê as matrizes
    matrizes = ler_matrizes_triad_correto(caminho_arquivo)
    
    if matrizes is not None:
        # Faz análise
        determinantes, erros_ortogonalidade = analisar_matrizes(matrizes)
        
        # Extrai ângulos de Euler
        angulos_rad, angulos_graus = extrair_angulos_euler(matrizes)
        
        # Cria gráficos
        try:
            fig = plotar_resultados(determinantes, erros_ortogonalidade, angulos_graus)
        except Exception as e:
            print(f"Erro ao criar gráficos: {e}")
        
        print(f"\n{'='*50}")
        print(f"COMO USAR AS MATRIZES NO SEU CÓDIGO")
        print(f"{'='*50}")
        print(f"# Importar e ler as matrizes:")
        print(f"import numpy as np")
        print(f"import pandas as pd")
        print(f"")
        print(f"# Carregar matrizes")
        print(f"dados = pd.read_csv('{caminho_arquivo}', header=None)")
        print(f"dados_array = dados.to_numpy()")
        print(f"num_matrizes = dados_array.shape[1] // 3")
        print(f"matrizes = np.zeros((num_matrizes, 3, 3))")
        print(f"for i in range(num_matrizes):")
        print(f"    matrizes[i, 0, :] = dados_array[0, i*3:(i+1)*3]")
        print(f"    matrizes[i, 1, :] = dados_array[1, i*3:(i+1)*3]")
        print(f"    matrizes[i, 2, :] = dados_array[2, i*3:(i+1)*3]")
        print(f"")
        print(f"# Usar as matrizes:")
        print(f"primeira_matriz = matrizes[0]")
        print(f"matriz_100 = matrizes[100]")
        print(f"ultima_matriz = matrizes[-1]")
        print(f"")
        print(f"# Aplicar rotação a um vetor:")
        print(f"vetor = np.array([1, 0, 0])")
        print(f"vetor_rotacionado = matrizes[0] @ vetor")
        
        # Salva resultados processados
        print(f"\n{'='*30}")
        print(f"SALVANDO RESULTADOS")
        print(f"{'='*30}")
        
        # Salva as matrizes reorganizadas
        np.save('matrizes_triad_reorganizadas.npy', matrizes)
        print("Matrizes reorganizadas salvas em: matrizes_triad_reorganizadas.npy")
        
        # Salva ângulos de Euler
        np.savetxt('angulos_euler_graus.csv', angulos_graus, delimiter=',', 
                   header='roll,pitch,yaw', comments='')
        print("Ângulos de Euler salvos em: angulos_euler_graus.csv")
        
        # Salva determinantes
        np.savetxt('determinantes.csv', determinantes, delimiter=',')
        print("Determinantes salvos em: determinantes.csv")
        
        # Salva erros de ortogonalidade
        np.savetxt('erros_ortogonalidade.csv', erros_ortogonalidade, delimiter=',')
        print("Erros de ortogonalidade salvos em: erros_ortogonalidade.csv")
        
        return matrizes
    else:
        print("Falha ao carregar as matrizes.")
        return None

if __name__ == "__main__":
    matrizes = main()