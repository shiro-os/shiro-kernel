#ifndef __PSController_HPP_
#define __PSController_HPP_
#include "../../logic/EventEmitter.hpp"

#define KEYBOARD_PORT_STATUS 0x64
#define KEYBOARD_PORT_BUFFER 0x60

class Keyboard : public EventEmitter{
public:
    static Keyboard* getInstance();
    void onIrq01(unsigned char charIn);
private:
    static Keyboard* instance;
};

#endif