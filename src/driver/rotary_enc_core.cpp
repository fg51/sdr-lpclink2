#include "driver/rotary_enc.h"


#ifdef __cplusplus
namespace rotaryenc {
#endif


//{{{ LED part
#include "driver/common_driver.h"

#include <lpc43xx_gpio.h>


static const uint32_t kPORT_RED   = 1UL << 3;
static const uint32_t kPORT_GREEN = 1UL << 4;


void init_rotary_LED(void)
{
    LPC_GPIO_PORT->DIR[1] |= kPORT_RED | kPORT_GREEN;
}


void turnon_ROT_RED(void)
{
    LPC_GPIO_PORT->SET[1] |= kPORT_RED;
    LPC_GPIO_PORT->CLR[1] =  kPORT_GREEN;
}


void turnon_ROT_GREEN(void)
{
    LPC_GPIO_PORT->SET[1] |= kPORT_GREEN;
    LPC_GPIO_PORT->CLR[1] =  kPORT_RED;
}


void turnoff_ROT_LED(void)
{
    LPC_GPIO_PORT->CLR[1] = kPORT_RED | kPORT_GREEN;
}

//}}} LED part


//----------------------------------------
//{{{ button, encoder part

#include "driver/common_driver.h"

#include "lpc43xx_scu.h"
#include <lpc43xx_gpio.h>


void init_rotary_enc(void)
{
    uint8_t kPORT = 1;
    uint8_t kPIN_ENCODER0 = 7;
    uint8_t kPIN_ENCODER1 = 8;
    uint8_t kPIN_BUTTON0  = 9;

    scu_pinmux(kPORT, kPIN_ENCODER0, GPIO_PUP, FUNC0); // GPIO1-0 (ENCODER0)
    scu_pinmux(kPORT, kPIN_ENCODER1, GPIO_PUP, FUNC0); // GPIO1-1 (ENCODER1)
    scu_pinmux(kPORT, kPIN_BUTTON0,  GPIO_PUP, FUNC0); // GPIO1-2 (BUTTON0)
}



/**
 * #define ENCODER0 (0b001)
 * #define ENCODER1 (0b010)
 * #define BUTTON0  (0b100)
 */
typedef struct ButtonEncoder_t {
    bool button;
    bool encoderup;
    bool encoderdown;
} ButtonEncoder_t;



uint32_t read_button_data(void)
{
    const uint8_t kPORT = 1;
    return GPIO_ReadValue(kPORT) & 0b00000111;
}

//}}} button, encoder part


#ifdef __cplusplus
} // namespace rotaryenc
#endif

