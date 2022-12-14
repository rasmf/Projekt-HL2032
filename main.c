/*
    \file  main.c
    \brief USB CDC ACM device

    \version 2019-6-5, V1.0.0, demo for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32vf103.h"
#include "lcd.h"
#include "delay.h"
#include "gd32v_mpu6500_if.h"

#define GRAPH_HEIGHT 30

int main(void)
{
    /* The related data structure for the IMU, contains a vector of x, y, z floats*/
    mpu_vector_t vec, vec_temp;
    mpu_vector_t vec2, vec2_temp;
    /* for lcd */
    uint16_t line_color;

    /* Initialize pins for I2C */
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_I2C0);
    gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);
    /* Initialize the IMU (Notice that MPU6500 is referenced, this is due to the fact that ICM-20600
       ICM-20600 is mostly register compatible with MPU6500, if MPU6500 is used only thing that needs
       to change is MPU6500_WHO_AM_I_ID from 0x11 to 0x70. */
    mpu6500_install(I2C0);

    /* Initialize LCD */
    Lcd_SetType(LCD_INVERTED);
    Lcd_Init();
    LCD_Clear(BLACK);

    // Creates temporary vectors to erase previously drwan lines
    mpu6500_getAccel(&vec_temp);
    mpu6500_getGyro(&vec2_temp);

    while (1)
    {
        
        LCD_ShowChar(20,20,'X',TRANSPARENT, line_color);
        LCD_ShowChar(20,40,'Y',TRANSPARENT, line_color);
        LCD_ShowChar(20,60,'Z',TRANSPARENT, line_color);
        //mpu6500_getGyroAccel(&vec2,&vec);
        // Calls on getAccel and getGyro at the same time

        /* Get accelleration data (Note: Blocking read) puts a force vector with 1G = 4096 into x, y, z directions respectively */
        mpu6500_getAccel(&vec);

        /* Do some fancy math to make a nice display */

        /* Green if pointing up, red if down */
        line_color = (vec.z < 0) ? RED : GREEN;
        /* Draw a unit circle (1G) */
        //Draw_Circle(40, 80 / 2, 28, BLUE);
        /* Erase last line */
        //LCD_DrawLine(40, 80 / 2, (40) + (vec_temp.y) / (4096 / 28), (80 / 2) + (vec_temp.x / (4096 / 28)), BLACK);
        /* Draw new line, scaled to the unit circle */
        //LCD_DrawLine(40, 80 / 2, (40) + (vec.y) / (4096 / 28), (80 / 2) + (vec.x / (4096 / 28)), line_color);
        /* Store the last vector in temporary so it can be erased */
        
        LCD_ShowNum1(40,20,vec.x,6,line_color);
        LCD_ShowNum1(40,40,vec.y,6,line_color);
        LCD_ShowNum1(40,60,vec.z,6,line_color);

        vec_temp = vec;

        //printf("%f", vec.x);

        // LCD_DrawLine(40, 80 / 2, (40) + (vec_temp.y) / (4096 / 28), (80 / 2) + (vec_temp.x / (4096 / 28)), BLACK);
        // "Upp" --> upp, "ner" --> Ner, V??nster --> v??nster, H??ger --> h??ger
        // Positivt y = lutar mot sladden           |  Negativt y = lutar bort fr??n sladden          (Skickar y v??rdet som x v??rde in till drawLine)
        // Positivt x = lutar bort fr??n knappsatsen |  Negativt x = lutar mot knappsatsen            (Skickar x v??rdet som y v??rde in till drawLine)

        // L??ngden p?? linjen beror p?? 

        // N??r vi ??ndrar f??rg beroende p?? z. line_color = (vec2.z < 0) ? RED : GREEN; LCD_NORMAL
        // Skiftar mellan r??tt o gr??nt beroende p?? om den ??r r??ttv??nd eller upp och ner.
        // R??tt = negativt = upp och ner | Gr??nt = positivt = r??ttv??nd
        
        
        /* Wait for LCD to finish drawing */
        LCD_Wait_On_Queue();
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /* Get Gyro data (Note: Blocking read???) puts a angular vector with degrees / sec into x, y, z directions respectively */
        //mpu6500_getGyro(&vec2);

        /* Do some fancy math to make a nice display */

        /* Green if pointing up, red if down */
        //line_color = (vec2.z < 0) ? RED : GREEN;
        /* Draw a unit circle (1G)  adapt to Gyro? */
        //Draw_Circle(120, 80 / 2, 28, BLUE);
        /* Erase last line */
        //LCD_DrawLine(120, 80 / 2, (120) + (-1*(vec2_temp.x)) / (2000 / 28), (80 / 2) + (vec2_temp.y / (2000 / 28)), BLACK);
        /* Draw new line, scaled to the unit circle */
        //LCD_DrawLine(120, 80 / 2, (120) + (-1*(vec2.x)) / (2000 / 28), (80 / 2) + (vec2.y / (2000 / 28)), line_color);
        /* Store the last vector so it can be erased */
        //vec2_temp = vec2;

        // LCD_DrawLine(120, 80 / 2, (120) + (vec2.x) / (2000 / 28), (80 / 2) + (vec2.y / (2000 / 28)), line_color);
        // "Upp" --> upp, "ner" --> Ner, V??nster --> h??ger, H??ger --> v??nster
        // Positivt x = lutar bort fr??n sladden |  Negativt x = lutar mot sladden               "Rotation runt x axeln"
        // Positivt y = lutar mot knappsatsen   |  Negativt y = lutar bort fr??n knappsatsen     "Rotation runt z axeln"

        // L??ngden p?? linjen beror p?? hastigheten som vinkeln ??ndras med.
        // Hur kan det anpassas eller tydas p?? ett bra s??tt?

        // N??r vi ??ndrar f??rg beroende p?? z. line_color = (vec2.z < 0) ? RED : GREEN; LCD_NORMAL
        // Skiftar mellan r??tt o gr??nt efter rotationen ? Sladd mot knappsats = r??tt, tv??rtom = gr??nt.
        // Gr??nt = moturs = positivt z | R??tt = medurs = negativt z
        // "Rotation runt y axeln"

        
        /* Wait for LCD to finish drawing */
        //LCD_Wait_On_Queue();
    }
}
