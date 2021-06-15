#ifndef __DICTIONARY_HPP_
#define __DICTIONARY_HPP_
#include "List.hpp"

template <typename TKey, typename TValue>
struct KeyValuePair {
    KeyValuePair(TKey key = 0, TValue value = 0) {
        this->key = key;
        this->value = value;
    }
    TKey key = 0;
    TValue value = 0;
};

template <typename TKey, typename TValue>
class Dictionary : private List<KeyValuePair<TKey, TValue>*> {
public:
    void insert(TKey key, TValue value) {
        KeyValuePair<TKey, TValue>* entry = new KeyValuePair<TKey, TValue>(key, value);
        this->append(entry);
    }

    TValue update(TKey key, TValue value) {
        KeyValuePair<TKey, TValue>* node = getNodeByKey(key);
        TValue oldValue = node->value;
        node->value = value;
        return oldValue;
    }

    TValue insertOrUpdate(TKey key, TValue value) {
        if(contains(key)) {
            return update(key, value);
        }
        else {
            insert(key, value);
            return value;
        }
    }

    bool contains(TKey key) {
        return getByKey(key) != 0;
    }

    TValue* getByKey(TKey key) {
        KeyValuePair<TKey, TValue>* node = getNodeByKey(key);
        return node ? &node->value : 0;
    }

    TValue* operator [](TKey key) const {
        return getByKey(key);
    }

    void remove(TKey key) {
        this->deleteAt(this->getNodeIndexByKey(key));
    }

    int count() {
        return this->_length;
    }
private:
    KeyValuePair<TKey, TValue>* getNodeByKey(TKey key) {
        for(int i = 0; i < this->_count; i++) {
            if(this->_elements[i]->key == key) return this->_elements[i];
        }
        return 0;
    }

    int getNodeIndexByKey(TKey key) {
        for(int i = 0; i < this->_count; i++) {
            if(this->_elements[i]->key == key) return i;
        }
        return -1;
    }
};

#endif
