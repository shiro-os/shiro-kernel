#include "interrupt_utils.hpp"
#include "../types.h"
#include "../utils/kernelutils.hpp"
#include "../io/PortIo.hpp"

void initRq8() {
    disable_interrupts();
    PortIo::writeToPort(0x80, 0x8B);
    uint8_t inFlags = PortIo::readFromPort(0x71);
    PortIo::writeToPort(0x70, 0x8A);
    PortIo::writeToPort(0x71, (inFlags | 0x40));
    enable_interrupts();
}
