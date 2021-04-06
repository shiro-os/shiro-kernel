#ifndef __KEYBOARD_HPP_
#define __KEYBOARD_HPP_
#include "../../logic/EventEmitter.hpp"
#include "../../logic/collections/Dictionary.hpp"
#include "layouts/IKeyboardLayout.hpp"

#define KEYBOARD_PORT_STATUS 0x64
#define KEYBOARD_PORT_BUFFER 0x60

struct KeypressEvent {
public:
    KeypressEvent(unsigned char charIn);
    unsigned char raw;
    bool bIsPressing;
    bool bIsReleasing;
    KeyMapping mapping;
};

class Keyboard : public EventEmitter<KeypressEvent> {
public:
    Keyboard();
    ~Keyboard();
    static Keyboard* getInstance();
    void onIrq01();
    bool isPressed(int keyCode);
    Dictionary<int, KeypressEvent>* lastEvents;
    IKeyboardLayout* layout;
private:
    static Keyboard* instance;
};

#endif