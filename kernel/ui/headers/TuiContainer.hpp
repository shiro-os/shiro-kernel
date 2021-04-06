#ifndef __TUICONTAINER_HPP_
#define __TUICONTAINER_HPP_
#include "TuiObject.hpp"
#include "../../logic/collections/List.hpp"

class TuiContainer : public TuiObject {
public:
    TuiContainer(vec2i position, vec2i size);
    ~TuiContainer();

    void addChild(TuiObject* child);
    void removeChild(TuiObject* child);
protected:
    List<TuiObject*> children;
private:
};

#endif
