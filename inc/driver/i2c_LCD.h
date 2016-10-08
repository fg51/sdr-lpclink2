#ifndef D_I2C_LCD_H
#define D_I2C_LCD_H

#include <stdint.h>


#ifdef __cplusplus
namespace driverI2CLCD {
#endif

void init_i2clcd(void);
void i2clcd_pos(const uint8_t x, const uint8_t y);
void puts_lcd(const char *p);

} //namespace driverI2CLCD

#endif  /* D_I2C_LCD_H */
