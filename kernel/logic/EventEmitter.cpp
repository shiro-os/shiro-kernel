#include "EventEmitter.hpp"

void EventEmitter::removeListener(EmitterCallback* callback) {
    if(this->head->callback == callback) {
        this->head = 0;
    }
    if(this->tail->callback == callback) {
        this->tail = 0;
    }

    EmitterNode* current = this->head;
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

void EventEmitter::emit(const char* event) {
    if(!this->head) return;
    EmitterNode* current = this->head;
    do {
        (*current->callback)(current->args);
    } while(current = current->next);
}

void EventEmitter::on(const char* event, EmitterCallback* callback, void* args) {
    EmitterNode* node;
    if(!this->head) {
        node = this->head = this->tail = new EmitterNode();
    }
    else {
        node = new EmitterNode();
        node->prev = this->tail;
        this->tail->next = node;
        this->tail = node;
    }

    node->callback = callback;
    node->args = args;
}
