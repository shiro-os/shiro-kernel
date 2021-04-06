#include "LinkedList.hpp"

template <typename T>
LinkedNode<T>::LinkedNode(T val, bool deleteOnDestruction) {
    this->value = val;
    this->deleteOnDestruction = deleteOnDestruction;
    this->before = 0;
    this->after = 0;
}

template <typename T>
LinkedListEnumerator<T>::LinkedListEnumerator(LinkedNode<T>* begin, int direction) {
    this->direction = direction;
    this->begin = begin;
    this->currentNode = 0;
}

template <typename T>
void LinkedListEnumerator<T>::reset() {
    this->currentNode = this->begin;
}

template <typename T>
T* LinkedListEnumerator<T>::current() {
    return this->currentNode->value;
}

template <typename T>
T* LinkedListEnumerator<T>::next() {
    if(!this->currentNode) {
        this->currentNode = this->begin;
        if(!this->currentNode) return 0;
        return &this->currentNode->value;
    }

    this->currentNode = this->direction == LLE_Direction_Forward ? this->currentNode->after : this->currentNode->before;
    if(!this->currentNode) return 0;
    return &this->currentNode->value;
}

template <typename T>
bool LinkedList<T>::deleteVal(T value) {
    IEnumerator<T> enumerator = this->getEnumerator();
    LinkedNode<T> current;
    while(current = enumerator.next()) {
        if(current.value == value) {
            return this->deleteNode(current);
        };
    }
    return false;
}

template <typename T>
bool LinkedList<T>::deleteNode(LinkedNode<T>* node) {
    if(!node) return false;

    if(this->head == node) {
        this->head = this->head->after ? this->head->after : 0;
    }

    if(this->tail == node) {
        this->tail = this->tail->before ? this->tail->before : 0;
    }

    if(node->before) {
        node->before->after = node->after;
    }

    if(node->after) {
        node->after->before = node->before;
    }

    if(node->deleteOnDestruction) {
        delete (void*)node->value;
    }

    return true;
};

template <typename T>
bool LinkedList<T>::contains(T value) {
    IEnumerator<T> enumerator = this->getEnumerator();
    LinkedNode<T> current;
    while(current = enumerator.next()) {
        if(current.value == value) return true;
    }
    return false;
}

template <typename T>
void LinkedList<T>::append(T value) {
    LinkedNode<T>* node = new LinkedNode<T>(value);

    if(this->tail)  {
        node->before = this->tail;
        this->tail->after = node;
        this->tail = node;
    }
    else {
        this->head = node;
        this->tail = node;
    }
}

template <typename T>
LinkedListEnumerator<T> LinkedList<T>::getEnumerator() {
    return LinkedListEnumerator<T>(this->head, LLE_Direction_Forward);
}

template <typename T>
LinkedList<T>::~LinkedList() {
    LinkedNode<T>* current = this->head;
    while(current) {
        LinkedNode<T>* next = current->after;
        if(current->deleteOnDestruction) {
            delete (void*)current->value;
        }
        delete current;
        current =  next;
    }
}
