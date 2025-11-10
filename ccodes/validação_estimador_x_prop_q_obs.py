import numpy as np
import pandas as pd
import ctypes

# --- 1. Carregar Bibliotecas e Definir Argtypes Corretamente ---
# (Note a correção no FK_prop, que recebe 6 argumentos, não 7)

my_atitude = ctypes.CDLL('./atitude.so')
my_FK = ctypes.CDLL('./FK.so')

# TRIAD: (v1, v2, w1, w2, q_out, var_accel, var_mag, R_out)
my_atitude.TRIAD.argtypes = [ctypes.POINTER(ctypes.c_double), 
                            ctypes.POINTER(ctypes.c_double), 
                            ctypes.POINTER(ctypes.c_double), 
                            ctypes.POINTER(ctypes.c_double), 
                            ctypes.POINTER(ctypes.c_double), 
                            ctypes.c_double, 
                            ctypes.c_double, 
                            ctypes.POINTER(ctypes.c_double)]
my_atitude.TRIAD.restype = ctypes.c_void_p

# FK_prop: (u_gyro, Dt, PT_est_in, x_est_in, x_prop_out, PT_prop_out)
my_FK.FK_prop.argtypes = [ctypes.POINTER(ctypes.c_double), 
                          ctypes.c_double, 
                          ctypes.POINTER(ctypes.c_double), 
                          ctypes.POINTER(ctypes.c_double), 
                          ctypes.POINTER(ctypes.c_double), 
                          ctypes.POINTER(ctypes.c_double)]
my_FK.FK_prop.restype = ctypes.c_void_p

# FK_estimador: (x_prop_in, PT_prop_in, q_obs_in, R_obs_in, iteracao, x_est_out, PT_est_out, P_est_out)
my_FK.FK_estimador.argtypes = [ctypes.POINTER(ctypes.c_double), 
                              ctypes.POINTER(ctypes.c_double), 
                              ctypes.POINTER(ctypes.c_double), 
                              ctypes.POINTER(ctypes.c_double), 
                              ctypes.c_int, 
                              ctypes.POINTER(ctypes.c_double), 
                              ctypes.POINTER(ctypes.c_double), 
                              ctypes.POINTER(ctypes.c_double)]
my_FK.FK_estimador.restype = ctypes.c_void_p

my_FK.main.argtypes = []
my_FK.main.restype = ctypes.c_int

# --- 2. Carregar Dados de Sensores (Inputs do Simulador) ---

# Não carregamos mais x_prop.csv ou PT_prop.csv, pois eles serão calculados
dados_accel = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Accel_cinematica.csv', header=None).to_numpy().transpose()
dados_mag = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/Mag_cinematica.csv', header=None).to_numpy().transpose()
dados_gyro = pd.read_csv('/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/gyro_cinematica.csv', header=None).to_numpy().transpose()

num_exe = len(dados_accel[0])
Dt = 0.05
print(f"Iniciando integração do filtro para {num_exe} iterações.")

# --- 3. Inicialização dos Vetores de Referência (TRIAD) ---
v1 = np.array([0, 1.0, 0], dtype=np.float64)
v2 = np.array([1/np.sqrt(2), 0, 1/np.sqrt(2)], dtype=np.float64)
v1_ptr = v1.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
v2_ptr = v2.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

# --- 4. Inicialização dos Estados e Buffers do Filtro ---

# ESTADO ESTIMADO (O estado final de cada loop, entrada do próximo)
# Estes arrays serão atualizados em C (in-place)
x_est = np.array([0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0], dtype=np.float64)
PT_est = 1e6 * np.eye(6, dtype=np.float64) 

# BUFFERS DE SAÍDA (Serão preenchidos pelas funções C)
x_prop = np.zeros(7, dtype=np.float64)
PT_prop = np.zeros((6, 6), dtype=np.float64)
q_obs = np.zeros(4, dtype=np.float64)
R_obs = np.zeros((3, 3), dtype=np.float64)
P_est_full = np.zeros((7, 7), dtype=np.float64) # Covariância 7x7 completa

# Ponteiros para os arrays
x_est_ptr = x_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
PT_est_ptr = PT_est.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
x_prop_ptr = x_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
PT_prop_ptr = PT_prop.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
q_ptr = q_obs.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
R_ptr = R_obs.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
P_est_ptr = P_est_full.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

