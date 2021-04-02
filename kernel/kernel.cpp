#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "io/Terminal.hpp"
#include "io/SerialIo.hpp"
#include "io/PortIo.hpp"
#include "shells/IShell.hpp"
#include "shells/ComShell.hpp"
#include "test/test.hpp"
#include "utils/gdt.hpp"
#include "utils/kernelutils.hpp"
#include "utils/util.hpp"
#include "interrupts/idt.hpp"
#include "interrupts/interrupt_utils.hpp"

extern "C"
{
    bool testA20() {
        int* a = (int*)0x112345;
        int* b = (int*)0x012345;

        int tmp0 = *a;
        int tmp1 = *b;

        *a = 1234;
        *b = 4321;

        bool result = !(*a == 4321);
        *a = tmp0;
        *b = tmp1;
        return result;
    }

    int _entry()
    {
        volatile auto gdt = Gdt::setupGdt();
        idt_init();
        // Initialize PIC
        PortIo::writeToPort(0x21, 0xFD);
        PortIo::writeToPort(0xA1, 0xFF);

        Terminal ctx;
        SerialPort serial = SerialPort(serialPort::COM1).initSerial();
        serial.write((const unsigned char*)"[Shiro] Initialized COM1 Serial connection\r\n");

        ctx.setBgColor(vgaTerminalColor::VGA_COLOR_WHITE)
            .setFgColor(vgaTerminalColor::VGA_COLOR_BLACK)
            .clear();

        ctx.setFgColor(vgaTerminalColor::VGA_COLOR_GREEN)
            .printLine("[Shiro] Shiro Kernel initialized")
            .printLine("[Shiro] Starting self-check...");

        if(testA20()) {
            ctx.printLine("[Shiro] A20 Line set!");
        } else {
            ctx.setFgColor(vgaTerminalColor::VGA_COLOR_RED)
                .printLine("[Shiro] A20 Line not set!");
        }

        enable_interrupts();
        while(true) {
            __asm__("hlt");
        }
        disable_interrupts();

        char checkError[1024];
        if(!Test::selfCheck(checkError)) {
            ctx.setFgColor(vgaTerminalColor::VGA_COLOR_RED)
                .printLine("[Shiro] Self-Check failed! Error:")
                .printLine(checkError);
            return 1;
        } else {
            ctx.setFgColor(vgaTerminalColor::VGA_COLOR_GREEN)
                .printLine("[Shiro] Self-Check succeeded!")
                .setFgColor(vgaTerminalColor::VGA_COLOR_BLACK);
            ComShell shell = ComShell(&serial);
            ctx.printLine("[Shiro] Initialized Shell on COM1");
            shell.writeLine("[Shiro] Initialized Shell on COM1");
            shell.runShell();
        }

        return 0;
    }
}