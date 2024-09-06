// TIMER_DEAKIN.h

#ifndef TIMER_DEAKIN_H
#define TIMER_DEAKIN_H

#include <Arduino.h>

class TIMER_DEAKIN {
public:
    bool config_timer(uint8_t timer_num, uint16_t start_count, uint16_t end_count, float resolution);
    uint16_t getTC0_count();
    void wait(float period);

private:
    void configureClock(uint8_t timer_num);
};

#endif
