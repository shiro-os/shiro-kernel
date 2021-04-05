#ifndef __EVENTEMITTER_HPP_
#define __EVENTEMITTER_HPP_
#include "../utils/util.hpp"

template <typename T>
struct EmitterNode {
    EmitterNode<T>* prev;
    EmitterNode<T>* next;
    T callback;
    void* thisObj;
    const char* trigger;
};

template <typename T>
class EventEmitter {
public:
    typedef void(*EmitterCallback)(void* thisObj, T eventArgs);

    void on(const char* event, EmitterCallback callback, void* thisObj) {
        EmitterNode<EmitterCallback>* node;
        if(!this->head) {
            node = this->head = this->tail = new EmitterNode<EmitterCallback>();
        }
        else {
            node = new EmitterNode<EmitterCallback>();
            node->prev = this->tail;
            this->tail->next = node;
            this->tail = node;
        }

        node->callback = callback;
        node->thisObj = thisObj;
        node->trigger = event;
    }

    void removeListener(void* callback) {
        if(this->head->callback == callback) {
            this->head = 0;
        }
        if(this->tail->callback == callback) {
            this->tail = 0;
        }

        EmitterNode<EmitterCallback>* current = this->head;
        if(!this->head) return;
        do {
            if(current->callback == callback) {
                if(current->prev) {
                    current->prev->next = current->next;
                }
                if(current->next) {
                    current->next->prev = current->prev;
                }
                break;
            }
        } while(current = current->next);
    }

    void emit(const char* event, T eventArgs = 0) {
        if(!this->head) return;
        EmitterNode<EmitterCallback>* current = this->head;
        do {
            if(strcmp(current->trigger, event)) {
                (*current->callback)(current->thisObj, eventArgs);
            }
        } while(current = current->next);
    }

private:
    EmitterNode<EmitterCallback>* head;
    EmitterNode<EmitterCallback>* tail;
};

#endif
