#ifndef __IENUMERATOR_HPP_
#define __IENUMERATOR_HPP_

template <typename T>
class IEnumerator {
public:
    T* next();
    T* current();
};

#endif
