#include "string.hpp"
#include "../utils/util.hpp"

String::String(const char* str) {
    if(str != 0) {
        this->data = str;
        this->length = strlen(str);
        return;
    }

    char newData[this->length];
    this->data = newData;
    this->length = 0;
}

void String::append(const char* str) {
    int appendLen = strlen(this->data);
    int newLen = this->length + appendLen;
    char newData[newLen];
    strcpy(this->data, newData);
    strcpy(str, newData + this->length);

    this->data = newData;
    this->length = newLen;
}

const char* String::getData() {
    return this->data;
}

int String::getLength() {
    return this->length;
}
