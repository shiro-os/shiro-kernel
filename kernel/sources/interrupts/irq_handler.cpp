#include "interrupts/irq_handler.hpp"
#include "io/PortIo.hpp"
#include "io/SerialIo.hpp"
#include "io/hid/Keyboard.hpp"
#include "io/RTC.hpp"

void irq00_handler() {
    PortIo::writeToPort(0x20, 0x20);
}

void irq01_handler() {
    PortIo::writeToPort(0x20, 0x20);
    Keyboard::getInstance()->onIrq01();
    PortIo::writeToPort(0x20, 0x20);
}

void irq02_handler() {
    PortIo::writeToPort(0x20, 0x20);
}

void irq03_handler() {
    PortIo::writeToPort(0x20, 0x20);
}

void irq04_handler() {
    PortIo::writeToPort(0x20, 0x20);
}

void irq05_handler() {
    PortIo::writeToPort(0x20, 0x20);
}

void irq06_handler() {
    PortIo::writeToPort(0x20, 0x20);
}

void irq07_handler() {
    PortIo::writeToPort(0x20, 0x20);
}

void irq08_handler() {
    PortIo::writeToPort(0xA0, 0x20);
    RTC::getInstance()->onIrq08();
    PortIo::writeToPort(0x20, 0x20);
}

void irq09_handler() {
    PortIo::writeToPort(0xA0, 0x20);
    PortIo::writeToPort(0x20, 0x20);
}

void irq10_handler() {
    PortIo::writeToPort(0xA0, 0x20);
    PortIo::writeToPort(0x20, 0x20);
}

void irq11_handler() {
    PortIo::writeToPort(0xA0, 0x20);
    PortIo::writeToPort(0x20, 0x20);
}

void irq12_handler() {
    PortIo::writeToPort(0xA0, 0x20);
    PortIo::writeToPort(0x20, 0x20);
}

void irq13_handler() {
    PortIo::writeToPort(0xA0, 0x20);
    PortIo::writeToPort(0x20, 0x20);
}

void irq14_handler() {
    PortIo::writeToPort(0xA0, 0x20);
    PortIo::writeToPort(0x20, 0x20);
}

void irq15_handler() {
    PortIo::writeToPort(0xA0, 0x20);
    PortIo::writeToPort(0x20, 0x20);
}
