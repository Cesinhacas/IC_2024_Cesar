# 🛩️ Visualizador de Atitude - Dois Magnetômetros

## 📡 Formatos de Dados Suportados

### Formato 1: Com Identificadores (Recomendado)
```
MAG1
0.998195, -0.060059, 0.001200
0.060059, 0.997988, 0.017453
-0.000000, -0.017499, 0.999847
MAG2
0.995372, -0.095846, 0.009613
0.095932, 0.995329, 0.008727
-0.008814, -0.009565, 0.999916
```

### Formato 2: Sequência Alternada
```
0.998195, -0.060059, 0.001200  # Mag1 linha 1
0.060059, 0.997988, 0.017453   # Mag1 linha 2
-0.000000, -0.017499, 0.999847 # Mag1 linha 3
0.995372, -0.095846, 0.009613  # Mag2 linha 1
0.095932, 0.995329, 0.008727   # Mag2 linha 2
-0.008814, -0.009565, 0.999916 # Mag2 linha 3
```

## 🚀 Como Usar

### 1. **Visualizador Principal**
```bash
python visualizador_dual_magnetometro.py
```
- Mostra dois aviões lado a lado
- Magnetômetro 1: cores azul/verde/vermelho
- Magnetômetro 2: cores ciano/magenta/laranja
- FPS e contador de dados em cada painel

### 2. **Teste com Simulador**
```bash
# Terminal 1: Simulador
python simulador_dual_magnetometro.py
# Escolha formato e método de envio

# Terminal 2: Visualizador
python visualizador_dual_magnetometro.py
```

### 3. **Monitorar Dados**
```bash
python monitor_matriz_rotacao.py  # Funciona com dados dual também
```

## ⚙️ Configuração no STM32

### Opção 1: Com Identificadores
```c
// Envia identificador do magnetômetro
sprintf(uart_buffer, "MAG1\n");
HAL_UART_Transmit(&huart1, (uint8_t*)uart_buffer, strlen(uart_buffer), 100);

// Envia matriz linha por linha
for (int row = 0; row < 3; row++) {
    sprintf(uart_buffer, "%.6f, %.6f, %.6f\n", 
           attitude1[row][0], attitude1[row][1], attitude1[row][2]);
    HAL_UART_Transmit(&huart1, (uint8_t*)uart_buffer, strlen(uart_buffer), 100);
}

// Repete para MAG2
sprintf(uart_buffer, "MAG2\n");
HAL_UART_Transmit(&huart1, (uint8_t*)uart_buffer, strlen(uart_buffer), 100);
// ... matriz do magnetômetro 2
```

### Opção 2: Sequência Alternada
```c
// Envia primeiro magnetômetro (3 linhas)
for (int row = 0; row < 3; row++) {
    sprintf(uart_buffer, "%.6f, %.6f, %.6f\n", 
           attitude1[row][0], attitude1[row][1], attitude1[row][2]);
    HAL_UART_Transmit(&huart1, (uint8_t*)uart_buffer, strlen(uart_buffer), 100);
}

// Envia segundo magnetômetro (3 linhas)
for (int row = 0; row < 3; row++) {
    sprintf(uart_buffer, "%.6f, %.6f, %.6f\n", 
           attitude2[row][0], attitude2[row][1], attitude2[row][2]);
    HAL_UART_Transmit(&huart1, (uint8_t*)uart_buffer, strlen(uart_buffer), 100);
}
```

## 🔧 Processamento dos Dois Magnetômetros

### 1. **Normalização Individual**
```c
// Normalizar cada magnetômetro separadamente
float mag1_norm = normalize_vector(&mag1_data);
float mag2_norm = normalize_vector(&mag2_data);
```

### 2. **Cálculo de Atitude Independente**
```c
// Calcular atitude para cada magnetômetro
calculate_attitude_triad(&acc_data, &mag1_normalized, attitude1);
calculate_attitude_triad(&acc_data, &mag2_normalized, attitude2);
```

### 3. **Validação Cruzada**
```c
// Comparar resultados dos dois magnetômetros
float attitude_diff = compare_attitudes(attitude1, attitude2);
if (attitude_diff > THRESHOLD) {
    // Possível interferência magnética ou falha
    use_backup_attitude();
}
```

## 📊 Vantagens do Sistema Dual

### ✅ **Redundância**
- Se um magnetômetro falhar, o outro continua
- Detecção de interferências magnéticas locais
- Maior confiabilidade do sistema

### ✅ **Validação Cruzada**
- Comparação entre leituras dos dois sensores
- Identificação de anomalias magnéticas
- Melhoria da precisão por fusão de dados

### ✅ **Diferentes Posicionamentos**
- Magnetômetros em posições diferentes no veículo
- Menor susceptibilidade a interferências locais
- Cobertura magnética mais ampla

## 🐛 Solução de Problemas

### Problema: "Só um avião se move"
**Possíveis causas:**
1. Dados de apenas um magnetômetro chegando
2. Identificadores MAG1/MAG2 incorretos
3. Sequência de dados incompleta

**Solução:**
1. Verificar formato de envio no STM32
2. Usar monitor para ver dados brutos
3. Conferir se 6 linhas consecutivas são enviadas

### Problema: "Aviões com movimentos muito diferentes"
**Possíveis causas:**
1. Magnetômetros em posições muito distantes
2. Interferência magnética local em um dos sensores
3. Calibração diferente entre sensores

**Solução:**
1. Verificar calibração individual de cada magnetômetro
2. Analisar ambiente magnético ao redor dos sensores
3. Implementar validação cruzada no código

### Problema: "Performance ruim"
**Solução:**
1. Reduzir taxa de envio para 5-10 Hz
2. Usar formato sem identificadores (mais eficiente)
3. Verificar se está enviando dados muito rapidamente

## 📈 Análise Comparativa

### Interface Visual:
- **Painel Esquerdo**: Magnetômetro 1 (azul/verde/vermelho)
- **Painel Direito**: Magnetômetro 2 (ciano/magenta/laranja)
- **Títulos**: Mostram FPS e quantidade de dados recebidos

### Métricas:
- Taxa de atualização individual para cada magnetômetro
- Contador de matrizes recebidas
- Performance geral do sistema

## 💡 Dicas de Implementação

### 1. **Sincronização**
```c
// Enviar dados dos dois magnetômetros em sequência
read_both_magnetometers();
calculate_both_attitudes();
send_both_attitudes();
HAL_Delay(100);  // 10 Hz
```

### 2. **Filtros Individuais**
```c
// Aplicar filtro independente para cada magnetômetro
filter_magnetometer_1(&mag1_raw, &mag1_filtered);
filter_magnetometer_2(&mag2_raw, &mag2_filtered);
```

### 3. **Validação de Dados**
```c
if (validate_magnetometer_data(&mag1_data) && 
    validate_magnetometer_data(&mag2_data)) {
    // Ambos os dados são válidos
    send_dual_attitude();
}
```

---

## 🎯 Resultado Esperado

Você verá dois aviões 3D lado a lado, cada um representando a atitude calculada por um magnetômetro diferente. Isso permite:

- **Comparação visual** das leituras
- **Validação** da consistência entre sensores  
- **Análise** de interferências magnéticas
- **Redundância** para maior confiabilidade

**Perfect para sistemas de navegação críticos!** ✈️🧭
