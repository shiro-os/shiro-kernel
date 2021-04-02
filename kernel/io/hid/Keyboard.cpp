#include "Keyboard.hpp"
#include "../PortIo.hpp"

Keyboard* Keyboard::instance = 0;

Keyboard* Keyboard::getInstance() {
    if(Keyboard::instance) {
        return Keyboard::instance;
    }

    return Keyboard::instance = new Keyboard();
}


void Keyboard::onIrq01(unsigned char charIn) {
    Keyboard::emit("irq", (unsigned int*)charIn);
}
