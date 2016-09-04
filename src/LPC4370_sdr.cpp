/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC43xx.h"
#endif

#include <cr_section_macros.h>

#if defined (__MULTICORE_MASTER_SLAVE_M0APP) | defined (__MULTICORE_MASTER_SLAVE_M0SUB)
#include "cr_start_m0.h"
#endif


#include <stdio.h>

#include "lpc43xx_gpio.h"
#include "lpc43xx_cgu.h"


#include "driver/timer.h"




int main(void) {
    // Setup SysTick Timer to interrupt at 1 msec intervals
    SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000);

    GPIO_SetDir(0, 1 << 8, 1);
    GPIO_ClearValue(0, 1 << 8);


    // Start M0APP slave processor
#if defined (__MULTICORE_MASTER_SLAVE_M0APP)
    cr_start_m0(SLAVE_M0APP, &__core_m0app_START__);
#endif

    // Start M0SUB slave processor
#if defined (__MULTICORE_MASTER_SLAVE_M0SUB)
    cr_start_m0(SLAVE_M0SUB, &__core_m0sub_START__);
#endif


    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        systick_delay(500);
        GPIO_SetValue(0, 1 << 8);
        systick_delay(1000);
        GPIO_ClearValue(0, 1 << 8);

        i++ ;
    }

    return 0 ;
}
