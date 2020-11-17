#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "Terminal.hpp"
#include "util.hpp"

extern "C"
{
    int _entry(void)
    {
        Terminal ctx;
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