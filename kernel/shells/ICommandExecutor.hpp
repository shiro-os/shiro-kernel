#ifndef __ICOMMANDEXECUTOR_HPP_
#define __ICOMMANDEXECUTOR_HPP_

class ICommandExecutor {
    public:
        bool executeLine(const char* str);
};

#endif