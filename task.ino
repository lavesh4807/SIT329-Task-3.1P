#include "GPIO_DEAKIN.h"
#include "sam.h"

enum PinMode {
    INPUT_MODE,
    OUTPUT_MODE
};

enum PinState {
    LOW_STATE,
    HIGH_STATE
};

bool validatePortAndPin(char PortNum, char PinNum) {
    if ((PortNum != 'A' && PortNum != 'B') || PinNum < 0 || PinNum > 31) {
        return false;
    }
    return true;
}

bool GPIO_DEAKIN::Config_GPIO(char PortNum, char PinNum, PinMode mode) {
    if (!validatePortAndPin(PortNum, PinNum)) {
        return false;
    }

    PortGroup *port = (PortNum == 'A') ? &PORT->Group[0] : &PORT->Group[1];

    if (mode == OUTPUT_MODE) {
        port->DIRSET.reg = (1 << PinNum);
    } else if (mode == INPUT_MODE) {
        port->DIRCLR.reg = (1 << PinNum);
    } else {
        return false;
    }

    return true;
}

bool GPIO_DEAKIN::Write_GPIO(char PortNum, char PinNum, PinState state) {
    if (!validatePortAndPin(PortNum, PinNum)) {
        return false;
    }

    PortGroup *port = (PortNum == 'A') ? &PORT->Group[0] : &PORT->Group[1];

    if (state == HIGH_STATE) {
        port->OUTSET.reg = (1 << PinNum);
    } else if (state == LOW_STATE) {
        port->OUTCLR.reg = (1 << PinNum);
    } else {
        return false;
    }

    return true;
}

bool GPIO_DEAKIN::Read_GPIO(char PortNum, char PinNum) {
    if (!validatePortAndPin(PortNum, PinNum)) {
        return false;
    }

    PortGroup *port = (PortNum == 'A') ? &PORT->Group[0] : &PORT->Group[1];

    return (port->IN.reg & (1 << PinNum)) != 0;
}
