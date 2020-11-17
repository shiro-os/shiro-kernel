#include "ShellCommandExecutor.hpp"
#include "../utils/util.hpp"

ShellCommandExecutor::ShellCommandExecutor(IShell* shell) {
    this->shell = shell;
}

bool ShellCommandExecutor::executeLine(const char* str) {
    if(strcmp(str, "hello")) {
        this->shell->writeLine("Hello World!");
        return true;
    }

    int num = atoi(str);
    char buf[64];
    itoa(num, buf, 64);

    this->shell->writeLine(buf);

    return true;
}