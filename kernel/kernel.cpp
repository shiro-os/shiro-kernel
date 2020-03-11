/**
 * @file kernel.cpp
 * @author Marcus Kram (m.kram@live.at)
 * @brief 
 * @version 0.1
 * @date 2020-03-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "Terminal.hpp"

extern "C"
{
    int _entry(void)
    {
        Terminal ctx;
        ctx.setColor(VGA_COLOR_GREEN);
        return 0;
    }
}