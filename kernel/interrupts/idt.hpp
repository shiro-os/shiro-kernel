#ifndef __IDT_HPP_
#define __IDT_HPP_
#include "../types.h"

extern "C" {
    struct IDT_Entry {
        uint16_t offset_lower;
        uint16_t selector;
        uint8_t null;
        uint8_t type_attribute;
        uint16_t offset_high;
    } __attribute__((packed));
    extern IDT_Entry IDT_Table;

    void idt_init();
}

#endif
