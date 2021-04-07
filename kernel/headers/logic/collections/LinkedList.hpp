#ifndef __LINKEDLIST_HPP_
#define __LINKEDLIST_HPP_
#include "../IEnumerator.hpp"

#define LLE_Direction_Forward 1
#define LLE_Direction_Backwards 2

template <typename T>
struct LinkedNode {
    LinkedNode(T val, bool deleteOnDestruction = true);
    LinkedNode<T>* before;
    LinkedNode<T>* after;
    bool deleteOnDestruction;
    T value;
};

template <typename T>
class LinkedListEnumerator : public IEnumerator<T> {
public:
    LinkedListEnumerator(LinkedNode<T>* begin, int direction = LLE_Direction_Forward);
    void reset();
    T* next();
    T* current();
private:
    LinkedNode<T>* begin;
    LinkedNode<T>* currentNode;
    int direction;
};

template <typename T>
class LinkedList {
public:
    ~LinkedList();
    LinkedListEnumerator<T> getEnumerator();
    void append(T value);
    bool deleteVal(T value);
    bool contains(T value);

private:
    LinkedNode<T>* head;
    LinkedNode<T>* tail;
    bool deleteNode(LinkedNode<T>* node);
};

#include "LinkedList.cpp"
#endif
