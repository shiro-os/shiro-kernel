#include "test/assert.hpp"
#include "utils/util.hpp"

bool Assert::assert(bool check, const char* msg, char* errorBuffer){
    if(!check && errorBuffer != 0) strcpy(msg, errorBuffer);
    return check;
}