#include "idt.hpp"
#include "../io/PortIo.hpp"
#include "../types.h"

extern "C" {
    void idt_init() {
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

        int a = PortIo::readFromPort(0x21);
        int b = PortIo::readFromPort(0xA1);

        // Initializing
        PortIo::writeToPort(0x20, 0x11);
        PortIo::writeToPort(0xA0, 0x11);
        // Defining offsets
        PortIo::writeToPort(0x21, 0x20);
        PortIo::writeToPort(0xA1, 0x28);
        // Define IRQ2 as Slave Interrupt
        PortIo::writeToPort(0x21, 0x04);
        PortIo::writeToPort(0xA1, 0x02);
        // Switch mode
        PortIo::writeToPort(0x21, 0x01);
        PortIo::writeToPort(0xA1, 0x01);
        // Restore masks
        // PortIo::writeToPort(0x21, 0x00);
        // PortIo::writeToPort(0xA1, 0x00);
        PortIo::writeToPort(0x21, a);
        PortIo::writeToPort(0xA1, b);

        int curTableIndex = 32;
        IDT_Entry* IDT_Table_l = &IDT_Table;
        for(int i = 0; i <= 15; i++, curTableIndex++) {
            IDT_Table_l[curTableIndex].offset_lower = irqHandlers[i] & 0x0000FFFF;
            IDT_Table_l[curTableIndex].selector = 0x08;
            IDT_Table_l[curTableIndex].null = 0x00;
            IDT_Table_l[curTableIndex].type_attribute = 0x8E;
            IDT_Table_l[curTableIndex].offset_high = (irqHandlers[i] & 0xFFFF0000) >> 16;
        }

        struct idt_descriptor {
            uint16_t limit;
            uint32_t base;
        } __attribute__((packed));
        extern int idt_load(idt_descriptor* idtDescriptor);

        idt_descriptor pIdt;
        pIdt.limit = (sizeof(struct IDT_Entry) * 256) - 1;
        pIdt.base = (uintptr_t) IDT_Table_l;

        idt_load(&pIdt);
    }
}
