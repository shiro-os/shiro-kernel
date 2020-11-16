// Default Imports
#include "constants.h"
#include "types.h"

// Dependencies
#include "util.h"
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