#include "RTC.hpp"
#include "PortIo.hpp"
#include "../utils/kernelutils.hpp"
#include "../utils/string.hpp"

long RTC::currentTime = 0;
long RTC::currentTick = 0;

long RTC::getCurrentTime() {
    return RTC::currentTime;
}

long RTC::getTick() {
    return RTC::currentTick;
}

void RTC::enableIrq08() {
    PortIo::writeToPort(0x70, 0x8B);
    unsigned char prevVal = PortIo::readFromPort(0x71);
    PortIo::writeToPort(0x70, 0x8B);
    PortIo::writeToPort(0x71, prevVal | 0x40);
}

void RTC::onIrq08() {
    // If we don't read this, IRQ08 doesn't get fired again in some cases
    PortIo::writeToPort(0x70, 0x0C);
    PortIo::readFromPort(0x71);
    RTC::currentTick++;
}

void RTC::setFrequency(unsigned char frequency) {
    if(frequency < 3 || frequency > 15) {
        String errStr = String("Tried to set RTC to an invalid frequency: ");
        errStr.append(frequency);
        kernel_panic(errStr.getData());
    }

    unsigned char rate = frequency & 0x0F;
    disable_interrupts();
    PortIo::writeToPort(0x70, 0x8A);
    unsigned char prevVal = PortIo::readFromPort(0x71);
    PortIo::writeToPort(0x70, 0x8A);
    PortIo::writeToPort(0x71, (prevVal & 0xF0) | rate);
    enable_interrupts();
}
