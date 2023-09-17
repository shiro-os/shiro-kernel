#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "utils/multiboot_info.hpp"
#include "io/Terminal.hpp"
#include "io/PortIo.hpp"
#include "io/RTC.hpp"
#include "io/MemoryMgmt.hpp"
#include "test/test.hpp"
#include "utils/gdt.hpp"
#include "utils/kernelutils.hpp"
#include "interrupts/idt.hpp"
#include "interrupts/interrupt_utils.hpp"
#include "io/hid/Keyboard.hpp"
#include "io/hid/layouts/Keys.h"
#include "ui/tui.hpp"

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

    void init(multiboot_info_t* mbi) {
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
    }

    int _entry(multiboot_info_t* mbi, unsigned int magic)
    {
        init(mbi);
        char* errorMessage = new char[255];
        Test::selfCheck(errorMessage);

        if(strlen(errorMessage) != 0) {
            kernel_panic(errorMessage);
        }

        Terminal* ctx = new Terminal();

        ctx->setBgColor(vgaTerminalColor::VGA_COLOR_WHITE)
            ->setFgColor(vgaTerminalColor::VGA_COLOR_BLACK)
            ->clear()
            ->setFgColor(vgaTerminalColor::VGA_COLOR_GREEN)
            ->printLine("Self-Check successfully completed")
            ->printLine("Shiro Kernel initialized");

        enable_interrupts();

        while(true) {
            if(Keyboard::getInstance()->isPressed(KEY_A)) {
                ctx->printLine("Homie");
            }
            asm volatile("hlt");
        }

        doInterruptLoop();

        return 0;
    }
}