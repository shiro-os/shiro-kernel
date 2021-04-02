#include "Keyboard.hpp"
#include "../PortIo.hpp"

int Keyboard::onIrq01(unsigned char charIn) {
    return charIn;
}
