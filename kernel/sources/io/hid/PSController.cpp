#include "io/hid/PSController.hpp"
#include "io/PortIo.hpp"
#include "utils/kernelutils.hpp"

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


void PSController::writePort(unsigned char port, unsigned char byte) {
    if(port == 1) {
        PSController::writePortOne(byte);
    }
    else if(port == 2) {
        PSController::writePortTwo(byte);
    }
    else {
        kernel_panic("Tried to write invalid PSController port");
    }
}

void PSController::writePortOne(unsigned char byte) {
    unsigned char status = PortIo::readFromPort(PSCONTROLLER_PORT_STATUS);
}

void PSController::writePortTwo(unsigned char byte) {
    
}
