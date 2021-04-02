#include <stdint.h>
#include "Keyboard.hpp"
#include "../PortIo.hpp"

void Keyboard::disable() {
    PortIo::writeToPort(KEYBOARD_PORT_STATUS, 0xAD);
}

void Keyboard::enable() {
    PortIo::writeToPort(KEYBOARD_PORT_STATUS, 0xAE);
}

void Keyboard::reset() {
    PortIo::writeToPort(KEYBOARD_PORT_STATUS, 0xFE);
}

void Keyboard::interfaceTest() {
    PortIo::writeToPort(KEYBOARD_PORT_STATUS, 0xAB);
}

void Keyboard::selfTest() {
    PortIo::writeToPort(KEYBOARD_PORT_STATUS, 0xAA);
}

void Keyboard::onIrq01(uint8_t charIn) {
    
}
