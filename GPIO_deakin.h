#ifndef GPIO_DEAKIN_H
#define GPIO_DEAKIN_H

#include "sam.h"

class GPIO_DEAKIN {
public:
    bool Config_GPIO(char PortNum, char PinNum, char Mode);
    bool Write_GPIO(char PortNum, char PinNum, bool State);
    bool Read_GPIO(char PortNum, char PinNum);
    
    // New methods for Task 3.1C
    bool Config_GPIO_Group(char PortNum, char* PinArray, char Mode);
    bool GPIO_Display_Pattern(char PortNum, char* PinArray, char GPIOPattern);
    void Run_Lights(char PortNum, char* PinArray, unsigned int delayTime);
};

#endif // GPIO_DEAKIN_H
