#include "constants.h"
#include "types.h"
#include "util.h"

void setchar(int x, int y, char c)
{
    y = y * CON_WIDTH * 2;
    x = ++x * 2;
    ((char *)0xb8000)[(x + y)] = c;
}

void setcharcolor(int x, int y, uint8_t color)
{
    y = y * CON_WIDTH * 2;
    x = ++x * 2;
    ((char *)0xb8000 + 1)[(x + y)] = color;
}

int strlen(char *str)
{
    int len = 0;
    while (str[len] != 0)
    {
        len++;
    }
    return len;
}

void cls()
{
    int i = 0;
    uint8_t *video_memory = VIDMEM;
    for ( ; i < 2000; i++)
    {
        *video_memory = ' ';
        video_memory = (uint8_t *)(video_memory + 2);
    }
}

void setColor(uint8_t color)
{
    int i = 0;
    uint8_t *video_memory = (uint8_t *)(VIDMEM + 1);
    for ( ; i < 2000; i++)
    {
        *video_memory = color;
        video_memory = video_memory + 2;
    }
}

void puts(const char *msg)
{
    uint8_t *video_memory = VIDMEM;
    int index = 0;
    while (msg[index] != 0)
    {
        *video_memory = msg[index];
        video_memory = video_memory + 2;
        index = index + 1;
    }
}