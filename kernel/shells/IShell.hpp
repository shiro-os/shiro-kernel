#ifndef __ISHELL_HPP_
#define __ISHELL_HPP_

class IShell {
    public:
        virtual void writeLine(const char* str) {};
        virtual bool readLine(char* buf, int bufLen) { return false; };
        virtual void runShell() {};
};

#endif