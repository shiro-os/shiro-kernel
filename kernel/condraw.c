// Default Imports
#include "constants.h"
#include "types.h"

// Dependencies
#include "math.h"
#include "util.h"
#include "condraw.h"

void drawLine(double fromX, double fromY, double toX, double toY) {
    double currentX = fromX;
    double currentY = fromY;

    while(absd(currentX - fromX) >= 0.25) {
        while(absd(currentY - fromY) >= 0.25) {

            if(currentY - fromY > 0) {
                currentY -= 0.25;
            } else {
                currentY += 0.25;
            }
        }
        if(currentX - fromX > 0) {
            currentX -= 0.25;
        } else {
            currentX += 0.25;
        }
    }
}