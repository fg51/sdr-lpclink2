/*
 * timer.h
 *
 *  Created on: Sep 4, 2016
 */

#ifndef D_TIMER_H
#define D_TIMER_H


#ifdef __cplusplus
namespace driverTimer {
extern "C" {
#endif

#include "driver/common_driver.h"

void init_systick(void);
void systick_delay(uint32_t delayTicks);
uint32_t get_msTicks(void);


#ifdef __cplusplus
}
} // namespace driverTimer
#endif

#endif /* D_TIMER_H */

