#ifndef __LIST_HPP_
#define __LIST_HPP_
#include "../../utils/kernelutils.hpp"
#include "../../utils/util.hpp"

template <typename T>
class List {
public:
    List(int initialLength = 32, int autoExpand = 0) {
        _length = initialLength;
        _count = 0;
        _elements = new T[_length];
        _autoExpand = autoExpand;
    }

    ~List() {
        delete[] _elements;
    }

    int count() {
        return _count;
    }

    void append(T value) {
        if(_length == _count) {
            if(_autoExpand > 0) {
                int newLength = _length + _autoExpand;
                T* newElements = new T[newLength];
                memcpy((const char*)_elements, (char*)newElements, sizeof(T) * _length);
                delete[] _elements;
                _elements =  newElements;
                _length = newLength;
            }
            else {
                kernel_panic("Failed to increase space of list: No autoexpansion");
            }
        }
        _elements[_count] = value;
        _count = _count + 1;
    }

    void setElementAt(int i, T value) {
        if(i >= _count) {
            return;
        }
        _elements[i] = value;
    }

    T elementAt(int i) {
        if(i < _count) {
            return _elements[i];
        }
        return 0;
    }

    T operator [](int i) {
        return elementAt(i);
    }

    List<T>* clone() {
        List<T>* result = new List<T>(_length, _autoExpand);
        result->_count = _count;
        for(int i = 0; i < count(); i++) {
            result[i] = this[i];
        }
        return result;
    }
private:
    T* _elements;
    int _count;
    int _length;
    int _autoExpand;
};

#endif