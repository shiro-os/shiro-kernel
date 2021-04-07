/**
 * @file Terminal.hpp
 * @author Marcus Kram (m.kram@live.at), Eric Himmelbauer (eric@ehdes.com)
 * @brief
 * @version 0.1
 * @date 2020-11-16
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
    /**
     * @brief Construct a new Terminal object
     *
     */
    Terminal();

    /**
     * @brief Clears the whole terminal screen and resets the offset.
     * color
     * @return Terminal&
     */
    Terminal* clear();

    /**
     * @brief Clears a line, removes Background and foreground color.
     *
     * @param lineNumber
     * @return Terminal&
     */
    Terminal* clearLine(size_t /* Line to clear */ lineNumber);

    /**
     * @brief Clears a section of the terminal from starting point until end of terminal
     *
     * @param start
     * @return Terminal&
     */
    Terminal* clearSection(size_t /*Section to Start with */ start);

    /**
     * @brief Clears a section of the terminal from starting pointer until endpoint.
     *
     * @param start
     * @param end
     * @return Terminal&
     */
    Terminal* clearSection(size_t /*Section to Start with */ start, size_t /* Section to stop */ end);

    /**
     * @brief Set the Color which should be used for text
     * Previous text is not affected by this function, only new text which should be inserted.
     *
     * @param color
     * @return Terminal&
     */
    Terminal* setFgColor(vgaTerminalColor color);

    /**
     * @brief Set the Backgroundcolor which should be used as the color behind text.
     * Previous text is not affected by this function, only new text which should be inserted.
     *
     * @param color
     * @return Terminal&
     */
    Terminal* setBgColor(vgaTerminalColor color);

    /**
     * @brief Prints text on the current offset.
     *
     * @param str
     * @return Terminal&
     */
    Terminal* print(const char* str);

    /**
     * @brief Prints a char on the specified coordinates.
     *
     * @param str
     * @return Terminal&
     */
    Terminal* setCharAt(size_t x, size_t y, const char c);

    /**
     * @brief Prints text on the current offset, and updates the offset to x=0; y=currentLine+1
     *
     * @param str
     * @return Terminal&
     */
    Terminal* printLine(const char* str);

    /**
     * @brief Sets the current offset to the specified coordinates
     *
     * @param x
     * @param y
     * @return Terminal&
     */
    Terminal* setPointer(size_t x, size_t y);

    Terminal* setVgaCursor(size_t offset);
    Terminal* setVgaCursor(size_t x, size_t y);

    static void normalizeString(const char* str, char* normalizedString);

private:
    vgaTerminalColor foregroundColor = vgaTerminalColor::VGA_COLOR_WHITE;
    vgaTerminalColor backgroundColor = vgaTerminalColor::VGA_COLOR_BLACK;
    /**
     * @brief The current offset of the terminal.
     */
    size_t currentIndex = 0;
    /**
     * @brief Translates current offset to X position
     *
     * @return size_t
     */
    size_t getIndexPosX();
    /**
     * @brief Translates current offset to Y position
     *
     * @return size_t
     */
    size_t getIndexPosY();
    /**
     * @brief Translates coordinates to console-offset
     *
     * @param x
     * @param y
     * @return size_t
     */
    size_t pointToIndex(size_t x, size_t y);
};

#endif
