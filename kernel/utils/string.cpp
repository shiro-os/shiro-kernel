#include "string.hpp"
#include "../utils/util.hpp"

String::String(const char* str) {
    if(str != 0) {
        int len = strlen(str);
        char* newData = new char[len + 1];
        strcpy(str, newData);
        this->data = newData;
        this->length = strlen(str);
        return;
    }

    this->data = new char[1];
    this->length = 0;
}

String::String(int num) {
    char* ibuf = new char[10];
    int chars = itoa(num, ibuf, 10);
    this->data = ibuf;
    this->length = chars;
}

void String::append(int i) {
    char* ibuf = new char[10];
    itoa(i, ibuf, 10);
    this->append(ibuf);
    delete[] ibuf;
}

void String::append(const char* str) {
    int appendLen = strlen(this->data);
    int newLen = this->length + appendLen;
    char* newData = new char[newLen];
    strcpy(this->data, newData);
    strcpy(str, newData + this->length);
    newData[newLen + 1] = '\0';

    delete this->data;
    this->data = newData;
    this->length = newLen;
}

const char* String::getData() {
    return this->data;
}

int String::getLength() {
    return this->length;
}

bool String::equals(const char* str) {
    return strcmp(this->data, str);
}

bool String::equals(String str) {
    return strcmp(this->data, str.data);
}

String::~String() {
    delete[] this->data;
}
