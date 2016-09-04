/*
 * timer.h
 *
 *  Created on: Sep 4, 2016
 */

#ifndef TIMER_H_
#define TIMER_H_


extern "C" {
#include <stdint.h>

void systick_delay(uint32_t delayTicks);
}


#endif /* TIMER_H_ */
