#ifndef __PSController_HPP_
#define __PSController_HPP_
#define PSCONTROLLER_PORT_STATUS 0x64
#define PSCONTROLLER_PORT_BUFFER 0x60

class PSController {
public:
    static void disable();
    static void enable();
    static void reset();
    static void selfTest();
    static void interfaceTest();
    static void writePort(unsigned char port, unsigned char byte);
private:
    static void writePortOne(unsigned char byte);
    static void writePortTwo(unsigned char byte);
};

#endif