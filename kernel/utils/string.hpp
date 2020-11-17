#ifndef __STRING_HPP_
#define __STRING_HPP_

class String {
private:
    const char* data;
    int length;
public:
    String(const char* str);
    int getLength();
    void append(const char* str);
    const char* getData();
};

#endif