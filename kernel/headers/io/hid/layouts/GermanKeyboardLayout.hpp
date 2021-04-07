#ifndef __GERMANKEYBOARDLAYOUT_HPP_
#define __GERMANKEYBOARDLAYOUT_HPP_
#include "IKeyboardLayout.hpp"

class GermanKeyboardLayout : public IKeyboardLayout {
public:
    GermanKeyboardLayout();
    static GermanKeyboardLayout* getInstance();

private:
    static GermanKeyboardLayout* instance;
};

#endif
