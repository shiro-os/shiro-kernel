// Default Imports
#include "constants.h"
#include "types.h"

// Dependencies
#include "util.h"
#include "condraw.h"

// TODO: .DATA SECTION STILL NEEDS FIXING!
// char pointers don't get initialized correctly


void _entry();
void init();

extern BYTE* _text;     // Text Segment
extern BYTE* _data;     // Data Segment
extern BYTE* _rodata;   // RoData Segment

void _entry() {
    init();
    while(1);
}

void init() {
    cls();
    setColor(0x02);
    setchar(CON_WIDTH/2,CON_HEIGHT/2, '|');
    setcharcolor(CON_WIDTH/2, CON_HEIGHT/2, 0xF0);

    //TODO: drawLine still crashes. Why? 
    //drawLine(1.0, 1.0, 2.0, 2.0);    
}
