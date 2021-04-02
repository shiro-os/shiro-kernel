#ifndef __KEYBOARD_HPP_
#define __KEYBOARD_HPP_
#define KEYBOARD_PORT_STATUS 0x64
#define KEYBOARD_PORT_BUFFER 0x60

class Keyboard {
public:
    static void disable();
    static void enable();
    static void reset();
    static void selfTest();
    static void interfaceTest();
    static void onIrq01(uint8_t input);
private:
};

#endif