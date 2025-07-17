/**
 * SPI Generated Driver API Header File
 *
 * @file  spi.h
 *
 * @defgroup  spi SPI
 *
 * @brief This header file provides API prototypes for the SPI driver.
 *
 * @version SPI Driver Version 2.0.0.
 *
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef SPI_H
#define SPI_H

// Section: Included Files
#include "../system/utils/compiler.h"
#include "spi_interface.h"

/**
 * @ingroup spi
 * @struct SPI_INTERFACE SPI
 * @brief SPI driver interface object.
 */
extern const struct SPI_INTERFACE SPI0_Client;

/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_Initialize API
 */
#define SPI0_Client_Initialize SPI_Initialize
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_Deinitialize API
 */
#define SPI0_Client_Deinitialize SPI_Deinitialize
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_Close API
 */
#define SPI0_Client_Close SPI_Close
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_Open API
 */
#define SPI0_Client_Open SPI_Open
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_ByteExchange API
 */
#define SPI0_Client_ByteExchange SPI_ByteExchange
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_BufferExchange API
 */
#define SPI0_Client_BufferExchange SPI_BufferExchange
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_BufferWrite API
 */
#define SPI0_Client_BufferWrite SPI_BufferWrite
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_BufferRead API
 */
#define SPI0_Client_BufferRead SPI_BufferRead
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_ByteWrite API
 */
#define SPI0_Client_ByteWrite SPI_ByteWrite
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_ByteRead API
 */
#define SPI0_Client_ByteRead SPI_ByteRead
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_IsRxReady API
 */
#define SPI0_Client_IsRxReady SPI_IsRxReady
/**
 * @ingroup  spi
 * @brief    This macro defines the Custom Name for \ref SPI_IsTxReady API
 */
#define SPI0_Client_IsTxReady SPI_IsTxReady

/**
 * @ingroup spi
 * @typedef enum spi_config_name_t
 * @brief Enumeration for the different configurations supported by the driver. 
 * A configuration is specified as parameter to SPI_Open()
 * and is used by the function to set SPI parameters as specified by the configuration.
 */
typedef enum 
{
    CLIENT_CONFIG,
    SPI_DEFAULT
} spi_configuration_name_t;

uint8_t SPI_receive();

void SPI_transmit(uint8_t data);

/**
 * @ingroup spi
 * @brief Initializes the SPI module.
 * @param None.
 * @return None.
 */
void SPI_Initialize(void);

/**
 * @ingroup spi
 * @brief Deinitializes the SPI module.
 * @param None.
 * @return None.
 */
void SPI_Deinitialize(void);

/**
 * @ingroup spi
 * @brief Enables the SPI module with the configurations passed as the parameter.
 * See spi_config_names_t for the available configurations.
 * @param spiConfigIndex Configuration index 
 * @retval True  SPI module is enabled successfully with the chosen configuration
 * @retval False SPI module is already open with another configuration
 */
bool SPI_Open(uint8_t spiConfigIndex);

/**
 * @ingroup spi
 * @brief Closes the active configuration of the SPI module.
 * @param None.
 * @return None.
 */
void SPI_Close(void);

/**
 * @ingroup spi
 * @brief Exchanges the buffer using the SPI protocol. This function is blocking in Polling mode.
 * @param [in,out] *bufferData Buffer address of the data to be exchanged
 * @param [in] bufferSize Size of the data in bytes
 * @return None.
 */
void SPI_BufferExchange(void * bufferData, size_t bufferSize);

/**
 * @ingroup spi
 * @brief Writes a buffer using the SPI protocol. This function is blocking in Polling mode.
 * @param [in] *bufferData Buffer address of the data to be written
 * @param [in] bufferSize Size of the data in bytes
 * @return None.
 */
void SPI_BufferWrite(void * bufferData, size_t bufferSize);

/**
 * @ingroup spi
 * @brief Reads a buffer using the SPI protocol. This function is blocking in Polling mode.
 * @param [out] *bufferData Buffer address of the data to be read
 * @param [in] bufferSize Size of the data in bytes
 * @return None.
 */
void SPI_BufferRead(void * bufferData, size_t bufferSize);

/**
 * @ingroup spi
 * @brief Exchanges one byte using the SPI protocol. This function is blocking.
 * @param byteData Byte to be written
 * @return Received data byte
 */
uint8_t SPI_ByteExchange(uint8_t byteData);

/**
 * @ingroup spi
 * @brief Writes one byte using the SPI protocol.
 * @param byteData Byte to be written
 * @return None.
 */
void SPI_ByteWrite(uint8_t byteData);

/**
 * @ingroup spi
 * @brief Receives one byte using the SPI protocol.
 * @param None.
 * @return Received data byte
 */
uint8_t SPI_ByteRead(void);

/**
 * @ingroup spi
 * @brief Checks if the SPI module is ready to read data.
 * @param None.
 * @retval True SPI module is ready to read data
 * @retval False SPI module is not ready to read data
 */
bool SPI_IsRxReady(void);

/**
 * @ingroup spi
 * @brief  Checks if the SPI is ready to write data.
 * @param None.
 * @retval True SPI module is ready to write data
 * @retval False SPI module is not ready to write data
 */
bool SPI_IsTxReady(void);
#endif //SPI_H