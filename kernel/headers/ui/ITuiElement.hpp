#ifndef __ITUIELEMENT_HPP_
#define __ITUIELEMENT_HPP_
#include "utils/vectors.hpp"
#include "utils/kernelutils.hpp"

class ITuiElement {
public:
    virtual vec2i getPosition() { };
    virtual void setPosition(int x, int y) { };
    virtual void setPosition(vec2i pos) { };

    virtual vec2i getSize() { };
    virtual void setSize(int width, int height) { };
    virtual void setSize(vec2i size) { };

    virtual bool hasFocus() { };
    virtual void setFocus(bool newFocus) { };
};

#endif