# Buffers de INPUT (Atualizados a cada loop)
g_input = np.zeros(3, dtype=np.float64)
w1_input = np.zeros(3, dtype=np.float64)
w2_input = np.zeros(3, dtype=np.float64)
g_ptr = g_input.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
w1_ptr = w1_input.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
w2_ptr = w2_input.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

# Arrays de armazenamento de resultados (Python)
estados_estimados_hist = np.zeros((num_exe, 7))
covariancias_estimadas_hist = np.zeros((num_exe, 7, 7))
covarianciasT_estimadas_hist = np.zeros((num_exe, 6, 6))

# Inicializa as variáveis globais em C (QT, GT, etc.)
my_FK.main()

# --- 5. Loop de Integração do Filtro de Kalman ---

for i in range(num_exe):
    
    # Carrega dados dos sensores para a iteração atual
    g_input[:] = dados_gyro[:, i]
    w1_input[:] = dados_accel[:, i]
    w2_input[:] = dados_mag[:, i]

    # ETAPA 1: PROPAGAÇÃO (Predict)
    # Usa o estado estimado (x_est, PT_est) do loop ANTERIOR (ou inicial)
    # Calcula o estado propagado (x_prop, PT_prop)
    my_FK.FK_prop(g_ptr, 
                  ctypes.c_double(Dt), 
                  PT_est_ptr,  # Input (Estimado do passo i-1)
                  x_est_ptr,   # Input (Estimado do passo i-1)
                  x_prop_ptr,  # Output
                  PT_prop_ptr) # Output

    # ETAPA 2: OBSERVAÇÃO (Measure)
    # Obtém a medição do TRIAD (q_obs, R_obs)
    my_atitude.TRIAD(v1_ptr, 
                     v2_ptr, 
                     w1_ptr, 
                     w2_ptr, 
                     q_ptr,    # Output
                     0.01, 
                     0.01, 
                     R_ptr)    # Output

    # ETAPA 3: ESTIMAÇÃO (Update)
    # Usa o estado propagado (x_prop, PT_prop) da ETAPA 1
    # Usa a observação (q_obs, R_obs) da ETAPA 2
    # Calcula o novo estado estimado (x_est, PT_est) para o passo ATUAL (i)
    
    cont = i + 1 # Passa o número da iteração (base 1)

    my_FK.FK_estimador(x_prop_ptr,  # Input (Propagado da Etapa 1)
                       PT_prop_ptr, # Input (Propagado da Etapa 1)
                       q_ptr,       # Input (Observação da Etapa 2)
                       R_ptr,       # Input (Observação da Etapa 2)
                       cont,
                       x_est_ptr,   # Output (Estimado do passo i)
                       PT_est_ptr,  # Output (Estimado do passo i)
                       P_est_ptr)   # Output (Estimado do passo i)

    # Os ponteiros x_est_ptr e PT_est_ptr agora apontam para os dados
    # atualizados, que serão usados na ETAPA 1 do *próximo* loop.

    # Armazena os resultados estimados do passo 'i'
    estados_estimados_hist[i] = x_est.copy()
    covariancias_estimadas_hist[i] = P_est_full.copy()
    covarianciasT_estimadas_hist[i] = PT_est.copy()

    if cont % 20 == 0:
        print(f"Iteração {cont}/{num_exe} completa.")

print("Simulação concluída.")

# --- 6. Salvamento dos Resultados ---

output_path = '/mnt/c/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab/Dados_simula_atitude/'

estados_estimados_df = pd.DataFrame(estados_estimados_hist)
estados_estimados_df.to_csv(output_path + 'estados_estimados_c_INTEGRADO.csv', header=False, index=False)

covariancias_estimadas_df = pd.DataFrame(covariancias_estimadas_hist.reshape(num_exe, 49))
covariancias_estimadas_df.to_csv(output_path + 'cov_triad_est_c_INTEGRADO.csv', header=False, index=False)

covarianciasT_estimadas_df = pd.DataFrame(covarianciasT_estimadas_hist.reshape(num_exe, 36))
covarianciasT_estimadas_df.to_csv(output_path + 'covT_triad_est_c_INTEGRADO.csv', header=False, index=False)

print("Resultados salvos.")