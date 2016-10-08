/*
 *
 * what is Status
 *  in lpc_types.h
 *  typedef enum Status {ERROR = 0, SUCCESS = !ERROR, } Status;
 */

//{{{includes
#include "driver/i2c_LCD.h"

#include <lpc43xx_gpio.h>
#include <lpc43xx_i2c.h>

//#include "clock_cfg.h"
#include "driver/timer.h"
//}}}


//{{{ static globals
enum {max_tx_length = 2,};

static I2C_M_SETUP_Type setup = {};
//}}}


//{{{ prot-type functions
static Status i2clcd_cmd(const uint8_t cmd);
static Status i2clcd_data(const uint8_t data);
//}}}


#ifdef __cplusplus
namespace driverI2CLCD {
#endif

void init_i2clcd(void)
{
    #ifndef D_I2C_OFF
    setup.sl_addr7bit = 0x7c >> 1;
    //setup.tx_data   = buf;
    setup.tx_length   = max_tx_length;
    setup.rx_data     = NULL;
    setup.rx_length   = 0;
    setup.retransmissions_max = 3;


    I2C_Init(LPC_I2C0, 10000);
    I2C_Cmd(LPC_I2C0, ENABLE);

    driverTimer::systick_delay(40);

    i2clcd_cmd(0x38);
    i2clcd_cmd(0x39);
    i2clcd_cmd(0x14);
    i2clcd_cmd(0x70);
    i2clcd_cmd(0x56);
    i2clcd_cmd(0x6c);

    driverTimer::systick_delay(200);

    i2clcd_cmd(0x38);
    i2clcd_cmd(0x0c);
    i2clcd_cmd(0x01);
    #endif

    driverTimer::systick_delay(2);
}



void i2clcd_pos(uint8_t x, uint8_t y)
{
#ifndef D_I2C_OFF
    i2clcd_cmd(0x80 | (0x40 * y) | x);
#endif
}


/**
 * max number of char is 8 [chr].
 */
void puts_lcd(const char *p)
{
#ifndef D_I2C_OFF
    while (*p != '\0') {i2clcd_data(*p++);}
#endif
}

#ifdef __cplusplus
} //namespace driverI2CLCD
#endif


static Status i2clcd_cmd(const uint8_t cmd)
{
    uint8_t buf[max_tx_length] = {0, cmd};
    setup.tx_data = buf;
    Status s = I2C_MasterTransferData(LPC_I2C0, &setup, I2C_TRANSFER_POLLING);
    //if (s != SUCCESS) { printf("I2C Failed\n"); }
    return s;
}


static Status i2clcd_data(uint8_t const data)
{
    uint8_t buf[max_tx_length] = {0x40, data,};
    setup.tx_data = buf;
    return I2C_MasterTransferData(LPC_I2C0, &setup, I2C_TRANSFER_POLLING);
}



/**
 * NOTE:
 * declared in lpc43xx_libcfg_default.h,
 */
#ifdef DEBUG
extern "C" {
void check_failed(uint8_t *file, uint32_t line)
{
/* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

/* Infinite loop */
while(1);
}
}
#endif

