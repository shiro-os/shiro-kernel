#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "io/Terminal.hpp"
#include "io/SerialIo.hpp"
#include "utils/util.hpp"
#include "shells/IShell.hpp"
#include "shells/ComShell.hpp"
#include "utils/math.h"
#include "test/assert.hpp"

extern "C"
{
    bool selfCheck(char* errorMsg) {
        if(!Assert::assert(strcmp("abcd", "abcd"), "strcmp: Failed basic compare", errorMsg)) return false;

        if(!Assert::assert(pow(10, 2) == 100, "pow: Failed calculation 1", errorMsg)) return false;
        if(!Assert::assert(pow(10, 3) == 1000, "pow: Failed calculation 2", errorMsg)) return false;
        if(!Assert::assert(pow(10, 4) == 10000, "pow: Failed calculation 3", errorMsg)) return false;
        if(!Assert::assert(pow(10, 5) == 100000, "pow: Failed calculation 4", errorMsg)) return false;

        char itoaBuff[5];
        itoa(1000, itoaBuff, 5);
        if(!Assert::assert(strcmp(itoaBuff, "1000"), "itoa: Failed conversion 1", errorMsg)) return false;

        if(!Assert::assert(atoi("1000") == 1000, "atoi: Failed conversion 1", errorMsg)) return false;


        return true;
    }

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
        if(!selfCheck(checkError)) {
            ctx.setFgColor(vgaTerminalColor::VGA_COLOR_RED)
                .printLine("[Shiro] Self-Check failed! Error:")
                .printLine(checkError);
            return 1;
        } else {
            ctx.setFgColor(vgaTerminalColor::VGA_COLOR_GREEN)
                .printLine("[Shiro] Self-Check succeeded!")
                .setFgColor(vgaTerminalColor::VGA_COLOR_BLACK);
            ComShell shell = ComShell(&serial);
            shell.writeLine("[Shiro] Initialized Shell on COM1");
            shell.runShell();
        }

        return 0;
    }
}