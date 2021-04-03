#ifndef __PSController_HPP_
#define __PSController_HPP_
#include "../../logic/EventEmitter.hpp"

#define KEYBOARD_PORT_STATUS 0x64
#define KEYBOARD_PORT_BUFFER 0x60

class KeypressEvent {
public:
    KeypressEvent(unsigned char charIn);
    unsigned char getRaw();
    bool isPressing();
    bool isReleasing();
private:
    unsigned char raw;
    bool bIsPressing;
    bool bIsReleasing;
};

class Keyboard : public EventEmitter{
public:
    static Keyboard* getInstance();
    void onIrq01(unsigned char charIn);
private:
    static Keyboard* instance;
};

#endif