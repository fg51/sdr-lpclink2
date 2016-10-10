#include "driver/rotary_enc.h"

#ifdef __cplusplus
namespace rotaryenc {
#endif

#include "driver/common_driver.h"
#include "driver/rotary_enc_event.h"
#include "driver/rotary_enc_core.h"
#include "driver/rotary_enc_button_statemachine.h"


event_t update_button_encoder(uint32_t tick)
{
    uint32_t btn_data = read_button_data();
    // pushed: 0b011, not-pushed: 0b111
    const bool kIS_PUSHED = (btn_data & 0b100)? false: true;

    update_button_state(kIS_PUSHED, tick);
    event_t event = get_button_event();
    if (event != NO_EVENT) { return event;}

    return ((btn_data & 0b001) == 0b000) ? EVT_ENCODER_UP
            : ((btn_data & 0b010) == 0b000) ? EVT_ENCODER_DOWN
            : NO_EVENT;
}





#ifdef __cplusplus
} // namespace rotaryenc
#endif

