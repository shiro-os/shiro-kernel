#ifndef __SHELLCOMMANDEXECUTOR_HPP
#define __SHELLCOMMANDEXECUTOR_HPP

#include "ICommandExecutor.hpp"
#include "IShell.hpp"

class ShellCommandExecutor {
    public:
        ShellCommandExecutor(IShell* shell);
        bool executeLine(const char* str);
    
    private:
        IShell* shell;
};

#endif