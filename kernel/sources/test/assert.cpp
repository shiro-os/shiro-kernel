#include "test/assert.hpp"
#include "utils/util.hpp"

bool Assert::assert(bool check, const char* errorMsg, const char* successMsg, char* messageBuffer){
    if(!check && messageBuffer != 0) strcpy(errorMsg, messageBuffer);
    if(check && messageBuffer != 0 && successMsg != 0) strcpy(successMsg, messageBuffer);
    return check;
}