#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "utils/multiboot_info.hpp"

#include "io/Terminal.hpp"
#include "io/SerialIo.hpp"
#include "io/PortIo.hpp"
#include "io/RTC.hpp"
#include "io/MemoryMgmt.hpp"
#include "shells/IShell.hpp"
#include "shells/ComShell.hpp"
#include "test/test.hpp"
#include "utils/gdt.hpp"
#include "utils/kernelutils.hpp"
#include "utils/util.hpp"
#include "interrupts/idt.hpp"
#include "interrupts/interrupt_utils.hpp"
#include "logic/EventEmitter.hpp"
#include "io/hid/Keyboard.hpp"
#include "io/hid/layouts/GermanKeyboardLayout.hpp"

extern "C"
{
    bool testA20() {
        int* a = (int*)0x112345;
        int* b = (int*)0x012345;

        int tmp0 = *a;
        int tmp1 = *b;

        *a = 1234;
        *b = 4321;

        bool result = !(*a == 4321);
        *a = tmp0;
        *b = tmp1;
        return result;
    }

    void doInterruptLoop() {
        enable_interrupts();
        while(true) {
            __asm__("hlt");
        }
        disable_interrupts();
    }

    int _entry(multiboot_info_t* mbi, unsigned int magic)
    {
        volatile auto gdt = Gdt::setupGdt();
        idt_init();
        MemoryMgmt::init(mbi);
        // Initialize PIC: All Interrupts disabled by default
        PortIo::writeToPort(0x21, 0xFF);
        PortIo::writeToPort(0xA1, 0xFF);
        // Initialize PIC: Enable certain interrupts
        enable_interrupt(1);
        enable_interrupt(2);
        enable_interrupt(8);
        enable_interrupt(12);
        RTC::getInstance()->setFrequency(13);
        RTC::getInstance()->enableIrq08();

        Terminal* ctx = new Terminal();

        ctx->setBgColor(vgaTerminalColor::VGA_COLOR_WHITE)
            ->setFgColor(vgaTerminalColor::VGA_COLOR_BLACK)
            ->clear()
            ->setFgColor(vgaTerminalColor::VGA_COLOR_GREEN)
            ->printLine("[Shiro] Shiro Kernel initialized");

        Keyboard::getInstance()->on("irq", [](void* thisObj, KeypressEvent event) {
            GermanKeyboardLayout* deLayout = GermanKeyboardLayout::getInstance();
            KeyMapping mapping = deLayout->getMapping(event.raw);

            Terminal* term = (Terminal*)thisObj;
            term->setBgColor(VGA_COLOR_BLUE);
            term->clear();

            if(mapping.mapped != 0 && mapping.label) {
                term->printLine(mapping.label->getData());
            }
            else {
                char res[10];
                itoa(event.raw, res, 10);
                term->printLine(res);
            }
        }, (void*)ctx);
        doInterruptLoop();

        return 0;
    }
}