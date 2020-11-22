#ifndef __GDT_HPP_
#define __GDT_HPP_
#include "../types.h"

struct gdtr {
    uint8_t limit;
    uint16_t base;
};

struct GdtEntry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
};

class Gdt {
public:
    static gdtr setupGdt();
    static GdtEntry constructEntry(uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity, void* writeTo) ;
};

#endif