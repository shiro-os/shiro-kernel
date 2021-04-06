#ifndef __ITUIELEMENT_HPP_
#define __ITUIELEMENT_HPP_
#include "../../utils/vectors.hpp"

class ITuiElement {
public:
    virtual vec2i getPosition() = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual void setPosition(vec2i pos) = 0;

    virtual vec2i getSize() = 0;
    virtual void setSize(int width, int height) = 0;
    virtual void setSize(vec2i size);

    virtual bool hasFocus();
    virtual void setFocus(bool newFocus);
};

#endif
