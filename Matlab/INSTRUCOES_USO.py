"""
INSTRUÇÕES DE USO - Plot Sensores Dual
=====================================

Este script visualiza dados de acelerômetro e magnetômetro em tempo real.

COMANDOS DISPONÍVEIS:
--------------------
's' + Enter = Salvar dados em arquivos CSV separados
'p' + Enter = Salvar plots como imagem PNG
'c' + Enter = Limpar todos os dados dos gráficos
'q' + Enter = Sair do programa

ARQUIVOS GERADOS:
-----------------

1. DADOS (comando 's'):
   - acelerometro_data_YYYYMMDD_HHMMSS.csv
     Colunas: Timestamp, X_Accel_g, Y_Accel_g, Z_Accel_g
   
   - magnetometro_data_YYYYMMDD_HHMMSS.csv  
     Colunas: Timestamp, X_Mag_mGa, Y_Mag_mGa, Z_Mag_mGa

2. PLOTS (comando 'p'):
   - plots_sensores_YYYYMMDD_HHMMSS.png
     Imagem em alta resolução (300 DPI) dos gráficos 3D

FORMATO DOS DADOS:
------------------
Via COM1, duas linhas alternadas:
Linha 1: ax, ay, az (acelerômetro em g)
Linha 2: mx, my, mz (magnetômetro em miliGauss)

ESCALAS DE REFERÊNCIA:
----------------------
- Acelerômetro: Esfera de 1g (campo gravitacional)
- Magnetômetro: Esfera de 500mGa (campo magnético terrestre típico)

EXEMPLO DE USO:
---------------
1. Execute: python plot_sensors_dual.py
2. Deixe coletando dados por um tempo
3. Digite 's' + Enter para salvar dados
4. Digite 'p' + Enter para salvar imagem dos gráficos
5. Digite 'q' + Enter para sair

Os arquivos serão salvos no mesmo diretório do script.
"""

print(__doc__)
