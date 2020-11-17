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
#include "PortIo.hpp"
#include "constants.h"
#include "util.hpp"

Terminal::Terminal()
{
    Terminal::clear();
}

Terminal &Terminal::clear()
{
    uint8_t *screen = ((uint8_t*)0xb8000);
    for(auto screenItr = 0; screenItr <= CON_HEIGHT * CON_WIDTH; screenItr++) {
        *(screen + (screenItr * 2)) = ' ';
        *(screen + (screenItr * 2) + 1) = (this->backgroundColor << 4) + this->foregroundColor;
    }

    this->currentIndex = 0;
    this->setVgaCursor(this->currentIndex);
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

        this->setVgaCursor(this->currentIndex);
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

Terminal &Terminal::setVgaCursor(size_t x, size_t y) {
    size_t offset = this->pointToIndex(x, y);
    this->setVgaCursor(offset);
    return *this;
}

Terminal &Terminal::setVgaCursor(size_t offset) {
    PortIo::writeToPort(0x3D4, 0xE);
    PortIo::writeToPort(0x3D5, (unsigned char) (offset >> 8));
    PortIo::writeToPort(0x3D4, 0xF);
    PortIo::writeToPort(0x3D5, (unsigned char) (offset));
    return *this;
}

void Terminal::normalizeString(const char* str, char* normalizedString) {
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        normalizedString[i] = str[i] < 32 ? ' ' : str[i];
    }
}
