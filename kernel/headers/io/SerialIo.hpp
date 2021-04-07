#ifndef __SERIALPORT_HPP_
#define __SERIALPORT_HPP_

enum serialPort {
    COM1 = 0x3f8,
    COM2 = 0x2f8,
    COM3 = 0x3e8,
    COM4 = 0x2e8
};

class SerialPort {
    public:
        SerialPort(serialPort port);
        SerialPort* initSerial();
        SerialPort* write(const unsigned char* buf, int bufLen);
        SerialPort* write(const unsigned char* str);
        SerialPort* write(const unsigned char buf);

        SerialPort* read(unsigned char* buf, int bufLen);
        SerialPort* readUntil(unsigned char* buf, int bufLen, const unsigned char* pattern, int patternLen);
        SerialPort* readNoWait(unsigned char* buf, int bufLen, int* readBytes);

    private:
        serialPort port;
};

#endif