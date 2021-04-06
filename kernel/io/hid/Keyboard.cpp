#include "Keyboard.hpp"
#include "../PortIo.hpp"
#include "layouts/GermanKeyboardLayout.hpp"

Keyboard* Keyboard::instance = 0;

Keyboard::Keyboard() {
    lastEvents = new Dictionary<int, KeypressEvent>();
    layout = GermanKeyboardLayout::getInstance();
}

Keyboard::~Keyboard() {
    delete lastEvents;
}

Keyboard* Keyboard::getInstance() {
    if(Keyboard::instance) {
        return Keyboard::instance;
    }

    return Keyboard::instance = new Keyboard();
}

bool Keyboard::isPressed(int keyCode) {
    KeypressEvent* lastEvent = lastEvents->getByKey(keyCode);
    return lastEvent != 0 && lastEvent->bIsPressing;
}

void Keyboard::onIrq01() {
    unsigned char charIn = PortIo::readFromPort(0x60);
    KeypressEvent kpe = KeypressEvent(charIn);
    kpe.mapping = layout->getMapping(charIn);
    Keyboard::emit("irq", kpe);
    lastEvents->insertOrUpdate(kpe.mapping.mapped, kpe);
}

KeypressEvent::KeypressEvent(unsigned char charIn) {
    this->raw = charIn;
    this->bIsReleasing = (this->raw & 0x80) > 0;
    this->bIsPressing = !this->bIsReleasing;
}
