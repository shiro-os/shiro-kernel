// Default Imports
#include "constants.h"
#include "types.h"

// Dependencies
#include "util.h"
#include "condraw.h"
#include "math.h"


int abs(int val) {
    if(val < 0) val = -val;
    return val;
}
double absd(double val) {
    if(val < 0) val = -val;
    return val;
}
float absf(float val) {
    if(val < 0) val = -val;
    return val;
}