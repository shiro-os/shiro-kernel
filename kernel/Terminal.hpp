/**
 * @file Terminal.hpp
 * @author Marcus Kram (m.kram@live.at)
 * @brief 
 * @version 0.1
 * @date 2020-03-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __TERMINAL_HPP_
#define __TERMINAL_HPP_

/**
 * Compiler Shipped Includes
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief VGA Terminal Colors - these colors a fixed by the BIOS
 */
enum vgaTerminalColor {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

/**
 * @brief Handler for all Terminal actions.
 */
class Terminal {
public:
    Terminal();
    Terminal &clear();
    Terminal &clearLine(size_t /* Line to clear */ lineNumber);
    Terminal &clearSection(size_t /*Section to Start with */ start);
    Terminal &clearSection(size_t /*Section to Start with */ start, size_t /* Section to stop */ end);
    
    Terminal &setColor(vgaTerminalColor color);
private:
    vgaTerminalColor color;

};

#endif
