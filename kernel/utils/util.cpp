#include "../constants.h"
#include "util.hpp"
#include "math.h"

int strlen(const char* str)
{
    int len = 0;
    while (str[len] != 0)
    {
        len++;
    }
    return len;
}

int strlen(const unsigned char* str)
{
    return strlen((const char*)str);
}

int strcpy(const char* src, char* dst) {
    int len = strlen(src);
    int i = 0;
    for(; i < len; i++) {
        dst[i] = src[i];
    }
    return i;
}

bool strcmp(const char* str0, const char* str1) {
    const char* s0 = str0;
    const char* s1 = str1;

    while(*s0 != '\0' || *s1 != '\0') {
        if(*s0 != *s1) {
            return false;
        }
        s0++;
        s1++;
    }

    return true;
}

int atoi(const char* str) {
    int result = 0;
    int len = strlen(str);
    bool isMinus = false;

    for(int i = 0; i < len; i++) {
        if(str[i] == 0x2D) {
            isMinus = true;
            continue;
        }

        if(str[i] < 0x30 || str[i] > 0x39) {
            return 0;
        }

        result += (str[i] - 0x30) * pow(10, len - i - 1);
    }

    return isMinus ? -result : result;
}

int itoa(int num, char* buf, int bufSize) {
    int steps = 0;
    int digits = 1;
    for(int i = num; i / 10 > 0; i /= 10, digits++);

    for(int curNum = num % 10; steps < bufSize && steps < digits && num > 0; steps++, curNum = (num = num / 10) % 10) {
        buf[digits - steps - 1] = curNum + 0x30;
    }

    return steps;
}
