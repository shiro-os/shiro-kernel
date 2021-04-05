#ifndef __KEYBOARD_HPP_
#define __KEYBOARD_HPP_
#include "../../logic/EventEmitter.hpp"

#define KEYBOARD_PORT_STATUS 0x64
#define KEYBOARD_PORT_BUFFER 0x60

struct KeypressEvent {
public:
    KeypressEvent(unsigned char charIn);
    unsigned char raw;
    bool bIsPressing;
    bool bIsReleasing;
};

class Keyboard : public EventEmitter<KeypressEvent> {
public:
    static Keyboard* getInstance();
    void onIrq01();
private:
    static Keyboard* instance;
};

#endif