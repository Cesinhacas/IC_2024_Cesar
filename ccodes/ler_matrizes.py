#!/usr/bin/env python3
"""
Script para ler 201 matrizes 3x3 de diferentes formatos de arquivo
Cesar - IC 2024
"""

import numpy as np
import pandas as pd

def ler_matrizes_csv(nome_arquivo):
    """
    Lê matrizes de um arquivo CSV onde cada linha contém os 9 elementos de uma matriz 3x3
    Formato esperado: cada linha tem 9 valores separados por vírgula
    """
    try:
        # Lê o arquivo CSV
        dados = pd.read_csv(nome_arquivo, header=None)
        
        # Converte para numpy array
        dados_array = dados.to_numpy()
        
        num_matrizes = dados_array.shape[0]
        print(f"Número de matrizes encontradas: {num_matrizes}")
        
        # Reshape para criar as matrizes 3x3
        matrizes = dados_array.reshape(num_matrizes, 3, 3)
        
        return matrizes
    
    except Exception as e:
        print(f"Erro ao ler arquivo CSV: {e}")
        return None

def ler_matrizes_txt(nome_arquivo):
    """
    Lê matrizes de um arquivo texto onde cada matriz está em 3 linhas consecutivas
    """
    try:
        with open(nome_arquivo, 'r') as arquivo:
            linhas = arquivo.readlines()
        
        # Remove quebras de linha e converte para float
        dados = []
        for linha in linhas:
            linha = linha.strip()
            if linha:  # Ignora linhas vazias
                valores = [float(x) for x in linha.split()]
                dados.extend(valores)
        
        # Calcula o número de matrizes
        num_elementos = len(dados)
        num_matrizes = num_elementos // 9
        
        print(f"Número de matrizes encontradas: {num_matrizes}")
        
        # Reshape para criar as matrizes 3x3
        dados_array = np.array(dados)
        matrizes = dados_array.reshape(num_matrizes, 3, 3)
        
        return matrizes
    
    except Exception as e:
        print(f"Erro ao ler arquivo TXT: {e}")
        return None

def ler_matrizes_npy(nome_arquivo):
    """
    Lê matrizes de um arquivo .npy (formato binário do NumPy)
    """
    try:
        matrizes = np.load(nome_arquivo)
        print(f"Formato das matrizes: {matrizes.shape}")
        return matrizes
    
    except Exception as e:
        print(f"Erro ao ler arquivo NPY: {e}")
        return None

def ler_matrizes_bin(nome_arquivo, num_matrizes=201):
    """
    Lê matrizes de um arquivo binário
    Assume que os dados são double (8 bytes) em formato little-endian
    """
    try:
        # Lê os dados binários
        dados = np.fromfile(nome_arquivo, dtype=np.float64)
        
        # Verifica se o tamanho está correto
        elementos_esperados = num_matrizes * 9
        if len(dados) != elementos_esperados:
            print(f"Aviso: Esperado {elementos_esperados} elementos, encontrado {len(dados)}")
        
        num_matrizes_real = len(dados) // 9
        print(f"Número de matrizes encontradas: {num_matrizes_real}")
        
        # Reshape para criar as matrizes 3x3
        matrizes = dados.reshape(num_matrizes_real, 3, 3)
        
        return matrizes
    
    except Exception as e:
        print(f"Erro ao ler arquivo binário: {e}")
        return None

def salvar_exemplo_matrizes(nome_arquivo="matrizes_exemplo.csv"):
    """
    Cria um arquivo de exemplo com 201 matrizes 3x3 para teste
    """
    print(f"Criando arquivo de exemplo: {nome_arquivo}")
    
    # Gera 201 matrizes 3x3 aleatórias
    num_matrizes = 201
    matrizes = np.random.rand(num_matrizes, 3, 3)
    
    # Salva no formato CSV (cada linha = uma matriz flatten)
    dados_flatten = matrizes.reshape(num_matrizes, 9)
    pd.DataFrame(dados_flatten).to_csv(nome_arquivo, index=False, header=False)
    
    print(f"Arquivo {nome_arquivo} criado com sucesso!")
    return matrizes

