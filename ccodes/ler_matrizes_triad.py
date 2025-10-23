#!/usr/bin/env python3
"""
Script para ler as 201 matrizes 3x3 do arquivo R_triad_matlab.csv
Cesar - IC 2024
"""

import numpy as np
import pandas as pd

def ler_matrizes_triad(caminho_arquivo):
    """
    Lê as matrizes 3x3 do arquivo R_triad_matlab.csv
    
    Args:
        caminho_arquivo: caminho para o arquivo CSV
        
    Returns:
        numpy array com shape (num_matrizes, 3, 3)
    """
    print(f"Lendo arquivo: {caminho_arquivo}")
    
    try:
        # Lê o arquivo CSV
        dados = pd.read_csv(caminho_arquivo, header=None)
        print(f"Dados carregados: {dados.shape[0]} linhas x {dados.shape[1]} colunas")
        
        # Converte para numpy array
        dados_array = dados.to_numpy()
        
        # Verifica se cada linha tem 9 elementos (3x3 = 9)
        if dados_array.shape[1] != 9:
            raise ValueError(f"Esperado 9 colunas por linha, encontrado {dados_array.shape[1]}")
        
        num_matrizes = dados_array.shape[0]
        print(f"Número de matrizes encontradas: {num_matrizes}")
        
        # Reshape para criar as matrizes 3x3
        # Cada linha do CSV vira uma matriz 3x3
        matrizes = dados_array.reshape(num_matrizes, 3, 3)
        
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
        
        pitch = np.arcsin(-R[2, 0])
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

def main():
    """
    Função principal
    """
    # Caminho do seu arquivo
    caminho_arquivo = '/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/R_triad_matlab.csv'
    
    # Lê as matrizes
    matrizes = ler_matrizes_triad(caminho_arquivo)
    
    if matrizes is not None:
        # Faz análise
        determinantes, erros_ortogonalidade = analisar_matrizes(matrizes)
        
        # Extrai ângulos de Euler
        angulos_rad, angulos_graus = extrair_angulos_euler(matrizes)
        
        print(f"\n{'='*50}")
        print(f"COMO USAR AS MATRIZES NO SEU CÓDIGO")
        print(f"{'='*50}")
        print(f"# Acessar matriz específica:")
        print(f"primeira_matriz = matrizes[0]")
        print(f"matriz_100 = matrizes[100]")
        print(f"ultima_matriz = matrizes[-1]")
        print()
        print(f"# Aplicar rotação a um vetor:")
        print(f"vetor = np.array([1, 0, 0])")
        print(f"vetor_rotacionado = matrizes[0] @ vetor")
        print()
        print(f"# Iterar sobre todas as matrizes:")
        print(f"for i, matriz in enumerate(matrizes):")
        print(f"    print(f'Matriz {{i}}: determinante = {{np.linalg.det(matriz):.6f}}')")
        
        # Salva resultados processados
        print(f"\n{'='*30}")
        print(f"SALVANDO RESULTADOS")
        print(f"{'='*30}")
        
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