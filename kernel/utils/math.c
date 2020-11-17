// Default Imports
#include "../constants.h"
#include "../types.h"

// Dependencies
#include "util.hpp"
#include "math.h"

int abs(int val)
{
    return val < 0 ? -val : val;
}

double absd(double val)
{
    return val < 0 ? -val : val;
}

float absf(float val)
{
    return val < 0 ? -val : val;
}

int pow(int val, int pow) {
     if(pow == 0) {
        return 1;
    }

    pow--;
    int result = val;
    for(int i = 0; i < pow; i++) {
        result *= val;
    }
    return result;
}
