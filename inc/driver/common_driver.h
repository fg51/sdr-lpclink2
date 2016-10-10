#ifndef D_COMMON_DRIVER_H
#define D_COMMON_DRIVER_H


#ifdef __USE_CMSIS
#include "LPC43xx.h"
#endif

//#include <cr_section_macros.h>

#if defined (__MULTICORE_MASTER_SLAVE_M0APP) | defined (__MULTICORE_MASTER_SLAVE_M0SUB)
#include "cr_start_m0.h"
#endif

//#include "lpc43xx_gpio.h"
//#include "lpc43xx_cgu.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#endif // D_COMMON_DRIVER_H

