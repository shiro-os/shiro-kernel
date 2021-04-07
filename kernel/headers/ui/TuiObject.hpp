#ifndef __TUIOBJECT_HPP_
#define __TUIOBJECT_HPP_
#include "ITuiElement.hpp"

class TuiObject : public ITuiElement {
public:
    TuiObject(int x, int y, int width, int height);
    TuiObject(vec2i position, vec2i size);

    vec2i getPosition() override;
    void setPosition(int x, int y) override;
    void setPosition(vec2i vec) override;

    vec2i getSize() override;
    void setSize(int width, int height) override;
    void setSize(vec2i size) override;

    bool hasFocus() override;
    void setFocus(bool newFocus) override;
protected:
    virtual void onPositionUpdate() { };
    virtual void onSizeUpdate() { };

private:
    vec2i _position;
    vec2i _size;
    bool _hasFocus;
};

#endif
