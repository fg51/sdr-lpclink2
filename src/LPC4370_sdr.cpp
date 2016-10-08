/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

//{{{ includes
#include "driver/common_driver.h"

#include "driver/timer.h" //TODO: rename to systick_config.h
using driverTimer::init_systick;
using driverTimer::systick_delay;

#include "driver/led1.h"
using driverLED::init_led1;
using driverLED::turnon_led1;
using driverLED::turnoff_led1;

#include "driver/i2c_LCD.h"
using driverI2CLCD::init_i2clcd;
using driverI2CLCD::puts_lcd;

//}}} includes


#include <stdio.h>


int main(void) {

    init_systick();

    init_led1();
    init_i2clcd();

    // Start M0APP slave processor
#if defined (__MULTICORE_MASTER_SLAVE_M0APP)
    cr_start_m0(SLAVE_M0APP, &__core_m0app_START__);
#endif

    // Start M0SUB slave processor
#if defined (__MULTICORE_MASTER_SLAVE_M0SUB)
    cr_start_m0(SLAVE_M0SUB, &__core_m0sub_START__);
#endif



    puts_lcd("HelloSDR");

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        systick_delay(500);
        turnon_led1();

        systick_delay(1000);
        turnoff_led1();

        i++ ;
    }

    return 0 ;
}
