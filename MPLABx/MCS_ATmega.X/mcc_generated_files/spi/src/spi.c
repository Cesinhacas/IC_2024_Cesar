/**
 * SPI Generated Driver File
 *
 * @file spi.c
 *
 * @ingroup spi
 *
 * @brief This file contains the driver code for the SPI module.
 *
 * @version SPI Driver Version 2.0.0.
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

#include <avr/io.h>

#include "../spi.h"
#include "../spi_polling_types.h"

/**
 * @ingroup spi
 * @struct SPI_INTERFACE SPI
 * @brief Defines an object for SPI_INTERFACE functions.
 */
const struct SPI_INTERFACE SPI0_Host = {
    .Initialize = SPI_Initialize,
    .Deinitialize = SPI_Deinitialize,
    .Open = SPI_Open,
    .Close = SPI_Close,
    .BufferExchange = SPI_BufferExchange,
    .BufferWrite = SPI_BufferWrite,
    .BufferRead = SPI_BufferRead,
    .ByteExchange = SPI_ByteExchange,
    .ByteWrite = SPI_ByteWrite,
    .ByteRead = SPI_ByteRead,
    .IsRxReady = SPI_IsRxReady,
    .IsTxReady = SPI_IsTxReady,
    .RxCompleteCallbackRegister = NULL,
    .TxCompleteCallbackRegister = NULL
};

static const spi_configuration_t spi_configuration[] = {
    { 0x52, 0x0 },
    { 0x11, 0x1 }
};

void SPI_Initialize(void)
{
    // Return SPI registers to reset state
    SPCR = 0U;
    SPSR = 0U;
    
    
    DDRB = 0; // COnfigura todos os pinos da porta B como entrada
    DDRB = (1 << 4); // Configura o pino 4(MISO) como saída
    SPCR = 0x40; //  Habilita a SPI no modo escravo
}

uint8_t SPI_receive()
{
    while(!(SPCR & (1 << SPIF)));
    
    return SPDR;
}

void SPI_transmit(uint8_t data)
{
    SPDR = data;
    while(!(SPCR & (1 << SPIF)));
}

void SPI_Deinitialize(void)
{
    // Return SPI registers to reset state
    SPCR = 0U;
    SPSR = 0U;
}

bool SPI_Open(uint8_t spiConfigIndex)
{
    bool returnValue = false;
    if (0U == (SPCR & (1 << SPE)))
    {
        SPCR = spi_configuration[spiConfigIndex].spcr;
        SPSR = spi_configuration[spiConfigIndex].spsr;

        // Disable SPI Interrupt and Enable SPI module
        SPCR &= (~(1 << SPIE));
        SPCR |= (1 << SPE);

        returnValue = true;
    }
    else
    {
        returnValue = false;
    }
    return returnValue;
}

void SPI_Close(void)
{
    // Disable SPI Interrupt and Disable SPI module
    SPCR &= (~(1 << SPIE));
    SPCR &= (~(1 << SPE));
    (void) SPDR; // Clear SPIF
}

void SPI_BufferExchange(void *bufferData, size_t bufferSize)
{
    uint8_t* bufferInput = bufferData;
    size_t bufferInputSize = bufferSize;
    while (0U != bufferInputSize)
    {
        SPDR = *bufferInput;
        while (0U == (SPSR & (1 << SPIF)))
        {
            // Wait for flag to get set
        }
        *bufferInput = SPDR;
        bufferInput++;
        bufferInputSize--;
    }
}

void SPI_BufferWrite(void *bufferData, size_t bufferSize)
{
    uint8_t* bufferInput = bufferData;
    uint8_t receivedData;
    size_t bufferInputSize = bufferSize;
    while (0U != bufferInputSize)
    {
        SPDR = *bufferInput;
        while (0U == (SPSR & (1 << SPIF)))
        {
            // Wait for flag to get set
        }
        receivedData = SPDR; // Read data in buffer to clear SPIF flag
        (void) receivedData;            // Discard received data
        bufferInput++;
        bufferInputSize--;
    }
}

void SPI_BufferRead(void *bufferData, size_t bufferSize)
{
    uint8_t* bufferInput = bufferData;
    size_t bufferInputSize = bufferSize;
    while (0U != bufferInputSize)
    {
        SPDR = 0x00;
        while (0U == (SPSR & (1 << SPIF)))
        {
            // Wait for flag to get set
        }
        *bufferInput = SPDR;
        bufferInput++;
        bufferInputSize--;
    }
}

uint8_t SPI_ByteExchange(uint8_t byteData)
{
    SPDR = byteData;
    while (0U == (SPSR & (1 << SPIF)))
    {
        // Wait for flag to get set
    }
    return SPDR;
}

void SPI_ByteWrite(uint8_t byteData)
{
    SPDR = byteData;
}

uint8_t SPI_ByteRead(void)
{
    return SPDR;
}

bool SPI_IsRxReady(void)
{
    bool returnValue = false;
    if (0U != (SPCR & (1 << SPE)))
    {
        returnValue = ((SPSR & (1 << SPIF)) != 0) ? true : false;
    }
    else
    {
        returnValue = false;
    }
    return returnValue;
}

bool SPI_IsTxReady(void)
{
    bool returnValue = false;
    if (0U != (SPCR & (1 << SPE)))
    {
        returnValue = ((SPSR & (1 << SPIF)) != 0) ? false : true;
    }
    else
    {
        returnValue = false;
    }
    return returnValue;
}