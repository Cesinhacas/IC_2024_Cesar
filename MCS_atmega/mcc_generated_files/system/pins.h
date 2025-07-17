/**
 * Generated Pins Header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This file contains the API prototypes and function macros for the Pins driver.
 *
 * @version Driver Version  1.0.0
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

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "./port.h"
/**  
 * @ingroup  pinsdriver
 * @name Pin Function Macros
 * Macros for the individual pin functions.
 * @note These sets of macros are generated for all the selected pins in the Pins module.
 */
 ///@{

//get/set IO_PB0 aliases
#define IO_PB0_SetHigh() do { PORTB |= 0x1; } while(0)
#define IO_PB0_SetLow() do { PORTB &= ~0x1; } while(0)
#define IO_PB0_Toggle() do { PINB |= 0x1; } while(0)
#define IO_PB0_GetValue() (PINB & (0x1 << 0))
#define IO_PB0_SetDigitalInput() do { DDRB &= ~0x1; } while(0)
#define IO_PB0_SetDigitalOutput() do { DDRB |= 0x1; } while(0)
#define IO_PB0_SetPullUp() do { PORTB |= 0x1; } while(0)
#define IO_PB0_ResetPullUp() do { PORTB &= ~0x1; } while(0)

//get/set IO_PB4 aliases
#define IO_PB4_SetHigh() do { PORTB |= 0x10; } while(0)
#define IO_PB4_SetLow() do { PORTB &= ~0x10; } while(0)
#define IO_PB4_Toggle() do { PINB |= 0x10; } while(0)
#define IO_PB4_GetValue() (PINB & (0x1 << 4))
#define IO_PB4_SetDigitalInput() do { DDRB &= ~0x10; } while(0)
#define IO_PB4_SetDigitalOutput() do { DDRB |= 0x10; } while(0)
#define IO_PB4_SetPullUp() do { PORTB |= 0x10; } while(0)
#define IO_PB4_ResetPullUp() do { PORTB &= ~0x10; } while(0)

//get/set IO_PB3 aliases
#define IO_PB3_SetHigh() do { PORTB |= 0x8; } while(0)
#define IO_PB3_SetLow() do { PORTB &= ~0x8; } while(0)
#define IO_PB3_Toggle() do { PINB |= 0x8; } while(0)
#define IO_PB3_GetValue() (PINB & (0x1 << 3))
#define IO_PB3_SetDigitalInput() do { DDRB &= ~0x8; } while(0)
#define IO_PB3_SetDigitalOutput() do { DDRB |= 0x8; } while(0)
#define IO_PB3_SetPullUp() do { PORTB |= 0x8; } while(0)
#define IO_PB3_ResetPullUp() do { PORTB &= ~0x8; } while(0)

//get/set IO_PB5 aliases
#define IO_PB5_SetHigh() do { PORTB |= 0x20; } while(0)
#define IO_PB5_SetLow() do { PORTB &= ~0x20; } while(0)
#define IO_PB5_Toggle() do { PINB |= 0x20; } while(0)
#define IO_PB5_GetValue() (PINB & (0x1 << 5))
#define IO_PB5_SetDigitalInput() do { DDRB &= ~0x20; } while(0)
#define IO_PB5_SetDigitalOutput() do { DDRB |= 0x20; } while(0)
#define IO_PB5_SetPullUp() do { PORTB |= 0x20; } while(0)
#define IO_PB5_ResetPullUp() do { PORTB &= ~0x20; } while(0)

//get/set IO_PB2 aliases
#define IO_PB2_SetHigh() do { PORTB |= 0x4; } while(0)
#define IO_PB2_SetLow() do { PORTB &= ~0x4; } while(0)
#define IO_PB2_Toggle() do { PINB |= 0x4; } while(0)
#define IO_PB2_GetValue() (PINB & (0x1 << 2))
#define IO_PB2_SetDigitalInput() do { DDRB &= ~0x4; } while(0)
#define IO_PB2_SetDigitalOutput() do { DDRB |= 0x4; } while(0)
#define IO_PB2_SetPullUp() do { PORTB |= 0x4; } while(0)
#define IO_PB2_ResetPullUp() do { PORTB &= ~0x4; } while(0)
///@}

/**
 * @ingroup  pinsdriver
 * @brief Initializes the General Purpose Input/Output (GPIO), peripheral I/O pins and related registers.
 * @param None.
 * @return None.
 */
void PIN_MANAGER_Initialize();

#endif /* PINS_H_INCLUDED */
