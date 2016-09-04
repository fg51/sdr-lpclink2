/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "driver/common_driver.h"

#include "driver/timer.h"
#include "driver/led1.h"


using driverTimer::init_systick;
using driverTimer::systick_delay;

using driverLED::init_led1;
using driverLED::turnon_led1;
using driverLED::turnoff_led1;


int main(void) {

    init_systick();

    init_led1();


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
        turnon_led1();

        systick_delay(1000);
        turnoff_led1();

        i++ ;
    }

    return 0 ;
}
