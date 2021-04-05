#include "Keyboard.hpp"
#include "../PortIo.hpp"

Keyboard* Keyboard::instance = 0;

Keyboard* Keyboard::getInstance() {
    if(Keyboard::instance) {
        return Keyboard::instance;
    }

    return Keyboard::instance = new Keyboard();
}

void Keyboard::onIrq01() {
    unsigned char charIn = PortIo::readFromPort(0x60);
    KeypressEvent kpe = KeypressEvent(charIn);
    Keyboard::emit("irq", kpe);
}

KeypressEvent::KeypressEvent(unsigned char charIn) {
    this->raw = charIn;
    this->bIsReleasing = (this->raw & 0x80) > 0;
    this->bIsPressing = !this->bIsReleasing;
}
