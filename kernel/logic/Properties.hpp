#ifndef __PROPERTIES_HPP_
#define __PROPERTIES_HPP_
#include "../utils/string.hpp"

template <typename T>
struct Property {
    String* name;
    T value;
};

class PropertySet {
    template <typename T>
    T getProperty(String* name);
};

#endif