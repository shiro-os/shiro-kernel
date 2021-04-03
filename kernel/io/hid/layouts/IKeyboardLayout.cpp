#include "IKeyboardLayout.hpp"

KeyMapping::KeyMapping() {
    this->in = 0;
    this->mapped = 0;
    this->label = 0;
}

KeyMapping::KeyMapping(unsigned char charIn, unsigned char mapped, String* label) {
    this->in = charIn;
    this->mapped = mapped;
    this->label = label;
}

KeyMapping IKeyboardLayout::getMapping(unsigned char charIn) {
    charIn = charIn & 0x7F;
    for(int i = 0; i < this->mappedKeys; i++) {
        if(this->mappings[i].in == charIn) {
            return this->mappings[i];
        }
    }
    return KeyMapping(0, 0);
}
