#ifndef __ASSERT_H_
#define __ASSERT_H_

class Assert {
public:
    static bool assert(bool check, const char* msg, char* errorBuffer);
};

#endif