/*
 * Exemplo STM32 - Dual Magnetometer Raw Data Transmission
 * 
 * Este código demonstra como ler dois magnetômetros e enviar os dados brutos (x,y,z)
 * via UART para o visualizador de esferas Python.
 * 
 * Autor: Cesar - IC 2024
 * Data: Janeiro 2025
 */

#include "main.h"
#include <stdio.h>
#include <math.h>

// Definições para os magnetômetros
#define MAG_SCALE_FACTOR 0.15f  // Conversão para μT (depende do sensor)
#define MAX_MAG_VALUE 4000      // Valor máximo em LSB
#define TRANSMISSION_RATE_MS 100 // Taxa de transmissão (10 Hz)

// Estrutura para dados do magnetômetro
typedef struct {
    float x;
    float y;
    float z;
    float magnitude;
} MagnetometerData_t;

// Variáveis globais
MagnetometerData_t mag1_data, mag2_data;
uint32_t last_transmission_time = 0;
uint8_t data_to_send[200];

// Protótipos de função
void MagnetometerInit(void);
void ReadMagnetometer1(MagnetometerData_t* data);
void ReadMagnetometer2(MagnetometerData_t* data);
void TransmitDualMagnetometerData(uint8_t format_type);
float CalculateMagnitude(float x, float y, float z);
void ApplyCalibration(MagnetometerData_t* data, uint8_t mag_id);

/**
 * @brief Inicialização dos magnetômetros
 */
void MagnetometerInit(void)
{
    // Inicialização específica para o seu sensor (exemplo com I2C)
    
    // Para magnetômetro 1 (ex: endereço 0x0D)
    // Configure registros de controle, faixa de medição, taxa de amostragem
    
    // Para magnetômetro 2 (ex: endereço 0x1E)
    // Configure registros similares
    
    printf("Magnetometers initialized\n");
}

/**
 * @brief Leitura do magnetômetro 1
 */
void ReadMagnetometer1(MagnetometerData_t* data)
{
    // Exemplo de leitura via I2C ou SPI
    int16_t raw_x, raw_y, raw_z;
    
    // Leia os registros do magnetômetro 1
    // raw_x = HAL_I2C_ReadReg16(...);
    // raw_y = HAL_I2C_ReadReg16(...);
    // raw_z = HAL_I2C_ReadReg16(...);
    
    // Para demonstração, usando valores simulados
    // Em implementação real, substitua por leitura do sensor
    static float time_sim = 0;
    time_sim += 0.1f;
    
    raw_x = (int16_t)(1000 * sinf(time_sim * 0.3f) + 500);
    raw_y = (int16_t)(1200 * cosf(time_sim * 0.2f) - 300);
    raw_z = (int16_t)(1500 + 200 * sinf(time_sim * 0.1f));
    
    // Conversão para μT
    data->x = (float)raw_x * MAG_SCALE_FACTOR;
    data->y = (float)raw_y * MAG_SCALE_FACTOR;
    data->z = (float)raw_z * MAG_SCALE_FACTOR;
    
    // Aplicar calibração
    ApplyCalibration(data, 1);
    
    // Calcular magnitude
    data->magnitude = CalculateMagnitude(data->x, data->y, data->z);
}

/**
 * @brief Leitura do magnetômetro 2
 */
void ReadMagnetometer2(MagnetometerData_t* data)
{
    int16_t raw_x, raw_y, raw_z;
    
    // Leia os registros do magnetômetro 2
    // raw_x = HAL_I2C_ReadReg16(...);
    // raw_y = HAL_I2C_ReadReg16(...);
    // raw_z = HAL_I2C_ReadReg16(...);
    
    // Para demonstração
    static float time_sim = 0;
    time_sim += 0.1f;
    
    raw_x = (int16_t)(900 * sinf(time_sim * 0.35f) - 200);
    raw_y = (int16_t)(1100 * cosf(time_sim * 0.25f) + 400);
    raw_z = (int16_t)(1400 + 300 * cosf(time_sim * 0.12f));
    
    // Conversão para μT
    data->x = (float)raw_x * MAG_SCALE_FACTOR;
    data->y = (float)raw_y * MAG_SCALE_FACTOR;
    data->z = (float)raw_z * MAG_SCALE_FACTOR;
    
    // Aplicar calibração
    ApplyCalibration(data, 2);
    
    // Calcular magnitude
    data->magnitude = CalculateMagnitude(data->x, data->y, data->z);
}

