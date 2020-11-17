#include "PortIo.hpp"
#include "../constants.h"

unsigned char PortIo::readFromPort(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void PortIo::writeToPort(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

int PortIo::readFromPort(unsigned short port, unsigned char* buffer, int bufferSize) {
    int i = 0;
    for(; i < bufferSize; i++) {
        buffer[i] = PortIo::readFromPort(port);
    }
    return i;
}

void PortIo::writeToPort(unsigned short port, const unsigned char* buffer, int bufferSize) {
    for(int i = 0; i < bufferSize; i++) {
        PortIo::writeToPort(port, buffer[i]);
    }
}
