#include "../headers/TuiContainer.hpp"

TuiContainer::TuiContainer(vec2i position, vec2i size) : TuiObject(position, size) {
    children = List<TuiObject*>();
}

TuiContainer::~TuiContainer() {
    for(int i = 0; i < this->children.count(); i++) {
        delete this->children[i];
    }
}


void TuiContainer::addChild(TuiObject* child) {
    this->children.append(child);
}

void TuiContainer::removeChild(TuiObject* child) {
    for(int i = 0; i < this->children.count(); i++) {
        if(this->children[i] == child) {
            this->children.deleteAt(i);
            break;
        }
    }
}