/**
 * @brief Aplicar calibração aos dados do magnetômetro
 */
void ApplyCalibration(MagnetometerData_t* data, uint8_t mag_id)
{
    if (mag_id == 1) {
        // Calibração magnetômetro 1 - Hard Iron Compensation
        data->x -= 2.0f;   // Offset X
        data->y += 1.5f;   // Offset Y
        data->z -= 3.0f;   // Offset Z
        
        // Soft Iron Compensation (matriz de correção)
        float temp_x = data->x;
        float temp_y = data->y;
        float temp_z = data->z;
        
        data->x = 1.02f * temp_x + 0.01f * temp_y + 0.005f * temp_z;
        data->y = 0.01f * temp_x + 0.98f * temp_y + 0.008f * temp_z;
        data->z = 0.005f * temp_x + 0.008f * temp_y + 1.05f * temp_z;
        
    } else {
        // Calibração magnetômetro 2
        data->x += 1.0f;   // Offset X
        data->y -= 2.5f;   // Offset Y
        data->z += 2.0f;   // Offset Z
        
        // Soft Iron Compensation
        float temp_x = data->x;
        float temp_y = data->y;
        float temp_z = data->z;
        
        data->x = 0.99f * temp_x - 0.02f * temp_y + 0.01f * temp_z;
        data->y = -0.02f * temp_x + 1.03f * temp_y - 0.005f * temp_z;
        data->z = 0.01f * temp_x - 0.005f * temp_y + 0.97f * temp_z;
    }
}

/**
 * @brief Calcular magnitude do campo magnético
 */
float CalculateMagnitude(float x, float y, float z)
{
    return sqrtf(x*x + y*y + z*z);
}

/**
 * @brief Transmitir dados dos dois magnetômetros
 * @param format_type: 1 = com identificadores, 2 = dados alternados
 */
void TransmitDualMagnetometerData(uint8_t format_type)
{
    if (format_type == 1) {
        // Formato com identificadores (mais robusto)
        sprintf((char*)data_to_send, "MAG1\n%.3f, %.3f, %.3f\nMAG2\n%.3f, %.3f, %.3f\n",
                mag1_data.x, mag1_data.y, mag1_data.z,
                mag2_data.x, mag2_data.y, mag2_data.z);
    } else {
        // Formato alternado (mais compacto)
        sprintf((char*)data_to_send, "%.3f, %.3f, %.3f\n%.3f, %.3f, %.3f\n",
                mag1_data.x, mag1_data.y, mag1_data.z,
                mag2_data.x, mag2_data.y, mag2_data.z);
    }
    
    // Transmitir via UART
    HAL_UART_Transmit(&huart1, data_to_send, strlen((char*)data_to_send), HAL_MAX_DELAY);
}

/**
 * @brief Loop principal de leitura e transmissão
 */
void DualMagnetometerMainLoop(void)
{
    uint32_t current_time = HAL_GetTick();
    
    if (current_time - last_transmission_time >= TRANSMISSION_RATE_MS) {
        // Ler dados dos dois magnetômetros
        ReadMagnetometer1(&mag1_data);
        ReadMagnetometer2(&mag2_data);
        
        // Transmitir dados (formato 1 = com identificadores)
        TransmitDualMagnetometerData(1);
        
        last_transmission_time = current_time;
        
        // Debug via printf (se necessário)
        printf("Mag1: [%.1f, %.1f, %.1f] |B|=%.1f μT | Mag2: [%.1f, %.1f, %.1f] |B|=%.1f μT\n",
               mag1_data.x, mag1_data.y, mag1_data.z, mag1_data.magnitude,
               mag2_data.x, mag2_data.y, mag2_data.z, mag2_data.magnitude);
    }
}

/**
 * @brief Função de teste para calibração
 */
