#include "constants.h"
#include "types.h"
#include "util.hpp"

int strlen(const char* str)
{
    int len = 0;
    while (str[len] != 0)
    {
        len++;
    }
    return len;
}

int strdup(const char* src, char* dst) {
    int len = strlen(src);
    int i = 0;
    for(; i < len; i++) {
        dst[i] = src[i];
    }
    return i;
}

int atoi(const char* str) {
    int result = 0;
    int len = strlen(str);

    char lmao[len];
    for(int i = 0; i < len; i++) {
        if(str[i] < 0x30 || str[i] > 0x39) {
            return 0;
        }

        result += str[i] - 0x30 * 10^(len - 1);
    }

    return result;
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
