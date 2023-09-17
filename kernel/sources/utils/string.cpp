#include "utils/string.hpp"
#include "utils/util.hpp"

String::String(const char* str) {
    if(str != 0) {
        int len = strlen(str);
        char* newData = new char[len + 1];
        strcpy(str, newData);
        this->length = strlen(str);
        newData[this->length] = '\0';
        this->data = newData;
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
    int appendLen = strlen(str);
    int newLen = this->length + appendLen;
    char* newData = new char[newLen + 1];
    strcpy(this->data, newData);
    strcpy(str, newData + this->length);
    newData[newLen] = '\0';

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

bool String::operator == (String other) {
    return this->equals(other);
}

bool String::operator == (const char* other) {
    return this->equals(other);
}

String* String::clone() {
    return new String(this->getData());
}

String::~String() {
    delete[] this->data;
}
