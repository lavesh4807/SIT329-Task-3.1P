#include "GPIO_DEAKIN.h"
#include <Arduino.h>  // Include this for Serial

bool GPIO_DEAKIN::Config_GPIO(char PortNum, char PinNum, char Mode) {
    uint32_t pin = (1 << PinNum);
    Serial.println(pin);
    uint8_t Num;
    if (PortNum == 'A') {
        Num = 0;
    } else if (PortNum == 'B') {
        Num = 1;
    } else {
        return false;
    }

    if (Mode == 'O') {
        PORT->Group[Num].DIR.reg |= pin;
    } else if (Mode == 'I') {
        PORT->Group[Num].DIR.reg &= ~pin;
    } else {
        return false;
    }
    return true;
}

bool GPIO_DEAKIN::Write_GPIO(char PortNum, char PinNum, bool State) {
    uint32_t pin = (1 << PinNum);
    uint8_t Num;
    if (PortNum == 'A') {
        Num = 0;
    } else if (PortNum == 'B') {
        Num = 1;
    } else {
        return false;
    }

    if (State) {
        PORT->Group[Num].OUT.reg |= pin;
    } else {
        PORT->Group[Num].OUT.reg &= ~pin;
    }
    return true;
}

bool GPIO_DEAKIN::Read_GPIO(char PortNum, char PinNum) {
    uint32_t pin = (1 << PinNum);
    uint8_t Num;
    if (PortNum == 'A') {
        Num = 0;
    } else if (PortNum == 'B') {
        Num = 1;
    } else {
        return false;
    }

    return (PORT->Group[Num].IN.reg & pin) != 0;
}

bool GPIO_DEAKIN::Config_GPIO_Group(char PortNum, char* PinArray, char Mode) {
    uint32_t pinMask = 0;
    for (int i = 0; i < 6; i++) {
        pinMask |= (1 << PinArray[i]);
    }

    uint8_t Num;
    if (PortNum == 'A') {
        Num = 0;
    } else if (PortNum == 'B') {
        Num = 1;
    } else {
        return false;
    }

    if (Mode == 'O') {
        PORT->Group[Num].DIR.reg |= pinMask;
    } else if (Mode == 'I') {
        PORT->Group[Num].DIR.reg &= ~pinMask;
    } else {
        return false;
    }
    return true;
}

bool GPIO_DEAKIN::GPIO_Display_Pattern(char PortNum, char* PinArray, char GPIOPattern) {
    uint32_t pinMask = 0;
    for (int i = 0; i < 6; i++) {
        if (GPIOPattern & (1 << i)) {
            pinMask |= (1 << PinArray[i]);
        }
    }

    uint8_t Num;
    if (PortNum == 'A') {
        Num = 0;
    } else if (PortNum == 'B') {
        Num = 1;
    } else {
        return false;
    }

    PORT->Group[Num].OUT.reg |= pinMask;
    PORT->Group[Num].OUT.reg &= ~((~GPIOPattern) & 0x3F); // Clear bits that should be off
    return true;
}

void GPIO_DEAKIN::Run_Lights(char PortNum, char* PinArray, unsigned int delayTime) {
    while (true) {
        for (int i = 0; i < 6; i++) {
            Write_GPIO(PortNum, PinArray[i], true);
            delay(delayTime);
            Write_GPIO(PortNum, PinArray[i], false);
        }
        for (int i = 5; i >= 0; i--) {
            Write_GPIO(PortNum, PinArray[i], true);
            delay(delayTime);
            Write_GPIO(PortNum, PinArray[i], false);
        }
    }
}
