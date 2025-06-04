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
#include "ff.h"
#include "diskio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Main application
*/

static float mx[tam] = {0}, my[tam] = {0}, mz[tam] = {0};
float p1[9] = {0}, p0[9] = {0};
uint8_t passos_NLLS = 0;

int main(void)
{
    SYSTEM_Initialize();
    
    char file_read[20] = {0};
    
    uint32_t start_time = 0;
    uint16_t file_cont = 1;
    float ETS_time = 0, NLLS_time = 0;
    
    FATFS fs;
    FRESULT res;

    // Monta o sistema de arquivos na unidade lógica "0:"
    res = f_mount(&fs, "0:", 1);
    if (res != FR_OK) {
        //printf("Falha ao montar o sistema de arquivos: %d\n", res);
        return 1;
    }
    

    while(1)
    {
        if(file_cont >= 3001)
        {
            return 1;
        }

        sprintf(file_read, "0:/DATA/run%d.txt", file_cont);  // Prefixo de volume (0:) é comum no FatFs

        FIL fil;
        FRESULT res;

        res = f_open(&fil, file_read, FA_READ);
        if (res != FR_OK)
        {
            return 1;
        }

        char line[7645];
        UINT br; // Bytes lidos

        float *linhas[] = {mx, my, mz};  // Vetor de ponteiros para facilitar o acesso

        for (int i = 0; i < 3; i++)
        {
            // lê uma linha completa (até '\n' ou fim do buffer)
            int line_pos = 0;
            char ch;
            do {
                res = f_read(&fil, &ch, 1, &br);
                if (res != FR_OK || br == 0) {
                    return 1;
                }
                line[line_pos++] = ch;
            } while (ch != '\n' && line_pos < sizeof(line)-1);
            line[line_pos] = '\0';

            char *token = strtok(line, ",");
            int j = 0;

            while (token != NULL && j < tam)
            {
                linhas[i][j] = strtof(token, NULL);
                token = strtok(NULL, ",");
                j++;
            }

            if (j != tam)
            {
                return 1;
            }
        }

        f_close(&fil);
        
        //start_time = HAL_GetTick();
        ETS(mx, my, mz, p1);
        //ETS_time = HAL_GetTick() - start_time;

        //start_time = HAL_GetTick();
        /*passos_NLLS = NLLS(mx, my, mz, p0);
        //NLLS_time = HAL_GetTick() - start_time;


        sprintf(file_read, "0:/RES/run%d.txt", file_cont);
        res = f_open(&fil, file_read, FA_WRITE | FA_CREATE_ALWAYS);
        if (res != FR_OK)
        {
            return 1;
        }

        char out_line[128];
        UINT bw;

        for (int i = 0; i < 9; i++) {
            sprintf(out_line, "%f, %f\n", p1[i], p0[i]);
            f_write(&fil, out_line, strlen(out_line), &bw);
        }

        sprintf(out_line, "%f, %f\n", ETS_time, NLLS_time);
        f_write(&fil, out_line, strlen(out_line), &bw);

        sprintf(out_line, "0, %u\n", passos_NLLS);
        f_write(&fil, out_line, strlen(out_line), &bw);

        f_close(&fil);

        file_cont++;*/
                    
    }
}