/**
 * @file Terminal.cpp
 * @author Marcus Kram (m.kram@live.at), Eric Himmelbauer (eric@ehdes.com)
 * @brief Implementation of the Terminal
 * @version 0.1
 * @date 2020-11-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Terminal.hpp"
#include "constants.h"

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

    this->currentIndex = 0;
    return *this;
}

Terminal &Terminal::setFgColor(vgaTerminalColor color) {
    this->foregroundColor = color;
    return *this;
}

Terminal &Terminal::setBgColor(vgaTerminalColor color) {
    this->backgroundColor = color;
    return *this;
}

Terminal &Terminal::setCharAt(size_t x, size_t y, const char c) {
    *((uint8_t*)0xb8000 + this->pointToIndex(x, y) * 2) = c;
    return *this;
}

Terminal &Terminal::print(const char* str) {
    uint8_t *screen =((uint8_t*)0xb8000) + this->currentIndex * 2;
    size_t index = 0;
    while (str[index] != 0)
    {
        this->currentIndex++;
        *((uint8_t*)screen + 1) = (this->backgroundColor << 4) + this->foregroundColor;
        *screen = str[index];
        screen = screen + 2;
        index = index + 1;
    }
    return *this;
}

Terminal &Terminal::printLine(const char* str) {
    this->print(str);
    this->currentIndex = pointToIndex(0, this->getIndexPosY() + 1);
    return *this;
}

size_t Terminal::getIndexPosX() {
    return this->currentIndex % CON_WIDTH;
}

size_t Terminal::getIndexPosY() {
    return this->currentIndex / CON_WIDTH;
}

size_t Terminal::pointToIndex(size_t x, size_t y) {
    return y * CON_WIDTH + x;
}

Terminal &Terminal::setPointer(size_t x, size_t y) {
    this->currentIndex = this->pointToIndex(x, y);
    return *this;
}
