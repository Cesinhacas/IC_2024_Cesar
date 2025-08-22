# 🛩️ Visualizador de Atitude - Formato Linha por Linha

## 📡 Formato de Dados do STM32

Seu STM32 está enviando a matriz de rotação em **3 transmissões separadas**:

```c
sprintf((char*)data_to_send, "%f, %f, %f\n", atitude[0][0], atitude[0][1], atitude[0][2]);
sprintf((char*)data_to_send, "%f, %f, %f\n", atitude[1][0], atitude[1][1], atitude[1][2]);
sprintf((char*)data_to_send, "%f, %f, %f\n", atitude[2][0], atitude[2][1], atitude[2][2]);
```

### Exemplo de dados recebidos:
```
0.998195, -0.060059, 0.001200
0.060059, 0.997988, 0.017453
-0.000000, -0.017499, 0.999847
```

## 🚀 Como Usar

### 1. **Monitor de Dados** (verificar se está funcionando)
```bash
python monitor_matriz_rotacao.py
```
- Escolha opção 1 para monitorar COM1
- Verifica se os dados estão chegando no formato correto
- Valida se as matrizes são matrizes de rotação válidas

### 2. **Visualizador Principal**
```bash
python visualizador_matriz_rotacao.py
```
- Conecta automaticamente na COM1
- Mostra o avião 3D em tempo real
- FPS contador no título da janela

### 3. **Teste com Simulador**
```bash
# Terminal 1: Simulador
python simulador_matriz_rotacao.py
# Escolha opção 2 (Serial)

# Terminal 2: Visualizador  
python visualizador_matriz_rotacao.py
```

## ⚙️ Configurações

### No STM32:
- **Porta**: COM1 (pode ser alterada no código Python)
- **Baudrate**: 115200
- **Formato**: 3 linhas por matriz, separadas por vírgula e espaço

### Taxa de Envio Recomendada:
```c
HAL_Delay(100);  // 10 Hz - ideal para visualização suave
```

## 🔧 Adaptações no Código

O visualizador foi adaptado para:

1. **Receber 3 linhas por matriz**:
   - Linha 1: `r11, r12, r13`
   - Linha 2: `r21, r22, r23`
   - Linha 3: `r31, r32, r33`

2. **Reconstituir a matriz automaticamente**:
   - Aguarda receber as 3 linhas
   - Monta a matriz 3x3
   - Aplica ao modelo 3D do avião

3. **Validação automática**:
   - Verifica se recebeu exatamente 3 valores por linha
   - Ignora linhas mal formatadas
   - Reseta buffer se houver inconsistência

## 🐛 Solução de Problemas

### Problema: "Dados não aparecem"
**Solução:**
1. Use o monitor: `python monitor_matriz_rotacao.py`
2. Verifique se está recebindo exatamente 3 valores por linha
3. Confirme se são 3 linhas consecutivas

### Problema: "Avião não se move"
**Possíveis causas:**
1. Matriz identidade (sem rotação)
2. Dados inconsistentes
3. Taxa muito rápida (>50 Hz pode travar)

### Problema: "Performance ruim"
**Soluções:**
1. Reduza taxa no STM32 para 10-20 Hz
2. Aumente o intervalo de animação no Python
3. Use a versão otimizada de quatérnion se preferir

## 📊 Validação da Matriz

O monitor automaticamente verifica se a matriz é válida:

### Matriz de Rotação Válida:
- ✅ Determinante ≈ 1.0
- ✅ Ortogonal: R × R^T = I
- ✅ Preserva comprimentos

### Exemplo de Matriz Identidade:
```
[ 1.000000   0.000000   0.000000]
[ 0.000000   1.000000   0.000000]
[ 0.000000   0.000000   1.000000]
```

### Exemplo de Rotação 30° em Y:
```
[ 0.866025   0.000000   0.500000]
[ 0.000000   1.000000   0.000000]
[-0.500000   0.000000   0.866025]
```

## 🎯 Performance

### Taxa de Dados Recomendada:
- **STM32**: 10-20 Hz
- **Visualização**: 10 FPS
- **Latência**: < 100ms

### Para PCs mais lentos:
```python
# Edite visualizador_matriz_rotacao.py
interval=150,     # 6.7 FPS
maxlen=20,       # Buffer menor
```

---

## 💡 Dicas Finais

1. **Sempre teste primeiro** com o monitor
2. **Use o simulador** para verificar se a interface funciona
3. **Ajuste a taxa** no STM32 se necessário (10 Hz é ideal)
4. **Verifique os eixos** - X (vermelho), Y (verde), Z (azul)

**Seu código STM32 está perfeito para este formato! 🚀**
