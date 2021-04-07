#include "shells/ComShell.hpp"
#include "shells/ShellCommandExecutor.hpp"

ComShell::ComShell(SerialPort* serialPort) {
    this->serialPort = serialPort;
}

void ComShell::writeLine(const char* str) {
    this->serialPort->write((const unsigned char*) str);
    this->serialPort->write('\r');
    this->serialPort->write('\n');
}


bool ComShell::readLine(char* buf, int bufLen) {
    int i = 0;
    while(i < bufLen) {
        this->serialPort->read((unsigned char*)(buf + i), 1);

        if(buf[i] == '\r') {
            buf[i] = '\0';
            this->serialPort->write((unsigned char*)"\r\n", 2);
            i++;
            break;
        } else if(buf[i] == '\b') {
            buf[i-1] = '\0';
            buf[i] = '\0';
            i--;
            this->serialPort->write((unsigned char*)"\b \b", 3);
            continue;
        }

        this->serialPort->write((unsigned char*)(buf + i), 1);
        i++;
    }

    return true;
}


void ComShell::runShell() {
    ShellCommandExecutor executor = ShellCommandExecutor(this);

    while(1) {
        char line[1024];
        this->serialPort->write((unsigned char*)"> ", 2);
        this->readLine(line, 1024);
        if(!executor.executeLine(line)) {
            this->writeLine("Unknown command.");
        }
    }
}
