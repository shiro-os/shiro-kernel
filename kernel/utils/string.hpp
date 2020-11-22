#ifndef __STRING_HPP_
#define __STRING_HPP_
#include "../utils/util.hpp"

class String {
private:
    const char* data;
    int length;
public:
    String(const char* str);
    int getLength();
    void append(const char* str);
    bool equals(const char* str);
    bool equals(String str);
    const char* getData();
};

#endif