// TIMER_DEAKIN.cpp

#include "TIMER_DEAKIN.h"

bool TIMER_DEAKIN::config_timer(uint8_t timer_num, uint16_t start_count, uint16_t end_count, float resolution) {
    // Enable the timer in the Power Management Controller (PM)
    PM->APBCMASK.reg |= (1 << (PM_APBCMASK_TC0_Pos + timer_num));

    // Configure the clock source and prescaler
    configureClock(timer_num);

    // Configure the timer
    Tc *TCx = (timer_num == 0) ? TC0 : TC1;  // Assuming TC0 and TC1 only
    TCx->COUNT16.CTRLA.reg = TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV1;
    TCx->COUNT16.COUNT.reg = start_count;
    TCx->COUNT16.CC[0].reg = end_count;

    // Enable the timer
    TCx->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;

    return true;
}

uint16_t TIMER_DEAKIN::getTC0_count() {
    // Return the current counter value of Timer 0
    return TC0->COUNT16.COUNT.reg;
}

void TIMER_DEAKIN::wait(float period) {
    // Configure the timer for the wait period
    uint16_t ticks = static_cast<uint16_t>(period * 10);  // Convert period to 0.1 ms ticks
    config_timer(0, 0, ticks, 0.1);

    // Polling the timer until it reaches the value
    while (TC0->COUNT16.COUNT.reg < ticks) {
        // Wait until the timer reaches the desired value
    }

    // Reset the timer
    TC0->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
}

void TIMER_DEAKIN::configureClock(uint8_t timer_num) {
    // Configure the Generic Clock for the timer
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCM_TC0_TC1 + timer_num) | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_CLKEN;
    while (GCLK->STATUS.bit.SYNCBUSY);
}
