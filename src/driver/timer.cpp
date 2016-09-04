/*
 * @file timer.cpp
 * @date Sep 4, 2016
 * @brife timer driver
 */

#ifdef __cplusplus
namespace driverTimer {
extern "C" {
#endif


#include <stdint.h>
#include "lpc43xx_cgu.h"


//  SysTick_Handler - just increment SysTick counter
volatile static uint32_t msTicks; // counter for 1ms SysTicks


/*
 * @brief Setup SysTick Timer to interrupt at 1 msec intervals
 */
void init_systick(void)
{
    SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000);

}


void SysTick_Handler(void) {
    msTicks++;
}


/*
 * systick_delay
 * - creates a delay of the appropriate number of Systicks (happens every 1 ms)
 */
void systick_delay(const uint32_t kDelayTicks) {
    const uint32_t kCurrentTicks = msTicks;    //NOTE: read current tick counter
    // Now loop until required number of ticks passes.
    while ((msTicks - kCurrentTicks) < kDelayTicks);
}


#ifdef __cplusplus
} // extern "C"
} // namespace driverTimer
#endif
