# 🧭 Sistema de Visualização de Esferas - Duplo Magnetômetro

## 📋 Visão Geral

Este sistema permite visualizar dados brutos de dois magnetômetros como pontos 3D em esferas de referência, facilitando a análise de calibração e comparação entre sensores.

## 🎯 Características Principais

- **Visualização 3D**: Dados plotados como pontos coloridos em esferas de referência
- **Duplo Magnetômetro**: Suporte para comparação simultânea de dois sensores
- **Análise Temporal**: Gradiente de cores mostra evolução temporal dos dados
- **Métricas em Tempo Real**: Magnitude, médias e estatísticas de cada sensor
- **Formatos Flexíveis**: Suporte para dados com/sem identificadores

## 📁 Arquivos do Sistema

### Python (Visualização)
- `visualizador_esferas_dual_magnetometro.py` - Visualizador principal
- `simulador_esferas_dual_magnetometro.py` - Simulador para testes

### STM32 (Aquisição)
- `dual_magnetometer_raw.c` - Código de exemplo para STM32

## 🚀 Como Usar

### 1. Preparação do Ambiente Python

```bash
# Instalar dependências
pip install matplotlib numpy pyserial

# Verificar versões
python --version  # Testado com Python 3.12.10
```

### 2. Configuração do STM32

#### Hardware Necessário:
- STM32 (F4, F7 ou similar)
- 2x Magnetômetros (HMC5883L, QMC5883L, LSM303, etc.)
- Conexão UART (USB-Serial ou ST-Link)

#### Conexões Típicas:
```
Magnetômetro 1:    Magnetômetro 2:
VCC → 3.3V         VCC → 3.3V
GND → GND          GND → GND
SDA → PB7 (I2C1)   SDA → PB11 (I2C2) ou usar endereços diferentes
SCL → PB6 (I2C1)   SCL → PB10 (I2C2)
```

#### Configuração CubeMX:
1. **UART1**: 115200 baud, 8N1
2. **I2C1/I2C2**: 100-400 kHz
3. **GPIO**: Configure pinos conforme hardware
4. **Clock**: Configure para performance adequada

### 3. Formatos de Dados Suportados

#### Formato 1: Com Identificadores (Recomendado)
```
MAG1
25.123, -15.456, 48.789
MAG2
23.567, -12.890, 51.234
MAG1
24.890, -15.123, 49.001
MAG2
23.234, -13.456, 50.789
```

#### Formato 2: Dados Alternados
```
25.123, -15.456, 48.789
23.567, -12.890, 51.234
24.890, -15.123, 49.001
23.234, -13.456, 50.789
```

### 4. Executando o Sistema

#### Opção A: Com Dados Reais (STM32)
```bash
# 1. Conectar STM32 via USB/Serial
# 2. Executar visualizador
python visualizador_esferas_dual_magnetometro.py

# 3. Configurar porta COM quando solicitado
# Exemplo: COM3, COM7, etc.
```

#### Opção B: Com Simulador (Teste)
```bash
# Terminal 1: Executar simulador
python simulador_esferas_dual_magnetometro.py
# Escolher opção 3 ou 4 (serial)

# Terminal 2: Executar visualizador
python visualizador_esferas_dual_magnetometro.py
# Usar mesma porta COM do simulador
```

## 🎨 Interface do Visualizador

### Elementos da Tela:
1. **Duas Esferas 3D**: Uma para cada magnetômetro
2. **Pontos Coloridos**: Dados com gradiente temporal (azul→vermelho)
3. **Informações em Tempo Real**:
   - Magnitude atual de cada sensor
   - Médias móveis
   - Contadores de amostras
   - Status da conexão

### Controles:
- **Mouse**: Rotacionar visualização 3D
- **Scroll**: Zoom in/out
- **Ctrl+C**: Parar coleta de dados

## 🔧 Calibração de Magnetômetros

### Processo de Calibração:

1. **Coleta de Dados**:
   ```bash
   # Executar sistema de visualização
   # Rotacionar sensores em TODAS as direções
   # Coletar dados por 2-3 minutos
   ```

2. **Identificação de Problemas**:
   - **Hard Iron**: Esfera deslocada do centro
   - **Soft Iron**: Esfera distorcida (elíptica)
   - **Ruído**: Pontos muito dispersos

3. **Análise Visual**:
   - Esfera ideal: pontos formam esfera perfeita centrada
   - Problemas: assimetrias, deslocamentos, distorções

