#include "constants.h"
#include "types.h"
#include "util.h"

void setchar(int x, int y, char c) {
    y = y * CON_WIDTH * 2;
    x = ++x * 2;
    ((char *)0xb8000)[(x + y)] = c;
}

void setcharcolor(int x, int y, BYTE color) {
    y = y * CON_WIDTH * 2;
    x = ++x * 2;
    ((char *)0xb8000 + 1)[(x + y)] = color;
}

int strlen(char * str) {
    int len = 0;
    while(str[len] != 0) {
        len++;
    }
    return len;
}

void cls() {
   BYTE* video_memory = VIDMEM;
   for(int i = 0; i < 2000; i++) {
       *video_memory = ' ';
       video_memory = (BYTE*)(video_memory + 2);
   } 
}

void setColor(BYTE color) {
   BYTE* video_memory = (BYTE*)(VIDMEM + 1);
   for(int i = 0; i < 2000; i++) {
       *video_memory = color;
       video_memory = video_memory + 2;
   } 
}

void print(char * msg) {
    BYTE* video_memory = VIDMEM;
    int index = 0;
    while(msg[index] != 0) {
        *video_memory = msg[index];
        video_memory = video_memory + 2;
        index = index + 1;
    }
}