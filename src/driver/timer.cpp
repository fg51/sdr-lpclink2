/*
 * timer.cpp
 *
 *  Created on: Sep 4, 2016
 *      Author: flamefly
 */

extern "C" {

#include <stdint.h>
//  SysTick_Handler - just increment SysTick counter
volatile static uint32_t msTicks; // counter for 1ms SysTicks


void SysTick_Handler(void) {
    msTicks++;
}


// ****************
// systick_delay
// - creates a delay of the appropriate number of Systicks (happens every 1 ms)
void systick_delay(uint32_t delayTicks) {
    uint32_t currentTicks;

    currentTicks = msTicks;    //NOTE: read current tick counter
    // Now loop until required number of ticks passes.
    while ((msTicks - currentTicks) < delayTicks);
}

} // END extern "C"

