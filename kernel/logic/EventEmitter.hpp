#ifndef __EVENTEMITTER_HPP_
#define __EVENTEMITTER_HPP_

typedef void EmitterCallback(void* args);

struct EmitterNode {
    EmitterNode* prev;
    EmitterNode* next;
    EmitterCallback* callback;
    void* args;
};

class EventEmitter {
public:
    void on(const char* event, EmitterCallback* callback, void* args);
    void removeListener(EmitterCallback* callback);
    void emit(const char* event);

private:
    EmitterNode* head;
    EmitterNode* tail;
};

#endif
