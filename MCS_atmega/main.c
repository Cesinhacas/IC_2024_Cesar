 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
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
#include "mcc_generated_files/system/system.h"
#include "calib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Main application
*/
union calib_t{
	uint8_t inteiro[4];
	float flutuante;
};

//float mx[tam] = {0}, my[tam] = {0}, mz[tam] = {0};
union calib_t mx_[tam] = {0}, my_[tam] = {0}, mz_[tam] = {0};
float p1[9] = {0}, p0[9] = {0};
uint8_t passos_NLLS = 0;

int main(void)
{
    SYSTEM_Initialize();
    
    union calib_t param[9], time;
    //uint32_t start_time = 0; 
    //float ETS_time = 0;//, NLLS_time = 0;   

    while(1)
    {
        while(PORTC & 0x01);
        PORTC &= 0x02;
        
        for(uint16_t i = 0; i < tam; i++)
        {
            for(uint8_t j = 0; j < 4; j++)
            {
                mx_[i].inteiro[j] = SPI_receive();
            }
        }
        for(uint16_t i = 0; i < tam; i++)
        {
            for(uint8_t j = 0; j < 4; j++)
            {
                my_[i].inteiro[j] = SPI_receive();
            }
        }
        for(uint16_t i = 0; i < tam; i++)
        {
            for(uint8_t j = 0; j < 4; j++)
            {
                mz_[i].inteiro[j] = SPI_receive();
            }
        }
        
        PORTC |= 0xFD;
        
        /*for(uint16_t i = 0; i<=tam; i++)
        {
            mx[i] = mx_[i].flutuante;
            my[i] = my_[i].flutuante;
            mz[i] = mz_[i].flutuante;
        }*/
        //start_time = HAL_GetTick();
        //ETS(mx, my, mz, p1);
        //ETS_time = HAL_GetTick() - start_time;

        //start_time = HAL_GetTick();
        passos_NLLS = NLLS((float *)mx_, (float *)my_, (float *)mz_, p1);
        time.flutuante = 0;
        //NLLS_time = HAL_GetTick() - start_time;
        
        for(uint16_t i = 0; i < 10; i++)
        {
            param[i].flutuante = p1[i];
        }
        
        PORTC &= 0x02;
        
        for(uint8_t i = 0; i < 10; i++)
        {
            for(uint8_t j = 0; j < 4; j++)
            {
                SPI_transmit(param[i].inteiro[j]);
            }
        }
        
        for(uint8_t i = 0; i < 4; i++)
        {
            SPI_transmit(time.inteiro[i]);
        }
        SPI_transmit(passos_NLLS);
        
        PORTC |= 0xFD;
    }
}