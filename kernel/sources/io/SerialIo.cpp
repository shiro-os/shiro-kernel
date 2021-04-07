#include "io/SerialIo.hpp"
#include "io/PortIo.hpp"
#include "utils/util.hpp"

SerialPort::SerialPort(serialPort port) {
    this->port = port;
    this->initSerial();
}

SerialPort* SerialPort::initSerial() {
    PortIo::writeToPort(this->port + 1, 0x00);
    PortIo::writeToPort(this->port + 3, 0x80);
    PortIo::writeToPort(this->port, 0x03);
    PortIo::writeToPort(this->port + 1, 0x00);
    PortIo::writeToPort(this->port + 3, 0x03);
    PortIo::writeToPort(this->port + 2, 0xC7);
    PortIo::writeToPort(this->port + 4, 0x0B);
    return this;
}

SerialPort* SerialPort::write(const unsigned char* buf, int bufLen) {
    PortIo::writeToPort(this->port, buf, bufLen);
    return this;
}

SerialPort* SerialPort::write(const unsigned char buf) {
    PortIo::writeToPort(this->port, buf);
    return this;
}

SerialPort* SerialPort::write(const unsigned char* str) {
    PortIo::writeToPort(this->port, str, strlen(str));
    return this;
}

SerialPort* SerialPort::read(unsigned char* buf, int bufLen) {
    int read = 0;
    while(read < bufLen) {
        while((PortIo::readFromPort(this->port + 5) & 0x1) == 0);
        buf[read] = PortIo::readFromPort(this->port);
        read++;
    }

    return this;
}

SerialPort* SerialPort::readUntil(unsigned char* buf, int bufLen, const unsigned char* pattern, int patternLen) {
    int read = 0;
    int iP = 0;
    while(read < bufLen) {
        while((PortIo::readFromPort(this->port + 5) & 0x1) == 0);
        buf[read] = PortIo::readFromPort(this->port);

        if(pattern[iP] == buf[read++]) {
            if(++iP >= patternLen) {
                return this;
            }
        } else {
            iP = 0;
        }
    }

    return this;
}


SerialPort* SerialPort::readNoWait(unsigned char* buf, int bufLen, int* readBytes) {
    int read = 0;
    while((PortIo::readFromPort(this->port + 5) & 0x1) != 0 && read < bufLen) {
        buf[read] = PortIo::readFromPort(this->port);
        bufLen++;
    }

    if(readBytes != 0) {
        *readBytes = read;
    }

    return this;
}