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
    KeypressEvent* kpe = new KeypressEvent(charIn);
    Keyboard::emit("irq", (unsigned int*)kpe);
    delete kpe;
}

KeypressEvent::KeypressEvent(unsigned char charIn) {
    this->raw = charIn;
    // TODO: REWORK!!!
    // This is not how you're supposed to do it, and it's also
    // extremely buggy if not unusable this way.
    this->bIsPressing = this->raw & 0x80 > 0;
    this->bIsReleasing = !this->bIsPressing;
}

unsigned char KeypressEvent::getRaw() {
    return this->raw;
}

bool KeypressEvent::isPressing() {
    return this->bIsPressing;
}

bool KeypressEvent::isReleasing() {
    return this->bIsReleasing;
}
