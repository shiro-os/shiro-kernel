#ifndef __EVENTEMITTER_HPP_
#define __EVENTEMITTER_HPP_

typedef void EmitterCallback(unsigned int thisobj, unsigned int* args, unsigned int* eventArgs);

struct EmitterNode {
    EmitterNode* prev;
    EmitterNode* next;
    EmitterCallback* callback;
    unsigned int* args;
    unsigned int thisObj;
};

class EventEmitter {
public:
    void on(const char* event, EmitterCallback* callback, unsigned int* args, unsigned int thisObj);
    void removeListener(EmitterCallback* callback);
    void emit(const char* event, unsigned int* eventArgs = 0);

private:
    EmitterNode* head;
    EmitterNode* tail;
};

#endif
