#include "GPIO_DEAKIN.h"
#include "sam.h"

bool GPIO_DEAKIN::Config_GPIO(char PortNum, char PinNum, char Mode) {
    // Determine the port
    PortGroup *port;
    if (PortNum == 'A') {
        port = &PORT->Group[0];
    } else if (PortNum == 'B') {
        port = &PORT->Group[1];
    } else {
        return false;
    }
    
    // Configure pin as input or output
    if (Mode == OUTPUT) {
        port->DIRSET.reg = (1 << PinNum);
    } else if (Mode == INPUT) {
        port->DIRCLR.reg = (1 << PinNum);
    } else {
        return false;
    }
    
    return true;
}

bool GPIO_DEAKIN::Write_GPIO(char PortNum, char PinNum, bool State) {
    PortGroup *port;
    if (PortNum == 'A') {
        port = &PORT->Group[0];
    } else if (PortNum == 'B') {
        port = &PORT->Group[1];
    } else {
        return false;
    }

    if (State == HIGH) {
        port->OUTSET.reg = (1 << PinNum);
    } else if (State == LOW) {
        port->OUTCLR.reg = (1 << PinNum);
    } else {
        return false;
    }

    return true;
}

bool GPIO_DEAKIN::Read_GPIO(char PortNum, char PinNum) {
    PortGroup *port;
    if (PortNum == 'A') {
        port = &PORT->Group[0];
    } else if (PortNum == 'B') {
        port = &PORT->Group[1];
    } else {
        return false;
    }

    return (port->IN.reg & (1 << PinNum)) != 0;
}