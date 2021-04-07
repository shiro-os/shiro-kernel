#ifndef __IKEYBOARDLAYOUT_HPP_
#define __IKEYBOARDLAYOUT_HPP_
#include "../../../utils/string.hpp"

struct KeyMapping {
    KeyMapping();
    KeyMapping(unsigned char charIn, unsigned char mapped, String* label = 0);
    unsigned char in = 0;
    unsigned char mapped = 0;
    String* label = 0;
};

class IKeyboardLayout  {
public:
    KeyMapping* mappings;
    unsigned int mappedKeys;
    KeyMapping getMapping(unsigned char charIn);
};

#endif
