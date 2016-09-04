#ifdef __cplusplus
namespace driverLED {
#endif


#include "lpc43xx_gpio.h"


const uint8_t kPORT_LED1 = 0;
const uint32_t kBIT_LED1 = 1 << 8;
const uint8_t kIS_DIRECTION = 1;    //NOTE: OUT? INN?


void init_led1(void)
{
    GPIO_SetDir(kPORT_LED1, kBIT_LED1, kIS_DIRECTION);
    GPIO_ClearValue(kPORT_LED1, kBIT_LED1);
}


void turnon_led1(void)
{
    GPIO_SetValue(kPORT_LED1, kBIT_LED1);
}


void turnoff_led1(void)
{
    GPIO_ClearValue(kPORT_LED1, kBIT_LED1);
}


#ifdef __cplusplus
} // namespace driverLED
#endif
