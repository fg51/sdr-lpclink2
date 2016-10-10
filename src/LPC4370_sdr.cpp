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

#include "driver/systick_cfg.h"
using driverSysTick::setup_systemclock;
using driverSysTick::init_systick;
using driverSysTick::systick_delay;
using driverSysTick::get_msTicks;

#include "driver/led1.h"
using driverLED::init_led1;
using driverLED::turnon_led1;
using driverLED::turnoff_led1;

#include "driver/rotary_enc.h"
using rotaryenc::init_rotary_LED;
using rotaryenc::turnoff_ROT_LED;
using rotaryenc::turnon_ROT_RED;
using rotaryenc::turnon_ROT_GREEN;

//using rotaryenc::event_t;
using rotaryenc::init_rotary_enc;
using rotaryenc::update_button_encoder;

#include "driver/i2c_LCD.h"
using driverI2CLCD::init_i2clcd;
using driverI2CLCD::puts_lcd;


void event_action(rotaryenc::event_t event);
void led1_blinkly(uint32_t tick);


int main(void) {
    setup_systemclock(); // to 204 [MHz]

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

    init_rotary_LED();
    turnoff_ROT_LED();
    //rotaryenc::turnon_ROT_RED();
    //rotaryenc::turnon_ROT_GREEN();

    init_rotary_enc();

    puts_lcd("HelloSDR");
    // Force the counter to be placed into memory
    volatile static int i = 0 ;

    // Enter an infinite loop, just incrementing a counter
    while(1) {
        uint32_t tick = get_msTicks();
        rotaryenc::event_t event = update_button_encoder(tick);
        event_action(event);

        led1_blinkly(tick);
        i++ ;
    }

    return 0 ;
}


void led1_blinkly(uint32_t tick)
{
    const uint32_t kDURATION_OFF = 500;
    const uint32_t kDURATION_ON  = 1000;
    static volatile bool is_on = false;
    static volatile uint32_t end_tick = 0 + kDURATION_ON;

    if (is_on) {
        if (tick >= end_tick) {
            turnoff_led1();
            is_on = false;
            end_tick = tick + kDURATION_OFF;
            return;
        }
        return;
    }
    if (tick >= end_tick) {
        turnon_led1();
        is_on = true;
        end_tick = tick + kDURATION_ON;
        return;
    }
    return;
}


void event_action(rotaryenc::event_t event)
{
    switch (event) {
    case rotaryenc::EVT_BUTTON_DOWN_LONG: {
        turnon_ROT_RED();
        break;}
    case rotaryenc::EVT_BUTTON_SINGLE_CLICK: {
        turnon_ROT_GREEN();
        break;}
    case rotaryenc::NO_EVENT: {
        break;}
    default: {
        turnon_ROT_GREEN();
        break;}
    }
}
