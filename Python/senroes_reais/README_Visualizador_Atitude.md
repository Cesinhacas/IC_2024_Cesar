# 🛩️ Visualizador de Atitude com Quatérnions

Sistema para visualização em tempo real da atitude de um avião baseado em dados de quatérnions recebidos de um STM32 com sensor 6DOF.

## 📁 Arquivos Criados

### 1. `visualizador_atitude_aviao.py`
**Visualizador principal que recebe dados via porta serial (COM1)**

- Conecta na porta COM1 (configurável)
- Recebe quatérnions no formato: `w,x,y,z`
- Mostra avião 3D em tempo real
- Exibe ângulos de Euler (Roll, Pitch, Yaw)
- Histórico dos ângulos em gráfico

### 2. `simulador_quaternion.py` 
**Simulador para testes sem hardware**

- Gera dados de quatérnion simulados
- Envia via porta serial ou salva em arquivo
- Simula manobras de voo realistas
- Útil para testes da interface

### 3. `visualizador_arquivo_quaternion.py`
**Reproduz dados de um arquivo**

- Lê quatérnions de arquivo texto
- Reproduz a sequência em loop
- Útil para análise de voos gravados

## 🚀 Como Usar

### Opção 1: Com STM32 Real
```bash
# Execute o visualizador principal
python visualizador_atitude_aviao.py
```

**Formato esperado do STM32:**
```
0.998,0.020,-0.015,0.058
0.997,0.022,-0.013,0.061
...
```
Cada linha deve conter: `w,x,y,z` (componentes do quatérnion)

### Opção 2: Teste com Simulador
```bash
# Terminal 1: Execute o simulador
python simulador_quaternion.py
# Escolha opção 2 (Serial)

# Terminal 2: Execute o visualizador
python visualizador_atitude_aviao.py
```

### Opção 3: Reprodução de Arquivo
```bash
# 1. Gere dados simulados
python simulador_quaternion.py
# Escolha opção 1 (Arquivo)

# 2. Reproduza o arquivo
python visualizador_arquivo_quaternion.py
```

## 📋 Requisitos

```bash
pip install numpy matplotlib pyserial
```

## ⚙️ Configuração

### Porta Serial
Para alterar a porta COM, edite no arquivo:
```python
visualizer = QuaternionAttitudeVisualizr(com_port='COM3', baudrate=115200)
```

### Taxa de Atualização
Para alterar a velocidade da animação:
```python
ani = animation.FuncAnimation(self.fig, self.update_plot, interval=50, blit=False)
#                                                               ^^
#                                                          50ms = 20 FPS
```

## 🎯 Funcionalidades

### Interface Principal
- **Visualização 3D**: Avião em perspectiva 3D
- **Informações em Tempo Real**: Quatérnions e ângulos de Euler
- **Histórico**: Gráfico dos últimos 100 pontos
- **Eixos de Referência**: X (vermelho), Y (verde), Z (azul)

### Avião 3D
- **Fuselagem**: Linha azul (nariz → cauda)
- **Asas**: Linha verde (asa esquerda ↔ asa direita)  
- **Cauda Vertical**: Linha vermelha
- **Cauda Horizontal**: Linhas vermelhas

### Ângulos de Euler
- **Roll**: Rotação em torno do eixo X (inclinação lateral)
- **Pitch**: Rotação em torno do eixo Y (subir/descer nariz)
- **Yaw**: Rotação em torno do eixo Z (virar esquerda/direita)

## 🔧 Estrutura do Código STM32

Para enviar dados do seu STM32, use algo como:

```c
// Exemplo de envio via UART
void send_quaternion(float w, float x, float y, float z) {
    char buffer[100];
    sprintf(buffer, "%.6f,%.6f,%.6f,%.6f\r\n", w, x, y, z);
    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 100);
}
```

## 🐛 Solução de Problemas

### "Porta COM não encontrada"
1. Verifique se o STM32 está conectado
2. Confirme a porta no Gerenciador de Dispositivos (Windows)
3. Teste com `python simulador_quaternion.py` primeiro

### "Dados não aparecem"
1. Verifique o formato: deve ser `w,x,y,z`
2. Confirme a taxa de transmissão (115200)
3. Use `monitor_com1.py` para ver dados brutos

### "Interface não atualiza"
1. Verifique se está enviando dados continuamente
2. Taxa recomendada: 10-50 Hz
3. Evite enviar muito rápido (>100 Hz pode travar)

## 📊 Formato dos Dados

### Quatérnion
- **w**: Parte escalar (coseno do meio-ângulo)
- **x, y, z**: Partes vetoriais (seno do meio-ângulo × eixo)
- **Normalização**: |q| = √(w² + x² + y² + z²) = 1

### Ângulos de Euler
- **Roll**: -180° a +180° (inclinação lateral)
- **Pitch**: -90° a +90° (subir/descer)
- **Yaw**: -180° a +180° (direção)

## 📈 Teste de Performance

Use o simulador para verificar:
- Taxa de atualização máxima
- Latência da visualização  
- Estabilidade em execuções longas

```bash
python simulador_quaternion.py
# Escolha opção 3 para testar conversões
```

## 🎮 Controles

- **Mouse**: Rotacionar visualização 3D
- **Scroll**: Zoom in/out
- **Ctrl+C**: Parar execução
- **Fechar janela**: Encerrar programa

---

## 💡 Dicas

1. **Calibração**: Certifique-se que seu sensor está calibrado
2. **Filtros**: Use filtros (Kalman, Complementar) no STM32
3. **Taxa**: 20-30 Hz é ideal para visualização suave
4. **Teste**: Sempre teste com simulador primeiro

---

**Desenvolvido para projetos de determinação de atitude com STM32** 🚁