def mostrar_estatisticas(matrizes):
    """
    Mostra estatísticas básicas das matrizes carregadas
    """
    if matrizes is None:
        return
    
    print(f"\n=== ESTATÍSTICAS DAS MATRIZES ===")
    print(f"Formato: {matrizes.shape}")
    print(f"Número de matrizes: {matrizes.shape[0]}")
    print(f"Dimensão de cada matriz: {matrizes.shape[1]}x{matrizes.shape[2]}")
    print(f"Valor mínimo: {np.min(matrizes):.6f}")
    print(f"Valor máximo: {np.max(matrizes):.6f}")
    print(f"Valor médio: {np.mean(matrizes):.6f}")
    print(f"Desvio padrão: {np.std(matrizes):.6f}")
    
    print(f"\n=== PRIMEIRA MATRIZ ===")
    print(matrizes[0])
    
    print(f"\n=== ÚLTIMA MATRIZ ===")
    print(matrizes[-1])

def main():
    """
    Função principal - demonstra como usar as funções de leitura
    """
    print("=== LEITOR DE MATRIZES 3x3 ===")
    print("Este script pode ler matrizes nos seguintes formatos:")
    print("1. CSV - cada linha contém 9 valores de uma matriz")
    print("2. TXT - texto com valores separados por espaço")
    print("3. NPY - formato binário do NumPy")
    print("4. BIN - arquivo binário com doubles")
    print()
    
    # Exemplo de uso - substitua pelo nome do seu arquivo
    nome_arquivo = input("Digite o nome do arquivo (ou pressione Enter para criar exemplo): ").strip()
    
    if not nome_arquivo:
        # Cria um arquivo de exemplo
        matrizes = salvar_exemplo_matrizes()
        nome_arquivo = "matrizes_exemplo.csv"
    
    # Detecta o formato pelo extensão
    if nome_arquivo.endswith('.csv'):
        print(f"Lendo arquivo CSV: {nome_arquivo}")
        matrizes = ler_matrizes_csv(nome_arquivo)
    elif nome_arquivo.endswith('.txt'):
        print(f"Lendo arquivo TXT: {nome_arquivo}")
        matrizes = ler_matrizes_txt(nome_arquivo)
    elif nome_arquivo.endswith('.npy'):
        print(f"Lendo arquivo NPY: {nome_arquivo}")
        matrizes = ler_matrizes_npy(nome_arquivo)
    elif nome_arquivo.endswith('.bin') or nome_arquivo.endswith('.dat'):
        print(f"Lendo arquivo binário: {nome_arquivo}")
        matrizes = ler_matrizes_bin(nome_arquivo)
    else:
        print("Extensão não reconhecida. Tentando como CSV...")
        matrizes = ler_matrizes_csv(nome_arquivo)
    
    # Mostra estatísticas
    mostrar_estatisticas(matrizes)
    
    if matrizes is not None:
        print(f"\nMatrizes carregadas com sucesso!")
        print(f"Use a variável 'matrizes' para acessar os dados.")
        print(f"Exemplo: matrizes[0] para a primeira matriz")
        print(f"         matrizes[-1] para a última matriz")
        print(f"         matrizes[50] para a matriz de índice 50")
        
        # Exemplo de processamento
        print(f"\n=== EXEMPLO DE PROCESSAMENTO ===")
        
        # Calcula determinantes de todas as matrizes
        determinantes = np.linalg.det(matrizes)
        print(f"Determinantes - Min: {np.min(determinantes):.6f}, Max: {np.max(determinantes):.6f}")
        
        # Calcula traços de todas as matrizes
        tracos = np.trace(matrizes, axis1=1, axis2=2)
        print(f"Traços - Min: {np.min(tracos):.6f}, Max: {np.max(tracos):.6f}")

if __name__ == "__main__":
    main()