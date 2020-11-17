#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "io/Terminal.hpp"
#include "io/SerialIo.hpp"
#include "shells/IShell.hpp"
#include "shells/ComShell.hpp"
#include "test/test.hpp"

extern "C"
{
    int _entry(void)
    {
        Terminal ctx;
        SerialPort serial = SerialPort(serialPort::COM1).initSerial();
        serial.write((const unsigned char*)"[Shiro] Initialized COM1 Serial connection\r\n");

        ctx.setBgColor(vgaTerminalColor::VGA_COLOR_WHITE)
            .setFgColor(vgaTerminalColor::VGA_COLOR_BLACK)
            .clear();

        ctx.setFgColor(vgaTerminalColor::VGA_COLOR_GREEN)
            .printLine("[Shiro] Shiro Kernel initialized")
            .printLine("[Shiro] Starting self-check...");

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