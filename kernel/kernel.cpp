#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "Terminal.hpp"
#include "SerialIo.hpp"
#include "util.hpp"

extern "C"
{
    int _entry(void)
    {
        Terminal ctx;
        SerialPort serial = SerialPort(serialPort::COM1).initSerial();
        serial.write((const unsigned char*)"[Shiro] Initialized COM1 Serial connection");

        ctx.setBgColor(vgaTerminalColor::VGA_COLOR_WHITE)
            .setFgColor(vgaTerminalColor::VGA_COLOR_BLACK)
            .clear();

        char test[5];
        itoa(1234, test, 4);

        ctx.setFgColor(vgaTerminalColor::VGA_COLOR_GREEN)
            .printLine("[Shiro] Shiro Kernel initialized\0")
            .printLine("OIDA")
            .printLine(test)
            .printLine("Lmao");


        return 0;
    }
}