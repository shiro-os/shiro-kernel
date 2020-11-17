#ifndef __COMSHELL_HPP_
#define __COMSHELL_HPP_

#include "IShell.hpp"
#include "../io/SerialIo.hpp"

class ComShell : public IShell {
    public:
        ComShell(SerialPort* serialPort);
        void writeLine(const char* str);
        bool readLine(char* buf, int bufLen);
        void runShell();

    private:
        SerialPort* serialPort;
};

#endif