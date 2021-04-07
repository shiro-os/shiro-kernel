#ifndef __STRING_HPP_
#define __STRING_HPP_
#include "util.hpp"

class String {
private:
    const char* data;
    int length;
public:
    String(const char* str);
    String(int str);
    ~String();
    int getLength();
    void append(const char* str);
    void append(int i);
    bool equals(const char* str);
    bool equals(String str);
    const char* getData();
    String* clone();

    bool operator == (String other);
    bool operator == (const char* other);
};

#endif