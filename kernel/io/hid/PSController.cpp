#include "PSController.hpp"
#include "../PortIo.hpp"

void PSController::disable() {
    PortIo::writeToPort(PSCONTROLLER_PORT_STATUS, 0xAD);
}

void PSController::enable() {
    PortIo::writeToPort(PSCONTROLLER_PORT_STATUS, 0xAE);
}

void PSController::reset() {
    PortIo::writeToPort(PSCONTROLLER_PORT_STATUS, 0xFE);
}

void PSController::interfaceTest() {
    PortIo::writeToPort(PSCONTROLLER_PORT_STATUS, 0xAB);
}

void PSController::selfTest() {
    PortIo::writeToPort(PSCONTROLLER_PORT_STATUS, 0xAA);
}
