/*
 * @file timer.cpp
 * @date Sep 4, 2016
 * @brife systick driver
 */

#ifdef __cplusplus
namespace driverTimer {
extern "C" {
#endif


#include <stdint.h>
#include <lpc43xx_cgu.h> // **_CGU_** functions
#include <lpc43xx_emc.h> // emc_WaitUS


//  SysTick_Handler - just increment SysTick counter
volatile static uint32_t msTicks; // counter for 1ms SysTicks

/*! Frequency of external xtal */
#define XTAL_FREQ  (12000000UL)


//in lpc43xx_cgu.c
extern uint32_t CGU_ClockSourceFrequency[CGU_CLKSRC_NUM];



/**
 * change the clock to 204 [MHz]
 */
void setup_systemclock(void)
{
    /* enable the crystal oscillator */
    CGU_SetXTALOSC(XTAL_FREQ);
    CGU_EnableEntity(CGU_CLKSRC_XTAL_OSC, ENABLE);

    /* connect the cpu to the xtal */
    CGU_EntityConnect(CGU_CLKSRC_XTAL_OSC, CGU_BASE_M4);

    /* connect the PLL to the xtal */
    CGU_EntityConnect(CGU_CLKSRC_XTAL_OSC, CGU_CLKSRC_PLL1);

    /* configure the PLL to 120 MHz */
    CGU_SetPLL1(10);
    while((LPC_CGU->PLL1_STAT&1) == 0x0);

    /* enable the PLL */
    CGU_EnableEntity(CGU_CLKSRC_PLL1, ENABLE);

    /* connect to the CPU core */
    CGU_EntityConnect(CGU_CLKSRC_PLL1, CGU_BASE_M4);

    SystemCoreClock = 120000000;

    /* wait one msec */
    emc_WaitUS(1000);

    /* Change the clock to 204 MHz */
    CGU_SetPLL1(17);
    while((LPC_CGU->PLL1_STAT&1) == 0x0);

    SystemCoreClock = 204000000;

    CGU_ClockSourceFrequency[CGU_CLKSRC_PLL1] = SystemCoreClock;
}


/*
 * @brief Setup SysTick Timer to interrupt at 1 msec intervals
 */
void init_systick(void)
{
    SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000);

}


void SysTick_Handler(void) {
    msTicks++;
}


/*
 * systick_delay
 * - creates a delay of the appropriate number of Systicks (happens every 1 ms)
 */
void systick_delay(const uint32_t kDelayTicks) {
    const uint32_t kCurrentTicks = msTicks;    //NOTE: read current tick counter
    // Now loop until required number of ticks passes.
    while ((msTicks - kCurrentTicks) < kDelayTicks);
}


uint32_t get_msTicks(void)
{
    return msTicks;
}


#ifdef __cplusplus
} // extern "C"
} // namespace driverTimer
#endif