void TestMagnetometerCalibration(void)
{
    printf("Iniciando teste de calibração...\n");
    printf("Rotacione os magnetômetros em todas as direções por 30 segundos\n");
    
    uint32_t start_time = HAL_GetTick();
    uint32_t test_duration = 30000; // 30 segundos
    
    float mag1_min[3] = {1000, 1000, 1000};
    float mag1_max[3] = {-1000, -1000, -1000};
    float mag2_min[3] = {1000, 1000, 1000};
    float mag2_max[3] = {-1000, -1000, -1000};
    
    while ((HAL_GetTick() - start_time) < test_duration) {
        ReadMagnetometer1(&mag1_data);
        ReadMagnetometer2(&mag2_data);
        
        // Atualizar valores mínimos e máximos para calibração
        for (int i = 0; i < 3; i++) {
            float* mag1_values[3] = {&mag1_data.x, &mag1_data.y, &mag1_data.z};
            float* mag2_values[3] = {&mag2_data.x, &mag2_data.y, &mag2_data.z};
            
            if (*mag1_values[i] < mag1_min[i]) mag1_min[i] = *mag1_values[i];
            if (*mag1_values[i] > mag1_max[i]) mag1_max[i] = *mag1_values[i];
            
            if (*mag2_values[i] < mag2_min[i]) mag2_min[i] = *mag2_values[i];
            if (*mag2_values[i] > mag2_max[i]) mag2_max[i] = *mag2_values[i];
        }
        
        HAL_Delay(50); // 20 Hz durante calibração
    }
    
    // Calcular offsets de calibração (Hard Iron)
    printf("Calibração concluída!\n");
    printf("Mag1 Offsets - X: %.2f, Y: %.2f, Z: %.2f\n",
           (mag1_max[0] + mag1_min[0]) / 2.0f,
           (mag1_max[1] + mag1_min[1]) / 2.0f,
           (mag1_max[2] + mag1_min[2]) / 2.0f);
    
    printf("Mag2 Offsets - X: %.2f, Y: %.2f, Z: %.2f\n",
           (mag2_max[0] + mag2_min[0]) / 2.0f,
           (mag2_max[1] + mag2_min[1]) / 2.0f,
           (mag2_max[2] + mag2_min[2]) / 2.0f);
}

/**
 * @brief Função principal do sistema
 */
int main(void)
{
    // Inicializações do HAL
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_I2C1_Init(); // Para comunicação com magnetômetros
    
    // Inicializar magnetômetros
    MagnetometerInit();
    
    printf("Sistema de Duplo Magnetômetro iniciado\n");
    printf("Dados brutos sendo transmitidos via UART\n");
    
    // Opcional: executar calibração
    // TestMagnetometerCalibration();
    
    // Loop principal
    while (1) {
        DualMagnetometerMainLoop();
        
        // Pequeno delay para não sobrecarregar o sistema
        HAL_Delay(10);
    }
}

/*
 * NOTAS DE IMPLEMENTAÇÃO:
 * 
 * 1. SENSORES SUPORTADOS:
 *    - HMC5883L/QMC5883L (comum em módulos GY-271)
 *    - LSM303DLHC (acelerômetro + magnetômetro)
 *    - MPU9250 (IMU com magnetômetro AK8963)
 *    - LIS3MDL (magnetômetro de alta precisão)
 * 
 * 2. CONFIGURAÇÃO I2C:
 *    - Velocidade: 100-400 kHz
 *    - Pull-ups: 4.7kΩ nas linhas SDA/SCL
 *    - Endereços típicos: 0x1E, 0x0D, 0x30
 * 
 * 3. CALIBRAÇÃO:
 *    - Hard Iron: offsets constantes (x_offset, y_offset, z_offset)
 *    - Soft Iron: matriz de correção 3x3
 *    - Procedimento: rotação completa em todas as direções
 * 
 * 4. CONFIGURAÇÃO UART:
 *    - Baudrate: 115200
 *    - Data bits: 8
 *    - Stop bits: 1
 *    - Parity: None
 * 
 * 5. FORMATOS DE DADOS:
 *    Formato 1 (com identificadores):
 *    MAG1
 *    25.123, -15.456, 48.789
 *    MAG2
 *    23.567, -12.890, 51.234
 * 
 *    Formato 2 (alternado):
 *    25.123, -15.456, 48.789
 *    23.567, -12.890, 51.234
 * 
 * 6. OTIMIZAÇÕES:
 *    - Use DMA para transmissão UART em aplicações críticas
 *    - Implemente filtro passa-baixa para reduzir ruído
 *    - Considere usar ponto flutuante de 16 bits para economizar banda
 * 
 * 7. TROUBLESHOOTING:
 *    - Verifique conexões I2C com osciloscópio
 *    - Confirme endereços dos sensores com I2C scanner
 *    - Use printf para debug durante desenvolvimento
 *    - Monitore consumo de CPU com profiler
 */
