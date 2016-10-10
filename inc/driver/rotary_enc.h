#ifndef D_ROTARY_ENC_H
#define D_ROTARY_ENC_H

#ifdef __cplusplus
namespace rotaryenc {
#endif


void init_rotary_LED(void);

void turnon_ROT_RED(void);
void turnon_ROT_GREEN(void);
void turnoff_ROT_LED(void);

//----------------------------------------

#include <stdint.h>
#include "driver/rotary_enc_event.h"
void init_rotary_enc(void);
event_t update_button_encoder(uint32_t tick);


#ifdef __cplusplus
} // namespace rotaryenc
#endif

#endif //D_ROTARY_ENC_H
