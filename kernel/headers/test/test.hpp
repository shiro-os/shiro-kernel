#include "build-settings.h"
#if RUN_TESTS == true
#ifndef __TEST_HPP_
#define __TEST_HPP_

class Test {
    public:
        static bool selfCheck(char* errorMsg);
};

#endif
#endif
