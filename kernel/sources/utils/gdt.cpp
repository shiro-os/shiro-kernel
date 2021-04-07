#include "utils/gdt.hpp"
#include "utils/util.hpp"

gdtr Gdt::setupGdt() {
    gdtr result = {};
    result.limit = (sizeof(struct GdtEntry) * 3) - 1;
    result.base = 0x800;

    GdtEntry entries[3];
    Gdt::constructEntry(0,0,0,0, (void*)&entries[0]);
    Gdt::constructEntry(0,0xFFFFFFFF,0x9A,0xCF, (void*)&entries[1]);
    Gdt::constructEntry(0,0xFFFFFFFF,0x92,0xCF, (void*)&entries[2]);

    memcpy((char*)entries, (char*)0x800, result.limit);

    asm("lgdt %0" : : "m"(result));
    asm("ljmp $0x8, $.1");
    asm(".1:");
    asm("mov %ax, 0x10");
    asm("mov %ds, %ax");
    asm("mov %es, %ax");
    asm("mov %fs, %ax");
    asm("mov %gs, %ax");
    asm("mov %ss, %ax");
    asm("mov %ds, %ax");

    return result;
}

GdtEntry Gdt::constructEntry(uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity, void* writeTo) {
    GdtEntry entry;
    entry.base_low = (base & 0xFFFF);
    entry.base_middle = (base >> 16) & 0xFF;
    entry.base_high = (base >> 24) & 0xFF;

    entry.limit_low = (limit & 0xFFFF);
    entry.granularity = ((limit >> 16) & 0x0F);

    entry.granularity |= (granularity & 0xF0);
    entry.access = access;

    if(writeTo != 0) {
        *((GdtEntry*)writeTo) = entry;
    }

    return entry;
}