### Cálculo de Offsets (Hard Iron):
```c
// No código STM32, após coleta de dados de calibração:
float offset_x = (max_x + min_x) / 2.0f;
float offset_y = (max_y + min_y) / 2.0f;
float offset_z = (max_z + min_z) / 2.0f;

// Aplicar correção:
mag_calibrated_x = mag_raw_x - offset_x;
mag_calibrated_y = mag_raw_y - offset_y;
mag_calibrated_z = mag_raw_z - offset_z;
```

## 🔍 Análise de Dados

### Métricas Importantes:

1. **Magnitude do Campo**:
   - Típico: 25-65 μT (varia por localização)
   - Estável: variação < 5%
   - Problemas: grandes oscilações

2. **Distribuição Espacial**:
   - Ideal: pontos uniformemente distribuídos na esfera
   - Problemas: clusters, vazios, assimetrias

3. **Consistência Entre Sensores**:
   - Magnitudes similares (diferença < 10%)
   - Padrões de movimento coerentes
   - Sincronização temporal

### Solução de Problemas:

| Problema | Sintoma Visual | Solução |
|----------|----------------|---------|
| Hard Iron | Esfera deslocada | Calcular e aplicar offsets |
| Soft Iron | Esfera elíptica | Matriz de correção 3x3 |
| Ruído elétrico | Pontos dispersos | Filtro passa-baixa |
| Interferência | Distorções locais | Afastar fontes magnéticas |
| Saturação | Pontos "colados" | Reduzir ganho do sensor |

## 📊 Parâmetros de Configuração

### No Visualizador Python:
```python
# Modificar em visualizador_esferas_dual_magnetometro.py
SPHERE_RADIUS = 50.0        # Raio da esfera de referência (μT)
BUFFER_SIZE = 500           # Número de pontos mostrados
UPDATE_INTERVAL = 50        # ms entre atualizações
MAX_MAGNITUDE = 100.0       # Limite máximo para escala
```

### No STM32:
```c
// Modificar em dual_magnetometer_raw.c
#define TRANSMISSION_RATE_MS 100    // Taxa de envio (10 Hz)
#define MAG_SCALE_FACTOR 0.15f      // Conversão LSB → μT
#define MAX_MAG_VALUE 4000          // Saturação do sensor
```

## 🎯 Aplicações Específicas

### 1. Desenvolvimento de IMU:
- Validação de algoritmos de fusão
- Comparação entre diferentes sensores
- Teste de robustez em ambiente ruidoso

### 2. Calibração Industrial:
- Compensação de hard/soft iron
- Validação de procedimentos de calibração
- Controle de qualidade em produção

### 3. Pesquisa Acadêmica:
- Análise de interferências magnéticas
- Desenvolvimento de novos algoritmos
- Comparação de tecnologias de sensores

## 🚨 Limitações e Considerações

### Performance:
- **Máximo**: ~50 Hz com 2 sensores
- **Recomendado**: 10-20 Hz para visualização suave
- **Buffer**: Limitar pontos para evitar lag

### Hardware:
- **Resolução**: Depende do sensor (12-16 bits típico)
- **Ruído**: Filtros analógicos/digitais recomendados
- **Temperatura**: Compensação pode ser necessária

### Software:
- **Memória**: ~100 MB RAM para operação normal
- **CPU**: Uso moderado com matplotlib
- **Compatibilidade**: Windows/Linux/macOS

## 📞 Suporte e Desenvolvimento

### Autor: Cesar - IC 2024
### Contato: [Inserir informações de contato]

### Versão: 1.0 - Janeiro 2025

### Próximas Melhorias:
- [ ] Exportação de dados para análise offline
- [ ] Filtros configuráveis em tempo real
- [ ] Detecção automática de problemas de calibração
- [ ] Suporte para mais de 2 magnetômetros
- [ ] Interface web para monitoramento remoto

---

## 📄 Exemplo de Uso Rápido

```bash
# 1. Preparar ambiente
git clone [repositório]
cd IC_2024_Cesar/Python
pip install -r requirements.txt

# 2. Testar com simulador
python simulador_esferas_dual_magnetometro.py
# Escolher opção 3 (serial com identificadores)
# Usar porta COM1

# 3. Em outro terminal
python visualizador_esferas_dual_magnetometro.py
# Inserir COM1 quando solicitado
# Observar esferas sendo preenchidas com dados

# 4. Para uso real
# Programar STM32 com dual_magnetometer_raw.c
# Conectar via USB/Serial
# Repetir passo 3 com porta real
```

**🎉 Sistema pronto para uso! Boa sorte com seus projetos!**
