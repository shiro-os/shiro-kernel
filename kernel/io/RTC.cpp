#include "RTC.hpp"
#include "PortIo.hpp"
#include "../utils/kernelutils.hpp"

RTC* RTC::instance = 0;

RTC* RTC::getInstance() {
    if(RTC::instance) {
        return RTC::instance;
    }

    return RTC::instance = new RTC();
}

long RTC::getCurrentTime() {
    return this->currentTime;
}

long RTC::getTick() {
    return this->currentTick;
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
    this->currentTick++;
    this->emit("tick");
}

void RTC::setFrequency(unsigned char frequency) {
    if(frequency < 3 || frequency > 15) {
        kernel_panic("Tried to set RTC to an invalid frequency.");
    }

    unsigned char rate = frequency & 0x0F;
    disable_interrupts();
    PortIo::writeToPort(0x70, 0x8A);
    unsigned char prevVal = PortIo::readFromPort(0x71);
    PortIo::writeToPort(0x70, 0x8A);
    PortIo::writeToPort(0x71, (prevVal & 0xF0) | rate);
    enable_interrupts();
}
