#ifndef D_LED1_H
#define D_LED1_H


#ifdef __cplusplus
namespace driverLED {
#endif

#include "driver/common_driver.h"

void init_led1(void);
void turnon_led1(void);
void turnoff_led1(void);


#ifdef __cplusplus
} // namespace driverLED
#endif

#endif // D_LED1_H
