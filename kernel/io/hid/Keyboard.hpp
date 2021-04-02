#ifndef __PSController_HPP_
#define __PSController_HPP_
#define KEYBOARD_PORT_STATUS 0x64
#define KEYBOARD_PORT_BUFFER 0x60

class Keyboard {
public:
    static void onIrq01(unsigned char charIn);
private:
};

#endif