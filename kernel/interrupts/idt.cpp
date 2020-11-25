#include "idt.hpp"
#include "../io/PortIo.hpp"
#include "../types.h"

extern "C" {
    void idt_init() {
        extern int idt_load(uint64_t* idtDescriptor);
        extern int irq0();
        extern int irq1();
        extern int irq2();
        extern int irq3();
        extern int irq4();
        extern int irq5();
        extern int irq6();
        extern int irq7();
        extern int irq8();
        extern int irq9();
        extern int irq10();
        extern int irq11();
        extern int irq12();
        extern int irq13();
        extern int irq14();
        extern int irq15();

        uint64_t irqHandlers[] = {
            (uint64_t)irq0,
            (uint64_t)irq1,
            (uint64_t)irq2,
            (uint64_t)irq3,
            (uint64_t)irq4,
            (uint64_t)irq5,
            (uint64_t)irq6,
            (uint64_t)irq7,
            (uint64_t)irq8,
            (uint64_t)irq9,
            (uint64_t)irq10,
            (uint64_t)irq11,
            (uint64_t)irq12,
            (uint64_t)irq13,
            (uint64_t)irq14,
            (uint64_t)irq15,
        };

        PortIo::writeToPort(0x20, 0x11);
        PortIo::writeToPort(0xA0, 0x11);
        PortIo::writeToPort(0x21, 0x20);
        PortIo::writeToPort(0xA1, 0x28);
        PortIo::writeToPort(0x21, 0x04);
        PortIo::writeToPort(0xA1, 0x02);
        PortIo::writeToPort(0x21, 0x01);
        PortIo::writeToPort(0xA1, 0x01);
        PortIo::writeToPort(0x21, 0x00);
        PortIo::writeToPort(0xA1, 0x00);

        int curTableIndex = 32;
        for(int i = 0; i <= 15; i++, curTableIndex++) {
            IDT_Entry* currentEntry = &IDT_Table[curTableIndex];
            currentEntry->offset_lower = irqHandlers[i] & 0x0000FFFF;
            currentEntry->selector = 0x08;
            currentEntry->null = 0x00;
            currentEntry->type_attribute = 0x8E;
            currentEntry->offset_high = (irqHandlers[i] & 0xFFFF0000) >> 16;
        }

        uint64_t pIdt[2];
        pIdt[0] = (sizeof(struct IDT_Entry) * 256) + (((uint64_t)IDT_Table & 0x0000FFFF) << 16);
        pIdt[1] = (((uint64_t)IDT_Table) & 0xFFFF0000) >> 16;

        idt_load(pIdt);
    }
}
