/**
 * SPI Type Definitions Header File
 *
 * @file spi_polling_types.h
 *
 * @defgroup spi SPI
 *
 * @version SPI Driver Version 2.0.0.
 *
 * @brief This header file provides type definitions for the SPI module operation in Polling mode.
 *
*/

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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

#ifndef SPI_POLLING_TYPES_H
#define	SPI_POLLING_TYPES_H


/**
 * @ingroup spi
 * @typedef struct spi_configuration_t
 * @brief Holds register configurations for SPI module.
 */
typedef struct
{ 
    uint8_t spcr; //Stores configuration for SPCR register - SPI Control Register
    uint8_t spsr; //Stores configuration for SPSR register - SPI Status Register
} spi_configuration_t;


#endif /* SPI_POLLING_TYPES_H */
