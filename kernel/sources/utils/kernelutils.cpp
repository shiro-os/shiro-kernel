#include "utils/kernelutils.hpp"
#include "io/PortIo.hpp"
#include "io/Terminal.hpp"

void kernel_panic(const char* errmsg) {
    Terminal* ctx = new Terminal();

    ctx->setBgColor(vgaTerminalColor::VGA_COLOR_RED)
        ->setFgColor(vgaTerminalColor::VGA_COLOR_WHITE)
        ->clear()
        ->setPointer(0, 0)
        ->printLine("SHIRO KERNEL PANIC")->printLine("")
        ->printLine(errmsg);

    delete ctx;

    while(true);
}

void enable_interrupt(unsigned char interrupt) {
    if(interrupt > 15) {
        kernel_panic("Tried to enable invalid interrupt");
    }

    unsigned char portToRead = 0x21;
    if(interrupt >= 8) {
        portToRead = 0xA1;
        interrupt = interrupt - 8;
    }
    unsigned char oldMask = PortIo::readFromPort(portToRead);

    PortIo::writeToPort(portToRead, oldMask & ~(1 << interrupt));
}

void disable_interrupt(unsigned char interrupt) {
    if(interrupt < 1 || interrupt > 15) {
        kernel_panic("Tried to disable invalid interrupt");
    }

    unsigned char portToRead = 0x21;
    if(interrupt >= 8) {
        portToRead = 0xA1;
        interrupt = interrupt - 8;
    }
    unsigned char oldMask = PortIo::readFromPort(portToRead);

    PortIo::writeToPort(portToRead, oldMask | (1 << interrupt));
}
