#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "Terminal.hpp"

extern "C"
{
    int _entry(void)
    {
        Terminal ctx;
        ctx.setFgColor(vgaTerminalColor::VGA_COLOR_RED)
            .printLine("[Shiro] Shiro Kernel initialized\0")
            .setFgColor(vgaTerminalColor::VGA_COLOR_GREEN)
            .printLine("[Shiro] Bingus imsd 1 nicer kadser\0")
            .setFgColor(vgaTerminalColor::VGA_COLOR_GREEN)
            .setBgColor(vgaTerminalColor::VGA_COLOR_WHITE)
            .printLine("[Shiro] I have top level autism\0")
            .setCharAt(50, 10, 'X');

        return 0;
    }
}