/**
 * @file Terminal.cpp
 * @author Marcus Kram (m.kram@live.at)
 * @brief Implementation of the Terminal
 * @version 0.1
 * @date 2020-03-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Terminal.hpp"

Terminal::Terminal() 
{
    Terminal::clear();
}

Terminal &Terminal::clear()
{
    uint8_t *screen = ((uint8_t*)0xb8000);
    for(auto screenItr = 0; screenItr <= 2000; screenItr++) {
        *(screen + screenItr++) = ' ';
    }
    return *this;
}

Terminal &Terminal::setColor(vgaTerminalColor color) {
    this->color = color;
    return *this;
}