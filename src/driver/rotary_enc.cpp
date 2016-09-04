#include "driver/rotary_enc.h"


#ifdef __cplusplus
namespace rotaryenc {
#endif


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


//----------------------------------------

#include "driver/common_driver.h"

#include "lpc43xx_scu.h"
#include <lpc43xx_gpio.h>

#define ENCODER0 (0b001)
#define ENCODER1 (0b010)
#define BUTTON0  (0b100)

// pushed: 0b011, not-pushed: 0b111


#define NO_EVENT                    (0b0000)
#define EVT_BUTTON_SINGLE_CLICK     (0b0001)
#define EVT_BUTTON_DOUBLE_CLICK     (0b0010)
#define EVT_BUTTON_DOWN_LONG        (0b0100)
#define ENCODER_UP                  (0x10)
#define ENCODER_DOWN                (0x20)

const uint32_t kBUTTON_DOWN_LONG_TICKS = 2000;
#define kBUTTON_DOUBLE_TICKS        : (500)
#define kBUTTON_DEBOUNCE_TICKS       (10)


static uint8_t last_button = ENCODER0 | ENCODER1 | BUTTON0;
static uint32_t last_button_down_ticks;


static inline int check_button(int status);
static inline int check_encoder(int status);



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


int btn_check(void)
{
    static uint32_t last_button = 0b111;

    uint8_t kPORT = 1;
    uint32_t cur_button = GPIO_ReadValue(kPORT) & 0b00000111;

    int status = 0;
    uint32_t changed = last_button ^ cur_button;


    if (changed & BUTTON0) {
        status = check_button(status);
    } else {
        if (!(cur_button & BUTTON0)) {
            //NOTE: check long push
            const uint32_t kCUR_TICK = get_msTicks();
            if (kCUR_TICK >= last_button_down_ticks + kBUTTON_DOWN_LONG_TICKS) {
                status |= EVT_BUTTON_DOWN_LONG;
            }
        }
    }


    if (changed & ENCODER0) {
        status = check_encoder(status);
    }

    last_button = cur_button;
    return status;
}


static inline
int check_button(int status)
{
    const uint32_t kCUR_TICK = get_msTicks();

    const bool isDebounced = kCUR_TICK >= last_button_down_ticks + kBUTTON_DEBOUNCE_TICKS;
    if (isDebounced) {
        return status;
    }

    //NOTE: check single push
    //NOTE: button released
    if (cur_button & BUTTON0) {
        status |= EVT_BUTTON_SINGLE_CLICK;
        return status;
    }

    //NOTE: check double push
    //NOTE: button pushed
    const bool is_double_clicked = kCUR_TICK < last_button_down_ticks + kBUTTON_DOUBLE_TICKS;

    if (is_double_clicked) {
        status |= EVT_BUTTON_DOUBLE_CLICK;
        return status;
    }

    last_button_down_ticks = kCUR_TICK;
    return status;
}


static inline
int check_encoder(int status)
{
#if 0
    const uint32_t kCUR_TICK = get_msTicks();

    if (!(cur_button & ENCODER0)) {
        if (kCUR_TICK > last_button_down_ticks + 1) {
            const int kE = cur_button & 0b011;
            //printf("%d\n", e);
            if (kE == 0) {
                status |= ENCODER_UP;
                return status;
            } else if (kE == 2) {
                status |= ENCODER_DOWN;
                return status;
            }
            last_button_down_ticks = kCUR_TICK;
            return status;
        }
    }
#endif
    return status;
}


#ifdef __cplusplus
} // namespace rotaryenc
#endif

