#ifndef __PORTIO_HPP_
#define __PORTIO_HPP_

/**
 * Compiler Shipped Includes
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

class PortIo {
public:
    static unsigned char readFromPort(unsigned short port);
    static void writeToPort(unsigned short port, unsigned char data);

    static int readFromPort(unsigned short port, unsigned char* buffer, int bufferSize);
    static void writeToPort(unsigned short port, const unsigned char* buffer, int bufferSize);

private:
    
};

#endif
