#include "../headers/TuiObject.hpp"

TuiObject::TuiObject(int x, int y, int width, int height) : TuiObject::TuiObject(vec2i(x, y), vec2i(width, height)) { }

TuiObject::TuiObject(vec2i position, vec2i size) {
    this->_position = position;
    this->_size = size;
}


void TuiObject::setPosition(int x, int y) {
    this->setPosition(vec2i(x, y));
}

void TuiObject::setPosition(vec2i vec) {
    this->_position = vec;
    this->onPositionUpdate();
}


bool TuiObject::hasFocus() {
    return this->_hasFocus;
}

void TuiObject::setFocus(bool newFocus) {
    this->_hasFocus = newFocus;
}


vec2i TuiObject::getSize() {
    return this->_size;
}

void TuiObject::setSize(int width, int height) {
    this->setSize(vec2i(width, height));
}

void TuiObject::setSize(vec2i size) {
    this->_size = size;
}
