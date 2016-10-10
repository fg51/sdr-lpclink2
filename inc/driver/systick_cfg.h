/*
 * systick_cfg.h
 *
 *  Created on: Sep 4, 2016
 */

#ifndef D_SYSTICK_CFG_H
#define D_SYSTICK_CFG_H


#ifdef __cplusplus
namespace driverSysTick{
extern "C" {
#endif

#include "driver/common_driver.h"

void setup_systemclock(void);
void init_systick(void);
void systick_delay(uint32_t delayTicks);
uint32_t get_msTicks(void);


#ifdef __cplusplus
}
} // namespace driverTimer
#endif

#endif

